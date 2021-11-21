#ifdef POWER_MONITOR_PLATFORM_XTENSA

#include "afe_reader.hh"
#include "math.hh"

#include <elsen/arduino_compatibility.hh>
#include <elsen/global.hh>
#include <elsen/logger.hh>
#include <elsen/utilities.hh>

#include <gsl/gsl>
#include <hedley/hedley.h>
#include <minfft.h>

#include <driver/spi_master.h>
#include <esp_pthread.h>

#include <pthread.h>

#include <bitset>
#include <cstdint>
#include <numeric>

#define PTHREAD_CHECK(result, message)                                    \
    do                                                                    \
    {                                                                     \
        if (result != 0)                                                  \
        {                                                                 \
            ELSEN_LOG_ERROR(message ". pthread API returned {}", result); \
            for (;;)                                                      \
                ;                                                         \
        }                                                                 \
    } while (false)

namespace
{
    constexpr std::uint32_t SPI_SPEED{ 2000000 };
    constexpr std::uint8_t  CS_PIN{ 5 };

    inline void init_timer(void (*callback)(void *),
        void               *callback_argument,
        esp_timer_handle_t &timer) noexcept
    {
        auto timer_config                  = esp_timer_create_args_t{};
        timer_config.callback              = callback;
        timer_config.arg                   = callback_argument;
        timer_config.dispatch_method       = ESP_TIMER_ISR;
        timer_config.name                  = "afe_reader";
        timer_config.skip_unhandled_events = true;

        esp_timer_create(&timer_config, &timer);
    }

    inline void set_up_pthread_config() noexcept
    {
        auto esp_pthread_cfg        = esp_pthread_get_default_config();
        esp_pthread_cfg.pin_to_core = 1;
        esp_pthread_cfg.prio        = 1;
        esp_pthread_cfg.stack_size  = 256;
        esp_pthread_cfg.thread_name = "afe_reader";
        ESP_ERROR_CHECK(esp_pthread_set_cfg(&esp_pthread_cfg));
    }

    inline void reset_pthread_config() noexcept
    {
        auto esp_pthread_cfg = esp_pthread_get_default_config();
        ESP_ERROR_CHECK(esp_pthread_set_cfg(&esp_pthread_cfg));
    }
} // namespace

AfeReader::AfeReader() noexcept
{
    using namespace elsen::arduino;
    using namespace elsen::signal;

    auto *address       = heap_caps_malloc(sizeof(DataBuffer), MALLOC_CAP_SPIRAM);
    current_samples_p1_ = new (address) DataBuffer{};

    address             = heap_caps_malloc(sizeof(DataBuffer), MALLOC_CAP_SPIRAM);
    voltage_samples_p1_ = new (address) DataBuffer{};

    address             = heap_caps_malloc(sizeof(DataBuffer), MALLOC_CAP_SPIRAM);
    current_samples_p2_ = new (address) DataBuffer{};

    address             = heap_caps_malloc(sizeof(DataBuffer), MALLOC_CAP_SPIRAM);
    voltage_samples_p2_ = new (address) DataBuffer{};

    address             = heap_caps_malloc(sizeof(DataBuffer), MALLOC_CAP_SPIRAM);
    current_samples_p3_ = new (address) DataBuffer{};

    address             = heap_caps_malloc(sizeof(DataBuffer), MALLOC_CAP_SPIRAM);
    voltage_samples_p3_ = new (address) DataBuffer{};

    address            = heap_caps_malloc(sizeof(DataBuffer), MALLOC_CAP_SPIRAM);
    current_samples_n_ = new (address) DataBuffer{};

    pinMode(CS_PIN, OUTPUT);
    digitalWrite(CS_PIN, LOW);

    ELSEN_LOG_INFO("Initializing AFE...");

    current_samples_n_->buffer_full.connect<&AfeReader::update_readings>(*this,
        ConnectionType::Queued);

    const auto spi_device_id =
        spi_.register_device({ SPI_SPEED, SpiMasterBus::DataMode::SPI_MODE0 });
    spi_device_ = &spi_.device(spi_device_id);
}

void AfeReader::start_reading() noexcept
{
    ELSEN_LOG_INFO("Preparing to read data from AFE...");

    set_up_pthread_config();

    auto thread_id = pthread_t{};
    auto result    = pthread_create(&thread_id, nullptr, &AfeReader::read_instance_values, this);
    PTHREAD_CHECK(result, "Failed to create instant value reader thread");

    result = pthread_detach(thread_id);
    PTHREAD_CHECK(result, "Failed to detach instant value reader thread");

    init_timer(&AfeReader::timer_callback, this, read_timer_);
    esp_timer_start_periodic(read_timer_, 244);

    ELSEN_LOG_INFO("Timer and task started, readings are ongoing...");

    reset_pthread_config();
}

void AfeReader::update_readings() noexcept
{
    using Span = gsl::span<float, DataBuffer::SIZE>;

    const auto start = std::chrono::system_clock::now();

    const auto samples_per_cycle_vp1 = helpers::samples_per_cycle(
        gsl::span<float>{ voltage_samples_p1_->inactive_buffer().data(), DataBuffer::SIZE });
    const auto samples_per_cycle_vp2 = helpers::samples_per_cycle(
        gsl::span<float>{ voltage_samples_p2_->inactive_buffer().data(), DataBuffer::SIZE });
    const auto samples_per_cycle_vp3 = helpers::samples_per_cycle(
        gsl::span<float>{ voltage_samples_p3_->inactive_buffer().data(), DataBuffer::SIZE });

    const auto samples_per_cycle_cp1 = helpers::samples_per_cycle(
        gsl::span<float>{ current_samples_p1_->inactive_buffer().data(), DataBuffer::SIZE });
    const auto samples_per_cycle_cp2 = helpers::samples_per_cycle(
        gsl::span<float>{ current_samples_p2_->inactive_buffer().data(), DataBuffer::SIZE });
    const auto samples_per_cycle_cp3 = helpers::samples_per_cycle(
        gsl::span<float>{ current_samples_p3_->inactive_buffer().data(), DataBuffer::SIZE });

    auto minfft_context =
        std::unique_ptr<minfft_aux, decltype(&minfft_free_aux)>{ minfft_mkaux_dft_1d(
                                                                     DataBuffer::SIZE),
            &minfft_free_aux };
    if (minfft_context == nullptr)
    {
        fprintf(stderr, "PowerMonitor: Failed to allocate FFT structure\n");
        return;
    }

    /** VOLTAGE **/
    {
        auto *sample_buffer_p1 = voltage_samples_p1_->inactive_buffer().data();
        auto *sample_buffer_p2 = voltage_samples_p2_->inactive_buffer().data();
        auto *sample_buffer_p3 = voltage_samples_p3_->inactive_buffer().data();

        auto input = std::vector<minfft_cmpl>(DataBuffer::SIZE);
        {
            for (std::size_t i = 0; i < DataBuffer::SIZE; ++i)
            {
                input[i][0] = sample_buffer_p1[i];
                input[i][1] = .0f;
            }

            auto *output = input.data();
            minfft_dft(input.data(), output, minfft_context.get());

            readings_.set_voltage_hd_phase_1(output, DataBuffer::SIZE);
            readings_.set_rms_voltage_phase_1(rms(Span{ sample_buffer_p1, DataBuffer::SIZE }));
        }

        {
            for (std::size_t i = 0; i < DataBuffer::SIZE; ++i)
            {
                input[i][0] = sample_buffer_p2[i];
                input[i][1] = .0f;
            }

            auto *output = input.data();
            minfft_dft(input.data(), output, minfft_context.get());

            readings_.set_voltage_hd_phase_2(output, DataBuffer::SIZE);
            readings_.set_rms_voltage_phase_2(rms(Span{ sample_buffer_p2, DataBuffer::SIZE }));
        }

        {
            for (std::size_t i = 0; i < DataBuffer::SIZE; ++i)
            {
                input[i][0] = sample_buffer_p3[i];
                input[i][1] = .0f;
            }

            auto *output = input.data();
            minfft_dft(input.data(), output, minfft_context.get());

            readings_.set_voltage_hd_phase_3(output, DataBuffer::SIZE);
            readings_.set_rms_voltage_phase_3(rms(Span{ sample_buffer_p3, DataBuffer::SIZE }));
        }

        {
            auto total = 0.F;
            for (std::size_t i = 0; i < DataBuffer::SIZE; ++i)
            {
                const auto v = sample_buffer_p1[i] - sample_buffer_p2[i];
                total += v * v;
            }
            readings_.set_rms_voltage_phase_1_to_2(std::sqrt(total / DataBuffer::SIZE));
        }

        {
            auto total = 0.F;
            for (std::size_t i = 0; i < DataBuffer::SIZE; ++i)
            {
                const auto v = sample_buffer_p2[i] - sample_buffer_p3[i];
                total += v * v;
            }
            readings_.set_rms_voltage_phase_2_to_3(std::sqrt(total / DataBuffer::SIZE));
        }

        {
            auto total = 0.F;
            for (std::size_t i = 0; i < DataBuffer::SIZE; ++i)
            {
                const auto v = sample_buffer_p3[i] - sample_buffer_p1[i];
                total += v * v;
            }
            readings_.set_rms_voltage_phase_3_to_1(std::sqrt(total / DataBuffer::SIZE));
        }

        // Unused for now
        readings_.set_phase_rotation_ok(true);
    }

    /** CURRENT **/
    {
        auto *sample_buffer_p1 = current_samples_p1_->inactive_buffer().data();
        auto *sample_buffer_p2 = current_samples_p2_->inactive_buffer().data();
        auto *sample_buffer_p3 = current_samples_p3_->inactive_buffer().data();
        auto *sample_buffer_n  = current_samples_n_->inactive_buffer().data();

        auto input = std::vector<minfft_cmpl>(DataBuffer::SIZE);
        {
            for (std::size_t i = 0; i < DataBuffer::SIZE; ++i)
            {
                input[i][0] = sample_buffer_p1[i];
                input[i][1] = .0f;
            }

            auto *output = input.data();
            minfft_dft(input.data(), output, minfft_context.get());

            readings_.set_current_hd_phase_1(output, DataBuffer::SIZE);
            readings_.set_rms_current_phase_1(rms(Span{ sample_buffer_p1, DataBuffer::SIZE }));
        }

        {
            for (std::size_t i = 0; i < DataBuffer::SIZE; ++i)
            {
                input[i][0] = sample_buffer_p2[i];
                input[i][1] = .0f;
            }

            auto *output = input.data();
            minfft_dft(input.data(), output, minfft_context.get());

            readings_.set_current_hd_phase_2(output, DataBuffer::SIZE);
            readings_.set_rms_current_phase_2(rms(Span{ sample_buffer_p2, DataBuffer::SIZE }));
        }

        {
            for (std::size_t i = 0; i < DataBuffer::SIZE; ++i)
            {
                input[i][0] = sample_buffer_p3[i];
                input[i][1] = .0f;
            }

            auto *output = input.data();
            minfft_dft(input.data(), output, minfft_context.get());

            readings_.set_current_hd_phase_3(output, DataBuffer::SIZE);
            readings_.set_rms_current_phase_3(rms(Span{ sample_buffer_p3, DataBuffer::SIZE }));
        }

        readings_.set_rms_current_neutral(rms(Span{ sample_buffer_n, DataBuffer::SIZE }));
    }

    /** POWER **/
    auto *sample_buffer_current_p1 = current_samples_p1_->inactive_buffer().data();
    auto *sample_buffer_voltage_p1 = voltage_samples_p1_->inactive_buffer().data();

    auto *sample_buffer_current_p2 = current_samples_p2_->inactive_buffer().data();
    auto *sample_buffer_voltage_p2 = voltage_samples_p2_->inactive_buffer().data();

    auto *sample_buffer_current_p3 = current_samples_p3_->inactive_buffer().data();
    auto *sample_buffer_voltage_p3 = voltage_samples_p3_->inactive_buffer().data();

    const auto app1 = active_power(Span{ sample_buffer_current_p1, DataBuffer::SIZE },
        Span{ sample_buffer_voltage_p1, DataBuffer::SIZE });
    const auto app2 = active_power(Span{ sample_buffer_current_p2, DataBuffer::SIZE },
        Span{ sample_buffer_voltage_p2, DataBuffer::SIZE });
    const auto app3 = active_power(Span{ sample_buffer_current_p3, DataBuffer::SIZE },
        Span{ sample_buffer_voltage_p3, DataBuffer::SIZE });
    const auto cap  = app1 + app2 + app3;

    readings_.set_active_power_phase_1(app1);
    readings_.set_active_power_phase_2(app2);
    readings_.set_active_power_phase_3(app3);
    readings_.set_cumulated_active_power(cap);

    const auto rpp1 = reactive_power(samples_per_cycle_cp1,
        Span{ sample_buffer_current_p1, DataBuffer::SIZE },
        Span{ sample_buffer_voltage_p1, DataBuffer::SIZE });
    const auto rpp2 = reactive_power(samples_per_cycle_cp2,
        Span{ sample_buffer_current_p2, DataBuffer::SIZE },
        Span{ sample_buffer_voltage_p2, DataBuffer::SIZE });
    const auto rpp3 = reactive_power(samples_per_cycle_cp3,
        Span{ sample_buffer_current_p3, DataBuffer::SIZE },
        Span{ sample_buffer_voltage_p3, DataBuffer::SIZE });
    const auto crp  = rpp1 + rpp2 + rpp3;

    readings_.set_reactive_power_phase_1(rpp1);
    readings_.set_reactive_power_phase_2(rpp2);
    readings_.set_reactive_power_phase_3(rpp3);
    readings_.set_cumulated_reactive_power(crp);

    const auto appp1 = apparent_power(app1, rpp1);
    const auto appp2 = apparent_power(app2, rpp2);
    const auto appp3 = apparent_power(app3, rpp3);
    const auto capp  = app1 + app2 + app3;

    readings_.set_apparent_power_phase_1(appp1);
    readings_.set_apparent_power_phase_2(appp2);
    readings_.set_apparent_power_phase_3(appp3);
    readings_.set_cumulated_apparent_power(capp);

    const auto pfp1 = power_factor(app1, appp1, Load::Capacitive);
    readings_.set_power_factor_phase_1(pfp1);

    const auto pfp2 = power_factor(app2, appp2, Load::Capacitive);
    readings_.set_power_factor_phase_1(pfp2);

    const auto pfp3 = power_factor(app3, appp3, Load::Capacitive);
    readings_.set_power_factor_phase_1(pfp3);

    /** POWER QUALITY **/
    {
        readings_.set_phi_phase_1(static_cast<float>(offset_degrees(samples_per_cycle_vp1,
            Span{ sample_buffer_voltage_p1, DataBuffer::SIZE },
            Span{ sample_buffer_current_p1, DataBuffer::SIZE })));
        readings_.set_phi_phase_2(static_cast<float>(offset_degrees(samples_per_cycle_vp2,
            Span{ sample_buffer_voltage_p2, DataBuffer::SIZE },
            Span{ sample_buffer_current_p2, DataBuffer::SIZE })));
        readings_.set_phi_phase_3(static_cast<float>(offset_degrees(samples_per_cycle_vp3,
            Span{ sample_buffer_voltage_p3, DataBuffer::SIZE },
            Span{ sample_buffer_current_p3, DataBuffer::SIZE })));

        readings_.set_phi_phase_1_to_2(static_cast<float>(offset_degrees(samples_per_cycle_cp1,
            Span{ sample_buffer_current_p1, DataBuffer::SIZE },
            Span{ sample_buffer_current_p2, DataBuffer::SIZE })));
        readings_.set_phi_phase_2_to_3(static_cast<float>(offset_degrees(samples_per_cycle_cp3,
            Span{ sample_buffer_current_p2, DataBuffer::SIZE },
            Span{ sample_buffer_current_p3, DataBuffer::SIZE })));
        readings_.set_phi_phase_3_to_1(static_cast<float>(offset_degrees(samples_per_cycle_cp3,
            Span{ sample_buffer_current_p3, DataBuffer::SIZE },
            Span{ sample_buffer_current_p1, DataBuffer::SIZE })));

        const auto fp1 = frequency<float>(DataBuffer::SIZE, samples_per_cycle_cp1);
        const auto fp2 = frequency<float>(DataBuffer::SIZE, samples_per_cycle_cp2);
        const auto fp3 = frequency<float>(DataBuffer::SIZE, samples_per_cycle_cp3);

        readings_.set_frequency_phase_1(fp1);
        readings_.set_frequency_phase_2(fp2);
        readings_.set_frequency_phase_3(fp3);
        readings_.set_frequency_average((fp1 + fp2 + fp3) / 3.F);
    }

    /** ENERGY **/
    {
        const auto aep1 = active_energy<float, DataBuffer::SIZE>(app1);
        const auto aep2 = active_energy<float, DataBuffer::SIZE>(app2);
        const auto aep3 = active_energy<float, DataBuffer::SIZE>(app3);

        cumulated_active_energy_ += aep1 + aep2 + aep3;

        readings_.set_active_energy_phase_1(aep1);
        readings_.set_active_energy_phase_2(aep2);
        readings_.set_active_energy_phase_3(aep3);
        readings_.set_cumulated_active_energy(cumulated_active_energy_);

        const auto rep1 = reactive_energy<float, DataBuffer::SIZE>(rpp1);
        const auto rep2 = reactive_energy<float, DataBuffer::SIZE>(rpp2);
        const auto rep3 = reactive_energy<float, DataBuffer::SIZE>(rpp3);

        cumulated_reactive_energy_ += rep1 + rep2 + rep3;

        readings_.set_reactive_energy_phase_1(rep1);
        readings_.set_reactive_energy_phase_2(rep2);
        readings_.set_reactive_energy_phase_3(rep3);
        readings_.set_cumulated_reactive_energy(cumulated_reactive_energy_);

        const auto aepp1 = apparent_energy<float, DataBuffer::SIZE>(appp1);
        const auto aepp2 = apparent_energy<float, DataBuffer::SIZE>(appp2);
        const auto aepp3 = apparent_energy<float, DataBuffer::SIZE>(appp3);

        cumulated_apparent_energy_ += aepp1 + aepp2 + aepp3;

        readings_.set_apparent_energy_phase_1(aepp1);
        readings_.set_apparent_energy_phase_2(aepp2);
        readings_.set_apparent_energy_phase_3(aepp3);
        readings_.set_cumulated_apparent_energy(cumulated_apparent_energy_);
    }

    auto readings_serialized = readings_.to_binary();
    readings_ready.emit(std::move(readings_serialized));

    std::printf("%s\n",
        fmt::format("All readings done and sent off to MQTT in {} milliseconds",
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now() - start)
                .count())
            .c_str());
}

void AfeReader::timer_callback(void *instance) noexcept
{
    auto *self = static_cast<AfeReader *>(instance);
    HEDLEY_DIAGNOSTIC_PUSH
    ELSEN_DIAGNOSTIC_IGNORE_USELESS_CAST

    xTaskNotifyGive(static_cast<TaskHandle_t>(self->read_instant_values_task_));

    HEDLEY_DIAGNOSTIC_POP
}

[[noreturn]] void *AfeReader::read_instance_values(void *instance) noexcept
{
    auto *self             = static_cast<AfeReader *>(instance);
    auto  read_buffer      = std::array<std::uint8_t, 4 * 2 * 16>{};
    auto  read_buffer_span = gsl::span<std::uint8_t>{ read_buffer };

    self->read_instant_values_task_ = xTaskGetCurrentTaskHandle();

    for (;;)
    {
        const auto notification_value = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (notification_value == 1)
        {
            using namespace elsen::utilities::data;

            std::memset(read_buffer.data(), 0, read_buffer.size());
            digitalWrite(CS_PIN, elsen::arduino::PinState::HIGH);
            {
                self->spi_device_->transfer_to(read_buffer_span, read_buffer_span);
            }
            digitalWrite(CS_PIN, elsen::arduino::PinState::LOW);

            const auto voltage_sample_p1 =
                static_cast<float>(deserialize_msb<std::uint16_t>(read_buffer_span));
            const auto current_sample_p1 =
                static_cast<float>(deserialize_msb<std::uint16_t>(read_buffer_span.subspan(2)));
            const auto voltage_sample_p2 =
                static_cast<float>(deserialize_msb<std::uint16_t>(read_buffer_span.subspan(4)));
            const auto current_sample_p2 =
                static_cast<float>(deserialize_msb<std::uint16_t>(read_buffer_span.subspan(6)));
            const auto voltage_sample_p3 =
                static_cast<float>(deserialize_msb<std::uint16_t>(read_buffer_span.subspan(8)));
            const auto current_sample_p3 =
                static_cast<float>(deserialize_msb<std::uint16_t>(read_buffer_span.subspan(10)));
            const auto current_sample_n =
                static_cast<float>(deserialize_msb<std::uint16_t>(read_buffer_span.subspan(14)));

            if (const auto push_success = self->current_samples_p1_->push_one(&current_sample_p1);
                !push_success)
            {
                ELSEN_LOG_ERROR("Failed to push current (P1) data to sample buffer");
                continue;
            }

            if (const auto push_success = self->voltage_samples_p1_->push_one(&voltage_sample_p1);
                !push_success)
            {
                ELSEN_LOG_ERROR("Failed to push voltage (P1) data to sample buffer");
                continue;
            }

            if (const auto push_success = self->current_samples_p2_->push_one(&current_sample_p2);
                !push_success)
            {
                ELSEN_LOG_ERROR("Failed to push current (P2) data to sample buffer");
                continue;
            }

            if (const auto push_success = self->voltage_samples_p2_->push_one(&voltage_sample_p2);
                !push_success)
            {
                ELSEN_LOG_ERROR("Failed to push voltage (P2) data to sample buffer");
                continue;
            }

            if (const auto push_success = self->current_samples_p3_->push_one(&current_sample_p3);
                !push_success)
            {
                ELSEN_LOG_ERROR("Failed to push current (P3) data to sample buffer");
                continue;
            }

            if (const auto push_success = self->voltage_samples_p3_->push_one(&voltage_sample_p3);
                !push_success)
            {
                ELSEN_LOG_ERROR("Failed to push voltage (P3) data to sample buffer");
                continue;
            }

            // Make sure to keep this last
            if (const auto push_success = self->current_samples_n_->push_one(&current_sample_n);
                !push_success)
            {
                ELSEN_LOG_ERROR("Failed to push current (N) data to sample buffer");
                continue;
            }
        }
    }
}

#endif
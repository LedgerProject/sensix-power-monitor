#pragma once

#include "common.hh"
#include "readings.hh"
#include "sample_buffer.hh"

#include <elsen/devices/spi.hh>
#include <elsen/signal.hh>

#ifdef __xtensa__
#include <FreeRTOS.h>
#include <esp_timer.h>
#include <freertos/semphr.h>
#else
using esp_timer_handle_t = void *;
#endif

#include <chrono>
#include <memory>

struct AfeReader
{
    static constexpr auto SPI_BUS_ID = std::uint8_t{ 2 }; // SPI3

    using SpiMasterBus = elsen::devices::Spi;

public:
    AfeReader() noexcept;
    void start_reading() noexcept;

public:
    inline float cumulated_active_energy() const noexcept
    {
        return cumulated_active_energy_;
    }

signals:
    elsen::Signal<std::vector<std::uint8_t> &&> readings_ready{};

private:
    void update_readings() noexcept;

private:
    static void               timer_callback(void *instance) noexcept;
    [[noreturn]] static void *read_instance_values(void *instance) noexcept;

private:
    SpiMasterBus          spi_{ SPI_BUS_ID };
    SpiMasterBus::Device *spi_device_{ nullptr };

    esp_timer_handle_t read_timer_{};

    using DataBuffer = SampleBuffer<float, SAMPLE_BUFFER_SIZE>;
    DataBuffer *current_samples_p1_{};
    DataBuffer *voltage_samples_p1_{};
    DataBuffer *current_samples_p2_{};
    DataBuffer *voltage_samples_p2_{};
    DataBuffer *current_samples_p3_{};
    DataBuffer *voltage_samples_p3_{};
    DataBuffer *current_samples_n_{};

    Readings readings_{};

    float cumulated_active_energy_{ 0.F };
    float cumulated_reactive_energy_{ 0.F };
    float cumulated_apparent_energy_{ 0.F };

    void *read_instant_values_task_{};
};

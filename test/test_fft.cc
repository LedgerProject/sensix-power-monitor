#if defined(POWER_MONITOR_PLATFORM_X86_64) || defined(POWER_MONITOR_PLATFORM_I386)

#include <fftw3.h>
#include <minfft.h>

#include <array>
#include <ctime>
#include <functional>
#include <random>

#include <cmocka.hh>

static constexpr std::size_t SAMPLE_COUNT{ 32 };

void fft_test_accuracy(void **)
{
    std::mt19937 engine{};
    engine.seed(static_cast<std::uint64_t>(std::time(nullptr)));

    auto distribution = std::uniform_real_distribution<float>(10, 30);
    auto rng = std::bind(distribution, engine);

    const auto calculate_wave = [&] {
        constexpr auto THETA{ 0.02f };
        constexpr auto TWO_PI{ 2.f * static_cast<float>(M_PI) };
        auto result = std::array<float, SAMPLE_COUNT>{};

        auto x = THETA;
        for (std::size_t i = 0; i < result.size(); i++)
        {
            if (i % 2 == 0)
            {
                result[i] = std::sin(x) * rng();
            }
            else
            {
                result[i] = std::cos(x) * rng();
            }
            const auto period = rng() * 10.f;
            x += TWO_PI / period;
        }

        return result;
    };

    auto wave = calculate_wave();

    auto fftw_input = std::array<fftwf_complex, SAMPLE_COUNT>{};
    auto fftw_result = std::array<fftwf_complex, SAMPLE_COUNT>{};
    {
        auto *plan_forward = fftwf_plan_dft_1d(fftw_input.size(),
            fftw_input.data(),
            fftw_result.data(),
            FFTW_FORWARD,
            FFTW_ESTIMATE);
        assert_true(plan_forward != nullptr);

        for (std::size_t i = 0; i < wave.size(); ++i)
        {
            fftw_input[i][0] = wave[i];
            fftw_input[i][1] = .0f;
        }

        fftwf_execute(plan_forward);
        fftwf_free(plan_forward);
    }

    auto &minfft_result = fftw_input;
    {

        auto minfft_a = minfft_mkaux_dft_1d(SAMPLE_COUNT);
        minfft_dft(fftw_input.data(), minfft_result.data(), minfft_a);

        minfft_free_aux(minfft_a);
    }

    for (std::size_t i = 0; i < minfft_result.size(); i += 1)
    {
        const auto lhs_re = static_cast<std::int32_t>(minfft_result[i][0] * 1000);
        const auto lhs_im = static_cast<std::int32_t>(minfft_result[i][1] * 1000);

        const auto rhs_re = static_cast<std::int32_t>(fftw_result[i][0] * 1000);
        const auto rhs_im = static_cast<std::int32_t>(fftw_result[i][1] * 1000);

        assert_true(lhs_re == rhs_re);
        assert_true(lhs_im == rhs_im);
    }
}

#endif
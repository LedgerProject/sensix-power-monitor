#include <gsl/gsl>

#include <array>
#include <cmath>
#include <cstring>
#include <type_traits>

namespace helpers
{
    template<typename Float>
    constexpr auto find_zero_cross(const gsl::span<Float> &samples) noexcept
    {
        static_assert(std::is_floating_point_v<Float>);

        auto previous_sample = samples[0];
        if (previous_sample == 0)
        {
            return std::size_t{ 0 };
        }

        for (std::size_t i = 1; i < samples.size(); ++i)
        {
            const auto current_sample = samples[i];
            if (current_sample == 0)
            {
                return i;
            }

            if ((previous_sample < 0 && current_sample > 0) ||
                (previous_sample > 0 && current_sample < 0))
            {
                return i;
            }

            previous_sample = current_sample;
        }

        return std::size_t{ 0 };
    }

    template<typename Float>
    constexpr auto samples_per_cycle(const gsl::span<Float> &samples) noexcept
    {
        const auto cycle_start = find_zero_cross(samples);
        auto       cycle_end   = find_zero_cross(samples.subspan(cycle_start + 1));
        cycle_end              = find_zero_cross(samples.subspan(cycle_end + 1));

        return cycle_end - cycle_start;
    }
} // namespace helpers

template<typename Float, std::size_t sample_count>
constexpr auto rms(const gsl::span<Float, sample_count> &samples,
    Float                                                awgn = 0, // Additive White Gaussian Noise
    Float                                                scaling_factor = 1) noexcept
{
    static_assert(std::is_floating_point_v<Float>);

    const auto sum_squared = std::accumulate(samples.begin(),
        samples.end(),
        static_cast<Float>(0.0),
        [](Float sum, const Float &value) {
            return sum + (value * value);
        });

    return scaling_factor * (std::sqrt((sum_squared / sample_count) - awgn));
}

template<typename Float, std::size_t sample_count>
constexpr auto active_power(const gsl::span<Float, sample_count> &current_samples,
    const gsl::span<Float, sample_count>                         &voltage_samples,
    Float                                                         scaling_factor = 1) noexcept
{
    static_assert(std::is_floating_point_v<Float>);

    auto result = Float{};
    for (std::size_t i = 0; i < sample_count; ++i)
    {
        result += current_samples[i] * voltage_samples[i];
    }

    return scaling_factor * (result / sample_count);
}

template<typename Float, std::size_t sample_count>
constexpr auto reactive_power(std::size_t samples_per_cycle,
    const gsl::span<Float, sample_count> &current_samples,
    const gsl::span<Float, sample_count> &voltage_samples,
    Float                                 scaling_factor = 1) noexcept
{
    static_assert(std::is_floating_point_v<Float>);

    const auto sample_offset = samples_per_cycle / 4; // Phase-shift by 90°

    auto result = Float{};
    for (std::size_t i = sample_offset; i < sample_count; ++i)
    {
        result += voltage_samples[i] * current_samples[i - sample_offset];
    }

    return scaling_factor * (result / sample_count);
}

template<typename Float>
constexpr auto apparent_power(Float active_power, Float reactive_power) noexcept
{
    static_assert(std::is_floating_point_v<Float>);

    return std::sqrt(active_power * active_power + reactive_power * reactive_power);
}

template<typename Float, std::size_t sample_count>
constexpr auto active_energy(Float active_power) noexcept
{
    static_assert(std::is_floating_point_v<Float>);

    return active_power * sample_count;
}

template<typename Float, std::size_t sample_count>
constexpr auto reactive_energy(Float reactive_power) noexcept
{
    static_assert(std::is_floating_point_v<Float>);

    return reactive_power * sample_count;
}

template<typename Float, std::size_t sample_count>
constexpr auto apparent_energy(Float apparent_power) noexcept
{
    static_assert(std::is_floating_point_v<Float>);

    return apparent_power * sample_count;
}

template<typename Float>
constexpr auto frequency(std::size_t samples_per_sec, std::size_t samples_per_cycle) noexcept
{
    static_assert(std::is_floating_point_v<Float>);

    return static_cast<Float>(static_cast<double>(samples_per_sec) / samples_per_cycle);
}

enum class Load
{
    Capacitive,
    Inductive
};

template<typename Float>
constexpr auto power_factor(Float active_power, Float apparent_power, Load load) noexcept
{
    static_assert(std::is_floating_point_v<Float>);

    const auto result = active_power / apparent_power;

    if (load == Load::Inductive)
    {
        return (-1 * result);
    }
    return result;
}

template<typename Float, std::size_t sample_count>
constexpr auto offset_index(const gsl::span<Float, sample_count> &sample_set_0,
    const gsl::span<Float, sample_count>                         &sample_set_1) noexcept
{
    const auto zc_0 = helpers::find_zero_cross(sample_set_0.subspan(0));
    const auto zc_1 = helpers::find_zero_cross(sample_set_1.subspan(0));

    return std::abs(static_cast<std::int64_t>(zc_0) - static_cast<std::int64_t>(zc_1));
}

template<typename Float, std::size_t sample_count>
constexpr auto offset_degrees(std::size_t samples_per_cycle,
    const gsl::span<Float, sample_count> &sample_set_0,
    const gsl::span<Float, sample_count> &sample_set_1) noexcept
{
    const auto diff = offset_index(sample_set_0, sample_set_1);

    return (diff * 360) / samples_per_cycle;
}

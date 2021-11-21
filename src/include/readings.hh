#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

#define DECLTYPE_FROM(type_name, underlying_type)                  \
    struct type_name                                               \
    {                                                              \
        using UnderlyingType           = underlying_type;          \
        constexpr type_name() noexcept = default;                  \
        constexpr explicit type_name(underlying_type v) noexcept   \
          : value_{ v }                                            \
        {}                                                         \
        constexpr type_name &operator=(underlying_type v) noexcept \
        {                                                          \
            value_ = v;                                            \
            return *this;                                          \
        }                                                          \
        constexpr operator underlying_type() const noexcept        \
        {                                                          \
            return value_;                                         \
        }                                                          \
                                                                   \
    private:                                                       \
        underlying_type value_{};                                  \
    }

template<typename T, std::size_t precision, typename Decimal>
constexpr auto to_internal_representation(Decimal value) noexcept
{
    for (std::size_t i = 0; i < precision; ++i)
    {
        value *= 10;
    }

    auto       v      = std::floor(value);
    const auto result = static_cast<typename T::UnderlyingType>(v < 0 ? std::ceil(value) : v);

    // Account for conversion error/overflow when very close to limits (+ => -)
    if (result < 0 && value > 0)
    {
        return std::numeric_limits<typename T::UnderlyingType>::max();
    }

    // Account for conversion error/overflow when very close to limits (- => +)
    if (result > 0 && value < 0)
    {
        return std::numeric_limits<typename T::UnderlyingType>::min();
    }

    return result;
}

template<typename T> constexpr void set_value(T &v, float value) noexcept
{
    v.value = to_internal_representation<typename T::Type, T::PRECISION>(value);
}

struct Readings
{
    DECLTYPE_FROM(Volt, std::int32_t);
    DECLTYPE_FROM(Amp, std::int32_t);
    DECLTYPE_FROM(Watt, std::int32_t);
    DECLTYPE_FROM(VoltAmp, std::int32_t);
    DECLTYPE_FROM(VoltAmpReactive, std::int32_t);
    DECLTYPE_FROM(WattPerVoltAmp, std::int8_t);
    DECLTYPE_FROM(WattHour, std::uint64_t);
    DECLTYPE_FROM(VoltAmpHour, std::int64_t);
    DECLTYPE_FROM(VoltAmpReactiveHour, std::int64_t);
    DECLTYPE_FROM(Hertz, std::uint16_t);
    DECLTYPE_FROM(Degrees, std::int16_t);
    DECLTYPE_FROM(Percentage, std::uint16_t);
    DECLTYPE_FROM(Boolean, std::int8_t);

    using Complex = float[2];

    template<typename T, std::uint8_t precision> struct Unit
    {
        static constexpr auto PRECISION = precision;
        using Type                      = T;

        constexpr typename T::UnderlyingType base_value() const noexcept
        {
            return static_cast<typename T::UnderlyingType>(value);
        }

        inline void serialize_to(std::vector<std::uint8_t> &target) const
        {
            const auto v = base_value();
            for (auto i = static_cast<std::int8_t>(sizeof(T)) - 1; i >= 0; --i)
            {
                target.push_back(static_cast<std::uint8_t>((v >> (i * 8)) & 0xFF));
            }
        }

        inline void deserialize_from(const std::uint8_t *&input)
        {
            auto v = typename T::UnderlyingType{};
            for (auto i = static_cast<std::int8_t>(sizeof(T)) - 1; i >= 0; --i)
            {
                v = static_cast<typename T::UnderlyingType>(v | *input);
                v = static_cast<typename T::UnderlyingType>(v << (i * 8));
                ++input;
            }

            value = v;
        }

        T value;
    };

public:
    [[nodiscard]] constexpr auto rms_voltage_phase_1() const noexcept;
    constexpr void               set_rms_voltage_phase_1(float value_milli_volt) noexcept;

    [[nodiscard]] constexpr auto rms_voltage_phase_2() const noexcept;
    constexpr void               set_rms_voltage_phase_2(float value_milli_volt) noexcept;

    [[nodiscard]] constexpr auto rms_voltage_phase_3() const noexcept;
    constexpr void               set_rms_voltage_phase_3(float value_milli_volt) noexcept;

    [[nodiscard]] constexpr auto rms_voltage_phase_1_to_2() const noexcept;
    constexpr void               set_rms_voltage_phase_1_to_2(float value_milli_volt) noexcept;

    [[nodiscard]] constexpr auto rms_voltage_phase_2_to_3() const noexcept;
    constexpr void               set_rms_voltage_phase_2_to_3(float value_milli_volt) noexcept;

    [[nodiscard]] constexpr auto rms_voltage_phase_3_to_1() const noexcept;
    constexpr void               set_rms_voltage_phase_3_to_1(float value_milli_volt) noexcept;

    [[nodiscard]] constexpr auto phase_rotation_ok() const noexcept;
    constexpr void               set_phase_rotation_ok(bool is_ok) noexcept;

    [[nodiscard]] constexpr auto rms_current_phase_1() const noexcept;
    constexpr void               set_rms_current_phase_1(float value_milli_amp) noexcept;

    [[nodiscard]] constexpr auto rms_current_phase_2() const noexcept;
    constexpr void               set_rms_current_phase_2(float value_milli_amp) noexcept;

    [[nodiscard]] constexpr auto rms_current_phase_3() const noexcept;
    constexpr void               set_rms_current_phase_3(float value_milli_amp) noexcept;

    [[nodiscard]] constexpr auto rms_current_neutral() const noexcept;
    constexpr void               set_rms_current_neutral(float value_milli_amp) noexcept;

    [[nodiscard]] constexpr auto rms_current_leak() const noexcept;
    constexpr void               set_rms_current_leak(float value_milli_amp) noexcept;

    [[nodiscard]] constexpr auto active_power_phase_1() const noexcept;
    constexpr void               set_active_power_phase_1(float value_milli_watt) noexcept;

    [[nodiscard]] constexpr auto active_power_phase_2() const noexcept;
    constexpr void               set_active_power_phase_2(float value_milli_watt) noexcept;

    [[nodiscard]] constexpr auto active_power_phase_3() const noexcept;
    constexpr void               set_active_power_phase_3(float value_milli_watt) noexcept;

    [[nodiscard]] constexpr auto cumulated_active_power() const noexcept;
    constexpr void               set_cumulated_active_power(float value_milli_watt) noexcept;

    [[nodiscard]] constexpr auto apparent_power_phase_1() const noexcept;
    constexpr void               set_apparent_power_phase_1(float value_milli_volt_amp) noexcept;

    [[nodiscard]] constexpr auto apparent_power_phase_2() const noexcept;
    constexpr void               set_apparent_power_phase_2(float value_milli_volt_amp) noexcept;

    [[nodiscard]] constexpr auto apparent_power_phase_3() const noexcept;
    constexpr void               set_apparent_power_phase_3(float value_milli_volt_amp) noexcept;

    [[nodiscard]] constexpr auto cumulated_apparent_power() const noexcept;
    constexpr void               set_cumulated_apparent_power(float value_milli_volt_amp) noexcept;

    [[nodiscard]] constexpr auto reactive_power_phase_1() const noexcept;
    constexpr void set_reactive_power_phase_1(float value_milli_volt_amp_reactive) noexcept;

    [[nodiscard]] constexpr auto reactive_power_phase_2() const noexcept;
    constexpr void set_reactive_power_phase_2(float value_milli_volt_amp_reactive) noexcept;

    [[nodiscard]] constexpr auto reactive_power_phase_3() const noexcept;
    constexpr void set_reactive_power_phase_3(float value_milli_volt_amp_reactive) noexcept;

    [[nodiscard]] constexpr auto cumulated_reactive_power() const noexcept;
    constexpr void set_cumulated_reactive_power(float value_milli_volt_amp_reactive) noexcept;

    [[nodiscard]] constexpr auto power_factor_phase_1() const noexcept;
    constexpr void               set_power_factor_phase_1(float value) noexcept;

    [[nodiscard]] constexpr auto power_factor_phase_2() const noexcept;
    constexpr void               set_power_factor_phase_2(float value) noexcept;

    [[nodiscard]] constexpr auto power_factor_phase_3() const noexcept;
    constexpr void               set_power_factor_phase_3(float value) noexcept;

    [[nodiscard]] constexpr auto active_energy_phase_1() const noexcept;
    constexpr void               set_active_energy_phase_1(float value_milli_watt_hour) noexcept;

    [[nodiscard]] constexpr auto active_energy_phase_2() const noexcept;
    constexpr void               set_active_energy_phase_2(float value_milli_watt_hour) noexcept;

    [[nodiscard]] constexpr auto active_energy_phase_3() const noexcept;
    constexpr void               set_active_energy_phase_3(float value_milli_watt_hour) noexcept;

    [[nodiscard]] constexpr auto cumulated_active_energy() const noexcept;
    constexpr void               set_cumulated_active_energy(float value_milli_watt_hour) noexcept;

    [[nodiscard]] constexpr auto apparent_energy_phase_1() const noexcept;
    constexpr void set_apparent_energy_phase_1(float value_milli_milli_volt_amp_hour) noexcept;

    [[nodiscard]] constexpr auto apparent_energy_phase_2() const noexcept;
    constexpr void set_apparent_energy_phase_2(float value_milli_milli_volt_amp_hour) noexcept;

    [[nodiscard]] constexpr auto apparent_energy_phase_3() const noexcept;
    constexpr void set_apparent_energy_phase_3(float value_milli_milli_volt_amp_hour) noexcept;

    [[nodiscard]] constexpr auto cumulated_apparent_energy() const noexcept;
    constexpr void set_cumulated_apparent_energy(float value_milli_milli_volt_amp_hour) noexcept;

    [[nodiscard]] constexpr auto reactive_energy_phase_1() const noexcept;
    constexpr void set_reactive_energy_phase_1(float value_milli_volt_amp_reactive_hour) noexcept;

    [[nodiscard]] constexpr auto reactive_energy_phase_2() const noexcept;
    constexpr void set_reactive_energy_phase_2(float value_milli_volt_amp_reactive_hour) noexcept;

    [[nodiscard]] constexpr auto reactive_energy_phase_3() const noexcept;
    constexpr void set_reactive_energy_phase_3(float value_milli_volt_amp_reactive_hour) noexcept;

    [[nodiscard]] constexpr auto cumulated_reactive_energy() const noexcept;
    constexpr void set_cumulated_reactive_energy(float value_milli_volt_amp_reactive_hour) noexcept;

    [[nodiscard]] constexpr auto frequency_phase_1() const noexcept;
    constexpr void               set_frequency_phase_1(float value_hz) noexcept;

    [[nodiscard]] constexpr auto frequency_phase_2() const noexcept;
    constexpr void               set_frequency_phase_2(float value_hz) noexcept;

    [[nodiscard]] constexpr auto frequency_phase_3() const noexcept;
    constexpr void               set_frequency_phase_3(float value_hz) noexcept;

    [[nodiscard]] constexpr auto frequency_average() const noexcept;
    constexpr void               set_frequency_average(float value_hz) noexcept;

    [[nodiscard]] constexpr auto phi_phase_1_to_2() const noexcept;
    constexpr void               set_phi_phase_1_to_2(float value_degrees) noexcept;

    [[nodiscard]] constexpr auto phi_phase_2_to_3() const noexcept;
    constexpr void               set_phi_phase_2_to_3(float value_degrees) noexcept;

    [[nodiscard]] constexpr auto phi_phase_3_to_1() const noexcept;
    constexpr void               set_phi_phase_3_to_1(float value_degrees) noexcept;

    [[nodiscard]] constexpr auto phi_phase_1() const noexcept;
    constexpr void               set_phi_phase_1(float value_degrees) noexcept;

    [[nodiscard]] constexpr auto phi_phase_2() const noexcept;
    constexpr void               set_phi_phase_2(float value_degrees) noexcept;

    [[nodiscard]] constexpr auto phi_phase_3() const noexcept;
    constexpr void               set_phi_phase_3(float value_degrees) noexcept;

    [[nodiscard]] constexpr auto voltage_thd_phase_1() const noexcept;
    constexpr void               set_voltage_thd_phase_1(float value) noexcept;

    [[nodiscard]] constexpr auto voltage_thd_phase_2() const noexcept;
    constexpr void               set_voltage_thd_phase_2(float value) noexcept;

    [[nodiscard]] constexpr auto voltage_thd_phase_3() const noexcept;
    constexpr void               set_voltage_thd_phase_3(float value) noexcept;

    [[nodiscard]] constexpr auto current_thd_phase_1() const noexcept;
    constexpr void               set_current_thd_phase_1(float value) noexcept;

    [[nodiscard]] constexpr auto current_thd_phase_2() const noexcept;
    constexpr void               set_current_thd_phase_2(float value) noexcept;

    [[nodiscard]] constexpr auto current_thd_phase_3() const noexcept;
    constexpr void               set_current_thd_phase_3(float value) noexcept;

    constexpr void set_voltage_hd_phase_1(const Complex *values, std::size_t count) noexcept;
    constexpr void set_voltage_hd_phase_2(const Complex *values, std::size_t count) noexcept;
    constexpr void set_voltage_hd_phase_3(const Complex *values, std::size_t count) noexcept;

    constexpr void set_current_hd_phase_1(const Complex *values, std::size_t count) noexcept;
    constexpr void set_current_hd_phase_2(const Complex *values, std::size_t count) noexcept;
    constexpr void set_current_hd_phase_3(const Complex *values, std::size_t count) noexcept;

    [[nodiscard]] std::vector<std::uint8_t> to_binary();
    void                                    to_binary(std::vector<std::uint8_t> &result);
    [[nodiscard]] static Readings           from_binary(const std::uint8_t *payload) noexcept;

private:
    static constexpr std::pair<std::size_t, float> find_fundamental_freq(const Complex *values,
        std::size_t count) noexcept;

    static constexpr float find_next_frequency(std::size_t index,
        std::size_t                                        min_offset,
        std::size_t                                        max_offset,
        const Complex                                     *values,
        std::size_t                                        count) noexcept;

    template<typename HDArray>
    constexpr void set_harmonic_distortion(HDArray &hd_values,
        void (Readings::*set_thd)(float),
        const Complex *values,
        std::size_t    count,
        const char    *prefix = "") noexcept
    {
        static_cast<void>(prefix);

        auto [fundamental_index, fundamental] = find_fundamental_freq(values, count);

        auto thd = float{};
        for (std::size_t i = fundamental_index, j = 0; i < count && j < hd_values.size();
             i += fundamental_index, ++j)
        {
            const auto v = find_next_frequency(i, 5, 5, values, count);
            set_value(hd_values[j], (v / fundamental));
            if (j != 0)
            {
                thd += v * v;
            }
        }

        if (fundamental != 0)
        {
            thd = std::sqrt(thd) / fundamental;
        }
        else
        {
            thd = .0F;
        }
        (this->*set_thd)(thd);

        //        std::printf("%sTHD: %f\n", prefix, static_cast<double>(thd));
        //        std::printf("%sFundamental: %f\n", prefix, static_cast<double>(fundamental));
        //        std::printf("%sFundamental Index: %d\n", prefix, fundamental_index);
    }

private:
    Unit<Volt, 0>                       rms_voltage_phase_1_{};
    Unit<Volt, 0>                       rms_voltage_phase_2_{};
    Unit<Volt, 0>                       rms_voltage_phase_3_{};
    Unit<Volt, 0>                       rms_voltage_phase_1_to_2_{};
    Unit<Volt, 0>                       rms_voltage_phase_2_to_3_{};
    Unit<Volt, 0>                       rms_voltage_phase_3_to_1_{};
    Unit<Boolean, 0>                    phase_rotation_ok_{};
    Unit<Amp, 0>                        rms_current_phase_1_{};
    Unit<Amp, 0>                        rms_current_phase_2_{};
    Unit<Amp, 0>                        rms_current_phase_3_{};
    Unit<Amp, 0>                        rms_current_neutral_{};
    Unit<Amp, 0>                        rms_current_leak_{};
    Unit<Watt, 0>                       active_power_phase_1_{};
    Unit<Watt, 0>                       active_power_phase_2_{};
    Unit<Watt, 0>                       active_power_phase_3_{};
    Unit<Watt, 0>                       cumulated_active_power_{};
    Unit<VoltAmp, 0>                    apparent_power_phase_1_{};
    Unit<VoltAmp, 0>                    apparent_power_phase_2_{};
    Unit<VoltAmp, 0>                    apparent_power_phase_3_{};
    Unit<VoltAmp, 0>                    cumulated_apparent_power_{};
    Unit<VoltAmpReactive, 0>            reactive_power_phase_1_{};
    Unit<VoltAmpReactive, 0>            reactive_power_phase_2_{};
    Unit<VoltAmpReactive, 0>            reactive_power_phase_3_{};
    Unit<VoltAmpReactive, 0>            cumulated_reactive_power_{};
    Unit<WattPerVoltAmp, 2>             power_factor_phase_1_{};
    Unit<WattPerVoltAmp, 2>             power_factor_phase_2_{};
    Unit<WattPerVoltAmp, 2>             power_factor_phase_3_{};
    Unit<WattHour, 0>                   active_energy_phase_1_{};
    Unit<WattHour, 0>                   active_energy_phase_2_{};
    Unit<WattHour, 0>                   active_energy_phase_3_{};
    Unit<WattHour, 0>                   cumulated_active_energy_{};
    Unit<VoltAmpHour, 0>                apparent_energy_phase_1_{};
    Unit<VoltAmpHour, 0>                apparent_energy_phase_2_{};
    Unit<VoltAmpHour, 0>                apparent_energy_phase_3_{};
    Unit<VoltAmpHour, 0>                cumulated_apparent_energy_{};
    Unit<VoltAmpReactiveHour, 0>        reactive_energy_phase_1_{};
    Unit<VoltAmpReactiveHour, 0>        reactive_energy_phase_2_{};
    Unit<VoltAmpReactiveHour, 0>        reactive_energy_phase_3_{};
    Unit<VoltAmpReactiveHour, 0>        cumulated_reactive_energy_{};
    Unit<Hertz, 3>                      frequency_phase_1_{};
    Unit<Hertz, 3>                      frequency_phase_2_{};
    Unit<Hertz, 3>                      frequency_phase_3_{};
    Unit<Hertz, 3>                      frequency_average_{};
    Unit<Degrees, 2>                    phi_phase_1_to_2_{};
    Unit<Degrees, 2>                    phi_phase_2_to_3_{};
    Unit<Degrees, 2>                    phi_phase_3_to_1_{};
    Unit<Degrees, 2>                    phi_phase_1_{};
    Unit<Degrees, 2>                    phi_phase_2_{};
    Unit<Degrees, 2>                    phi_phase_3_{};
    Unit<Percentage, 2>                 voltage_thd_phase_1_{};
    Unit<Percentage, 2>                 voltage_thd_phase_2_{};
    Unit<Percentage, 2>                 voltage_thd_phase_3_{};
    Unit<Percentage, 2>                 current_thd_phase_1_{};
    Unit<Percentage, 2>                 current_thd_phase_2_{};
    Unit<Percentage, 2>                 current_thd_phase_3_{};
    std::array<Unit<Percentage, 2>, 40> voltage_hd_phase_1_{};
    std::array<Unit<Percentage, 2>, 40> voltage_hd_phase_2_{};
    std::array<Unit<Percentage, 2>, 40> voltage_hd_phase_3_{};
    std::array<Unit<Percentage, 2>, 40> current_hd_phase_1_{};
    std::array<Unit<Percentage, 2>, 40> current_hd_phase_2_{};
    std::array<Unit<Percentage, 2>, 40> current_hd_phase_3_{};
};

constexpr auto Readings::rms_voltage_phase_1() const noexcept
{
    return rms_voltage_phase_1_.value;
}

constexpr void Readings::set_rms_voltage_phase_1(float value) noexcept
{
    set_value(rms_voltage_phase_1_, value);
}

constexpr auto Readings::rms_voltage_phase_2() const noexcept
{
    return rms_voltage_phase_2_.value;
}

constexpr void Readings::set_rms_voltage_phase_2(float value) noexcept
{
    set_value(rms_voltage_phase_2_, value);
}

constexpr auto Readings::rms_voltage_phase_3() const noexcept
{
    return rms_voltage_phase_3_.value;
}

constexpr void Readings::set_rms_voltage_phase_3(float value) noexcept
{
    set_value(rms_voltage_phase_3_, value);
}

constexpr auto Readings::rms_voltage_phase_1_to_2() const noexcept
{
    return rms_voltage_phase_1_to_2_.value;
}

constexpr void Readings::set_rms_voltage_phase_1_to_2(float value) noexcept
{
    set_value(rms_voltage_phase_1_to_2_, value);
}

constexpr auto Readings::rms_voltage_phase_2_to_3() const noexcept
{
    return rms_voltage_phase_2_to_3_.value;
}

constexpr void Readings::set_rms_voltage_phase_2_to_3(float value) noexcept
{
    set_value(rms_voltage_phase_2_to_3_, value);
}

constexpr auto Readings::rms_voltage_phase_3_to_1() const noexcept
{
    return rms_voltage_phase_3_to_1_.value;
}

constexpr void Readings::set_rms_voltage_phase_3_to_1(float value) noexcept
{
    set_value(rms_voltage_phase_3_to_1_, value);
}

constexpr auto Readings::phase_rotation_ok() const noexcept
{
    return phase_rotation_ok_.value != 0;
}

constexpr void Readings::set_phase_rotation_ok(bool is_ok) noexcept
{
    phase_rotation_ok_.value = static_cast<std::int8_t>(is_ok);
}

constexpr auto Readings::rms_current_phase_1() const noexcept
{
    return rms_current_phase_1_.value;
}

constexpr void Readings::set_rms_current_phase_1(float value) noexcept
{
    set_value(rms_current_phase_1_, value);
}

constexpr auto Readings::rms_current_phase_2() const noexcept
{
    return rms_current_phase_2_.value;
}

constexpr void Readings::set_rms_current_phase_2(float value) noexcept
{
    set_value(rms_current_phase_2_, value);
}

constexpr auto Readings::rms_current_phase_3() const noexcept
{
    return rms_current_phase_3_.value;
}

constexpr void Readings::set_rms_current_phase_3(float value) noexcept
{
    set_value(rms_current_phase_3_, value);
}

constexpr auto Readings::rms_current_neutral() const noexcept
{
    return rms_current_neutral_.value;
}

constexpr void Readings::set_rms_current_neutral(float value) noexcept
{
    set_value(rms_current_neutral_, value);
}

constexpr auto Readings::rms_current_leak() const noexcept
{
    return rms_current_leak_.value;
}

constexpr void Readings::set_rms_current_leak(float value) noexcept
{
    set_value(rms_current_leak_, value);
}

constexpr auto Readings::active_power_phase_1() const noexcept
{
    return active_power_phase_1_.value;
}

constexpr void Readings::set_active_power_phase_1(float value) noexcept
{
    set_value(active_power_phase_1_, value);
}

constexpr auto Readings::active_power_phase_2() const noexcept
{
    return active_power_phase_2_.value;
}

constexpr void Readings::set_active_power_phase_2(float value) noexcept
{
    set_value(active_power_phase_2_, value);
}

constexpr auto Readings::active_power_phase_3() const noexcept
{
    return active_power_phase_3_.value;
}

constexpr void Readings::set_active_power_phase_3(float value) noexcept
{
    set_value(active_power_phase_3_, value);
}

constexpr auto Readings::cumulated_active_power() const noexcept
{
    return cumulated_active_power_.value;
}

constexpr void Readings::set_cumulated_active_power(float value) noexcept
{
    set_value(cumulated_active_power_, value);
}

constexpr auto Readings::apparent_power_phase_1() const noexcept
{
    return apparent_power_phase_1_.value;
}

constexpr void Readings::set_apparent_power_phase_1(float value) noexcept
{
    set_value(apparent_power_phase_1_, value);
}

constexpr auto Readings::apparent_power_phase_2() const noexcept
{
    return apparent_power_phase_2_.value;
}

constexpr void Readings::set_apparent_power_phase_2(float value) noexcept
{
    set_value(apparent_power_phase_2_, value);
}

constexpr auto Readings::apparent_power_phase_3() const noexcept
{
    return apparent_power_phase_3_.value;
}

constexpr void Readings::set_apparent_power_phase_3(float value) noexcept
{
    set_value(apparent_power_phase_3_, value);
}

constexpr auto Readings::cumulated_apparent_power() const noexcept
{
    return cumulated_apparent_power_.value;
}

constexpr void Readings::set_cumulated_apparent_power(float value) noexcept
{
    set_value(cumulated_apparent_power_, value);
}

constexpr auto Readings::reactive_power_phase_1() const noexcept
{
    return reactive_power_phase_1_.value;
}

constexpr void Readings::set_reactive_power_phase_1(float value) noexcept
{
    set_value(reactive_power_phase_1_, value);
}

constexpr auto Readings::reactive_power_phase_2() const noexcept
{
    return reactive_power_phase_2_.value;
}

constexpr void Readings::set_reactive_power_phase_2(float value) noexcept
{
    set_value(reactive_power_phase_2_, value);
}

constexpr auto Readings::reactive_power_phase_3() const noexcept
{
    return reactive_power_phase_3_.value;
}

constexpr void Readings::set_reactive_power_phase_3(float value) noexcept
{
    set_value(reactive_power_phase_3_, value);
}

constexpr auto Readings::cumulated_reactive_power() const noexcept
{
    return cumulated_reactive_power_.value;
}

constexpr void Readings::set_cumulated_reactive_power(float value) noexcept
{
    set_value(cumulated_reactive_power_, value);
}

constexpr auto Readings::power_factor_phase_1() const noexcept
{
    return power_factor_phase_1_.value;
}

constexpr void Readings::set_power_factor_phase_1(float value) noexcept
{
    set_value(power_factor_phase_1_, value);
}

constexpr auto Readings::power_factor_phase_2() const noexcept
{
    return power_factor_phase_2_.value;
}

constexpr void Readings::set_power_factor_phase_2(float value) noexcept
{
    set_value(power_factor_phase_2_, value);
}

constexpr auto Readings::power_factor_phase_3() const noexcept
{
    return power_factor_phase_3_.value;
}

constexpr void Readings::set_power_factor_phase_3(float value) noexcept
{
    set_value(power_factor_phase_3_, value);
}

constexpr auto Readings::active_energy_phase_1() const noexcept
{
    return active_energy_phase_1_.value;
}

constexpr void Readings::set_active_energy_phase_1(float value) noexcept
{
    set_value(active_energy_phase_1_, value);
}

constexpr auto Readings::active_energy_phase_2() const noexcept
{
    return active_energy_phase_2_.value;
}

constexpr void Readings::set_active_energy_phase_2(float value) noexcept
{
    set_value(active_energy_phase_2_, value);
}

constexpr auto Readings::active_energy_phase_3() const noexcept
{
    return active_energy_phase_3_.value;
}

constexpr void Readings::set_active_energy_phase_3(float value) noexcept
{
    set_value(active_energy_phase_3_, value);
}

constexpr auto Readings::cumulated_active_energy() const noexcept
{
    return cumulated_active_energy_.value;
}

constexpr void Readings::set_cumulated_active_energy(float value) noexcept
{
    set_value(cumulated_active_energy_, value);
}

constexpr auto Readings::apparent_energy_phase_1() const noexcept
{
    return apparent_energy_phase_1_.value;
}

constexpr void Readings::set_apparent_energy_phase_1(float value) noexcept
{
    set_value(apparent_energy_phase_1_, value);
}

constexpr auto Readings::apparent_energy_phase_2() const noexcept
{
    return apparent_energy_phase_2_.value;
}

constexpr void Readings::set_apparent_energy_phase_2(float value) noexcept
{
    set_value(apparent_energy_phase_2_, value);
}

constexpr auto Readings::apparent_energy_phase_3() const noexcept
{
    return apparent_energy_phase_3_.value;
}

constexpr void Readings::set_apparent_energy_phase_3(float value) noexcept
{
    set_value(apparent_energy_phase_3_, value);
}

constexpr auto Readings::cumulated_apparent_energy() const noexcept
{
    return cumulated_apparent_energy_.value;
}

constexpr void Readings::set_cumulated_apparent_energy(float value) noexcept
{
    set_value(cumulated_apparent_energy_, value);
}

constexpr auto Readings::reactive_energy_phase_1() const noexcept
{
    return reactive_energy_phase_1_.value;
}

constexpr void Readings::set_reactive_energy_phase_1(float value) noexcept
{
    set_value(reactive_energy_phase_1_, value);
}

constexpr auto Readings::reactive_energy_phase_2() const noexcept
{
    return reactive_energy_phase_2_.value;
}

constexpr void Readings::set_reactive_energy_phase_2(float value) noexcept
{
    set_value(reactive_energy_phase_2_, value);
}

constexpr auto Readings::reactive_energy_phase_3() const noexcept
{
    return reactive_energy_phase_3_.value;
}

constexpr void Readings::set_reactive_energy_phase_3(float value) noexcept
{
    set_value(reactive_energy_phase_3_, value);
}

constexpr auto Readings::cumulated_reactive_energy() const noexcept
{
    return cumulated_reactive_energy_.value;
}

constexpr void Readings::set_cumulated_reactive_energy(float value) noexcept
{
    set_value(cumulated_reactive_energy_, value);
}

constexpr auto Readings::frequency_phase_1() const noexcept
{
    return frequency_phase_1_.value;
}

constexpr void Readings::set_frequency_phase_1(float value) noexcept
{
    set_value(frequency_phase_1_, value);
}

constexpr auto Readings::frequency_phase_2() const noexcept
{
    return frequency_phase_2_.value;
}

constexpr void Readings::set_frequency_phase_2(float value) noexcept
{
    set_value(frequency_phase_2_, value);
}

constexpr auto Readings::frequency_phase_3() const noexcept
{
    return frequency_phase_3_.value;
}

constexpr void Readings::set_frequency_phase_3(float value) noexcept
{
    set_value(frequency_phase_3_, value);
}

constexpr auto Readings::frequency_average() const noexcept
{
    return frequency_average_.value;
}

constexpr void Readings::set_frequency_average(float value) noexcept
{
    set_value(frequency_average_, value);
}

constexpr auto Readings::phi_phase_1_to_2() const noexcept
{
    return phi_phase_1_to_2_.value;
}

constexpr void Readings::set_phi_phase_1_to_2(float value) noexcept
{
    set_value(phi_phase_1_to_2_, value);
}

constexpr auto Readings::phi_phase_2_to_3() const noexcept
{
    return phi_phase_2_to_3_.value;
}

constexpr void Readings::set_phi_phase_2_to_3(float value) noexcept
{
    set_value(phi_phase_2_to_3_, value);
}

constexpr auto Readings::phi_phase_3_to_1() const noexcept
{
    return phi_phase_3_to_1_.value;
}

constexpr void Readings::set_phi_phase_3_to_1(float value) noexcept
{
    set_value(phi_phase_3_to_1_, value);
}

constexpr auto Readings::phi_phase_1() const noexcept
{
    return phi_phase_1_.value;
}

constexpr void Readings::set_phi_phase_1(float value) noexcept
{
    set_value(phi_phase_1_, value);
}

constexpr auto Readings::phi_phase_2() const noexcept
{
    return phi_phase_2_.value;
}

constexpr void Readings::set_phi_phase_2(float value) noexcept
{
    set_value(phi_phase_2_, value);
}

constexpr auto Readings::phi_phase_3() const noexcept
{
    return phi_phase_3_.value;
}

constexpr void Readings::set_phi_phase_3(float value) noexcept
{
    set_value(phi_phase_3_, value);
}

constexpr auto Readings::voltage_thd_phase_1() const noexcept
{
    return voltage_thd_phase_1_.value;
}

constexpr void Readings::set_voltage_thd_phase_1(float value) noexcept
{
    set_value(voltage_thd_phase_1_, value);
}

constexpr auto Readings::voltage_thd_phase_2() const noexcept
{
    return voltage_thd_phase_2_.value;
}

constexpr void Readings::set_voltage_thd_phase_2(float value) noexcept
{
    set_value(voltage_thd_phase_2_, value);
}

constexpr auto Readings::voltage_thd_phase_3() const noexcept
{
    return voltage_thd_phase_3_.value;
}

constexpr void Readings::set_voltage_thd_phase_3(float value) noexcept
{
    set_value(voltage_thd_phase_3_, value);
}

constexpr auto Readings::current_thd_phase_1() const noexcept
{
    return current_thd_phase_1_.value;
}

constexpr void Readings::set_current_thd_phase_1(float value) noexcept
{
    set_value(current_thd_phase_1_, value);
}

constexpr auto Readings::current_thd_phase_2() const noexcept
{
    return current_thd_phase_2_.value;
}

constexpr void Readings::set_current_thd_phase_2(float value) noexcept
{
    set_value(current_thd_phase_2_, value);
}

constexpr auto Readings::current_thd_phase_3() const noexcept
{
    return current_thd_phase_3_.value;
}

constexpr void Readings::set_current_thd_phase_3(float value) noexcept
{
    set_value(current_thd_phase_3_, value);
}

constexpr void Readings::set_voltage_hd_phase_1(const Complex *values, std::size_t count) noexcept
{
    set_harmonic_distortion(voltage_hd_phase_1_,
        &Readings::set_voltage_thd_phase_1,
        values,
        count,
        "V1 ");
}

constexpr void Readings::set_voltage_hd_phase_2(const Complex *values, std::size_t count) noexcept
{
    set_harmonic_distortion(voltage_hd_phase_2_,
        &Readings::set_voltage_thd_phase_2,
        values,
        count,
        "V2 ");
}

constexpr void Readings::set_voltage_hd_phase_3(const Complex *values, std::size_t count) noexcept
{
    set_harmonic_distortion(voltage_hd_phase_3_,
        &Readings::set_voltage_thd_phase_3,
        values,
        count,
        "V3 ");
}

constexpr void Readings::set_current_hd_phase_1(const Complex *values, std::size_t count) noexcept
{
    set_harmonic_distortion(current_hd_phase_1_,
        &Readings::set_current_thd_phase_1,
        values,
        count,
        "I1 ");
}

constexpr void Readings::set_current_hd_phase_2(const Complex *values, std::size_t count) noexcept
{
    set_harmonic_distortion(current_hd_phase_2_,
        &Readings::set_current_thd_phase_2,
        values,
        count,
        "I2 ");
}

constexpr void Readings::set_current_hd_phase_3(const Complex *values, std::size_t count) noexcept
{
    set_harmonic_distortion(current_hd_phase_3_,
        &Readings::set_current_thd_phase_3,
        values,
        count,
        "I3 ");
}

constexpr std::pair<std::size_t, float> Readings::find_fundamental_freq(const Complex *values,
    std::size_t count) noexcept
{
    const auto max_i = std::min(count, std::size_t{ 60 });

    auto index = std::size_t{ 0 };
    auto value = float{ 0.F };

    for (std::size_t i = 40; i < max_i; ++i)
    {
        const auto v = std::abs(values[i][0]);
        if (v > value)
        {
            value = v;
            index = i;
        }
    }

    return { index, value };
}

constexpr float Readings::find_next_frequency(std::size_t index,
    std::size_t                                           min_offset,
    std::size_t                                           max_offset,
    const Complex                                        *values,
    std::size_t                                           count) noexcept
{
    auto value = values[index][0];

    min_offset       = index - min_offset;
    max_offset       = index + max_offset;
    const auto max_i = std::min(count, max_offset);

    for (std::size_t i = min_offset; i < max_i; ++i)
    {
        const auto v = std::abs(values[i][0]);
        if (v > value)
        {
            value = v;
            index = i;
        }
    }

    return value;
}
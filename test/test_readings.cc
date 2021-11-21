#include <elsen/global.hh>
#include <hedley/hedley.h>

HEDLEY_DIAGNOSTIC_PUSH
ELSEN_DIAGNOSTIC_IGNORE_KEYWORD_MACRO
#define private public
#include "readings.hh"
HEDLEY_DIAGNOSTIC_POP

#include <fmt/format.h>

#include <cmocka.hh>

namespace
{
    constexpr double EPSILON{ 4.94065645841247E-324 };
}

void readings_all(void **)
{
    Readings readings{};

    {
        using UnderlyingType = decltype(Readings::rms_voltage_phase_1_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 213230.032F };
        constexpr auto EXPECTED{ static_cast<UnderlyingType>(ORIGINAL_VALUE) };

        readings.set_rms_voltage_phase_1(ORIGINAL_VALUE);
        assert_true(readings.rms_voltage_phase_1_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::rms_voltage_phase_2_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 223330.032F };
        constexpr auto EXPECTED{ static_cast<UnderlyingType>(ORIGINAL_VALUE) };

        readings.set_rms_voltage_phase_2(ORIGINAL_VALUE);
        assert_true(readings.rms_voltage_phase_2_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::rms_voltage_phase_3_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 240561.032F };
        constexpr auto EXPECTED{ static_cast<UnderlyingType>(ORIGINAL_VALUE) };

        readings.set_rms_voltage_phase_3(ORIGINAL_VALUE);
        assert_true(readings.rms_voltage_phase_3_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::rms_voltage_phase_1_to_2_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 400042.032F };
        constexpr auto EXPECTED{ static_cast<UnderlyingType>(ORIGINAL_VALUE) };

        readings.set_rms_voltage_phase_1_to_2(ORIGINAL_VALUE);
        assert_true(readings.rms_voltage_phase_1_to_2_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::rms_voltage_phase_2_to_3_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 402356.032F };
        constexpr auto EXPECTED{ static_cast<UnderlyingType>(ORIGINAL_VALUE) };

        readings.set_rms_voltage_phase_2_to_3(ORIGINAL_VALUE);
        assert_true(readings.rms_voltage_phase_2_to_3_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::rms_voltage_phase_3_to_1_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 399990.032F };
        constexpr auto EXPECTED{ static_cast<UnderlyingType>(ORIGINAL_VALUE) };

        readings.set_rms_voltage_phase_3_to_1(ORIGINAL_VALUE);
        assert_true(readings.rms_voltage_phase_3_to_1_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::phase_rotation_ok_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ true };
        constexpr auto EXPECTED{ static_cast<UnderlyingType>(ORIGINAL_VALUE) };

        readings.set_phase_rotation_ok(ORIGINAL_VALUE);
        assert_true(readings.phase_rotation_ok_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::rms_current_phase_1_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 123360.032F };
        constexpr auto EXPECTED{ static_cast<UnderlyingType>(ORIGINAL_VALUE) };

        readings.set_rms_current_phase_1(ORIGINAL_VALUE);
        assert_true(readings.rms_current_phase_1_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::rms_current_phase_2_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 100860.032F };
        constexpr auto EXPECTED{ static_cast<UnderlyingType>(ORIGINAL_VALUE) };

        readings.set_rms_current_phase_2(ORIGINAL_VALUE);
        assert_true(readings.rms_current_phase_2_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::rms_current_phase_3_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 99123.032F };
        constexpr auto EXPECTED{ static_cast<UnderlyingType>(ORIGINAL_VALUE) };

        readings.set_rms_current_phase_3(ORIGINAL_VALUE);
        assert_true(readings.rms_current_phase_3_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::rms_current_neutral_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 10223.032F };
        constexpr auto EXPECTED{ static_cast<UnderlyingType>(ORIGINAL_VALUE) };

        readings.set_rms_current_neutral(ORIGINAL_VALUE);
        assert_true(readings.rms_current_neutral_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::rms_current_leak_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 1.032F };
        constexpr auto EXPECTED{ static_cast<UnderlyingType>(ORIGINAL_VALUE) };

        readings.set_rms_current_leak(ORIGINAL_VALUE);
        assert_true(readings.rms_current_leak_.base_value() == EXPECTED);
    }
    {
        constexpr auto ORIGINAL_VALUE{ 2024026858.032F };
        constexpr auto EXPECTED{ 2024026880 };

        readings.set_active_power_phase_1(ORIGINAL_VALUE);
        assert_true(readings.active_power_phase_1_.base_value() == EXPECTED);
    }
    {
        constexpr auto ORIGINAL_VALUE{ 0.032F };
        constexpr auto EXPECTED{ 0 };

        readings.set_active_power_phase_2(ORIGINAL_VALUE);
        assert_true(readings.active_power_phase_2_.base_value() == EXPECTED);
    }
    {
        constexpr auto ORIGINAL_VALUE{ 123456789.032F };
        constexpr auto EXPECTED{ 123456792 };

        readings.set_active_power_phase_3(ORIGINAL_VALUE);
        assert_true(readings.active_power_phase_3_.base_value() == EXPECTED);
    }
    {
        constexpr auto ORIGINAL_VALUE{ 2147483647.032F };
        constexpr auto EXPECTED{ 2147483647 };

        readings.set_cumulated_active_power(ORIGINAL_VALUE);
        assert_true(readings.cumulated_active_power_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::apparent_power_phase_1_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 1200210.036F };
        constexpr auto EXPECTED = UnderlyingType{ 1200210 };

        readings.set_apparent_power_phase_1(ORIGINAL_VALUE);
        assert_true(readings.apparent_power_phase_1_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::apparent_power_phase_2_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 1300123.036F };
        constexpr auto EXPECTED = UnderlyingType{ 1300123 };

        readings.set_apparent_power_phase_2(ORIGINAL_VALUE);
        assert_true(readings.apparent_power_phase_2_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::apparent_power_phase_3_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 1500999.036F };
        constexpr auto EXPECTED = UnderlyingType{ 1500999 };

        readings.set_apparent_power_phase_3(ORIGINAL_VALUE);
        assert_true(readings.apparent_power_phase_3_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::cumulated_apparent_power_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 4001332.036F };
        constexpr auto EXPECTED = UnderlyingType{ 4001332 };

        readings.set_cumulated_apparent_power(ORIGINAL_VALUE);
        assert_true(readings.cumulated_apparent_power_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::reactive_power_phase_1_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ -2024026857.036F };
        constexpr auto EXPECTED = UnderlyingType{ -2024026880 };

        readings.set_reactive_power_phase_1(ORIGINAL_VALUE);
        assert_true(readings.reactive_power_phase_1_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::reactive_power_phase_2_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 0.36F };
        constexpr auto EXPECTED = UnderlyingType{ 0 };

        readings.set_reactive_power_phase_2(ORIGINAL_VALUE);
        assert_true(readings.reactive_power_phase_2_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::reactive_power_phase_3_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ -123456791.036F };
        constexpr auto EXPECTED = UnderlyingType{ -123456792 };

        readings.set_reactive_power_phase_3(ORIGINAL_VALUE);
        assert_true(readings.reactive_power_phase_3_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::cumulated_reactive_power_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ -2147483648.036F };
        constexpr auto EXPECTED = UnderlyingType{ -2147483648 };

        readings.set_cumulated_reactive_power(ORIGINAL_VALUE);
        assert_true(readings.cumulated_reactive_power_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::power_factor_phase_1_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ -0.89F };
        constexpr auto EXPECTED = UnderlyingType{ -89 };

        readings.set_power_factor_phase_1(ORIGINAL_VALUE);
        assert_true(readings.power_factor_phase_1_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::power_factor_phase_2_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 0.110F };
        constexpr auto EXPECTED = UnderlyingType{ 11 };

        readings.set_power_factor_phase_2(ORIGINAL_VALUE);
        assert_true(readings.power_factor_phase_2_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::power_factor_phase_3_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 0.710F };
        constexpr auto EXPECTED = UnderlyingType{ 71 };

        readings.set_power_factor_phase_3(ORIGINAL_VALUE);
        assert_true(readings.power_factor_phase_3_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::active_energy_phase_1_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 173709550200.036F };
        constexpr auto EXPECTED = UnderlyingType{ 173709557760 };

        readings.set_active_energy_phase_1(ORIGINAL_VALUE);
        assert_true(readings.active_energy_phase_1_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::active_energy_phase_2_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 854.036F };
        constexpr auto EXPECTED = UnderlyingType{ 854 };

        readings.set_active_energy_phase_2(ORIGINAL_VALUE);
        assert_true(readings.active_energy_phase_2_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::active_energy_phase_3_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 6666.036F };
        constexpr auto EXPECTED = UnderlyingType{ 6666 };

        readings.set_active_energy_phase_3(ORIGINAL_VALUE);
        assert_true(readings.active_energy_phase_3_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::cumulated_active_energy_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 173709557720.036F };
        constexpr auto EXPECTED = UnderlyingType{ 173709557760 };

        readings.set_cumulated_active_energy(ORIGINAL_VALUE);
        assert_true(readings.cumulated_active_energy_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::apparent_energy_phase_1_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 6154.036F };
        constexpr auto EXPECTED = UnderlyingType{ 6154 };

        readings.set_apparent_energy_phase_1(ORIGINAL_VALUE);
        assert_true(readings.apparent_energy_phase_1_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::apparent_energy_phase_2_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 9521.036F };
        constexpr auto EXPECTED = UnderlyingType{ 9521 };

        readings.set_apparent_energy_phase_2(ORIGINAL_VALUE);
        assert_true(readings.apparent_energy_phase_2_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::apparent_energy_phase_3_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 65321.036F };
        constexpr auto EXPECTED = UnderlyingType{ 65321 };

        readings.set_apparent_energy_phase_3(ORIGINAL_VALUE);
        assert_true(readings.apparent_energy_phase_3_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::cumulated_apparent_energy_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 80996.036F };
        constexpr auto EXPECTED = UnderlyingType{ 80996 };

        readings.set_cumulated_apparent_energy(ORIGINAL_VALUE);
        assert_true(readings.cumulated_apparent_energy_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::reactive_energy_phase_1_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ -31540.036F };
        constexpr auto EXPECTED = UnderlyingType{ -31540 };

        readings.set_reactive_energy_phase_1(ORIGINAL_VALUE);
        assert_true(readings.reactive_energy_phase_1_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::reactive_energy_phase_2_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 99620.036F };
        constexpr auto EXPECTED = UnderlyingType{ 99620 };

        readings.set_reactive_energy_phase_2(ORIGINAL_VALUE);
        assert_true(readings.reactive_energy_phase_2_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::reactive_energy_phase_3_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ -9631.036F };
        constexpr auto EXPECTED = UnderlyingType{ -9631 };

        readings.set_reactive_energy_phase_3(ORIGINAL_VALUE);
        assert_true(readings.reactive_energy_phase_3_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::cumulated_reactive_energy_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 58449.036F };
        constexpr auto EXPECTED = UnderlyingType{ 58449 };

        readings.set_cumulated_reactive_energy(ORIGINAL_VALUE);
        assert_true(readings.cumulated_reactive_energy_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::frequency_phase_1_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 50.990F };
        constexpr auto EXPECTED = UnderlyingType{ 50990 };

        readings.set_frequency_phase_1(ORIGINAL_VALUE);
        assert_true(readings.frequency_phase_1_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::frequency_phase_2_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 50.110F };
        constexpr auto EXPECTED = UnderlyingType{ 50110 };

        readings.set_frequency_phase_2(ORIGINAL_VALUE);
        assert_true(readings.frequency_phase_2_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::frequency_phase_3_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 50.130F };
        constexpr auto EXPECTED = UnderlyingType{ 50130 };

        readings.set_frequency_phase_3(ORIGINAL_VALUE);
        assert_true(readings.frequency_phase_3_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::frequency_average_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 50.410F };
        constexpr auto EXPECTED = UnderlyingType{ 50410 };

        readings.set_frequency_average(ORIGINAL_VALUE);
        assert_true(readings.frequency_average_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::phi_phase_1_to_2_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 0.90F };
        constexpr auto EXPECTED = UnderlyingType{ 90 };

        readings.set_phi_phase_1_to_2(ORIGINAL_VALUE);
        assert_true(readings.phi_phase_1_to_2_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::phi_phase_2_to_3_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ -1.65F };
        constexpr auto EXPECTED = UnderlyingType{ -165 };

        readings.set_phi_phase_2_to_3(ORIGINAL_VALUE);
        assert_true(readings.phi_phase_2_to_3_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::phi_phase_3_to_1_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ -9.150F };
        constexpr auto EXPECTED = UnderlyingType{ -915 };

        readings.set_phi_phase_3_to_1(ORIGINAL_VALUE);
        assert_true(readings.phi_phase_3_to_1_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::phi_phase_1_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 0.66F };
        constexpr auto EXPECTED = UnderlyingType{ 66 };

        readings.set_phi_phase_1(ORIGINAL_VALUE);
        assert_true(readings.phi_phase_1_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::phi_phase_2_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 0.99F };
        constexpr auto EXPECTED = UnderlyingType{ 99 };

        readings.set_phi_phase_2(ORIGINAL_VALUE);
        assert_true(readings.phi_phase_2_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::phi_phase_3_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 1.12F };
        constexpr auto EXPECTED = UnderlyingType{ 112 };

        readings.set_phi_phase_3(ORIGINAL_VALUE);
        assert_true(readings.phi_phase_3_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::voltage_thd_phase_1_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 12.34F };
        constexpr auto EXPECTED = UnderlyingType{ 1234 };

        readings.set_voltage_thd_phase_1(ORIGINAL_VALUE);
        assert_true(readings.voltage_thd_phase_1_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::voltage_thd_phase_2_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 12.34F };
        constexpr auto EXPECTED = UnderlyingType{ 1234 };

        readings.set_voltage_thd_phase_2(ORIGINAL_VALUE);
        assert_true(readings.voltage_thd_phase_2_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::voltage_thd_phase_3_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 12.34F };
        constexpr auto EXPECTED = UnderlyingType{ 1234 };

        readings.set_voltage_thd_phase_3(ORIGINAL_VALUE);
        assert_true(readings.voltage_thd_phase_3_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::current_thd_phase_1_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 12.34F };
        constexpr auto EXPECTED = UnderlyingType{ 1234 };

        readings.set_current_thd_phase_1(ORIGINAL_VALUE);
        assert_true(readings.current_thd_phase_1_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::current_thd_phase_2_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 12.34F };
        constexpr auto EXPECTED = UnderlyingType{ 1234 };

        readings.set_current_thd_phase_2(ORIGINAL_VALUE);
        assert_true(readings.current_thd_phase_2_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = decltype(Readings::current_thd_phase_3_)::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE{ 12.34F };
        constexpr auto EXPECTED = UnderlyingType{ 1234 };

        readings.set_current_thd_phase_3(ORIGINAL_VALUE);
        assert_true(readings.current_thd_phase_3_.base_value() == EXPECTED);
    }
    {
        using UnderlyingType = std::remove_pointer_t<
            decltype(Readings::voltage_hd_phase_1_.data())>::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE = std::array{ 12.34F, .0F };
        constexpr auto EXPECTED       = UnderlyingType{ 100 };

        const auto values =
            std::vector<std::array<float, 2>>(51 * readings.voltage_hd_phase_1_.size(),
                ORIGINAL_VALUE);
        readings.set_voltage_hd_phase_1(reinterpret_cast<Readings::Complex const *>(values.data()),
            values.size());
        for (auto &v : readings.voltage_hd_phase_1_)
        {
            assert_true(v.base_value() == EXPECTED);
            set_value(v, 12.34F);
        }
        assert_true(static_cast<double>(
                        std::abs(readings.voltage_thd_phase_1_.base_value() - 624.F)) < EPSILON);
    }
    {
        using UnderlyingType = std::remove_pointer_t<
            decltype(Readings::voltage_hd_phase_2_.data())>::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE = std::array{ 12.34F, .0F };
        constexpr auto EXPECTED       = UnderlyingType{ 100 };

        const auto values =
            std::vector<std::array<float, 2>>(51 * readings.voltage_hd_phase_2_.size(),
                ORIGINAL_VALUE);
        readings.set_voltage_hd_phase_2(reinterpret_cast<Readings::Complex const *>(values.data()),
            values.size());
        for (auto &v : readings.voltage_hd_phase_2_)
        {
            assert_true(v.base_value() == EXPECTED);
            set_value(v, 12.34F);
        }
        assert_true(static_cast<double>(
                        std::abs(readings.voltage_thd_phase_2_.base_value() - 624.F)) < EPSILON);
    }
    {
        using UnderlyingType = std::remove_pointer_t<
            decltype(Readings::voltage_hd_phase_3_.data())>::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE = std::array{ 12.34F, .0F };
        constexpr auto EXPECTED       = UnderlyingType{ 100 };

        const auto values =
            std::vector<std::array<float, 2>>(51 * readings.voltage_hd_phase_3_.size(),
                ORIGINAL_VALUE);
        readings.set_voltage_hd_phase_3(reinterpret_cast<Readings::Complex const *>(values.data()),
            values.size());
        for (auto &v : readings.voltage_hd_phase_3_)
        {
            assert_true(v.base_value() == EXPECTED);
            set_value(v, 12.34F);
        }
        assert_true(static_cast<double>(
                        std::abs(readings.voltage_thd_phase_3_.base_value() - 624.F)) < EPSILON);
    }
    {
        using UnderlyingType = std::remove_pointer_t<
            decltype(Readings::current_hd_phase_1_.data())>::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE = std::array{ 12.34F, .0F };
        constexpr auto EXPECTED       = UnderlyingType{ 100 };

        const auto values =
            std::vector<std::array<float, 2>>(51 * readings.current_hd_phase_1_.size(),
                ORIGINAL_VALUE);
        readings.set_current_hd_phase_1(reinterpret_cast<Readings::Complex const *>(values.data()),
            values.size());
        for (auto &v : readings.current_hd_phase_1_)
        {
            assert_true(v.base_value() == EXPECTED);
            set_value(v, 12.34F);
        }
        assert_true(static_cast<double>(
                        std::abs(readings.current_thd_phase_1_.base_value() - 624.F)) < EPSILON);
    }
    {
        using UnderlyingType = std::remove_pointer_t<
            decltype(Readings::current_hd_phase_2_.data())>::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE = std::array{ 12.34F, .0F };
        constexpr auto EXPECTED       = UnderlyingType{ 100 };

        const auto values =
            std::vector<std::array<float, 2>>(51 * readings.current_hd_phase_2_.size(),
                ORIGINAL_VALUE);
        readings.set_current_hd_phase_2(reinterpret_cast<Readings::Complex const *>(values.data()),
            values.size());
        for (auto &v : readings.current_hd_phase_2_)
        {
            assert_true(v.base_value() == EXPECTED);
            set_value(v, 12.34F);
        }
        assert_true(static_cast<double>(
                        std::abs(readings.current_thd_phase_2_.base_value() - 624.F)) < EPSILON);
    }
    {
        using UnderlyingType = std::remove_pointer_t<
            decltype(Readings::current_hd_phase_3_.data())>::Type::UnderlyingType;

        constexpr auto ORIGINAL_VALUE = std::array{ 12.34F, .0F };
        constexpr auto EXPECTED       = UnderlyingType{ 100 };

        const auto values =
            std::vector<std::array<float, 2>>(51 * readings.current_hd_phase_3_.size(),
                ORIGINAL_VALUE);
        readings.set_current_hd_phase_3(reinterpret_cast<Readings::Complex const *>(values.data()),
            values.size());
        for (auto &v : readings.current_hd_phase_3_)
        {
            assert_true(v.base_value() == EXPECTED);
            set_value(v, 12.34F);
        }
        assert_true(static_cast<double>(
                        std::abs(readings.current_thd_phase_3_.base_value() - 624.F)) < EPSILON);
    }

    constexpr auto EXPECTED_BINARY_HEX_STRING =
        "000340EE000368620003ABB100061AAA000623B400061A76010001E1E0000189FC00018333000027EF0000"
        "000178A432EA00000000075BCD157FFFFFFF001250520013D69B0016E747003D0E34875BCD1700000000F8A432"
        "E980000000A70C470000002871E5627800000000000003560000000000001A0A0000002871E57FD80000000000"
        "00180A0000000000002531000000000000FF290000000000013C64FFFFFFFFFFFF84CC0000000000018524FFFF"
        "FFFFFFFFDA61000000000000E451C72EC3BEC3D2C4EA005AFF5BFC6D00420063007004D204D204D204D204D204"
        "D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D2"
        "04D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204"
        "D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D2"
        "04D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204"
        "D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D2"
        "04D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204"
        "D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D2"
        "04D204D21A0A04D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204"
        "D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D2"
        "04D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204"
        "D204D204D204D204D204D204D204D204D204D204D204D204D204D204D204D2";

    const auto to_byte_array = [](std::string_view byte_array) -> std::vector<std::uint8_t> {
        if (byte_array.size() % 2 != 0)
        {
            return {};
        }

        auto result = std::vector<std::uint8_t>(byte_array.size() / 2);
        for (std::size_t index = 0; index < result.size(); ++index)
        {
            const auto byte_value = std::string{ byte_array.substr(index * 2, 2) };
            result[index] =
                static_cast<std::uint8_t>(std::strtoul(byte_value.c_str(), nullptr, 16));
        }

        return result;
    };

    readings.rms_voltage_phase_1_.value       = 213230;
    readings.rms_voltage_phase_2_.value       = 223330;
    readings.rms_voltage_phase_3_.value       = 240561;
    readings.rms_voltage_phase_1_to_2_.value  = 400042;
    readings.rms_voltage_phase_2_to_3_.value  = 402356;
    readings.rms_voltage_phase_3_to_1_.value  = 399990;
    readings.phase_rotation_ok_.value         = 1;
    readings.rms_current_phase_1_.value       = 123360;
    readings.rms_current_phase_2_.value       = 100860;
    readings.rms_current_phase_3_.value       = 99123;
    readings.rms_current_neutral_.value       = 10223;
    readings.rms_current_leak_.value          = 1;
    readings.active_power_phase_1_.value      = 2024026858;
    readings.active_power_phase_2_.value      = 0;
    readings.active_power_phase_3_.value      = 123456789;
    readings.cumulated_active_power_.value    = 2147483647;
    readings.apparent_power_phase_1_.value    = 1200210;
    readings.apparent_power_phase_2_.value    = 1300123;
    readings.apparent_power_phase_3_.value    = 1500999;
    readings.cumulated_apparent_power_.value  = 4001332;
    readings.reactive_power_phase_1_.value    = -2024026857;
    readings.reactive_power_phase_2_.value    = 0;
    readings.reactive_power_phase_3_.value    = -123456791;
    readings.cumulated_reactive_power_.value  = -2147483648;
    readings.power_factor_phase_1_.value      = -89;
    readings.power_factor_phase_2_.value      = 12;
    readings.power_factor_phase_3_.value      = 71;
    readings.active_energy_phase_1_.value     = 173709550200;
    readings.active_energy_phase_2_.value     = 854;
    readings.active_energy_phase_3_.value     = 6666;
    readings.cumulated_active_energy_.value   = 173709557720;
    readings.apparent_energy_phase_1_.value   = 6154;
    readings.apparent_energy_phase_2_.value   = 9521;
    readings.apparent_energy_phase_3_.value   = 65321;
    readings.cumulated_apparent_energy_.value = 80996;
    readings.reactive_energy_phase_1_.value   = -31540;
    readings.reactive_energy_phase_2_.value   = 99620;
    readings.reactive_energy_phase_3_.value   = -9631;
    readings.cumulated_reactive_energy_.value = 58449;
    readings.frequency_phase_1_.value         = 50990;
    readings.frequency_phase_2_.value         = 50110;
    readings.frequency_phase_3_.value         = 50130;
    readings.frequency_average_.value         = 50410;
    readings.phi_phase_1_to_2_.value          = 90;
    readings.phi_phase_2_to_3_.value          = -165;
    readings.phi_phase_3_to_1_.value          = -915;
    readings.phi_phase_1_.value               = 66;
    readings.phi_phase_2_.value               = 99;
    readings.phi_phase_3_.value               = 112;
    readings.voltage_thd_phase_1_.value       = 1234;
    readings.voltage_thd_phase_2_.value       = 1234;
    readings.voltage_thd_phase_3_.value       = 1234;
    readings.current_thd_phase_1_.value       = 1234;
    readings.current_thd_phase_2_.value       = 1234;
    readings.current_thd_phase_3_.value       = 1234;

    for (auto &v : readings.voltage_hd_phase_1_)
    {
        v.value = 1234;
    }

    for (auto &v : readings.voltage_hd_phase_2_)
    {
        v.value = 1234;
    }

    for (auto &v : readings.voltage_hd_phase_3_)
    {
        v.value = 1234;
    }

    for (auto &v : readings.current_hd_phase_1_)
    {
        v.value = 1234;
    }
    readings.current_hd_phase_1_[39].value = 6666;

    for (auto &v : readings.current_hd_phase_2_)
    {
        v.value = 1234;
    }

    for (auto &v : readings.current_hd_phase_3_)
    {
        v.value = 1234;
    }

    auto readings_serialized_hex_string = std::string{};

    const auto readings_serialized = readings.to_binary();
    assert_true(strlen(EXPECTED_BINARY_HEX_STRING) / 2 == readings_serialized.size());

    for (std::size_t i = 0; i < readings_serialized.size(); ++i)
    {
        auto expected_hex_byte = std::array<char, 2>{};
        expected_hex_byte[0]   = EXPECTED_BINARY_HEX_STRING[i * 2];
        expected_hex_byte[1]   = EXPECTED_BINARY_HEX_STRING[i * 2 + 1];

        auto serialized_hex_byte = std::array<char, 3>{};
        std::snprintf(serialized_hex_byte.data(), 3, "%02X", readings_serialized[i]);

        //        auto serialized_hex_byte = fmt::format("{:02x}", readings_serialized[i]);
        if (strncmp(serialized_hex_byte.data(), expected_hex_byte.data(), 2) != 0)
        {
            std::printf("%s != %.*s\n", serialized_hex_byte.data(), 2, expected_hex_byte.data());

            auto lhs = Readings::from_binary(readings_serialized.data());
            auto rhs = Readings::from_binary(to_byte_array(EXPECTED_BINARY_HEX_STRING).data());

            if (lhs.rms_voltage_phase_1_.value != rhs.rms_voltage_phase_1_.value) {}
            if (lhs.rms_voltage_phase_2_.value != rhs.rms_voltage_phase_2_.value) {}
            if (lhs.rms_voltage_phase_3_.value != rhs.rms_voltage_phase_3_.value) {}
            if (lhs.rms_voltage_phase_1_to_2_.value != rhs.rms_voltage_phase_1_to_2_.value)
            {
                assert_true(false);
            }
            if (lhs.rms_voltage_phase_2_to_3_.value != rhs.rms_voltage_phase_2_to_3_.value)
            {
                assert_true(false);
            }
            if (lhs.rms_voltage_phase_3_to_1_.value != rhs.rms_voltage_phase_3_to_1_.value)
            {
                assert_true(false);
            }
            if (lhs.phase_rotation_ok_.value != rhs.phase_rotation_ok_.value)
            {
                assert_true(false);
            }
            if (lhs.rms_current_phase_1_.value != rhs.rms_current_phase_1_.value)
            {
                assert_true(false);
            }
            if (lhs.rms_current_phase_2_.value != rhs.rms_current_phase_2_.value)
            {
                assert_true(false);
            }
            if (lhs.rms_current_phase_3_.value != rhs.rms_current_phase_3_.value)
            {
                assert_true(false);
            }
            if (lhs.rms_current_neutral_.value != rhs.rms_current_neutral_.value)
            {
                assert_true(false);
            }
            if (lhs.rms_current_leak_.value != rhs.rms_current_leak_.value)
            {
                assert_true(false);
            }
            if (lhs.active_power_phase_1_.value != rhs.active_power_phase_1_.value)
            {
                assert_true(false);
            }
            if (lhs.active_power_phase_2_.value != rhs.active_power_phase_2_.value)
            {
                assert_true(false);
            }
            if (lhs.active_power_phase_3_.value != rhs.active_power_phase_3_.value)
            {
                assert_true(false);
            }
            if (lhs.cumulated_active_power_.value != rhs.cumulated_active_power_.value)
            {
                assert_true(false);
            }
            if (lhs.apparent_power_phase_1_.value != rhs.apparent_power_phase_1_.value)
            {
                assert_true(false);
            }
            if (lhs.apparent_power_phase_2_.value != rhs.apparent_power_phase_2_.value)
            {
                assert_true(false);
            }
            if (lhs.apparent_power_phase_3_.value != rhs.apparent_power_phase_3_.value)
            {
                assert_true(false);
            }
            if (lhs.cumulated_apparent_power_.value != rhs.cumulated_apparent_power_.value)
            {
                assert_true(false);
            }
            if (lhs.reactive_power_phase_1_.value != rhs.reactive_power_phase_1_.value)
            {
                assert_true(false);
            }
            if (lhs.reactive_power_phase_2_.value != rhs.reactive_power_phase_2_.value)
            {
                assert_true(false);
            }
            if (lhs.reactive_power_phase_3_.value != rhs.reactive_power_phase_3_.value)
            {
                assert_true(false);
            }
            if (lhs.cumulated_reactive_power_.value != rhs.cumulated_reactive_power_.value)
            {
                assert_true(false);
            }
            if (lhs.power_factor_phase_1_.value != rhs.power_factor_phase_1_.value)
            {
                assert_true(false);
            }
            if (lhs.power_factor_phase_2_.value != rhs.power_factor_phase_2_.value)
            {
                assert_true(false);
            }
            if (lhs.power_factor_phase_3_.value != rhs.power_factor_phase_3_.value)
            {
                assert_true(false);
            }
            if (lhs.active_energy_phase_1_.value != rhs.active_energy_phase_1_.value)
            {
                assert_true(false);
            }
            if (lhs.active_energy_phase_2_.value != rhs.active_energy_phase_2_.value)
            {
                assert_true(false);
            }
            if (lhs.active_energy_phase_3_.value != rhs.active_energy_phase_3_.value)
            {
                assert_true(false);
            }
            if (lhs.cumulated_active_energy_.value != rhs.cumulated_active_energy_.value)
            {
                assert_true(false);
            }
            if (lhs.apparent_energy_phase_1_.value != rhs.apparent_energy_phase_1_.value)
            {
                assert_true(false);
            }
            if (lhs.apparent_energy_phase_2_.value != rhs.apparent_energy_phase_2_.value)
            {
                assert_true(false);
            }
            if (lhs.apparent_energy_phase_3_.value != rhs.apparent_energy_phase_3_.value)
            {
                assert_true(false);
            }
            if (lhs.cumulated_apparent_energy_.value != rhs.cumulated_apparent_energy_.value)
            {
                assert_true(false);
            }
            if (lhs.reactive_energy_phase_1_.value != rhs.reactive_energy_phase_1_.value)
            {
                assert_true(false);
            }
            if (lhs.reactive_energy_phase_2_.value != rhs.reactive_energy_phase_2_.value)
            {
                assert_true(false);
            }
            if (lhs.reactive_energy_phase_3_.value != rhs.reactive_energy_phase_3_.value)
            {
                assert_true(false);
            }
            if (lhs.cumulated_reactive_energy_.value != rhs.cumulated_reactive_energy_.value)
            {
                assert_true(false);
            }
            if (lhs.frequency_phase_1_.value != rhs.frequency_phase_1_.value)
            {
                assert_true(false);
            }
            if (lhs.frequency_phase_2_.value != rhs.frequency_phase_2_.value)
            {
                assert_true(false);
            }
            if (lhs.frequency_phase_3_.value != rhs.frequency_phase_3_.value)
            {
                assert_true(false);
            }
            if (lhs.frequency_average_.value != rhs.frequency_average_.value)
            {
                assert_true(false);
            }
            if (lhs.phi_phase_1_to_2_.value != rhs.phi_phase_1_to_2_.value)
            {
                assert_true(false);
            }
            if (lhs.phi_phase_2_to_3_.value != rhs.phi_phase_2_to_3_.value)
            {
                assert_true(false);
            }
            if (lhs.phi_phase_3_to_1_.value != rhs.phi_phase_3_to_1_.value)
            {
                assert_true(false);
            }
            if (lhs.phi_phase_1_.value != rhs.phi_phase_1_.value)
            {
                assert_true(false);
            }
            if (lhs.phi_phase_2_.value != rhs.phi_phase_2_.value)
            {
                assert_true(false);
            }
            if (lhs.phi_phase_3_.value != rhs.phi_phase_3_.value)
            {
                assert_true(false);
            }
            if (lhs.voltage_thd_phase_1_.value != rhs.voltage_thd_phase_1_.value)
            {
                assert_true(false);
            }
            if (lhs.voltage_thd_phase_2_.value != rhs.voltage_thd_phase_2_.value)
            {
                assert_true(false);
            }
            if (lhs.voltage_thd_phase_3_.value != rhs.voltage_thd_phase_3_.value)
            {
                assert_true(false);
            }
            if (lhs.current_thd_phase_1_.value != rhs.current_thd_phase_1_.value)
            {
                assert_true(false);
            }
            if (lhs.current_thd_phase_2_.value != rhs.current_thd_phase_2_.value)
            {
                assert_true(false);
            }
            if (lhs.current_thd_phase_3_.value != rhs.current_thd_phase_3_.value)
            {
                assert_true(false);
            }

            for (std::size_t j = 0; j < lhs.voltage_hd_phase_1_.size(); ++i)
            {
                if (lhs.voltage_hd_phase_1_[j].value != rhs.voltage_hd_phase_1_[j].value)
                {
                    assert_true(false);
                }
            }

            for (std::size_t j = 0; j < lhs.voltage_hd_phase_2_.size(); ++i)
            {
                if (lhs.voltage_hd_phase_2_[j].value != rhs.voltage_hd_phase_2_[j].value)
                {
                    assert_true(false);
                }
            }

            for (std::size_t j = 0; j < lhs.voltage_hd_phase_3_.size(); ++i)
            {
                if (lhs.voltage_hd_phase_3_[j].value != rhs.voltage_hd_phase_3_[j].value)
                {
                    assert_true(false);
                }
            }

            for (std::size_t j = 0; j < lhs.current_hd_phase_1_.size(); ++i)
            {
                if (lhs.current_hd_phase_1_[j].value != rhs.current_hd_phase_1_[j].value)
                {
                    assert_true(false);
                }
            }

            for (std::size_t j = 0; j < lhs.current_hd_phase_2_.size(); ++i)
            {
                if (lhs.current_hd_phase_2_[j].value != rhs.current_hd_phase_2_[j].value)
                {
                    assert_true(false);
                }
            }

            for (std::size_t j = 0; j < lhs.current_hd_phase_3_.size(); ++i)
            {
                if (lhs.current_hd_phase_3_[j].value != rhs.current_hd_phase_3_[j].value)
                {
                    assert_true(false);
                }
            }
        }

        readings_serialized_hex_string += serialized_hex_byte.data();
    }

    assert_true(readings_serialized_hex_string == EXPECTED_BINARY_HEX_STRING);
}

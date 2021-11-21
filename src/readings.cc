#include "readings.hh"

std::vector<std::uint8_t> Readings::to_binary()
{
    std::vector<std::uint8_t> result;
    result.reserve(706);

    rms_voltage_phase_1_.serialize_to(result);
    rms_voltage_phase_2_.serialize_to(result);
    rms_voltage_phase_3_.serialize_to(result);
    rms_voltage_phase_1_to_2_.serialize_to(result);
    rms_voltage_phase_2_to_3_.serialize_to(result);
    rms_voltage_phase_3_to_1_.serialize_to(result);
    phase_rotation_ok_.serialize_to(result);
    rms_current_phase_1_.serialize_to(result);
    rms_current_phase_2_.serialize_to(result);
    rms_current_phase_3_.serialize_to(result);
    rms_current_neutral_.serialize_to(result);
    rms_current_leak_.serialize_to(result);
    active_power_phase_1_.serialize_to(result);
    active_power_phase_2_.serialize_to(result);
    active_power_phase_3_.serialize_to(result);
    cumulated_active_power_.serialize_to(result);
    apparent_power_phase_1_.serialize_to(result);
    apparent_power_phase_2_.serialize_to(result);
    apparent_power_phase_3_.serialize_to(result);
    cumulated_apparent_power_.serialize_to(result);
    reactive_power_phase_1_.serialize_to(result);
    reactive_power_phase_2_.serialize_to(result);
    reactive_power_phase_3_.serialize_to(result);
    cumulated_reactive_power_.serialize_to(result);
    power_factor_phase_1_.serialize_to(result);
    power_factor_phase_2_.serialize_to(result);
    power_factor_phase_3_.serialize_to(result);
    active_energy_phase_1_.serialize_to(result);
    active_energy_phase_2_.serialize_to(result);
    active_energy_phase_3_.serialize_to(result);
    cumulated_active_energy_.serialize_to(result);
    apparent_energy_phase_1_.serialize_to(result);
    apparent_energy_phase_2_.serialize_to(result);
    apparent_energy_phase_3_.serialize_to(result);
    cumulated_apparent_energy_.serialize_to(result);
    reactive_energy_phase_1_.serialize_to(result);
    reactive_energy_phase_2_.serialize_to(result);
    reactive_energy_phase_3_.serialize_to(result);
    cumulated_reactive_energy_.serialize_to(result);
    frequency_phase_1_.serialize_to(result);
    frequency_phase_2_.serialize_to(result);
    frequency_phase_3_.serialize_to(result);
    frequency_average_.serialize_to(result);
    phi_phase_1_to_2_.serialize_to(result);
    phi_phase_2_to_3_.serialize_to(result);
    phi_phase_3_to_1_.serialize_to(result);
    phi_phase_1_.serialize_to(result);
    phi_phase_2_.serialize_to(result);
    phi_phase_3_.serialize_to(result);
    voltage_thd_phase_1_.serialize_to(result);
    voltage_thd_phase_2_.serialize_to(result);
    voltage_thd_phase_3_.serialize_to(result);
    current_thd_phase_1_.serialize_to(result);
    current_thd_phase_2_.serialize_to(result);
    current_thd_phase_3_.serialize_to(result);

    for (auto v : voltage_hd_phase_1_)
    {
        v.serialize_to(result);
    }

    for (auto v : voltage_hd_phase_2_)
    {
        v.serialize_to(result);
    }

    for (auto v : voltage_hd_phase_3_)
    {
        v.serialize_to(result);
    }

    for (auto v : current_hd_phase_1_)
    {
        v.serialize_to(result);
    }

    for (auto v : current_hd_phase_2_)
    {
        v.serialize_to(result);
    }

    for (auto v : current_hd_phase_3_)
    {
        v.serialize_to(result);
    }

    return result;
}

void Readings::to_binary(std::vector<std::uint8_t> &result)
{
    result.reserve(706);

    rms_voltage_phase_1_.serialize_to(result);
    rms_voltage_phase_2_.serialize_to(result);
    rms_voltage_phase_3_.serialize_to(result);
    rms_voltage_phase_1_to_2_.serialize_to(result);
    rms_voltage_phase_2_to_3_.serialize_to(result);
    rms_voltage_phase_3_to_1_.serialize_to(result);
    phase_rotation_ok_.serialize_to(result);
    rms_current_phase_1_.serialize_to(result);
    rms_current_phase_2_.serialize_to(result);
    rms_current_phase_3_.serialize_to(result);
    rms_current_neutral_.serialize_to(result);
    rms_current_leak_.serialize_to(result);
    active_power_phase_1_.serialize_to(result);
    active_power_phase_2_.serialize_to(result);
    active_power_phase_3_.serialize_to(result);
    cumulated_active_power_.serialize_to(result);
    apparent_power_phase_1_.serialize_to(result);
    apparent_power_phase_2_.serialize_to(result);
    apparent_power_phase_3_.serialize_to(result);
    cumulated_apparent_power_.serialize_to(result);
    reactive_power_phase_1_.serialize_to(result);
    reactive_power_phase_2_.serialize_to(result);
    reactive_power_phase_3_.serialize_to(result);
    cumulated_reactive_power_.serialize_to(result);
    power_factor_phase_1_.serialize_to(result);
    power_factor_phase_2_.serialize_to(result);
    power_factor_phase_3_.serialize_to(result);
    active_energy_phase_1_.serialize_to(result);
    active_energy_phase_2_.serialize_to(result);
    active_energy_phase_3_.serialize_to(result);
    cumulated_active_energy_.serialize_to(result);
    apparent_energy_phase_1_.serialize_to(result);
    apparent_energy_phase_2_.serialize_to(result);
    apparent_energy_phase_3_.serialize_to(result);
    cumulated_apparent_energy_.serialize_to(result);
    reactive_energy_phase_1_.serialize_to(result);
    reactive_energy_phase_2_.serialize_to(result);
    reactive_energy_phase_3_.serialize_to(result);
    cumulated_reactive_energy_.serialize_to(result);
    frequency_phase_1_.serialize_to(result);
    frequency_phase_2_.serialize_to(result);
    frequency_phase_3_.serialize_to(result);
    frequency_average_.serialize_to(result);
    phi_phase_1_to_2_.serialize_to(result);
    phi_phase_2_to_3_.serialize_to(result);
    phi_phase_3_to_1_.serialize_to(result);
    phi_phase_1_.serialize_to(result);
    phi_phase_2_.serialize_to(result);
    phi_phase_3_.serialize_to(result);
    voltage_thd_phase_1_.serialize_to(result);
    voltage_thd_phase_2_.serialize_to(result);
    voltage_thd_phase_3_.serialize_to(result);
    current_thd_phase_1_.serialize_to(result);
    current_thd_phase_2_.serialize_to(result);
    current_thd_phase_3_.serialize_to(result);

    for (auto v : voltage_hd_phase_1_)
    {
        v.serialize_to(result);
    }

    for (auto v : voltage_hd_phase_2_)
    {
        v.serialize_to(result);
    }

    for (auto v : voltage_hd_phase_3_)
    {
        v.serialize_to(result);
    }

    for (auto v : current_hd_phase_1_)
    {
        v.serialize_to(result);
    }

    for (auto v : current_hd_phase_2_)
    {
        v.serialize_to(result);
    }

    for (auto v : current_hd_phase_3_)
    {
        v.serialize_to(result);
    }
}

Readings Readings::from_binary(const std::uint8_t *payload) noexcept
{
    auto result = Readings{};

    result.rms_voltage_phase_1_.deserialize_from(payload);
    result.rms_voltage_phase_2_.deserialize_from(payload);
    result.rms_voltage_phase_3_.deserialize_from(payload);
    result.rms_voltage_phase_1_to_2_.deserialize_from(payload);
    result.rms_voltage_phase_2_to_3_.deserialize_from(payload);
    result.rms_voltage_phase_3_to_1_.deserialize_from(payload);
    result.phase_rotation_ok_.deserialize_from(payload);
    result.rms_current_phase_1_.deserialize_from(payload);
    result.rms_current_phase_2_.deserialize_from(payload);
    result.rms_current_phase_3_.deserialize_from(payload);
    result.rms_current_neutral_.deserialize_from(payload);
    result.rms_current_leak_.deserialize_from(payload);
    result.active_power_phase_1_.deserialize_from(payload);
    result.active_power_phase_2_.deserialize_from(payload);
    result.active_power_phase_3_.deserialize_from(payload);
    result.cumulated_active_power_.deserialize_from(payload);
    result.apparent_power_phase_1_.deserialize_from(payload);
    result.apparent_power_phase_2_.deserialize_from(payload);
    result.apparent_power_phase_3_.deserialize_from(payload);
    result.cumulated_apparent_power_.deserialize_from(payload);
    result.reactive_power_phase_1_.deserialize_from(payload);
    result.reactive_power_phase_2_.deserialize_from(payload);
    result.reactive_power_phase_3_.deserialize_from(payload);
    result.cumulated_reactive_power_.deserialize_from(payload);
    result.power_factor_phase_1_.deserialize_from(payload);
    result.power_factor_phase_2_.deserialize_from(payload);
    result.power_factor_phase_3_.deserialize_from(payload);
    result.active_energy_phase_1_.deserialize_from(payload);
    result.active_energy_phase_2_.deserialize_from(payload);
    result.active_energy_phase_3_.deserialize_from(payload);
    result.cumulated_active_energy_.deserialize_from(payload);
    result.apparent_energy_phase_1_.deserialize_from(payload);
    result.apparent_energy_phase_2_.deserialize_from(payload);
    result.apparent_energy_phase_3_.deserialize_from(payload);
    result.cumulated_apparent_energy_.deserialize_from(payload);
    result.reactive_energy_phase_1_.deserialize_from(payload);
    result.reactive_energy_phase_2_.deserialize_from(payload);
    result.reactive_energy_phase_3_.deserialize_from(payload);
    result.cumulated_reactive_energy_.deserialize_from(payload);
    result.frequency_phase_1_.deserialize_from(payload);
    result.frequency_phase_2_.deserialize_from(payload);
    result.frequency_phase_3_.deserialize_from(payload);
    result.frequency_average_.deserialize_from(payload);
    result.phi_phase_1_to_2_.deserialize_from(payload);
    result.phi_phase_2_to_3_.deserialize_from(payload);
    result.phi_phase_3_to_1_.deserialize_from(payload);
    result.phi_phase_1_.deserialize_from(payload);
    result.phi_phase_2_.deserialize_from(payload);
    result.phi_phase_3_.deserialize_from(payload);
    result.voltage_thd_phase_1_.deserialize_from(payload);
    result.voltage_thd_phase_2_.deserialize_from(payload);
    result.voltage_thd_phase_3_.deserialize_from(payload);
    result.current_thd_phase_1_.deserialize_from(payload);
    result.current_thd_phase_2_.deserialize_from(payload);
    result.current_thd_phase_3_.deserialize_from(payload);

    for (auto &v : result.voltage_hd_phase_1_)
    {
        v.deserialize_from(payload);
    }

    for (auto &v : result.voltage_hd_phase_2_)
    {
        v.deserialize_from(payload);
    }

    for (auto &v : result.voltage_hd_phase_3_)
    {
        v.deserialize_from(payload);
    }

    for (auto &v : result.current_hd_phase_1_)
    {
        v.deserialize_from(payload);
    }

    for (auto &v : result.current_hd_phase_2_)
    {
        v.deserialize_from(payload);
    }

    for (auto &v : result.current_hd_phase_3_)
    {
        v.deserialize_from(payload);
    }

    return result;
}

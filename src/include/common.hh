#pragma once

#include <hedley/hedley.h>

#include <cstdint>
#include <cstring>
#include <string_view>

#ifdef CONFIG_POWER_MONITOR_WIFI_SSID
constexpr std::string_view WIFI_SSID{ CONFIG_POWER_MONITOR_WIFI_SSID };
#else
constexpr std::string_view WIFI_SSID{ "" };
#endif

#ifdef CONFIG_POWER_MONITOR_WIFI_PASSWORD
constexpr std::string_view WIFI_PASSWORD{ CONFIG_POWER_MONITOR_WIFI_PASSWORD };
#else
constexpr std::string_view WIFI_PASSWORD{ "" };
#endif

#ifdef CONFIG_POWER_MONITOR_WIFI_MAXIMUM_RETRIES
constexpr std::uint8_t WIFI_MAXIMUM_RETRIES{ CONFIG_POWER_MONITOR_WIFI_MAXIMUM_RETRIES };
#else
constexpr std::uint8_t WIFI_MAXIMUM_RETRIES{ 5 };
#endif

#ifdef CONFIG_POWER_MONITOR_MQTT_BROKER_URL
constexpr std::string_view MQTT_BROKER_URL{ CONFIG_POWER_MONITOR_MQTT_BROKER_URL };
#else
constexpr std::string_view MQTT_BROKER_URL{
    "mqtt://f96c1ea9d3924042871342ee37420662.s1.eu.hivemq.cloud"
};
#endif

#ifdef CONFIG_POWER_MONITOR_MQTT_TLS_PORT
constexpr auto MQTT_TLS_PORT = std::uint32_t{ CONFIG_POWER_MONITOR_MQTT_TLS_PORT };
#else
constexpr auto MQTT_TLS_PORT = std::uint32_t{ 8883 };
#endif

#ifdef CONFIG_POWER_MONITOR_MQTT_USERNAME
constexpr std::string_view MQTT_USERNAME{ CONFIG_POWER_MONITOR_MQTT_USERNAME };
#else
constexpr std::string_view MQTT_USERNAME{ "mqttest" };
#endif

#ifdef CONFIG_POWER_MONITOR_MQTT_PASSWORD
constexpr std::string_view MQTT_PASSWORD{ CONFIG_POWER_MONITOR_MQTT_PASSWORD };
#else
constexpr std::string_view MQTT_PASSWORD{ "Zomfg1234" };
#endif

#ifdef CONFIG_POWER_MONITOR_SAMPLE_BUFFER_SIZE
constexpr auto SAMPLE_BUFFER_SIZE =
    static_cast<std::size_t>(CONFIG_POWER_MONITOR_SAMPLE_BUFFER_SIZE);
#else
constexpr std::size_t SAMPLE_BUFFER_SIZE{ 4096 };
#endif

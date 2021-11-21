#ifdef POWER_MONITOR_PLATFORM_XTENSA

#include "afe_reader.hh"
#include "common.hh"
#include "resources.h"

#include <elsen/arduino_compatibility.hh>
#include <elsen/logger.hh>
#include <elsen/mqtt_client.hh>
#include <elsen/wifi.hh>

#include <gsl/gsl>

#include <esp_event.h>
#include <esp_http_client.h>
#include <esp_task_wdt.h>
#include <esp_tls.h>
#include <esp_wifi.h>
#include <nvs_flash.h>

#include <string_view>

namespace
{
    constexpr auto PAYLOAD_TARGET_TOPIC =
        std::string_view{ "v1/GesIuWDVKLqsYYXG/devices/DEADBFEED0000000/0/bin" };

    constexpr auto DEFAULT_INTERVAL_MS = std::chrono::milliseconds{ 2 * 1000 }.count();

    constexpr auto BURST_MODE_TOPIC =
        std::string_view{ "v1/GesIuWDVKLqsYYXG/devices/DEADBFEED0000000/0/config" };
    constexpr auto BURST_MODE_INTERVAL_MS        = std::chrono::milliseconds{ 5 * 1000 }.count();
    constexpr auto BURST_MODE_MAX_ACTIVE_TIME_MS = std::chrono::milliseconds{ 20 * 1000 }.count();

    constexpr auto HTTP_POST_INTERVAL_MS = std::chrono::milliseconds{ 900 * 1000 }.count();

    inline void initialize_nvs()
    {
        auto ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
        {
            ESP_ERROR_CHECK(nvs_flash_erase());
            ret = nvs_flash_init();
        }
        ESP_ERROR_CHECK(ret);
    }

    inline void initialize_tcp_ip_stack()
    {
        ESP_ERROR_CHECK(esp_netif_init());
    }

    inline void create_main_event_loop()
    {
        ESP_ERROR_CHECK(esp_event_loop_create_default());
    }

    inline void initialize_wifi()
    {
        esp_netif_create_default_wifi_sta();
        const wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    }

    inline void send_cumulated_energy(float value)
    {
        esp_http_client_config_t config{};
        config.url                         = "https://apiroom.net/api/lucianovici/power_monitor";
        config.cert_pem                    = reinterpret_cast<const char *>(resource_ISRG_Root_X1);
        config.method                      = esp_http_client_method_t::HTTP_METHOD_POST;
        config.skip_cert_common_name_check = true;
        auto client                        = esp_http_client_init(&config);

        esp_http_client_set_header(client, "Accept", "application/json");
        esp_http_client_set_header(client, "Content-Type", "application/json");

        auto payload =
            fmt::format("{{ \"data\": {{ \"kwh\": {} }}, \"keys\": {{}} }}", value / 1'000.F);
        esp_http_client_set_post_field(client,
            payload.c_str(),
            static_cast<std::int32_t>(payload.size()));

        std::printf("Sending: %s\n", payload.c_str());

        ESP_ERROR_CHECK(esp_http_client_perform(client));

        ESP_ERROR_CHECK(esp_http_client_cleanup(client));
    }
} // namespace

int main(int argc, char *argv[])
{
    ELSEN_UNUSED(argc);
    ELSEN_UNUSED(argv);

    initialize_nvs();

    esp_err_t esp_ret = ESP_FAIL;
    esp_ret           = esp_tls_set_global_ca_store(resource_ISRG_Root_X1,
                  static_cast<std::uint32_t>(resource_ISRG_Root_X1_size));
    if (esp_ret != ESP_OK)
    {
        ELSEN_LOG_ERROR("Error in setting the global ca store: [{:x}] ({}),could not complete the "
                        "https_request using global_ca_store",
            esp_ret,
            esp_err_to_name(esp_ret));
        vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
        std::exit(EXIT_FAILURE);
    }

    initialize_tcp_ip_stack();
    create_main_event_loop();
    initialize_wifi();

    elsen::signal::platform_init_queued_signal_handler();

    static auto wifi        = elsen::WiFi{};
    static auto mqtt_client = elsen::MQTTClient{};

    static auto burst_mode_active{ false };
    static auto burst_mode_active_since = std::chrono::system_clock::now();
    static auto last_sent           = std::chrono::system_clock::now() - std::chrono::hours{ 1 };
    static auto last_http_post_sent = std::chrono::system_clock::now() - std::chrono::hours{ 1 };

    static auto afe_reader = new AfeReader{};
    afe_reader->readings_ready.connect(
        [](std::vector<std::uint8_t> &&readings_serialized) noexcept {
            if (mqtt_client.is_connected())
            {
                const auto time_since_last_sent_ms =
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now() - last_sent)
                        .count();

                if ((burst_mode_active && time_since_last_sent_ms >= BURST_MODE_INTERVAL_MS) ||
                    (time_since_last_sent_ms >= DEFAULT_INTERVAL_MS))
                {
                    readings_serialized.insert(readings_serialized.cbegin(), 0);
                    readings_serialized.insert(readings_serialized.cbegin(), 0);
                    mqtt_client.publish_message(PAYLOAD_TARGET_TOPIC,
                        readings_serialized.data(),
                        readings_serialized.size());

                    last_sent = std::chrono::system_clock::now();

                    const auto time_since_burst_mode_active =
                        std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now() - burst_mode_active_since)
                            .count();
                    if (time_since_burst_mode_active > BURST_MODE_MAX_ACTIVE_TIME_MS)
                    {
                        burst_mode_active = false;
                    }
                }

                const auto time_since_http_post =
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now() - last_http_post_sent)
                        .count();
                if (time_since_http_post >= HTTP_POST_INTERVAL_MS)
                {
                    send_cumulated_energy(afe_reader->cumulated_active_energy());
                    last_http_post_sent = std::chrono::system_clock::now();
                }
            }
            else
            {
                ELSEN_LOG_WARN("No MQTT connection available. Cannot send readings.");
            }
        },
        elsen::signal::ConnectionType::Queued);

    wifi.connected.connect([](std::uint32_t ip_address) {
        ELSEN_LOG_INFO("Connected to access point with SSID: \"{}\"", WIFI_SSID);

        const auto esp_ip_addr = esp_ip4_addr_t{ ip_address };
        ELSEN_LOG_INFO("Ip address: {}.{}.{}.{}", IP2STR(&esp_ip_addr));

        ELSEN_LOG_INFO("Connecting to MQTT broker...");
        mqtt_client.set_broker_url(MQTT_BROKER_URL, MQTT_TLS_PORT);
        mqtt_client.set_username(MQTT_USERNAME);
        mqtt_client.set_password(MQTT_PASSWORD);
        mqtt_client.connect();
    });

    mqtt_client.connected.connect(
        [](AfeReader *afe) {
            std::srand(static_cast<std::uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch())
                                                      .count()));

            ELSEN_LOG_INFO("MQTT: Connected to {}...", MQTT_BROKER_URL);
            afe->start_reading();
            mqtt_client.subscribe(BURST_MODE_TOPIC);
        },
        *afe_reader);

    mqtt_client.subscribed.connect([](elsen::MQTTClient::MessageID) noexcept {
        ELSEN_LOG_INFO("MQTT subscribed to topic");
    });

    mqtt_client.received.connect([](std::string_view topic, auto data) {
        ELSEN_UNUSED(data);
        if (topic == BURST_MODE_TOPIC)
        {
            ELSEN_LOG_INFO("Toggling burst mode {}...", (burst_mode_active ? "OFF" : "ON"));
            burst_mode_active_since = std::chrono::system_clock::now();
            burst_mode_active       = !burst_mode_active;
        }
    });

    wifi.connection_failed.connect([]() {
        ELSEN_LOG_ERROR("Failed to connect to Access Point \"{}\"", WIFI_SSID);
        vTaskDelay((5 * 1000) / portTICK_PERIOD_MS);
        std::exit(EXIT_FAILURE);
    });

    wifi.disconnected.connect([]() {
        ELSEN_LOG_INFO("WiFi disconnected. Trying to reconnect...");
        mqtt_client.disconnect();
        wifi.connect();
    });

    ELSEN_LOG_INFO("Connecting to WiFi access point...");
    wifi.set_ssid(WIFI_SSID);
    wifi.set_password(WIFI_PASSWORD);
    wifi.set_authentication(elsen::WiFi::AuthenticationMode::WPA2_PSK);
    wifi.connect();

    for (;;)
    {
        vTaskDelay(portMAX_DELAY);
    }
}

#endif

#include "wifi.hh"
#include "logger.hh"

#include <esp_event.h>
#include <esp_wifi.h>
#include <freertos/event_groups.h>

#include <cstring>

namespace
{
    constexpr auto WIFI_CONNECTED_BIT = std::uint32_t{ BIT0 };
    constexpr auto WIFI_FAIL_BIT = std::uint32_t{ BIT1 };

    struct WiFiHandles
    {
        wifi_config_t config;
        EventGroupHandle_t event_group;
        esp_event_handler_instance_t event_handler_wifi;
        esp_event_handler_instance_t event_handler_ip;

        ~WiFiHandles() noexcept
        {
            vEventGroupDelete(event_group);
            ESP_ERROR_CHECK(esp_event_handler_instance_unregister(WIFI_EVENT,
                ESP_EVENT_ANY_ID,
                event_handler_wifi));

            ESP_ERROR_CHECK(esp_event_handler_instance_unregister(IP_EVENT,
                ESP_EVENT_ANY_ID,
                event_handler_ip));
        }
    };

    struct WiFiEventCallbackData
    {
        elsen::WiFi &wifi_instance;
        bool &is_connected;
        std::uint8_t &ongoing_retry_count;
        WiFiHandles handles;
    };

    void event_handler(void *callback_data,
        esp_event_base_t event_base,
        std::int32_t event_id,
        void *event_data) noexcept
    {
        auto &cb_data = *static_cast<WiFiEventCallbackData *>(callback_data);
        auto &self = cb_data.wifi_instance;

        if (event_base == WIFI_EVENT)
        {
            if (event_id == WIFI_EVENT_STA_START)
            {
                esp_wifi_connect();
            }
            else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
            {
                if (cb_data.is_connected)
                {
                    cb_data.is_connected = false;
                    self.disconnected.emit();
                }
                else if (cb_data.ongoing_retry_count < 5)
                {
                    esp_wifi_connect();
                    ++(cb_data.ongoing_retry_count);
                    ELSEN_LOG_WARN("Connection failed, retrying for the {}th time",
                        cb_data.ongoing_retry_count);
                }
                else
                {
                    xEventGroupSetBits(cb_data.handles.event_group, WIFI_FAIL_BIT);
                    self.connection_failed.emit();
                }
            }
        }
        else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
        {
            const auto *event = static_cast<ip_event_got_ip_t *>(event_data);
            cb_data.ongoing_retry_count = 0;
            cb_data.is_connected = true;
            self.connected.emit(event->ip_info.ip.addr);
            xEventGroupSetBits(cb_data.handles.event_group, WIFI_CONNECTED_BIT);
        }
        else
        {
            ELSEN_LOG_WARN("Unhandled event");
        }
    }
} // namespace

using namespace elsen;

WiFi::WiFi() noexcept
  : platform_impl_{ new WiFiEventCallbackData{ *this,
        this->is_connected_,
        this->ongoing_retry_count_,
        { {}, xEventGroupCreate(), nullptr, nullptr } } }
{
    auto &wifi_event_cb_data = *static_cast<WiFiEventCallbackData *>(platform_impl_);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
        ESP_EVENT_ANY_ID,
        &event_handler,
        platform_impl_,
        &wifi_event_cb_data.handles.event_handler_wifi));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
        ESP_EVENT_ANY_ID,
        &event_handler,
        platform_impl_,
        &wifi_event_cb_data.handles.event_handler_ip));
}

WiFi::~WiFi() noexcept
{
    disconnect();

    delete static_cast<WiFiHandles *>(platform_impl_);
}

void WiFi::set_ssid(std::string_view ssid) noexcept
{
    auto &config = static_cast<WiFiEventCallbackData *>(platform_impl_)->handles.config;

    constexpr std::size_t MAX_SIZE = sizeof(wifi_config_t::sta.ssid);

    const std::size_t byte_count = ssid.size() >= MAX_SIZE ? MAX_SIZE : ssid.size();
    std::memcpy(config.sta.ssid, ssid.data(), byte_count);
}

void WiFi::set_password(std::string_view password) noexcept
{
    auto &config = static_cast<WiFiEventCallbackData *>(platform_impl_)->handles.config;

    constexpr std::size_t MAX_SIZE = sizeof(wifi_config_t ::sta.password);

    const std::size_t byte_count = password.size() >= MAX_SIZE ? MAX_SIZE : password.size();
    std::memcpy(config.sta.password, password.data(), byte_count);
}

void WiFi::set_authentication(AuthenticationMode mode) noexcept
{
    auto &config = static_cast<WiFiEventCallbackData *>(platform_impl_)->handles.config;

    static_assert(static_cast<int>(AuthenticationMode::Open) == WIFI_AUTH_OPEN);
    static_assert(static_cast<int>(AuthenticationMode::WEP) == WIFI_AUTH_WEP);
    static_assert(static_cast<int>(AuthenticationMode::WPA2_PSK) == WIFI_AUTH_WPA2_PSK);
    static_assert(static_cast<int>(AuthenticationMode::WPA_WPA2_PSK) == WIFI_AUTH_WPA_WPA2_PSK);
    static_assert(static_cast<int>(AuthenticationMode::WPA3_PSK) == WIFI_AUTH_WPA3_PSK);
    static_assert(static_cast<int>(AuthenticationMode::WPA2_WPA3_PSK) == WIFI_AUTH_WPA2_WPA3_PSK);

    config.sta.threshold.authmode =
        static_cast<decltype(wifi_config_t ::sta.threshold.authmode)>(mode);
}

void WiFi::connect() noexcept
{
    auto &handles = static_cast<WiFiEventCallbackData *>(platform_impl_)->handles;

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &handles.config));
    ESP_ERROR_CHECK(esp_wifi_start());

    /* Following call blocks until one of the BITs is set */
    [[maybe_unused]] EventBits_t bits = xEventGroupWaitBits(handles.event_group,
        WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
        pdFALSE,
        pdFALSE,
        portMAX_DELAY);
}

void WiFi::disconnect() noexcept
{
    if (is_connected_)
    {
        ongoing_retry_count_ = 0;
        ESP_ERROR_CHECK(esp_wifi_disconnect());
    }
}

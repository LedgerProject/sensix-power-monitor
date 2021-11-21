#pragma once

#include <elsen/global.hh>
#include <elsen/signal.hh>

#include <cstdint>
#include <string_view>

namespace elsen
{
    ELSEN_API struct WiFi
    {
        enum struct AuthenticationMode
        {
            Open = 0,
            WEP = 1,
            WPA2_PSK = 3,
            WPA_WPA2_PSK = 4,
            WPA3_PSK = 6,
            WPA2_WPA3_PSK = 7,
        };

        WiFi() noexcept;
        ~WiFi() noexcept;

        void set_ssid(std::string_view ssid) noexcept;
        void set_password(std::string_view password) noexcept;
        void set_authentication(AuthenticationMode mode) noexcept;

        void connect() noexcept;
        void disconnect() noexcept;

        inline bool is_connected() const noexcept
        {
            return is_connected_;
        }

    signals:
        Signal<std::uint32_t /* ip_address */> connected{};
        Signal<> disconnected{};
        Signal<> connection_failed{};

    private:
        std::uint8_t ongoing_retry_count_{ 0 };
        bool is_connected_{ false };

    private:
        void *platform_impl_{};

    private:
        ELSEN_DISABLE_COPY(WiFi);
        ELSEN_DISABLE_MOVE(WiFi);
    };
} // namespace elsen
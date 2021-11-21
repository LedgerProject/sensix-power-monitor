#pragma once

#include <elsen/global.hh>
#include <elsen/signal.hh>

#include <gsl/gsl>

#include <string>
#include <string_view>

namespace elsen
{
    ELSEN_API class MQTTClient
    {
    public:
        using MessageID = std::int32_t;

        enum struct Error
        {
            TCPTransportError = 0,
            BadProtocol,
            IDRejected,
            ServerUnavailable,
            BadUsername,
            NotAuthorized,
            Unknown = 255
        };

    public:
        MQTTClient() noexcept;
        ~MQTTClient() noexcept;

    public:
        void set_broker_url(std::string_view url, std::uint32_t port) noexcept;
        void set_username(std::string_view username) noexcept;
        void set_password(std::string_view password) noexcept;

        void connect() noexcept;
        void disconnect() noexcept;
        inline bool is_connected() noexcept
        {
            return is_connected_;
        }

        void subscribe(std::string_view topic) noexcept;

        MessageID publish_message(std::string_view topic,
            const std::uint8_t *message,
            std::size_t length) noexcept;
        MessageID enqueue_message(std::string_view topic,
            const std::uint8_t *message,
            std::size_t length) noexcept;

    signals:
        Signal<> connected{};
        Signal<MessageID> subscribed{};
        Signal<MessageID> unsubscribed{};
        Signal<MessageID> published{};
        Signal<std::string_view, gsl::span<std::uint8_t>> received{};
        Signal<Error> error{};
        Signal<> disconnected{};

    private:
        std::string url_{};
        std::string username_{};
        std::string password_{};
        std::uint32_t port_{};

        bool is_connected_{ false };

    private:
        void *native_handle_{};
        void *platform_impl_{};

    private:
        ELSEN_DISABLE_COPY(MQTTClient);
        ELSEN_DISABLE_MOVE(MQTTClient);
    };
} // namespace elsen
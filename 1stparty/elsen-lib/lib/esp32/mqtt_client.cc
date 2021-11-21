#include "mqtt_client.hh"
#include "global.hh"
#include "logger.hh"

#include <esp_tls.h>
#include <mqtt_client.h>

#include <array>
#include <type_traits>

namespace
{
    template<typename T> constexpr esp_mqtt_client_handle_t esp_handle(T *var) noexcept
    {
        static_assert(std::is_same_v<T, void>);
        return static_cast<esp_mqtt_client_handle_t>(var);
    }

    struct MQTTEventCallbackData
    {
        elsen::MQTTClient &mqtt_client_instance;
        bool &is_connected;
    };

    void event_handler(void *callback_data,
        const char *base,
        std::int32_t event_id,
        void *event_data) noexcept
    {
        ELSEN_UNUSED(base);

        using namespace elsen;

        ELSEN_LOG_INFO("MQTT event: {}", event_id);

        auto &mqtt_event_callback_data = *static_cast<MQTTEventCallbackData *>(callback_data);
        auto &self = mqtt_event_callback_data.mqtt_client_instance;

        esp_mqtt_event_handle_t event = static_cast<esp_mqtt_event_handle_t>(event_data);
        switch (static_cast<esp_mqtt_event_id_t>(event_id))
        {
        case MQTT_EVENT_CONNECTED:
            mqtt_event_callback_data.is_connected = true;
            self.connected.emit();
            break;
        case MQTT_EVENT_DISCONNECTED:
            mqtt_event_callback_data.is_connected = false;
            self.disconnected.emit();
            break;
        case MQTT_EVENT_SUBSCRIBED: {
            self.subscribed.emit(event->msg_id);

            break;
        }
        case MQTT_EVENT_UNSUBSCRIBED: {
            self.unsubscribed.emit(event->msg_id);

            break;
        }
        case MQTT_EVENT_PUBLISHED:
            self.published.emit(event->msg_id);
            break;
        case MQTT_EVENT_DATA: {
            const auto event_topic_length = static_cast<std::size_t>(event->topic_len);
            self.received.emit(std::string_view{ event->topic, event_topic_length },
                gsl::span{ reinterpret_cast<std::uint8_t *>(event->data),
                    static_cast<std::size_t>(event->data_len) });

            break;
        }
        case MQTT_EVENT_ERROR: {
            using Error = elsen::MQTTClient::Error;

            static_assert(static_cast<int>(Error::BadProtocol) == MQTT_CONNECTION_REFUSE_PROTOCOL);
            static_assert(
                static_cast<int>(Error::IDRejected) == MQTT_CONNECTION_REFUSE_ID_REJECTED);
            static_assert(static_cast<int>(Error::ServerUnavailable) ==
                          MQTT_CONNECTION_REFUSE_SERVER_UNAVAILABLE);
            static_assert(
                static_cast<int>(Error::BadUsername) == MQTT_CONNECTION_REFUSE_BAD_USERNAME);
            static_assert(
                static_cast<int>(Error::NotAuthorized) == MQTT_CONNECTION_REFUSE_NOT_AUTHORIZED);

            if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT)
            {
                self.error.emit(Error::TCPTransportError);
            }
            else if (event->error_handle->error_type == MQTT_ERROR_TYPE_CONNECTION_REFUSED)
            {
                self.error.emit(static_cast<Error>(event->error_handle->connect_return_code));
            }
            else
            {
                self.error.emit(Error::Unknown);
            }

            break;
        }
        default:
            break;
        }
    }
} // namespace

using namespace elsen;

MQTTClient::MQTTClient() noexcept
  : platform_impl_{ new MQTTEventCallbackData{ *this, this->is_connected_ } }
{}

MQTTClient::~MQTTClient() noexcept
{
    disconnect();
    delete static_cast<MQTTEventCallbackData *>(platform_impl_);
}

void MQTTClient::connect() noexcept
{
    auto mqtt_config = esp_mqtt_client_config_t{};
    mqtt_config.uri = url_.c_str();
    mqtt_config.username = username_.c_str();
    mqtt_config.password = password_.c_str();
    mqtt_config.port = port_;
    mqtt_config.use_global_ca_store = true;

    native_handle_ = esp_mqtt_client_init(&mqtt_config);
    esp_mqtt_client_register_event(esp_handle(native_handle_),
        static_cast<esp_mqtt_event_id_t>(ESP_EVENT_ANY_ID),
        &event_handler,
        platform_impl_);
    esp_mqtt_client_start(esp_handle(native_handle_));
}

void MQTTClient::disconnect() noexcept
{
    esp_mqtt_client_disconnect(esp_handle(native_handle_));
    esp_mqtt_client_destroy(esp_handle(native_handle_));
}

void MQTTClient::subscribe(std::string_view topic) noexcept
{
    esp_mqtt_client_subscribe(esp_handle(native_handle_), topic.data(), 0);
}

MQTTClient::MessageID MQTTClient::publish_message(std::string_view topic,
    const std::uint8_t *message,
    std::size_t length) noexcept
{
    return esp_mqtt_client_publish(esp_handle(native_handle_),
        topic.data(),
        reinterpret_cast<const char *>(message),
        static_cast<int>(length),
        0,
        0);
}

MQTTClient::MessageID MQTTClient::enqueue_message(std::string_view topic,
    const std::uint8_t *message,
    std::size_t length) noexcept
{
    return esp_mqtt_client_enqueue(esp_handle(native_handle_),
        topic.data(),
        reinterpret_cast<const char *>(message),
        static_cast<int>(length),
        0,
        0,
        true);
}

void MQTTClient::set_broker_url(std::string_view url, std::uint32_t port) noexcept
{
    url_.clear();
    url_.append(url);
    port_ = port;
}

void MQTTClient::set_username(std::string_view username) noexcept
{
    username_.clear();
    username_.append(username);
}

void MQTTClient::set_password(std::string_view password) noexcept
{
    password_.clear();
    password_.append(password);
}

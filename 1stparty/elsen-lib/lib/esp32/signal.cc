#include "signal.hh"
#include "logger.hh"

#include <esp_event.h>
#include <freertos/event_groups.h>

esp_event_base_t ELSEN_SIGNAL_EVENT_BASE{};

namespace
{
    void queued_signal_handler(void *, esp_event_base_t, std::int32_t, void *event_data) noexcept
    {
        auto *cb = *static_cast<std::function<void()> **>(event_data);

        ELSEN_LOG_DEBUG("Sending signal via callback {}...", static_cast<void *>(cb));
        (*cb)();

        delete cb;
    }
} // namespace

using namespace elsen;

void signal::platform_init_queued_signal_handler() noexcept
{
    ELSEN_SIGNAL_EVENT_BASE = "ELSEN_SIGNAL_EVENT_BASE";

    ESP_ERROR_CHECK(esp_event_handler_instance_register(ELSEN_SIGNAL_EVENT_BASE,
        0,
        &queued_signal_handler,
        nullptr,
        nullptr));
}

void signal::detail::platform_post_signal_event(std::function<void()> *callback) noexcept
{
    ELSEN_LOG_DEBUG("Posting message with callback {}...", static_cast<void *>(callback));
    const auto result = esp_event_post(ELSEN_SIGNAL_EVENT_BASE, 0, &callback, sizeof(callback), 1);
    if (result != ESP_OK)
    {
        ELSEN_LOG_ERROR("Failed to emit queued signal; ESP32 error: {}", esp_err_to_name(result));
        delete callback;
    }
}

#include "arduino/utilities.hh"

#include <FreeRTOS.h>
#include <driver/gpio.h>
#include <freertos/task.h>

void elsen::arduino::digitalWrite(std::uint8_t pin, PinState value) noexcept
{
    const auto result = gpio_set_level(static_cast<gpio_num_t>(pin), value);
    ESP_ERROR_CHECK(result);
}

void elsen::arduino::pinMode(std::uint8_t pin, PinMode mode) noexcept
{
    static_assert(static_cast<std::int32_t>(INPUT) == static_cast<std::int32_t>(GPIO_MODE_INPUT));
    static_assert(static_cast<std::int32_t>(OUTPUT) == static_cast<std::int32_t>(GPIO_MODE_OUTPUT));

    gpio_config_t io_conf{};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = static_cast<gpio_mode_t>(mode);
    io_conf.pin_bit_mask = (1ULL << pin);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;

    const auto result = gpio_config(&io_conf);
    ESP_ERROR_CHECK(result);
}

void elsen::arduino::delay(std::uint32_t milliseconds) noexcept
{
    vTaskDelay(milliseconds / portTICK_PERIOD_MS);
}

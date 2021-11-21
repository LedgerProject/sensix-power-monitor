#pragma once

#include <elsen/global.hh>

#include <cstdint>

namespace elsen::arduino
{
    ELSEN_API enum PinState {
        HIGH = 1,
        LOW = 0,
    };

    ELSEN_API enum PinMode {
        INPUT = 0x00000001,
        OUTPUT = 0x00000002,
    };

    ELSEN_API void digitalWrite(std::uint8_t pin, PinState value) noexcept;
    ELSEN_API void pinMode(std::uint8_t pin, PinMode value) noexcept;
    ELSEN_API void delay(std::uint32_t milliseconds) noexcept;
} // namespace elsen::arduino
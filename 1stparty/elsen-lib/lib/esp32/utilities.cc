#include "utilities.hh"

#include <esp_timer.h>

namespace elsen::utilities::timing
{
    void delay_microseconds(std::uint32_t value) noexcept
    {
        const auto m = static_cast<std::uint64_t>(esp_timer_get_time());
        if (value)
        {
            const auto e = uint64_t{ m + value };
            if (m > e)
            {
                while (static_cast<std::uint64_t>(esp_timer_get_time()) > e)
                {
                    __asm volatile("nop");
                }
            }
            while (static_cast<std::uint64_t>(esp_timer_get_time()) < e)
            {
                __asm volatile("nop");
            }
        }
    }
} // namespace elsen::utilities::timing
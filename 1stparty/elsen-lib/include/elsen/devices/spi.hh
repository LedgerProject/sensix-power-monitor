#pragma once

#include <elsen/arduino/spi.hh>
#include <elsen/global.hh>

#include <gsl/gsl>

#include <array>
#include <cassert>
#include <type_traits>
#include <utility>
#include <vector>

namespace elsen::devices
{
    ELSEN_API class Spi
    {
    public:
        using ByteOrder = arduino::ByteOrder;
        using DataMode = arduino::DataMode;

    public:
        struct Device
        {
        public:
            constexpr Device(std::uint32_t speed, DataMode data_mode) noexcept
              : speed_{ speed }
              , data_mode_{ data_mode }
              , platform_handle_{ nullptr }
            {}

            std::array<std::uint8_t, 4> transfer(std::array<std::uint8_t, 4> tx_data,
                std::size_t actual_size = 4) const;
            std::vector<std::uint8_t> transfer(gsl::span<std::uint8_t> tx_data) const;
            void transfer_to(gsl::span<std::uint8_t> tx_data,
                gsl::span<std::uint8_t> rx_data) const;

        private:
            std::uint32_t speed_;
            DataMode data_mode_;
            void *platform_handle_;

            friend class Spi;
        };

    public:
        Spi(std::uint8_t device_id);
        ~Spi();

    public:
        std::size_t register_device(Device &&device);
        Device &device(std::size_t id);

    private:
        void *spi_device_handle_{ nullptr };
        std::uint8_t device_id_{ 255 };
        std::vector<Device> registered_devices_{};

    private:
        ELSEN_DISABLE_COPY(Spi);
        ELSEN_DISABLE_MOVE(Spi);
    };
} // namespace elsen::devices

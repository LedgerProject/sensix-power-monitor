#pragma once

#include <elsen/global.hh>

#include <cstdint>

namespace elsen::arduino
{
    ELSEN_API enum ByteOrder { MSBFIRST, LSBFIRST };

    ELSEN_API enum DataMode { SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3 };

    ELSEN_API struct ArduinoSPI
    {
        static_assert(ACOMP_SPI_HOST_ID >= 1);

        struct Settings
        {
            constexpr Settings(std::uint32_t s, ByteOrder b, DataMode d) noexcept
              : speed{ s }
              , byte_order{ b }
              , data_mode{ d }
            {}

            std::uint32_t speed;
            ByteOrder byte_order;
            DataMode data_mode;
        };

        constexpr ArduinoSPI(std::uint8_t spi_device_id = ACOMP_SPI_HOST_ID) noexcept
          : spi_device_id_{ static_cast<uint8_t>(spi_device_id - 1) }
        {}

        void begin() noexcept;
        void end() noexcept;

        void beginTransaction(Settings settings) noexcept;
        void endTransaction() noexcept;

        std::uint8_t transfer8(std::uint8_t data) noexcept;
        std::uint16_t transfer16(std::uint16_t data) noexcept;
        std::uint32_t transfer32(std::uint32_t data) noexcept;

    private:
        static void serialize_16_msb(std::uint16_t data, std::uint8_t *buffer) noexcept;
        static void serialize_16_lsb(std::uint16_t data, std::uint8_t *buffer) noexcept;
        static std::uint16_t deserialize_16_msb(std::uint8_t *buffer) noexcept;
        static std::uint16_t deserialize_16_lsb(std::uint8_t *buffer) noexcept;

        static void serialize_32_msb(std::uint32_t data, std::uint8_t *buffer) noexcept;
        static void serialize_32_lsb(std::uint32_t data, std::uint8_t *buffer) noexcept;
        static std::uint32_t deserialize_32_msb(std::uint8_t *buffer) noexcept;
        static std::uint32_t deserialize_32_lsb(std::uint8_t *buffer) noexcept;

    private:
        using SerializationFunction16 = void (*)(std::uint16_t, std::uint8_t *) noexcept;
        using DeserializationFunction16 = std::uint16_t (*)(std::uint8_t *) noexcept;

        using SerializationFunction32 = void (*)(std::uint32_t, std::uint8_t *) noexcept;
        using DeserializationFunction32 = std::uint32_t (*)(std::uint8_t *) noexcept;

        SerializationFunction16 serialize_16_{ nullptr };
        DeserializationFunction16 deserialize_16_{ nullptr };

        SerializationFunction32 serialize_32_{ nullptr };
        DeserializationFunction32 deserialize_32_{ nullptr };

    private:
        void *spi_device_handle_{ nullptr };
        std::uint8_t spi_device_id_{};
    };

    using SPISettings = ArduinoSPI::Settings;
} // namespace elsen::arduino

extern elsen::arduino::ArduinoSPI SPI;

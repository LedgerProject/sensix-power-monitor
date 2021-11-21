#include "arduino/spi.hh"
#include "logger.hh"

#include <FreeRTOS.h>
#include <driver/spi_master.h>

#include <cstring>

using namespace elsen::arduino;

ArduinoSPI SPI{};

void ArduinoSPI::begin() noexcept
{
    [[maybe_unused]] static const int init_spi_bus = [this] {
        spi_bus_config_t buscfg{};

        if (spi_device_id_ < 1 || spi_device_id_ > 2)
        {
            ELSEN_LOG_ERROR("Only SPI devices 2 and 3 can be used for general purpose I/O; tried "
                            "to use device id {}",
                spi_device_id_);
            abort();
        }

        if (spi_device_id_ == static_cast<std::uint8_t>(SPI2_HOST))
        {
            buscfg.miso_io_num = 12;
            buscfg.mosi_io_num = 13;
            buscfg.sclk_io_num = 14;
        }
        else
        {
            buscfg.miso_io_num = 19;
            buscfg.mosi_io_num = 23;
            buscfg.sclk_io_num = 18;
        }

        buscfg.quadwp_io_num = -1;
        buscfg.quadhd_io_num = -1;
        auto result = spi_bus_initialize(static_cast<spi_host_device_t>(spi_device_id_),
            &buscfg,
            SPI_DMA_DISABLED);
        ESP_ERROR_CHECK(result);

        return 0;
    }();
}

void ArduinoSPI::end() noexcept
{}

void ArduinoSPI::beginTransaction(Settings settings) noexcept
{
    auto device_config = spi_device_interface_config_t{};
    device_config.mode = settings.data_mode;
    device_config.spics_io_num = -1;
    device_config.queue_size = 1;
    device_config.clock_speed_hz = static_cast<std::int32_t>(settings.speed);

    spi_device_handle_t spi_device_handle;
    auto result = spi_bus_add_device(static_cast<spi_host_device_t>(spi_device_id_),
        &device_config,
        &spi_device_handle);
    ESP_ERROR_CHECK(result);

    spi_device_handle_ = spi_device_handle;

    if (settings.byte_order == MSBFIRST)
    {
        serialize_16_ = ArduinoSPI::serialize_16_msb;
        deserialize_16_ = ArduinoSPI::deserialize_16_msb;

        serialize_32_ = ArduinoSPI::serialize_32_msb;
        deserialize_32_ = ArduinoSPI::deserialize_32_msb;
    }
    else
    {
        serialize_16_ = ArduinoSPI::serialize_16_lsb;
        deserialize_16_ = ArduinoSPI::deserialize_16_lsb;

        serialize_32_ = ArduinoSPI::serialize_32_lsb;
        deserialize_32_ = ArduinoSPI::deserialize_32_lsb;
    }
}

void ArduinoSPI::endTransaction() noexcept
{
    spi_bus_remove_device(static_cast<spi_device_handle_t>(spi_device_handle_));
    spi_device_handle_ = nullptr;

    serialize_16_ = nullptr;
    deserialize_16_ = nullptr;

    serialize_32_ = nullptr;
    deserialize_32_ = nullptr;
}

std::uint8_t ArduinoSPI::transfer8(std::uint8_t data) noexcept
{
    spi_transaction_t transaction;
    std::memset(&transaction, 0, sizeof(spi_transaction_t));
    transaction.length = 8;
    transaction.flags = SPI_TRANS_USE_RXDATA | SPI_TRANS_USE_TXDATA;

    transaction.tx_data[0] = data;

    esp_err_t ret =
        spi_device_polling_transmit(static_cast<spi_device_handle_t>(spi_device_handle_),
            &transaction);
    assert(ret == ESP_OK);

    auto response = std::uint8_t{};
    if (transaction.rxlength > 0)
    {
        response = transaction.rx_data[0];
    }

    return response;
}

std::uint16_t ArduinoSPI::transfer16(std::uint16_t data) noexcept
{
    spi_transaction_t transaction;
    std::memset(&transaction, 0, sizeof(spi_transaction_t));
    transaction.length = 16;
    transaction.flags = SPI_TRANS_USE_RXDATA | SPI_TRANS_USE_TXDATA;

    serialize_16_(data, transaction.tx_data);

    esp_err_t ret =
        spi_device_polling_transmit(static_cast<spi_device_handle_t>(spi_device_handle_),
            &transaction);
    assert(ret == ESP_OK);

    auto response = std::uint16_t{};
    if (transaction.rxlength > 0)
    {
        response = deserialize_16_(transaction.rx_data);
    }

    return response;
}

std::uint32_t ArduinoSPI::transfer32(std::uint32_t data) noexcept
{
    spi_transaction_t transaction;
    std::memset(&transaction, 0, sizeof(spi_transaction_t));
    transaction.length = 32;
    transaction.flags = SPI_TRANS_USE_RXDATA | SPI_TRANS_USE_TXDATA;

    serialize_32_(data, transaction.tx_data);

    esp_err_t ret =
        spi_device_polling_transmit(static_cast<spi_device_handle_t>(spi_device_handle_),
            &transaction);
    assert(ret == ESP_OK);

    auto response = std::uint32_t{};
    if (transaction.rxlength > 0)
    {
        response = deserialize_32_(transaction.rx_data);
    }

    return response;
}

void ArduinoSPI::serialize_16_msb(std::uint16_t data, std::uint8_t *buffer) noexcept
{
    buffer[0] = static_cast<std::uint8_t>((data >> 8) & 0xff);
    buffer[1] = static_cast<std::uint8_t>(data & 0xff);
}

void ArduinoSPI::serialize_16_lsb(std::uint16_t data, std::uint8_t *buffer) noexcept
{
    buffer[0] = static_cast<std::uint8_t>(data & 0xff);
    buffer[1] = static_cast<std::uint8_t>((data >> 8) & 0xff);
}

std::uint16_t ArduinoSPI::deserialize_16_msb(std::uint8_t *buffer) noexcept
{
    auto result = std::uint16_t{};
    result = std::uint16_t(buffer[0] << 8);
    result = std::uint16_t(result | buffer[1]);

    return result;
}

std::uint16_t ArduinoSPI::deserialize_16_lsb(std::uint8_t *buffer) noexcept
{
    auto result = std::uint16_t{};
    result = std::uint16_t(buffer[1] << 8);
    result = std::uint16_t(result | buffer[0]);

    return result;
}

void ArduinoSPI::serialize_32_msb(std::uint32_t data, std::uint8_t *buffer) noexcept
{
    buffer[0] = static_cast<std::uint8_t>((data >> 24) & 0xff);
    buffer[1] = static_cast<std::uint8_t>((data >> 16) & 0xff);
    buffer[2] = static_cast<std::uint8_t>((data >> 8) & 0xff);
    buffer[3] = static_cast<std::uint8_t>(data & 0xff);
}

void ArduinoSPI::serialize_32_lsb(std::uint32_t data, std::uint8_t *buffer) noexcept
{
    buffer[0] = static_cast<std::uint8_t>(data & 0xff);
    buffer[1] = static_cast<std::uint8_t>((data >> 8) & 0xff);
    buffer[2] = static_cast<std::uint8_t>((data >> 16) & 0xff);
    buffer[3] = static_cast<std::uint8_t>((data >> 24) & 0xff);
}

std::uint32_t ArduinoSPI::deserialize_32_msb(std::uint8_t *buffer) noexcept
{
    auto result = std::uint32_t{};
    result = std::uint32_t(buffer[0] << 24);
    result = (result | std::uint32_t(buffer[1]) << 16);
    result = (result | std::uint32_t(buffer[2]) << 8);
    result = (result | buffer[3]);

    return result;
}

std::uint32_t ArduinoSPI::deserialize_32_lsb(std::uint8_t *buffer) noexcept
{
    auto result = std::uint32_t{};
    result = std::uint32_t(buffer[3] << 24);
    result = (result | std::uint32_t(buffer[2]) << 16);
    result = (result | std::uint32_t(buffer[1]) << 8);
    result = (result | buffer[0]);

    return result;
}

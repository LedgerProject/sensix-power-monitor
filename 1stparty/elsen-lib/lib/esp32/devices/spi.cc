#include "devices/spi.hh"

#include "logger.hh"

#include <FreeRTOS.h>
#include <driver/spi_master.h>

using namespace elsen::devices;

std::array<std::uint8_t, 4> Spi::Device::transfer(std::array<std::uint8_t, 4> tx_data,
    std::size_t actual_size) const
{
    spi_transaction_t transaction;
    std::memset(&transaction, 0, sizeof(spi_transaction_t));
    transaction.length = actual_size;
    transaction.flags = SPI_TRANS_USE_RXDATA | SPI_TRANS_USE_TXDATA;

    std::memcpy(transaction.tx_data, tx_data.data(), tx_data.size());

    const auto ret = spi_device_polling_transmit(static_cast<spi_device_handle_t>(platform_handle_),
        &transaction);
    ESP_ERROR_CHECK(ret);

    auto response = std::array<std::uint8_t, 4>{};
    if (transaction.rxlength > 0)
    {
        std::memcpy(response.data(), transaction.rx_data, response.size());
    }

    return response;
}

std::vector<std::uint8_t> Spi::Device::transfer(gsl::span<std::uint8_t> tx_data) const
{
    spi_transaction_t transaction;
    std::memset(&transaction, 0, sizeof(spi_transaction_t));
    transaction.length = tx_data.size();
    transaction.tx_buffer = tx_data.data();

    auto response = std::vector<std::uint8_t>{};
    // rx_buffer in transaction needs to be 4 byte aligned
    if (tx_data.size() % 4 == 0)
    {
        response.resize(tx_data.size());
    }
    else
    {
        response.resize(((tx_data.size() / 4) + 1) * 4);
    }
    transaction.rx_buffer = response.data();

    const auto ret = spi_device_polling_transmit(static_cast<spi_device_handle_t>(platform_handle_),
        &transaction);
    ESP_ERROR_CHECK(ret);

    response.resize(transaction.rxlength);
    return response;
}

void Spi::Device::transfer_to(gsl::span<std::uint8_t> tx_data,
    gsl::span<std::uint8_t> rx_data) const
{
    spi_transaction_t transaction;
    std::memset(&transaction, 0, sizeof(spi_transaction_t));
    transaction.length = tx_data.size();
    transaction.tx_buffer = tx_data.data();

    // rx_buffer in transaction needs to be 4 byte aligned
    if (rx_data.size() % 4 != 0)
    {
        return;
    }
    transaction.rx_buffer = rx_data.data();

    const auto ret = spi_device_polling_transmit(static_cast<spi_device_handle_t>(platform_handle_),
        &transaction);
    ESP_ERROR_CHECK(ret);
}

Spi::Spi(std::uint8_t device_id)
  : device_id_{ device_id }
{
    spi_bus_config_t buscfg{};

    if (device_id < 1 || device_id > 2)
    {
        ELSEN_LOG_ERROR("Only SPI devices 2 and 3 can be used for general purpose I/O; tried "
                        "to use device id {}",
            device_id);
        abort();
    }

    if (device_id == static_cast<std::uint8_t>(SPI2_HOST))
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
    auto result =
        spi_bus_initialize(static_cast<spi_host_device_t>(device_id), &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(result);
}

Spi::~Spi()
{
    for (auto &d : registered_devices_)
    {
        spi_bus_remove_device(static_cast<spi_device_t *>(d.platform_handle_));
    }
    ESP_ERROR_CHECK(spi_bus_free(static_cast<spi_host_device_t>(device_id_)));
}

std::size_t Spi::register_device(Device &&device)
{
    auto device_config = spi_device_interface_config_t{};
    device_config.mode = device.data_mode_;
    device_config.spics_io_num = -1;
    device_config.queue_size = 1;
    device_config.clock_speed_hz = static_cast<std::int32_t>(device.speed_);

    spi_device_handle_t spi_device_handle;
    auto result = spi_bus_add_device(static_cast<spi_host_device_t>(device_id_),
        &device_config,
        &spi_device_handle);
    ESP_ERROR_CHECK(result);

    device.platform_handle_ = spi_device_handle;
    registered_devices_.push_back(std::move(device));

    return registered_devices_.size() - 1;
}

Spi::Device &Spi::device(std::size_t id)
{
    return registered_devices_[id];
}

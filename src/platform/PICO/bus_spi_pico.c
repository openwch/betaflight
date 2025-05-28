/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 *
 * Betaflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "platform.h"

#ifdef USE_SPI

#include "common/maths.h"
#include "drivers/bus.h"
#include "drivers/bus_spi.h"
#include "drivers/bus_spi_impl.h"
#include "drivers/exti.h"
#include "drivers/io.h"

#include "hardware/spi.h"
#include "hardware/gpio.h"


#define SPI_SPEED_20MHZ 20000000
#define SPI_DATAWIDTH 8
#define SPI_DMA_THRESHOLD 8

const spiHardware_t spiHardware[] = {
    {
        .device = SPIDEV_0,
        .reg = SPI0,
        .sckPins = {
            { DEFIO_TAG_E(PA2) },
            { DEFIO_TAG_E(PA6) },
            { DEFIO_TAG_E(PA18) },
            { DEFIO_TAG_E(PA22) },
#ifdef RP2350B
            { DEFIO_TAG_E(PA34) },
            { DEFIO_TAG_E(PA38) },
#endif
        },
        .misoPins = {
            { DEFIO_TAG_E(PA0) },
            { DEFIO_TAG_E(PA4) },
            { DEFIO_TAG_E(PA16) },
            { DEFIO_TAG_E(PA20) },
#ifdef RP2350B
            { DEFIO_TAG_E(PA32) },
            { DEFIO_TAG_E(PA36) },
#endif
        },
        .mosiPins = {
            { DEFIO_TAG_E(PA3) },
            { DEFIO_TAG_E(PA7) },
            { DEFIO_TAG_E(PA19) },
            { DEFIO_TAG_E(PA23) },
#ifdef RP2350B
            { DEFIO_TAG_E(PA35) },
            { DEFIO_TAG_E(PA39) },
#endif
        },
    },
    {
        .device = SPIDEV_1,
        .reg = SPI1,
        .sckPins = {
            { DEFIO_TAG_E(PA10) },
            { DEFIO_TAG_E(PA14) },
            { DEFIO_TAG_E(PA26) },
#ifdef RP2350B
            { DEFIO_TAG_E(PA30) },
            { DEFIO_TAG_E(PA42) },
            { DEFIO_TAG_E(PA46) },
#endif
        },
        .misoPins = {
            { DEFIO_TAG_E(PA8) },
            { DEFIO_TAG_E(PA12) },
            { DEFIO_TAG_E(PA24) },
            { DEFIO_TAG_E(PA28) },
#ifdef RP2350B
            { DEFIO_TAG_E(PA40) },
            { DEFIO_TAG_E(PA44) },
#endif
        },
        .mosiPins = {
            { DEFIO_TAG_E(PA11) },
            { DEFIO_TAG_E(PA15) },
            { DEFIO_TAG_E(PA27) },
#ifdef RP2350B
            { DEFIO_TAG_E(PA31) },
            { DEFIO_TAG_E(PA43) },
            { DEFIO_TAG_E(PA47) },
#endif
        },
    },
};

void spiPinConfigure(const struct spiPinConfig_s *pConfig)
{
    UNUSED(instance);
    divisor = constrain(divisor, 2, 256);
    return 0;
}

static void spiSetDivisorBRreg(spi_inst_t *instance, uint16_t divisor)
{
    //TODO: implement
    UNUSED(instance);
    UNUSED(divisor);
}

void spiInitDevice(SPIDevice device)
{
  // maybe here set getSpiInstanceByDevice(spi->dev) SPI device with
  // settings like
  // STM does
  //SetRXFIFOThreshold ...QF (1/4 full presumably)
  //         Init -> full duplex, master, 8biut, baudrate, MSBfirst, no CRC,
  //                  Clock = PolarityHigh, Phase_2Edge

  
    const spiDevice_t *spi = &spiDevice[device];

    if (!spi->dev) {
        return;
    }

    // Set owners
    IOInit(IOGetByTag(spi->sck),  OWNER_SPI_SCK,  RESOURCE_INDEX(device));
    IOInit(IOGetByTag(spi->miso), OWNER_SPI_SDI, RESOURCE_INDEX(device));
    IOInit(IOGetByTag(spi->mosi), OWNER_SPI_SDO, RESOURCE_INDEX(device));

    spi_init(SPI_INST(spi->dev), SPI_SPEED_20MHZ);

    gpio_set_function(IO_PINBYTAG(spi->miso), GPIO_FUNC_SPI);
    gpio_set_function(IO_PINBYTAG(spi->mosi), GPIO_FUNC_SPI);
    gpio_set_function(IO_PINBYTAG(spi->sck), GPIO_FUNC_SPI);
}

void spiInternalResetDescriptors(busDevice_t *bus)
{
    //TODO: implement
    UNUSED(bus);
}

void spiInternalResetStream(dmaChannelDescriptor_t *descriptor)
{
    //TODO: implement
    UNUSED(descriptor);
}

static bool spiInternalReadWriteBufPolled(spi_inst_t *instance, const uint8_t *txData, uint8_t *rxData, int len)
{
    //TODO: implement
    UNUSED(instance);
    UNUSED(txData);
    UNUSED(rxData);
    UNUSED(len);
    return true;
}

void spiInternalInitStream(const extDevice_t *dev, bool preInit)
{
#ifndef USE_DMA
    UNUSED(dev);
    UNUSED(preInit);
#else
    UNUSED(preInit);

    int dma_tx = dma_claim_unused_channel(true);
    int dma_rx = dma_claim_unused_channel(true);

    dev->bus->dmaTx->channel = dma_tx;
    dev->bus->dmaRx->channel = dma_rx;
    dev->bus->dmaTx->irqHandlerCallback = NULL;
    dev->bus->dmaRx->irqHandlerCallback = spiInternalResetStream; // TODO: implement - correct callback

    const spiDevice_t *spi = &spiDevice[spiDeviceByInstance(dev->bus->busType_u.spi.instance)];
    dma_channel_config config = dma_channel_get_default_config(dma_tx);
    channel_config_set_transfer_data_size(&config, DMA_SIZE_8);
    channel_config_set_dreq(&config, spi_get_dreq(SPI_INST(spi->dev), true));

    dma_channel_configure(dma_tx, &config, &spi_get_hw(SPI_INST(spi->dev))->dr, dev->txBuf, 0, false);

    config = dma_channel_get_default_config(dma_rx);
    channel_config_set_transfer_data_size(&config, DMA_SIZE_8);
    channel_config_set_dreq(&config, spi_get_dreq(SPI_INST(spi->dev), false));

    dma_channel_configure(dma_rx, &config, dev->rxBuf, &spi_get_hw(SPI_INST(spi->dev))->dr, 0, false);
#endif
}

void spiInternalStartDMA(const extDevice_t *dev)
{
#ifndef USE_DMA
    UNUSED(dev);
#else
    // TODO check correct, was len + 1 now len
    dma_channel_set_trans_count(dev->bus->dmaTx->channel, dev->bus->curSegment->len, false);
    dma_channel_set_trans_count(dev->bus->dmaRx->channel, dev->bus->curSegment->len, false);

    dma_channel_start(dev->bus->dmaTx->channel);
    dma_channel_start(dev->bus->dmaRx->channel);
#endif
}

void spiInternalStopDMA (const extDevice_t *dev)
{
    //TODO: implement
    UNUSED(dev);
}

// DMA transfer setup and start
void spiSequenceStart(const extDevice_t *dev)
{
    //TODO: implement
    UNUSED(dev);
}
#endif

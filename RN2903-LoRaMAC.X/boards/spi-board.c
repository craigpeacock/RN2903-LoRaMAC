#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include "spi.h"

void SpiInit( Spi_t *obj, SpiId_t spiId, PinNames mosi, PinNames miso, PinNames sclk, PinNames nss )
{
    //printf("SpiInit()\r\n");
}

void SpiDeInit( Spi_t *obj )
{
    //printf("SpiDeInit()\r\n");
}

uint16_t SpiInOut( Spi_t *obj, uint16_t outData )
{
    //printf("SpiInOut()\r\n");
}
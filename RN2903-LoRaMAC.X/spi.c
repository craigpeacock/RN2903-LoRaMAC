

#include <xc.h>
#include <stdio.h>
#include "board.h"
#include "spi.h"

void SPI_Initialise(void)
{
    // SX1276 has a maximum SPI frequency of 10MHz
    // SX1276 uses CPOL = 0, CPHA = 0;
    
    ANSELDbits.ANSD4 = 0;   // Configure as Digital Pin
    ANSELDbits.ANSD1 = 0;   // Configure as Digital Pin
    ANSELDbits.ANSD0 = 0;   // Configure as Digital Pin
    
    DDRDbits.RD4 = 0;       // MOSI
    DDRDbits.RD1 = 1;       // MISO
    DDRDbits.RD0 = 0;       // SCK
    
    SSP2STAT = 0x40;
    SSP2CON1 = 0x20;
    SSP2ADD = 0x00;         // fclock = FOSC/4
}

uint8_t SPI_data(uint8_t data)
{
    SSP2CON1bits.WCOL = 0;
    SSP2BUF = data;
    while (SSP2STATbits.BF == 0) {  }
    return (SSP2BUF);
}

void SX1276_Initialise(void)
{
    uint8_t value;
    
    SX1276_NSS = 1;
    SX1276_NSS_DIR = 0;
        
    SX1276_nRST = 0;
    SX1276_nRST_DIR = 0;
    __delay_ms(10);
    SX1276_nRST = 1;
    __delay_ms(10);
    
    SX1276_NSS = 0;
    SPI_data(0x42);     // RegVersion
    value = SPI_data(0x00);
    SX1276_NSS = 1;
    printf("RegVersion = %02x\r\n",value);
    
    SX1276_NSS = 0;
    SPI_data(0x3C);     // RegVersion
    value = SPI_data(0x00);
    SX1276_NSS = 1;
    printf("Temperature = %d\r\n",value);
}

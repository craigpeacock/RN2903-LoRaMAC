#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "spi.h"
#include "i2c.h"
#include "eeprom.h"

void main(void) {

    uint8_t EUI64[8];
    
    OSC_Initialise();
    EUSART1_Initialise();
    SPI_Initialise();
    SX1276_Initialise();
    I2C1_Initialise();
    
    printf("\r\nRN2903 LoRaWAN Example\r\n");
    
    EEPROM_Get_EUI64(EUI64);
    printf("EUI64 = 0x");
    for (uint8_t i = 0; i <= 7; i++)
        printf("%02x", EUI64[i]);
    printf("\r\n");
        
    while (1) {

    }
}


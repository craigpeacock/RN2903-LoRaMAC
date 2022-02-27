#include <xc.h>
#include <stdio.h>
#include "board.h"
#include "spi.h"

void main(void) {

    OSC_Initialise();
    EUSART1_Initialise();
    SPI_Initialise();
    SX1276_Initialise();
    
    printf("\r\nRN2903 LoRaWAN Example\r\n");
    
    while (1) {

    }
}


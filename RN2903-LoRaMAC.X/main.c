#include <xc.h>
#include <stdio.h>
#include "board.h"

void main(void) {

    OSC_Initialise();
    EUSART1_Initialise();
    
    printf("\r\nRN2903 LoRaWAN Example\r\n");
    
    while (1) {
        printf("Hello World\r\n");
    }
}


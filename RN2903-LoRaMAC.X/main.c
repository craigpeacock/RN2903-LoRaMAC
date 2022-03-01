#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "boards/board.h"
#include "spi.h"
#include "i2c.h"
#include "eeprom.h"

#include "radio.h"

#if defined( REGION_AS923 )

#define RF_FREQUENCY                                923000000 // Hz

#elif defined( REGION_AU915 )

#define RF_FREQUENCY                                915000000 // Hz

#elif defined( REGION_CN779 )

#define RF_FREQUENCY                                779000000 // Hz

#elif defined( REGION_EU868 )

#define RF_FREQUENCY                                868000000 // Hz

#elif defined( REGION_KR920 )

#define RF_FREQUENCY                                920000000 // Hz

#elif defined( REGION_IN865 )

#define RF_FREQUENCY                                865000000 // Hz

#elif defined( REGION_US915 )

#define RF_FREQUENCY                                915000000 // Hz

#elif defined( REGION_RU864 )

#define RF_FREQUENCY                                864000000 // Hz

#else

    #error "Please define a frequency band in the compiler options."

#endif

#define TX_OUTPUT_POWER                             20        // 20 dBm
#define TX_TIMEOUT                                  65535     // seconds (MAX value)

/*!
 * Radio events function pointer
 */
static RadioEvents_t RadioEvents;

/*!
 * \brief Function executed on Radio Tx Timeout event
 */
void OnRadioTxTimeout( void )
{
    // Restarts continuous wave transmission when timeout expires
    Radio.SetTxContinuousWave( RF_FREQUENCY, TX_OUTPUT_POWER, TX_TIMEOUT );
}

void main(void) {

    uint8_t EUI64[8];
    
    OSC_Initialise();
    EUSART1_Initialise();
    SPI_Initialise();
    //SX1276_Initialise();
    I2C1_Initialise();
    
    printf("\r\nRN2903 LoRaWAN Example\r\n");
    
    EEPROM_Get_EUI64(EUI64);
    printf("EUI64 = 0x");
    for (uint8_t i = 0; i <= 7; i++)
        printf("%02x", EUI64[i]);
    printf("\r\n");
        
    //EEPROM_Dump();
    
    // Target board initialization
    BoardInitMcu();
    BoardInitPeriph();
    
    // Radio initialization
    RadioEvents.TxTimeout = OnRadioTxTimeout;
    Radio.Init( &RadioEvents );

    Radio.SetTxContinuousWave( RF_FREQUENCY, TX_OUTPUT_POWER, TX_TIMEOUT );
    
    while (1) {

    }
}


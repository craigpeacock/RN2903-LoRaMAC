
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "eeprom.h"
#include "i2c.h"

#define EEPROM_I2C_SLAVE_ADDRESS        0x50
#define EEPROM_EUI64_ADDR               0xF8

uint8_t EEPROM_Get_EUI64(uint8_t * data)
{
     /* Set the initial state to IDLE */
    I2C1_status.state = I2C_IDLE;
    
    for (uint8_t i = 0; i <= 7; i++)
        data[i] = I2C1_read1ByteRegister(EEPROM_I2C_SLAVE_ADDRESS, i + EEPROM_EUI64_ADDR);
    
    return(true);
}

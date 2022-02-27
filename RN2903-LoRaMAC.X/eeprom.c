
/*
 * 24AA02E64 Serial EEPROM Support Functions
 * Copyright (C) 2020 Craig Peacock 
 * 
 * The RN2903 module contains a 24AA02E64 2Kbit I2C Serial EEPROM with EUI-48 
 * or EUI-64 Node Identity. 
 * 
 * The globally unique EUI node address is programmed at the factory into the 
 * upper half of the array and permanently write-protected. This means the 
 * device is effectively a 1Kbit Serial EEPROM.
 *  
 */

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

void EEPROM_Dump(void)
{
    /* Set the initial state to IDLE */
    I2C1_status.state = I2C_IDLE;
    
    uint8_t i, offset;
    
    for (offset = 0; offset <= 8; offset++)
    {
        printf("0x%04X:",offset * 16);
        for (uint8_t i = 0; i <= 16; i++)
            printf(" %02X",I2C1_read1ByteRegister(EEPROM_I2C_SLAVE_ADDRESS, i + offset * 16));
        printf("\r\n");
    }
    
}
/*
 * Code copied from 
 * https://github.com/microchip-pic-avr-examples/pic18f47q10-cnano-i2c-read-write-int-bare
 * Reference: 90003281A TB3281 Getting Started with I2C Using MSSP on PIC18
 */

/*
 *  (c) 2020 Microchip Technology Inc. and its subsidiaries. 
 *       
 *  Subject to your compliance with these terms, you may use Microchip software and any 
 *  derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
 *  license terms applicable to your use of third party software (including open source software) that 
 *  may accompany Microchip software.
 *   
 *  THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
 *  EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
 *  IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
 *  FOR A PARTICULAR PURPOSE.
 *   
 *  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 *  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 *  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
 *  HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
 *  THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
 *  CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
 *  OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
 *  SOFTWARE.
 */

#include <pic18.h>
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "board.h"
#include "i2c.h"

/*************************** SYSTEM INITIALIZATION ****************************/

void I2C1_Initialise(void)
{
    /* Set pins as Digital */
    ANSELCbits.ANSC3 = 0;       // SCL1
    ANSELCbits.ANSC4 = 0;       // SDA1
    
    /* I2C Master Mode: Clock = F_OSC / (4 * (SSP1ADD + 1)) */
    SSP1CON1bits.SSPM3 = 1;
    
    /* Set the baud rate divider to obtain the I2C clock at 62500 Hz*/
    SSP1ADD  = 0x03;
    
    /* Enable the Global Interrupts */
    INTCONbits.GIE = 1;
    /* Enable the Peripheral Interrupts */
    INTCONbits.PEIE = 1;
}

/******************************** I2C Driver **********************************/

uint8_t I2C1_open(void)
{
    if(I2C1_status.state != I2C_IDLE)  
    {
        /* Return 0 if failed opening I2C */
        return 0;
    }
    
    /* Clear IRQ */
    PIR1bits.SSP1IF = 0;

    /* Enable SSP1 Interrupts */
    PIE1bits.SSP1IE = 1;
    
    /* I2C Master Open */
    SSP1CON1bits.SSPEN = 1;

    /* Return 1 if successfully opened I2C */
    return 1;
}

void I2C1_close(void)
{
    /* Disable I2C1 */
    SSP1CON1bits.SSPEN = 0;

    /* Disable SSP1 Interrupts */
    PIE1bits.SSP1IE = 0;
}

void I2C1_startCondition(void)
{
    /* START Condition*/
    SSP1CON2bits.SEN = 1;
}

void I2C1_stopCondition(void)
{
    /* STOP Condition */
    SSP1CON2bits.PEN = 1;
}

uint8_t I2C1_getAckstatBit(void)
{
    /* Return ACKSTAT bit */
    return SSP1CON2bits.ACKSTAT;
}

void I2C1_sendNotAcknowledge(void)
{
    /* Send NACK bit to slave */
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
}

void I2C1_setReceiveMode(void)
{
    /* Start receiving mode */
    SSP1CON2bits.RCEN = 1;
}

void I2C1_write1ByteRegister(uint8_t address, uint8_t reg, uint8_t data)
{
    while (!I2C1_open())
    {
        ;
    }

    I2C1_status.state = I2C_WRITE_START;
    I2C1_status.address = address;
    I2C1_status.reg = reg;
    I2C1_status.data = data;
    I2C1_status.read = false;

    I2C1_startCondition();
    
    while (I2C1_status.state != I2C_IDLE);
}

uint8_t I2C1_read1ByteRegister(uint8_t address, uint8_t reg)
{
    while (!I2C1_open())
    {
        ;
    }

    I2C1_status.state = I2C_WRITE_START;
    I2C1_status.address = address;
    I2C1_status.reg = reg;
    I2C1_status.data = 0;
    I2C1_status.read = true;

    I2C1_startCondition();
    
    while (I2C1_status.state != I2C_IDLE);
    
    return I2C1_status.data;
}

/************************** I2C Interrupt States ******************************/

void I2C_stateWriteStartComplete(void)
{
    I2C1_status.state = I2C_WRITE_ADDRESS_SENT;
    
    /* Shift the 7 bit address and add a 0 bit to indicate write operation */
    SSP1BUF = (uint8_t)(I2C1_status.address << 1) & ~I2C_RW_BIT;
}

void I2C_stateWriteAddressSent(void)
{
    /* Check the ACK bit and exit the function if its not acknowledge bit */
    if (I2C1_getAckstatBit())
    {
        I2C1_status.state = I2C_IDLE;
        return ;
    }
    
    if (I2C1_status.read)
    {
        I2C1_status.state = I2C_READ_INIT;
    }
    else
    {
        I2C1_status.state = I2C_REGISTER_SENT;
    }
    
    SSP1BUF = I2C1_status.reg;
}

void I2C_stateWriteRegisterSent(void)
{
    /* Check the ACK bit and exit the function if its not acknowledge bit */
    if (I2C1_getAckstatBit())
    {
        I2C1_status.state = I2C_IDLE;
        return ;
    }
    
    I2C1_status.state = I2C_WRITE_DATA_SENT;
    
    SSP1BUF = I2C1_status.data;
}

void I2C_stateWriteDataSent(void)
{
    /* Check the ACK bit and exit the function if its not acknowledge bit */
    if (I2C1_getAckstatBit())
    {
        I2C1_status.state = I2C_IDLE;
        return ;
    }
    
    I2C1_status.state = I2C_STOPBIT;
    
    I2C1_stopCondition();
}

void I2C_stateReadInit(void)
{
    I2C1_status.state = I2C_READ_START_COMPLETE;
    
    /* Send start condition for the read operation */
    I2C1_startCondition();
}

void I2C_stateReadStartComplete(void)
{
    I2C1_status.state = I2C_READ_ADDRESS_SENT;
    
    /* Shift the 7 bit address and add a 1 bit to indicate read operation */
    SSP1BUF = (uint8_t)(I2C1_status.address << 1) | I2C_RW_BIT;
}

void I2C_stateReadAddressSent(void)
{
    /* Check the ACK bit and exit the function if its not acknowledge bit */
    if (I2C1_getAckstatBit())
    {
        I2C1_status.state = I2C_IDLE;
        return ;
    }
    
    I2C1_status.state = I2C_RECEIVE_ENABLE;
    I2C1_setReceiveMode();
}

void I2C_stateReadReceiveEnable(void)
{
    I2C1_status.state = I2C_READ_DATA_COMPLETE;
    
    I2C1_status.data = SSP1BUF;
    
    /* Send NACK bit to stop receiving mode */
    I2C1_sendNotAcknowledge();
}

void I2C_stateReadDataComplete(void)
{
    I2C1_status.state = I2C_STOPBIT;
    I2C1_stopCondition();
}

void I2C_stateStopComplete(void)
{
    I2C1_status.state = I2C_IDLE;
    I2C1_close();
}

void MSSP1_interruptHandler(void)
{
    /* Call the function associated with the current state */
    I2C_stateFuncs[I2C1_status.state]();
    
    /* Clear Interrupt Flag */
    PIR1bits.SSP1IF = 0;
}

void __interrupt() INTERRUPT_InterruptManager (void)
{
    if(INTCONbits.PEIE == 1)
    {
        if(PIE1bits.SSP1IE == 1 && PIR1bits.SSP1IF == 1)
        {
            MSSP1_interruptHandler();
        }
    }
}

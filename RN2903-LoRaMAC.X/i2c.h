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

/* SYSTEM initialization functions */
void I2C1_Initialise(void);

/* Driver functions */
uint8_t I2C1_open(void);
void I2C1_close(void);
void I2C1_startCondition(void);
void I2C1_stopCondition(void);
uint8_t I2C1_getAckstatBit(void);
void I2C1_sendNotAcknowledge(void);
void I2C1_setReceiveMode(void);
void I2C1_write1ByteRegister(uint8_t address, uint8_t reg, uint8_t data);
uint8_t I2C1_read1ByteRegister(uint8_t address, uint8_t reg);

/* State functions for interrupt handler */
void I2C_stateWriteStartComplete(void);
void I2C_stateWriteAddressSent(void);
void I2C_stateWriteRegisterSent(void);
void I2C_stateWriteDataSent(void);
void I2C_stateReadInit(void);
void I2C_stateReadStartComplete(void);
void I2C_stateReadAddressSent(void);
void I2C_stateReadReceiveEnable(void);
void I2C_stateReadDataComplete(void);
void I2C_stateStopComplete(void);

void MSSP1_interruptHandler(void);

#define I2C_RW_BIT                      0x01

typedef enum {
    I2C_WRITE_START = 0,
    I2C_WRITE_ADDRESS_SENT,
    I2C_REGISTER_SENT,
    I2C_WRITE_DATA_SENT,
    I2C_READ_INIT,
    I2C_READ_START_COMPLETE,
    I2C_READ_ADDRESS_SENT,
    I2C_RECEIVE_ENABLE,
    I2C_READ_DATA_COMPLETE,
    I2C_STOPBIT,
    I2C_IDLE
} i2c1_states_t;

void (*I2C_stateFuncs[10])() = {
    I2C_stateWriteStartComplete,    /* I2C_WRITE_START         */
    I2C_stateWriteAddressSent,      /* I2C_WRITE_ADDRESS_SENT  */
    I2C_stateWriteRegisterSent,     /* I2C_REGISTER_SENT       */
    I2C_stateWriteDataSent,         /* I2C_WRITE_DATA_SENT     */
    I2C_stateReadInit,              /* I2C_READ_INIT           */
    I2C_stateReadStartComplete,     /* I2C_READ_START_COMPLETE */
    I2C_stateReadAddressSent,       /* I2C_READ_ADDRESS_SENT   */
    I2C_stateReadReceiveEnable,     /* I2C_RECEIVE_ENABLE      */
    I2C_stateReadDataComplete,      /* I2C_READ_DATA_COMPLETE  */
    I2C_stateStopComplete,          /* I2C_STOP                */
};

struct status {
    volatile i2c1_states_t state;
    uint8_t address;
    uint8_t reg;
    volatile uint8_t data;
    bool read;
} I2C1_status;
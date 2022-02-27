
#define SX1276_DIO0     LATBbits.LATB1
#define SX1276_DIO1     LATBbits.LATB2
#define SX1276_SW_PWR   LATBbits.LATB3
#define SX1276_DIO2     LATBbits.LATB4
#define SX1276_DIO4     LATBbits.LATB5
#define SX1276_DIO5     LATBbits.LATB0

#define SX1276_nRST     LATCbits.LATC2
#define SX1276_nRST_DIR DDRCbits.RC2 

#define SX1276_NSS      LATDbits.LATD3
#define SX1276_NSS_DIR  DDRDbits.TRISD3

void SPI_Initialise(void);
uint8_t SPI_data(uint8_t data);
void SX1276_Initialise(void);


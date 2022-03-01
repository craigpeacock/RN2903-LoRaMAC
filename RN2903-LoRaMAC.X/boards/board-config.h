#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define RADIO_RESET         RC2

#define RADIO_MOSI          RD4
#define RADIO_MISO          RD1
#define RADIO_SCLK          RD0

#define RADIO_NSS           RD3

#define RADIO_DIO_0         RB1
#define RADIO_DIO_1         RB2
#define RADIO_DIO_2         RB4
#define RADIO_DIO_3         NC
#define RADIO_DIO_4         RB5
#define RADIO_DIO_5         RB0

#define RADIO_SWITCH_CTRL1  RB3  

#ifdef __cplusplus
}
#endif

#endif // __BOARD_CONFIG_H__
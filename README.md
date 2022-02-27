# RN2903-LoRaMAC

Source code for the [Microchip RN2903 Module](https://www.beyondlogic.org/microchip-rn2903-lora-transceiver-breakout-board/).

The RN2903 Module includes a:
* [Microchip PIC18LF46K22 MCU](https://www.microchip.com/stellent/groups/picmicro_sg/documents/devicedoc/cn547043.pdf)
* [Semtech SX1276 Radio Transceiver](https://semtech--c.na98.content.force.com/sfc/dist/version/download/?oid=00DE0000000JelG&ids=0682R000006TQEPQA4&d=%2Fa%2F2R0000001Rbr%2F6EfVZUorrpoKFfvaF_Fkpgp5kzjiNyiAbqcpqh9qSjE&operationContext=DELIVERY&asPdf=true&viewId=05H2R000002WGmXUAW&dpt=)
* [Microchip 24AA02E64T 2Kb I2C Serial EEPROM with Pre-Programmed EUI-64™ MAC ID](https://ww1.microchip.com/downloads/en/DeviceDoc/24AA02E48-24AA025E48-24AA02E64-24AA025E64-Data-Sheet-20002124H.pdf)

The goal is to port LoRaMAC-Node to this device:
* https://github.com/Lora-net/LoRaMac-node

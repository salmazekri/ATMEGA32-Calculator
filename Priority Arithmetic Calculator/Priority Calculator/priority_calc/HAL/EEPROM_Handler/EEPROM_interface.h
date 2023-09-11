#ifndef _EEPROM_INTERFACE_H
#define _EEPROM_INTERFACE_H

#define VCC 1
#define GND 0

/*set this macro to VCC or GND*/
#define A2 GND

void EEPROM_SendDataByte(u8 Copy_u8DataByte,u16 Copy_u16LocationAddress);
void EEPROM_ReadDataByte(u8 *Copy_pu8DataByte,u16 Copy_u16LocationAddress);


// void EEPROM_voidSentDataByte(u8 Copy_u8DataByte,u16 Copy_u16LocationAddress);
// void EEPROM_voidReadDataByte(u8 *Copy_u8DataByte,u16 Copy_u16LocationAddress);

#endif // _EEPROM_INTERFACE_H

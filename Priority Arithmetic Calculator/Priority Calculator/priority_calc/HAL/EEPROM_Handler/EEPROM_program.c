#include <avr/io.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include <util/delay.h>
#include "../../MCAL/TWI_Driver/TWI_interface.h"
#include "EEPROM_interface.h"


void EEPROM_SendDataByte(u8 Copy_u8DataByte,u16 Copy_u16LocationAddress){
   /*send start condition*/
   TWI_SendStartCondition();
   /*send slave address with write*/
   TWI_SendSlaveAddressWithWrite( (0b1010 << 3) | (A2 << 2) | (Copy_u16LocationAddress >> 8) );
  // TWI_SendSlaveAddressWithWrite(0b1010000);
   /*send location address*/
   /*casting to 8 bits to send the first 8 bits only*/
   TWI_MasterWriteDataByte((u8)Copy_u16LocationAddress);
   /*send data byte*/
   TWI_MasterWriteDataByte(Copy_u8DataByte);
   /*send stop condition*/
   TWI_SendStopCondition();
}

void EEPROM_ReadDataByte(u8 *Copy_pu8DataByte,u16 Copy_u16LocationAddress){
   /*send start condition*/
   TWI_SendStartCondition();
   /*send slave address with write*/
   TWI_SendSlaveAddressWithWrite( (0b1010 << 3) | (A2 << 2) | (Copy_u16LocationAddress >> 8) );
   //TWI_SendSlaveAddressWithWrite(0b1010000);
   /*send location address*/
   /*casting to 8 bits to send the first 8 bits only*/
   TWI_MasterWriteDataByte((u8)Copy_u16LocationAddress);
   /*send repeated start condition*/
   /*3ashan a8yar men write lel read*/
   TWI_SendRepeatedStart();
   /*send slave address with read*/
   TWI_SendSlaveAddressWithRead( (0b1010 << 3) | (A2 << 2) | (Copy_u16LocationAddress >> 8) );
   //TWI_MasterWriteDataByte(0b10100001);
   /*read data byte*/
   TWI_MasterReadDataByte(Copy_pu8DataByte);
   /*send stop condition*/
   TWI_SendStopCondition();
}

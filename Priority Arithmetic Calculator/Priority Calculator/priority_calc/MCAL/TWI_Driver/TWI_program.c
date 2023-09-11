#include <avr/io.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include <util/delay.h>

#include "TWI_interface.h"

//pass 0 in the master if the master will not be addressed
void TWI_voidMasterInit(u8 Copy_u8MasterAddress){
   /*set clock frquency
     set TWBR to 2
   */
  //original
   TWBR = 2;

    //working
   //  TWBR=255;
   /*set prescaler to 1
     set TWPS0 and TWPS1 to 0
   */
   CLR_BIT(TWSR,TWPS0);
   CLR_BIT(TWSR,TWPS1);
   //set master address
 if(Copy_u8MasterAddress != 0){
   /*set master address*/
   TWAR = Copy_u8MasterAddress << 1; //shift left to make the last bit zero... this is the read/write bit //bits men 1 ly 7 dol el address
 }
   /*enable TWI*/
   SET_BIT(TWCR,TWEN);
}

void TWI_voidSlaveInit(u8 Copy_u8SlaveAddress){
   /*set slave address*/
   TWAR = Copy_u8SlaveAddress << 1;
   /*Enable TWI*/
   SET_BIT(TWCR,TWEN);
}

TWI_ErrStatus TWI_SendStartCondition(void){

   TWI_ErrStatus Local_ErrorStatus = NoError;

   /*send start condition on the bus*/
   SET_BIT(TWCR,TWSTA);

   /*clear interrupt flag to start the previous operation*/
   SET_BIT(TWCR,TWINT);

   /*wait until the start condition is sent*/
   /*wait until the interrupt flag is raised again and the previous operation is completed*/
   while(GET_BIT(TWCR,TWINT) == 0);

   /*check the status of the start condition*/
   //bits from 3 to 7 are status bits (0xf8) and the last two bits are reserved bits and they are always zero
   if((TWSR & 0xF8) != START_ACK){
       Local_ErrorStatus = StartConditionErr;
   }

   return Local_ErrorStatus;

}

//cases for repeated start
/*law 3ayez a8yar address elslave ely baklemo aw ha8yar el operation men read ly write w el 3aks*/
TWI_ErrStatus TWI_SendRepeatedStart(void){

       TWI_ErrStatus Local_ErrorStatus = NoError;

       /*send repeated start condition on the bus*/
       SET_BIT(TWCR,TWSTA);

       /*clear interrupt flag to start the previous operation*/
       SET_BIT(TWCR,TWINT);

       /*wait until the repeated start condition is sent*/
       /*wait until the interrupt flag is raised again and the previous operation is completed*/
       while(GET_BIT(TWCR,TWINT) == 0);

       /*check the status of the repeated start condition*/
       //bits from 3 to 7 are status bits (0xf8) and the last two bits are reserved bits and they are always zero
       if((TWSR & 0xF8) != REP_START_ACK){
           Local_ErrorStatus = RepeatedStartErr;
       }

       return Local_ErrorStatus;

}

TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress){
   TWI_ErrStatus Local_ErrorStatus = NoError;

   /*clear start condition bit*/
   CLR_BIT(TWCR,TWSTA);

   /*set slave address in the 7 most significant bits in the data register*/
   TWDR = Copy_u8SlaveAddress << 1;

   /*clear read/write bit to write on the bus*/
   CLR_BIT(TWDR,0);

   /*clear interrupt flag to start the previous operation*/
   SET_BIT(TWCR,TWINT);

   //TWCR=(1<<TWINT)|(1<<TWEN);
   /*wait until the slave address is sent*/
   /*wait until the interrupt flag is raised again and the previous operation is completed*/
   while(GET_BIT(TWCR,TWINT) == 0);

   /*check the status of the slave address*/
   //bits from 3 to 7 are status bits (0xf8) and the last two bits are reserved bits and they are always zero
   if((TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK){
       Local_ErrorStatus = SlaveAddressWithWriteErr;
   }

   return Local_ErrorStatus;
}

TWI_ErrStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress){
   TWI_ErrStatus Local_ErrorStatus = NoError;

   /*clear start condition bit*/
   CLR_BIT(TWCR,TWSTA);

   /*set slave address in the 7 most significant bits in the data register*/
   TWDR = Copy_u8SlaveAddress << 1;

   /*set read/write bit to read from the bus*/
   SET_BIT(TWDR,0);

   /*clear interrupt flag to start the previous operation*/
   SET_BIT(TWCR,TWINT);

   /*wait until the slave address is sent*/
   /*wait until the interrupt flag is raised again and the previous operation is completed*/
   while(GET_BIT(TWCR,TWINT) == 0);

   /*check the status of the slave address*/
   //bits from 3 to 7 are status bits (0xf8) and the last two bits are reserved bits and they are always zero
   if((TWSR & 0xF8) != SLAVE_ADD_AND_RD_ACK){
       Local_ErrorStatus = SlaveAddressWithReadErr;
   }

   return Local_ErrorStatus;
}

TWI_ErrStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte){
   TWI_ErrStatus Local_ErrorStatus = NoError;

   /*write data byte in the data register*/
   TWDR = Copy_u8DataByte;

   /*clear interrupt flag to start the previous operation*/
   SET_BIT(TWCR,TWINT);

   /*wait until the data byte is sent*/
   /*wait until the interrupt flag is raised again and the previous operation is completed*/
   while(GET_BIT(TWCR,TWINT) == 0);

   /*check the status of the data byte*/
   //bits from 3 to 7 are status bits (0xf8) and the last two bits are reserved bits and they are always zero
   if((TWSR & 0xF8) != MSTR_WR_BYTE_ACK){
       Local_ErrorStatus = MasterWriteDataByteErr;
   }

   return Local_ErrorStatus;
}

TWI_ErrStatus TWI_MasterReadDataByte(u8 *Copy_pu8DataByte){
   TWI_ErrStatus Local_ErrorStatus = NoError;

   /*enable ACK bit after receiving data*/
   /*master sends ack after receiving data*/
   SET_BIT(TWCR,TWEA);

   /*clear interrupt flag to start the previous operation*/
   SET_BIT(TWCR,TWINT);

   /*wait until the data byte is received*/
   /*wait until the interrupt flag is raised again and the previous operation is completed*/
   while(GET_BIT(TWCR,TWINT) == 0);

   /*check the status of the data byte*/
   //bits from 3 to 7 are status bits (0xf8) and the last two bits are reserved bits and they are always zero
   if((TWSR & 0xF8) != MSTR_RD_BYTE_WITH_ACK){
       Local_ErrorStatus = MasterReadDataByteErr;
   }
   else{
       /*read data byte from the data register*/
       *Copy_pu8DataByte = TWDR;
   }

   return Local_ErrorStatus;
}

void TWI_SendStopCondition(void){
   /*send stop condition on the bus*/
   /*generate stop condition on the bus*/
   SET_BIT(TWCR,TWSTO);

   /*clear interrupt flag to start the previous operation*/
   /*ba3mel clear lel flag 3ashan el ta3delat ely ana 3amala a3melha fy el registers elhardware yenfezha 3al bus */
   /*3ashan tol ma el flag mesh ma3molo clear el clock wa2fa w mesh sha8ala*/
   SET_BIT(TWCR,TWINT);
}

#include <avr/io.h>
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "USART_interface.h"



void USART_voidInit(void)
{
	u8 Local_u8UCSRC_value=0;

	//select UCSRC register
    SET_BIT(Local_u8UCSRC_value,7);

	//select Asynchronous mode
	CLR_BIT(Local_u8UCSRC_value,6);

	//Disable parity mode
	CLR_BIT(Local_u8UCSRC_value,4);
	CLR_BIT(Local_u8UCSRC_value,5);

	//select stop bit to be 1 bit
	CLR_BIT(Local_u8UCSRC_value,3);

	//select 8 bit character size
	SET_BIT(Local_u8UCSRC_value,2);
	SET_BIT(Local_u8UCSRC_value,1);
	CLR_BIT(UCSRB,2);


	UCSRC=Local_u8UCSRC_value;

	//Baud Rate
	UBRRL=51;

	//enable receiver
     SET_BIT(UCSRB,4);
	//enable transmitter
     SET_BIT(UCSRB,3);

}

void USART_voidTransmitData(u8 Copy_u8Data)
{// Wait until transmit date buffer is empty
   while(GET_BIT(UCSRA,5)==0);

   //Clear flag
   SET_BIT(UCSRA,5);


   UDR=Copy_u8Data;



}

u8 USART_u8ReceiveData(void)
{
	 while(GET_BIT(UCSRA,7)==0);



	return UDR;
}

void USART_voidTransmitString(u8 *Copy_u8String)
{
    u8 Local_u8Counter=0;
    while(Copy_u8String[Local_u8Counter]!='\0')
    {
        USART_voidTransmitData(Copy_u8String[Local_u8Counter]);
        Local_u8Counter++;
    }
}
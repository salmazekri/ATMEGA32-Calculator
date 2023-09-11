#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

void USART_voidInit(void);

void USART_voidTransmitData(u8 Copy_u8Data);

u8 USART_u8ReceiveData(void);

void USART_voidTransmitString(u8 *Copy_u8String);

#endif
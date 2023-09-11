#ifndef seg_INTERFACE_H_
#define seg_INTERFACE_H_
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"

#define seg_PORTD DIO_PORTD
#define seg_PORTC DIO_PORTC


void seg_voidInit(u8 seg_PORT);
void seg_voidDisplay(u8 seg_PORT,u8 Copy_u8Number);


#endif /* seg_INTERFACE_H_ */

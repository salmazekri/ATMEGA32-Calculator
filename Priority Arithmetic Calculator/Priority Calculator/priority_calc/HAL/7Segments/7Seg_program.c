

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "7Seg_interface.h"

void seg_voidInit(u8 seg_PORT){
    //set direction of 7seg pins as output on port D
    DIO_voidSetSpecificPortDirection(seg_PORT,0b11111111);
}

void seg_voidDisplay(u8 seg_PORT,u8 Copy_u8Number){
    //display numbers from 0 to 9 on 7-segment on port D
   u8 arr[10]={0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,
               0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};
   DIO_voidSetSpecificPortValue(seg_PORT,arr[Copy_u8Number]);
}
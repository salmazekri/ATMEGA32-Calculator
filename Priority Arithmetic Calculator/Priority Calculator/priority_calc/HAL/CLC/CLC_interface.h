#ifndef  CLCI_INTERFACE_H_
#define  CLCI_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"


//4x4 Keypad
#define CLC_ROW0_PIN DIO_PIN0
#define CLC_ROW1_PIN DIO_PIN1
#define CLC_ROW2_PIN DIO_PIN2
#define CLC_ROW3_PIN DIO_PIN3

#define CLC_COL0_PIN DIO_PIN4
#define CLC_COL1_PIN DIO_PIN5
#define CLC_COL2_PIN DIO_PIN6
#define CLC_COL3_PIN DIO_PIN7


#define DIV 10
#define MUL 11
#define SUB 12
#define ADD 13
#define EQU 14
#define ON_CLC 15



void CLC_voidInit(u8 CLC_COL_PORT,u8 CLC_ROW_PORT);
u8 CLC_u8GetPressedKey(u8 CLC_COL_PORT,u8 CLC_ROW_PORT);



#endif // CLCI_INTERFACE_H_






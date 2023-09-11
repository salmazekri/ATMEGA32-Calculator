#ifndef KPDI_INTERFACE_H_
#define KPDI_INTERFACE_H_
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"

//3x4 Keypad
// #define KPD_COL_PORT DIO_PORTA
#define KPD_COL0_PIN DIO_PIN0
#define KPD_COL1_PIN DIO_PIN1
#define KPD_COL2_PIN DIO_PIN2

// #define KPD_ROW_PORT DIO_PORTA
#define KPD_ROW0_PIN DIO_PIN4
#define KPD_ROW1_PIN DIO_PIN5
#define KPD_ROW2_PIN DIO_PIN6
#define KPD_ROW3_PIN DIO_PIN7




void KPD_voidInit(u8 KPD_COL_PORT,u8 KPD_ROW_PORT);
u8 KPD_u8GetPressedKey(u8 KPD_COL_PORT,u8 KPD_ROW_PORT);








#endif /* KPDI_INTERFACE_H_ */
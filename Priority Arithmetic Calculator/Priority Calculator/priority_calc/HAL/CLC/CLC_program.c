#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"

#include "CLC_interface.h"



//4x4 Keypad
#define DIV 10
#define MUL 11
#define SUB 12
#define ADD 13
#define EQU 14
#define ON_CLC 15


void CLC_voidInit(u8 CLC_COL_PORT,u8 CLC_ROW_PORT){
    //set rows as input 
    DIO_voidSetPinDirection(CLC_ROW_PORT,CLC_ROW0_PIN,INPUT);
    DIO_voidSetPinDirection(CLC_ROW_PORT,CLC_ROW1_PIN,INPUT);
    DIO_voidSetPinDirection(CLC_ROW_PORT,CLC_ROW2_PIN,INPUT);
    DIO_voidSetPinDirection(CLC_ROW_PORT,CLC_ROW3_PIN,INPUT);

    //set rows pull up
    DIO_voidSetPinValue(CLC_ROW_PORT,CLC_ROW0_PIN,HIGH);
    DIO_voidSetPinValue(CLC_ROW_PORT,CLC_ROW1_PIN,HIGH);
    DIO_voidSetPinValue(CLC_ROW_PORT,CLC_ROW2_PIN,HIGH);
    DIO_voidSetPinValue(CLC_ROW_PORT,CLC_ROW3_PIN,HIGH);

    //set columns as output
    DIO_voidSetPinDirection(CLC_COL_PORT,CLC_COL0_PIN,OUTPUT);
    DIO_voidSetPinDirection(CLC_COL_PORT,CLC_COL1_PIN,OUTPUT);
    DIO_voidSetPinDirection(CLC_COL_PORT,CLC_COL2_PIN,OUTPUT);
    DIO_voidSetPinDirection(CLC_COL_PORT,CLC_COL3_PIN,OUTPUT);

    //set columns pull up
    DIO_voidSetPinValue(CLC_COL_PORT,CLC_COL0_PIN,HIGH);
    DIO_voidSetPinValue(CLC_COL_PORT,CLC_COL1_PIN,HIGH);
    DIO_voidSetPinValue(CLC_COL_PORT,CLC_COL2_PIN,HIGH);
    DIO_voidSetPinValue(CLC_COL_PORT,CLC_COL3_PIN,HIGH);
}
u8 CLC_u8GetPressedKey(u8 CLC_COL_PORT,u8 CLC_ROW_PORT){
    u8 Local_u8PressedKey=0xAA;

    u8 Local_u8ColumnsArray[4]={CLC_COL0_PIN,CLC_COL1_PIN,CLC_COL2_PIN,CLC_COL3_PIN};
    u8 Local_u8RowsArray[4]={CLC_ROW0_PIN,CLC_ROW1_PIN,CLC_ROW2_PIN,CLC_ROW3_PIN};

    u8 Local_u8KeyArray[4][4]={{7,8,9,DIV},{4,5,6,MUL},{1,2,3,SUB},{ON_CLC,0,EQU,ADD}};
    while(1){
    //set columns to high one by one and check which row is pressed
    for(u8 Local_u8ColumnsIndex=0;Local_u8ColumnsIndex<4;Local_u8ColumnsIndex++)
    {  DIO_voidSetPinValue(CLC_COL_PORT,Local_u8ColumnsArray[Local_u8ColumnsIndex],LOW);

     //check which row is pressed
     for(u8 Local_u8RowsIndex=0;Local_u8RowsIndex<4;Local_u8RowsIndex++)
      {
         u8 Local_u8PinState =DIO_u8GetPinValue(CLC_ROW_PORT,Local_u8RowsArray[Local_u8RowsIndex]);
         if(Local_u8PinState==LOW)
         {
             Local_u8PressedKey=Local_u8KeyArray[Local_u8RowsIndex][Local_u8ColumnsIndex];
            //wait until key is released
             while(Local_u8PinState==LOW)
             {
                 Local_u8PinState=DIO_u8GetPinValue(CLC_ROW_PORT,Local_u8RowsArray[Local_u8RowsIndex]);
             }
             return Local_u8PressedKey;
         }
      }
      //set column to high again
      DIO_voidSetPinValue(CLC_COL_PORT,Local_u8ColumnsArray[Local_u8ColumnsIndex],HIGH);
    }
    }   
}

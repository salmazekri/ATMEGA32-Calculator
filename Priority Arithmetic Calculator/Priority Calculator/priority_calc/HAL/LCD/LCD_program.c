#include <util/delay.h>
#include <avr/io.h>
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "LCD_interface.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void LCD_voidInit(void)
{
    //set direction
    DIO_voidSetPinDirection(LCD_RS_PORT,LCD_RS_PIN,OUTPUT);
    DIO_voidSetPinDirection(LCD_RW_PORT,LCD_RW_PIN,OUTPUT);
    DIO_voidSetPinDirection(LCD_EN_PORT,LCD_EN_PIN,OUTPUT);
    DIO_voidSetSpecificPortDirection(LCD_DATA_PORT,OUTPUT);
    //delay
    _delay_ms(50);
    //function set 2 lines 
    LCD_voidSendCommand(0b00111000);
    //delay
    _delay_ms(1);
    //display on/off control
    LCD_voidSendCommand(0b00001100);
    //delay
    _delay_ms(1);
    //display clear
    LCD_voidSendCommand(0b00000001);
    //delay
    _delay_ms(2);
    //entry mode set
    LCD_voidSendCommand(0b00000110);
    //delay
    _delay_ms(1);
}

void LCD_voidClearDisplay(void)
{
    //display clear
    LCD_voidSendCommand(0b00000001);
    //delay
    _delay_ms(2);
}


void LCD_voidSendData(u8 Copy_u8Data)
{ 
    //set RS
    DIO_voidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,HIGH);
    //set RW
    DIO_voidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,LOW);
    for(u8 i=0;i<8;i++)
    {
        //send data
       DIO_voidSetPinValue(LCD_DATA_PORT,i,GET_BIT(Copy_u8Data,i));
    }
    //set EN
    DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,HIGH);
    //delay
    _delay_ms(2);
    //clear EN
    DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,LOW);

}

void LCD_voidSendCommand(u8 Copy_u8Command)
{
    //set RS
    DIO_voidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,LOW);
    //set RW
    DIO_voidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,LOW);
    for(u8 i=0;i<8;i++)
    {
        //send data
       DIO_voidSetPinValue(LCD_DATA_PORT,i,GET_BIT(Copy_u8Command,i));
    }
    //set EN
    DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,HIGH);
    //delay
    _delay_ms(2);
    //clear EN
    DIO_voidSetPinValue(LCD_EN_PORT,LCD_EN_PIN,LOW);    
}


void LCD_voidSendString(u8 *Copy_u8String)
{
    u8 i=0;
    while(Copy_u8String[i]!='\0')
    {
        LCD_voidSendData(Copy_u8String[i]);
        i++;
    }
}

void LCD_voidSendNumber(int Copy_u32Number)
{
//to display positive and negative numbers
    if(Copy_u32Number<0)
    { LCD_voidGoToXY(1,0);
    	//LCD_voidSendString("negative number");
        LCD_voidSendData('-');
        Copy_u32Number*=-1;
    }
    if(Copy_u32Number==0)
    {
        LCD_voidSendData('0');
    }
    else
    {
        u8 i=0;
        u8 arr[10];
        while(Copy_u32Number>0)
        {
            arr[i]=(Copy_u32Number%10)+48;
            Copy_u32Number/=10;
            i++;
        }
        for(u8 j=i;j>0;j--)
        {
            LCD_voidSendData(arr[j-1]);
        }
    }
}

 void LCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos)
 {
  u8 Local_u8Address=0;

  if(Copy_u8XPos==0)
  {
      Local_u8Address=Copy_u8YPos;
  }
  else if(Copy_u8XPos==1)
  {
      Local_u8Address=Copy_u8YPos+0x40;
  }
 
     SET_BIT(Local_u8Address,7);
     LCD_voidSendCommand(Local_u8Address);
 }


 void LCD_voidSendSpecialChar (unsigned char loc, unsigned char *msg)
{
	unsigned char i;
	if(loc<8)
	{
        LCD_voidSendCommand(0x40+(loc*8));  //send the location of CGRAM address
        for(i=0;i<8;i++)  //write 8 byte for generation of 1 character
        {
            LCD_voidSendData(msg[i]);
        }
	}
}
// LCD_voidSendDecimalNumber(f32 Copy_f32Number){
//      u8 *str;
//      u8 i;

//      str= gcvt(Copy_f32Number,2,)
// }


 void  LCD_voidPrintSpecialChar(void)
 {
	 u8 MULTIPLICATION_CHAR[8]= {
	                               0b00000,
	                               0b10001,
	                               0b01010,
	                               0b00100,
	                               0b01010,
	                               0b10001,
	                               0b00000,
	                               0b00000
	                              };
	   u8 DIVISION_CHAR[8]= {
	                               0b00000,
	                               0b00100,
	                               0b00000,
	                               0b11111,
	                               0b00000,
	                               0b00100,
	                               0b00000,
	                               0b00000
	                        };
	   u8 ADDITION_CHAR[8]= {
	                               0b00000,
	                               0b00100,
	                               0b00100,
	                               0b11111,
	                               0b00100,
	                               0b00100,
	                               0b00000,
	                               0b00000
	                        };
	   u8 SUBTRACTION_CHAR[8]= {
	                               0b00000,
	                               0b00000,
	                               0b00000,
	                               0b11111,
	                               0b00000,
	                               0b00000,
	                               0b00000,
	                               0b00000
	                           };

	   LCD_voidSendSpecialChar(0,ADDITION_CHAR);
	      LCD_voidSendSpecialChar(1,DIVISION_CHAR);
	      LCD_voidSendSpecialChar(2,MULTIPLICATION_CHAR);
	      LCD_voidSendSpecialChar(3,SUBTRACTION_CHAR);

 }

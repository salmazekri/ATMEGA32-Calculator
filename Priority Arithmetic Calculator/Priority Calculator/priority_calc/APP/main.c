/*
 * main.c
 *
 *  Created on: Aug 16, 2023
 *      Author: HP
 */
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/KPD/KPD_interface.h"
#include "../HAL/7Segments/7Seg_interface.h"
#include "../MCAL/TIMER/TIMER_interface.h"
#include "../MCAL/USART/USART_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/TWI_Driver/TWI_interface.h"
#include "../HAL/EEPROM_Handler/EEPROM_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../HAL/ServoMotor/Servo_interface.h"

#include "../HAL/CLC/CLC_interface.h"
#include "../HAL/CLC/calculate.h"






void main(void){



   //define operation characters for display


   //Map operation characters to CGRAM
   LCD_voidInit();
  // LCD_voidSendNumber(120);
   LCD_voidPrintSpecialChar();
   CLC_voidInit(DIO_PORTC,DIO_PORTC);
   u8 Local_u8PressedKey=0;
   u8 Negative_Sign=0;
   u8 number_added=0;
   u8 invalid_operation=0;
   u8 divide_by_zero=0;
   while(1){
      //wait for on_clc button to be pressed
	   while(Local_u8PressedKey!=ON_CLC)
	        {
	            Local_u8PressedKey=CLC_u8GetPressedKey(DIO_PORTC,DIO_PORTC);

	        }


  LCD_voidClearDisplay();

  u8 expression[255]={};
   u32 number=0;
   u8 i=0;

   //wait for on_clc button to be pressed

   //clear lcd

while(Local_u8PressedKey!=EQU)
    {

        //get pressed key
        Local_u8PressedKey=CLC_u8GetPressedKey(DIO_PORTC,DIO_PORTC);
    
              //if pressed key is a number
                if(Local_u8PressedKey!=DIV && Local_u8PressedKey!=MUL && Local_u8PressedKey!=SUB && Local_u8PressedKey!=ADD && Local_u8PressedKey!=EQU)
                {
                    //convert pressed key to number
                    number=number*10+Local_u8PressedKey;
                    if(number==0){
                        //add zero to expression
                        expression[i]='0';
                        i++;
                        //add space to expression
                        expression[i]=' ';
                        i++;
                    }
                    //display number on lcd
                    LCD_voidSendNumber(Local_u8PressedKey);
                    number_added=1;
                }

                else if ((Local_u8PressedKey==DIV || Local_u8PressedKey==MUL || Local_u8PressedKey==SUB || Local_u8PressedKey==ADD)&& Local_u8PressedKey!=EQU)
                    {
                    //change number to string
                    if(number_added==1)
                    {
                        u8 temp[255]={};
                        u8 k=0;
                        while(number!=0){
                            temp[k]=number%10+'0';
                            number/=10;
                            k++;         
                        }
                        //reverse temp string
                        for(u8 j=0;j<k/2;j++){
                            u8 temp2=temp[j];
                            temp[j]=temp[k-j-1];
                            temp[k-j-1]=temp2;
                            }
                        //add temp string to expression
                        for(u8 j=0;j<k;j++){
                            expression[i]=temp[j];
                            i++;
                        }
                            //add space to expression
                                expression[i]=' ';
                                i++;
                                number_added=0;
                    }


                        //if pressed key is an operation character
                        if(Local_u8PressedKey==DIV)
                        {
                            expression[i]='/';
                            i++;
                            //add space to expression
                            expression[i]=' ';
                            i++;
                            LCD_voidSendData(1);
                        }
                        else if(Local_u8PressedKey==MUL)
                        {                                
                            expression[i]='*';
                            i++;
                            //add space to expression
                                expression[i]=' ';
                                i++;
                            LCD_voidSendData(2);
                        }
                        else if(Local_u8PressedKey==SUB)
                        {
                            // if(!isdigit(expression[i-2]))
                                expression[i]='-';
                                i++;
                             //add space to expression
                                expression[i]=' ';
                                i++;
                            LCD_voidSendData(3);
                        }
                        else if(Local_u8PressedKey==ADD)
                        {       
                            expression[i]='+';
                            i++;
                            //add space to expression
                            expression[i]=' ';
                            i++;
                            LCD_voidSendData(0);
                        }
                     number=0;

                    }



    }


    //if pressed key is equal

    //add last number in expression
    if(number !=0)
    {
        u8 temp[255]={};
        u8 j=0;
         while(number!=0)
         {
          
            temp[j]=number%10+'0';
            number/=10;
            j++;
         }
         //reverse temp string
            for(u8 k=0;k<j/2;k++)
            {
                u8 temp2=temp[k];
                temp[k]=temp[j-k-1];
                temp[j-k-1]=temp2;
            }
                //add space to expression
                    temp[j]=' ';
                    j++;

        //add temp string to expression
        for(u8 k=0;k<j;k++)
        {
            expression[i]=temp[k];
            i++;
        
        }
     }


    //  //search expression for division by zero
    //  //LCD_voidSendNumber(i);
    //     for(u8 k=0;k<i;k++)
    //     {
    //         if(expression[k]=='/' && expression[k+2]=='0')
    //         {
    //             LCD_voidClearDisplay();
    //             LCD_voidGoToXY(1,0);
    //             LCD_voidSendString("Division by zero");
    //             invalid_operation=1;
    //             break;
    //         }
    //     }

    //     //search for invalid operation
    //     for(u8 k=0;k<i;k++)
    //     {
    //         if(expression[k]=='+' || expression[k]=='-')
    //         {
    //             if(expression[k+2]=='/' || expression[k+2]=='*')
    //             {
    //                 LCD_voidClearDisplay();
    //                 LCD_voidGoToXY(1,0);
    //                 LCD_voidSendString("Syntax Error");
    //                 invalid_operation=1;
    //                 break;
    //             }
    //         }
    //     }

    //     //if last character is an operation character
    //     if(expression[i-2]=='+' || expression[i-2]=='-' || expression[i-2]=='*' || expression[i-2]=='/')
    //     {
    //         LCD_voidClearDisplay();
    //         LCD_voidGoToXY(1,0);
    //         LCD_voidSendString("Syntax Error");
    //         invalid_operation=1;
    //     }

//check if expression is valid
invalid_operation=isValidOperation(expression);

     if(!invalid_operation){
   CalculateResult(expression);
    // LCD_voidGoToXY(1,0);
    // LCD_voidSendString(expression);

     }
     else{
        LCD_voidGoToXY(1,0);
        LCD_voidSendString("Syntax Error");
     }
}

   }

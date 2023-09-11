



#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/USART/USART_interface.h"
#include "../../MCAL/GIE/GIE_interface.h"
#include "../../MCAL/EXTI/EXTI_interface.h"
#include "../../MCAL/TWI_Driver/TWI_interface.h"
#include "../../HAL/EEPROM_Handler/EEPROM_interface.h"
#include "../../MCAL/ADC/ADC_interface.h"
#include "../../HAL/ServoMotor/Servo_interface.h"
#include "../../HAL/CLC/CLC_interface.h"
#include "../../HAL/CLC/calculate.h"
#include "../../HAL/LCD/LCD_interface.h"
#include "../../HAL/KPD/KPD_interface.h"
#include "../../HAL/7Segments/7Seg_interface.h"
#include "../../MCAL/TIMER/TIMER_interface.h"
#include <util/delay.h>
#include <avr/io.h>
#include "../../HAL/LCD/LCD_interface.h"
#include "calculate.h"


 Stack * initialize()
 {
    Stack* s=malloc(sizeof(Stack));
    s->top=0;
    return s;
 }

 int isEmpty(Stack *s)
 {
    if (s->top==0)
        return 1;
    else
        return 0;
 }
 Item top(Stack *s)
 {
    return s->items[s->top-1];

 }
 Item pop(Stack *s)
 {
    s->top--;
    Item temp=s->items[s->top];
    return temp;
 }
 void push(Stack *s, Item val)
 {
    s->items[s->top]=val;
    s->top++;
 }

 int first(char c)
 {

	 if (c=='*' ||c=='/' || c=='%' )
	    {
	        return 1;
	    }
	    else if (c=='+' ||c=='-'  )
	    {
	        return 0;
	    }
	    else if (c=='^')
	        return 2;
	    else
	        return 3;
 }

 void infixToPostfix(char* infix, char *postfix)
 {
	 Stack *s1= initialize();
	     Item x;
	     char*tok=strtok(infix," ");
	     while(tok!=NULL)
	     {
	         if (isdigit(*tok) ||(*tok=='-'&&strlen(tok)>1))
	         {
	             strncat(postfix, tok, strlen(tok));
	             strncat(postfix, " ", 2);
	         }
	         else if(*tok==')')
	         {
	             while(!isEmpty(s1)&&top(s1).cData!='(')
	             {
	                 x=pop(s1);
	                 strncat(postfix, &x.cData, 1);
	                 strncat(postfix, " ", 2);
	             }
	             pop(s1);
	         }
	         else if(isEmpty(s1))
	         {
	             x.cData=tok[0];
	             push(s1,x);
	         }

	         else if (!isEmpty(s1)&&(first(top(s1).cData)<first(*tok)||top(s1).cData=='('))
	         {
	             x.cData=tok[0];
	             push(s1,x);
	         }
	         else if (!isEmpty(s1)&&first(top(s1).cData)>=first(*tok)&&top(s1).cData!='(')
	         {
	             while(!isEmpty(s1)&&first(top(s1).cData)>=first(*tok))
	             {
	                 x=pop(s1);
	                 strncat(postfix, &x.cData, 1);
	                 strncat(postfix, " ", 2);
	             }
	             x.cData=tok[0];
	             push(s1,x);
	         }
	         tok=strtok(NULL," ");


	     }
	     while(!isEmpty(s1))
	     {
	         x=pop(s1);
	         strncat(postfix,&x.cData, 1);
	         strncat(postfix, " ", 2);
	     }

 }




 float  eval(char tok[],float op1,float op2)
 {
	 float a;
	     if (strchr(tok,'*')!=NULL)
	     {
	         a=op2*op1;

	     }
	     else if (strchr(tok,'+')!=NULL)
	     {
	         a=op2+op1;
	     }
	     else if (strchr(tok,'-')!=NULL)
	     {
	         a=op2-op1;
	     }
	     else if (strchr(tok,'/')!=NULL)
	     {
	         a=op2/op1;
	     }

	     return a;
 }


 float evaluatePostfix(char* postfixexp )
 {
	 Stack *s=initialize();
	     char *tok=strtok(postfixexp," ");
	     Item x,op1,op2,a;
	     while(tok!=NULL )
	     {

	         if(isdigit(tok[0])!=0||tok[0]=='-' &&strlen(tok)>1 )
	         {
	             x.fData=atoi(tok);
	             push(s,x);

	         }
	         else
	         {

	             op1=pop(s);
	             op2=pop(s);
	             a.fData=eval(tok,op1.fData,op2.fData);
	             push(s,a);
	         }
	         tok=strtok(NULL," ");

	     }

	     return pop(s).fData;
	 }

 void replaceNewLineBySpace(char *s)
 {
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
 }

 void CalculateResult(u32 *expression)
 {
 //LCD_voidGoToXY(1,0);

 //LCD_voidSendString(expression);
 _delay_ms(1000);
   //char infixExpr[256] = "1 + 3 + 4";
    u8 postfixExpr[256] = "";

      //  replaceNewLineBySpace(infixExpr);
     //  replaceNewLineBySpace(expression);
        infixToPostfix(expression, postfixExpr);
        u16 answer = evaluatePostfix(postfixExpr);
        LCD_voidGoToXY(1,0);
        LCD_voidSendNumber(answer);
       // _delay_ms(6000);
       // LCD_voidClearDisplay();


  // return answer;
 }
 
 u8 isValidOperation(u8 *expression){
	//get length of expression
		u8 invalid_operation=0;
		u8 i=0;
		while(expression[i]!='\0')
		{
			i++;
		}

	//search expression for division by zero
        for(u8 k=0;k<i;k++)
        {
            if(expression[k]=='/' && expression[k+2]=='0')
            {
                // LCD_voidClearDisplay();
                // LCD_voidGoToXY(1,0);
                // LCD_voidSendString("Division by zero");
                invalid_operation=1;
                break;
            }
        }

        //search for invalid operation
        for(u8 k=0;k<i;k++)
        {
            if(expression[k]=='+' || expression[k]=='-')
            {
                if(expression[k+2]=='/' || expression[k+2]=='*')
                {
                    // LCD_voidClearDisplay();
                    // LCD_voidGoToXY(1,0);
                    // LCD_voidSendString("Syntax Error");
                    invalid_operation=1;
                    break;
                }
            }
        }

        //if last character is an operation character
        if(expression[i-2]=='+' || expression[i-2]=='-' || expression[i-2]=='*' || expression[i-2]=='/')
        {
            // LCD_voidClearDisplay();
            // LCD_voidGoToXY(1,0);
            // LCD_voidSendString("Syntax Error");
            invalid_operation=1;
        }
    
	return invalid_operation;
 }

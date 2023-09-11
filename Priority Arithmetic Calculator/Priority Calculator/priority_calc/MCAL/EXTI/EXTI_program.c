#include <avr/io.h>
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "EXTI_interface.h"
#include "../GIE/GIE_interface.h"

#define NULL_ptr ((void *)0)

void (*Global_pvINT0NotificationFunction)(void)=NULL_ptr;
void (*Global_pvINT1NotificationFunction)(void)=NULL_ptr;

void EXTI_voidInit(void)
{
    //enable global interrupt
   // GIE_voidEnableGlobalInterrupt();
    //enable peripheral interrupt
    //SET_BIT(SREG,7);


    //enable interrupt 0
    SET_BIT(GICR,6);
    //enable interrupt 1
    SET_BIT(GICR,7);
    //set interrupt 0 sense control to any logical change
    SET_BIT(MCUCR,0);
    CLR_BIT(MCUCR,1);
    //set interrupt 1 sense control to any logical change
    SET_BIT(MCUCR,2);
    CLR_BIT(MCUCR,3);
}

//set callback function for interrupt 0
//receives pointer to function to be called when interrupt 0 occurs
//this function is called from main.c
//example: EXTI_voidInit0SetCallBack(&led_on);
void EXTI_voidInit0SetCallBack(void (*NotificationFunction)(void))
{
    Global_pvINT0NotificationFunction=NotificationFunction;
}

//set callback function for interrupt 1
//receives pointer to function to be called when interrupt 1 occurs
//this function is called from main.c
//example: EXTI_voidInit1SetCallBack(&led_on);

void EXTI_voidInit1SetCallBack(void (*NotificationFunction)(void))
{
    Global_pvINT1NotificationFunction=NotificationFunction;
}

//ISR for interrupt 0
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
    if(Global_pvINT0NotificationFunction!=NULL_ptr)
    {
        Global_pvINT0NotificationFunction();
    }
}

//ISR for interrupt 1
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
    if(Global_pvINT1NotificationFunction!=NULL_ptr)
    {
        Global_pvINT1NotificationFunction();
    }
}

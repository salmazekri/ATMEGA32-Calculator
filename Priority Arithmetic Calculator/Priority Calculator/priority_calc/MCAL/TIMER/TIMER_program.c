#include <avr/io.h>
#include <util/delay.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "TIMER_interface.h"
#include "../../HAL/LCD/LCD_interface.h"

#define NULL_ptr ((void*)0)
//Timer normal mode
//req time=1s
//tick time=prescalar/system frequency
//prescalar=8, system frequency=8MHz
//tick time=8/8MHz=1us
//overflow time=tick time * overflow ticks
//overflow ticks=2^resolution
//overflow time=1us * 2^16=65.536ms  (resolution=16 for timer 1)
//overflow time=1us * 2^8=256us  (resolution=8 for timer 0)

//timer 0
///number of overflow=req/overflow time
//number of overflow=1s/256us=3906.25
/*
isr()
{
    static u16 counter=0;
    counter++;
    if(counter==3906.25)
    {
        //do something
        counter=0;
    }
}
*/
//can't stop timer at 3906.25 due to floating point
//fy timer register 2a2dar ast8demo 3la 7sb el overflow time
//timer 0
//40%  60%--->100%
//256*(1-,y)=(1-,25)=192
//timer register=192
/*
isr()
{
        static u16 counter=0;
    counter++;
    if(counter==3907)
    {
        //do something
        counter=0;
        timer register=192;
    }
}
*/

//*********************************************************************************
//overflow time=tick time * overflow ticks
//1us*250=250us //3ayzah ye3ml overflow kol 250us 3ashan y3ml 1s men 8er m yeb2a fy floating point
//number of overflow=req/overflow time
//number of overflow=1s/250us=4000
//*********************************************************************************
/*
implementing a delay function using timer 0
req=1 ms
prescalar=8, system frequency=8MHz
tick time=8/8MHz=1us
CTC mode

number of overflow=req/overflow time
number of overflow=1 ms/250us=4

*/
//*********************************************************************************
 
 
  void (*Global_pvICUFunction)(void)=NULL_ptr;

//Timer 0

void TIMER_voidTimer0OVFInit(void)
{
    //normal mode
    CLR_BIT(TCCR0,WGM00); //bit 6
    CLR_BIT(TCCR0,WGM01); //bit 3
    //prescalar=8
    SET_BIT(TCCR0,CS01); //bit 1
    CLR_BIT(TCCR0,CS00); //bit 0
    CLR_BIT(TCCR0,CS02); //bit 2
    //enable overflow interrupt
    SET_BIT(TIMSK,TOIE0); //bit 0
    //enable global interrupt
    //SET_BIT(SREG,7);
    //set timer register (preload value)
    TCNT0=192;
}

void TIMER_voidTimer0CTCInit(void){
    //CTC mode
     SET_BIT(TCCR0,WGM01); //bit 3
     CLR_BIT(TCCR0,WGM00); //bit 6
    //prescalar=8
    SET_BIT(TCCR0,CS01); //bit 1
    CLR_BIT(TCCR0,CS00); //bit 0
    CLR_BIT(TCCR0,CS02); //bit 2
    //enable compare match interrupt
    SET_BIT(TIMSK,OCIE0); //bit 1
    //enable global interrupt
   // SET_BIT(SREG,7);
    // //set timer register (preload value)
    // OCR0=192;

}
void TIMER_voidTimer0SetCompareMatchValue(u8 Copy_u8CompareMatchValue)
{
    OCR0=Copy_u8CompareMatchValue;
}


//disable global interrupt in CTC mode function before using this function
void TIMER_voidSetBusyWaitTimer0_ms(u32 Copy_u32Time_ms)
{
    TIMER_voidTimer0SetCompareMatchValue(250);
    //yestana kam ms
   for(u16 Local_u16Counter1=0;Local_u16Counter1<Copy_u32Time_ms;Local_u16Counter1++)
    {
        //yestana 1ms
      for(u16 Local_u16Counter2=0;Local_u16Counter2<4;Local_u16Counter2++)
        {
            //wait for flag to be set (polling)
            while(GET_BIT(TIFR,OCF0)==0);
            //clear flag
            SET_BIT(TIFR,OCF0);

       }

    }
}


//*********************************************************************************
void TIMER_voidTimer1Init(void)
{
	//set prescaler   div by 8
	CLR_BIT(TCCR1B,0);
	SET_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);


	//set pwm mode clear on compare set at top
	SET_BIT(TCCR1A,7);
	CLR_BIT(TCCR1A,6);


	//set mode 14
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);

	//set normal mode
//	CLR_BIT(TCCR1A,0);
//	CLR_BIT(TCCR1A,1);
//	CLR_BIT(TCCR1B,3);
//	CLR_BIT(TCCR1B,4);
	//enable interrupt
	//SET_BIT(TIMSK,0);


}




//*********************************************************************************
void TIMER_voidTimer1SetOverFlowValue(u16 Copy_u16OverFlowValue)
{
	ICR1=Copy_u16OverFlowValue;
}

void TIMER_voidTimer1ChannelASetCompareMatchValue(u16 Copy_u16CompareMatchValue)
{
     OCR1A=Copy_u16CompareMatchValue;
}
//*********************************************************************************
//Timer 2
void TIMER_voidTimer2FastPWM(void)
{
    //fast PWM mode
    SET_BIT(TCCR2,WGM20); //bit 6
    SET_BIT(TCCR2,WGM21); //bit 3
    //non inverting mode (clear OC2 on compare match, set OC2 at TOP)
    SET_BIT(TCCR2,COM21); //bit 5
    CLR_BIT(TCCR2,COM20); //bit 4
    //prescalar=8
    SET_BIT(TCCR2,CS21); //bit 1
    CLR_BIT(TCCR2,CS20); //bit 0
    CLR_BIT(TCCR2,CS22); //bit 2
    //set timer register (preload value)
    // OCR2=192;
}
void TIMER_voidTimer2SetCompareMatchValue(u8 Copy_u8CompareMatchValue)
{
    OCR2=Copy_u8CompareMatchValue;
}

void TIMER_voidSetBusyWaitTimer2_ms(u32 Copy_u32Time_ms)
{
    TIMER_voidTimer2SetCompareMatchValue(250);
    //yestana kam ms
   for(u16 Local_u16Counter1=0;Local_u16Counter1<Copy_u32Time_ms;Local_u16Counter1++)
    {
        //yestana 1ms
      for(u16 Local_u16Counter2=0;Local_u16Counter2<4;Local_u16Counter2++)
        {
            //wait for flag to be set (polling)
            while(GET_BIT(TIFR,OCF2)==0);
            //clear flag
            SET_BIT(TIFR,OCF2);

       }

    }
}


void TIMERS_voidTimer1SetPreloadValue(u16 Copy_u16Value)
{
	TCNT1=Copy_u16Value;
}

u16  TIMERS_voidGetTimer1Value(void)
{
	return TCNT1;
}






void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
    static u16 counter=0;
    counter++;

    //toggle led on pin0 portA
    static u8 flag=0;
    if(counter==3907)
    {
        //do something
        DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0,flag);
        TOG_BIT(flag,0);
        counter=0;
        TCNT0=192;
    }
}

//CTC mode
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
    static u16 counter=0;
    counter++;

    //toggle led on pin0 portA
    static u8 flag=0;
    if(counter==4000)
    {
        //do something
        DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0,flag);
        TOG_BIT(flag,0);
        counter=0;
    }
}


void ICU_voidInit(void)
{
	SET_BIT(TIFR,5);
}

void ICU_voidSetSenseControl(u8 Copy_u8SenseControl)
{
	switch(Copy_u8SenseControl)
	{
	case FALLING_EDGE:
		CLR_BIT(TCCR1B,6);
		break;

	case RISING_EDGE:
		SET_BIT(TCCR1B,6);
		break;
	}
}

void ICU_voidSetCallBackFunction(void (*Copy_pvNotificationFunction)(void))
{
	Global_pvICUFunction=Copy_pvNotificationFunction;
}


u16 ICU_u16ReadInputCapture(void)
{
	return ICR1;
}

void ICU_voidInterruptControl(u8 Copy_u8InterruptState)
{
	switch(Copy_u8InterruptState)
	{
	case ENABLE:
		SET_BIT(TIMSK,5);

		break;
	case DISABLE:
		CLR_BIT(TIMSK,5);
		break;

	}
}


void __vector_6 (void)  __attribute__((signal));
void __vector_6 (void)
{

	if(Global_pvICUFunction!=NULL_ptr)
	{
		Global_pvICUFunction();
	}
	else
	{
		/*Do Nothing*/
	}


}

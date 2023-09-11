#include <avr/io.h>
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "Servo_interface.h"
#include "../../MCAL/TIMER/TIMER_interface.h"
#include <util/delay.h>


#define PWM_FREQUENCY 50
#define MIN_PULSE_WIDTH 1000
#define MAX_PULSE_WIDTH 2000

#define NULL_ptr ((void*)0)

void ServoMotor_voidInit(u8 Copy_u8Angle){

    // Set the data direction for the servo pin as output
    DDRD |= (1 << PD7);

    // Configure Timer2 for Fast PWM mode
    TCCR2 |= (1 << WGM20) | (1 << WGM21) | (1 << COM21) | (1 << CS21);

    // Set the top value to generate the desired PWM frequency
    OCR2 = 249;

    // Enable Timer2 overflow interrupt
    TIMSK |= (1 << TOIE2);

    // Start Timer2 with prescaler 8
    TCCR2 |= (1 << CS21);
}

void ServoMotor_voidSetAngle(u8 Copy_u8Angle){
//set angle of servo using timer 2 in pwm mode

    // Calculate the pulse width corresponding to the given angle
    uint16_t pulse_width = 1000 + ((Copy_u8Angle * 1000) / 180); // Angle to pulse width conversion

    // Set the pulse width by setting the compare match value
    OCR2 = (pulse_width * 8) / 1000;
}




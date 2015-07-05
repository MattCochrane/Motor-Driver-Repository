/*
 * Motor_Driver.c
 *
 * Created: 2015-07-03 9:26:18 PM
 *  Author: Matthew Cochrane
 */ 

/*
	This project is protected by the MIT license. Please see LICENSE for more information
	Copyright (c) Matthew Cochrane
 */ 

//required headers
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Motor Driver.h"

// Define motor settings
#define STOP 0
#define FWD 1
#define REV 2
#define BRAKE 3 



void motor_setup(void)
{
        DDRB |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3);
}

//different modes are required for motors, this function is used to select how to do the different modes
int motor_set_mode(int setting)
{
	if (setting == STOP)
	{
		// set in1 in2 high so the motors are off
		
	}
	
	if (setting == FWD)
	{
		//pulse in1 in2 to turn motors CW
	}
	
	if (setting == BRAKE)
	{
		//set in1 high, pulse in2 to brake
	}
	
	if (setting == REV)
	{
		//set in2 high, pulse in1 to turn motors CCW
	}
	return 1;
}

/*
	IN1	|	IN2	|	Operation
	-------------------------
	L	|	L	|	CW
	-------------------------
	L	|	H	|	CCW
	-------------------------
	H	|	L	|	Brake
*/

// left motor is IN1 = PB0 & IN2 = PB1
void left_motor_CW() 
{
	//clear IN1 & IN2
	PORTB &= ~((1<<PB0)|(1<<PB1)); // clear IN1, IN2 to run motor CW
}

void left_motor_CCW()
{
	// clear IN1, set IN2
	PORTB &= ~(1<<PB0); // clear IN1
	PORTB |= (1<<PB1); // set IN2
}

// right motor is IN1 = PB2 & IN2 = PB3
void right_motor_CW()
{
	//clear IN1 & IN2
	PORTB &= ~((1<<PB2)|(1<<PB3)); // clear IN1, IN2 to run motor CW
}

void right_motor_CCW()
{
	// clear IN1, set IN2
	PORTB &= ~(1<<PB2);	// clear IN1
	PORTB |= (1<<PB3); // set IN2
}

void left_motor_stop()
{
	//clear IN2, set IN1
	PORTB &= ~(1<<PB1);
	PORTB |= (1<<PB0);
}

void right_motor_stop()
{
	//clear IN2, set IN1
	PORTB &= ~(1<<PB3);
	PORTB |= (1<<PB2);
}





/*		CODE GRAVEYARD



TIMER SETUP


//enable interrupts
sei();

TIMSK0 |= 1 << TOIE0; // enables overflow

//initialize timer
TCNT0 = 0;
TCCR0B |= (1<<CS02); // prescale clk/256 (arbitrary)

// configure timer		normal mode and compare will allow duty cycle adjust
TCCR0A = 0; // normal mode, overflow flag is set at TCNT0 = 0xFF

//use OCR0A as top to adjust pulse width

//initialize I/O pins
DDRB |= (1<<0) | (1<<1);// change to DDRC?

// set in1 in2 high so the motors are off

//pulse in1 in2 to turn motors CW

//set in1 high, pulse in2 to brake

//set in2 high, pulse in1 to turn motors CCW


ISR
//create interrupt vector
// NOTES
//		keep ISR brief!
//		any variables modified here that are used in main must be declared volatile

// use overflow and compare isr overflow high, compare low
ISR(TIMER0_OVF_vect) // occurs when TCNT0 = 0xFF
{
	//this interrupt will set PB0 and PB1 high to start pulse
	
	PORTB |= (1<<PB0) | (1<<PB1);
	
	//reset timer?
}

ISR(TIMER0_COMPA_vect) // occurs when TCNT0 = OCR0A
{
	//this interrupt will be used to set PB0 & PB1 low again to end the pulse
	PORTB &=  ~((1<<PB0) | (1<<PB1));
}
*/
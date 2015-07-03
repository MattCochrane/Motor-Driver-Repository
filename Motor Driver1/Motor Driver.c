/*
 * Motor_Driver.c
 *
 * Created: 2015-06-25 8:52:34 AM
 *  Author: Matthew Cochrane
	
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

//create interrupt vector
/* NOTES
		keep ISR brief!
		any variables modified here that are used in main must be declared volatile
	*/
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

int motor_setup(void)
{
    while(1)
    {
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
		
    }
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
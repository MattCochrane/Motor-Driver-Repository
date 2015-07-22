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

#define OA_left 180 //  left motor PD7
#define OB_right 190 // Right motor PD6

void motor_setup(void)
{
	
	DDRD |= (1<<PD6) | (1<<PD7) |(1<<PD4) | (1<<PD5); //output
	PORTD |= (1<<PD6) | (1<<PD7) | (1<<PD5) | (1<<PD4); // initialize pins high
}

void timersetup(void)
{	
	sei();
	TCCR2A |= _BV(COM2A0)|_BV(COM2A1)| _BV(WGM20) |_BV(COM2B1)|_BV(COM2B0); //pwm phase correct inverted. Set OC2x on compare match A = 7, B = 6
	TCCR2B |= (1<<CS21);	// prescale 8
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
		//pulse in1 in2 to turn motors CCW
		left_motor_CCW();
		right_motor_CCW();
	}
	
	if (setting == BRAKE)
	{
		//set in1 high, pulse in2 to brake
		left_motor_stop();
		right_motor_stop();
	}
	
	/*if (setting == REV)
	{
		//set in2 high, pulse in1 to turn motors CCW
	}
	return 1;
	*/
}

/*
	
	PD7 |	PD5	|	Operation
	-------------------------
	PWM	|	PWM	|	CW
	-------------------------
	PWM	|	H	|	CCW
	-------------------------
	H	|	PWM	|	Brake
	
*/

// left motor is IN1 = PD7 & IN2 = PD5
void left_motor_CW() 
{
	//PWM IN1 & IN2
	PORTD &= ~((1<<PD5)|(1<<PD7)); // PWM IN1, IN2 to run motor CW
}

void left_motor_CCW()
{
	// clear IN1, set IN2
	OCR2A = OA_left;
	PORTD |= (1<<PD5); // set IN2
	
}

// right motor is IN1 = PD6 & IN2 = PD4
void right_motor_CW()
{
	//PWM IN1 & IN2
	PORTD &= ~(1<<PD4); // PWM IN1, IN2 to run motor CW
						// something something need switches?
}

void right_motor_CCW()
{
	// PWM IN1, set IN2
	OCR2B  = OB_right;
	PORTD |= (1<<PD4); // set IN2
}

void left_motor_stop()
{
	//PWM IN2, set IN1
	PORTD &= ~(1<<PD5);
	OCR2A = 0;
}

void right_motor_stop()
{
	//PWM IN2, set IN1
	PORTD &= ~(1<<PD4);
	OCR2B = 0;
}
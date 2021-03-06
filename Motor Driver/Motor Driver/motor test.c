
#define F_CPU 14745600UL // define clock freq for delay function

#include <avr/io.h>
#include <util/delay.h>
#include "Motor Driver.h"

// Define motor settings
#define STOP 0
#define FWD 1
#define REV 2
#define BRAKE 3

#define OA_left 180
#define OB_right 190


int main(void)
{
	motor_setup();
	timersetup();
	_delay_ms(1000);
	
	//double dist;
	
	//Strategy A
	
	//leave circle
	motor_set_mode(FWD);
	_delay_ms(650);
	motor_set_mode(BRAKE);
	_delay_ms(300);
	
	//turn
	left_motor_CCW();
	_delay_ms(525);
	motor_set_mode(BRAKE);
	
	motor_set_mode(FWD);
	_delay_ms(3000);
	motor_set_mode(BRAKE);
	
	
	/*
	for(int i=0; i<7; i++){
		motor_set_mode(FWD);
		_delay_ms(500);
		dist = GETRANGE();
		if(dist < 310) break;
	}
	
	motor_set_mode(BRAKE);
	*/
}
//TEST 1
	/*left_motor_CW();
	_delay_ms(1000);
	left_motor_stop();
	_delay_ms(1000);
	left_motor_CCW();
	_delay_ms(1000);
	left_motor_stop();
	_delay_ms(1000);
	right_motor_CW();
	_delay_ms(1000);
	right_motor_stop();
	_delay_ms(1000);
	right_motor_CCW();
	_delay_ms(1000);
	//left_motor_stop();
	right_motor_stop();
	*/
	
	//TEST 2
	/*left_motor_CW();
	right_motor_CW();
	_delay_ms(3000);
	left_motor_stop();
	right_motor_stop();
	_delay_ms(1000);
	left_motor_CCW();
	right_motor_CCW();
	_delay_ms(1000);
	left_motor_stop();
	right_motor_stop();
	*/
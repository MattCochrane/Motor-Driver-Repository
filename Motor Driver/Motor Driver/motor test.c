
#define F_CPU 14745600UL // define clock freq for delay function

#include <avr/io.h>
#include <util/delay.h>
#include "Motor Driver.h"


int main(void)
{
	motor_setup();
	_delay_ms(500);
	left_motor_CW();
	_delay_ms(1000);
	left_motor_stop();
	_delay_ms(1000);
	left_motor_CCW();
	_delay_ms(1000);
	right_motor_CW();
	_delay_ms(2000);
	right_motor_stop();
	_delay_ms(2000);
	right_motor_CCW();
	_delay_ms(2000);
	left_motor_stop();
	right_motor_stop();
}
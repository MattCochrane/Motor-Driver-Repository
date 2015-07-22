/*
Range Finder Code
Nicholas Cameron
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#include<math.h>
//#include "uartmaster.h"
#define F_CPU 14745600ul
#define MAX 400
#include <util/delay.h>


int ovflw = 0;
int count = 0;
double d = 0;
double a = 0;
double b = 0;
double diff = 0;
int diff1 = 100;

void RANGER_ON(int u);		//Ranger setup
double GETRANGE(void);

/*
int main(void){
	double test = GETRANGE();
	printf("dist.: %d            test: %d\n",(int) d,(int) test);
	
}
*/
double GETRANGE(void)
{
	while(diff1 > 5) {
		RANGER_ON(1);
		a = d;
		_delay_ms(200);
		RANGER_ON(1);
		b = d;
		_delay_ms(200);
		diff = b-a;
		diff1 = abs(diff);
	}
	if (diff1 <= 5){
		return d;
		}else{
		return 0;
	}
	diff1 = 100;
	
}
void RANGER_ON(int u){
	//init_uart();
	sei();
	if (u == 1){
		DDRB |= (1<<4);	// Set PB 4 as output
		TIMSK0 |= (1<<TOIE0); //overflow mask

		
		EICRA |= (1<<ISC00)|(1<< ISC01)|(1<<ISC11); //set PD2 rising edge and PD3 falling edge. (pins are wired together)
		EIMSK |= (1<<INT0)|(1<<INT1);	//enable external pin interrupts
		
		PORTB |= (1<<PB4);	//send pulse to ranger
		_delay_us(10);
		PORTB &=~ (1<<PB4);
	}
	if(u == 0){
		cli();
		TIMSK0 &=~ (1<<TOIE0); //overflow mask
		
		EICRA &=~ (1<<ISC00)|(1<< ISC01)|(1<<ISC11); //set PD2 rising edge and PD3 falling edge. (pins are wired together)
		EIMSK &=~ (1<<INT0)|(1<<INT1);	//enable external pin interrupts
		sei();
		TCNT0 = 0;
		count = 0;
		ovflw = 0;
	}

}
ISR (INT0_vect){
	TCCR0B |= (1<<CS00);	// no pre-scale
	TCCR0A |= (1<<WGM00);	// normal mode
	
}
ISR (INT1_vect){
	TCCR0A &=~ (1<<WGM00);
	TCCR0B &=~ (1<<CS00);	// turn off clock
	
	d = (2*ovflw*17.29)/58;
	if(d >= 401){
		d = MAX;
	}
	
	ovflw = 0;
	TCNT0 = 0;
}
ISR (TIMER0_OVF_vect)
{
	ovflw ++;
}

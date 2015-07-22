/*
Range Finder Code
Nicholas Cameron
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#include<math.h>
#include "uartmaster.h"
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

//main for testing
/*           
int main(void){
	double test = GETRANGE();
	printf("dist.: %d            test: %d\n",(int) d,(int) test);

}
*/
double GETRANGE(void)
{
	while(diff1 > 5) {
	_delay_ms(100); 
	RANGER_ON(0);
	a = d;
	RANGER_ON(1);
	_delay_ms(100);
	RANGER_ON(0);
	b = d;
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
	init_uart();
	sei();
	if (u == 1){
		DDRB |= (1<<4);	// Set PB 4 as output
		
		TCCR0A |= (1<<WGM01);	// set up pwm CTC mode
		TIMSK0 |= (1<<OCIE0A) | (1<<TOIE0); //count, overflow masks
		OCR0A = 20;	// for 10us
		
		EICRA |= (1<<ISC00)|(1<< ISC01)|(1<<ISC11); //set PD2 rising edge and PD3 falling edge. (pins are wired together)
		EIMSK |= (1<<INT0)|(1<<INT1);	//enable external pin interrupts
		
		PORTB |= (1<<PB4);	//send pulse to ranger
		TCCR0B |= (1<<CS01);	// pre scale clk/8		
	}
	if(u == 0){
		cli();
		TCCR0B &=~ (1<<CS01);	// pre scale clk/8
		DDRB &=~ (1<<4);	// Set PB 4 as output
		
		TCCR0A &=~ (1<<WGM01);	// set up pwm CTC mode
		TIMSK0 &=~ (1<<OCIE0A) | (1<<TOIE0); //count, overflow masks
		
		EICRA &=~ (1<<ISC00)|(1<< ISC01)|(1<<ISC11); //set PD2 rising edge and PD3 falling edge. (pins are wired together)
		EIMSK &=~ (1<<INT0)|(1<<INT1);	//enable external pin interrupts
		PORTB &=~ (1<<PB4);	//send pulse to ranger
		sei();
		
	}

}
ISR (TIMER0_COMPA_vect) // stop transmitting
{
	TCCR0A &=~ (1<<WGM01); //turn off ctc
	TCCR0B &=~ (1<<CS01); //turn off pre scaler					
	PORTB  &= 0;	//turn off pulse to ranger
	TIMSK0 &=~ (1<<OCIE0A); //turn off mask
	TCNT0 = 0; //set counter to 0
}
ISR (INT0_vect){
	TCCR0B |= (1<<CS00);	// no pre-scale					
	TCCR0A |= (1<<WGM00);	// normal mode
	
}
ISR (INT1_vect){
	TCCR0A &=~ (1<<WGM00);	
	TCCR0B &=~ (1<<CS00);	// turn off clock
	
	d = (2*ovflw*17.29)/58;
	if(d >= 401 || d == 0){
		d = MAX;
	}
	
	
	ovflw = 0;
	TCNT0 = 0;
	
	TCCR0A |= (1<<WGM01);	//Turn CTC back on
	TIMSK0 |= (1<<OCIE0A);	//turn mask back on for 10u pulse
	PORTB |= (1<<PB4);		 //send pulse to ranger
	TCCR0B |= (1<<CS01);	// turn clock back on
	
}
ISR (TIMER0_OVF_vect)
{
	ovflw ++;
}

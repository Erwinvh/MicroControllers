/*
 * main.c
 *
 * Created: 3/17/2021 2:40:42 PM
 *  Author: Kasper & Erwin
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "LCD.h"
#include "morse.h"

/*Busy wait number of millisecs*/
void wait2( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR( INT0_vect ) {
	// hier de code
	// bij overgang0 ?1
	// op PORTD.0
	PORTD = 0x10;
}
ISR( INT1_vect ) {
	// hier de code
	// bij overgang0 ?1
	// op PORTD.1
	PORTD = 0x20;
}
ISR( INT2_vect ) {
	// hier de code
	// bij overgang0 ?1
	// op PORTD.2
	PORTD = 0x40;
}
ISR( INT3_vect ) {
	// hier de code
	// bij overgang0 ?1
	// op PORTD.3
	PORTD = 0x80;
}

int main(void)
{
	DDRD = 0xF0;
	EICRA |= 0xFF;
	EIMSK |= 0x0F;
	sei();	
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}
/*
 * main.c
 *
 * Created: 2/10/2021 3:05:19 PM
 *  Author: erwin
 */ 


#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/******************************************************************

short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/*****************************************************************
short:			ISR INT0
inputs:
outputs:
notes:			Set PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
ISR( INT0_vect ) {
	if (PORTD !=0x80)
	{
		PORTD = PORTD<<1;
	}
}

/******************************************************************
short:			ISR INT1
inputs:
outputs:
notes:			Clear PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
ISR( INT1_vect ) {
	
	if (PORTD != 0x10)
	{
		PORTD = PORTD>>1;
	}
}


int main(void)
{
	
		DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input
PORTD = 0x10;
		// Init Interrupt hardware
		EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
		EIMSK |= 0x03;			// Enable INT1 & INT0
		
		// Enable global interrupt system
		//SREG = 0x80;			// Of direct via SREG of via wrapper
		sei();
	
    while(1)
    {
        
    }
}
/*
 * main.c
 *
 * Created: 2/3/2021 8:59:11 PM
 *  Author: KAsper Adan & Erwin van Hunnik
 */ 

# define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/******************************************************************/
int main( void )
{
	
	DDRD = 0b11111111;			// All pins PORTD are set to output 
	
	while (1)
	{
		PORTD = 0x40;			// Write 01000000b PORTD
		wait( 500 );				//01000000
		PORTD = 0x80;			// Write 10000000b PORTD
		wait( 500 );				//10000000
	}

	return 1;
}

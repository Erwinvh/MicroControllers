/*
 * main.c
 *
 * Created: 2/3/2021 9:05:47 PM
 *  Author: Kasper Adan & Erwin van Hunnik
 */ 

# define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


/******************************************************************/
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
	DDRC = 0b00000000;
	PORTD = 0x01;
	while (1)
	{
		PORTD = PORTD << 1;
		wait(50);
		if (PORTD == 0x80)
		{
			PORTD = 0x01;
			wait(50);
		}
	}

	return 1;
}

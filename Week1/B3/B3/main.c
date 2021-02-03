/*
 * main.c
 *
 * Created: 2/3/2021 9:02:34 PM
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
	while (1)
	{
		if (PINC & 0x01)
		{
			if (PORTD == 0x80)
			{
				PORTD = 0x00;
			}else{
				PORTD = 0x80;
			}
		}else{
			PORTD = 0X00;
		}
		wait(500);
				//10000000
	}

	return 1;
}

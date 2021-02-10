/*
 * main.c
 *
 * Created: 2/3/2021 9:08:00 PM
 *  Author: erwin
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
	int light[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02};
	DDRD = 0b11111111;			// All pins PORTD are set to output 
	DDRC = 0b00000000;
	int position = 0;
	while (1)
	{
		PORTD = light[position];
		position++;
		wait(100);
		if (position>13)
		{
			position = 0;
		}
	}

	return 1;
}

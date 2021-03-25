/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** lookup.c
**
** Beschrijving:	Ledpatroon op PORTD dmv table lookup (scheiding logica en data)
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c switch.c
**					avr-gcc -g -mmcu=atmega128 -o lookup.elf lookup.o
**					avr-objcopy -O ihex lookup.elf lookup.hex
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	
	{0x01, 50}, {0x02, 50}, {0x40, 50}, {0x10, 50}, {0x08, 50}, {0x04, 50}, {0x40, 50}, {0x20, 50},
	{0x01, 100}, {0x02, 100}, {0x40, 100}, {0x10, 100}, {0x08, 100}, {0x04, 100}, {0x40, 100}, {0x20, 100},
	{0x01, 200}, {0x02, 200}, {0x40, 200}, {0x10, 200}, {0x08, 200}, {0x04, 200}, {0x40, 200}, {0x20, 200},
	{0x01, 100}, {0x02, 100}, {0x40, 100}, {0x10, 100}, {0x08, 100}, {0x04, 100}, {0x40, 100}, {0x20, 100},
	{0x01, 50}, {0x02, 50}, {0x40, 50}, {0x10, 50}, {0x08, 50}, {0x04, 50}, {0x40, 50}, {0x20, 50},
	{0x01, 25}, {0x02, 25}, {0x40, 25}, {0x10, 25}, {0x08, 25}, {0x04, 25}, {0x40, 25}, {0x20, 25}, {0x00, 0x00}
};

/*Busy wait number of millisecs*/
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


/*
main() loop, entry point of executable
*/
int main( void )
{
	DDRD = 0b11111111;					// PORTD all output
	
	while (1==1) {
		// Set index to begin of pattern array
		int index = 0;
		// as long as delay has meaningful content
		while( pattern[index].delay != 0 ) {
			// Write data to PORTD
			PORTD = pattern[index].data;
			// wait
			wait(pattern[index].delay);
			// increment for next round
			index++;
		}
	}

	return 1;
}
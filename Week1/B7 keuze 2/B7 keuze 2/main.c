/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** knipper.c
**
** Beschrijving:	Toggle even en oneven leds PORTD  
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c knipper.c
**					avr-gcc -g -mmcu=atmega128 -o knipper.elf knipper.o
**					avr-objcopy -O ihex knipper.elf knipper.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void setCharliePlexingLed(int lednr);
void setBitOne(int bit);
void setBitZero(int bit);

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever, flipping bits on PORTD
Version :    	DMK, Initial code
*******************************************************************/
{
	int i = 0;
	int number[] = {1,2,3,4,5,6};
	while (1)
	{
		i++;
		i = i%6;
		int j = number[i];
		setCharliePlexingLed(j);
		wait(1000);
	}

	return 1;
}


void setCharliePlexingLed(int lednr) {
	DDRD = 0b00001110;			// 3 pins PORTD are set to output 
	
	switch(lednr) {
		case 1:
			setBitOne(1);
			setBitZero(2);
			DDRD = 0b00000110;
			break;
		case 2:
			setBitZero(1);
			setBitOne(2);
			DDRD = 0b00000110;
			break;
		case 3:	
			DDRD = 0b00001100;
			setBitOne(2);
			setBitZero(3);
			break;
		case 4:
			DDRD = 0b00001100;
			setBitZero(2);
			setBitOne(3);
			break;
		case 5:
			setBitZero(1);
			DDRD = 0b00001010;
			setBitOne(3);
			break;
		case 6:
			setBitOne(1);
			DDRD = 0b00001010;
			setBitZero(3);
			break;
	}

}

void setBitOne(int bit) {
	int orValue = 0b00000001 << bit;
	PORTD = orValue | PORTD;
}

void setBitZero(int bit) {
	int orValue = 0b00000001 << bit;
	orValue = ~orValue;
	PORTD = orValue & PORTD;
}

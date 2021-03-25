/*
 * main.c
 *
 * Created: 2/10/2021 3:33:27 PM
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




void display(int digit);


int main(void)
{
	DDRD = 0xFF;
	int pos = 0;
	DDRC = 0x00;
    while(1)
    {
		if (PINC & 0x01 && PINC & 0x02)
		{
			pos = 0;
			display(pos);
		}
		else if (PINC & 0x01)
		{
			pos++;
			display(pos);
		}
		else if (PINC & 0x02)
		{
			pos--;
			display(pos);
		}
		wait(250);

    }
}

const unsigned int Numbers [16] = {
	// dPgfe dcba
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, //A
	0b01111100, //b
	0b00111001, //C
	0b00111111, //D
	0b01110001, //F
	0b01111001 //ERROR
};


void display(int digit){
	
if (digit>=0 && digit<=14)
{
	PORTD = Numbers[digit];
}else{
	PORTD = Numbers[15];
}
	
}
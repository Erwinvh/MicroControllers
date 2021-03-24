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
#include "buzz.h"

#define BIT(x)	(1 << (x))

char sentence[16];
int sentenceLength = 0;
int morse[6] = {empty, empty, empty, empty, empty, empty};
int morsePos = 0;


/*Busy wait number of millisecs*/
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

//dot pressed
ISR( INT0_vect ) {
	// op PORTD.0
	morse[morsePos] = dot;
	morsePos++;
	
}
//dash pressed
ISR( INT1_vect ) {
	// op PORTD.1
	morse[morsePos] = dash;
	morsePos++;
	
}
//next pressed
ISR( INT2_vect ) {
	// op PORTD.2
	unsigned char character = getCharFromMorse(morse);
	if (character != '$')
	{
		if (!(sentence[sentenceLength-1] == ' ' && character == ' '))
		{
			lcd_write_data(character);
			sentence[sentenceLength] = character;
			sentenceLength++;
		}
	}
	
	
	for (int i = 0; i < 6; i++)
	{
		morse[i] = empty;
	}
	morsePos = 0;
	}
//biep biep pressed
ISR( INT3_vect ) {
	// op PORTD.3
	buzz_init();
	buzz_play(sentence, sentenceLength);
}// Initialize ADC: 10-bits (left justified), free running
void adcInit( void )
{
	ADMUX = 0b01100001;			// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b11100110;		// ADC-enable, no interrupt, start, free running, division by 64
}

int main(void)
{
	DDRD = 0xF0;
	EICRA |= 0xFF;
	EIMSK |= 0x0F;
	sei();	
	
	lcd_init();
	lcd_clear();
	
	DDRF = 0x00;				// set PORTF for input (ADC)
	adcInit();					// initialize ADC

	while (1)
	{
		setBuzzUnit(ADCH);
		wait(100);				// every 100 ms (busy waiting)
	}
}
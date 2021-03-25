/*
 * buzz.c
 *
 * Created: 24/03/2021 14:26:52
 *  Author: Kasper & Erwin
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include "buzz.h"
#include "morse.h"

int unit = 100;

/*Busy wait number of millisecs*/
void waitBuzz( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void buzz_init(void){
	DDRD = 0xF0;
}

void setBuzzUnit(int speed) {
	unit = speed;
}

void buzz_play(char sentence[], int sentenceLenght){
	for (int i = 0; i < sentenceLenght; i++)
	{
		char character = sentence[i];
		
		if (character == ' ')
		{
			waitBuzz(7 * unit);
		}else
		{		
			int *p;
			p = getMorseFromChar(character);
		
			  for (int i = 0; i < 6; i++ ) {
				  int morsePart = *(p + i);
			  
				  if (morsePart == dot)
				  {
					  PORTD = 0x10;
					  waitBuzz(unit);
					  PORTD = 0x00;
					  waitBuzz(unit);
				  }
				  if (morsePart == dash)
				  {
					  PORTD = 0x10;
					  waitBuzz(3 * unit);
					  PORTD = 0x00;
					  waitBuzz(unit);
				  }
				  if (morsePart == empty)
				  {
					  break;
				  }
			  }
			  waitBuzz(2 * unit);			
		}
	}
}

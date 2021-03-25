/*
 * main.c
 *
 * Created: 2/24/2021 1:00:21 PM
 *  Author: erwin
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "main.h"

#define LCD_E 	3
#define LCD_RS	2


/*Busy wait number of millisecs*/
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void init(){
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00;

	// Step 2 (table 12)
	PORTC = 0x20;	// function set
	lcd_strobe_lcd_e();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();
	

}

void lcd_strobe_lcd_e(void) {
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);			// nodig
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			// nodig?
}

void lcd_write_data(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
	_delay_ms(50);
}

void display_text(char str[]) {
	// Het kan met een while:


for (int i = 0; i<12; i++)
{
	lcd_write_data(str[i]);
}

	// of met een for:
	//for(;*str; str++){
	//	lcd_write_data(*str);
	//}
}

void lcd_clear() {
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x01;
	lcd_strobe_lcd_e();
		PORTC = 0x00;   // Entry mode set
		lcd_strobe_lcd_e();
		PORTC = 0x02;
		lcd_strobe_lcd_e();
}

void lcd_write_cmd(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTA &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTA &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}


int main(void)
{
	char text[] = {'H', 'E', 'L', 'L', 'O', '!','W', 'O', 'R','L', 'D', '!'};
	lcd_clear();
	init();
	lcd_clear();
	
	display_text(text);

    while(1)
    {
		
		_delay_ms(250);
    }
	
	return 1;
}


/*
 * Project name:
     Demo4_1 : Free running AD conversion on channel 1, PORTF.1
 * Author: Avans-TI, JW
 * Revision History: 
     20101229: - initial release;
 * Description:
     This program gives an interrupt on each ms
 * Test configuration:
     MCU:             ATmega128
     Dev.Board:       BIGAVR6
     Oscillator:      External Clock 08.0000 MHz
     Ext. Modules:    -
     SW:              AVR-GCC
 * NOTES:
     - Turn ON the PORT LEDs at SW12.1 - SW12.8
*/
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)	(1 << (x))

void lcd_strobe_lcd_e(void);
void init(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);
void lcd_clear(void);

#define LCD_E 	3
#define LCD_RS	2

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
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

void lcd_write_string(char str[]) {
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

void adcInit( void )
{
	ADMUX = 0b11100001;			// AREF=2,56 V, result left adjusted, channel1 at pin PF3
	ADCSRA = 0b10000110;		// ADC-enable, no interrupt, no free running, division by 64
}

void update_lcd(int value) {
	lcd_clear();
	lcd_write_data(value/10 + '0');
	lcd_write_data(value%10 + '0');
}
	

// Main program: Counting on T1
int main( void )
{
	init();
	
	DDRF = 0x00;					// set PORTF for input (ADC)
	DDRA = 0xFF;					// set PORTA for output
	adcInit();						// initialize ADC

	while (1)
	{
		ADCSRA |= BIT(6);				// Start ADC
		while ( ADCSRA & BIT(6) ) ;		// Wait for completion
		PORTA = ADCH;					// Show MSB (bit 9:2) of ADC
		
		update_lcd(ADCH);

		wait(500);						// every 50 ms (busy waiting)
	}
}
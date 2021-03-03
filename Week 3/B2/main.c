/*
 * counter_t2_cmp.c
 *
 * Created: 21/02/2021 13:08:08
 * Author : Etienne
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void lcd_strobe_lcd_e(void);
void init(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);
void lcd_clear(void);

#define LCD_E 	3
#define LCD_RS	2

#define BIT(x)			(1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
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
volatile int hunderdValue = 0;
volatile int tenthValue = 0;

void update_lcd(char value) {
	if (value > '9') {
	
		tenthValue++;
		TCNT2 = 0x00;
	}
	if (tenthValue > 9) {
		hunderdValue++;
		tenthValue = 0;
	}
	lcd_clear();
	lcd_write_data(hunderdValue+ '0');
	lcd_write_data(tenthValue+ '0');
	lcd_write_data(TCNT2+ '0');
}

int main(void) {
	
	DDRD &= ~BIT(7);		// PD7 op input: DDRD=xxxx xxx0
	DDRB = 0xFF;			// PORTB is output
	TCCR2 = 0b00000111;		// counting via PD7, rising edge
	init();
	
	while (1) {
		PORTB = TCNT2;		// Toon waarde TCCR2
		update_lcd(TCNT2 + '0');
		wait(500);
	}
}
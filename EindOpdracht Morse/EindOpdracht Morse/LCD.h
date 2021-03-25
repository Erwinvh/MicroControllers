/*
 * LCD.h
 *
 * Created: 3/17/2021 14:43:00
 *  Author: Kasper & Erwin
 */ 


#ifndef LCD_H_
#define LCD_H_

void lcd_strobe_lcd_e(void);
void lcd_init(void);
void lcd_write_data(unsigned char byte);
void lcd_clear(void);


#endif /* LCD_H_ */
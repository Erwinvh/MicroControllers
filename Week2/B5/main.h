/*
 * main.h
 *
 * Created: 17/03/2021 13:36:17
 *  Author: kaspe
 */ 


#ifndef MAIN_H_
#define MAIN_H_

void lcd_strobe_lcd_e(void);
void init(void);
void display_text(char str[]);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);
void lcd_clear(void);



#endif /* MAIN_H_ */
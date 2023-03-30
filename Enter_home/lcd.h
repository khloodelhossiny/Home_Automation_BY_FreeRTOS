/*
 * lcd.h
 *
 * Created: 11/16/2022 12:49:39 PM
 *  Author: Ve-ga
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "std_macros.h"

void LCD_init(void);
void LCD_write_char(uint8_t);
void LCD_write_string(uint8_t *);
void LCD_write_command(uint8_t);
void LCD_write_number(int32_t);




#endif /* LCD_H_ */
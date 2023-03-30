/*
 * lcd.c
 *
 * Created: 11/16/2022 12:49:25 PM
 *  Author: Ve-ga
 */ 
#include "lcd.h"
#include "lcd_cfg.h"

void LCD_init(void){
	INIT_LCD_PINS();
	LCD_write_command(0x3);
	_delay_ms(4);
	LCD_write_command(0x3);
	_delay_ms(4);
	LCD_write_command(0x3);
	LCD_write_command(0x2);
	LCD_write_command(0x28);
	LCD_write_command(0x1);
	LCD_write_command(0x06);
	LCD_write_command(0x0c);
	_delay_ms(20);
	
}
void LCD_write_char(uint8_t data){
	LCD_RS(1);
	LCD_D7(READBIT(data,7));
	LCD_D6(READBIT(data,6));
	LCD_D5(READBIT(data,5));
	LCD_D4(READBIT(data,4));
	LCD_EN(1);
	_delay_ms(1);
	LCD_EN(0);
	_delay_ms(1);
	
	LCD_D7(READBIT(data,3));
	LCD_D6(READBIT(data,2));
	LCD_D5(READBIT(data,1));
	LCD_D4(READBIT(data,0));
	LCD_EN(1);
	_delay_ms(1);
	LCD_EN(0);
	_delay_ms(1);

}
void LCD_write_string(uint8_t *txt){
	while(*txt){
		LCD_write_char(*txt);
		txt++;
	}
}
void LCD_write_command(uint8_t cmd){
	LCD_RS(0);
	LCD_D7(READBIT(cmd,7));
	LCD_D6(READBIT(cmd,6));
	LCD_D5(READBIT(cmd,5));
	LCD_D4(READBIT(cmd,4));
	LCD_EN(1);
	_delay_ms(1);
	LCD_EN(0);
	_delay_ms(1);
	
	LCD_D7(READBIT(cmd,3));
	LCD_D6(READBIT(cmd,2));
	LCD_D5(READBIT(cmd,1));
	LCD_D4(READBIT(cmd,0));
	LCD_EN(1);
	_delay_ms(1);
	LCD_EN(0);
	_delay_ms(1);
}
void LCD_write_number(int32_t num){
	if(num == 0) {
		LCD_write_char('0');
		return;
	}	
	int8_t i = 0, neg = 0;
	uint8_t num_arr[10];
	if(num < 0){
		neg = 1;
		num = -num;
	}
	for(i = 0; num != 0 ;i++){ // 6,5,2,1  -125
		num_arr[i] = num % 10 + '0';
		num /= 10;
	}
	i--;
	if(neg){
		i++;
		num_arr[i] = '-';
	}
	while (i >= 0){
		LCD_write_char(num_arr[i]);
		i--;
	}
	
}

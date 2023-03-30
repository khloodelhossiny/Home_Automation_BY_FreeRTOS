/*
 * smart_home.c
 *
 * Created: 2/13/2023 1:13:30 PM
 *  Author: Ve-ga
 */ 
#include "Smart_home.h"
uint8_t input_pass[10], key, idx , num_of_press = 0, reversed = 1;
#define size_pass  eeprom_read(10)
void Enter_Password(void){
	OLD_PASSWORD :
	LCD_write_command(1);
	LCD_write_command(0x80);
	LCD_write_string("Enter Password");
	_delay_ms(80);
	LCD_write_command(1);
	key = get_input_from_user() ;
	idx = 0;
	while(key != 'c' && idx < 10){
		input_pass[idx++] = key;
		key = get_input_from_user();
	}
	if(idx == size_pass){
		reversed = 1;
		for(int i = 0, j = idx; i < size_pass; i++){
			if(input_pass[--j] != eeprom_read(i)){
				reversed = 0;
				break;
			}
		}
		if(reversed == 1){
			LCD_write_command(1);
			LCD_write_string("Calling 122");
			_delay_ms(200);
			return;
		}
	}
	for(int i = 0; i < idx; i++){
		if((idx != size_pass) || (input_pass[i] != eeprom_read(i))){
			LCD_write_command(1);
			num_of_press++;
			LCD_write_string("Wrong Password");
			if(num_of_press == 3){
				num_of_press = 0;
				Buzzer_on();
				_delay_ms(200);
				Buzzer_off();
				goto OLD_PASSWORD;
			}
			goto OLD_PASSWORD;
		}
	}
	num_of_press = 0;
	LCD_write_command(1);
	LCD_write_string("Welcome Back");
	Open_Door();
}
void Chang_Password(void){
	OLD_PASSWORD :
	LCD_write_command(1);
	LCD_write_command(0x80);
	LCD_write_string("Enter Old Password");
	_delay_ms(80);
	LCD_write_command(1);
	key = get_input_from_user() ;
	idx = 0;
	while(key != 'c' && idx < 10){
		input_pass[idx++] = key;
		key = get_input_from_user();
	}

	for(int i = 0; i < idx; i++){
		if((idx != size_pass) || (input_pass[i] != eeprom_read(i))){
			LCD_write_command(1);
			num_of_press++;
			LCD_write_string("Wrong Password");
			if(num_of_press == 3){
				num_of_press = 0;
				Buzzer_on();
				_delay_ms(150);
				Buzzer_off();
				return ;
			}
			goto OLD_PASSWORD;
		}
	}
	num_of_press = 0;
	NEW_PASSWORD :
	 LCD_write_command(1);
	LCD_write_string("Enter New Password");
	_delay_ms(80);
	LCD_write_command(1);
	key = get_input_from_user();
	idx = 0;
	while(key != 'c' && idx < 10){
		input_pass[idx++] = key;
		key = get_input_from_user();
	}
	if(key == 'c'){
		if(idx < 4){
			LCD_write_command(0x80);
			LCD_write_string("too weak");
			LCD_write_command(0xc0);
			LCD_write_string("try again");
			_delay_ms(80);
			goto NEW_PASSWORD ;
		}
		else{
			LCD_write_command(1);
			LCD_write_string("Done");
			eerpom_write(10, idx);         //size_pass = idx;
			for(int i = 0; i < idx; i++){
				eerpom_write(i, input_pass[i]);
			}
			return;
		}
	}
	else{
		LCD_write_command(1);
		LCD_write_string("too long");
		_delay_ms(80);
		goto NEW_PASSWORD ;
	}
	
}
void Open_Door(void){
	DC_direction;
	PWM1_OC1A_duty(90);
	_delay_ms(300);
	PWM1_OC1A_duty(0);
	_delay_ms(200);
	DC_direction_reverse;
	PWM1_OC1A_duty(90);
	_delay_ms(300);
	PWM1_OC1A_duty(0);
}
uint8_t get_input_from_user(){
	int8_t key;
	do{
		key = KEYPAD_read();
	}while(key == -1);
	if(key == 'c'){
		LCD_write_string("OK");
	}
	else{
		LCD_write_char('*');
	}
	while(KEYPAD_read() != -1){}
	return key;
}
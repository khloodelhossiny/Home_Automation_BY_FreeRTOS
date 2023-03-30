/*
 * Enter_home.c
 *
 * Created: 2/12/2023 11:48:49 AM
 * Author : Ve-ga
 */ 

#include "Smart_home.h"
int main(void)
{
	KEYPAD_init();
	LCD_init();
	PWM1_OC1A_init();
	int8_t key ;
	SETBIT(DDRC, 1);
	while (1)
	{
		LCD_write_command(0x80);
		LCD_write_string("1=Enter Password");
		LCD_write_command(0xc0);
		LCD_write_string("2=Change Password");
		key = get_input_from_user();
		if(key == '1'){
			Enter_Password();
		}
		else if( key == '2'){
			Chang_Password();
			
		}

	}
}



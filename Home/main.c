/*
 * Home.c
 *
 * Created: 3/24/2023 11:46:57 PM
 * Author : Ve-ga
 */ 
#include "FreeRTOS.h"
#include "task.h"

#include "std_macros.h"
#include "lcd.h"
#include "PWM.h"
#include "ADC.h"
void PIR_Sensor(void);
void LDR_Sensor(void);
void Temperture_Sensor(void);
void Rain_Sensor(void);
void GAS_Sensor(void);


#define FAN_direction SETBIT(DDRD,0);SETBIT(DDRD,1);SETBIT(PORTD,0);CLRBIT(PORTD,1);
#define Window_direction SETBIT(DDRD,2);SETBIT(DDRD,3);SETBIT(PORTD,2);CLRBIT(PORTD,3);
#define Window_direction_reverse SETBIT(DDRD,2);SETBIT(DDRD,3);CLRBIT(PORTD,2);SETBIT(PORTD,3);
#define open_window SETBIT(PORTB, 3);
#define close_window CLRBIT(PORTB, 3);
#define entry_request READBIT(PINA,0)
#define GAS_LED_on() SETBIT(PORTB,1);
#define GAS_LED_off() CLRBIT(PORTB,1);
#define  OFF_LED() CLRBIT(PORTA,5);
#define  ON_LED() SETBIT(PORTA,5);
#define Rain() READBIT(PINA, 4)
#define GAS() READBIT(PINB, 0)

#define start_degree_temp 34
#define  const_speed 6

int main(void)
{
	LCD_init();
	ADC_init();
	PWM1_OC1A_init();
	SETBIT(DDRA, 0);
	SETBIT(DDRA, 1);
	SETBIT(DDRA, 5);  // for out LED
	SETBIT(DDRA, 6);  // for inside LED
	SETBIT(DDRC, 1);
	SETBIT(DDRC, 0);
	SETBIT(DDRB,3); // for windows
	SETBIT(DDRB,1); // for buzzer
	
	
	xTaskCreate(LDR_Sensor, "LDR_Sensor", 100, NULL, 5, NULL);
	xTaskCreate(Temperture_Sensor, "Temperture_Sensor", 100, NULL, 5, NULL);
	xTaskCreate(PIR_Sensor, "PIR_Sensor", 100, NULL, 5, NULL);
	xTaskCreate(Rain_Sensor, "Rain_Sensor", 100, NULL, 5, NULL);
	xTaskCreate(GAS_Sensor, "GAS_Sensor", 100, NULL, 5, NULL);
	
	
   vTaskStartScheduler();
}

void PIR_Sensor(){
	while(1){
		if(entry_request){
			SETBIT(PORTA,6);
		}
		else{
			CLRBIT(PORTA,6);
			LCD_write_command(0x80);
			LCD_write_string("                  ");
			FAN_direction;
			PWM1_OC1A_duty(0);
		}
		vTaskDelay(1);
	}
}
void LDR_Sensor(){
	static uint16_t LDR;
	while(1){
		LDR = ADC_read(2);
		LDR = (LDR * 3) / 1024;
		switch(LDR){
			case 0 :
				OFF_LED();
				break;
			default: ON_LED();
		}
		vTaskDelay(1);
	}
	
}
void Temperture_Sensor(){
	int16_t temp, speed;
	while(1){
		temp = ADC_read(3);
		temp = (temp - 1) / 2.0;
		speed = (temp - start_degree_temp) * const_speed; // > 35
		speed *=2;
		if(speed > 90 ){
			speed = 90;
		}
		if(speed < 0){
			speed = 0;
		}
		if(entry_request == 1){      // if anybody inside
			LCD_write_command(0x80);
			LCD_write_string("Temperature = ");
			LCD_write_number(temp);
			FAN_direction;
			PWM1_OC1A_duty(speed);
		}
		vTaskDelay(1);
	}
}
void Rain_Sensor(){
	uint8_t window_opend = 1;
	while(1){
		if(Rain() == 1){
			LCD_write_command(0xc0);
			LCD_write_string("It's Raining");
			if(window_opend == 1){
				Window_direction_reverse;
				open_window;
				LCD_write_command(0xc0);
				LCD_write_string("Windows are closing");
				window_opend = 0;
				_delay_ms(135);
				close_window;
				LCD_write_command(1);
			}			
		}
		else{
			LCD_write_command(0xc0);
			LCD_write_string("                  ");	
		}
		vTaskDelay(1);

	}
}
void GAS_Sensor(){
	SETBIT(DDRB, 1);
	CLRBIT(DDRB, 0);
	while(1){
		if(GAS() == 1){
			GAS_LED_on();
		}
		else{
			GAS_LED_off();
		}
		vTaskDelay(1);
	}
}
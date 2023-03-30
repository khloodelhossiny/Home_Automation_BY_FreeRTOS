/*
 * PWM.c
 *
 * Created: 12/7/2022 10:15:05 PM
 *  Author: Ve-ga
 */ 
#include "PWM.h"
void PWM1_OC1A_init(void){
	SETBIT(DDRD, 5);
	SETBIT(TCCR1A, COM1A1);
	SETBIT(TCCR1A, WGM10);
	SETBIT(TCCR1A, WGM11);
	SETBIT(TCCR1A, WGM12);
	SETBIT(TCCR1B, CS10);	
}
void PWM1_OC1A_duty(uint8_t duty_cycle){
	OCR1A = duty_cycle * 10.23;
}
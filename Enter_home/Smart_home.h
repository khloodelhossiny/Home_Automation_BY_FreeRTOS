/*
 * Smart_home.h
 *
 * Created: 2/13/2023 1:12:11 PM
 *  Author: Ve-ga
 */ 


#ifndef SMART_HOME_H_
#define SMART_HOME_H_
#include "std_macros.h"
#include "lcd.h"
#include "PWM.h"
#include "keypad.h"
#include "eeprom.h"
void Open_Door(void);
void Enter_Password(void);
uint8_t get_input_from_user(void);
void Chang_Password(void);
#define DC_direction SETBIT(DDRD,0);SETBIT(DDRD,1);SETBIT(PORTD,0);CLRBIT(PORTD,1);
#define DC_direction_reverse SETBIT(DDRD,0);SETBIT(DDRD,1);SETBIT(PORTD,1);CLRBIT(PORTD,0);
#define Buzzer_on() SETBIT(PORTC,1);
#define Buzzer_off() CLRBIT(PORTC,1);
#define set_password()	eerpom_write(0, '/'); eerpom_write(1, '*');  eerpom_write(10, 2);   // size of password = 10





#endif /* SMART_HOME_H_ */
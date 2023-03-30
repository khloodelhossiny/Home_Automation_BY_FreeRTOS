/*
 * lcd_cfg.h
 *
 * Created: 11/16/2022 7:58:44 PM
 *  Author: Ve-ga
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_
#include "std_macros.h"

/*
D7 -- D4  ==> A7 --- A4
A3 -> En
A2 -> RS
PORTA(2--7) connected to LCD
*/
#define INIT_LCD_PINS() DDRC |= 0xfc; // 0b11111100

#define LCD_RS(x) if(x == 1) SETBIT(PORTC,2); else CLRBIT(PORTC,2);
#define LCD_EN(x) if(x == 1) SETBIT(PORTC,3); else CLRBIT(PORTC,3);
#define LCD_D4(x) if(x == 1) SETBIT(PORTC,4); else CLRBIT(PORTC,4);
#define LCD_D5(x) if(x == 1) SETBIT(PORTC,5); else CLRBIT(PORTC,5);
#define LCD_D6(x) if(x == 1) SETBIT(PORTC,6); else CLRBIT(PORTC,6);
#define LCD_D7(x) if(x == 1) SETBIT(PORTC,7); else CLRBIT(PORTC,7);




#endif /* LCD_CFG_H_ */
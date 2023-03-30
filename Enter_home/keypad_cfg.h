/*
 * keypad_cfg.h
 *
 * Created: 11/16/2022 8:42:41 PM
 *  Author: Ve-ga
 */ 


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#include "std_macros.h"
/*
PORTC 0 to 3   pulled up input
PORTC 4 to 7   Output

*/
#define INIT_KEYPAD_PINS() DDRB = 0xf0; PORTB = 0xff;

#define K0() READBIT(PINB,0)
#define K1() READBIT(PINB,1)
#define K2() READBIT(PINB,2)
#define K3() READBIT(PINB,3)
#define K4(x) if(x == 1) SETBIT(PORTB,4); else CLRBIT(PORTB,4);
#define K5(x) if(x == 1) SETBIT(PORTB,5); else CLRBIT(PORTB,5);
#define K6(x) if(x == 1) SETBIT(PORTB,6); else CLRBIT(PORTB,6);
#define K7(x) if(x == 1) SETBIT(PORTB,7); else CLRBIT(PORTB,7);





#endif /* KEYPAD_CFG_H_ */
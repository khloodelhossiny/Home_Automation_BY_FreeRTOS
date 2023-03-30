/*
 * std_macros.h
 *
 * Created: 11/16/2022 7:59:53 PM
 *  Author: Ve-ga
 */ 


#ifndef STD_MACROS_H_
#define STD_MACROS_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include <avr/interrupt.h> // this header is necessary when you deal with interrupt

#define SETBIT(REG,BIT)  (REG |= 1 << BIT)
#define CLRBIT(REG,BIT)  (REG &= ~(1 << BIT))
#define TOGBIT(REG,BIT)  (REG ^= 1 << BIT)
#define READBIT(REG,BIT)  ((REG >> BIT) & 1)



#endif /* STD_MACROS_H_ */
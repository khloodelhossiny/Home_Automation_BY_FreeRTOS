/*
 * ADC.h
 *
 * Created: 12/15/2022 2:45:23 PM
 *  Author: Ve-ga
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "std_macros.h"

void ADC_init(void);

uint16_t ADC_read(uint8_t ch);



#endif /* ADC_H_ */
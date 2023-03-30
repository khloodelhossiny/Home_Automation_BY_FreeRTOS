/*
 * eeprom.h
 *
 * Created: 11/26/2022 10:30:38 PM
 *  Author: Ve-ga
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "std_macros.h"
void eerpom_write (uint16_t add, uint8_t data);
uint8_t eeprom_read(uint16_t add);




#endif /* EEPROM_H_ */
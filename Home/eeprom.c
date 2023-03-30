/*
 * eeprom.c
 *
 * Created: 11/26/2022 10:31:00 PM
 *  Author: Ve-ga
 */ 
#include "eeprom.h"
void eerpom_write (uint16_t add, uint8_t data){
	while (READBIT(EECR,EEWE) != 0);
	EEAR = add;
	EEDR = data;
	SETBIT(EECR, EEMWE);
	SETBIT(EECR, EEWE);
}
uint8_t eeprom_read(uint16_t add){
	while (READBIT(EECR,EEWE) != 0);
	EEAR = add;
	SETBIT(EECR, EERE);
	return EEDR;
}
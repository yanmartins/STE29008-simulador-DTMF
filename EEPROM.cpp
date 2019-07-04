/*
 * EEPROM.cpp
 *
 *  Created on: 30 de jun de 2019
 *      Author: yan
 */


#include "EEPROM.h"


char EEPROM::read(uint8_t * pos){
	return eeprom_read_byte(pos);
}

void EEPROM::write(uint8_t * pos, uint8_t byte){
	eeprom_write_byte(pos, byte);
}

void EEPROM::write_string(uint8_t * pos, Fila<uint8_t,10> bytes){
	uint8_t * _pos = pos;
	while(!bytes.vazia()){
		eeprom_write_byte(_pos, bytes.desenfileira());
		_pos++;
	}
}

/*
 * EEPROM.h
 *
 *  Created on: 30 de jun de 2019
 *      Author: yan
 */

#ifndef EEPROM_H_
#define EEPROM_H_
#include "fila.h"
#include <avr/eeprom.h>

class EEPROM{
public:
	EEPROM(){};
	~EEPROM(){};
	char read(uint8_t * pos);
	void write(uint8_t * pos, uint8_t byte);
	void write_string(uint8_t * pos, Fila<uint8_t,10> bytes);

private:

};


#endif /* EEPROM_H_ */

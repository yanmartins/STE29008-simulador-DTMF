/*
 * uart_mapping.h
 *
 *  Created on: 21 de mai de 2019
 *      Author: yan
 */

#ifndef UART_MAPPING_H_
#define UART_MAPPING_H_
#include <stdio.h>

namespace UART_MAPPING{

class UART_Mapping{
public:
	void definirUart(uint32_t baud, uint8_t speed, uint8_t db, uint8_t parity, uint8_t sb);

	uint8_t getUDR();
	void setUDR(uint8_t data);

	void ativaInt();
	void desativaInt();

private:
	uint8_t UCSRnA;
	uint8_t UCSRnB;
	uint8_t UCSRnC;
	uint8_t reserved;
	uint8_t UBRRnL;
	uint8_t UBRRnH;
	uint8_t UDRn;
};
	extern UART_Mapping * AllUarts[4];
}

#endif /* UART_MAPPING_H_ */

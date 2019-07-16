/*
 * uart_mapping.cpp
 *
 *  Created on: 28 de mai de 2019
 *      Author: yan
 */

#include "uart_mapping.h"
#include <avr/io.h>

namespace UART_MAPPING{

enum UART_ADDR_BASE {
	UART_0 = 0x00C0,
	UART_1 = 0x00C8,
	UART_2 = 0x00D0,
	UART_3 = 0x0130
};


/**
 * Ponteiro para referenciar região de memória
 * de cada UART
 */
UART_Mapping * AllUarts[4] = {
		reinterpret_cast<UART_Mapping*>(UART_0),
		reinterpret_cast<UART_Mapping*>(UART_1),
		reinterpret_cast<UART_Mapping*>(UART_2),
		reinterpret_cast<UART_Mapping*>(UART_3)
};


/**
 * Define os modos de operação da serial
 */
void UART_Mapping::definirUart(uint32_t baud, uint8_t speed, uint8_t db, uint8_t parity, uint8_t sb){

	if (speed == 0){
		UBRRnH =  (((F_CPU/16/baud)-1)>>8);
		UBRRnL =  ((F_CPU/16/baud)-1);
	} else {
		UBRRnH =  (((F_CPU/8/baud)-1)>>8);
		UBRRnL =  ((F_CPU/8/baud)-1);
	}
	UCSRnB = 152;
	UCSRnC = db|parity|sb;
}


uint8_t UART_Mapping::getUDR(){
	return UDRn;
}

void UART_Mapping::setUDR(uint8_t data){
	UDRn = data;
}

void UART_Mapping::ativaInt(){
	UCSRnB |= (1<<5);
}

void UART_Mapping::desativaInt(){
	UCSRnB &= ~(1<<5);
}

}


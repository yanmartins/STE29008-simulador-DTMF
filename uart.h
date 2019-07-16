/*
 * uart_mapping.h
 *
 *  Created on: 21 de mai de 2019
 *      Author: yan
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart_mapping.h"
#include "fila.h"

#ifndef UART_H_
#define UART_H_

class UART {
public:

	enum DATABITS_t {
		DATABITS_5 = 0,
		DATABITS_6 = 2,
		DATABITS_7 = 4,
		DATABITS_8 = 6
	};

	enum PARITY_t {
			NONE = 0,
			EVEN = 32,
			ODD = 48
		};

	enum STOPBITS_t {
			STOPBIT_1 = 0,
			STOPBIT_2 = 8
		};

	enum SPEED_t{
			NORMAL_SPEED = 0,
			DOUBLE_SPEED = 1
		};

	UART(uint8_t id, uint32_t baud, UART::SPEED_t speed, UART::DATABITS_t db, UART::PARITY_t parity, UART::STOPBITS_t sb);
	~UART();
	void put(uint8_t data);
	void puts(char data[]);
	uint8_t get();
	bool has_data();
	static void rxc_isr_handler(uint8_t id);
	static void tx_isr_handler(uint8_t id);

	UART_MAPPING::UART_Mapping * _serial;	// Ponteiro para a classe UART_Mapping

	Fila<uint8_t, 10> _rx;	// Fila de recepção
	Fila<uint8_t, 10> _tx;	// Fila de transmissão

private:
	static UART * uart_singleton[4]; 	// Garante que apenas 4 seriais sejam criadas.
};


#endif /* UART3_H_ */

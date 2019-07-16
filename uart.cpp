/*
 * uart_mapping.h
 *
 *  Created on: 21 de mai de 2019
 *      Author: yan
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

UART * UART::uart_singleton[4];


/**
 * Construtor da classe UART
 */
UART::UART(uint8_t id, uint32_t baud, UART::SPEED_t speed, UART::DATABITS_t db, UART::PARITY_t parity, UART::STOPBITS_t sb) {
	_serial = UART_MAPPING::AllUarts[id];
	_serial->definirUart(baud, speed, db, parity, sb);
	uart_singleton[id] = this;
}


/**
 * Destrutor da classe UART
 */
UART::~UART(){}


/**
 * Adiciona dados na fila de transmissão
 * e ativa a interrupção.
 */
void UART::put(uint8_t data) {
	if(!_tx.cheia()){
		_tx.enfileira(data);
		_serial->ativaInt();
	}
}


/**
 * Transmite uma string, adicioninado-a na
 * fila de transmissão através da função put().
 */
void UART::puts(char data[]) {
	int i = 0;
	while(data[i] != 0){
		put(data[i]);
		i++;
	}
}


/**
 * Retorna o dado recebido a partir da
 * fila de recepção e o remove da mesma.
 */
uint8_t UART::get() {
	uint8_t data = _rx.desenfileira();
	return data;
}


/**
 * Retorna TRUE caso haja dados na
 * fila de Recepção (RX).
 */
bool UART::has_data(){
	return !_rx.vazia();
}


/**
 * Função para tratamento da recepção (RX)
 * invocada pelas interrupções da respectiva
 * serial utilizada.
 */
void UART::rxc_isr_handler(uint8_t id) {
	if(!uart_singleton[id]->_rx.cheia()){
		uart_singleton[id]->_rx.enfileira(uart_singleton[id]->_serial->getUDR());
	}
}


/**
 * Função para tratamento da transmissão (TX)
 * invocada pelas interrupções da respectiva
 * serial utilizada.
 */
void UART::tx_isr_handler(uint8_t id) {
	if(!uart_singleton[id]->_tx.vazia()){
		uart_singleton[id]->_serial->setUDR(uart_singleton[id]->_tx.desenfileira());
	}
	else {
		uart_singleton[id]->_serial->desativaInt();
	}
}

ISR(USART0_RX_vect) {
	UART::rxc_isr_handler(0);
}

ISR(USART0_UDRE_vect) {
	UART::tx_isr_handler(0);
}

ISR(USART1_RX_vect){
	UART::rxc_isr_handler(1);
}

ISR(USART1_UDRE_vect){
	UART::tx_isr_handler(1);
}

ISR(USART2_RX_vect){
	UART::rxc_isr_handler(2);
}

ISR(USART2_UDRE_vect){
	UART::tx_isr_handler(2);
}

ISR(USART3_RX_vect){
	UART::rxc_isr_handler(3);
}

ISR(USART3_UDRE_vect){
	UART::tx_isr_handler(3);
}

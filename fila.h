/*
 * uart_mapping.h
 *
 *  Created on: 21 de mai de 2019
 *      Author: yan
 */

#ifndef FILA_H_
#define FILA_H_

template <typename T, int cap> class Fila {

public:
	Fila() {
		_inicio = 0;
		_final = 0;
		_N = 0;
	}

	void enfileira(T data){

		_buffer[_final] = data;
		_final++;
		_N++;
		 if (_final == cap) _final = 0;
	}

	T desenfileira(){
		T data = _buffer[_inicio];
		_N--;
		_inicio++;
		if (_inicio == cap) _inicio = 0;
		return data;
	}

	bool cheia(){
		return (_N == cap);
	}

	bool vazia(){
		return(_N == 0);
	}

	int comprimento(){
		return _N;
	}

private:
	T _buffer[cap];
	int _inicio;
	int _final;
	int _N;
};

#endif /* FILA_H_ */

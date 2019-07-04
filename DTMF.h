#ifndef DTMF_H_
#define DTMF_H_
#include "GPIO.h"

class DTMF{
public:

	DTMF(GPIO * c1, GPIO * c2, GPIO * c3, GPIO * c4, GPIO *l1,
			GPIO * l2, GPIO * l3, GPIO * l4);
	~DTMF(){};
	void send(char digito);

private:
	// Colunas
	GPIO * c1;
	GPIO * c2;
	GPIO * c3;
	GPIO * c4;

	// Linhas
	GPIO * l1;
	GPIO * l2;
	GPIO * l3;
	GPIO * l4;
};

#endif /* DTMF_H_ */

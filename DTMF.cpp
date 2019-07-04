#include "DTMF.h"
#include "GPIO.h"
#include <util/delay.h>

DTMF::DTMF(GPIO * c1, GPIO * c2, GPIO * c3, GPIO * c4, GPIO *l1,
		GPIO * l2, GPIO * l3, GPIO * l4){
	this->c1 = c1;
	this->c2 = c2;
	this->c3 = c3;
	this->c4 = c4;

	this->l1 = l1;
	this->l2 = l2;
	this->l3 = l3;
	this->l4 = l4;

	this->c1->set(true);
	this->c2->set(true);
	this->c3->set(true);
	this->c4->set(true);

	this->l1->set(true);
	this->l2->set(true);
	this->l3->set(true);
	this->l4->set(true);
}

void DTMF::send(char digito){
	int delay = 25;
	switch(digito){
		case '0':
			l4->toggle();
			l2->toggle();
			_delay_ms(delay);
			l4->toggle();
			l2->toggle();
			break;

		case '1':
			l1->toggle();
			c1->toggle();
			_delay_ms(delay);
			l1->toggle();
			c1->toggle();
			break;

		case '2':
			l1->toggle();
			c2->toggle();
			_delay_ms(delay);
			l1->toggle();
			c2->toggle();
			break;

		case '3':
			l1->toggle();
			c3->toggle();
			_delay_ms(delay);
			l1->toggle();
			c3->toggle();
			break;

		case '4':
			l2->toggle();
			c1->toggle();
			_delay_ms(delay);
			l2->toggle();
			c1->toggle();
			break;

		case '5':
			l2->toggle();
			c2->toggle();
			_delay_ms(delay);
			l2->toggle();
			c2->toggle();
			break;

		case '6':
			l2->toggle();
			c3->toggle();
			_delay_ms(delay);
			l2->toggle();
			c3->toggle();
			break;

		case '7':
			l3->toggle();
			c1->toggle();
			_delay_ms(delay);
			l3->toggle();
			c1->toggle();
			break;

		case '8':
			l3->toggle();
			c2->toggle();
			_delay_ms(delay);
			l3->toggle();
			c2->toggle();
			break;

		case '9':
			l3->toggle();
			c3->toggle();
			_delay_ms(delay);
			l3->toggle();
			c3->toggle();
			break;

		case '*':
			l4->toggle();
			c1->toggle();
			_delay_ms(delay);
			l4->toggle();
			c1->toggle();
			break;

		case '#':
			l4->toggle();
			c3->toggle();
			_delay_ms(delay);
			l4->toggle();
			c3->toggle();
	}
}

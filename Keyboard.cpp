/*
 * Keyboard.cpp
 *
 *  Created on: Jul 3, 2019
 *      Author: root
 */


#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include inbuilt defined Delay header file */
#include "Keyboard.h"


Keyboard::Keyboard(GPIO *l1, GPIO *l2, GPIO *l3,GPIO *l4,GPIO *c1,GPIO *c2,GPIO *c3,GPIO *c4 ){

	key = 'N';
	l[0] = l1;
	l[1] = l2;
	l[2] = l3;
	l[3] = l4;


	c[0] = c1;
	c[1] = c2;
	c[2] = c3;
	c[3] = c4;

}

bool Keyboard::Percorre(){

bool teste = true;
	for (int ti = 0; ti<4; ti++)
	    {
	    //Alterna o estado dos pinos das linhas

		l[0]->set(false);
		l[1]->set(false);
		l[2]->set(false);
		l[3]->set(false);

	    l[ti]->set(true);

	    //Verifica se alguma tecla da coluna 1 foi pressionada
	    if (c[0]->get())
	    {
	    	Key(ti, 0);
	    	while(c[0]->get());
	    	teste = false;

	    }

	    //Verifica se alguma tecla da coluna 2 foi pressionada
	    if (c[1]->get())
	    {
	      Key(ti, 1);
	      while(c[1]->get());
	      teste = false;

	    }

	    //Verifica se alguma tecla da coluna 3 foi pressionada
	    if (c[2]->get())
	    {
	     Key(ti, 2);
	      while(c[2]->get());
	      teste = false;

	    }

	    //Verifica se alguma tecla da coluna 4 foi pressionada
	    if (c[3]->get())
	    {
	     Key(ti, 3);
	      while(c[3]->get());
	      teste = false;
	    }
	   }
	   _delay_ms(10);

return teste;

}

char Keyboard::retKey(){
	return key;
}

void Keyboard::Key(int i, int j) {

	unsigned char keypad[4][4] = {	{'1','2','3','A'},
									{'4','5','6','B'},
									{'7','8','9','C'},
									{'*','0','#','D'}};

	key = keypad[i][j];
	//return key;
}



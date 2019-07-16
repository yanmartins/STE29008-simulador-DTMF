/*
 * Keyboard.h
 *
 *  Created on: Jul 3, 2019
 *      Author: root
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#include "GPIO.h"

class Keyboard {
public:

	Keyboard(GPIO *l1, GPIO *l2, GPIO *l3,GPIO *l4,GPIO *c1,GPIO *c2,GPIO *c3,GPIO *c4 );
	bool Percorre();
	char retKey();
	void Key(int i, int j);

private:

	char key;
	GPIO *l[4];
	GPIO *c[4];


};




#endif /* KEYBOARD_H_ */

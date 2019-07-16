/*
 * LCD.h
 *
 *  Created on: Jul 3, 2019
 *      Author: root
 */

#ifndef LCD_H_
#define LCD_H_

class LCD {
public:

	LCD();
	void LCD_Command(unsigned char cmnd);
	void LCD_Char (unsigned char char_data);
	void LCD_Init (void);
	void LCD_String (char *str);
	void LCD_Clear();

private:

};




#endif /* LCD_H_ */

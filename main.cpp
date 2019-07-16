#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>
#include "LCD.h"
#include "Keyboard.h"
#include "GPIO.h"
#include "uart.h"
#include "DTMF.h"
#include "EEPROM.h"

void addSeq(uint8_t * posi, Keyboard teclado, EEPROM eeprom, LCD display){
	display.LCD_Clear();
	display.LCD_String("Digite a seq");
	display.LCD_Command(0xC0);
	int i = 0;
	char a = 'n';
	Fila <uint8_t, 10> filat;
	while(i < 9){
		while(teclado.Percorre()){
		_delay_ms(20);

	}
	i++;
	a = teclado.retKey();
	filat.enfileira(a);
	display.LCD_Char(a);

	}
	eeprom.write_string(posi, filat);
	display.LCD_Clear();

}
int main() {

//------------------------- Instancias linhas e colunas do teclado------------------------
	GPIO l1 = GPIO(11, GPIO::OUTPUT);
	GPIO l2 = GPIO(10, GPIO::OUTPUT);
	GPIO l3 = GPIO(9, GPIO::OUTPUT);
	GPIO l4 = GPIO(8, GPIO::OUTPUT);
	GPIO c1 = GPIO(7, GPIO::INPUT);
	GPIO c2 = GPIO(6, GPIO::INPUT);
	GPIO c3 = GPIO(5, GPIO::INPUT);
	GPIO c4 = GPIO(4, GPIO::INPUT);

	//Instancias linhas e colunas DTMF

	GPIO c1_d(29 , GPIO::OUTPUT);
	GPIO c2_d(23 , GPIO::OUTPUT);
	GPIO c3_d(25 , GPIO::OUTPUT);
	GPIO c4_d(27 , GPIO::OUTPUT);

	GPIO l1_d(26 , GPIO::OUTPUT);
	GPIO l2_d(24 , GPIO::OUTPUT);
	GPIO l3_d(22 , GPIO::OUTPUT);
	GPIO l4_d(28 , GPIO::OUTPUT);

//----------------------------------------------------

	//led de teste
	GPIO led = GPIO(13, GPIO::OUTPUT);

	int currentState = 1;
	int ctl = false;
	char a = 'n';
	///// 1 - Idle, 2 - Online, 3 - Conf seq, 4 - Discar seq

	UART uart = UART(0, 9600, UART::NORMAL_SPEED, UART::DATABITS_8,UART::NONE, UART::STOPBIT_2);

	DTMF dtmf = DTMF(&c1_d,&c2_d,&c3_d,&c4_d,&l1_d,&l2_d, &l3_d,&l4_d);

	Keyboard teclado = Keyboard(&l1, &l2, &l3, &l4, &c1, &c2, &c3, &c4);

	LCD display = LCD();

	EEPROM eeprom;

	uint8_t * pos = 0;
	uint8_t * pos2 = pos + 10;
	uint8_t * pos3 = pos + 20;

	Fila <uint8_t, 10> fila;
	Fila <uint8_t, 10> fila2;
	Fila <uint8_t, 10> fila3;

	unsigned char sequencia[] = "123456789";
	for(unsigned int i = 0; i < sizeof(sequencia); i++){
		fila.enfileira(sequencia[i]);
	}

	unsigned char sequencia2[] = "eeeeeeeee";
	for(unsigned int i = 0; i < sizeof(sequencia2); i++){
		fila2.enfileira(sequencia2[i]);
	}

	unsigned char sequencia3[] = "eeeeeeeee";
	for(unsigned int i = 0; i < sizeof(sequencia3); i++){
		fila3.enfileira(sequencia3[i]);
	}

	eeprom.write_string(pos, fila);
	//eeprom.write_string(pos2, fila2);
	//eeprom.write_string(pos3, fila3);


	sei();

	display.LCD_Init();

	int print = 0;
	int controle = 0;
	while(1) {
		if (currentState == 1) { //idle
			if (print == 0) {
				display.LCD_Clear();
				display.LCD_String("Sel. Modo. A: On");	/* write string on 1st line of LCD*/
				display.LCD_Command(0xC0);		/* Go to 2nd line*/
				display.LCD_String("B:CSeq.   C:DSeq");	/* Write string on 2nd line*/
				print++;
			}

			while(teclado.Percorre()){
				led.toggle();
				_delay_ms(20);
			};
			a = teclado.retKey();

			switch(a) {
				case 'A':
					currentState = 2;
					uart.puts("Indo On");
					print = 0;
					break;
				case 'B':
					currentState = 3;
					uart.puts("Indo Cseq");
					print = 0;
					break;
				case 'C':
					currentState = 4;
					uart.puts("Indo Dseq");
					print = 0;
					break;
			}




		} else if (currentState == 2){ //discar online
			if(print == 0){
				display.LCD_Clear();
				display.LCD_String("Online. D:Voltar");
				display.LCD_Command(0xC0);
				print ++;
			}

			a = 'n';
			while(teclado.Percorre()){
				led.toggle();
				_delay_ms(20);
			};

			a = teclado.retKey();

			if(a == '*' or a == '#' or a == '0' or a == '1' or a == '2' or a == '3' or a == '4' or a == '5' or a == '6' or a == '7' or a == '8' or a == '9'){
				if(controle < 9){
					display.LCD_Char(a);
					dtmf.send(a);
					uart.puts("Discou: ");
					uart.put(a);
					controle ++;
				} else {
					//print = 0;
					display.LCD_Clear();
					display.LCD_String("Online. D:Voltar");
					display.LCD_Command(0xC0);
					display.LCD_Char(a);
					dtmf.send(a);
					uart.puts("Discou: ");
					uart.put(a);
					controle = 0;

				}

			} else if (a == 'D') {
				currentState = 1;
				uart.puts("Volt. Idle");
				print = 0;
				controle = 0;
			}

		} else if (currentState == 3){ //configurar sequencias
			uint8_t * _pos = 0;
			uint8_t * _pos2 = _pos+10;
			uint8_t * _pos3 = _pos+20;
			if(print == 0){
				display.LCD_Clear();
				display.LCD_String("Seq:");

				if(eeprom.read(_pos2) != 'e'){
					display.LCD_String("A:");
					for (uint8_t  i = 0; i < 9; i++){
						a = eeprom.read(_pos2);
						uart.put(a);
						display.LCD_Char(a);
						_pos2++;
						_delay_ms(500);
					}
					_pos = 0;
				} else {
					//display.LCD_Command(0xC0);
					display.LCD_String("A:Add ");
					ctl = false;

				}

				if(eeprom.read(_pos3) != 'e'){
					display.LCD_Command(0xC0);
					display.LCD_String("B:");
					for (uint8_t  i = 0; i < 9; i++){
						a = eeprom.read(_pos3);
						uart.put(a);
						display.LCD_Char(a);
						_pos3++;
						_delay_ms(500);
					}
					_pos = 0;
				} else {
					display.LCD_Command(0xC0);
					display.LCD_String("B:Add");
				}

				display.LCD_String("D:Vol");

				//display.LCD_Command(0xC0);
				print ++;
			}

			a = 'n';
			while(teclado.Percorre()){
				led.toggle();
				_delay_ms(20);
			};

			a = teclado.retKey();
			_pos = 0;
			_pos2 = _pos+10;
			_pos3 = _pos + 20;
			switch (a) {
				case 'A':
					addSeq(_pos2, teclado, eeprom, display);
					//currentState =1;
					//uart.puts("Voltando para Idle");
					print = 0;
					//controle = 0;
					break;

				case 'B':
					addSeq(_pos3, teclado, eeprom, display);
					//currentState =1;
					//uart.puts("Voltando para Idle");
					print = 0;
					//controle = 0;
					break;
				case 'D':
					currentState = 1;
					uart.puts("Volt. Idle");
					print = 0;
					controle = 0;
					break;
			}


		} else if (currentState == 4) { //discar sequencias
			//verificar sequencias, printar e discar
			uint8_t * _pos = 0;
			uint8_t * _pos2 = _pos+10;
			uint8_t * _pos3 = _pos+20;
			if(print == 0){
				display.LCD_Clear();
				display.LCD_String("Dseq:");
				if(eeprom.read(_pos2) != 'e'){
					display.LCD_String("A:");
					for (uint8_t  i = 0; i < 9; i++){
						a = eeprom.read(_pos2);
						uart.put(a);
						display.LCD_Char(a);
						//dtmf.send(a);
						_pos2++;
						_delay_ms(500);
					}
				_pos = 0;
				} else {
				//display.LCD_Command(0xC0);
				}

				if(eeprom.read(_pos3) != 'e'){
					display.LCD_Command(0xC0);
					display.LCD_String("B:");
					for (uint8_t  i = 0; i < 9; i++){
						a = eeprom.read(_pos3);
						uart.put(a);
						display.LCD_Char(a);
						//dtmf.send(a);
						_pos3++;
						_delay_ms(500);
					}
					_pos = 0;
				} else {
				display.LCD_Command(0xC0);
				}
				if(eeprom.read(_pos) != 'e'){
					display.LCD_Command(0xC0);
					display.LCD_String("C:");
					for (uint8_t  i = 0; i < 9; i++){
						a = eeprom.read(_pos);
						uart.put(a);
						display.LCD_Char(a);
						//dtmf.send(a);
						_pos++;
						_delay_ms(500);
					}
					_pos = 0;
				}
				display.LCD_String("D:Vol");

							//display.LCD_Command(0xC0);
							print ++;
						}

						a = 'n';
						while(teclado.Percorre()){
							led.toggle();
							_delay_ms(20);
						};
						a = teclado.retKey();
						_pos = 0;
						_pos2 = _pos+10;
						_pos3 = _pos + 20;
								switch (a) {
									case 'A':
										if(eeprom.read(_pos2) != 'e'){
										display.LCD_Clear();
										display.LCD_String("Discando");
										uart.puts("discando ");
										display.LCD_Command(0xC0);

										for (uint8_t  i = 0; i < 9; i++){
											a = eeprom.read(_pos2);
											uart.put(a);
											display.LCD_Char(a);
											dtmf.send(a);
											_pos2++;
											_delay_ms(500);
										}
										}
										_pos = 0;
										currentState = 1;
										//currentState =1;
										//uart.puts("Voltando para Idle");
										print = 0;
										//controle = 0;
										break;

									case 'B':
										if(eeprom.read(_pos3) != 'e'){
										display.LCD_Clear();
										display.LCD_String("Discando");
										uart.puts("discando ");
										display.LCD_Command(0xC0);
										for (uint8_t  i = 0; i < 9; i++){
											a = eeprom.read(_pos3);
											dtmf.send(a);
											uart.put(a);
											display.LCD_Char(a);
											_pos3++;
											_delay_ms(500);
										}
										}
										_pos = 0;
										currentState = 1;
										print = 0;
										//controle = 0;
										break;
									case 'C':
										if(eeprom.read(_pos) != 'e'){
										display.LCD_Clear();
										display.LCD_String("Discando");
										uart.puts("discando ");
										display.LCD_Command(0xC0);
										for (uint8_t  i = 0; i < 9; i++){
											a = eeprom.read(_pos);
											dtmf.send(a);
											uart.put(a);
											display.LCD_Char(a);

											_pos++;
											_delay_ms(500);
										}
										}
										_pos = 0;
										print = 0;
										currentState = 1;
									break;

									case 'D':
										currentState = 1;
										uart.puts("Volt.DSeq");
										print = 0;
										controle = 0;
										break;
								}

		}

}
}









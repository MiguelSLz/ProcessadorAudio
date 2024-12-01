#ifndef INTERFACE_H
#define INTERFACE_H
#include "FFT.cpp"
#include "Dados.cpp"
#include "LCD_display.cpp"


class Interface{
	bool botaoEsq, botaoDir, botaoOK;

public:
	Interface();
	bool getEsq();
	bool getDir();
	bool getOK();
	
	bool setEsq(bool valor);
	bool setDir(bool valor);
	bool setOK(bool valor);
	
	void montaContador(char str[], unsigned char contador);
	void montaBarra(char barraEq[], char volume);
	void runLcdUI();
};

#endif

#ifndef Interface_H
#define Interface_H
#include "Audio.cpp"


class Interface{
	bool botaoEsq, botaoDir, botaoOK;
	Audio gravacao;

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

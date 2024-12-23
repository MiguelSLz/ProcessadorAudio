#ifndef Interface_H
#define Interface_H
#include "Audio.h"


class Interface{
	bool botaoEsq, botaoDir, botaoOK;
	Audio gravacao;

public:
	Interface();
	bool getEsq();
	bool getDir();
	bool getOK();
	
	void setEsq(bool valor);
	void setDir(bool valor);
	void setOK(bool valor);
	
	void montaContador(char str[], unsigned char contador);
	void montaBarra(char barraEq[], char volume);
	void runLcdUI();
};

#endif
#ifndef Interface_H
#define Interface_H
#include "Audio.h"


class Interface{
	bool botaoEsq, botaoDir, botaoOK;
	long unsigned int counter;
	Audio gravacao;

public:
	Interface();
	bool getEsq();
	bool getDir();
	bool getOK();
	long unsigned int getCounter();
	
	void setEsq(bool valor);
	void setDir(bool valor);
	void setOK(bool valor);
	void setCounter(long unsigned int valor);

	void montaBarra(char barraEq[], signed char volume);
	void runLcdUI();
};

#endif
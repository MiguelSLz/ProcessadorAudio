//Dados.h
#ifndef Dados_H
#define Dados_H

#include "Interrupts.h"

class Dados{
	float *sinal;
public:
	void setupADC();
	void lerMic(); 
	float getsinal();
};

#endif // Dados_H
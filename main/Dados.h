//Dados.h
#ifndef Dados_H
#define Dados_H

#include "Interrupts.h"

class Dados{
	float *Sinal;
public:
	void setupADC();
	void LerMic(); 
};

#endif // Dados_H

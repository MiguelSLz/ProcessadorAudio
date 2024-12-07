//Dados.h
#ifndef Dados_H
#define Dados_H
#define NUM_AMOSTRAS 65536

#include "Interrupts.h"

class Dados{
	float audioData[NUM_AMOSTRAS];
	float *enderecoSinal;
	Interrupts Interruptor;
public:
	Dados();
	void lerMic(); 
	float* getSinal();
};

#endif // Dados_H
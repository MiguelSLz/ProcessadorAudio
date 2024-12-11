//Dados.h
#ifndef Dados_H
#define Dados_H
#define NUM_AMOSTRAS 65536

#include "Interrupts.h"

struct RegsGPIO
{
    unsigned long int *ENABLE;
    unsigned long int *OUT_W1TS;
    unsigned long int *OUT_W1TC;
};

class Dados{
	float audioData[NUM_AMOSTRAS];
	float *enderecoSinal;
	Interrupts Interruptor;
	RegsGPIO saidaPDM;
public:
	Dados();
	void IRAM_ATTR lerMic(); 
	float* getSinal();

	void IRAM_ATTR criarPDM();
	void IRAM_ATTR lerReproduzir();
};

#endif // Dados_H
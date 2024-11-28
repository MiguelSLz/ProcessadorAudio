//Dados.h
#ifndef Dados_H
#define Dados_H

#include "Interrupts.h"

class Dados{
	int *SinalIN;
	int *SinalOUT;
public:
    int LerMic(); 
};

#endif // Dados_H

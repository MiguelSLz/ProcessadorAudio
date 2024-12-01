#ifndef Effects_H
#define Effects_H
#include "Dados.h"

class Audio{

public:
    Audio();
    void EqualizerEffect(float *Sinal, char Volume);
    void ECOEffect(float *Sinal,char Volume);
};

#endif // Effects_H
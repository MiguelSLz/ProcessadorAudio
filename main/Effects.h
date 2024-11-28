#ifndef Effects_H
#define Effects_H
#include "Dados.cpp"
#include "FFT.cpp"

class Effects{
    Dados audio;
    FFT frequencia;
public:
    Effects();
    void Equalizer();
    void ECO();
};

#endif // Effects_H

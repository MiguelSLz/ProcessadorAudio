#ifndef Audio_H
#define Audio_H
#include "Dados.cpp"
#include "FFT.cpp"

class Audio{
    Dados data;
    FFT frequencia;
public:
    void gravar(unsigned char escolha, char forca, char volume[]);
    void aplicarEco(char forca);
    void aplicarEq(char volume[]);
    void reproduzirAudio();
};

#endif // Audio_H

#ifndef Audio_H
#define Audio_H
#include "Dados.h"
#include "FFT.h"
#include "LCD_display.h"

class Audio{
    Dados data;
    FFT frequencia;
public:
    void gravar(unsigned char escolha, char forca, signed char volume[]);
    void aplicarEco(char forca);
    void aplicarEqualizacaoLinear(signed char volume[]);
    void aplicarEqualizacaoGaussiana(signed char volume[]);
    void reproduzirAudio();
};

#endif // Audio_H
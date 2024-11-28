#ifndef FFT_H
#define FFT_H

#include "esp_dsp.h"

class FFT{

public:

    /*
        Ideias e sugestoes:

        Vc entende melhor como a FFT funciona exatamente, mas poderiamos ter funcoes tipo: 
        getFrequency();
        inverseFFT();

        acho que alem dos metodos podemos definir que a FFT tenha um atributo como:
        float espectroFrequencia[1024];
        para manipular e acessar... ai' podemos acessar esse buffer com um ponteiro la na classe Efeitos...
    */
    FFT(); 
};

#endif // FFT_H

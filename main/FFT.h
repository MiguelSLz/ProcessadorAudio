//FFT.h
#ifndef FFT_H
#define FFT_H

#include "esp_dsp.h"

class FFT{

public:
    FFT();
    void ExecuteFFT(float *Sinal);
    void AmplitudeFFT(float *Sinal);
};

#endif // FFT_H

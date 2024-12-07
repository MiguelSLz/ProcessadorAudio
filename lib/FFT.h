//FFT.h
#ifndef FFT_H
#define FFT_H

#include "esp_dsp.h"

class FFT{

public:
	FFT();
	void executeFFT(float *sinal);
	void fasorFFT(float *sinal);
	void retangularFFT(float *sinal);
	void iFFT(float *sinal);
};

#endif // FFT_H
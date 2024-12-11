//FFT.cpp
#include "FFT.h"
#include <math.h>
//NUM_AMOSTRAS = 65536 = 2^16 para poder ser processado na fft e considerando a taxa de amostragem utilizada, ter 8 segundos de audio
#define NUM_AMOSTRAS 65536

FFT::FFT() {
    dsps_fft2r_init_fc32(NULL, CONFIG_DSP_MAX_FFT_SIZE); // inicializa a biblioteca esp_dsp
}

void FFT::executeFFT(float *sinal){ // realiza a fft e organiza o sinal, sendo organizado com pares de valor real e imaginario para cada frequencia
									// cada amostra no dominio da freq (RE, IM) eh separada por 0,12207 Hz
	dsps_fft2r_fc32(sinal, NUM_AMOSTRAS); // realiza a fft
	dsps_bit_rev_fc32(sinal, NUM_AMOSTRAS); // organiza a fft
	
}
void FFT::fasorFFT(float *sinal){
	int i = 0;
	//calculo da amplitude sobrescrevendo no vetor
	for (i= 0; i < NUM_AMOSTRAS / 2; i++) {  // divisao por 2 pelo fato da fft ser simetrica
        float Re = sinal[2 * i];     
        float Im = sinal[2 * i + 1]; 
        sinal[2*i] = sqrt(Re * Re + Im * Im); // indice onde ficava os valores reais receberam o valor da amplitude
        sinal[2*i +1] = atan(Im/Re); // indice que continha os valores imaginarios receberam o valor da fase 
    }
}

void FFT::retangularFFT(float *sinal){ // transforma os fasores para forma quadratica

	for (int i = 0; i < NUM_AMOSTRAS / 2; i++) {
		
		float amplitude = sinal[2 * i];
		float fase = sinal[2 * i + 1];
		
		float Re = amplitude * cosf(fase);
		float Im = amplitude * sinf(fase);
		
		sinal[2*i] = Re;
		sinal[2*i + 1] = Im;
	}
}

void FFT::iFFT(float *sinal){ // sinal deve estar na forma retangular
	
	// Restaurando a Simetria do sinal
	int i = 1;
	for (i = 1; i < NUM_AMOSTRAS / 2; i++){
		sinal[2 * (NUM_AMOSTRAS - i)] = sinal[2 * i];       		// Copia a parte real
        sinal[2 * (NUM_AMOSTRAS - i) + 1] = -sinal[2 * i + 1]; 	// Inverte a parte imaginaria
	}
	
	// Executa a iFFT
    dsps_fft2r_fc32(sinal, NUM_AMOSTRAS); // FFT inversa
    dsps_bit_rev_fc32(sinal, NUM_AMOSTRAS); // Corrige a ordem dos valores
	
	// Normalizacao
	for (i = 0; i < NUM_AMOSTRAS; i++) {
        sinal[i] /= NUM_AMOSTRAS;
    }
	
}

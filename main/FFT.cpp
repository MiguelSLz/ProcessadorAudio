//FFT.cpp
#include "FFT.h"
#include <math.h>
//NumAmostras = 65536 = 2^16 para poder ser processado na fft e considerando a taxa de amostragem utilizada, ter 8 segundos de audio
#define NumAmostras 65536 

FFT::FFT() {
    dsps_fft2r_init_fc32(NULL, CONFIG_DSP_MAX_FFT_SIZE); // inicializa a biblioteca esp_dsp
}

void FFT::ExecuteFFT(float *Sinal){ // realiza a fft e organiza o sinal, sendo organizado com pares de valor real e imaginario para cada frequencia
									// cada amostra no dominio da freq (RE, IM) eh separada por 0,12207 Hz
	dsps_fft2r_fc32(Sinal, NumAmostras); // realiza a fft
	dsps_bit_rev_fc32(Sinal, NumAmostras); // organiza a fft
	
}
void FFT::FasorFFT(float *Sinal){
	int i=0;
	//calculo da amplitude sobrescrevendo no vetor
	for ( i= 0; i < NumAmostras / 2; i++) {  // divisao por 2 pelo fato da fft ser simetrica
        float Re = Sinal[2 * i];     
        float Im = Sinal[2 * i + 1]; 
        Sinal[2*i] = sqrt(Re * Re + Im * Im); // indice onde ficava os valores reais receberam o valor da amplitude
        Sinal[2*i +1] = atan(Im/Re); // indice que continha os valores imaginarios receberam o valor da fase 
    }

	for (; i < NumAmostras; i++){ // definindo como 0 o restante dos valores que agora nao serao mais utilizados
		Sinal[i] = 0;
	}
}

void FFT::QuadraticaFFT(float *Sinal){ // transforma os fasores para forma quadratica
	int i=0;
	for ( i= 0; i < NumAmostras / 2; i++) {
		
		float Amplitude = Sinal[i];
		float Fase = Sinal[i+1];
		
		float Re = Amplitude * cosf(Fase);
		float Im = Amplitude * sinf(Fase);
		
		Sinal[i] = Re;
		Sinal[i+1] = Im;
	}
	for (; i < NumAmostras; i++){
		Sinal[i] = 0;
	}
}

void FFT::iFFT(float *Sinal){ // Sinal deve estar na forma quadratica
	
	// Restaurando a Simetria do Sinal
	
	int i=1;
	for (i=1; i < NumAmostras / 2; i++){
		
		Sinal[2 * (NumAmostras - i)] = Sinal[2 * i];       		// Copia a parte real
        Sinal[2 * (NumAmostras - i) + 1] = -Sinal[2 * i + 1]; 	// Inverte a parte imaginaria
        
	}
	
	// Executa a iFFT
	
    dsps_fft2r_fc32(Sinal, NumAmostras); // FFT inversa
    dsps_bit_rev_fc32(Sinal, NumAmostras); // Corrige a ordem dos valores
	
	// Normalizacao
	
	for (i = 0; i < NumAmostras; i++) {
        Sinal[i] /= NumAmostras;
    }
	
}
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
	dsps_fft2r_fc32(Sinal, NumAmostras);
	dsps_bit_rev_fc32(Sinal, NumAmostras);
	
}
void FFT::AmplitudeFFT(float *Sinal){
	int i=0;
	//calculo da amplitude sobrescrevendo no vetor
	for ( i= 0; i < NumAmostras / 2; i++) {  // divisao por 2 pelo fato da fft ser simetrica
        float Re = Sinal[2 * i];     
        float Im = Sinal[2 * i + 1]; 
        Sinal[2*i] = sqrt(Re * Re + Im * Im); // indice onde ficava os valores reais receberam o valor da amplitude
        Sinal[2*i +1] = 0; // indice que continha os valores imaginarios receberam o valor 0 
    }

	for (; i < NumAmostras; i++){ // definindo como 0 o restante dos valores que agora nao serao mais utilizados
		Sinal[i] = 0;
	}
}
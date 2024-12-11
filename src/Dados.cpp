//Dados.cpp
#include "Dados.h"
#include "driver/adc_types_legacy.h"
#include "hal/adc_types.h"
#include "driver/adc.h"
#include <stdint.h>
#include <math.h>
//NUM_AMOSTRAS = 65536 = 2^16 para poder ser processado na fft e considerando a taxa de amostragem utilizada, ter 8 segundos de audio
#define NUM_AMOSTRAS 65536
#define OVERSAMPLING_COUNTER 3

#define GPIO_ENABLE_REG 0x60004020
#define GPIO_OUT_W1TS_REG 0x60004008
#define GPIO_OUT_W1TC_REG 0x6000400C


Dados::Dados(){
	// Inicializa o ponteiro
	enderecoSinal = audioData;
	
	// Configurando o ADC
	adc1_config_width(ADC_WIDTH_BIT_12);  // palavra de processamento do ADC
	adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_12);

	// Habilita GPIO9 como saida
	saidaPDM.ENABLE = (unsigned long int*) GPIO_ENABLE_REG;
	saidaPDM.OUT_W1TS = (unsigned long int*) GPIO_OUT_W1TS_REG;
	saidaPDM.OUT_W1TC = (unsigned long int*) GPIO_OUT_W1TC_REG;
	*saidaPDM.ENABLE = (1 << 10);
	*saidaPDM.OUT_W1TC = (1 << 10);
}

void Dados::lerMic(){
	unsigned int i = 0;
	unsigned char counter = 0;

	Interruptor.configTimer();

	// escolha do while ao inves do for foi para apenas contar o numero de amostras quando for lido uma amostra (acontece a cada 125ms)
	while(i < NUM_AMOSTRAS){ // i indo ate 65536 porque eh igual a 2^16, resultando na potencia de 2 mais proxima que resulte em 8 segundos de audio

		if(Interruptor.getTimerFlag()){ // verdade a cada 31,25 us
			counter++;
			Interruptor.clearTimerFlag();
			if(counter >= OVERSAMPLING_COUNTER){
				counter = 0;
				audioData[i] = adc1_get_raw(ADC1_CHANNEL_4);
				Interruptor.clearTimerFlag();
				i++;
			}
		}
		
	}

	Interruptor.stopTimer();
}

float* Dados::getSinal(){
	return enderecoSinal;
}

void Dados::criarPDM(){
	unsigned int i = 0;
	int integrator = 0, feedback = 0;
	unsigned char counter = 0;

	Interruptor.configTimer();

	// escolha do while ao inves do for foi para apenas contar o numero de amostras quando for lido uma amostra (acontece a cada 125ms)
	while(i < NUM_AMOSTRAS){ // i indo ate 65536 porque eh igual a 2^16, resultando na potencia de 2 mais proxima que resulte em 8 segundos de audio

		if(Interruptor.getTimerFlag()){ // verdade a cada 31,25 us
			Interruptor.clearTimerFlag();
			counter++;
			integrator += (int)audioData[i] - feedback;
			
			if(integrator >= 2048){
				feedback = 4095;
				*saidaPDM.OUT_W1TS = (1 << 10);
			}
			else{
				feedback = 0;
				*saidaPDM.OUT_W1TC = (1 << 10);
			}
			if(counter >= OVERSAMPLING_COUNTER){
				counter = 0;
				i++;
			}
		}
		
	}
	i = 0;
	integrator = 0;
	feedback = 0;
	counter = 0;
	*saidaPDM.OUT_W1TC = (1 << 10);
	Interruptor.stopTimer();
}

void Dados::lerReproduzir(){
	unsigned int i = 0;
	int integrator = 0, feedback = 0;
	unsigned char counter = 0;

	Interruptor.configTimer();

	// pega o primeiro sinal
	if(Interruptor.getTimerFlag()){
		audioData[i] = adc1_get_raw(ADC1_CHANNEL_4);
		Interruptor.clearTimerFlag();
		i++;
	}

	// escolha do while ao inves do for foi para apenas contar o numero de amostras quando for lido uma amostra (acontece a cada 125ms)
	while(i < NUM_AMOSTRAS){ // i indo ate 65536 porque eh igual a 2^16, resultando na potencia de 2 mais proxima que resulte em 8 segundos de audio

		if(Interruptor.getTimerFlag()){ // verdade a cada 31,25 us
			Interruptor.clearTimerFlag();
			counter++;
			integrator += (int)audioData[i - 1] - feedback;
			
			if(integrator >= 2200){
				feedback = 4095;
				*saidaPDM.OUT_W1TS = (1 << 10);
			}
			else{
				feedback = 0;
				*saidaPDM.OUT_W1TC = (1 << 10);
			}
			if(counter >= OVERSAMPLING_COUNTER){
				counter = 0;
				audioData[i] = adc1_get_raw(ADC1_CHANNEL_4);
				i++;
			}
		}
		
	}
	i = 0;
	integrator = 0;
	feedback = 0;
	counter = 0;
	*saidaPDM.OUT_W1TC = (1 << 10);
	Interruptor.stopTimer();
}
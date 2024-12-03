//Dados.cpp
#include "Dados.h"
#include "driver/adc_types_legacy.h"
#include "hal/adc_types.h"
#include "driver/adc.h"
#include <stdint.h>

Dados::Dados(){
	Interruptor.configTimer();
	
	// Configurando o ADC
	adc1_config_width(ADC_WIDTH_BIT_12);  // palavra de processamento do ADC
	adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_12);
}

void Dados::lerMic(){
	unsigned int i = 0;
	float amostra;

	// escolha do while ao inves do for foi para apenas contar o numero de amostras quando for lido uma amostra (acontece a cada 125ms)
	while(i < NUM_AMOSTRAS){ // i indo ate 65536 porque eh igual a 2^16, resultando na potencia de 2 mais proxima que resulte em 8 segundos de audio
			
		switch(Interruptor.getTimerFlag()){ // verdade a cada 0,125 ms
			case true:	
			amostra = adc1_get_raw(ADC1_CHANNEL_4);
			audioData[i] = amostra;
				
			Interruptor.clearTimerFlag();
			i++;
			break;

			// nao faz nada caso o timer nao dispare
			case false:
			break;
		}
		
	}
}

float* Dados::getSinal(){
	return *enderecoSinal;
}

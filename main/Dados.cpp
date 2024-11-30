//Dados.cpp
#include "Dados.h"
#include "driver/adc_types_legacy.h"
#include "hal/adc_types.h"
#include "driver/adc.h"
#include <stdint.h>

void Dados::setupADC(){
	Interrupts Interruptor;
	Interruptor.configTimer();
	
	// Configurando o ADC
	adc1_config_width(ADC_WIDTH_BIT_12);  // palavra de processamento do ADC
	adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_12);
}

void Dados::LerMic(){
	unsigned int NumAmostras=0;
	// escolha do while true com o break ao inves do for foi para apenas contar o numero de amostras quando for lido uma amostra (acontece a cada 125ms)
	while(true){ // NumAmostras indo ate 65536 porque eh igual a 2^16, resultando na potencia de 2 mais proxima que resulte em 8 segundos de audio
			
		if(Interruptor.getTimerFlag()){ // verdade a cada 0,125 ms
				
			float amostra = adc1_get_raw(ADC1_CHANNEL_4);
			Sinal[NumAmostras] = amostra;
				
			Interruptor.clearTimerFlag();
			NumAmostras++;
		}
		
		if (NumAmostras == 65536){
			break; // sai do loop quando foram lidas 65536 amostras
		}
	}
}

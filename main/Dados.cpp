//Dados.cpp
#include "Dados.h"
#include "driver/adc_types_legacy.h"
#include "hal/adc_types.h"
#include "driver/adc.h"
#include <stdint.h>
 
int Dados::LerMic(){ 			// talvez seja interessante separar a parte do codigo antes do while
	Interrupts Interruptor;
	Interruptor.configTimer();
	
	// Configurando o ADC
	adc1_config_width(ADC_WIDTH_BIT_12);  // palavra de processamento do ADC
	adc1_config_channel_atten(ADC1_CHANNEL_2, ADC_ATTEN_DB_12);
	
	int NumAmostras=0; // contador
	while(true){ // substituir true por algo que indique que o botao esta pressionado
			
		if(Interruptor.getTimerFlag()){ // verdade a cada 0,125 ms
				
			uint16_t amostra = adc1_get_raw(ADC1_CHANNEL_2);
			SinalIN[NumAmostras] = amostra;
				
			Interruptor.clearTimerFlag();
			NumAmostras++;
		}
	}
	return NumAmostras;
}
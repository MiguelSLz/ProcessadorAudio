// Audio.cpp
#include "Audio.h"
#define NUM_AMOSTRAS 65536
#define ATTENUATION1 0.35
#define ATTENUATION2 0.5
#define ATTENUATION3 0.65

void Audio::gravar(unsigned char escolha, char forca, char volume[]){
	
	data.lerMic();

	LCD_escreve_strings("Processando...", "");
	
	switch(escolha){
		// SEM EFEITOS
		case 1:
			// nada
		break;

		// ECO
		case 2:
			aplicarEco();
		break;

		// EQUALIZACAO
		case 3:
			aplicarEq();
		break;
	}
}

void Audio::aplicarEq(char volume[]){

}

void Audio::aplicarEco(char forca){ // Volume representa a intensidade do eco
	int i;
	float *sinal;

	sinal = data.getSinal();

	switch (forca) {
		
		case 1:
			for(int i=4000; i< NUM_AMOSTRAS; i++){ // a contagem comeca em 4000 (0.5s) para ter tempo de comecar o eco
				sinal[i] = sinal[i] + ATTENUATION2 * sinal[i - 4000];
			}
			break;
			
		case 2: // Como ha' mais de um eco foi necessario percorrer o vetor de tras para frente
			for(i=NUM_AMOSTRAS - 1 ; i >= 4000; i--){ // 0.25s -> 0.5s ( 1 eco)
				
				sinal[i] += ATTENUATION2 * sinal[i - 2000];
                
                if (i >= 4000) {					// 0.5s -> fim do audio ( 2 ecos )
                    sinal[i] += ATTENUATION1 * sinal[i - 4000];
                }
                
			}
			break;
		case 3: // 3 ecos
			for (int i = NUM_AMOSTRAS - 1; i >= 6000; i--) { // 0.25s, 0.5s e 0.75s de atraso
                sinal[i] += ATTENUATION3 * sinal[i - 2000];
                sinal[i] += ATTENUATION2 * sinal[i - 4000];
                sinal[i] += ATTENUATION1 * sinal[i - 6000];
            }
            for (int i = 5999; i >= 4000; i--) { // Apenas 2 ecos
                sinal[i] += ATTENUATION3 * sinal[i - 2000];
                sinal[i] += ATTENUATION2 * sinal[i - 4000];
            }
            for (int i = 3999; i >= 2000; i--) { // Apenas 1 eco
                sinal[i] += ATTENUATION3 * sinal[i - 2000];
            }
            break;
		default: // caso 2
			for(i=NUM_AMOSTRAS -1 ; i >= 4000; i--){ // 0.25s -> 0.5s ( 1 eco)
				
				sinal[i] += ATTENUATION2 * sinal[i - 2000];
                
                if (i >= 4000) {					// 0.5s -> fim do audio ( 2 ecos )
                    sinal[i] += ATTENUATION1 * sinal[i - 4000];
                }
                
			}
	}
	
}

void Audio::reproduzirAudio(){
	float *sinal;

	sinal = data.getSinal();

	// configurar I2C aqui
}

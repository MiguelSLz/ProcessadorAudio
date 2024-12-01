// Audio.cpp
#include "Audio.h"
#define NumAmostras 65536
#define Attenuation1 0.35
#define Attenuation2 0.5
#define Attenuation3 0.65

void Audio::ECOEffect(float *Sinal, char Volume){ // Volume representa a intensidade do eco
	int i;
	switch (Volume) {
		
		case 1:
			for(int i=4000; i< NumAmostras; i++){ // a contagem comeca em 4000 (0.5s) para ter tempo de comecar o eco
				Sinal[i] = Sinal[i] + Attenuation2 * Sinal[i - 4000];
			}
			break;
			
		case 2: // Como ha mais de um eco foi necessario percorrer o vetor de tras para frente
			for(i=NumAmostras -1 ; i >= 4000; i--){ // 0.25s -> 0.5s ( 1 eco)
				
				Sinal[i] += Attenuation2 * Sinal[i - 2000];
                
                if (i >= 4000) {					// 0.5s -> fim do audio ( 2 ecos )
                    Sinal[i] += Attenuation1 * Sinal[i - 4000];
                }
                
			}
			break;
		case 3: // 3 ecos
			for (int i = NumAmostras - 1; i >= 6000; i--) { // 0.25s, 0.5s e 0.75s de atraso
                Sinal[i] += Attenuation3 * Sinal[i - 2000];
                Sinal[i] += Attenuation2 * Sinal[i - 4000];
                Sinal[i] += Attenuation1 * Sinal[i - 6000];
            }
            for (int i = 5999; i >= 4000; i--) { // Apenas 2 ecos
                Sinal[i] += Attenuation3 * Sinal[i - 2000];
                Sinal[i] += Attenuation2 * Sinal[i - 4000];
            }
            for (int i = 3999; i >= 2000; i--) { // Apenas 1 eco
                Sinal[i] += Attenuation3 * Sinal[i - 2000];
            }
            break;
		default: // caso 2
			for(i=NumAmostras -1 ; i >= 4000; i--){ // 0.25s -> 0.5s ( 1 eco)
				
				Sinal[i] += Attenuation2 * Sinal[i - 2000];
                
                if (i >= 4000) {					// 0.5s -> fim do audio ( 2 ecos )
                    Sinal[i] += Attenuation1 * Sinal[i - 4000];
                }
                
			}
	}
	
}
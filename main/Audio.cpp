// Audio.cpp
#include "Audio.h"
#include<math.h>

#define FREQ_BASE 50
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
			aplicarEqualizacaoGaussiana();
		break;
	}
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

/*
	volume[]
	Index	Freq
	0		50Hz
	1		100Hz
	2		200Hz
	3		400Hz
	4		800Hz
	5		1600Hz
	6		3200Hz

	sinal[] (fft processada)
	Index		Freq
	0			0Hz
	1			~0,12Hz
	2			~0,24Hz
	...
	410			~50Hz
	819			~100Hz
	1638		~200Hz
	3277		~400Hz
	6554		~800Hz
	13107		~1600Hz
	26214		~3200Hz
	...
	65535		8000Hz

	sera necessaria uma conversao que onde:
	entrada		saida
	0			410
	1			819
	2			1638
	3			3277
	4			6554
	5			13107
	6			26214
*/

/*
	tambem e' necessaria uma funcao matematica que aumente ou diminua o valor apenas ao redor da frequencia
	desejada com uma queda exponencial ao redor...

	digamos que queremos que algo no estilo:
	
	Volume
		^
	+3|           
	+2|          /\
	+1|         /  \ 
	+0|________/    \_________
	-1|
	-2|
	-3|----------|------------> Freq.(f)
	//   Freq. desejada (F)
	
	A curva do equalizador poderia ser modelada por duas linhas retas que iniciam e acabam em algum valor
	proporcional à F, como começar em 0.5*F e terminar em 1.5*F

	Alternativamente, podemos modelar usando a seguinte funcao baseada na curva gaussiana: 
	volume * e^(-(f - F)^2/((0.35 * F)^2))

	para decidir detalhes de parametros dessas funcoes, o Geogebra foi utilizado para modelar algumas situacoes
*/

void Audio::aplicarEqualizacaoLinear(char[] volume){
	unsigned short int indexFftFreq[7] = {410, 819, 1638, 3277, 6554, 13107, 26214};
	float *sinal;
	float modeloLinear = 0;

	sinal = data.getSinal();

	frequencia.executeFFT(sinal);
	frequencia.fasorFFT(sinal);

	

	for(unsigned short int i = 0; i < NUM_AMOSTRAS / 2; i++){
		
		for(unsigned short int j = 0; j < 7; j++){
			// parametros escolhidos atraves de modelagem no Geogebra
			if((i > 0.5*indexFftFreq[j]) && (i <= indexFftFreq[j])){
				modeloLinear += (volume[j] * (i - 0.5*indexFftFreq[j])) / (0.5*indexFftFreq[j]);
				
				// acumula-se aditivamente a influencia de cada faixa de frequencia
				modeloLinear += modeloLinear;
			}
			else if ((i > indexFftFreq[j]) && (i < 1.5*indexFftFreq[j])){
				modeloLinear += -(volume[j] * (i - 1.5*indexFftFreq[j])) / (0.5*indexFftFreq[j]);
				
				// acumula-se aditivamente a influencia de cada faixa de frequencia
				modeloLinear += modeloLinear;
			}
		}
		// aplicando um fato de correcao ao modelo para que ele nao abaixe ou aumente demais o volume
		modeloLinear = (modeloLinear / 10) + 1;

		sinal[2*i] = modeloLinear * sinal[2*i];

		modeloLinear = 0;
	}

}

void Audio::aplicarEqualizacaoGaussiana(char[] volume){
	unsigned short int indexFftFreq[7] = {410, 819, 1638, 3277, 6554, 13107, 26214};
	float *sinal;
	float modeloGaussiano = 0, expoente = 0;

	sinal = data.getSinal();

	frequencia.executeFFT(sinal);
	frequencia.fasorFFT(sinal);

	

	for(unsigned short int i = 0; i < NUM_AMOSTRAS / 2; i++){
		
		for(unsigned short int j = 0; j < 7; j++){
			// parametros escolhidos atraves de modelagem no Geogebra
			expoente = -(pow(i - indexFftFreq[j], 2)) / (pow(0.35 * indexFftFreq[j], 2));
			
			// acumula-se aditivamente a influencia de cada faixa de frequencia
			modeloGaussiano += volume[j] * exp(expoente);
		}
		// aplicando um fato de correcao ao modelo para que ele nao abaixe ou aumente demais o volume
		modeloGaussiano = (modeloGaussiano / 10) + 1;

		sinal[2*i] = modeloGaussiano * sinal[2*i];

		modeloGaussiano = 0;
	}
}

void Audio::reproduzirAudio(){
	float *sinal;

	sinal = data.getSinal();

	// configurar I2C aqui
}

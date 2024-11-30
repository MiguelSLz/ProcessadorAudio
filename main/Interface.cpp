#include "Interface.h"
#include<stdlib.h>

#define FREQBASE 125

// Variaveis globais
unsigned char contadorBotao = 1;
bool flagInterrupt = false;

// Funcoes


// Definicao de metodos da classe Interface
Interface::Interface(){
  state = 0;
  botaoOK = 0;
}

unsigned char Interface::getState(){ return state; }
void Interface::setState(unsigned char newState){ state = newState; }
bool Interface::getOK{ return botaoOK; }
void Interface::setOK(bool valor){ botaoOK = valor; }
void Interface::montaContador(char str[], unsigned char contador){
	unsigned char tamanho = 0, i = 0;
	char[1] a;
	
	// descobre quantos caracteres a string tem
	while(str[tamanho] != '\0'){
			tamanho++;
	}
	
	// adiciona espacos 'a string
	for(i = 0; i < (16 - tamanho); i++){
		str[tamanho+i] = ' ';
	}

	//traduz o numero contador para um caractere
	sprintf(a, "%d", contador);
	
	// adiciona o contador ao ultimo espaco do LCD e coloca o caratere nulo de volta no novo final da string
	str[15] = char(numero);
	str[16] = '\0';
}
void Interface::montaBarra(char barraEq[], unsigned char valor, char volume){
	
}


// Metodo mais importante de Interface
	/* 
		-Leo: O QUE E O STATE?
		
		ele define em qual menu estamos
		
		state = 0
		primeiro menu da Interface, pergunta se o usuario quer:
		escolhaEfeito = 1 - Nenhum efeito
		escolhaEfeito = 2 - Eco
		escolhaEfeito = 3 - Equalizacao
		
		state = 1
		"Gravando..."
		e executa de fato o efeito escolhido (se um foi escolhido)
		
		state = 2
		Menu que configura a forca do eco
		
		state = 3
		Menu que configura as frequencias da equalizacao
		
		state = 4
		da opcao de dar play e replay e de voltar ao comeco do programa (apagando dados anteriores)
	*/
	
	/*
		Os ifs tao mostrando a mensagem uma vez, enquanto os whiles tao rodando um loop que espera
		algum interrupt mudar o valor de botaoOK para verdadeiro
	*/


void Interface::runLcdUI(){
	// variavel a ser manipulada para adicionar
	char str[17], barraEq[17], volumeEq[6];
	
	
	//LCD_inicializa_4_bits(char rs, char en, char d4, char d5, char d6, char d7);
	LCD_inicializa_4_bits(27, 28, 0, 1, 2, 3);
	
	while(true){


		if(state == 0){
			str = "Selecione:";
			montaContador(str, contadorBotao);
			LCD_escreve_strings(str, "1-N. 2-Eco 3-Eq.");
		}
		while(state == 0){
			if(flagInterrupt){

				str = "2-Eco 3-Eq.";
				montaContador(str, contadorBotao);
				LCD_escreve_strings("1-Sem efeitos", str);
				
				if(botaoOK){
					state = contadorBotao;
					escolhaEfeito = contadorBotao;
				}
			}//end if
		}//end while(0)
		


		if(state == 1){
			LCD_escreve_strings("Gravando...", "");
			//metodoEfeito(escolhaEfeito, forcaEfeito);
		}
		


		if(state == 2){
			str = "Forca do eco:";
			montaContador(str, contadorBotao);
			LCD_escreve_strings(str, "1 2 3; 0-Voltar");
		}
		while(state == 2){
			if(flagInterrupt){

				str = "1 2 3";
				montaContador(str, contadorBotao);
				LCD_escreve_strings("Forca do eco:", str);

				if(botaoOK){
					state = 1;
					// forcaEfeito = contadorBotao;
				}

			}//end if
		}//end while(2)
		


		if(state == 3){
			str = "";
			sprintf(str, "%dHz", FREQ_BASE*1);
			montaContador(str, contadorBotao);

			barraEq = "       /       ";
			LCD_escreve_strings(str,);
		}
		while(state == 3){
			if(flagInterrupt){

				str = "1 2 3";
				montaContador(str, contadorBotao);
				LCD_escreve_strings("Forca do eco:", str);

				if(botaoOK){
					state = 1;
					// forcaEfeito = contadorBotao;
				}
			}
		}//end while(3)
		


		if(state == 4){
			// envia msg que mostra opcoes do menu 4
		}
		while(state == 4){
			if(flagInterrupt){

			}//end if
		}//end while(4)
	} //end while(true)
} //end runLcdUI()

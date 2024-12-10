#include "Interface.h"
#include "LCD_display.h"
#include <stdio.h>

#define FREQ_BASE 50
#define DELAY_MS 20

static void delay(int ms){
  for(volatile int i = 0; (i < ms*1000); i++);
}

// Definicao de metodos da classe Interface
Interface::Interface(){
  botaoEsq = false;
  botaoDir = false;
  botaoOK = false;
  counter = 10;
  LCD_inicializa_4_bits(20, 21, 0, 1, 2, 3);
}

bool Interface::getEsq(){ return botaoEsq; }
bool Interface::getDir(){ return botaoDir; }
bool Interface::getOK(){ return botaoOK; }
long unsigned int Interface::getCounter(){ return counter; }

void Interface::setEsq(bool valor){ botaoEsq = valor; }
void Interface::setDir(bool valor){ botaoDir = valor; }
void Interface::setOK(bool valor){ botaoOK = valor; }
void Interface::setCounter(long unsigned int valor){ counter = valor; }

void Interface::montaBarra(char barraEq[], signed char volume){
	char numChar[4];
	
	for(signed char i = 0; i < 13; i++){
		if((volume < 0) && (i < (6 + volume))){
			barraEq[i] = '-';
		}
		else if((volume < 0) && (i == (6 + volume))){
			barraEq[i] = '<';
		}
		else if((volume < 0) && (i > (6 + volume)) && (i < 6)){
			barraEq[i] = '=';
		}
		else if(!(volume < 0) && (i < 6)){
			barraEq[i] = '-';
		}
		else if(i == 6){
			barraEq[i] = '|';
		}
		else if((volume > 0) && (i < (6 + volume))){
			barraEq[i] = '=';
		}
		else if((volume > 0) && (i == (6 + volume))){
			barraEq[i] = '>';
		}
		else if((volume > 0) && (i > (6 + volume))){
			barraEq[i] = '-';
		}
		else if(!(volume > 0) && (i > 6)){
			barraEq[i] = '-';
		}
	}

	barraEq[13] = '/';

	if(volume < 0){
		sprintf(numChar, "%d", -volume);
		barraEq[14] = '-';
		barraEq[15] = numChar[0];
	}
	else{
		sprintf(numChar, "%d", volume);
		barraEq[14] = '+';
		barraEq[15] = numChar[0];
	}
	barraEq[16] = '\0';
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
		da opcao de dar play e replay e de voltar ao comeco do programa

  		state = 5
    		"Reproduzindo..."
	*/
	
	/*
		Os ifs tao mostrando a mensagem uma vez, enquanto os whiles tao rodando um loop que espera
		algum interrupt mudar o valor de botaoOK para verdadeiro
	*/


void Interface::runLcdUI(){
	// variavel a ser manipulada para adicionar
	unsigned char state = 0, menuPage = 1, escolhaEfeito = 1, forcaEco = 1;
	char str[17], barraEq[17];
	signed char volumeEq[7] = {0, 0, 0, 0, 0, 0};
	unsigned char multiploFreqBase[7] = {1, 2, 4, 8, 16, 32, 64};
	bool volumeSelect = false;
	
	//LCD_inicializa_4_bits(char rs, char en, char d4, char d5, char d6, char d7);
	
	while(true){

		// ===== MENU ESCOLHA =====
		if(state == 0){
			menuPage = 1;
			LCD_escreve_strings((char*)"Selecione:", (char*)"1. Nenhum efeito");
		}
		while(state == 0){
			if(botaoEsq || botaoDir || botaoOK){

				// tratamento dos botoes
				if(botaoEsq){
						if(menuPage <= 1){
							menuPage = 1;
						}
						else{
							menuPage--;
						}
						botaoEsq = false;
					}
					else if(botaoDir){
						if(menuPage >= 3){
							menuPage = 3;
						}
						else{
							menuPage++;
						}
						botaoDir = false;
					}
					else{
						state = menuPage;
						escolhaEfeito = menuPage;
						botaoOK = false;
					}
					

				// mostra o menu de acordo com a pagina
				switch(menuPage){
					case 1:
					LCD_escreve_strings((char*)"Selecione:", (char*)"1. Nenhum efeito");
					break;

					case 2:
					LCD_escreve_strings((char*)"Selecione:", (char*)"2. Eco");
					break;

					case 3:
					LCD_escreve_strings((char*)"Selecione:", (char*)"3. Equalizacao");
					break;
				}

			}//end if botaoEsq || botaoDir || botaoOK
			counter++;
			delay(DELAY_MS);
		}//end while(0)
		


		// ===== TELA DE GRAVACAO =====
		if(state == 1){
			LCD_escreve_strings((char*)"Gravando...", (char*)" ");
			//gravacao.gravar(escolhaEfeito, forcaEco, volumeEq);
		}//end if 1
		


		// ===== MENU ECO =====
		if(state == 2){
			menuPage = 1;
			LCD_escreve_strings((char*)"Escolha a forca:", (char*)"1. Eco fraco");
		}
		while(state == 2){
			if(botaoEsq || botaoDir || botaoOK){
				
				// tratamento dos botoes
				if(botaoEsq){
						if(menuPage <= 0){
							menuPage = 0;
						}
						else{
							menuPage--;
						}
						botaoEsq = false;
					}
					else if(botaoDir){
						if(menuPage >= 3){
							menuPage = 3;
						}
						else{
							menuPage++;
						}
						botaoDir = false;
					}
					else{
						if(menuPage == 0){
							state = 0;
						}
						else{
							state = 1;
							escolhaEfeito = 2;
							forcaEco = menuPage;
						}
						botaoOK = false;
						
					}
					

				// mostra o menu de acordo com a pagina
				switch(menuPage){
					case 0:
					LCD_escreve_strings((char*)"Pressione OK", (char*)"para voltar");
					break;

					case 1:
					LCD_escreve_strings((char*)"Escolha a forca:", (char*)"1. Eco fraco");
					break;

					case 2:
					LCD_escreve_strings((char*)"Escolha a forca:", (char*)"2. Eco mediano");
					break;

					case 3:
					LCD_escreve_strings((char*)"Escolha a forca:", (char*)"3. Eco forte");
					break;
				}

			}//end if
			counter++;
			delay(DELAY_MS);
		}//end while(2)
		


		// ===== MENU EQUALIZACAO =====
		if(state == 3){
			// primeira pagina sera a frequencia base e seu volume
			menuPage = 1;

			sprintf(str, "%dHz", (FREQ_BASE * multiploFreqBase[menuPage - 1]));
			montaBarra(barraEq, volumeEq[menuPage - 1]);
			LCD_escreve_strings(str, barraEq);
		}
		while(state == 3){
			if(botaoEsq || botaoDir || botaoOK){
				
				// tratamento dos botoes com respeito ao volume estar selecionado ou nao e as condicoes atuais de pagina e volume
				// EDICAO DE VOLUME SELECIONADA
				if(volumeSelect){
					if(botaoEsq){
						if(volumeEq[menuPage - 1] <= -6){
							volumeEq[menuPage - 1] = -6;
						}
						else{
							volumeEq[menuPage - 1]--;
						}
						botaoEsq = false;
					}
					else if(botaoDir){
						if(volumeEq[menuPage - 1] >= 6){
							volumeEq[menuPage - 1] = 6;
						}
						else{
							volumeEq[menuPage - 1]++;
						}
						botaoDir = false;
					}
					else{
						volumeSelect = false;
						botaoOK = false;
					}
				}//end if volumeSelect
				// EDICAO DE VOLUME NAO SELECIONADA
				else{
					if(botaoEsq){
						if(menuPage <= 0){
							menuPage = 0;
						}
						else{
							menuPage--;
						}
						botaoEsq = false;
					}
					else if(botaoDir){
						if(menuPage > 7){
							menuPage = 8;
						}
						else{
							menuPage++;
						}
						botaoDir = false;
					}
					else{
						if(menuPage <= 0){
							state = 0;
						}
						else if(menuPage > 7){
							state = 1;
							escolhaEfeito = 3;
						}
						else{
							volumeSelect = true;
						}
						botaoOK = false;
					}
				}//end else

				// mostra o menu correspondente 'a pagina atual
				if(menuPage <= 0){

					LCD_escreve_strings((char*)"Pressione OK", (char*)"para voltar");

				}//end if menuPage <= 0

				else if(menuPage > 7){

					LCD_escreve_strings((char*)"Pressione OK", (char*)"para gravar");

				}//end elseif menuPage > 7

				else if(!volumeSelect){
					
					sprintf(str, "%dHz", FREQ_BASE * multiploFreqBase[menuPage - 1]);
					montaBarra(barraEq, volumeEq[menuPage - 1]);
					LCD_escreve_strings(str, barraEq);
					
				}//end elseif !volumeSelect


				else if(volumeSelect){
					
					sprintf(str, "%dHz EDITANDO", FREQ_BASE * multiploFreqBase[menuPage - 1]);
					montaBarra(barraEq, volumeEq[menuPage - 1]);
					LCD_escreve_strings(str, barraEq);

				}//end elseif volumeSelect

			}//end if botaoEsq || botaoDir || botaoOK
			counter++;
			delay(DELAY_MS);
		}//end while(3)
		


		// ===== MENU PLAY/REPLAY =====
		if(state == 4){
			menuPage = 1;
			LCD_escreve_strings((char*)"Pressione OK", (char*)"para voltar");
		}
		while(state == 4){
			if(botaoEsq || botaoDir || botaoOK){

				// tratamento dos botoes
				if(botaoEsq){
						if(menuPage <= 1){
							menuPage = 1;
						}
						else{
							menuPage--;
						}
						botaoEsq = false;
					}
					else if(botaoDir){
						if(menuPage >= 3){
							menuPage = 3;
						}
						else{
							menuPage++;
						}
						botaoDir = false;
					}
					else{
						switch(menuPage){
							case 1:
								state = 5;
							break;

							case 2:
								state = 0;
							break;

							case 3:
								state = 1;
							break;
						}
						botaoOK = false;
					}

				// mostra o menu de acordo com a pagina
				switch(menuPage){

					case 1:
					LCD_escreve_strings((char*)"1. Reproduzir", (char*)"audio");
					break;

					case 2:
					LCD_escreve_strings((char*)"2. Reconfigurar", (char*)"e regravar");
					break;

					case 3:
					LCD_escreve_strings((char*)"2. Regravar com", (char*)"mesmo efeito");
					break;
				}

			}//end if
			counter++;
			delay(DELAY_MS);
		}//end while(4)


		// ===== TELA DE REPRODUCAO =====
		if(state == 5){
			LCD_escreve_strings((char*)"Reproduzindo...", (char*)"");
			//gravacao.reproduzirAudio();
		}//end if 5

		

	} //end while(true)
} //end runLcdUI()
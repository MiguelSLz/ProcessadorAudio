#include "Interface.h"
#include<stdio.h>

#define FREQ_BASE 50

// Definicao de metodos da classe Interface
Interface::Interface(){
  botaoEsq = false;
  botaoDir = false;
  botaoOK = false;
}

bool Interface::getEsq{ return botaoEsq; }
bool Interface::getDir{ return botaoDir; }
bool Interface::getOK{ return botaoOK; }

void Interface::setEsq(bool valor){ botaoEsq = valor; }
void Interface::setDir(bool valor){ botaoDir = valor; }
void Interface::setOK(bool valor){ botaoOK = valor; }

void Interface::montaBarra(char barraEq[], char volume){
	char numChar[1];
	
	for(unsigned char i = 0; i < 13; i++){
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

	switch(volume < 0){
		case true:
		sprintf(numChar, "%d", -volume);
		barraEq[14] = '-';
		barraEq[15] = numChar[0];
		break;
		
		case false:
		sprintf(numChar, "%d", volume);
		barraEq[14] = '+';
		barraEq[15] = numChar[0];
		break;
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
		da opcao de dar play e replay e de voltar ao comeco do programa (apagando dados anteriores)
	*/
	
	/*
		Os ifs tao mostrando a mensagem uma vez, enquanto os whiles tao rodando um loop que espera
		algum interrupt mudar o valor de botaoOK para verdadeiro
	*/


void Interface::runLcdUI(){
	// variavel a ser manipulada para adicionar
	unsigned char state = 0, menuPage = 1, escolhaEfeito = 1;
	char str[17], barraEq[17], volumeEq[7] = {0, 0, 0, 0, 0, 0};
	unsigned char multiploFreqBase[7] = {1, 2, 4, 8, 16, 32, 64};
	bool volumeSelect = false;
	
	
	//LCD_inicializa_4_bits(char rs, char en, char d4, char d5, char d6, char d7);
	LCD_inicializa_4_bits(27, 28, 0, 1, 2, 3);
	
	while(true){



		// ===== MENU ESCOLHA =====
		if(state == 0){
			menuPage = 1;
			LCD_escreve_strings("Selecione:", "1. Nenhum efeito");
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
					}
					else if(botaoDir){
						if(menuPage >= 3){
							menuPage = 3;
						}
						else{
							menuPage++;
						}
					}
					else{
						state = menuPage;
						escolhaEfeito = menuPage;
					}

				// mostra o menu de acordo com a pagina
				switch(menuPage){
					case 1:
					LCD_escreve_strings("Selecione:", "1. Nenhum efeito");
					break;

					case 2:
					LCD_escreve_strings("Selecione:", "2. Eco");
					break;

					case 3:
					LCD_escreve_strings("Selecione:", "3. Equalizacao");
					break;
				}

			}//end if botaoEsq || botaoDir || botaoOK
		}//end while(0)
		


		// ===== TELA DE GRAVACAO =====
		if(state == 1){
			LCD_escreve_strings("Gravando...", "");
			//metodoEfeito(escolhaEfeito, forcaEfeito);
		}//end if 1
		


		// ===== MENU ECO =====
		if(state == 2){
			menuPage = 1;
			LCD_escreve_strings("Escolha a forca:", "1. Eco fraco");
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
					}
					else if(botaoDir){
						if(menuPage >= 3){
							menuPage = 3;
						}
						else{
							menuPage++;
						}
					}
					else{
						state = menuPage;
						escolhaEfeito = menuPage;
					}

				// mostra o menu de acordo com a pagina
				switch(menuPage){
					case 0:
					LCD_escreve_strings("Pressione OK", "para voltar");
					break;

					case 1:
					LCD_escreve_strings("Escolha a forca:", "1. Eco fraco");
					break;

					case 2:
					LCD_escreve_strings("Escolha a forca:", "2. Eco mediano");
					break;

					case 3:
					LCD_escreve_strings("Escolha a forca:", "3. Eco forte");
					break;
				}

			}//end if
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
				switch(volumeSelect){
					
					// EDICAO DE VOLUME NAO SELECIONADA
					case false:
					if(botaoEsq){
						if(menuPage <= 0){
							menuPage = 0;
						}
						else{
							menuPage--;
						}
					}
					else if(botaoDir){
						if(menuPage >= 7){
							menuPage = 7;
						}
						else{
							menuPage++;
						}
					}
					else{
						if(menuPage <= 0){
							state = 0;
						}
						else if(menuPage >= 7){
							state = 1;
							escolhaEfeito = 3;
						}
						else{
							volumeSelect = true;
						}
					}
					break;


					// EDICAO DE VOLUME SELECIONADA
					case true:
					if(botaoEsq){
						if(volumeEq[menuPage - 1] <= -6){
							volumeEq[menuPage - 1] = -6;
						}
						else{
							volumeEq[menuPage - 1]--;
						}
					}
					else if(botaoDir){
						if(volumeEq[menuPage - 1] >= 6){
							volumeEq[menuPage - 1] = 6;
						}
						else{
							volumeEq[menuPage - 1]++;
						}
					}
					else{
						volumeSelect = false;
					}
					break;


				}//end switch(volumeSelect)

				// mostra o menu correspondente 'a pagina atual
				if(menupage <= 0){

					LCD_escreve_strings("Pressione OK", "para voltar");

				}//end if menuPage <= 0

				else if(menupage >= 7){

					LCD_escreve_strings("Pressione OK", "para gravar");

				}//end elseif menuPage >= 7

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
		}//end while(3)
		


		// ===== MENU PLAY/REPLAY =====
		if(state == 4){
			menuPage = 1;
			LCD_escreve_strings("Pressione OK", "para voltar");
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
					}
					else if(botaoDir){
						if(menuPage >= 3){
							menuPage = 3;
						}
						else{
							menuPage++;
						}
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
					}

				// mostra o menu de acordo com a pagina
				switch(menuPage){

					case 1:
					LCD_escreve_strings("1. Reproduzir", "audio");
					break;

					case 2:
					LCD_escreve_strings("2. Reconfigurar", "e regravar");
					break;

					case 3:
					LCD_escreve_strings("2. Regravar com", "mesmo efeito");
					break;
				}

			}//end if
		}//end while(4)


		// ===== TELA DE REPRODUCAO =====
		if(state == 5){
			LCD_escreve_strings("Tocando...", "");
			//metodoTocaAudio();
		}//end if 5


	} //end while(true)
} //end runLcdUI()

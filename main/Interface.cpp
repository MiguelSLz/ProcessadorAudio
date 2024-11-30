#include "Interface.h"

Interface::Interface(){ 
  state = 0;
  entradaUsuario = 0;
}

short int Interface::getState(){ return state; }
void Interface::setState(short int newState){ state = newState; }
short int Interface::entradaUsuario{ return entradaUsuario; }
void Interface::setEntrada(short int newEntrada){ entradaUsuario = newEntrada; }

	/* 
		-Leo: O QUE E O STATE?
		
		ele define em qual menu estamos
		
		state = 0
		primeiro menu da Interface, pergunta se o usuario quer:
		entradaUsuario = 1 - Nenhum efeito
		entradaUsuario = 2 - Eco
		entradaUsuario = 3 - Equalizacao
		
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
		-Leo: PQ OS IFS E OS WHILES?
		
		Os ifs tao mostrando a mensagem uma vez, enquanto os whiles tao rodando um loop que espera
		algum interrupt mudar o valor de entradaUsuario zerar
	*/
void Interface::runLcdUI(){
	//LCD_inicializa_4_bits(char rs, char en, char d4, char d5, char d6, char d7);
	LCD_inicializa_4_bits(27, 28, 0, 1, 2, 3);
	
	while(true){
		if(state == 0){
			LCD_escreve_strings("1-Sem efeitos", "2-Eco 3-Eq.");
		}
		while(state == 0){
			switch(entradaUsuario){
				default:
				// n faz nada, while reseta e fica esperando
				// e assim, espera entrada de botao digital com interrupt
				break;
				
				case 1:
				// state = 1 (pula para gravacao)
				// executa gravacao sem efeitos
				break;
				
				case 2:
				// state = 2 (mostrar opcoes de forca do Eco)
				// executa gravacao e aplica Eco
				break;
				
				case 3:
				// state = 3 (mostrar opcoes de Equalizacao)
				// executa gravacao e aplica Eq.
				break;
			}//end switch()
		}//end while(0)
		
		setEntrada(0);
		if(state == 1){
			// envia msg que mostra msg de gravacao do menu 1
		}
		while(state == 1){
			switch(entradaUsuario){
				default:
				break;
			}//end switch()
		}//end while(1)
		
		setEntrada(0);
		if(state == 2){
			// envia msg que mostra opcoes do menu 2
		}
		while(state == 2){
			switch(entradaUsuario){
				default:
				break;
			}//end switch()
		}//end while(2)
		
		setEntrada(0);
		if(state == 3){
			// envia msg que mostra opcoes do menu 3
		}
		while(state == 3){
			switch(entradaUsuario){
				default:
				break;
			}//end switch()
		}//end while(3)
		
		setEntrada(0);
		if(state == 4){
			// envia msg que mostra opcoes do menu 4
		}
		while(state == 4){
			switch(entradaUsuario){
				default:
				break;
			}//end switch()
		}//end while(4)
	} //end while(true)
} //end runLcdUI()

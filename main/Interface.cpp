#include "Interface.h"
//#include bibliotecaLCD

Interface::Interface(){ 
  state = 0;
  entradaUsuario = 0;
}

short int Interface::getState(){ return state; }

void Interface::setState(short int newState){ state = newState; }

short int Interface::getEntrada(){ return entradaUsuario; }

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
  // initLCD4bits();
  
  
  while(true){
    if(getState() == 0){
      // envia msg que mostra opcoes do menu 0
    }
    while(getState() == 0){
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
      }
    }

    setEntrada(0);
    if(getState() == 1){
      // envia msg que mostra msg de gravacao do menu 1
    }
    while(getState() == 1){
      switch(getEntrada()){
        default:
        break;
      }//end switch()
    }

    setEntrada(0);
    if(getState() == 2){
      // envia msg que mostra opcoes do menu 2
    }
    while(getState() == 2){
      switch(getEntrada()){
        default:
        break;
      }//end switch()
    }

    setEntrada(0);
    if(getState() == 3){
      // envia msg que mostra opcoes do menu 3
    }
    while(getState() == 3){
      switch(getEntrada()){
        default:
        break;
      }//end switch()
    }

    setEntrada(0);
    if(getState() == 4){
      // envia msg que mostra opcoes do menu 4
    }
    while(getState() == 4){
      switch(getEntrada()){
        default:
        break;
      }//end switch()
    }//end while(4)
  } //end while(true)
} //end runLcdUI()

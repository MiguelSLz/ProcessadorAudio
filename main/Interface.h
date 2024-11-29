#ifndef INTERFACE_H
#define INTERFACE_H
#include "FFT.cpp"
#include "Dados.cpp"


class Interface{
  short int state;
  short int entradaUsuario;
  
public:
  Interface();
  short int getState();
  void setState(short int state);

  void runLcdUI();
};

#endif

#ifndef INTERFACE_H
#define INTERFACE_H
#include "FFT.cpp"
#include "Dados.cpp"
#include "LCD_display.cpp"


class Interface{
  short int state;
  short int entradaUsuario;
  
public:
  Interface();
  short int getState();
  short int getEntrada();

  void setState(short int newState);
  void setEntrada(short int newEntrada);

  void runLcdUI();
};

#endif

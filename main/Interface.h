#ifndef INTERFACE_H
#define INTERFACE_H
#include "FFT.cpp"
#include "Dados.cpp"
#include "LCD_display.cpp"


class Interface{
  unsigned char state;
  unsigned char entradaUsuario;
  
public:
  Interface();
  unsigned char getState();
  unsigned char getEntrada();

  void setState(unsigned char newState);
  void setEntrada(unsigned char newEntrada);

  void runLcdUI();
};

#endif

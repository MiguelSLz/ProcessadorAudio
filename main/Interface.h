#ifndef INTERFACE_H
#define INTERFACE_H
#include "FFT.cpp"
#include "Dados.cpp"
#include "LCD_display.cpp"


class Interface{
  unsigned char state;
  bool botaoOK;
  
public:
  Interface();
  unsigned char getState();
  bool getOK();

  void setState(unsigned char newState);
  bool setOK(bool valor);

  void montaContador(char str[], unsigned char contador);
  void montaBarra(char barraEq[], unsigned char valor, char volume);
  void runLcdUI();
};

#endif

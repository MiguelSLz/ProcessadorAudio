#ifndef INTERFACE_H
#define INTERFACE_H
#include "FFT.cpp"
#include "Dados.cpp"


class Interface{
  int state;
  
public:
  Interface();
  int getState();
  void setState(int state);

  void runLcdUI();
};

#endif

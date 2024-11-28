#ifndef INTERFACE_H
#define INTERFACE_H

class Interface{
  int state;
  
public:
  Interface();
  int getState();
  void setState(int state);

  void runLcdUI();
};

#endif

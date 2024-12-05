#include "Interface.cpp"

Interface LCD;
extern "C" {
	void app_main(void);
}
void app_main(void){
	LCD.runLcdUi();
}

static void botaoEsqInterrupt(void* arg){
	LCD.setEsq(true);
}
static void botaoDirInterrupt(void* arg){
	LCD.setDir(true);
}
static void botaoOKInterrupt(void* arg){
	LCD.setOK(true);
}

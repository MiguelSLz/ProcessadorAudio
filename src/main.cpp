#include "Interface.h"

#define COUNTER_MINIMUM 100

void configInterruptExt();

Interface display;


extern "C" {
	void app_main(void);
}
void app_main(void){
	configInterruptExt();
	display.runLcdUI();
}

// Interrupt Externo

static void botaoEsqInterrupt(void* arg){
	if(display.getCounter() > COUNTER_MINIMUM){
		display.setEsq(true);
		display.setCounter(0);
	}
}
static void botaoDirInterrupt(void* arg){
	if(display.getCounter() > COUNTER_MINIMUM){
		display.setDir(true);
		display.setCounter(0);
	}
}
static void botaoOKInterrupt(void* arg){
	if(display.getCounter() > COUNTER_MINIMUM){
		display.setOK(true);
		display.setCounter(0);
	}
}

void configInterruptExt(){
	gpio_config_t io_conf; // A estrutura e’ utilizada para definir a variavel io_conf
	io_conf.intr_type = GPIO_INTR_POSEDGE; // Interrupcao na borda de subida
	io_conf.pin_bit_mask = (1ULL << 5) | (1ULL << 6) | (1ULL << 7); // Mascara para GPIO 5, 6 e 7
	io_conf.mode = GPIO_MODE_INPUT; // Configura a porta como entrada
	io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE; // Habilita o pull-down
	io_conf.pull_up_en = GPIO_PULLUP_DISABLE; // Desabilita o pull-up
	
	gpio_config(&io_conf);
	
	gpio_install_isr_service(ESP_INTR_FLAG_IRAM);
	gpio_isr_handler_add(GPIO_NUM_5, botaoEsqInterrupt, NULL);
	gpio_isr_handler_add(GPIO_NUM_6, botaoDirInterrupt, NULL);
	gpio_isr_handler_add(GPIO_NUM_7, botaoOKInterrupt, NULL);
}

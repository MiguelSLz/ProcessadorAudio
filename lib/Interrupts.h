// Interrupts.h
#ifndef Interrupts_H
#define Interrupts_H

#include "driver/gpio.h"
#include "driver/gptimer.h"
#include "esp_attr.h"

class Interrupts {
	
	volatile bool timer_flag = false; // Flag para sinalizar a interrupcao
	static Interrupts *instance;     // Ponteiro para a instancia da classe
	
	static bool IRAM_ATTR timer_callback(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx);

public:
	Interrupts();  // Construtor
	void configTimer();
	bool getTimerFlag();
	void clearTimerFlag();
	void configInterruptExt();
};

#endif // Interrupts_H
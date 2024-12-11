// Interrupts.cpp
#include "Interrupts.h"

#define OVERSAMPLING 4

// Inicializa o ponteiro da instância
Interrupts *Interrupts::instance = nullptr;

// Construtor
Interrupts::Interrupts() {
	instance = this; // Define a instância ativa da classe
}

// Função estática de callback
bool IRAM_ATTR Interrupts::timer_callback(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx) {
	if (instance) {
	instance->timer_flag = true; // Sinaliza o evento de alarme
	}
	return true; // Solicita a reinicialização automática do alarme
}

// Configuração do Timer
void Interrupts::configTimer() {
	gptimer_handle_t temporizador = NULL;
	
	// Configuração do temporizador
	gptimer_config_t config_temporizador = {
		.clk_src = GPTIMER_CLK_SRC_APB,		// Fonte de clock APB
		.direction = GPTIMER_COUNT_UP,		// Contagem crescente
		.resolution_hz = 1024 * 1000,		// Resolução de 1,024 MHz (1 tick = 1 us)
		.intr_priority = 1,					// Nivel de prioridade
	};
	ESP_ERROR_CHECK(gptimer_new_timer(&config_temporizador, &temporizador));
	
	// Configuração do alarme
	gptimer_alarm_config_t alarm_config;
	alarm_config.alarm_count = 128 / OVERSAMPLING;		// 125 µs = 128 ticks; OVERSAMPLING devido ao PDM
	alarm_config.reload_count = 0;						// Começa a contar do zero
	alarm_config.flags.auto_reload_on_alarm = true;		// Reinicia automaticamente após o alarme

	ESP_ERROR_CHECK(gptimer_set_alarm_action(temporizador, &alarm_config));

    // Registro do callback
	gptimer_event_callbacks_t config_callback = {
		.on_alarm = Interrupts::timer_callback, // Callback estático
    };
	ESP_ERROR_CHECK(gptimer_register_event_callbacks(temporizador, &config_callback, NULL));

    // Habilita e inicia o temporizador
	ESP_ERROR_CHECK(gptimer_enable(temporizador));
	ESP_ERROR_CHECK(gptimer_start(temporizador));
}

// Stop the timer and clean up
void Interrupts::stopTimer() {
    if (temporizador) {
        ESP_ERROR_CHECK(gptimer_stop(temporizador));
        ESP_ERROR_CHECK(gptimer_disable(temporizador));
        ESP_ERROR_CHECK(gptimer_del_timer(temporizador));
        temporizador = NULL; // Clear the handle
    }
}

// Obter o valor da flag
bool Interrupts::getTimerFlag() {
	return timer_flag;
}

// Limpar a flag
void Interrupts::clearTimerFlag() {
	timer_flag = false;
}
// Interrupts.cpp
#include "Interrupts.h"

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
		.clk_src = GPTIMER_CLK_SRC_APB,    // Fonte de clock APB
		.direction = GPTIMER_COUNT_UP,     // Contagem crescente
		.resolution_hz = 1 * 1000000,      // Resolução de 1 MHz (1 tick = 1 us)
	};
	ESP_ERROR_CHECK(gptimer_new_timer(&config_temporizador, &temporizador));
	
	// Configuração do alarme
	gptimer_alarm_config_t alarm_config = {
		.alarm_count = 125,                   // 125 µs = 125 ticks
		.reload_count = 0,                    // Começa a contar do zero
		.flags.auto_reload_on_alarm = true,   // Reinicia automaticamente após o alarme
	};
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

// Obter o valor da flag
bool Interrupts::getTimerFlag() {
	return timer_flag;
}

// Limpar a flag
void Interrupts::clearTimerFlag() {
	timer_flag = false;
}

void Interrupts::configInterruptExt(){
	gpio_config_t io_conf; // A estrutura e’ utilizada para definir a variavel io_conf
	io_conf.intr_type = GPIO_INTR_POSEDGE; // Interrupcao na borda de subida
	io_conf.pin_bit_mask = (1ULL << 5) | (1ULL << 6) | (1ULL << 7); // Mascara para GPIO 5, 6 e 7
	io_conf.mode = GPIO_MODE_INPUT; // Configura a porta como entrada
	io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE; // Habilita o pull-down
	io_conf.pull_up_en = GPIO_PULLUP_DISABLE; // Desabilita o pull-up
	
	gpio_config(&io_conf);
	
	gpio_install_isr_service(ESP_INTR_FLAG_IRAM);
	gpio_isr_handler_add(5, botaoEsqInterrupt, NULL);
	gpio_isr_handler_add(6, botaoDirInterrupt, NULL);
	gpio_isr_handler_add(7, botaoOKInterrupt, NULL);
}
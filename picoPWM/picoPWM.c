#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22
#define LED_RGB_PIN 12
#define PWM_FREQ 50
#define STEP_US 5
#define STEP_DELAY 10

void setServoPulse(uint slice, uint channel, uint32_t pulse_us) {
    uint32_t clock = clock_get_hz(clk_sys);
    uint32_t wrap = clock / (PWM_FREQ * 1000) - 1; // Configura o período do PWM para aproximadamente 50Hz, atendendo à diretriz 1
    pwm_set_wrap(slice, wrap);
    uint32_t level = (pulse_us * (wrap + 1)) / 20000;
    pwm_set_chan_level(slice, channel, level);
}

int main() {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    gpio_set_function(LED_RGB_PIN, GPIO_FUNC_PWM);
    
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
    uint channel = pwm_gpio_to_channel(SERVO_PIN);
    pwm_set_enabled(slice, true);
    
    setServoPulse(slice, channel, 2400); // Configura o servo para 180 graus, movendo a flange para a posição máxima
    sleep_ms(5000);
    setServoPulse(slice, channel, 1470);
    sleep_ms(5000);
    setServoPulse(slice, channel, 500); // Configura o servo para 0 graus, posicionando a flange na posição inicial
    sleep_ms(5000);

    // Inicia um loop infinito para movimentação periódica do servo entre 0 e 180 graus
    while (1) {
        // Move gradualmente de 0 para 180 graus
        for (uint32_t pulse = 500; pulse <= 2400; pulse += STEP_US) {
            setServoPulse(slice, channel, pulse);
            sleep_ms(STEP_DELAY);
        }
        // Move gradualmente de 180 para 0 graus
        for (uint32_t pulse = 2400; pulse >= 500; pulse -= STEP_US) {
            setServoPulse(slice, channel, pulse);
            sleep_ms(STEP_DELAY);
        }
    }
}

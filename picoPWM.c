#include <stdio.h>
#include "pico/stdlib.h" // Biblioteca necessária para configurar GPIO e lidar com tempo
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define GPIOSERV 22 // GPIO associada ao controle do servo
#define LED 12 // GPIO para controle do LED RGB
#define FREQUENCIA 50
#define WRAP 19531
#define DIV 128.0
#define DELAY 10 // Tempo de espera em ms
#define ADDING 5 // Passo do ajuste do PWM

#define DUTY_180 2343  // Valor correspondente a ~180 graus
#define DUTY_90 1435   // Valor correspondente a ~90 graus
#define DUTY_0 488     // Valor correspondente a ~0 graus

int main() {
    stdio_init_all();

    gpio_set_function(LED, GPIO_FUNC_PWM);
    uint slice_led = pwm_gpio_to_slice_num(LED);
    pwm_set_clkdiv(slice_led, DIV);
    pwm_set_wrap(slice_led, WRAP);
    pwm_set_enabled(slice_led, true);
    pwm_set_gpio_level(LED, DUTY_0);

    gpio_set_function(GPIOSERV, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(GPIOSERV);
    pwm_set_clkdiv(slice, DIV);
    pwm_set_wrap(slice, WRAP);
    pwm_set_enabled(slice, true);
    pwm_set_gpio_level(GPIOSERV, DUTY_0);
    sleep_ms(1000);

    pwm_set_gpio_level(GPIOSERV, DUTY_180);
    pwm_set_gpio_level(LED, DUTY_180);
    sleep_ms(5000);

    pwm_set_gpio_level(GPIOSERV, DUTY_90);
    pwm_set_gpio_level(LED, DUTY_90);
    sleep_ms(5000);

    pwm_set_gpio_level(GPIOSERV, DUTY_0);
    pwm_set_gpio_level(LED, DUTY_0);
    sleep_ms(5000);

    while (1) {
        // Movimento progressivo do servo de 0 a 180 graus
        for (int i = DUTY_0; i <= DUTY_180; i += ADDING) {
            pwm_set_gpio_level(GPIOSERV, i);
            pwm_set_gpio_level(LED, i);
            sleep_ms(DELAY);
        }
        // Retorno gradual de 180 a 0 graus
        for (int i = DUTY_180; i >= DUTY_0; i -= ADDING) {
            pwm_set_gpio_level(GPIOSERV, i);
            pwm_set_gpio_level(LED, i);
            sleep_ms(DELAY);
        }
        sleep_ms(50); // Pequena pausa para evitar carga excessiva na CPU
    }

    return 0;
}

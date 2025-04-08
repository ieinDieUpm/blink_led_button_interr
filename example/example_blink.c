#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "port_system.h"
#include "port_led.h"

#define BLINK_T_MS 1000

int main()
{
    port_system_init();                 // inicializamos el sistema
    port_led_gpio_setup(); // Configuramos el GPIO para el LED

    uint32_t t = port_system_get_millis(); // en t llevamos cuenta del tiempo actual
    while (1)
    {
        port_led_toggle(); // Hacemos parpadear el LED
        port_system_delay_until_ms(&t, BLINK_T_MS / 2); // Y esperamos el periodo de la FSM
    }
    return 0;
}

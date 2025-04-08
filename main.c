/**
 * @file main.c
 * @author Josué Pagán (j.pagan@upm.es)
 * @brief LD2 blinks permanently within a cycle 300 ms ON - 700 ms OFF. Delay time using polling over SysTick.  
 * @version 0.1
 * @date 2024-03-01
 * 
 */

/* INCLUDES */
#include "port_system.h"
#include "port_led.h"

int main() {
    port_system_init();
    port_led_gpio_setup();

    while (1) {
        port_led_toggle(); // Toggle LD2
        port_system_delay_ms(300);       
        port_led_toggle(); // Toggle LD2
        port_system_delay_ms(700);
    }
    return 0;
}
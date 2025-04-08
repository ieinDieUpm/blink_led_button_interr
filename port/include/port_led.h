/**
 * @file port_led.h
 * @author Román Cárdenas (r.cardenas@upm.es), Josue Pagán Ortiz (j.pagan@upm.es)
 * @brief Header file for the LED port layer.
 * @date 01-03-2025
 */
#ifndef PORT_LED_H_
#define PORT_LED_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdbool.h>

/* Function prototypes and explanations ---------------------------------------*/

/**
 * @brief Configures the GPIO port connected to the LED.
 * 
 */
void port_led_gpio_setup(void);

/**
 * @brief Returns the current state of the LED.
 * 
 * @return true if the LED is on
 * @return false if the LED is off
 */
bool port_led_get_status(void);


/**
 * @brief Turn on the LED
 * 
 */
void port_led_on(void);


/**
 * @brief Turn off the LED
 * 
 */
void port_led_off(void);


/**
 * @brief Toggles the LED state.
 * 
 */
void port_led_toggle(void);

#endif // PORT_LED_H_

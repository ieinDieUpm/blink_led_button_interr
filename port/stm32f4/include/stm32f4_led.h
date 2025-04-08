/**
 * @file stm32f4_led.h
 * @author Josué Pagán (j.pagan@upm.es)
 * @brief Header file for the LED port layer of the STM32F4 Nucleo board.
 * @version 0.1
 * @date 2025-03-01
 *
 */

#ifndef STM32F4_LED_H
#define STM32F4_LED_H

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

// HW Nucleo-STM32F446RE:
#define STM32F4_LD2_GPIO_PIN GPIO_PIN_5 /*!< GPIO pin of the LED2 in the Nucleo board */
#define STM32F4_LD2_GPIO_PORT GPIOA     /*!< GPIO port of the LED2 in the Nucleo board */

#endif /* STM32F4_LED_H */
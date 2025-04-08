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

// HW Nucleo-STM32F446RE:
#define STM32F4_LD2_GPIO_PIN 5           /*!< GPIO pin of the LED2 in the Nucleo board */
#define STM32F4_LD2_GPIO_PORT GPIOA /*!< GPIO port of the LED2 in the Nucleo board */

#define STM32F4_MODER_LD2_MASK (GPIO_MODER_MODE0 << STM32F4_LD2_GPIO_PIN * 2) /*!< Mask for the LED2 in the MODE Register */
#define STM32F4_PUPDR_LD2_MASK (GPIO_PUPDR_PUPD0 << STM32F4_LD2_GPIO_PIN * 2) /*!< Mask for the LED2 in the PUPD Register */

#define STM32F4_MODER_LD2_AS_OUTPUT (STM32F4_GPIO_MODE_OUT << STM32F4_LD2_GPIO_PIN * 2)     /*!< Output mode for the LED2 in the MODE Register */
#define STM32F4_PUPDR_LD2_AS_NOPUPD (STM32F4_GPIO_PUPDR_NOPULL << STM32F4_LD2_GPIO_PIN * 2) /*!< No push/pull configuration for the LED2 in the MODE Register */

#define STM32F4_IDR_LD2_MASK (GPIO_IDR_ID0 << STM32F4_LD2_GPIO_PIN) /*!< Mask for the LED2 in the Input Data Register */
#define STM32F4_ODR_LD2_MASK (GPIO_ODR_OD0 << STM32F4_LD2_GPIO_PIN) /*!< Mask for the LED2 in the Output Data Register */

#endif /* STM32F4_LED_H */
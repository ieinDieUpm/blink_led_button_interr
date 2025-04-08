/**
 * @file port_led.c
 * @author Josué Pagán (j.pagan@upm.es)
 * @brief Port layer for the LED of the STM32F4 Nucleo board.
 * @date 01-03-2025
 */
/* Standard C includes */
#include <stdio.h>

/* HW dependent includes */
#include "port_led.h"
#include "port_system.h"

/* Microcontroller dependent includes */
#include "stm32f4_led.h" // Used to get the GPIO pin and port of the LED

// HW Nucleo-STM32F446RE:
#define STM32F4_LD2_GPIO_PIN GPIO_PIN_5 /*!< GPIO pin of the LED2 in the Nucleo board */
#define STM32F4_LD2_GPIO_PORT GPIOA     /*!< GPIO port of the LED2 in the Nucleo board */

void port_led_gpio_setup(void)
{
    /* GPIO init structure */
    GPIO_InitTypeDef led = {0}; // Initialize to 0 all fields by default

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Configure GPIO pin */
    led.Pin = STM32F4_LD2_GPIO_PIN; // LED2 Pin
    led.Mode = MODE_OUTPUT;         // A LED is an output device
    led.Pull = GPIO_NOPULL;         // No pull-up or pull-down internal resistors

    /* Initialize GPIO pin */
    HAL_GPIO_Init(STM32F4_LD2_GPIO_PORT, &led);

    /* Set GPIO pin output level to low */
    HAL_GPIO_WritePin(STM32F4_LD2_GPIO_PORT, STM32F4_LD2_GPIO_PIN, GPIO_PIN_RESET);
}

bool port_led_get_status(void)
{
    return (HAL_GPIO_ReadPin(STM32F4_LD2_GPIO_PORT, STM32F4_LD2_GPIO_PIN) == GPIO_PIN_SET);
}

void port_led_on(void)
{
    HAL_GPIO_WritePin(STM32F4_LD2_GPIO_PORT, STM32F4_LD2_GPIO_PIN, GPIO_PIN_SET);
    printf("[%ld] LED ON\n", port_system_get_millis()); // For debug purposes only
}

void port_led_off(void)
{
    HAL_GPIO_WritePin(STM32F4_LD2_GPIO_PORT, STM32F4_LD2_GPIO_PIN, GPIO_PIN_RESET);
    printf("[%ld] LED OFF\n", port_system_get_millis()); // For debug purposes only
}

void port_led_toggle(void)
{
    HAL_GPIO_TogglePin(STM32F4_LD2_GPIO_PORT, STM32F4_LD2_GPIO_PIN);

    if (port_led_get_status())
    {
        printf("[%ld] LED ON\n", port_system_get_millis()); // For debug purposes only
    }
    else
    {
        printf("[%ld] LED OFF\n", port_system_get_millis()); // For debug purposes only
    }
}

/**
 * @file port_led.c
 * @author Josué Pagán (j.pagan@upm.es)
 * @brief Port layer for the LED of the STM32F4 Nucleo board.
 * @date 01-03-2024
 */
/* Standard C includes */
#include <stdio.h>

/* HW dependent includes */
#include "port_led.h"
#include "port_system.h"
#include "stm32f4_system.h"
#include "stm32f4_led.h"

void port_led_gpio_setup(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;     // Enable peripheral clock
    STM32F4_LD2_GPIO_PORT->MODER &= ~STM32F4_MODER_LD2_MASK; // Clean the registers
    STM32F4_LD2_GPIO_PORT->PUPDR &= ~STM32F4_PUPDR_LD2_MASK;
    STM32F4_LD2_GPIO_PORT->MODER |= STM32F4_MODER_LD2_AS_OUTPUT; // Set the corresponfing configuration
    STM32F4_LD2_GPIO_PORT->PUPDR |= STM32F4_PUPDR_LD2_AS_NOPUPD;
}

bool port_led_get_status(void)
{
    return (STM32F4_LD2_GPIO_PORT->IDR & STM32F4_IDR_LD2_MASK) != 0;
}

void port_led_on(void)
{
    STM32F4_LD2_GPIO_PORT->ODR |= STM32F4_ODR_LD2_MASK;
    printf("[%ld] LED ON\n", port_system_get_millis()); // For debug purposes only
}

void port_led_off(void)
{
    STM32F4_LD2_GPIO_PORT->ODR &= ~STM32F4_ODR_LD2_MASK;
    printf("[%ld] LED OFF\n", port_system_get_millis()); // For debug purposes only
}

void port_led_toggle(void)
{
    STM32F4_LD2_GPIO_PORT->ODR ^= STM32F4_ODR_LD2_MASK;

    if (port_led_get_status())
    {
        printf("[%ld] LED ON\n", port_system_get_millis()); // For debug purposes only
    }
    else
    {
        printf("[%ld] LED OFF\n", port_system_get_millis()); // For debug purposes only
    }
}

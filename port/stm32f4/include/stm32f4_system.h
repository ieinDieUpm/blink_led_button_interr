/**
 * @file stm32f4_system.h
 * @author Josue Pagán Ortiz (j.pagan@upm.es)
 * @brief System functions for the STM32F4 platform.
 * @date 01-03-2025
 */

#ifndef STM32F4_SYSTEM_H_
#define STM32F4_SYSTEM_H_

/* Includes ------------------------------------------------------------------*/
/* HW dependent includes */
#include "stm32f4xx.h"

/* Defines ------------------------------------------------------------------*/
#define STM32F4_GPIO_MODE_IN 0x00        /*!< GPIO as input */
#define STM32F4_GPIO_MODE_OUT 0x01       /*!< GPIO as output */

#define STM32F4_GPIO_PUPDR_NOPULL 0x00 /*!< GPIO no pull up or down */
#define STM32F4_GPIO_PUPDR_PUP 0x01    /*!< GPIO pull up */
#define STM32F4_GPIO_PUPDR_PDOWN 0x02  /*!< GPIO pull down */

/* Function prototypes and explanations ---------------------------------------*/

#endif /* STM32F4_SYSTEM_H_ */

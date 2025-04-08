/**
 * @file stm32f4_system.c
 * @author Josué Pagán Ortiz (j.pagan@upm.es)
 * @brief Port layer for the system functions in the STM32F4 platform.
 * @date 01-03-2025
 */

/* HW dependent includes */
#include "port_system.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"

#ifdef USE_SEMIHOSTING
extern void initialise_monitor_handles(void);
#endif

//------------------------------------------------------
// PRIVATE (STATIC) VARIABLES
//------------------------------------------------------
static volatile uint32_t msTicks = 0; /*!< Variable to store millisecond ticks. @warning **It must be declared volatile!** Just because it is modified in an ISR. **Add it to the definition** after *static*. */

//------------------------------------------------------
// PUBLIC (GLOBAL) VARIABLES
//------------------------------------------------------
/* These variables are declared extern in CMSIS (system_stm32f4xx.h) */
uint32_t SystemCoreClock = HSI_VALUE;                                               /*!< Frequency of the System clock */
const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9}; /*!< Prescaler values for AHB bus */
const uint8_t APBPrescTable[8] = {0, 0, 0, 0, 1, 2, 3, 4};                          /*!< Prescaler values for APB bus */

//------------------------------------------------------
// PRIVATE (STATIC) FUNCTIONS
//------------------------------------------------------

/**
 * @brief System Clock Configuration
 *
 * @attention This function should NOT be accesible from the outside to avoid configuration problems.
 * @note This function starts a system timer that generates a SysTick every 1 ms.
 */
static void system_clock_config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0}; /*!< RCC Oscillator configuration structure */
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0}; /*!< RCC System Clock configuration structure */

  /* Configure the main internal regulator output voltage */
  __HAL_RCC_PWR_CLK_ENABLE();                                    /*!< Enable Power Control clock */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1); /*!< Configure the main internal regulator output voltage */

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI; /*!< Set the oscillator type */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                   /*!< Set the HSI state */
  RCC_OscInitStruct.HSICalibrationValue = 16;                /*!< Set the HSI calibration value */
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;               /*!< Set the PLL state */
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;       /*!< Set the PLL source */
  RCC_OscInitStruct.PLL.PLLM = 16;                           /*!< Set the PLL M division factor */
  RCC_OscInitStruct.PLL.PLLN = 336;                          /*!< Set the PLL N multiplication factor */
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;                /*!< Set the PLL P division factor */
  RCC_OscInitStruct.PLL.PLLQ = 7;                            /*!< Set the PLL Q division factor */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  { /*!< Configure the main internal regulator output voltage */
    while (1)
      ;
  }

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2; /*!< Set the clock type */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;                                                            /*!< Set the system clock source */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                                                   /*!< Set the AHB clock divider */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;                                                                    /*!< Set the APB1 clock divider */
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;                                                                    /*!< Set the APB2 clock divider */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  { /*!< Initializes the CPU, AHB and APB busses clocks */
    while (1)
      ;
  }
}

//------------------------------------------------------
// PUBLIC (GLOBAL) FUNCTIONS
//------------------------------------------------------

/**
 * @brief  Setup the microcontroller system
 *         Initialize the FPU setting, vector table location and External memory
 *         configuration.
 *
 * @note   This function is called at startup by CMSIS in startup_stm32f446xx.s.
 */
void SystemInit(void)
{
/* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif

#if defined(DATA_IN_ExtSRAM) || defined(DATA_IN_ExtSDRAM)
  SystemInit_ExtMemCtl();
#endif /* DATA_IN_ExtSRAM || DATA_IN_ExtSDRAM */

  /* Configure the Vector Table location -------------------------------------*/
#if defined(USER_VECT_TAB_ADDRESS)
  SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#endif                                                 /* USER_VECT_TAB_ADDRESS */
}

uint32_t port_system_init()
{
#ifdef USE_SEMIHOSTING
  initialise_monitor_handles();
#endif

  // Init HAL
  HAL_Init(); /*!< Initialize the HAL Library */

  // Configure the system clock
  system_clock_config();

  return HAL_OK;
}

void port_system_delay_ms(uint32_t ms)
{
  uint32_t tickstart = port_system_get_millis();

  while ((port_system_get_millis() - tickstart) < ms)
  {
  }
}

void port_system_delay_until_ms(uint32_t *t, uint32_t ms)
{
  uint32_t until = *t + ms;
  uint32_t now = port_system_get_millis();
  if (until > now)
  {
    port_system_delay_ms(until - now);
  }
  *t = port_system_get_millis();
}

uint32_t port_system_get_millis()
{
  return msTicks;
}

void port_system_set_millis(uint32_t ms)
{
  msTicks = ms;
}

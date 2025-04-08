/**
 * @file interr.c
 * @brief Interrupt service routines for the STM32F4 platform.
 * @author Román Cárdenas (r.cardenas@upm.es)
 * @date 2024-01-01
 */
// Include HW dependencies:
#include "port_system.h"

// Include headers of different port elements:

//------------------------------------------------------
// INTERRUPT SERVICE ROUTINES
//------------------------------------------------------
/**
 * @brief Interrupt service routine for the System tick timer (SysTick).
 *
 * @note This ISR is called when the SysTick timer generates an interrupt.
 * The program flow jumps to this ISR and increments the tick counter by one millisecond.
 *
 * @warning **The variable `msTicks` must be declared volatile!** Just because it is modified by a call of an ISR, in order to avoid [*race conditions*](https://en.wikipedia.org/wiki/Race_condition)
. **Added to the definition** after *static*.
 *
 */
void SysTick_Handler(void)
{
  port_system_set_millis(port_system_get_millis() + 1);
}

# Blink LED con interrupción de botón y polling

Este proyecto hace parpadear el LED LD2 de la Nucleo-STM32F446RE a una frecuencia de `c` Hz. La frecuencia es controlada por el pulsado del botón de usuario B1. Cada vez que se pulsa el botón, la frecuencia (`c`) aumenta en 1. El LED está apagado cuando `c` es igual a 0. El botón es manejado por una rutina de servicio de interrupción (ISR) mientras que el retardo es manejado por *polling*.

## Autor

* **Josué Pagán Ortiz** - email: [j.pagan@upm.es](mailto:j.pagan@upm.es)

## Ejercicio: parpadeo con interrupción de un botón

**Cree el proyecto** `blink_led_button_interr`. **Se trata de una modificación del programa** [blink_led_button](https://ieindieupm.github.io/blink_led_button) **donde la acción de parpadeo no se toma al leer mediante polling el valor de la GPIO del botón, sino mediante su ISR.**

![](docs/assets/imgs/ejercicio.png)

1 . **Modifique la definición del modo de la GPIO del botón**. Ahora, además de entrada, se debe configurar la línea como fuente de interrupción externa que genere una interrupción en el flanco de subida y de bajada.

* En la función `port_button_gpio_setup()` cambie el modo de la GPIO del botón a `GPIO_MODE_IT_RISING_FALLING`.

  Esta etiqueta se extiende a `(MODE_INPUT | EXTI_IT | TRIGGER_RISING | TRIGGER_FALLING)`; como ve, se configura como entrada, fuente de interrupción externa y que genere interrupción en flanco de subida y de bajada.

2 . **Cree la función** `port_button_exti_config()` **para configurar la interrupción:**

* Primero: habilite el reloj del módulo generador de interrupciones: `__HAL_RCC_SYSCFG_CLK_ENABLE();`
* Llame a `HAL_NVIC_SetPriority()` para poner la interrupción con prioridad ‘1’ y subprioridad ‘0’. Las prioridades están definidas en `stm32f4_button.h`.
* Llame a `HAL_NVIC_EnableIRQ()` para habilitar la interrupción.
  * **La ISR de la línea donde se conecta el botón es** `EXTI15_10_IRQn`. Esta línea se ha definido en el archivo `stm32f4_button.h` como `#define BUTTON_EXTI_IRQn EXTI15_10_IRQn`.

![](docs/assets/imgs/nvic.png)

3 . **Deberá hacer públicas las funciones o macros necesarias**

4 . **En** `main.c`:

* **Crear un *flag* global y volátil** (`volatile`) para indicar que se ha ha pulsado (y soltado) el botón
  * El *flag* lo activa la ISR y lo desactiva la función `main()`
* **Hacer el contador** `c` **global y volátil** → lo aumenta la ISR

5 . **En la ISR** en `interr.c`:

* Declarar como `extern` el *flag* y `c` (están en `main.c`)
* Implementar la ISR `EXTI15_10_IRQHandler()` que:
  * Haga un GET del bit `STM32F4_BUTTON_GPIO_PIN` para comprobar si ha sido un flanco de subida o de bajada del botón quién ha interrumpido
  * Si ha sido el botón, llamar a la función `HAL_GPIO_EXTI_IRQHandler()`. Ésta limpiará el *flag* de interrupción y llamará a la función de *callback* `HAL_GPIO_EXTI_Callback()`.
  * En el *callback* use una variable local (o *flag*) `static` para llevar el control de si el flanco de una interrupción anterior fue de subida o de bajada.
  * Si el pin recibido como argumento en el *callback* es el del botón (`STM32F4_BUTTON_GPIO_PIN`), entonces gestionar el *flag* y el contador `c` adecuadamente

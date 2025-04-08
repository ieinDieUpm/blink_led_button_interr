#include <unity.h>
#include "port_led.h"
#include "stm32f4xx.h" // we can use the definitions from the MCU

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_led(void)
{
    port_led_gpio_setup();
    TEST_ASSERT_FALSE(port_led_get_status());

    port_led_on();
    TEST_ASSERT_TRUE(port_led_get_status());

    port_led_off();
    TEST_ASSERT_FALSE(port_led_get_status());

    port_led_toggle();
    TEST_ASSERT_TRUE(port_led_get_status());
    port_led_toggle();
    TEST_ASSERT_FALSE(port_led_get_status());
}


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_led);
    return UNITY_END();
}

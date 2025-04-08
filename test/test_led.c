/**
 * @file test_led.c
 * @brief Unit test for the LED.
 *
 * @author Josué Pagán (j.pagan@upm.es)
 * @date 2025-03-01
 */
/* System dependent libraries */
#include <stdlib.h>
#include <unity.h>

/* HW independent libraries */
#include "port_system.h"
#include "port_led.h"

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
    port_system_init();

    UNITY_BEGIN();
    RUN_TEST(test_led);

    exit(UNITY_END());
}

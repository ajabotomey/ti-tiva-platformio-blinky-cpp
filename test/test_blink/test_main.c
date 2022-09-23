#include <unity.h>
#include "main.h"

#define TEST_MAX (uint8_t)5

void setUp(void)
{

}

void tearDown(void)
{

}

void test_red_led_pin_number(void)
{
    TEST_ASSERT_EQUAL(GPIO_PIN_1, LED_RED);
}

void test_led_red(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED, LED_RED);
    TEST_ASSERT_EQUAL(LED_RED, GPIOPinRead(GPIO_PORTF_BASE, LED_RED));
}

void test_led_blue(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN, LED_BLUE);
    TEST_ASSERT_EQUAL(LED_BLUE, GPIOPinRead(GPIO_PORTF_BASE, LED_BLUE));
}

void test_led_green(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN, LED_GREEN);
    TEST_ASSERT_EQUAL(LED_GREEN, GPIOPinRead(GPIO_PORTF_BASE, LED_GREEN));
}

void setup(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    SysCtlDelay(20000000);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN);

    UNITY_BEGIN();
    RUN_TEST(test_red_led_pin_number);

    for (uint8_t i = 0; i < TEST_MAX; i++)
    {
        RUN_TEST(test_led_red);
        SysCtlDelay(3000000);
        RUN_TEST(test_led_blue);
        SysCtlDelay(3000000);
        RUN_TEST(test_led_green);
        SysCtlDelay(3000000);
    }

    UNITY_END();
}

void loop(void)
{

}
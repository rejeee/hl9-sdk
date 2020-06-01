/*******************************************************************************
 * @file    hal_led.c
 * @brief   The special implemetation for common LED function
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#include "dev_led.h"

#define LED_N_GPIO          GpioPortA
#define LED1_PIN            GpioPin10
#define LED2_PIN            GpioPin9

void LED_Enable(bool enable)
{
    stc_gpio_config_t gpioCfg;
    DDL_ZERO_STRUCT(gpioCfg);

    if(enable){
        Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
        gpioCfg.enDir = GpioDirOut;
        Gpio_Init(LED_N_GPIO, LED1_PIN, &gpioCfg);
        Gpio_Init(LED_N_GPIO, LED2_PIN, &gpioCfg);

        LED_OFF(LED_RF_TX);
        LED_OFF(LED_RF_RX);
    } else {
        LED_OFF(LED_RF_TX);
        LED_OFF(LED_RF_RX);
    }
}

void LED_ON(uint32_t led_num)
{
    switch(led_num){
    case LED_RF_TX:
        Gpio_SetIO(LED_N_GPIO, LED1_PIN);
        break;
    case LED_RF_RX:
        Gpio_SetIO(LED_N_GPIO, LED2_PIN);
        break;
    default:
        break;
    }

    return;
}

void LED_OFF(uint32_t led_num)
{
    switch(led_num){
    case LED_RF_TX:
        Gpio_ClrIO(LED_N_GPIO, LED1_PIN);
        break;
    case LED_RF_RX:
        Gpio_ClrIO(LED_N_GPIO, LED2_PIN);
        break;
    default:
        break;
    }

    return;
}

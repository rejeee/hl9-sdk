/*******************************************************************************
 * @file    dev_led.c
 * @brief   The common LED function
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#include "dev_led.h"

void LED_Enable(bool enable)
{
    stc_gpio_config_t gpioCfg;
    DDL_ZERO_STRUCT(gpioCfg);

    if(enable){
        Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
        gpioCfg.enDir = GpioDirOut;
        Gpio_SetAfMode(LED_N_GPIO, LED1_PIN, GpioAf0);
        Gpio_Init(LED_N_GPIO, LED1_PIN, &gpioCfg);
        Gpio_SetAfMode(LED_N_GPIO, LED2_PIN, GpioAf0);
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

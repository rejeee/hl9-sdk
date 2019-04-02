/*******************************************************************************
 * @file    dev_led.h
 * @brief   The common LED function
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/

#ifndef PLATFORM_DEV_LED_H
#define PLATFORM_DEV_LED_H

/****
Include Files
****/
#include "bsp.h"

/* LED num */
enum {
  LED_NORMAL = 0x00,
  LED_RF_TX,
  LED_RF_RX,
  LED_ULED
};

void LED_Enable(bool enable);
void LED_ON(uint32_t led_num);
void LED_OFF(uint32_t led_num);

#endif

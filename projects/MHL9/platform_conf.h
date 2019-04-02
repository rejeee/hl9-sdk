#ifndef PLATFORM_CONF_H
#define PLATFORM_CONF_H

#include "bsp.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 *  Debug Port Settings
 */
#define DBG_UART_SIZE           255
#define DBG_UART_NUM            BSP_LEUART0
#define DBG_TX_GPIO             GpioPortB   /* TX: PB00 */
#define DBG_TX_PIN              GpioPin0
#define DBG_RX_GPIO             GpioPortB   /* RX: PB11 */
#define DBG_RX_PIN              GpioPin11
#define DBG_AF                  GpioAf3

/* AT mode select, PB07 */
#define AT_GPIO                 GpioPortB
#define AT_PIN                  GpioPin7
#define AT_HIGH()               Gpio_SetIO(AT_GPIO, AT_PIN)
#define AT_LOW()                Gpio_ClrIO(AT_GPIO, AT_PIN)

/* USER Wakeup KEY, PB05  */
#define UKEY_PORT_IRQ           PORTB_IRQn
#define UKEY_GPIO               GpioPortB
#define UKEY_PIN                GpioPin5

/****
Global Variable
****/
extern BSP_OS_MQ        gUartQ;
extern BSP_OS_MPOOL     gMemPool;

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

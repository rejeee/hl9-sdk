#ifndef PLATFORM_CONF_H
#define PLATFORM_CONF_H

#include "bsp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Debug Port Settings
 */

/* The min timeslice of between two frames */
#define DBG_UART_TIMEOUT        5U
#define DBG_UART_SIZE           255
#define DBG_UART_NUM            BSP_LPUART0
#define DBG_GPIO                GpioPortB
#define DBG_TX_PIN              GpioPin0    /* TX: PB00 */
#define DBG_RX_PIN              GpioPin11   /* RX: PB11 */
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
Global Variables
****/
extern BSP_OS_MQ        gUartQ;
extern BSP_OS_MPOOL     gMemPool;
extern BSP_OS_SEM       gDbgSem;

void Dev_GetVol(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

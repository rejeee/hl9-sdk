#ifndef PLATFORM_CONF_H
#define PLATFORM_CONF_H

#include "bsp.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MIN_VOL_LEVEL   3000
#define MAX_VOL_LEVEL   3600

#define BOOL_EXTL_EN    1

/**
 *  Debug Port Settings
 */
#define DBG_UART_TIMEOUT        5U
#define DBG_UART_SIZE           255
#define DBG_UART_IDX            BSP_LPUART0
#define DBG_GPIO                GpioPortB
#define DBG_TX_PIN              GpioPin0    /* TX: PB00 */
#define DBG_RX_PIN              GpioPin11   /* RX: PB11 */
#define DBG_AF                  GpioAf3

#define AT_GPIO                 GpioPortB
#define AT_PIN                  GpioPin7
#define AT_HIGH()               Gpio_SetIO(AT_GPIO, AT_PIN)
#define AT_LOW()                Gpio_ClrIO(AT_GPIO, AT_PIN)

/* USER Wakeup KEY, PB05  */
#define UKEY_PORT_IRQ           PORTB_IRQn
#define UKEY_GPIO               GpioPortB
#define UKEY_PIN                GpioPin5

#define UPA_GPIO                GpioPortB
#define UPA_PIN                 GpioPin3
#define UNUSED_GPIO             GpioPortB
#define UNUSED_PIN              GpioPin6

/****
Global Variables
****/
extern BSP_OS_MQ        gUartQ;
extern BSP_OS_MPOOL     gMemPool;
extern bool gPaEnable;

/****
Global Functions
****/
bool DevUserInit(void);

void DevGetVol(uint32_t param1, uint16_t param2);

void AppMacQueryCSQ(int16_t *rssi, int8_t *snr);
bool AppMacUpdateRx(bool update);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

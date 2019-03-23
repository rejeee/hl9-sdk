/*******************************************************************************
 * @file    dev.h
 * @brief   The main function of special device platform
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef PLATFORM_DEV_H
#define PLATFORM_DEV_H

#include "bsp.h"
#include "dev_debug.h"
#include "dev_config.h"
#include "dev_radio.h"
#include "dev_led.h"

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

#define GPIO_READ               Gpio_GetInputIO

typedef union {
    uint8_t val;
    stc_reset_cause_t bits;
} union_cause_t;

struct global_param_t {
    BSP_OS_MUTEX    mutex;
    union_cause_t   rst;            /* device reset cause   */
    uint32_t        vol;            /* device voltage   */
    uint8_t         at_mode;        /* AT command or transparent */
    uint8_t         at_switch;      /* AT switch */
    uint8_t         extl;
};

/****
Global Variable
****/
extern struct global_param_t gParam;

extern BSP_OS_THREAD    gMacThreadID;
extern volatile bool    gEnableRadioRx;

/****
Global Functions
****/

/*!
 * @brief Platform board and global variables initialize.
 *
 * @param param     the watchdog WOV count
 *
 */
bool PlatformInit(uint32_t param);

/*!
 * @brief Set Chip enter low power mode.
 *
 * @param second    the chip wake up after second
 * @return          the actual sleep time
 */
uint32_t PlatformSleep(uint32_t second);

/**
 * @brief Enable or disable external GPIO for user
 *
 * @param   enable      true is enable , false is disable
 */
void DevExternalGPIO(bool enable);
bool DebugInit(uint32_t baudrateType, uint8_t pariType);
bool DebugReInit(uint32_t baudrateType, uint8_t pariType);
void DebugWrite(const uint8_t *data, uint32_t len);

void DevEnterAT(bool enable);
void DevCheckAT(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

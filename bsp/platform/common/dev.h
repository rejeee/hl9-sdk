/*******************************************************************************
 * @file    dev.h
 * @brief   The common platform define
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef PLATFORM_DEV_H
#define PLATFORM_DEV_H

#include "bsp.h"
#include "common/dev_debug.h"
#include "common/dev_config.h"
#include "common/dev_radio.h"
#include "common/dev_led.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum RJ_STATUS
 * @brief return platform initialize result
 */
typedef enum
{
    RJ_ERR_OK   = 0x00, /**< OK */
    RJ_ERR_OS,          /**< create OS object fail */
    RJ_ERR_FLASH,       /**< flash init fail */
    RJ_ERR_LPW,         /**< LPower and timer init fail */
    RJ_ERR_CHK,         /**< HL9 sign check fail */
} RJ_STATUS;

/**
 * @struct dev_param_t
 * @brief device parameter
 */
typedef struct  {
    uint32_t vol;       /**> device voltage ADC */
    uint32_t exth : 1;  /**> whether to use external high frequency OSC */
    uint32_t extl : 1;  /**> whether to use external low frequency OSC */
} dev_param_t;

/****
Global Functions
****/

/**
 * @brief Platform board and global variables initialize.
 *
 * @param param     the watchdog WOV count
 *
 */
RJ_STATUS PlatformInit(uint32_t param);

/**
 * @brief Set Chip enter low power mode(DeepSleep).
 *
 * @param secs      the chip wake up after secs second.
 * @return          the actual sleep time, unit is second
 *
 * @note    The chip will be always sleep untill wakeup by IRQ if secs is 0.
 */
uint32_t PlatformSleep(uint32_t secs);

/**
 * @TODO:The following code must be implement by the user
 */

/**
 * @brief Enable or disable external GPIO for user
 *
 * @param   enable      true is enable , false is disable
 */
void UserExternalGPIO(bool enable);

/**
 * @FIXME:The following code should be customized by the user
 */

/**
 * @brief Enable or disable external GPIO for user
 *
 * @param   reinit          true is reinit, false is first init
 * @param   baudrateType    refer baudrate define from hal_def.h
 * @param   pariType        refer Parity define from hal_def.h
 * @return  true if success else false.
 */
bool UserDebugInit(bool reinit, uint32_t baudrateType, uint8_t pariType);

void UserDebugDeInit(void);

/**
 * @brief Write the data using the serial port initialized above
 *
 * @param   data    the pointer of data to be write
 * @param   len     the length of data to be write
 */
void UserDebugWrite(const uint8_t *data, uint32_t len);

void UserEnterAT(bool enable);

void UserCheckAT(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

/*******************************************************************************
 * @file    dev_config.h
 * @brief   The platform device flash configuration API
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef PLATFORM_DEV_CONFIG_H
#define PLATFORM_DEV_CONFIG_H

/****
Include Files
****/
#include <stdint.h>
#include <stdbool.h>

/****
Definitions
****/
#define FLASH_PARAM_VERSION     0x04

#define FREQ_NEXT_STEP          200000U

/* default use 470MHz region standard */
#define DEFAULT_FREQ_UPLINK     475500000U
#define DEFAULT_FREQ_DWLINK     506500000U

/****
Global Functions
****/
void DevCfg_InitParam(void);
void DevCfg_Recovery(void);
void DevCfg_Display(void);

/* User special parameters using param fields in @struct device_flash_t */
void DevCfg_UserDefault(void);
bool DevCfg_UserUpdate(uint8_t *data, uint32_t len);

#endif

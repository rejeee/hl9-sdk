/*******************************************************************************
 * @file    dev_radio.h
 * @brief   Radio Interface drivers
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef PLATFORM_DEV_RADIO_H
#define PLATFORM_DEV_RADIO_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Init Radio RST GPIO */
void DevRadioGPIORST(void);

/**
 * @param   enable      true is enable , false is disable
 *
 * @brief Enable Radio GPIO and SPI
 */
void DevRadioGPIO(bool enable);

/**
 * @brief IO interrupt service rutine
 */
void DevRadioIRQHandler(uint32_t u32Param);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

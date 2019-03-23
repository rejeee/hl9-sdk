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

/****
Include Files
****/
#include <stdint.h>
#include <stdbool.h>

/*!
 * @brief Enable Radio GPIO and SPI
 */
void DevRadioGPIO(bool enable);

/*!
 * @brief IO interrupt service rutine
 */
void DevRadioIRQHandler(uint8_t u8Param);

#endif

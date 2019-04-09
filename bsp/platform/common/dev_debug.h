/*******************************************************************************
 * @file    dev_debug.h
 * @brief   A UART driver for DEBUG COM.
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef PLATFORM_DEV_DEBUG_H
#define PLATFORM_DEV_DEBUG_H

#include "bsp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize a UART to be use debug print
 *
 * @param   ptr     the pointer of UART struct
 * @param   buf     the pointer of UART data buffer
 * @param   size    the size of UART data buffer
 *
 * @return  true if success else false
 */
bool DevDebug_Init(const BSP_UART_TypeDef* ptr, uint8_t *buf, uint32_t size);

/**
 * @brief ReInitialize the UART with the pointer of UART struct
 *
 * @param   ptr     the pointer of UART struct
 *
 * @return  true if success else false
 */
bool DevDebug_ReInit(const BSP_UART_TypeDef* ptr);

/**
 * @brief Read data into data from UART and return the data size,
 *        if there are not data arrived when timeout is exceed, then return 0
 *
 * @param   data       save the data which read from UART
 * @param   max_size   the max number bytes to be read
 * @param   timeout    the max wait time for read opeartion
 *
 * @return  the size of data which read
 */
uint32_t DevDebug_Read(uint8_t *data, uint32_t max_size, uint32_t timeout);

/**
 * @brief Put a byte into a fifo from UART RX_DATA
 *
 * @param   userData      the data to be written
 */
void DevDebug_IRQHandler(uint32_t userData);

void DevDebug_FlushAll(uint32_t timeout);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

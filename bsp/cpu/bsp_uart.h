/*******************************************************************************
 * @file    bsp_uart.h
 * @brief   UART application interface
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef BSP_CPU_UART_H
#define BSP_CPU_UART_H

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>
#include "hal_def.h"
#include "em_device.h"

/****
Function Declaration
****/

/**
 * @brief Init UART with input pointer
 *
 * @param ptr    The pointer of UART initialization structure
 */
void BSP_UartInit(const BSP_UART_TypeDef *ptr);

/**
 * @brief DeInit UART
 *
 * @param num   The number of UART with enum BSP_UART_NUM
 */
void BSP_UartDeInit(BSP_UART_NUM num);

/**
 * @brief Enable or Disable UART Rx
 *
 * @param num       The number of UART with enum BSP_UART_NUM
 * @param enable    true is enable else false is disable
 */
void BSP_UartRxEnable(BSP_UART_NUM num, bool enable);

/**
 * @brief UART send the size bytes buffer data
 *
 * @param num     The number of UART with enum BSP_UART_NUM
 * @param data    the pointer of data buffer
 * @param len     the length of data buffer
 */
void BSP_UartSend(BSP_UART_NUM num, const uint8_t *data, uint32_t len);

/**
 * @brief Get baudrate of baudrate type mapping
 *
 * @param bdtype  @see hal_def.h
 *
 * @return  the actual baudrate
 */
uint32_t BSP_UartGetBaudRate(uint8_t bdtype);

/**
 * @brief Enable or Disable UART Port
 *
 * @param ptr       The pointer of UART initialization structure
 * @param enable    true is enable else false is disable
 *
 */
void BSP_UartPortEnable(const BSP_UART_TypeDef *ptr, bool enable);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

/*******************************************************************************
 * @file    dev_uart.h
 * @brief   A common UART driver
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef PLATFORM_DEV_UART_H
#define PLATFORM_DEV_UART_H

#include "bsp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize a UART to be use debug print
 *
 * @param   ptr     the pointer of UART struct
 * @param   sp      the pointer of UART FIFO Handler
 * @param   buf     the pointer of UART data buffer
 * @param   size    the size of UART data buffer
 *
 * @return  true if success else false
 */
bool DevUART_Init(const BSP_UART_TypeDef* ptr, const struct sp_uart_t *sp,
                  uint8_t *buf, uint32_t max_size);

/**
 * @brief ReInitialize the UART with the pointer of UART struct
 *
 * @param   ptr     the pointer of UART struct
 *
 * @return  true if success else false
 */
bool DevUART_ReInit(const BSP_UART_TypeDef* ptr);

/**
 * @brief Read data into data from UART and return the data size,
 *        if there are not data arrived when timeout is exceed, then return 0
 *
 * @param   sp          the pointer of UART FIFO Handler
 * @param   data        save the data which read from UART
 * @param   max_size    the max number bytes to be read
 * @param   timeout     the max wait time for read opeartion
 *
 * @return  the size of data which read
 */
uint32_t DevUART_Read(const struct sp_uart_t *sp, uint8_t *data, uint32_t max_size,
                      uint32_t timeout);

uint32_t DevUART_WriteAndRead(const struct sp_uart_t *sp, uint8_t *wdata, size_t wlen,
                              uint8_t *rdata, uint32_t timeout);

/**
 * @brief Put a byte into a fifo from UART RX_DATA.
 * @note  Please fetch data as quickly if FIFO is overrun
 *
 * @param   sp          the pointer of UART FIFO Handler
 * @param   userData    the data to be written
 * @return  -2      sp is invalid(pointer or pointer content is NULL)
 *          -1      FIFO is overrun and post fail
 *          0       FIFO is overrun but post success
 *          1       put data into FIFO and post success
 *          2       put data into FIFO but post fail
 */
int DevUART_IRQHandler(const struct sp_uart_t *sp, uint32_t userData);

void DevUART_FlushAll(const struct sp_uart_t *sp, uint32_t timeout);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

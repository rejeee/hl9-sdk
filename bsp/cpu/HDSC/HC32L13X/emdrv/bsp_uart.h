/*******************************************************************************
 * @file    bsp_uart.h
 * @brief   UART application interface
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef BSP_CPU_UART_H
#define BSP_CPU_UART_H

/****
Include Files
****/
#include <stdbool.h>
#include "uart.h"
#include "lpuart.h"
#include "gpio.h"
#include "hal_def.h"

/**
 * @brief UART NO.
 * @enum BSP_UART_NUM
 */
typedef enum {
    BSP_LPUART0 = 0,    /**<    LPUART0         */
    BSP_LPUART1,        /**<    LPUART1         */
    BSP_UART0,          /**<    UART0           */
    BSP_UART1,          /**<    UART1           */
    BSP_UART_INVALID    /**<    Invalid UART    */
} BSP_UART_NUM;

/** @brief UART transfer callback function. */
typedef void (*uart_callback_t)(uint32_t userData);

/**
 * @brief UART initialization structure.
 * @struct BSP_UART_TypeDef
 */
typedef struct
{
    uart_callback_t     cb;
    en_gpio_port_t  	tx_port;
    en_gpio_pin_t   	tx_pin;
    en_gpio_port_t  	rx_port;
    en_gpio_pin_t   	rx_pin;
    en_gpio_af_t    	af;
    BSP_UART_NUM        num;
    uint8_t             bdtype;
    uint8_t    	        pri;
} BSP_UART_TypeDef;

/****
Global Variables
****/

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

#endif

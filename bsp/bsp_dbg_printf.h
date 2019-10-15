/*******************************************************************************
 * @file    bsp_dbg_printf.h
 * @brief   A formatted data output functions API.
 *   Support styles "%[f][w][.p]s"
 *   [f]: format flags:'-', '+', '#', ' ', '0'
 *   [w]: data integer width(0,1...)
 *   [.p]: data decimal width(0,1...)
 *   [s]: specifier, eg: 'd', 'i', 'f', 'F', 'x', 'X', 'o', 'p', 'u', 'c', 's', 'n'
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef BSP_DBG_PRINTF_H
#define BSP_DBG_PRINTF_H

#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "cpu/bsp_uart.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define PRINTF      BSP_Printf
#define PUTCHAR     BSP_Putchar

#define printk      BSP_Printf

/** @brief UART transfer callback function. */
typedef void (*PutChar)(const uint8_t *buffer, uint32_t length);

/**
 * @brief Initializes the UART peripheral for print messages.
 */
void BSP_DbgInit(BSP_UART_IDX comIdx, PutChar callback);

/**
 * @brief De-initializes the peripheral used for print messages.
 *       Call this function to stop print and disable the UART peripheral.
 *
 * @return Indicates whether de-initialization was successful or not.
 */
void BSP_DbgDeinit(void);

/**
 * @brief Writes formatted output to the standard output stream.
 *
 * @param   fmt_s   Format control string.
 * @return  the number of characters printed or a negative value if an error occurs.
 */
int BSP_Printf(const char *fmt_s, ...);

/**
 * @brief Writes a character to stdout.
 *
 * @param   ch  Character to be written.
 * @return  the character written.
 */
int BSP_Putchar(int ch);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

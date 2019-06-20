/*******************************************************************************
 * @file    bsp.h
 * @brief   The common board support library for all kinds of platform
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef  BSP_H
#define  BSP_H

#define  LOG_ERR(x)
#define  LOG_INFO(x)
#define  LOG_DEBUG(x)

#include "app_cfg.h"
#include "bsp_RTX.h"
#include "cpu/bsp_cpu.h"
#include "utils/util.h"
#include "utils/ringfifo.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */


/**
 * @brief the pointer of uart rx operation
 */
struct sp_uart_t
{
    BSP_OS_SEM      rx_sem;     /**< BSP_OS_SEM should be a pointer type */
    Ringfifo*       rx_fifo;    /**< UART Rx FIFO */
    uint32_t        timeout;    /**< The min timeslice of between two frames */
};

/****
Global Variables
****/
extern char*            gCodeVers;
extern BSP_OS_SEM       gIRQSem;
extern BSP_OS_SEM       gScanSem;

/****
Global Functions
****/
bool BSP_OS_Init(bool exth, bool extl);

void BSP_DelayMsWithDog(uint32_t dly_ms);

void BSP_OS_RandSeed(uint32_t seed);

uint32_t BSP_OS_Rand(uint32_t max);

uint32_t BSP_UartSplitTime(uint32_t baudrateType);

/** @name customer printf ouput function */
/*@{*/
int printk(const char *fmt_s, ...);
/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif


/*******************************************************************************
 * @file    bsp_watchdog.h
 * @brief   Device watchdog interface.
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef  BSP_CPU_WATCHDOG_H
#define  BSP_CPU_WATCHDOG_H

/****
Include Files
****/
#include "wdt.h"

/**
 * @brief Initialize watchdog
 * @param  wov  the watchdog overflow count
 */
void BSP_WatchdogInit(uint32_t wov);

/**
 * @brief Feed watchdog
 */
void BSP_WatchdogFeed(void);

#endif

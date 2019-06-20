/*******************************************************************************
 * @file    bsp_clock.h
 * @brief   the device clock API
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef BSP_CPU_CLOCK_H
#define BSP_CPU_CLOCK_H

/****
Include Files
****/
#include "flash.h"
#include "sysctrl.h"
#include <stdbool.h>

/**
 * @brief default unuse external high frequency
 */
#ifndef USE_CLOCK_EXTH
    #define USE_CLOCK_EXTH          0
#endif

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/**
 * @brief Chip clock initialize
 *
 * @param exth  use external high frequency
 * @param extl  use external low frequency
 */
void BSP_ClockInit(bool exth, bool extl);

/**
 * @todo Function has been not implemented yet.
 */
void BSP_ClockDeInit(void);

/**
 * @brief   Inaccurate delay function with RCH24MHz
 *
 * @param count    the wait time, unit us
 *
 * @note    the follow code execute ~5 us if count = 5
 */
void BSP_ClockdelayUs(int count);

/**
 * @brief check EXTL clock if or not ok
 *
 * @param waitms    the wait time, unit ms with RCH24MHz
 *
 * @return the actual times
 */
uint32_t BSP_ClockCheck(const uint32_t waitms);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif

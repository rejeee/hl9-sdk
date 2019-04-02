/*******************************************************************************
 * @file bsp_rtc.h
 * @brief The RTC Driver API
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef BSP_CPU_RTC_H
#define BSP_CPU_RTC_H

/****
Include Files
****/
#include <stdbool.h>
#include "rtc.h"

/*!
 * @brief RTC mode initialization
 */
void BSP_RTC_Init(bool ext, stc_rtc_time_t *rtcTime, stc_rtc_cyc_sel_t *rtcCycSel, func_ptr_t callback);

bool BSP_RTC_Elapse(const stc_rtc_time_t* oldTimeDate, uint32_t *elapse);

bool BSP_RTC_GetTime(stc_rtc_time_t *curTime);

void BSP_RTC_DeInit(void);

#endif

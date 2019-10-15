/*******************************************************************************
 * @file bsp_rtc.h
 * @brief The RTC Driver API
 *
 * @version 1.0.0
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
#include "em_device.h"

/**
 * @brief RTC mode initialization
 */
bool BSP_RTC_Init(const BSP_RTC_TypeDef *ptr);

void BSP_RTC_DeInit(void);

void BSP_RTC_WakeUp(uint32_t secs);

/**
 * @brief Get the current time from RTC registers
 *
 * @return   secs    Seconds count of RTC All registers
 *                   contain Year Month Day Hour Minute Second
 *
 * @Note    Equivalent seconds count from 1 January 2000
 */
uint32_t BSP_RTC_GetSecs(void);
bool BSP_RTC_GetDateTime(stc_rtc_time_t *ptr);

/**
 * @brief Set the current time into RTC registers
 *
 * @param   secs    Seconds count from 1 January 2000
 */
bool BSP_RTC_SetSecs(uint32_t secs);

bool BSP_RTC_SetDateTime(stc_rtc_time_t *ptr);

uint32_t BSP_RTC_RtcTimeToSecs(const stc_rtc_time_t *ptr);
void BSP_RTC_SecsToRtcTime(uint32_t secs, stc_rtc_time_t *ptr);

#endif

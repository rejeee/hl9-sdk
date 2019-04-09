/*******************************************************************************
 * @file bsp_adc.h
 * @brief The ADC Driver API
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef BSP_CPU_ADC_H
#define BSP_CPU_ADC_H

/****
Include Files
****/
#include <stdint.h>
#include "sysctrl.h"
#include "gpio.h"
#include "adc.h"

/*!
 * @brief ADC mode initialization
 */
void BSP_ADC_Enable(void);

void BSP_ADC_Disable(void);

uint32_t BSP_ADC_Sample(uint8_t channel);

#endif

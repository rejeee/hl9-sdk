/*******************************************************************************
 * @file bsp_adc.h
 * @brief The ADC Driver API
 *
 * @version 1.0.0
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
#include "em_device.h"

/**
 * @brief ADC mode initialization
 */
void BSP_ADC_Enable(void);

void BSP_ADC_Disable(void);

uint32_t BSP_ADC_Sample(uint8_t channel);

#endif

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
#include <stdbool.h>
#include "em_device.h"

/**
 * @brief ADC mode initialization
 */
void BSP_ADC_Init(const BSP_ADC_TypeDef *ptr);

/**
 * @brief Enable ADC Peripheral(some MCU contain ADC calibration)
 *
 * @param ptr    the pointer of ADC structure
 */
void BSP_ADC_Enable(const BSP_ADC_TypeDef *ptr);

/**
 * @brief Disable ADC Peripheral(it must be enable again if you disable)
 *
 * @param ptr    the pointer of ADC structure
 */
void BSP_ADC_Disable(const BSP_ADC_TypeDef *ptr);

/**
 * @brief enable or disable ADC ContinuousMode
 *
 * @param adcIdx    the index of ADC Peripheral
 * @param enable    disable or enable
 */
void BSP_ADC_Continuous(const BSP_ADC_IDX adcIdx, bool enable);

/**
 * @brief Get a channel ADC sample value, unit is mV
 *
 * @param adcIdx    the index of ADC Peripheral
 * @param ch        ADC channel NO.
 *
 * @return the channel sample value
 */
uint32_t BSP_ADC_Sample(const BSP_ADC_IDX adcIdx, uint8_t ch);

/**
 * @brief Get cpu internal tempearature
 *
 * @param val   the value of Vsensor, unit is mV
 *
 * @return unit is 0.01 degree
 */
int BSP_ADC_CPU_Teamp(int val);

#endif

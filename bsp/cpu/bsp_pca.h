/*******************************************************************************
 * @file bsp_pca.h
 * @brief PCA Interface driver
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef BSP_CPU_PCA_H
#define BSP_CPU_PCA_H

#include <stdbool.h>
#include "em_device.h"

bool BSP_PCA_Init(BSP_PCA_TypeDef *ptr);

bool BSP_PCA_PWM(uint8_t pcaMode);

#endif

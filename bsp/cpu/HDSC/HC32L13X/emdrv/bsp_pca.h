/*******************************************************************************
 * @file bsp_pca.h
 * @brief PCA Interface driver
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef BSP_CPU_PCA_H
#define BSP_CPU_PCA_H

#include <stdbool.h>
#include "pca.h"
#include "gpio.h"

bool BSP_PCA_PwmInit(en_pca_module_t pcaMode);

#endif

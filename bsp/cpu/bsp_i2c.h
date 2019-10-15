/*******************************************************************************
 * @file bsp_i2c.h
 * @brief I2C Interface driver
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef BSP_CPU_I2C_H
#define BSP_CPU_I2C_H

#include <stdbool.h>
#include "em_device.h"
#include "hal_def.h"

/*******************************************************************************
 * @brief
 *   Initalize basic I2C master mode driver.
 *
 * @details
 *   This driver only supports master mode, single bus-master.
 *
 * @param[in] init
 *   Pointer to I2C initialization structure.
 ******************************************************************************/
void BSP_I2C_Init(BSP_I2C_TypeDef *ptr);

/*******************************************************************************
 * @brief
 *   Perform I2C transfer write data into the slave device.
 *   exemple:S+ADDR(W)+DATA0+P.
 *
 * @details
 *   This driver only supports master mode, single bus-master. It does not
 *   return until the transfer is complete, polling for completion.
 *
 * @param[in] data      the pointer of data to be write
 * @param[in] len       the length of data to be write
 *
 * @return  true if success else false
 ******************************************************************************/
bool BSP_I2C_Write(BSP_Slave_Param *ptr, uint8_t *data, int len);

/*******************************************************************************
 * @brief
 *   Perform I2C transfer read data from the slave device.
 *   exemple:
 *
 *   if write register and read :S+ADDR(W)+DATA0+Sr+ADDR(R)+DATA1+P.
 *   if direct read from slave :S+ADDR(R)+DATA0~1+P.
 *
 * @details
 *   This driver only supports master mode, single bus-master. It does not
 *   return until the transfer is complete, polling for completion.
 *
 * @param[in] data      the pointer of data to be read
 * @param[in] len       the length of data to be read
 *
 * @return  true if success else false
 ******************************************************************************/
bool BSP_I2C_Read(BSP_Slave_Param *ptr, uint8_t *data, int len);

#endif

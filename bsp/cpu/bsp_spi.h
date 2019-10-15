/*******************************************************************************
 * @file    bsp_spi.h
 * @brief   SPI Interface drivers
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef BSP_CPU_SPI_H
#define BSP_CPU_SPI_H

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>
#include "em_device.h"

/**
 * @brief Init SPI with input pointer
 *
 * @param ptr    The pointer of SPI initialization structure
 */
void BSP_SPI_Init(BSP_SPI_TypeDef *ptr);
void BSP_SPI_PortInit(BSP_SPI_TypeDef *ptr);

/**
 * @brief DeInit SPI
 *
 * @param spiIdx    The index of SPI
 */
void BSP_SPI_DeInit(BSP_SPI_IDX spiIdx);

/**
 * @brief Write data to SPI
 *
 * @param spiIdx    The number of SPI
 * @param addr      The register address of SPI device
 * @param data      The data buffer to be write
 * @param len       The data length to be write
 *
 * @return          true if write success else false
 */
bool BSP_SPI_Write(BSP_SPI_IDX spiIdx, uint8_t addr, const uint8_t* data, uint32_t len);

bool BSP_SPI_ReadWrite(BSP_SPI_IDX spiIdx, uint8_t addr, uint8_t* data, uint32_t len);

void BSP_SPI_SetCS(BSP_SPI_IDX spiIdx, bool high);
uint16_t BSP_SpiReadWrite(BSP_SPI_IDX spiIdx, uint16_t data);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

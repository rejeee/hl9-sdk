/*******************************************************************************
 * @file    bsp_spi.h
 * @brief   SPI Interface drivers use SPI
 *
 * @version 0.0.2
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef BSP_CPU_SPI_H
#define BSP_CPU_SPI_H

/****
Include Files
****/
#include <stdbool.h>
#include "spi.h"
#include "gpio.h"

/**
 * @brief SPI NO.
 * @enum BSP_SPI_NUM
 */
typedef enum {
    BSP_SPI0 = 0,       /**<    SPI0            */
    BSP_SPI1,           /**<    SPI1            */
    BSP_SPI_INVALID     /**<    Invalid SPI No. */
} BSP_SPI_NUM;

/**
 * @brief SPI initialization structure.
 * @struct BSP_SPI_TypeDef
 */
typedef struct
{
    BSP_SPI_NUM     num;    /**<    SPI No.             */
    en_gpio_port_t  gpio;   /**<    SPI Port            */
    en_gpio_pin_t   nss;    /**<    the Pin of SPI CS   */
    en_gpio_pin_t   sck;    /**<    the Pin of SPI CLK  */
    en_gpio_pin_t   miso;   /**<    the Pin of SPI MISO */
    en_gpio_pin_t   mosi;   /**<    the Pin of SPI MOSI */
    en_gpio_af_t    af;     /**<    SPI alter function  */
} BSP_SPI_TypeDef;

/**
 * @brief Init SPI with input pointer
 *
 * @param ptr    The pointer of SPI initialization structure
 */
void BSP_SPI_Init(BSP_SPI_TypeDef *ptr);

/**
 * @brief DeInit SPI
 *
 * @param spiNum    The number of SPI
 */
void BSP_SPI_DeInit(BSP_SPI_NUM spiNum);

/**
 * @brief Write data to SPI
 *
 * @param spiNum    The number of SPI
 * @param addr      The register address of SPI device
 * @param data      The data buffer to be write
 * @param len       The data length to be write
 *
 * @return          true if write success else false
 */
bool BSP_SPI_Write(BSP_SPI_NUM spiNum, uint8_t addr, const uint8_t* data, uint32_t len);

bool BSP_SPI_ReadWrite(BSP_SPI_NUM spiNum, uint8_t addr, uint8_t* data, uint32_t len);

#endif

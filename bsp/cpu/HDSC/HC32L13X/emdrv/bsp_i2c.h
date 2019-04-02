/*******************************************************************************
 * @file bsp_i2c.h
 * @brief I2C Interface driver
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef BSP_CPU_I2C_H
#define BSP_CPU_I2C_H

#include <stdbool.h>
#include "i2c.h"
#include "gpio.h"

/**
 * I2C BaudRate mode
 */
typedef enum
{
    I2C_BAUD_NORMAL = 0u,   /* Standard rate = 100Kbps  */
    I2C_BAUD_FAST,          /* Fast rate = 400Kbps      */
    I2C_BAUD_MAX            /* Fast rate = 1000Kbps     */
} I2C_BaudrateMode;

/** Master mode transfer states. */
typedef enum
{
  i2cStateStartAddrSend     = 0x08, /**< Send start + (first part of) address. */
  i2cStateRStartAddrSend    = 0x10, /**< Send repeated start + (first part of) address. */
  i2cStateAddrWFAckNack     = 0x18, /**< Wait for ACK/NACK on (first part of) address. */
  i2cStateRAddrWFAckNack    = 0x40, /**< Wait for ACK/NACK on address sent after repeated start. */
  i2cStateDataSend          = 0x28, /**< Send data. */
  i2cStateWFData            = 0x50, /**< Wait for data. */
  i2cStateWFStopSent        = 0x58, /**< Wait for STOP to have been transmitted. */
  i2cStateDone                      /**< Transfer completed successfully. */
} I2C_TransferState;

/** I2C initialization structure. */
typedef struct
{
    I2C_BaudrateMode    baudmode;
    uint8_t             i2c_idx;
    en_gpio_port_t      scl_port;
    en_gpio_pin_t       scl_pin;
    en_gpio_port_t      sda_port;
    en_gpio_pin_t       sda_pin;
    en_gpio_af_t        af;
} BSP_I2C_TypeDef;

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
void BSP_I2CInit(BSP_I2C_TypeDef *ptr);

/*******************************************************************************
 * @brief
 *   Perform I2C transfer write data into the slave device.
 *   exemple:S+ADDR(W)+DATA0+P.
 *
 * @details
 *   This driver only supports master mode, single bus-master. It does not
 *   return until the transfer is complete, polling for completion.
 *
 * @param[in] i2c_idx   the index of I2C
 * @param[in] addr      the address of data to be write
 * @param[in] data      the pointer of data to be write
 * @param[in] len       the length of data to be write
 *
 * @return  true if success else false
 ******************************************************************************/
bool BSP_I2CWrite(uint8_t i2c_idx, uint8_t addr, uint8_t *data, uint32_t len);

/*******************************************************************************
 * @brief
 *   Perform I2C transfer read data from the slave device.
 *   exemple:S+ADDR(W)+DATA0+Sr+ADDR(R)+DATA1+P.
 *
 * @details
 *   This driver only supports master mode, single bus-master. It does not
 *   return until the transfer is complete, polling for completion.
 *
 * @param[in] i2c_idx   the index of I2C
 * @param[in] addr      the address of data to be read
 * @param[in] regs      the register of Slave module
 * @param[in] data      the pointer of data to be read
 * @param[in] len       the length of data to be read
 *
 * @return  true if success else false
 ******************************************************************************/
bool BSP_I2CWriteAndRead(uint8_t i2c_idx, uint8_t addr, uint8_t regs, uint8_t *data, uint32_t len);

/*******************************************************************************
 * @brief
 *   Perform I2C transfer read data from the slave device.
 *   exemple:S+ADDR(R)+DATA0~1+P.
 *
 * @details
 *   This driver only supports master mode, single bus-master. It does not
 *   return until the transfer is complete, polling for completion.
 *
 * @param[in] i2c_idx   the index of I2C
 * @param[in] addr      the address of data to be read
 * @param[in] data      the pointer of data to be read
 * @param[in] len       the length of data to be read
 *
 * @return  true if success else false
 ******************************************************************************/
bool BSP_I2CRead(uint8_t i2c_idx, uint8_t addr, uint8_t *data, uint32_t len);

#endif

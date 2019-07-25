/*******************************************************************************
 * @file    em_device.h
 * @brief   common embedded device type define
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef  CPU_EM_DEVICE_H
#define  CPU_EM_DEVICE_H

#include "flash.h"
#include "gpio.h"
#include "lpuart.h"
#include "spi.h"
#include "reset.h"
#include "adc.h"

typedef volatile unsigned long vu32;

/** @brief UART transfer callback function. */
typedef void (*uart_callback_t)(uint32_t userData);

/**
 * @brief UART NO.
 * @enum BSP_UART_NUM
 */
typedef enum {
    BSP_LPUART0 = 0,    /**<    LPUART0         */
    BSP_LPUART1,        /**<    LPUART1         */
#ifndef USE_NO_UART
    BSP_UART0,          /**<    UART0           */
    BSP_UART1,          /**<    UART1           */
#endif
    BSP_UART_INVALID    /**<    Invalid UART    */
} BSP_UART_NUM;

/**
 * @brief UART initialization structure.
 * @struct BSP_UART_TypeDef
 */
typedef struct
{
    uart_callback_t     cb;
    en_gpio_port_t  	gpio;
    en_gpio_pin_t   	tx_pin;
    en_gpio_pin_t   	rx_pin;
    en_gpio_af_t    	af;
    en_gpio_pupd_t      pd;
    BSP_UART_NUM        num;
    uint8_t             bdtype;
    uint8_t    	        pri;
} BSP_UART_TypeDef;

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
typedef struct {
    en_gpio_port_t  gpio;   /**<    SPI Port            */
    en_gpio_pin_t   nss;    /**<    the Pin of SPI CS   */
    en_gpio_pin_t   sck;    /**<    the Pin of SPI CLK  */
    en_gpio_pin_t   miso;   /**<    the Pin of SPI MISO */
    en_gpio_pin_t   mosi;   /**<    the Pin of SPI MOSI */
    en_gpio_af_t    af;     /**<    SPI alter function  */
    BSP_SPI_NUM     num;    /**<    SPI No.             */
} BSP_SPI_TypeDef;

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

#endif

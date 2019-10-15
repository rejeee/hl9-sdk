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
#include "rtc.h"

typedef volatile uint32_t vu32;
typedef volatile uint16_t vu16;
typedef volatile uint8_t vu8;

/** @brief UART transfer callback function. */
typedef void (*uart_callback_t)(uint32_t userData);

/**
 * @brief UART NO.
 * @enum BSP_UART_IDX
 */
typedef enum {
    BSP_LPUART0 = 0,    /**<    LPUART0         */
    BSP_LPUART1,        /**<    LPUART1         */
#ifndef USE_NO_UART
    BSP_UART0,          /**<    UART0           */
    BSP_UART1,          /**<    UART1           */
#endif
    BSP_UART_INVALID    /**<    Invalid UART    */
} BSP_UART_IDX;

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
    BSP_UART_IDX        idx;
    uint8_t             bdtype;
    uint8_t    	        pri;
} BSP_UART_TypeDef;

/**
 * @brief SPI NO.
 * @enum BSP_SPI_IDX
 */
typedef enum {
    BSP_SPI0 = 0,       /**<    SPI0            */
    BSP_SPI1,           /**<    SPI1            */
    BSP_SPI_INVALID     /**<    Invalid SPI No. */
} BSP_SPI_IDX;

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
    BSP_SPI_IDX     idx;    /**<    SPI No.             */
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
    uint8_t             idx;
    en_gpio_port_t      scl_port;
    en_gpio_pin_t       scl_pin;
    en_gpio_port_t      sda_port;
    en_gpio_pin_t       sda_pin;
    en_gpio_af_t        af;
} BSP_I2C_TypeDef;

/**
 * @brief ADC NO.
 * @enum BSP_ADC_IDX
 */
typedef enum {
    BSP_ADC1 = 0,       /**<    ADC1            */
    BSP_ADC2,           /**<    ADC2            */
    BSP_ADC3,           /**<    ADC3            */
    BSP_ADC_INVALID     /**<    Invalid ADC No. */
} BSP_ADC_IDX;

/**
 * @brief ADC initialization structure.
 *
 * @struct BSP_ADC_TypeDef
 *
* @FIXME    current API unused this structure
 */
typedef struct
{
    en_gpio_port_t  gpio;
    uint8_t         ref;        /**> ADC reference index */
    uint8_t         single;     /**> single or continuous mode */
} BSP_ADC_TypeDef;

typedef struct
{
    func_ptr_t      callback;
    stc_rtc_time_t  *dateTime;
    uint8_t         extl;
} BSP_RTC_TypeDef;

#endif

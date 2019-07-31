/*******************************************************************************
 * @file    at_api.h
 * @brief   The common API
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef AT_API_H
#define AT_API_H

/****
Include Files
****/
#include <stdint.h>
#include <string.h>
#include "hal_def.h"

/** @name AT command version */
/*@{*/
/** @brief AT command version */
#define AT_VER                          5
/*@}*/

/** @brief AT OK response */
#define AT_STR_OK                       "\r\nOK\r\n"

/** @brief AT command minimal length */
#define AT_CMD_MIN_LEN                  4U

/** @brief AT command maximal length */
#define AT_CMD_MAX_LEN                  255U

/** @brief AT command max prefix length, example AT+XXXX= */
#define AT_CMD_PREFIX_LEN               10U

/** @brief AT command max parameter length, example AT+AK= XXXX */
#define AT_CMD_PARAM_LEN                32U

/*! @brief the byte length of AT parameter. */
enum {
    CFG_1BYTE_LEN  = 1U,    /**< 1 Byte  */
    CFG_2BYTE_LEN  = 2U,    /**< 2 Byte  */
    CFG_4BYTE_LEN  = 4U,    /**< 4 Byte  */
    CFG_8BYTE_LEN  = 8U,    /**< 8 Byte  */
    CFG_16BYTE_LEN = 16U    /**< 16 Byte */
};

/*! @brief the AT enable type for diffrence device. */
typedef enum
{
    AT_EN_ALL       = 0xFF,
    AT_EN_NODE      = 0x01,
    AT_EN_NODE_TX   = 0x02,
    AT_EN_GW81      = 0x04,
    AT_EN_GWX3      = 0x08
} AT_EN_TYPE;

enum {
    DATA_TYPE_SIMPLE = 0,
    DATA_TYPE_TLV,
    DATA_TYPE_FRAME,
    DATA_TYPE_JSON,
    DATA_TYPE_TLV_OLD,
    DATA_TYPE_NUM
};

enum {
    LOWRATE_OP_AUTO = 0x00,
    LOWRATE_OP_ON,
    LOWRATE_OP_OFF
};

/* the address mode */
enum {
    SIP_MODE_NONE  = 0U,
    SIP_ADDR_MASK  = 0x0FU,
    SIP_SEQ_MASK   = 0xF0U
};

/* Device RX printf format */
enum {
    RX_MODE_NONE   = 0U,
    RX_MODE_FACTORY,
    RX_MODE_NUM
};

/**
 * @enum AT_STATUS
 * @brief return result definition
 */
typedef enum
{
    AT_STATUS_NONE     = 0x00,  /**< no response need print */
    AT_STATUS_OK,               /**< respone "OK" */
    AT_STATUS_UNKNOWN,          /**< ER00 command unknown */
    AT_STATUS_PARAM,            /**< ER01 parameter is error */
    AT_STATUS_ERR,              /**< ER02 execute command fail */
    AT_STATUS_BUSY,             /**< ER03 radio channel is busy */
    AT_STATUS_LEN_ERR,          /**< ER04 length is error(overlap or empty) */
    AT_STATUS_FLASH_ERR,        /**< ER05 R/W flash fail */
    AT_STATUS_MEM_ERR,          /**< ER06 no free memory */
    AT_STATUS_TIMEOUT,          /**< ER07 TX timeout */
    AT_STATUS_UNUSED,           /**< ER08 cmd unsupport */
    AT_STATUS_ACCESS,           /**< ER09 cannot access */
    AT_STATUS_RX_ERR,           /**< radio rx error */
    AT_STATUS_CAD_ERR,          /**< CAD error */
    /**> NOTE: the follow code depend user customer funtion */
    AT_STATUS_H,                /**< AT command list */
    AT_STATUS_I,                /**< print device version */
    AT_STATUS_Z,                /**< restore factory configuration */
    AT_STATUS_R,                /**< software reset */
    AT_STATUS_T,                /**< switch AT mode */
    AT_STATUS_CFG,              /**< print configuration */
    AT_STATUS_CSQ,              /**< print rssi and snr */
    AT_STATUS_UART,             /**< change UART settings */
    AT_STATUS_SET_RF,
    AT_STATUS_SET_SYNC,         /**< transpond sync config into TX module */
    AT_STATUS_SET_LDR,
    AT_STATUS_SLEEP,            /**< delay ok for sleep */
    AT_STATUS_RX_MODE           /**< need change RX printf style */
} AT_STATUS;

extern uint8_t gAtEnableType;

extern const uint32_t gDevFlashSize;

/** @name the follow function need customer implement */

/*@{*/

/**
 * @brief  the AT Binary Log printf callback, must implement
 *
 * @param   ptr     the pointer of binary data
 * @param   len     the length of binary data
 */
void AT_LOG(const uint8_t *ptr, size_t len);

/**
 * @brief  the AT printf callback, must implement
 *
 * @param   str     the pointer of string to be printf output
 */
void AT_Printf(const char *str);

/**
 * @brief  the AT+TX command callback
 *
 * @param   forward    whether to forward this command.
 * @param   buf        the pointer of AT command string
 * @param   len        the length of AT command string
 *
 * return @see AT_STATUS
 */
uint32_t AT_TxProcess(bool forward, uint8_t *buf, uint32_t len);

/**
 * @brief  save customer configuration
 *
 * @param   data       the pointer of data buffer to to saved
 * @param   len        the length of data buffer to to saved
 *
 * return true if save successful else false.
 */
bool Flash_WriteParam(uint32_t *data, uint32_t len);

/*@}*/

#endif

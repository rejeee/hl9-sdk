/*******************************************************************************
 * @file at_config.h
 * @brief The platform device flash configuration API
 *
 * @version 0.0.1
 *******************************************************************************
 * @license refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef AT_CONFIG_H
#define AT_CONFIG_H

/****
Include Files
****/
#include "at/at_api.h"

/****
Definitions
****/

/** @name radio defines */
/*@{*/

/** @brief minimal radio frequency */
#define RF_FREQ_MIN             13e7

/** @brief maximal radio frequency */
#define RF_FREQ_MAX             105e7

/** @brief minimal spread spectrum  */
#define RF_SF_MIN_6             6U

/** @brief maximal spread spectrum  */
#define RF_SF_MAX_12            12U

/** @brief minimal code rate = 4/5  */
#define RF_CR_MIN_5             1U

/** @brief maximal code rate = 4/8  */
#define RF_CR_MAX_8             4U

/** @brief bandwidth = 500kHz  */
#define RF_BW_MAX_500           9U

/*@}*/

/** @brief Device EUI length */
#define DEV_EUI_LEN             8U

/** @brief Device address */
typedef uint32_t devaddr_t;

struct g_at_param_t {
    uint16_t    sleep_secs;     /**< sleep seconds    */
    uint8_t     rx_mode;        /**< indicate radio rx continue */
};

/**
 * @struct rps_t
 * @brief radio parameter set
 */
typedef struct
{
    uint32_t    bw     : 4;  /**> [0]:7.8kHz, [9]:500kHz             */
    uint32_t    cr     : 3;  /**> [1]:CR_4_5 ... [4]:CR_4_8          */
    uint32_t    crc    : 1;  /**> [0 CRC OFF, 1 CRC ON]              */
    uint32_t    fixlen : 11; /**> [0: variable; other: fixed length] */
} rps_t;

/**
 * @struct device_flash_t
 * @brief device configuration
 */
struct device_flash_t {
    rps_t       rps;
    uint32_t    syncword;                 /**> sync word */
    uint32_t    rxfreq;                   /**> RX frequency */
    uint32_t    txfreq;                   /**> TX frequency */
    uint32_t    freqa;                    /**> radio A */
    uint32_t    freqb;                    /**> radio B */
    uint32_t    step;                     /**> frequency increase step */
    devaddr_t   addr;                     /**> unicast address */
    uint8_t     appKey[CFG_16BYTE_LEN];
    devaddr_t   maddr;                    /**> multicast address */
    uint32_t    lat;                      /**> latitude */
    uint32_t    lgt;                      /**> longitude */
    uint16_t    tprem;
    uint16_t    rprem;
    uint16_t    lcp;                      /**> unit minute */
    uint16_t    lftime;                   /**> unit second */
    uint8_t     modem;                    /**> radio modem */
    uint8_t     tiq;
    uint8_t     riq;
    int8_t      txpow;
    int8_t      txChan;                   /**> TX channel number */
    uint8_t     adr;
    uint8_t     netmode;                  /**> LPWA network protocol mode */
    uint8_t     ipMode;                   /**> IP(Addr) mode: 0 no present, 1 present */
    uint8_t     seqMode;                  /**> seq mode: 0 no present, 1 present */
    uint8_t     baudrate;                 /**> AT command UART baudrate */
    uint8_t     ack;
    uint8_t     txsf;
    uint8_t     rxsf;
    uint8_t     lowRate;                  /**> low datarate optimize */
    uint8_t     pari;                     /**> UART odd or even */
    uint8_t     dtype;                    /**> data output format type */
    uint8_t     param[CFG_16BYTE_LEN];    /**> user parameters */

    uint8_t     flash_ver;                /**> flash structure version */
};

/**
 * @union DeviceFlash_t
 * @brief device configuration for save into flash
 */
typedef union
{
    struct device_flash_t config;
    uint32_t values[sizeof(struct device_flash_t)/sizeof(uint32_t) + 1];
} DeviceFlash_t;

/****
Glocal variables
****/
extern DeviceFlash_t  gDevFlash;
extern uint8_t gDevEUI[DEV_EUI_LEN];
extern struct g_at_param_t gDevRam;

/****
Global Functions
****/

/**
 * @brief  Set parameter into configuration from buf
 *
 * @param   cmd_type    the command byte to be read parameter
 * @param   buf         the pointer of parameter buffer
 * @param   len         the length of parameter buffer
 *
 * @return  @see AT_STATUS
 */
uint32_t AtCfg_SetParam(uint8_t cmd_type, uint8_t *buf, uint8_t len);

/**
 * @brief  Get parameter into buf from configuration
 *
 * @param   cmd_type    the command byte to be read parameter
 * @param   buf         the pointer of parameter buffer
 *
 * @return  the valid parameter length, if command is unknown, return 0
 */
int AtCfg_GetParam(uint8_t cmd_type, uint8_t *buf);

#endif

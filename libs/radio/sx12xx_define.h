/*******************************************************************************
 * @file    sx12xx_define.h
 * @brief   The definitions of SX12xx radio module
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef SX12XX_DEFINE_H
#define SX12XX_DEFINE_H

/****
Include Files
****/
#include <stdint.h>
#include "hal_def.h"

/****
Macro definiens
****/

/* Radio Chip Middle Frequency  */
#define RF_MID_BAND_THRESH       525000000U

/** @name SF defines */
/*@{*/

/** @brief SF5: 32  */
#define RF_SF_5                  5U
/** @brief SF6: 64  */
#define RF_SF_6                  6U
/** @brief SF7: 128, default  */
#define RF_SF_7                  7U
/** @brief SF8: 256  */
#define RF_SF_8                  8U
/** @brief SF9: 512  */
#define RF_SF_9                  9U
/** @brief SF10: 1024  */
#define RF_SF_10                 10U
/** @brief SF11: 2048  */
#define RF_SF_11                 11U
/** @brief SF12: 4096  */
#define RF_SF_12                 12U
/*@}*/

/** @name code rate defines */
/*@{*/

/** @brief code rate 4/5, default */
#define RF_CODERATE_4_5          1U
/** @brief code rate 4/6 */
#define RF_CODERATE_4_6          2U
/** @brief code rate 4/7 */
#define RF_CODERATE_4_7          3U
/** @brief code rate 4/8 */
#define RF_CODERATE_4_8          4U
/*@}*/

/** @name bandwidth defines */
/*@{*/

/** @brief bandwidth 7.8kHz */
#define RF_BANDWIDTH_7D8         0U

/** @brief bandwidth 10.4kHz */
#define RF_BANDWIDTH_10D4        1U

/** @brief bandwidth 15.6kHz */
#define RF_BANDWIDTH_15D6        2U

/** @brief bandwidth 20.8kHz */
#define RF_BANDWIDTH_20D8        3U

/** @brief bandwidth 31.2kHz */
#define RF_BANDWIDTH_31D2        4U

/** @brief bandwidth 41.7kHz */
#define RF_BANDWIDTH_41D7        5U

/** @brief bandwidth 62.5kHz */
#define RF_BANDWIDTH_62D5        6U

/** @brief bandwidth 125kHz, default */
#define RF_BANDWIDTH_125         7U

/** @brief bandwidth 250kHz */
#define RF_BANDWIDTH_250         8U

/** @brief bandwidth 500kHz */
#define RF_BANDWIDTH_500         9U
/*@}*/

/*
 *@brief Radio LoRa modem parameters
 */
typedef struct
{
    uint32_t bw         : 4;  /**< LORA [0: 7.8  kHz, 1: 10.4 kHz, 2: 15.6 kHz, 3: 20.8 kHz,
                                       4: 31.2 kHz, 5: 41.6 kHz, 6: 62.5 kHz, 7: 125 kHz,
                                       8: 250  kHz, 9: 500  kHz, other: Reserved] */
    uint32_t sf         : 4;  /**< LoRa: 6~12 */
    uint32_t cr         : 3;  /**< Coding rate (LoRa only)          */
    uint32_t iq         : 1;  /**< Inverts IQ signals (LoRa only)   */
    uint32_t lowrate    : 1;  /**< 0:OFF, 1: On */
    uint32_t symbtime   : 10;
} LoRaSettings_t;

/**
 *@brief Radio FSK modem parameters
 */
typedef struct
{
    uint32_t    fdev;       /**< FSK: Sets the frequency deviation (Hz) */
    uint32_t    bw;         /**< FSK: >= 2600 and <= 250000 Hz */
    uint32_t    bwafc;      /**< FSK: >= 2600 and <= 250000 Hz */
    uint32_t    dr;         /**< FSK: 600..300000 bits/s */
    uint32_t    rxtimeout;
} FskSettings_t;

#endif

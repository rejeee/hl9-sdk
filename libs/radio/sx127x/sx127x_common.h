/*******************************************************************************
 * @file    sx127x_common.h
 * @brief   The common interface for sx127x
 *
 * This is a convenience header file for defining difference radio chip.
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef SX127X_COMMON_H
#define SX127X_COMMON_H

/****
Include Files
****/
#include <stdint.h>
#include "radio/sx127x/sx127x_define.h"

/****
Macro definiens
****/

/** @name Radio HAL version */
/*@{*/
/** @brief Radio HAL version */
#define RADIO_HAL_VERSION       18U
/*@}*/

/** @brief 32MHz XTAL frequency */
#define RADIO_XOSC_FREQ         32000000U

/** @brief Radio TX/RX maximal payload */
#define RADIO_MAX_PAYLOAD       255U
#define RADIO_DEFAULT_FREQ      475500000U

#ifdef __cplusplus
extern "C" {
#endif

/****
type definiens
****/

/* Radio IRQ type */
typedef enum
{
  RADIO_IRQ_TIMEOUT = 0,
  RADIO_IRQ_LORA_TX,
  RADIO_IRQ_LORA_RX,
  RADIO_IRQ_FSK_TX,
  RADIO_IRQ_FSK_RX,
  RADIO_IRQ_RX_ERR,
  RADIO_IRQ_RX_TIMEOUT,
  RADIO_IRQ_UNKOWN
} RadioIrqType_t;

/*
 * Radio Quality Calculator
 */
typedef struct
{
    int32_t     freqerr;
    int16_t     rssi;       /* max physical RSSI range -198..+63 */
    int8_t      snr;        /* max physical SNR range -32..+31.75 */
} RadioQoS_t;

/**
 * Radio driver supported modems
 */
typedef enum
{
  MODEM_FSK = 0,
  MODEM_LORA
} RadioModems_t;

/**
 * Radio driver operation mode
 */
typedef enum
{
  OP_MODE_STANDBY = 0,
  OP_MODE_TX,
  OP_MODE_RX,
  OP_MODE_RX_SINGLE,
  OP_MODE_CAD
} RadioOpMode_t;

/**
 * Radio Settings
 */
typedef struct
{
  LoRaSettings_t    LoRa;
  FskSettings_t     Fsk;
  uint32_t          freq;
  uint32_t          syncword;
  uint32_t          preamb : 16;  /* RadioOpMode_t */
  uint32_t          modem  : 1;   /* [0: FSK; 1: LoRa] */
  uint32_t          crcon  : 1;   /* [0: OFF; 1: ON] */
  uint32_t          opmode : 3;   /* RadioOpMode_t */
  uint32_t          fixlen : 11;  /* [0: variable; other: fixed length] */
  int8_t            power;        /* the output power [dbm] */
  uint8_t           rfo;          /* rfo */
} RadioSettings_t;

#ifdef __cplusplus
}
#endif

#endif

/*******************************************************************************
 * @file mac_rdio.h
 * @brief Radio API by MAC invoke
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef MAC_RADIO_H
#define MAC_RADIO_H

/****
Include
****/
#include <stdbool.h>
#include "bsp.h"
#include "radio/sx127x/sx127x_common.h"

/****
Global Functions
****/
bool MacRadio_Init(void);

/**
 *@return AT_STATUS
 */
uint32_t MacRadio_TxProcess(uint8_t spiIdx, uint8_t *buf, uint32_t len, struct mac_lorawan_t *ptr);
uint32_t MacRadio_RxProcess(uint8_t spiIdx, bool reconfig);
uint32_t MacRadio_CadProcess(uint8_t spiIdx, bool reconfig);

/**
 *@brief Wait radio to be idle, if radio is continue mode,
 *        then post a signal to release it.
 *
 *@return true if success else false.
 */
bool MacRadio_AbortRx(uint8_t spiIdx);

bool RadioGetCanRx(uint8_t spiIdx);

/**
 * @brief Follow function need be implementation
 *
 * @FIXME: need user special implementation
 */
bool RadioWaitDone(uint8_t spiIdx, uint8_t semIdx, uint32_t timeout);
RadioIrqType_t RadioRxFinish(uint8_t spiIdx);
RadioIrqType_t RadioDecode(uint8_t spiIdx, struct sx127x_rx_t *rxObj, struct mac_lorawan_t *ptr);

bool RadioSemClear(uint8_t spiIdx, uint8_t semIdx);

void RadioCustomization(bool rx, RadioSettings_t *ptr);

#endif

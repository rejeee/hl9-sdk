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
#include "radio/sx12xx_common.h"

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
bool RadioWaitDone(uint8_t spiIdx, SemIndex_t semIdx, uint32_t timeout);
RadioIrqType_t RadioRxFinish(uint8_t spiIdx);
RadioIrqType_t RadioDecode(uint8_t spiIdx, struct sx12xx_rx_t *rxObj, struct mac_lorawan_t *ptr);

bool RadioSemClear(uint8_t spiIdx, SemIndex_t semIdx);

void RadioCustomization(uint8_t spiIdx, bool tx, RadioSettings_t *ptr);

/**
 * @brief Recheck LDR config for radio
 *
 * @param lowRate   LOWRATE_OP_AUTO
 *                  LOWRATE_OP_ON
 *                  LOWRATE_OP_OFF
 *
 * @param sf        <=RF_SF_12
 * @param bw        0~9(RF_BANDWIDTH_7D8~RF_BANDWIDTH_500)
 *
 * @return  1 enable Low DateRate Optimize
 *          0 disable Low DateRate Optimize
 */
uint8_t RadioCheckLDR(uint8_t lowRate, uint8_t sf, uint8_t bw);

/**
 * @brief Parse AT command from radio received data
 *
 * @param buf   the pointer of radio data
 * @param size  the size of radio data
 *
 * @return  -1  current is not invalid AT command
 *          >0  current AT command index of radio data
 */
int RadioDecodeAt(uint8_t *buf, uint32_t size, uint32_t *addr);

#endif

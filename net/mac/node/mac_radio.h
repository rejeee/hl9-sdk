/*******************************************************************************
 * @file mac_rdio.h
 * @brief Radio API by MAC invoke
 * @version 0.0.1
 ******************************************************************************/
#ifndef MAC_RADIO_H
#define MAC_RADIO_H

/****
Include
****/
#include <stdbool.h>
#include "bsp.h"

/****
Define
****/
#define DEFAULT_RADIO_TIMEOUT_MS    1000U
#define MAC_DATA_MAX_LEN            228
#define FREQ_NEXT_COUNT             8U

/** @brief Device LPWAN mode */
enum {
    NET_MODE_NONE     = 0U, /**< node to node, fix frequency */
    NET_MODE_LOCAL,         /**< node to gateway, auto frequency */
    NET_MODE_NUM,           /**< all mode number */
};

/****
Global Functions
****/

bool MacRadio_Init(void);

/**
 *@brief Wait radio to be idle, if radio is continue mode,
 *        then post a signal to release it.
 *
 *@return true if success else false.
 */
bool MacRadio_AbortRx(void);

/**
 *@return AT_STATUS
 */
uint32_t MacRadio_TxProcess(uint8_t *buf, uint32_t len);
uint32_t MacRadio_RxProcess(uint8_t rxmode);
uint32_t MacRadio_CadProcess(uint8_t rxmode);

#endif

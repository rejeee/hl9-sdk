/******************************************************************************
 * @file mac_api.c
 * @brief  the MAC common API
 * @version 0.0.1
 ******************************************************************************/
#ifndef MAC_API_H
#define MAC_API_H

/****
Include
****/
#include <stdint.h>
#include <stdbool.h>
#include "radio/sx127x/sx127x_common.h"

/****
Define
****/

/****
Glocal variable
****/
struct mac_lorawan_t {
    RadioQoS_t  qos;
    /* device level down stream seqno */
    uint16_t    seqnoUp;
    uint16_t    seqnoDn;

    uint8_t     frame[RADIO_MAX_PAYLOAD];
    uint8_t     dataLen;
    uint8_t     dataIdx;
    bool        ack;
};

extern struct mac_lorawan_t gMacParam;

/****
Global functions
****/

bool Mac_Init(bool rfo);

/* AT query command */
void Mac_queryCSQ(int16_t *rssi, int8_t *snr);

#endif

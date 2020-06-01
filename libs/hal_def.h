/*******************************************************************************
 * @file    hal_def.h
 * @brief   hardware abstract layder type definitions
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef HAL_DEF_H
#define HAL_DEF_H

/****
Include Files
****/
#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/****
Macro Defines
****/

/****
Type Defines
****/

/** @brief the callback for user-specific function. */
typedef void (*func_ptr)(void);
typedef void (* lpwan_func_t)(uint32_t addr, uint16_t seq);

/**
 * @brief UART baudrate type define.
 */
enum {
    UART_BRATE_1200 = 0,
    UART_BRATE_2400,
    UART_BRATE_4800,
    UART_BRATE_9600,
    UART_BRATE_19200,
    UART_BRATE_38400,
    UART_BRATE_57600,
    UART_BRATE_115200,
#ifdef USE_HIGH_BRATE
    UART_BRATE_230400,
    UART_BRATE_460800,
    UART_BRATE_921600,
    UART_BRATE_2000000,
#endif
    UART_BRATE_NUM
};

/**
 * @brief UART Parity.
 */
enum {
    UART_PARI_NONE = 0u,
    UART_PARI_EVEN,
    UART_PARI_ODD
};

/**
 * @brief float union define
 * @union FloatUnion
 */
typedef union {
    float   f;
    uint8_t c[4];
    int32_t i;
} FloatUnion;

/**
 * @brief a gps data struct define
 * @struct GpsDataType
 */
typedef struct gps_data_t {
    FloatUnion latitude;
    FloatUnion longitude;
    int        hdop;
} GpsDataType;

typedef struct {
    uint32_t    time;
    uint32_t    u32data;
    uint32_t    u8data  : 8;
    uint32_t    imme    : 1;    /* immediate TX */
    uint32_t    busy    : 1;    /* 1 busy, 0 free */
    uint32_t    forward : 1;
    uint32_t    len     : 8;    /* MemPool payload length */
} BSP_MP_Param;

typedef struct
{
    uint8_t addr;       /**<    Slave Address */
    uint8_t idx;        /**<    Slave index or Channel  */
    uint8_t regs[4];    /**<    Slave register address */
    uint8_t len;        /**<    the byte width of @regs, max is 4 */
} BSP_Slave_Param;

/*
 * Radio Quality Calculator
 */
typedef struct
{
    int32_t     freqerr;
    int16_t     rssi;       /**<  max physical RSSI range -198..+63 */
    int8_t      snr;        /**<  max physical SNR range -32..+31.75 */
} RadioQoS_t;

struct mac_lorawan_t {
    lpwan_func_t    cb;
    RadioQoS_t      qos;
    uint32_t        freq;
    uint32_t        addr;
    uint32_t        sf      : 4;
    uint32_t        fwd     : 1;        /**> forward directly */
    uint32_t        ack     : 1;
    uint32_t        seqnoUp :16;
    uint8_t         payload[255];   /**<  to be write or read from radio FIFO */
    uint8_t         size;           /**<  total size to be write or read */
    uint8_t         rxLen;          /**<  valid Rx data length */
    uint8_t         rxIdx;          /**<  valid Rx data index */
};

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif


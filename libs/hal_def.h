/*******************************************************************************
 * @file    hal_def.h
 * @brief   hardware abstract layder type definitions
 *
 * @version 1.0
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
    UART_BRATE_380400,
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

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif


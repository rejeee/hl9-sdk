/*******************************************************************************
 * @file crc.c
 * @brief  A CRC API
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef UTILS_CRC_H
#define UTILS_CRC_H

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

uint16_t cal_crc16(const uint8_t *ptr, const uint32_t len);

uint16_t modbus_crc16(const uint8_t *ptr, const uint8_t len);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

/*******************************************************************************
 * @file    util.h
 * @brief   Utils function implementation
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef UTILS_UTIL_H
#define UTILS_UTIL_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal_def.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define IS_DIGIT(x)   ((0x2F < (x)) && ((x) < 0x3A))

/**
 * @brief Set the random seed
 *
 * @param seed  the random seed to be set
 */
void srand_t(unsigned int seed);

/**
 * @brief Computes a random number between 0 and max
 *
 * @param max   range maximum value
 *
 * @return      a random value in range 0..max.
 */
int32_t randr(int32_t max);

/**
 * @brief Read 16-bit quantity from given pointer in little endian byte order.
 */
uint16_t ros_rlsbf2(const uint8_t* buf);

/**
 * @brief Read 32-bit quantity from given pointer in little endian byte order.
 */
uint32_t ros_rlsbf4(const uint8_t* buf);

uint16_t ros_rmsbf2(const uint8_t* buf);

/**
 * @brief Read 32-bit quantity from given pointer in big endian byte order.
 */
uint32_t ros_rmsbf4(const uint8_t* buf);

/**
 * @brief Write 16-bit quntity into buffer in little endian byte order.
 */
void ros_wlsbf2(uint8_t* buf, uint16_t v);

/**
 * @brief Write 32-bit quntity into buffer in little endian byte order.
 */
void ros_wlsbf4(uint8_t* buf, uint32_t v);

void ros_wmsbf2(uint8_t* buf, uint16_t v);

/**
 * @brief Write 32-bit quantity into buffer in big endian byte order.
 */
void ros_wmsbf4(uint8_t* buf, uint32_t v);

char b2hex(uint8_t b);

/**
 * @brief Convert a hex string to a binary data
 *
 * @param str   the pointer of this hex string
 * @param len   the length of this hex string
 *
 * @return      true if convert is successful else false.
 */
bool hex2bin(uint8_t *str, uint32_t len);

/**
 * @brief Invert the binary data byte order
 *
 * @param buf   the pointer of this binary data
 * @param len   the length of this binary data
 *
 */
void bin2invert(uint8_t *buf, uint32_t len);

/**
 * Convert a binary to hex string
 *
 * @param   bin     A pointer to a binary data buffer
 * @param   len     the length of bin
 * @param   str     the hex string of bin data
 */
void bin2str(uint8_t *bin, uint32_t len, char *str);

/**
 * @brief Check whether the binary data is all tag value.
 *
 * @param tag   the value of tag
 * @param buf   the pointer of this binary data
 * @param len   the length of this binary data
 *
 */
bool binIsTag(uint8_t tag, uint8_t *buf, uint32_t len);

/**
 * @brief Calculate voltage level according @klevel use input parameters.
 *
 * @param klevel    the const LEVEL to be divided
 * @param min       the minimal reference voltage, unit mV
 * @param max       the maximal reference voltage, unit mV
 * @param vol       the value of current voltage, unit mV
 *
 * @return a level according this functions.
 */
uint8_t calc_level(const uint8_t klevel, const uint32_t min, const uint32_t max, const uint32_t vol);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

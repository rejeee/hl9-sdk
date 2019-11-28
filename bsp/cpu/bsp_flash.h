/*******************************************************************************
 * @file    bsp_flash.h
 * @brief   the device flash driver
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef BSP_CPU_FLASH_H
#define BSP_CPU_FLASH_H

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>
#include "em_device.h"

#define REG_READ32(address)     ((uint32_t)(*(vu32*)(address)))
#define REG_READ16(address)     ((uint16_t)(*(vu16*)(address)))
#define REG_READ8(address)      ((uint8_t)(*(vu8*)(address)))

/**
 * @brief Flash Initialize
 */
bool BSP_FlashInit(void);

/**
 * @brief Flash Check Initialize tag
 */
bool BSP_CheckFlag(void);

/**
 * @brief Read length data from addr
 *
 * @param addr      The start address of the desired flash memory to be read.
 *                      Must be word-aligned.
 * @param data      The pointer of data to be read
 * @param len       The length of data to be read.
 *
 * @return          true if write success else false.
 */
bool BSP_FlashRead(uint32_t addr, uint32_t *data, uint32_t len);
bool BSP_FlashReadHalf(uint32_t addr, uint16_t *data, uint32_t len);

/**
 * @brief Write length data to addr
 *
 * @param addr      The start address of the desired flash memory to be writed.
 *                      Must be word-aligned.
 * @param data      The pointer of data to be writed
 * @param len       The length of data to be writed.
 *
 * @return          true if write success else false.
 */
bool BSP_FlashWrite(uint32_t addr, uint32_t *data, uint32_t len);

/**
 * @brief Program length halfword data to addr
 *
 * @param addr      The start address of the desired flash memory to be writed.
 *                      Must be word-aligned.
 * @param data      The pointer of halfword data to be program
 * @param len       The length of halfword data to be program.
 *
 * @return          true if write success else false.
 */
bool BSP_FlashHalfWord(uint32_t addr, uint16_t *data, uint32_t len);

/**
 * @brief Erase size data from addr
 *
 * @param addr      The start address of the desired flash memory to be erase.
 *                      Must be word-aligned.
 * @param bytes     The bytes of data to be erase. unit is byte
 *
 * @return          true if erase success else false.
 */
bool BSP_FlashErase(uint32_t addr, uint32_t bytes);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

/*******************************************************************************
 * @file    at.h
 * @brief   The common AT API
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef AT_H
#define AT_H

/****
Include Files
****/
#include "at/at_api.h"
/****
Global Functions
****/

/**
 * @brief Print AT support command list
 */
void AT_Help(void);

/**
 * @brief Parse a length data with AT command refernce manual
 *
 * @param   data        the pointer of data buffer which read from UART
 * @param   len         the length of data buffer
 *
 * @return  a result of @see AT_STATUS
 *
 * @note  data  cannot NULL and must is a valid AT command string,
 *                     detail refer manual.
 *        len   must is valid(min < len < max)
 *        @see at_api.h
 */
uint32_t AT_HandleFrame(uint8_t *data, const uint32_t len);

#endif

/*******************************************************************************
 * @file    app.h
 * @brief   Project application interface
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef APP_H
#define APP_H

/****
Include Files
****/
#include "platform/platform.h"

#if DISABLE_WDOG
#define APP_FeedDog()
#else
#define APP_FeedDog()               BSP_WatchdogFeed()
#endif

/****
Global Functions
****/

/*!
 * @brief the application initialize
 */
void AppInit(void);

/*!
 * @brief  Create the application task
 */
bool AppTaskCreate(void);

/*!
 * @brief  AppTask extends operation use MAIN task
 */
void AppTaskExtends(void);

#endif

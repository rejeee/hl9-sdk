/*******************************************************************************
 * @file    app.c
 * @brief   Project application interface
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/

/****
Include Files
****/
#include "app.h"

/****
Global Functions
****/

/*!
 * @brief  Initialize all applications
 *
 * @return  true if success else false
 */
void AppInit(void)
{
    /* Application module initialize, create and start task */
    if(false == AppTaskCreate()){
        /* NOTE: here can use watchdog reboot */
        NVIC_SystemReset();
        return;
    }

    AppTaskExtends();
}

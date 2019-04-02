/*******************************************************************************
 * @file    app_project.c
 * @brief   Project application interface
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#include "app.h"
#include "app_at.h"
#include "app_mac.h"
#include "at/at_config.h"
#include "radio/sx127x/sx127x_common.h"

#define TASK_PERIOD_MS      100U    /* unit ms */

char *gCodeVers = "1012";

/****
Local Variables
****/

/****
Local Functions
****/

/*!
 * @brief  Initialize all tasks
 *
 * @return  true if success else false
 */
static bool App_Init(void)
{
    bool result = true;

    /* start MAC task */
    APP_FeedDog();
    result = AppMacTask();

    /**
     * we should opearte AT command when other task is OK,
     * so we start AT command task at the end.
     */
    if(result){
        APP_FeedDog();
        result = AppATTask();
    }

    return result;
}

static void AppTaskManager(void)
{
    BSP_OS_MutexLock(&gParam.mutex, OS_ALWAYS_DELAY);
    UserCheckAT();
    BSP_OS_MutexUnLock(&gParam.mutex);
}

/****
Global Functions
****/

/*!
 * @brief  Create the App task
 */
bool AppTaskCreate(void)
{
    bool success = false;

    success = UserDebugInit(false, gDevFlash.config.baudrate, gDevFlash.config.pari);

    printk("LoRa %s SDK, HAL V%u:%u, XTL:%d, Firmware V%s\r\n", MODULE_NAME,
           RADIO_HAL_VERSION, AT_VER, gParam.dev.extl, gCodeVers);

    if(success) {
        success = App_Init();
    }

    return success;
}

void AppTaskExtends(void)
{
    while (1) {
        APP_FeedDog();
        AppTaskManager();
        osDelayMs(TASK_PERIOD_MS);
        if(gDevFlash.config.lcp <= 0){
            LED_OFF(LED_RF_RX);
        }
    }
}

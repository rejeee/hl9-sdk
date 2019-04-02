/*******************************************************************************
 * @file    app_at.c
 * @brief   AT Command processd
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#include "app_at.h"
#include "at/at.h"
#include "at/at_config.h"
#include "mac/node/mac_api.h"
#include "mac/node/mac_radio.h"

/****
Global Variables
****/
static void ATTaskHandler(void const *p_arg);

/* Task variables  */
osThreadDef(ATTaskHandler, osPriorityNormal, 1, 0);
#define APP_AT_NAME   osThread(ATTaskHandler)
osThreadId  sATThreadID = NULL;

/****
Local Functions
****/
static void App_Help(void)
{
    /* Close interrupt ****/
    osSaveCritical();
    /* Enter critical */
    osEnterCritical();
    AT_Help();
    /* Exit critical */
    osExitCritical();
}

static void App_Information(void)
{
    printk("\r\n+ATI:%s,%s\r\n", HAL_VER, gCodeVers);
}

static void App_Recovery(void)
{
    /* restore default configuration */
    DevCfg_Recovery();
    printk("\r\nOK\r\n");
    osDelayMs(5);
    /* Reset system */
    NVIC_SystemReset();
    return;
}

static void App_SoftReset(void)
{
    printk("\r\nOK\r\n");
    osDelayMs(5);
    /* Reset system */
    NVIC_SystemReset();
    return;
}

static void App_Response(uint32_t status)
{
    int16_t    rssi = 0;
    int8_t     snr = 0;
    switch(status){
        case AT_STATUS_OK:
            printk("\r\nOK\r\n");
            break;
        case AT_STATUS_UNKNOWN:
            printk("\r\nER00\r\n");
            break;
        case AT_STATUS_PARAM:
            printk("\r\nER01\r\n");
            break;
        case AT_STATUS_ERR:
            printk("\r\nER02\r\n");
            break;
        case AT_STATUS_BUSY:
            printk("\r\nER03\r\n");
            break;
        case AT_STATUS_LEN_ERR:
            printk("\r\nER04\r\n");
            break;
        case AT_STATUS_FLASH_ERR:
            printk("\r\nER05\r\n");
            break;
        case AT_STATUS_MEM_ERR:
            printk("\r\nER06\r\n");
            break;
        case AT_STATUS_TIMEOUT:
            printk("\r\nER07\r\n");
            break;
        case AT_STATUS_UNUSED:
            printk("\r\nER08\r\n");
            break;
        case AT_STATUS_SLEEP:
            if(gDevFlash.config.baudrate <= UART_BRATE_9600){
                printk("\r\nER08\r\n");
            } else {
                UserDebugWrite((uint8_t *)"\r\nOK\r\n", 6);
                osDelayMs(5); /* delay for pinkt OK */
                PlatformSleep(gDevRam.sleep_secs);
            }
            break;
        case AT_STATUS_H:
            App_Help();
            break;
        case AT_STATUS_I:
            App_Information();
            break;
        case AT_STATUS_Z:
            App_Recovery();
            break;
        case AT_STATUS_R:
            App_SoftReset();
            break;
        case AT_STATUS_T:
            UserEnterAT(false);
            printk("\r\nOK\r\n");
            break;
        case AT_STATUS_CFG:
            DevCfg_Display();
            break;
        case AT_STATUS_CSQ:
            Mac_queryCSQ(&rssi, &snr);
            if(snr || rssi){
                printk("\r\n+CSQ:%d,%d\r\n", snr, rssi);
            } else {
                printk("\r\nER09\r\n");
            }
            break;
        case AT_STATUS_UART:
            UserDebugWrite((uint8_t *)"\r\nOK\r\n", 6);
            UserDebugInit(true, gDevFlash.config.baudrate, gDevFlash.config.pari);
            DevDebug_FlushAll(5);
            break;
        case AT_STATUS_SET_RF:
            MacRadio_UpdateRx(true);
            printk("\r\nOK\r\n");
            break;
        case AT_STATUS_RX_MODE:
            MacRadio_AbortRx();
            printk("\r\nOK\r\n");
            break;
        case AT_STATUS_NONE:
        default:
            break;
    }

    return;
}

/*!
 * @brief  AT task handler
 */
static void ATTaskHandler(void const *p_arg)
{
    int rev_len    = 0;
    uint8_t recv_buf[MEM_POOL_BLOCK_SIZE+1] = { 0 };

    while (1) {
        /* memory get success */
        rev_len = DevDebug_Read(recv_buf, MEM_POOL_BLOCK_SIZE, OS_ALWAYS_DELAY);
        if(gParam.at_mode){
            /* execute AT command */
            App_Response(AT_HandleFrame(recv_buf, rev_len));
        } else {
            if ((NULL != recv_buf) && (3 == rev_len) && (0 == strncmp("+++", (char *)recv_buf, 3))) {
                UserEnterAT(true);
                printk("\r\nOK\r\n");
            } else {
                MacRadio_TxProcess(recv_buf, rev_len);
            }
        }
        gEnableRadioRx = true;
    }
}

/****
Global Functions
****/
void AT_Printf(const char *str, size_t len)
{
    UserDebugWrite((uint8_t *)str, len);
    return;
}

/* return refer @AT_STATUS */
uint32_t AT_TxProcess(bool forward, uint8_t *buf, uint32_t len)
{
    if(forward){
        return MacRadio_TxProcess(buf, len);
    } else {
        /* TODO: set customer parameters */
        return AT_STATUS_UNUSED;
    }
}

/*!
 * @brief  Create the AT task
 */
bool AppATTask(void)
{
    bool result = false;

    gAtEnableType = AT_EN_NODE;

    result = BSP_OS_TaskCreate(&sATThreadID, APP_AT_NAME, NULL);

    if (true != result) {
        LOG_ERR(("AT Command task start error.\r\n"));
    }

    return result;
}

/*******************************************************************************
 * @file    app_at.c
 * @brief   AT Command task
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#include "app_at.h"
#include "at/at.h"
#include "at/at_config.h"
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
static void AppAtResp(const char *str)
{
    UserDebugWrite((uint8_t *)str, strlen(str));
}

static void App_Help(void)
{
    osSaveCritical();
    osEnterCritical();
    AT_Help();
    osExitCritical();
}

static void App_Information(void)
{
    printk("\r\n+ATI:%s,%s\r\n", HAL_VER, gCodeVers);
}

static void App_Recovery(void)
{
    if(DevCfg_Recovery(1)){
        AppAtResp("\r\nOK\r\n");
        NVIC_SystemReset();
    } else {
        AppAtResp("\r\nER05\r\n");
    }

    return;
}

static void App_SoftReset(void)
{
    AppAtResp("\r\nOK\r\n");
    NVIC_SystemReset();
    return;
}

static void App_Response(uint32_t status)
{
    int16_t    rssi = 0;
    int8_t     snr = 0;
    switch(status){
        case AT_STATUS_OK:
            AppAtResp("\r\nOK\r\n");
            break;
        case AT_STATUS_UNKNOWN:
            AppAtResp("\r\nER00\r\n");
            break;
        case AT_STATUS_PARAM:
            AppAtResp("\r\nER01\r\n");
            break;
        case AT_STATUS_ERR:
            AppAtResp("\r\nER02\r\n");
            break;
        case AT_STATUS_BUSY:
            AppAtResp("\r\nER03\r\n");
            break;
        case AT_STATUS_LEN_ERR:
            AppAtResp("\r\nER04\r\n");
            break;
        case AT_STATUS_FLASH_ERR:
            AppAtResp("\r\nER05\r\n");
            break;
        case AT_STATUS_MEM_ERR:
            AppAtResp("\r\nER06\r\n");
            break;
        case AT_STATUS_TIMEOUT:
            AppAtResp("\r\nER07\r\n");
            break;
        case AT_STATUS_UNUSED:
            AppAtResp("\r\nER08\r\n");
            break;
        case AT_STATUS_SLEEP:
            if(gDevFlash.config.prop.bdrate <= UART_BRATE_9600){
                AppAtResp("\r\nER08\r\n");
            } else {
                AppAtResp("\r\nOK\r\n");
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
            AppAtResp("\r\nOK\r\n");
            break;
        case AT_STATUS_CFG:
            DevCfg_Display(BSP_LPUART0);
            break;
        case AT_STATUS_CSQ:
            AppMacQueryCSQ(&rssi, &snr);
            if(snr || rssi){
                printk("\r\n+CSQ:%d,%d\r\n", snr, rssi);
            } else {
                AppAtResp("\r\nER09\r\n");
            }
            break;
        case AT_STATUS_UART:
            AppAtResp("\r\nOK\r\n");
            UserDebugInit(true, gDevFlash.config.prop.bdrate, gDevFlash.config.prop.pari);
            DevUART_FlushAll(&gDebugUart, 5);
            break;
        case AT_STATUS_SET_RF:
            AppMacUpdateRx(true);
            AppAtResp("\r\nOK\r\n");
            break;
        case AT_STATUS_RX_MODE:
            AppMacUpdateRx(true);
            AppAtResp("\r\nOK\r\n");
            break;
        case AT_STATUS_NONE:
        default:
            break;
    }

    return;
}

/**
 * @brief  AT task handler
 */
static void ATTaskHandler(void const *p_arg)
{
    int rev_len    = 0;
    uint8_t recv_buf[MEM_POOL_BLOCK_SIZE+1] = { 0 };

    while (1) {
        /* memory get success */
        rev_len = DevUART_Read(&gDebugUart, recv_buf, MEM_POOL_BLOCK_SIZE, OS_ALWAYS_DELAY);
        if(gParam.mode){
            /* execute AT command */
            App_Response(AT_HandleFrame(recv_buf, rev_len));
        } else {
            if ((3 == rev_len) && (0 == strncmp("+++", (char *)recv_buf, 3))) {
                UserEnterAT(true);
                printk("\r\nOK\r\n");
            } else {
                AT_TxFreq(0, recv_buf, rev_len);
            }
        }
        gEnableRadioRx = true;
    }
}

/****
Global Functions
****/
void AT_Printf(const char *str)
{
    UserDebugWrite((uint8_t *)str, strlen(str));
    return;
}

void AT_LOG(const uint8_t *ptr, size_t len)
{
    UserDebugWrite(ptr, len);
    return;
}

/* return refer @AT_STATUS */
uint32_t AT_TxProcess(uint8_t opts, uint8_t *buf, uint32_t len)
{
    uint32_t status = AT_STATUS_OK;

    switch(opts){
    case 1:
        if(!DevCfg_UserUpdate(buf, len)){
            status = AT_STATUS_FLASH_ERR;
        }
        break;
    case 2:
        /* TODO: set customer parameters with AT+CMD =<x> */
        status = AT_STATUS_UNUSED;
        break;
    case 0:
    default:
        status = AT_TxFreq(0, buf, len);
        break;
    }

    return status;
}

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

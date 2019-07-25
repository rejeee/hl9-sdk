/*******************************************************************************
 * @file    app_mac.c
 * @brief   the MAC task
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#include "app_mac.h"
#include "at/at_config.h"
#include "mac/node/mac_radio.h"
#include "mac/node/mac_api.h"

/****
Global Variables
****/

/****
Local Variables
****/
static void MacTaskHandler(void const *p_arg);

/* Task variables  */
osThreadDef(MacTaskHandler, osPriorityNormal, 1, 0);
#define APP_MAC_NAME   osThread(MacTaskHandler)

/****
Local Functions
****/

/* print recv data */
static void RadioPrintRecv(bool format)
{
    uint8_t i = 0;

    if(gMacParam.ack){
        gMacParam.ack = false;
        printk("\r\nOK\r\n");
    } else if(gMacParam.dataLen > 0){
        if(format){
            printk("\r\n+DATA:%d,%u,%d,%d,%u\r\n\r\n",
                   gMacParam.qos.freqerr, gDevFlash.config.rxfreq,
                   gMacParam.qos.snr, gMacParam.qos.rssi,
                   gMacParam.dataLen);
            for(i = gMacParam.dataIdx; i < gMacParam.dataLen + gMacParam.dataIdx; i++){
                printk("%02X", gMacParam.frame[i]);
            }
            printk("\r\n");
        } else {
            UserDebugWrite(gMacParam.frame + gMacParam.dataIdx, gMacParam.dataLen);
        }
    }
}

/*!
 * @brief  MAC task handler
 */
static void MacTaskHandler(void const *p_arg)
{
    uint32_t status = AT_STATUS_NONE;

    while (1) {
        if(gDevFlash.config.lcp > 0 && gEnableRadioRx && gDevFlash.config.prop.bdrate <= UART_BRATE_9600){
            if(MacRadio_CanRx()){
                /* if you need milliseconds level sleep */
                /* PlatformSleepMs(1000 * gDevFlash.config.lcp); */
                PlatformSleep(gDevFlash.config.lcp);
            }
        }

        if(gEnableRadioRx){
            if(gParam.mode){
                if(RX_MODE_NONE != gDevRam.rx_mode){
                    if(gDevFlash.config.lcp > 0){
                        status = MacRadio_CadProcess(gDevRam.rx_mode);
                    } else {
                        status = MacRadio_RxProcess(gDevRam.rx_mode);
                    }
                }
            } else {
                if(gDevFlash.config.lcp > 0){
                    status = MacRadio_CadProcess(RX_MODE_NONE);
                } else {
                    status = MacRadio_RxProcess(RX_MODE_NONE);
                }
            }

            if(status == AT_STATUS_OK){
                if(gDevFlash.config.lcp <= 0){
                    LED_ON(LED_RF_RX);
                }
                RadioPrintRecv((RX_MODE_FACTORY == gDevRam.rx_mode));
            } else if(status == AT_STATUS_RX_ERR) {
                if(RX_MODE_FACTORY == gDevRam.rx_mode){
                    printk("CRC ERR,SNR:%d, RSSI:%ddBm,Calc:%d\r\n",
                           gMacParam.qos.snr, gMacParam.qos.rssi, gMacParam.qos.freqerr);
                }
            }
            status = AT_STATUS_NONE;
        } else {
            BSP_OS_SemReset(&gDbgSem);
            if(gDevFlash.config.lcp > 0){
                if(!BSP_OS_SemWait(&gDbgSem, gDevFlash.config.lcp*1000)){
                    gEnableRadioRx = true;
                }
            }
        }
        osDelayMs(1);
    }
}

/****
Global Functions
****/

/*!
 * @brief  Create the MAC task
 */
bool AppMacTask(void)
{
    bool result = Mac_Init(gDevFlash.config.dtype & DTYPE_BITS_RFO);

    if(result){
        result = BSP_OS_TaskCreate(&gParam.macid, APP_MAC_NAME, NULL);
        if (true != result) {
            LOG_ERR(("NetTask start error.\r\n"));
        }
    } else {
        LOG_ERR(("Mac init error.\r\n"));
    }

    return result;
}

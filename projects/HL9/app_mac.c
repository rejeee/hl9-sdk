/*******************************************************************************
 * @file    app_mac.c
 * @brief   Radio MAC task
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#include "app_mac.h"
#include "at/at_config.h"
#include "mac/node/mac_radio.h"

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

static struct mac_lorawan_t sMacParam = {0};

/****
Local Functions
****/

/* print recv data */
static void RadioPrintRecv(bool format)
{
    uint8_t i = 0;

    osSaveCritical();
    osEnterCritical();

    if(sMacParam.ack){
        sMacParam.ack = false;
        printk("\r\nOK\r\n");
    } else if(sMacParam.rxLen > 0){
        if(format){
            printk("\r\n+DATA:%d,%u,%d,%d,%u\r\n\r\n",
                   sMacParam.qos.freqerr, gDevFlash.config.rxfreq,
                   sMacParam.qos.snr, sMacParam.qos.rssi,
                   sMacParam.rxLen);
            for(i = sMacParam.rxIdx; i < sMacParam.rxLen + sMacParam.rxIdx; i++){
                printk("%02X", sMacParam.payload[i]);
            }
            printk("\r\n");
        } else {
            if((gDevFlash.config.dtype >> TYPE_BITS_RAW)&0x01){
                UserDebugWrite(sMacParam.payload, sMacParam.size);
            } else {
                UserDebugWrite(sMacParam.payload + sMacParam.rxIdx, sMacParam.rxLen);
            }
        }
    }
    osExitCritical();
}

/**
 * @brief  MAC task handler
 */
static void MacTaskHandler(void const *p_arg)
{
    uint32_t status = AT_STATUS_NONE;
    uint8_t spiIdx = BSP_SPI0;

    while (1) {
        if(gDevFlash.config.lcp > 0 && gEnableRadioRx && gDevFlash.config.prop.bdrate <= UART_BRATE_9600){
            if(RadioGetCanRx(spiIdx)){
                /* if you need milliseconds level sleep */
                /* PlatformSleepMs(1000 * gDevFlash.config.lcp); */
                PlatformSleep(gDevFlash.config.lcp);
            }
        }

        if(gEnableRadioRx){
            if(gParam.mode){
                if(RX_MODE_NONE != gDevRam.rx_mode){
                    if(gDevFlash.config.lcp > 0){
                        status = MacRadio_CadProcess(spiIdx, true);
                    } else {
                        status = MacRadio_RxProcess(spiIdx, false);
                    }
                }
            } else {
                if(gDevFlash.config.lcp > 0){
                    status = MacRadio_CadProcess(spiIdx, true);
                } else {
                    status = MacRadio_RxProcess(spiIdx, false);
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
                           sMacParam.qos.snr, sMacParam.qos.rssi, sMacParam.qos.freqerr);
                }
            }
            status = AT_STATUS_NONE;
        }
        osDelayMs(1);
    }
}

/****
Global Functions
****/
bool AppMacTask(void)
{
    bool success = true;

    memset(&sMacParam, 0 ,sizeof(struct mac_lorawan_t));

    if (false == MacRadio_Init()) {
        LOG_ERR(("Radio Mac Init error.\r\n"));
        return false;
    }

    success = BSP_OS_TaskCreate(&gParam.appid, APP_MAC_NAME, NULL);
    if(false == success){
        LOG_ERR(("Mac task start error.\r\n"));
    }

    return success;
}

uint32_t AT_TxFreq(uint32_t freq, uint8_t *buf, uint32_t len)
{
    uint32_t status = 0;

    if(gPaEnable){
        if(gDevFlash.config.txpow > 0){
            gDevFlash.config.txpow = 0;
        }
    }

    sMacParam.freq = freq;
    status = MacRadio_TxProcess(BSP_SPI0, buf, len, &sMacParam);

    return status;
}

RadioIrqType_t RadioRxFinish(uint8_t spiIdx)
{
    struct sx12xx_rx_t rxObj;
    RadioIrqType_t type_flag = RADIO_IRQ_UNKOWN;
    {
        rxObj.modem = gDevFlash.config.rps.modem;
        rxObj.bandwidth = gDevFlash.config.rps.bw;
        rxObj.opmode = OP_MODE_RX;
        rxObj.freq = gDevFlash.config.rxfreq;
        rxObj.crc = gDevFlash.config.rps.crc;
    }

    type_flag =  RadioDecode(spiIdx, &rxObj, &sMacParam);

    if(RADIO_IRQ_LORA_RX != type_flag && RADIO_IRQ_FSK_RX != type_flag){
        /* clear buffer */
        memset(sMacParam.payload, 0, sizeof(sMacParam.payload));
        sMacParam.size = 0;
    }

    return type_flag;
}

void RadioCustomization(uint8_t spiIdx, bool tx, RadioSettings_t *ptr)
{
    /**
     * This is a callback function before sending or receiving.
     *
     * You can modify the RF parameters dynamic adjustment of transceiver.
     *
     */

    /* @todo */
    /*
    if(tx){
        ptr->freq = USER_CFG_TFREQ;
    } else {
        ptr->freq = USER_CFG_RFREQ;
    }
    */
}

bool AppMacUpdateRx(bool update)
{
    bool success = MacRadio_AbortRx(BSP_SPI0);

    return success;
}

void AppMacQueryCSQ(int16_t *rssi, int8_t *snr)
{
    *rssi = sMacParam.qos.rssi;
    *snr = sMacParam.qos.snr;
    return;
}


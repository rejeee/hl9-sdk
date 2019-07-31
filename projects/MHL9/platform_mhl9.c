/*******************************************************************************
 * @file    platform_mhl9.c
 * @brief   The HL9 platform interface implementation
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#include "platform/platform.h"
#include <stdarg.h>
#include "at/at_config.h"
#include "radio/sx127x/sx127x_common.h"
#include "mac/node/mac_radio.h"

osSemaphoreDef(debugSemaphore);
#define DEBUG_SEM_NAME      osSemaphore(debugSemaphore)

/****
Local Variables
****/
static uint8_t sDebugBuffer[DBG_UART_SIZE + 1] = {0};
static Ringfifo sDebugFIFO = {0};
struct sp_uart_t gDebugUart = {
    .rx_sem = {0},
    .rx_fifo = &sDebugFIFO,
    .timeout = DBG_UART_TIMEOUT,
    .num = DBG_UART_NUM
};

static void DevUpdateAT(void)
{
    if(gParam.aswitch){
        if(0 == GPIO_READ(AT_GPIO, AT_PIN)) {
            gParam.mode = 0;
        } else {
            gParam.mode = 1;
        }
    }
}

/* UART user callback */
static void DebugCallback(uint32_t userData)
{
    int result = 0;
    BSP_LPowerStop();
    result = DevUART_IRQHandler(&gDebugUart, userData);
    if(0 == result || 1 == result){
        gEnableRadioRx = false;
    }
}

/****
Global Functions
****/

/**
 * @brief IO interrupt service rutine
 */
void Gpio_IRQHandler(uint8_t u8Param)
{
    DevRadioIRQHandler(u8Param);

    /* User Key IRQ */
    if(1 == u8Param) {
        if(TRUE == Gpio_GetIrqStatus(UKEY_GPIO, UKEY_PIN)){
            Gpio_ClearIrq(UKEY_GPIO, UKEY_PIN);
            BSP_LPowerStop();
        }
    }
}

/**
 * @brief radio hal API implemetation
 *
 * function declarations refer radio common definitions
 */
void RadioDelay(uint32_t ms)
{
    osDelayMs(ms);
}

/* Ant control is empty implemetation to be compatible different designs */
void RadioAntLowPower(uint8_t param){ }
void RadioAntSwitch(uint8_t param) { }

/**
 * @brief user project special implemetation
 * function declarations refer platform common definitions
 */
void UserExternalGPIO(bool enable)
{
    stc_gpio_config_t gpioCfg;
    DDL_ZERO_STRUCT(gpioCfg);

    gpioCfg.enDir = GpioDirIn;
    gpioCfg.enPuPd = GpioPd;
    gpioCfg.enOD = GpioOdDisable;
    gpioCfg.enDrv = GpioDrvL;
    if(enable) {
        Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
        Gpio_Init(AT_GPIO, AT_PIN, &gpioCfg);
        Gpio_SetAfMode(AT_GPIO, AT_PIN,  GpioAf0);
        Gpio_Init(UKEY_GPIO, UKEY_PIN, &gpioCfg);
        Gpio_SetAfMode(UKEY_GPIO, UKEY_PIN,  GpioAf0);

        /* IRQ on rising edge trigger */
        EnableNvic(UKEY_PORT_IRQ, IrqLevel3, TRUE);
        Gpio_EnableIrq(UKEY_GPIO, UKEY_PIN, GpioIrqRising);
        DevUpdateAT();

        /* unused GPIO diabled */
        Gpio_Init(GpioPortA, GpioPin11, &gpioCfg);
        Gpio_Init(GpioPortA, GpioPin12, &gpioCfg);
        Gpio_SetAfMode(GpioPortA, GpioPin11,  GpioAf0);
        Gpio_SetAfMode(GpioPortA, GpioPin12,  GpioAf0);

        Gpio_Init(GpioPortB, GpioPin3, &gpioCfg);
        Gpio_Init(GpioPortB, GpioPin4, &gpioCfg);
        Gpio_Init(GpioPortB, GpioPin6, &gpioCfg);
        Gpio_SetAfMode(GpioPortB, GpioPin3,  GpioAf0);
        Gpio_SetAfMode(GpioPortB, GpioPin4,  GpioAf0);
        Gpio_SetAfMode(GpioPortB, GpioPin6,  GpioAf0);
    } else {
        /** @todo: */
    }
}

bool UserDebugInit(bool reinit, uint32_t baudrateType, uint8_t pariType)
{
    bool success = false;

    BSP_UART_TypeDef uart = {
        .cb = DebugCallback,
        .gpio = DBG_GPIO,
        .tx_pin = DBG_TX_PIN,
        .rx_pin = DBG_RX_PIN,
        .af = DBG_AF,
        .pd = GpioPu,
        .num = DBG_UART_NUM,
        .bdtype = baudrateType,
        .pri = pariType
    };

    /* Note: you can set timeout you need */
    gDebugUart.timeout = BSP_UartSplitTime(baudrateType);
    gDebugUart.num = uart.num;

    if(false == reinit){
        /* first init */
        success = BSP_OS_SemCreate(&gDebugUart.rx_sem, 0, DEBUG_SEM_NAME);
        if (false == success) {
            /* NOTE: Must make device reset */
            return false;
        }
        success = DevUART_Init(&uart, &gDebugUart, sDebugBuffer, sizeof(sDebugBuffer));
    } else {
        success = DevUART_ReInit(&uart);
    }

    return success;
}

void UserDebugWrite(const uint8_t *data, uint32_t len)
{
    BSP_UartSend(DBG_UART_NUM, data, len);
}

void UserEnterAT(bool enable)
{
    BSP_OS_MutexLock(&gParam.mutex, OS_ALWAYS_DELAY);
    if(enable){
        gParam.mode = 1U;
        gParam.aswitch = 0U;
        AT_HIGH();
    } else {
        gParam.mode = 0U;
        gParam.aswitch = 1;
        AT_LOW();
    }
    BSP_OS_MutexUnLock(&gParam.mutex);
    /* exit transparent */
    if(enable){
        MacRadio_UpdateRx(true);
    }
}

void UserCheckAT(void)
{
    if(gParam.aswitch){
        if(0 == GPIO_READ(AT_GPIO, AT_PIN)) {
            gParam.mode = 0;
        } else {
            gParam.mode = 1;
        }

        if(1 == gParam.mode){
            MacRadio_UpdateRx(true);
        }
    }

    return;
}

/**
 *  FIXME:
 *  User should redefine config display function to reduce code size
 *  This function is called only by AT task.
 */
void DevCfg_Display(void)
{
    rps_t rps = gDevFlash.config.rps;
    uint32_t freq  = gDevFlash.config.txfreq;
    int8_t txpow = gDevFlash.config.txpow;
    char* bwstr = NULL;
    char* ldrstr = NULL;
    char* parstr = NULL;
    bool notAes = binIsTag(0x00, gDevFlash.config.appKey, 16);

    switch(rps.bw){
    case RF_BANDWIDTH_7D8:
        bwstr = "7.8kHz";
        break;
    case RF_BANDWIDTH_10D4:
        bwstr = "10.4kHz";
        break;
    case RF_BANDWIDTH_15D6:
        bwstr = "15.6kHz";
        break;
    case RF_BANDWIDTH_20D8:
        bwstr = "20.8kHz";
        break;
    case RF_BANDWIDTH_31D2:
        bwstr = "31.2kHz";
        break;
    case RF_BANDWIDTH_41D7:
        bwstr = "41.7kHz";
        break;
    case RF_BANDWIDTH_62D5:
        bwstr = "62.5kHz";
        break;
    case RF_BANDWIDTH_125:
        bwstr = "125kHz";
        break;
    case RF_BANDWIDTH_250:
        bwstr = "250kHz";
        break;
    case RF_BANDWIDTH_500:
        bwstr = "500kHz";
        break;
    default:
        bwstr = "UNKNOWN";
        break;
    }

    switch(gDevFlash.config.rps.lowRate){
    case LOWRATE_OP_AUTO:
        ldrstr ="AUTO";
        break;
    case LOWRATE_OP_ON:
        ldrstr ="ON";
        break;
    case LOWRATE_OP_OFF:
        ldrstr ="OFF";
        break;
    default:
        ldrstr ="UNKNOWN";
        break;
    }

    switch(gDevFlash.config.prop.pari){
    case UART_PARI_EVEN:
        parstr = "Even";
        break;
    case UART_PARI_ODD:
        parstr = "Odd";
        break;
    default:
        parstr = "None";
        break;
    }

    /* Use RFO, limit power +14dBm */
    if(gDevFlash.config.dtype & DTYPE_BITS_RFO){
        if(txpow > 14){
            txpow = 14;
        }
    } else {
        if(txpow < 2){
            txpow = 2;
        }
    }
    osSaveCritical();
    osEnterCritical();
    printk("NET:\t%s\r\nTFREQ:\t%0.1fMHz\r\nRFREQ:\t%0.1fMHz\r\n",
           gDevFlash.config.prop.netmode ? "Node to Gateway":"Node to Node",
           (float)(freq/1e6),(float)(gDevFlash.config.rxfreq/1e6));
    printk("POW:\t%udBm\r\nBW:\t%s\r\n"
           "TSF:\t%u\r\nRSF:\t%u\r\nCR:\t4/%u\r\nMODE:\t%s\r\nSYNC:\t0x%X\r\n",
           txpow,bwstr,
           gDevFlash.config.txsf,gDevFlash.config.rxsf,rps.cr + 4,
           gDevFlash.config.rps.modem?"LORA":"FSK",
           gDevFlash.config.syncword);
    printk("PREM:\t%u,%u\r\nFIX:\t%u,%u\r\nCRC:\t%s\r\nTIQ:\t%s\r\nRIQ:\t%s\r\n",
           gDevFlash.config.tprem,gDevFlash.config.rprem,
           gDevFlash.config.tfix,gDevFlash.config.rfix,
           rps.crc?"ON":"OFF",
           gDevFlash.config.rps.tiq?"ON":"OFF",
           gDevFlash.config.rps.riq?"ON":"OFF");
    printk("SEQ:\t%s\r\nIP:\t%s\r\nAES:\t%s\r\nACK:\t%s\r\n"
           "LDR:\t%s\r\nPAR:\t%s\r\n"
           "LCP:\t%u\r\nLFT:\t%u\r\nFNB:\t0x%02X\r\nTYPE:\t0x%02X\r\n",
           gDevFlash.config.prop.seqMode?"ON":"OFF",
           gDevFlash.config.prop.ipMode?"ON":"OFF",
           notAes?"OFF":"ON",
           gDevFlash.config.prop.ack?"ON":"OFF",ldrstr,parstr,
           gDevFlash.config.lcp, gDevFlash.config.lftime,
           gDevFlash.config.fnb,
           gDevFlash.config.dtype);

    osExitCritical();
    return;
}

void DevCfg_UserDefault(void)
{
    /**
     * Indicate if or not use RFO
     *      false(0)  Use PA BOOST
     *      true(1)   Use RFO
     */
    gDevFlash.config.dtype = 0;
}

void Dev_GetVol(void)
{
    /**
     * NOTE:  you can wait a moment for measure VCC after execute TX, but you
     *        should not be too long and must be less than TX Air Time.
     *
     * for example: Delay for a short time for radio TX work,
     *              you can measure voltage at maximum power consumption
     *        osDelayMs(5);
     */

    /* voltage value */
    BSP_ADC_Enable();
    gParam.dev.vol = (3 * BSP_ADC_Sample(AdcAVccDiV3Input));
    BSP_ADC_Disable();
}

/**
 *  NOTE:
 *  User should redefine print function to reduce code size
 *  by disable IAR print Automatic choice of formatter.
 */
int printk(const char *fmt_s, ...)
{
    static char outbuf[128] = {0};

    va_list ap;
    int result;
    uint32_t len = sizeof(outbuf);

    va_start(ap, fmt_s);
    result = vsnprintf(outbuf, len, fmt_s, ap);
    va_end(ap);

    if(result > 0){
        BSP_UartSend(DBG_UART_NUM, (uint8_t *)outbuf, result);
    }

    return result;
}

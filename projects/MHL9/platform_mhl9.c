/*******************************************************************************
 * @file    platform_mhl9.c
 * @brief   The HL9 platform interface implementation
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#include "platform/platform.h"
#include <stdarg.h>
#include "at/at_config.h"
#include "radio/sx127x/sx127x_common.h"
#include "mac/node/mac_radio.h"

/****
Local Variables
****/
static uint8_t sDebugBuffer[DBG_UART_SIZE] = {0};

static void DevUpdateAT(void)
{
    if(gParam.at_switch){
        if(0 == GPIO_READ(AT_GPIO, AT_PIN)) {
            gParam.at_mode = 0;
        } else {
            gParam.at_mode = 1;
        }
    }
}

/* UART user callback */
static void DebugCallback(uint32_t userData)
{
    gEnableRadioRx = false;
    BSP_LPowerStop();
    DevDebug_IRQHandler(userData);
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
        .tx_port = DBG_TX_GPIO,
        .tx_pin = DBG_TX_PIN,
        .rx_port = DBG_RX_GPIO,
        .rx_pin = DBG_RX_PIN,
        .af = DBG_AF,
        .num = DBG_UART_NUM,
        .bdtype = baudrateType,
        .pri = pariType
    };

    if(false == reinit){
        /* first init */
        success = DevDebug_Init(&uart, sDebugBuffer, sizeof(sDebugBuffer));
    } else {
        success = DevDebug_ReInit(&uart);
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
        gParam.at_mode = 1U;
        gParam.at_switch = 0U;
        AT_HIGH();
    } else {
        gParam.at_mode = 0U;
        gParam.at_switch = 1;
        AT_LOW();
    }
    BSP_OS_MutexUnLock(&gParam.mutex);
    /* exit transparent */
    if(enable){
        MacRadio_AbortRx();
    }
}

void UserCheckAT(void)
{
    if(gParam.at_switch){
        if(0 == GPIO_READ(AT_GPIO, AT_PIN)) {
            gParam.at_mode = 0;
        } else {
            gParam.at_mode = 1;
        }

        if(1 == gParam.at_mode){
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

    switch(gDevFlash.config.lowRate){
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

    switch(gDevFlash.config.pari){
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

    printk("NET:\t%s\r\nTFREQ:\t%0.1fMHz\r\nRFREQ:\t%0.1fMHz\r\n",
           gDevFlash.config.netmode ? "Node to Gateway":"Node to Node",
           (float)(freq/1e6),(float)(gDevFlash.config.rxfreq/1e6));
    printk("POW:\t%udBm\r\nBW:\t%s\r\n"
           "TSF:\t%u\r\nRSF:\t%u\r\nCR:\t4/%u\r\nMODE:\t%s\r\nSYNC:\t0x%X\r\n",
           txpow,bwstr,
           gDevFlash.config.txsf,gDevFlash.config.rxsf,rps.cr + 4,
           gDevFlash.config.modem?"LORA":"FSK",
           gDevFlash.config.syncword);
    printk("PREM:\t%u,%u\r\nCRC:\t%s\r\nTIQ:\t%s\r\nRIQ:\t%s\r\n",
           gDevFlash.config.tprem,gDevFlash.config.rprem,
           rps.crc?"ON":"OFF",
           gDevFlash.config.tiq?"ON":"OFF",
           gDevFlash.config.riq?"ON":"OFF");
    printk("SEQ:\t%s\r\nIP:\t%s\r\nAES:\t%s\r\nACK:\t%s\r\n"
           "LDR:\t%s\r\nPAR:\t%s\r\n"
           "LCP:\t%u\r\nLFT:\t%u\r\n",
           gDevFlash.config.seqMode?"ON":"OFF",
           gDevFlash.config.ipMode?"ON":"OFF",
           notAes?"OFF":"ON",
           gDevFlash.config.ack?"ON":"OFF",ldrstr,parstr,
           gDevFlash.config.lcp, gDevFlash.config.lftime);
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

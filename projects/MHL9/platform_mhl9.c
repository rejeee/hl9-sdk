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
#include "at/at_config.h"
#include "radio/sx127x/sx127x_common.h"
#include "mac/node/mac_radio.h"

#define APP_DEV_VER        1

/****
Global Variables
****/
osSemaphoreDef(debugSemaphore);
#define DEBUG_SEM_NAME      osSemaphore(debugSemaphore)

DeviceFlash_t  gDevFlash;
struct g_at_param_t gDevRam = {
    .sleep_secs = 0,
    .rx_mode = RX_MODE_NONE
};

struct global_param_t gParam = {
    .dev        = {0},
    .mainid     = NULL,
    .appid      = NULL,
    .mutex      = NULL,
    .dtime      = 0,
    .rst        = {0},
    .mode       = 0,
    .aswitch    = 1
};

/****
Local Variables
****/
static uint8_t sDebugBuffer[DBG_UART_SIZE + 1] = {0};
static Ringfifo sDebugFIFO = {0};
struct sp_uart_t gDebugUart = {
    .rx_sem = {0},
    .rx_fifo = &sDebugFIFO,
    .timeout = DBG_UART_TIMEOUT,
    .idx = DBG_UART_IDX
};

static BSP_ADC_TypeDef sADCConfig;

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

static void UserInitGPIO(void)
{
    stc_gpio_config_t gpioCfg;
    DDL_ZERO_STRUCT(gpioCfg);

    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

    gpioCfg.enDir = GpioDirIn;
    gpioCfg.enPuPd = GpioPd;
    Gpio_Init(AT_GPIO, AT_PIN, &gpioCfg);
    Gpio_SetAfMode(AT_GPIO, AT_PIN, GpioAf0);

    Gpio_Init(UKEY_GPIO, UKEY_PIN, &gpioCfg);
    Gpio_SetAfMode(UKEY_GPIO, UKEY_PIN, GpioAf0);

    /* IRQ on rising edge trigger */
    EnableNvic(UKEY_PORT_IRQ, IrqLevel3, TRUE);
    Gpio_EnableIrq(UKEY_GPIO, UKEY_PIN, GpioIrqRising);
    DevUpdateAT();

    /* unused GPIO diabled */
    Gpio_Init(GpioPortA, GpioPin11, &gpioCfg);

    gpioCfg.enDir = GpioDirIn;
    gpioCfg.enPuPd = GpioPu;
    Gpio_Init(GpioPortB, GpioPin3, &gpioCfg);
    Gpio_Init(GpioPortB, GpioPin4, &gpioCfg);
    Gpio_Init(GpioPortB, GpioPin6, &gpioCfg);
}

/****
Global Functions
****/

/**
 * @brief IO interrupt service rutine
 */
void Gpio_IRQHandler(uint8_t u8Param)
{
    if(0 == u8Param) {
        DevRadioIRQHandler(u8Param);
    }

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
void RadioAntLowPower(uint8_t spiIdx, uint8_t status){ }
void RadioAntSwitch(uint8_t spiIdx, uint8_t rxTx) { }

/**
 * @brief user project special implementation
 * function declarations refer platform common definitions
 */
void UserExternalGPIO(bool enable)
{
    if(enable) {
        DevUpdateAT();
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
        .idx = DBG_UART_IDX,
        .bdtype = baudrateType,
        .pri = pariType
    };

    /* Note: you can set timeout you need */
    gDebugUart.timeout = BSP_UartSplitTime(baudrateType);
    gDebugUart.idx = uart.idx;

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
    BSP_DbgInit(uart.idx, UserDebugWrite);

    return success;
}

void UserDebugDeInit(void)
{
    BSP_UART_TypeDef uart = {
        .idx = DBG_UART_IDX
    };

    BSP_UartDeInit(&uart);

    BSP_DbgDeinit();

    return;
}

void UserDebugWrite(const uint8_t *data, uint32_t len)
{
    BSP_UartSend(DBG_UART_IDX, data, len);
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
        AppMacUpdateRx(true);
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
            AppMacUpdateRx(true);
        }
    }

    return;
}

/**
 *  FIXME:
 *  User should redefine config display function to reduce code size
 *  This function is called only by AT task.
 */
void DevCfg_Display(uint8_t uartIdx)
{
    rps_t rps = gDevFlash.config.rps;
    uint32_t freq  = gDevFlash.config.txfreq;
    char* bwstr = NULL;
    uint8_t ldrtx = 0;
    uint8_t ldrrx = 0;
    int8_t txpow = gDevFlash.config.txpow;
    bool notAes = binIsTag(0x00, gDevFlash.config.appKey, 16);
    ldrtx = (gDevFlash.config.rps.lowRate >> 2)&0x03;
    ldrrx = gDevFlash.config.rps.lowRate&0x03;

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

    /* Use RFO, limit power +14dBm */
    if((gDevFlash.config.dtype >> TYPE_BITS_RFO) & 0x01){
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

    printk("POW:\t%ddBm\r\nBW:\t%s\r\n"
           "TSF:\t%u\r\nRSF:\t%u\r\nCR:\t4/%u\r\nMODE:\t%s\r\nSYNC:\t0x%X\r\n"
           "PREM:\t%u,%u\r\nFIX:\t%u,%u\r\nCRC:\t%s\r\nTIQ:\t%s\r\nRIQ:\t%s\r\n",
           txpow,bwstr,
           gDevFlash.config.txsf,gDevFlash.config.rxsf,rps.cr + 4,
           gDevFlash.config.rps.modem?"LORA":"FSK",
           gDevFlash.config.syncword,
           gDevFlash.config.tprem,gDevFlash.config.rprem,
           gDevFlash.config.tfix,gDevFlash.config.rfix,
           rps.crc?"ON":"OFF",
           gDevFlash.config.rps.tiq?"ON":"OFF",
           gDevFlash.config.rps.riq?"ON":"OFF");

    printk("SEQ:\t%s\r\nIP:\t%s\r\nAES:\t%s\r\nACK:\t%s\r\n"
           "LDR:\t%u,%u\r\nLCP:\t%u\r\nLFT:\t%u\r\n"
           "FNB:\t0x%02X\r\nTYPE:\t0x%02X\r\nFlash:\t%u\r\n",
           gDevFlash.config.prop.seqMode?"ON":"OFF",
           gDevFlash.config.prop.ipMode?"ON":"OFF",
           notAes?"OFF":"ON",
           gDevFlash.config.prop.ack?"ON":"OFF",ldrtx,ldrrx,
           gDevFlash.config.lcp, gDevFlash.config.lftime,
           gDevFlash.config.fnb,
           gDevFlash.config.dtype,gDevFlash.config.flash_err);

    osExitCritical();
    return;
}

void DevCfg_UserDefault(uint8_t opts)
{
}

bool DevCfg_UserUpdate(uint8_t *data, uint32_t len)
{
    /** @todo: */
    return true;
}

bool DevUserInit(void)
{
    bool success = false;

    /* init default parameters */
    memset(&sADCConfig, 0, sizeof(sADCConfig));
    gParam.dev.ver = APP_DEV_VER;

    success = UserDebugInit(false, gDevFlash.config.prop.bdrate, gDevFlash.config.prop.pari);

    UserInitGPIO();

    return success;
}

void DevGetVol(uint32_t param1, uint16_t param2)
{
    uint32_t adc = 0;

    /* Internal 2.5V voltage reference */
    sADCConfig.ref = RefVolSelInBgr2p5;

    BSP_ADC_Enable(&sADCConfig);
    adc = 3 * BSP_ADC_Sample(0, AdcAVccDiV3Input);
    /** example */
    /*
    adc = BSP_ADC_Sample(0, AdcExInputCH2);
    adc = (adc*2500)/4096;
    */
    BSP_ADC_Disable(NULL);

    gParam.dev.vol = (adc*2500)/4096;
    gParam.dev.level = calc_level(16, MIN_VOL_LEVEL, MAX_VOL_LEVEL, gParam.dev.vol);
    gParam.dev.res = adc/100;

}


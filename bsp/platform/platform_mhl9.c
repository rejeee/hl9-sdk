/*******************************************************************************
 * @file    platform_mhl9.h
 * @brief   The HL9 platform interface implementation
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#include "platform.h"
#include <stdarg.h>

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
    /* TODO: */
}

bool DebugInit(uint32_t baudrateType, uint8_t pariType)
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

    /* first init UART for DEBUG */
    success = DevDebug_Init(&uart, sDebugBuffer, sizeof(sDebugBuffer));

    return success;
}

bool DebugReInit(uint32_t baudrateType, uint8_t pariType)
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

    /* first init UART for DEBUG */
    success = DevDebug_ReInit(&uart);

    return success;
}

void DebugWrite(const uint8_t *data, uint32_t len)
{
    BSP_UartSend(DBG_UART_NUM, data, len);
}

/*!
 * @brief radio hal API implemetation
 */
void RadioDelay(uint32_t ms)
{
    osDelayMs(ms);
}

/*!
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

void DevExternalGPIO(bool enable)
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

void RadioAntLowPower(uint8_t param)
{

}

void RadioAntSwitch(uint8_t param)
{

}

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

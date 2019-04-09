/*******************************************************************************
 * @file    hl9.h
 * @brief   The main function of special device platform
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef PLATFORM_HL9_H
#define PLATFORM_HL9_H

#include "platform_conf.h"
#include "common/dev.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO_READ       Gpio_GetInputIO

typedef union {
    uint8_t val;
    stc_reset_cause_t bits;
} union_cause_t;

struct global_param_t {
    dev_param_t     dev;
    BSP_OS_THREAD   mainid;
    BSP_OS_THREAD   macid;
    BSP_OS_MUTEX    mutex;
    union_cause_t   rst;
    uint8_t         at_mode;        /* AT command or transparent */
    uint8_t         at_switch;      /* AT switch */
};

/****
Global Variable
****/
extern struct global_param_t    gParam;
extern volatile bool            gEnableRadioRx;

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

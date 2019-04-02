/*******************************************************************************
 * @file    bsp_cpu.h
 * @brief   The mcu driver libraries.
 *          This is a convenience header file for defining difference board.
 *
 * @version 0.0.1
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/

#ifndef BSP_CPU_H
#define BSP_CPU_H

/*
 * Include the cpu specific register header files.
 *
 * The CPU macro should be declared in the project or makefile.
 */
#include "HC32L13X/driver/inc/reset.h"

#include "HC32L13X/emdrv/bsp_adc.h"
#include "HC32L13X/emdrv/bsp_clock.h"
#include "HC32L13X/emdrv/bsp_flash.h"
#include "HC32L13X/emdrv/bsp_lpower.h"
#include "HC32L13X/emdrv/bsp_i2c.h"
#include "HC32L13X/emdrv/bsp_pca.h"
#include "HC32L13X/emdrv/bsp_spi.h"
#include "HC32L13X/emdrv/bsp_rtc.h"
#include "HC32L13X/emdrv/bsp_uart.h"
#include "HC32L13X/emdrv/bsp_watchdog.h"

#endif


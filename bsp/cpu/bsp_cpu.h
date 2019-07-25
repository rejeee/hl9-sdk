/*******************************************************************************
 * @file    bsp_cpu.h
 * @brief   The mcu driver libraries.
 *          This is a convenience header file for defining difference board.
 *
 * @version 1.0.0
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
#include "bsp_watchdog.h"
#include "bsp_spi.h"
#include "bsp_flash.h"
#include "bsp_uart.h"
#include "bsp_adc.h"
#include "bsp_clock.h"
#include "bsp_lpower.h"

#endif


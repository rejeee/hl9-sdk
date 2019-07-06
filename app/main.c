/*******************************************************************************
 * @file    main.c
 * @brief   the entry of current program
 *
 * @version 0.0.2
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#include "app.h"

#ifndef BOOL_EXTL_EN
    #define BOOL_EXTL_EN          0
#endif

#ifndef BOOL_EXTH_EN
    #define BOOL_EXTH_EN          0
#endif

/****
Global Variable
****/

/****
Global Funtion
****/

/**
 * Main Funtcion
 */
int main(void)
{
    /* the first initialization operation */
    if(false == BSP_OS_Init(BOOL_EXTH_EN, BOOL_EXTL_EN)){
        NVIC_SystemReset();
        return 1;
    }

    AppInit();

    return 0;
}

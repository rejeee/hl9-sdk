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
    if(false == BSP_OS_Init()){
        NVIC_SystemReset();
        return 1;
    }

    AppInit();

    return 0;
}

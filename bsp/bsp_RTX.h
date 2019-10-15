/*******************************************************************************
 * @file    bsp_RTX.h
 * @brief   The common RTX interface for embedded devices
 *
 * @version 1.0.0
 *******************************************************************************
 * @license Refer License or other description Docs
 * @author  Felix
 ******************************************************************************/
#ifndef  BSP_RTX_H
#define  BSP_RTX_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "cmsis_os.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define  DEF_DISABLED           0U
#define  DEF_ENABLED            1U

#ifndef  TRACE_LEVEL_OFF
#define  TRACE_LEVEL_OFF        0u
#endif

#ifndef  TRACE_LEVEL_ERR
#define  TRACE_LEVEL_ERR        1u
#endif

#ifndef  TRACE_LEVEL_INFO
#define  TRACE_LEVEL_INFO       2u
#endif

#ifndef  TRACE_LEVEL_DBG
#define  TRACE_LEVEL_DBG        3u
#endif

#ifndef  TRACE_LEVEL_TRAC
#define  TRACE_LEVEL_TRAC       4u
#endif

/* Block size must be a multiple address size (4X) */
#define MEM_POOL_BLOCK_SIZE     228
#define MEM_POOL_LIST_SIZE      5U

/* redefine RTOS funcion API */
#define OS_ALWAYS_DELAY         osWaitForever
#define osSaveCritical()
#define osEnterCritical()       __disable_irq()
#define osExitCritical()        __enable_irq()

#define osDelayMs(x)            osDelay(x)

#define BSP_OS_SemPostISR(x)    BSP_OS_SemPost(x)

/*
********************************************************************************
* Data Types
********************************************************************************
*/
typedef osThreadId              BSP_OS_THREAD;
typedef osSemaphoreId           BSP_OS_SEM;
typedef osMutexId               BSP_OS_MUTEX;
typedef osPoolId                BSP_OS_MPOOL;
typedef osMessageQId            BSP_OS_MQ;
typedef osThreadId              BSP_OS_FLAG;

#if (osFeature_Pool == DEF_ENABLED)
typedef struct {
  uint8_t data[MEM_POOL_BLOCK_SIZE];
  uint8_t len;
} BSP_OS_MPoolBlock;
#endif

/*
********************************************************************************
* Function prototypes
********************************************************************************
*/

bool BSP_OS_TaskCreate(osThreadId *ptr, const osThreadDef_t *def, void *argument);

/**
 * @brief Creates a sempahore to lock/unlock
 *
 * @param p_sem      Pointer to a semaphore structure
 * @param count     Initial value of the semaphore
 * @param def       Pointer to a semaphore definition
 *
 * @return  true  if the semaphore was created.
 *          false if the semaphore could not be created.
 */
bool BSP_OS_SemCreate(BSP_OS_SEM *p_sem, int32_t count, const osSemaphoreDef_t *def);

/**
 * @brief Wait on a semaphore to become available
 *
 * @param p_sem     Pointer to a semaphore structure
 * @param dly_ms    delay in miliseconds to wait on the semaphore
 *
 * @return  true  if the semaphore was acquire.
 *          false if the semaphore could not be acquire.
 */
bool BSP_OS_SemWait(const BSP_OS_SEM *p_sem, uint32_t dly_ms);

/**
 * @brief Post a semaphore
 *
 * @param p_sem      Pointer to a semaphore structure
 *
 * @return  true  if the semaphore was posted.
 *          false if the semaphore could not be posted.
 */
bool BSP_OS_SemPost(const BSP_OS_SEM *p_sem);

/**
 * @brief This function creates a mutex.
 *
 * @param p_mutex      is a pointer to the semaphore to initialize.
 *
 * @return  true  if the semaphore was set.
 *          false if the semaphore could not be set.
 */
bool BSP_OS_SemReset(const BSP_OS_SEM *p_sem);

/**
 * @brief This function creates a mutex.
 *
 * @param p_mutex   is a pointer to the mutex to initialize.
 * @param def       is a pointer to the mutex definition.
 *
 * @return  true  if the mutex was created.
 *          false if the mutex could not be created.
 */
bool BSP_OS_MutexCreate(BSP_OS_MUTEX *p_mutex, const osMutexDef_t *def);

/**
 * @brief Wait on a mutex to become available
 *
 * @param p_mutex   Pointer to a mutex structure
 * @param dly_ms    delay in miliseconds to wait on the mutex
 *
 * @return  true  if the mutex was acquire.
 *          false if the mutex could not be acquire.
 */
bool BSP_OS_MutexLock(const BSP_OS_MUTEX *p_mutex, uint32_t dly_ms);

/**
 * @brief Post a mutex
 *
 * @param p_mutex   Pointer to a mutex structure
 *
 * @return  true  if the mutex was posted.
 *          false if the mutex could not be posted.
 */
bool BSP_OS_MutexUnLock(const BSP_OS_MUTEX *p_mutex);

#if (osFeature_MessageQ == DEF_ENABLED)
/**
 * @brief Creates a message queue.
 *
 * @param p_q       is a pointer of the message queue
 * @param def       is a pointer of the message definition.
 * @param thread_id thread ID or NULL
 *
 * @Note    that it's also not possible to have a size higher than the maximum number of osMessageQDef_t available.
 *
 * @return  true  if the queue was created.
 *          false if the queue could not be created.
 */
bool BSP_OS_QCreate(BSP_OS_MQ *p_q, const osMessageQDef_t *def, osThreadId thread_id);

/**
 * @brief Sends a message to a queue.
 *
 *
 * @param p_q       is a pointer to a message queue that must have been created
 * @param msg       is a pointer to the message to send.
 * @param msg_size  specifies the size of the message (in bytes)
 *
 * @return  true  if the queue was posted.
 *          false if the queue could not be posted.
 */
bool BSP_OS_QPost(const BSP_OS_MQ *p_q, void *msg, int16_t msg_size);

/**
 * @brief Waits for a message to be sent to a queue.
 *
 * @param p_q           is a pointer to the message queue
 * @param dly_ms        is an optional timeout period (in clock ticks).
 *
 * @param msg_size      the size of the message will be received
 *
 * @return     : != (void *)0  is a pointer to the message received
 *              == (void *)0  if you received a NULL pointer message or,
 *                            if no message was received or,
 *                            if 'ptr' is a NULL pointer or,
 *                            if you didn't pass a pointer to a queue.
 */
void *BSP_OS_QPend(const BSP_OS_MQ *p_q, uint32_t dly_ms, int16_t msg_size);

#endif

#if (osFeature_Pool == DEF_ENABLED)
bool BSP_OS_MemCreate(osPoolId *ptr, const osPoolDef_t *def);
bool BSP_OS_MemGet(const osPoolId *ptr, void **msg);
bool BSP_OS_MemPut(const osPoolId *ptr, void *p_blk);
#endif

/**
 * @brief Post a FLAG
 *
 * @param ptid      Pointer to a thread
 * @param evt       the value of FLAG to be post.
 *
 * @return  true  if the flag was posted.
 *          false if the flag could not be posted.
 */
bool BSP_OS_FlagPost(const osThreadId *ptid, int32_t evt);

int32_t BSP_OS_FlagWait(void *arg, int32_t flags, int32_t dly_ms);

bool BSP_OS_FlagClear(void *arg, int32_t evt);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

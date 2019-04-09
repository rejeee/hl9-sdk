/*******************************************************************************
 * @file    ringfifo.h
 * @brief   A implementation of FIFO buffer
 * Description: Buffer data is an array from external input
 *
 * @version 0.0.1
 *******************************************************************************
 * @license refer License or other description Docs
 * @author  Felix
 ******************************************************************************/

/*******************************************************************************
History: revision  date  author

v0.0.1
  1. The first revision.

*******************************************************************************/
#ifndef UTILS_RINGFIFO_H
#define UTILS_RINGFIFO_H

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
    
/**
 * the ring fifo structure
 */
typedef struct
{
    uint32_t getIdx;
    uint32_t putIdx;
    uint32_t idx;
    uint32_t size;
    uint8_t *pdata;
} Ringfifo;

/**
 * Initialize a ring fifo
 *
 * @param   rfifo   A pointer to a struct Ringfifo
 * @param   buffer  A pointer to an array of the buffer
 * @param   size    the size of the ring fifo
 */
void ringfifo_init(Ringfifo *rfifo, uint8_t *buffer, uint32_t size);

/**
 * Put a byte into the ring fifo
 *
 * @param   rfifo   A pointer to a struct Ringfifo
 * @param   b       The byte to be written to the buffer
 *
 * @return  1 if put success else 0
 */
int ringfifo_put(Ringfifo *rfifo, uint8_t b);

/**
 * Get a byte from the ring fifo
 *
 * @param   rfifo   A pointer to a struct Ringfifo
 *
 * @return  The byte to be read from the buffer else -1 if buffer is empty
 */
int ringfifo_get(Ringfifo *rfifo);

/**
 * Flush the ring fifo, reset all idx value to 0
 *
 * @param   rfifo   A pointer to a struct Ringfifo
 */
void ringfifo_flush(Ringfifo *rfifo);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif

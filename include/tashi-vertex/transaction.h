#ifndef TASHI_VERTEX_TRANSACTION_H
#define TASHI_VERTEX_TRANSACTION_H

#include <stddef.h>
#include <stdint.h>
#include <tashi-vertex/error.h>

#include "tashi-vertex/engine.h"

/**
 * @brief Allocates a buffer for a transaction of the specified size.
 */
extern TVResult tv_transaction_allocate(size_t size, uint8_t** data);

/**
 * @brief Sends a transaction to the Tashi Vertex engine.
 *
 * Data must have been allocated using tv_transaction_allocate.
 * Ownership of data is transferred to the engine; do not use it after calling this function.
 */
extern TVResult tv_transaction_send(const TVEngine* engine, uint8_t* data, size_t size);

/**
 * @brief Frees a transaction buffer that was allocated but never sent.
 *
 * Pass the pointer returned by tv_transaction_allocate and the exact size it
 * was allocated with. tv_transaction_send takes ownership of the buffer and
 * reclaims it, so this is only for a transaction that is never sent.
 *
 * Do NOT use tv_free for this — transaction buffers are not tagged pointers.
 */
extern TVResult tv_transaction_free(uint8_t* data, size_t size);

#endif  // TASHI_VERTEX_TRANSACTION_H

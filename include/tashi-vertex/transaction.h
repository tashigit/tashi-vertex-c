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

#endif  // TASHI_VERTEX_TRANSACTION_H

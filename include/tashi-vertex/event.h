#ifndef TASHI_VERTEX_EVENT_H
#define TASHI_VERTEX_EVENT_H

#include <stddef.h>
#include <stdint.h>
#include <tashi-vertex/error.h>
#include <tashi-vertex/key-public.h>

/**
 * @brief An event that has reached consensus in the Tashi Vertex network.
 */
typedef struct {
  /** @brief The timestamp that this event has reached consensus. */
  uint64_t consensus_at;

  /** @brief A cryptographically secure hash of this event. */
  uint8_t hash[32];

  /** @brief The peer that created the event. */
  TVKeyPublic peer;
} TVEvent;

/**
 * @brief Gets the timestamp at which the event was created.
 */
extern TVResult tv_event_get_created_at(const TVEvent* event, uint64_t* created_at);

/**
 * @brief Gets the number of transactions included in the event.
 */
extern TVResult tv_event_get_transaction_count(const TVEvent* event, size_t* count);

/**
 * @brief Gets the transaction at the given index.
 */
extern TVResult tv_event_get_transaction(const TVEvent* event, size_t index, uint8_t** transaction,
                                         size_t* transaction_size);

/**
 * @brief Gets the whitened signature, created by bytewise XORing the signature with the signatures
 * of all the unique famous witnesses for this event.
 *
 * This value is infeasible to predict ahead of time and is relatively high in entropy,
 * but all peers that see the event come to consensus will calculate the same result,
 * which makes it a good seed for a consensus-driven PRNG.
 */
extern TVResult tv_event_get_whitened_signature(const TVEvent* event, size_t index,
                                                uint8_t** signature, size_t* signature_size);

#endif  // TASHI_VERTEX_EVENT_H

#ifndef TASHI_VERTEX_EVENT_H
#define TASHI_VERTEX_EVENT_H

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

  // flexible storage that is not directly accessible
  uint8_t _internal[1];
} TVEvent;

/**
 * @brief Returns the number of transactions in the given event.
 */
extern size_t tv_event_transaction_count(const TVEvent* event);

#endif  // TASHI_VERTEX_EVENT_H

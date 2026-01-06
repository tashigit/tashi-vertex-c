#ifndef TASHI_VERTEX_PEER_H
#define TASHI_VERTEX_PEER_H

#include <stddef.h>
#include <tashi-vertex/error.h>
#include <tashi-vertex/key-public.h>

typedef enum {
  /**
   * @brief Peer does not contribute to determining the finalized order of events.
   */
  TV_PEER_NO_ORDER = 1 << 1,

  /**
   * @brief Peer does not know application logic.
   */
  TV_PEER_NO_LOGIC = 1 << 2,

  /**
   * @brief Peer is marked as having a stable public address (not behind NAT).
   */
  TV_PEER_PUBLIC = 1 << 3,

  /**
   * @brief Peer cannot be kicked from the session.
   */
  TV_PEER_UNKICKABLE = 1 << 4,
} TVPeerCapabilities;

/**
 * @brief Opaque pointer handle for a set of peers.
 *
 * Represents a unique set of peers in the network,
 * each identified by their network address and public key.
 *
 * @see tv_free() to release memory associated with a TVPeers.
 *      Note that passing a TVPeers into tv_engine_start() will transfer ownership.
 */
typedef struct TVPeers TVPeers;

/**
 * @brief Creates a new empty set of peers with the specified initial capacity.
 */
extern TVResult tv_peers_new(size_t capacity, TVPeers** peers);

/**
 * @brief Inserts a new peer into the set.
 *
 * Note that the address must be a valid IPv4 or IPv6 address, including the port number.
 * A DNS lookup is not performed.
 *
 */
extern TVResult tv_peers_insert(TVPeers* peers, const char* address, const TVKeyPublic* public_key,
                                int capabilities);

#endif  // TASHI_VERTEX_PEER_H

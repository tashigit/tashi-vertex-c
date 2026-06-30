#ifndef TASHI_VERTEX_ENGINE_H
#define TASHI_VERTEX_ENGINE_H

#include <stddef.h>
#include <stdint.h>
#include <tashi-vertex/context.h>
#include <tashi-vertex/error.h>
#include <tashi-vertex/key-public.h>
#include <tashi-vertex/key-secret.h>
#include <tashi-vertex/options.h>
#include <tashi-vertex/peer.h>
#include <tashi-vertex/socket.h>

/**
 * @brief Opaque handle for the Tashi Vertex (TV) engine.
 */
typedef struct TVEngine TVEngine;

/**
 * @brief Starts the consensus engine.
 *
 * The ownership of the provided socket, options, and peers is transferred to the engine.
 * The pointers are zeroed-out after the call to prevent accidental use.
 */
TVResult tv_engine_start(const TVContext* ctx, TVSocket** socket, TVOptions** options,
                         const TVKeySecret* secret, TVPeers** peers, TVEngine** engine,
                         bool joining_running_session);

/**
 * @brief Writes the DER-encoded public keys of the CURRENT active voting creators
 *        (the live BFT quorum membership) into out_buf.
 *
 * out_buf must have capacity cap_count * TV_KEY_PUBLIC_DER_LENGTH bytes; each key
 * occupies TV_KEY_PUBLIC_DER_LENGTH (91) bytes back-to-back. *out_count is set to
 * the TOTAL number of active creators -- if it exceeds cap_count, only the first
 * cap_count keys were written (retry with a larger buffer).
 *
 * Lets an external orchestrator read ground-truth quorum membership
 * (e.g. a kill-gate deciding whether a node may be failed).
 */
TVResult tv_engine_get_active_creators(const TVEngine* engine, uint8_t* out_buf, size_t cap_count,
                                       size_t* out_count);

/**
 * @brief Votes to (re-)admit a creator into the active voting set.
 *
 * A node that was kicked (fell behind / failed) is no longer in the active
 * creators; restarting it with joining_running_session lets it sync but does NOT
 * make it a voter again. Re-admission needs a supermajority of the CURRENT voters
 * to vote to add it. Each live voter calls this for the creator being recovered;
 * once a supermajority has, the engine re-adds it.
 *
 * address/public_key/capabilities describe the creator exactly as in
 * tv_peers_insert() (same capability bit layout). timeout_secs is how long this
 * add-vote stays active waiting for the supermajority to gather.
 */
TVResult tv_engine_vote_add_node(const TVEngine* engine, const char* address,
                                 const TVKeyPublic* public_key, uint8_t capabilities,
                                 uint64_t timeout_secs);

#endif  // TASHI_VERTEX_ENGINE_H

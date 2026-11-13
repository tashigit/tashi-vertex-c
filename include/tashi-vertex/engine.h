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

/**
 * @brief Gracefully stops the consensus engine.
 *
 * Signals the engine to begin a graceful shutdown. Once the engine has wound
 * down, in-flight and subsequent calls to tv_message_recv() complete with
 * TV_MESSAGE_NONE, so a consumer blocked on recv observes the stop even when no
 * further consensus messages are flowing (e.g. the session has lost quorum).
 *
 * The engine pointer remains valid after this call and must still be freed
 * with tv_free(). Calling this more than once is safe (idempotent).
 */
TVResult tv_engine_stop(const TVEngine* engine);

/** The agreed state was downloaded; `data`/`len` hold it for the duration of the callback. */
#define TV_STATE_READY 0
/** This node's own report for the epoch matches the agreed state; nothing was downloaded. */
#define TV_STATE_CONVERGED 1
/** No state for the epoch was agreed and downloaded in time. */
#define TV_STATE_TIMED_OUT 2
/** The request was cancelled, for instance because the engine shut down. */
#define TV_STATE_CANCELLED 3
/** The request failed, for instance because state sharing is disabled. */
#define TV_STATE_ERROR 4

/**
 * @brief Called once with the outcome of tv_engine_request_state().
 *
 * `status` is one of the TV_STATE_* values. With TV_STATE_READY, `data`/`len` hold the agreed
 * state and are only valid during the call. Runs on an engine thread.
 */
typedef void (*TVStateRequestCallback)(TVResult result, uint8_t status, const uint8_t* data,
                                       size_t len, void* user_data);

/**
 * @brief Reports this node's application state for the epoch that a sync point began.
 *
 * The engine signs the hash of `data` as this node's state proof for `epoch_index`. When a
 * super-majority of active creators report the same hash, that state is authoritative for the
 * epoch, and a creator that comes back after missing epochs can download it with
 * tv_engine_request_state() instead of the events it missed.
 *
 * Every node must derive `data` deterministically from the finalized order, so that honest nodes
 * report identical bytes. Read the epoch from tv_sync_point_get_epoch_index().
 */
TVResult tv_engine_report_state(const TVEngine* engine, uint64_t epoch_index, const uint8_t* data,
                                size_t len);

/**
 * @brief Requests the application state agreed for `epoch_index`.
 *
 * The engine waits until a super-majority of the epoch's active creators signed one state hash,
 * downloads that state from peers and checks it against the hash before `callback` runs with
 * TV_STATE_READY. `callback` is called exactly once. Requires
 * tv_options_set_enable_state_sharing().
 */
TVResult tv_engine_request_state(const TVEngine* engine, uint64_t epoch_index,
                                 TVStateRequestCallback callback, void* user_data);

#endif  // TASHI_VERTEX_ENGINE_H

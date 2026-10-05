#ifndef TASHI_VERTEX_SYNC_POINT_H
#define TASHI_VERTEX_SYNC_POINT_H

#include <stdbool.h>
#include <stdint.h>
#include <tashi-vertex/error.h>

/**
 * @brief A sync point describes a decision or action related to the management of the consensus engine which a super-majority of peers agreed upon.
 */
typedef struct TVSyncPoint TVSyncPoint;

/**
 * @brief Gets the index of the epoch this sync point begins.
 *
 * A new epoch is the application's cue to checkpoint/serialize its state (and,
 * if it submits state proofs, to report or request state for this epoch).
 */
TVResult tv_sync_point_get_epoch_index(const TVSyncPoint* sync_point, uint64_t* epoch_index);

/**
 * @brief Reports whether this sync point is the first one observed after the node
 * synced into the session (its address book was delivered as a unit).
 *
 * On a just-synced sync point the application should load its initial state.
 */
TVResult tv_sync_point_is_just_synced(const TVSyncPoint* sync_point, bool* just_synced);

/**
 * @brief Reports whether this sync point marks the end of the session, after which
 * no further consensus messages will be produced.
 */
TVResult tv_sync_point_is_session_ended(const TVSyncPoint* sync_point, bool* session_ended);

#endif  // TASHI_VERTEX_SYNC_POINT_H

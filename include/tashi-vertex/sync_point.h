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
 * A new epoch is the application's cue to checkpoint its state for this epoch
 * (and, if it submits state proofs, to report or request state).
 */
extern TVResult tv_sync_point_get_epoch_index(const TVSyncPoint* sync_point, uint64_t* epoch_index);

/**
 * @brief Reports whether this is the first sync point after the node synced
 * into the session. On a just-synced sync point the application should load its
 * initial state.
 */
extern TVResult tv_sync_point_is_just_synced(const TVSyncPoint* sync_point, bool* just_synced);

/**
 * @brief Reports whether this sync point marks the end of the session, after
 * which no further consensus messages will be produced.
 */
extern TVResult tv_sync_point_is_session_ended(const TVSyncPoint* sync_point, bool* session_ended);

#endif  // TASHI_VERTEX_SYNC_POINT_H

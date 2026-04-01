#ifndef TASHI_VERTEX_ENGINE_H
#define TASHI_VERTEX_ENGINE_H

#include <tashi-vertex/context.h>
#include <tashi-vertex/error.h>
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

#endif  // TASHI_VERTEX_ENGINE_H

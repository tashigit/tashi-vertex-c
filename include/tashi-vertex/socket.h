#ifndef TASHI_VERTEX_SOCKET_H
#define TASHI_VERTEX_SOCKET_H

#include <tashi-vertex/context.h>
#include <tashi-vertex/error.h>

/**
 * @brief Opaque handle to a Tashi Vertex socket.
 *
 * @see tv_free() to release memory associated with a TVSocket.
 */
typedef struct TVSocket TVSocket;

typedef void (*TVSocketBindCallback)(TVResult result, TVSocket* socket, void* user_data);

/**
 * @brief Binds a Tashi Vertex (TV) socket to the specified address.
 */
extern TVResult tv_socket_bind(const TVContext* context, char* address,
                               TVSocketBindCallback callback, void* user_data);

#endif  // TASHI_VERTEX_SOCKET_H

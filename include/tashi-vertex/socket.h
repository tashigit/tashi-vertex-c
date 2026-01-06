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
 *
 * Note that the address must be a valid IPv4 or IPv6 address, including the port number.
 * A DNS lookup is not performed.
 *
 */
extern TVResult tv_socket_bind(const TVContext* context, const char* address,
                               TVSocketBindCallback callback, void* user_data);

#endif  // TASHI_VERTEX_SOCKET_H

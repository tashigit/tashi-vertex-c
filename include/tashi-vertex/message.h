#ifndef TASHI_VERTEX_MESSAGE_H
#define TASHI_VERTEX_MESSAGE_H

#include <tashi-vertex/engine.h>
#include <tashi-vertex/error.h>

typedef enum {
  TV_MESSAGE_NONE = 0,
  TV_MESSAGE_EVENT = 1,
  TV_MESSAGE_SYNC_POINT = 2,
} TVMessage;

typedef void (*TVMessageRecvCallback)(TVResult result, TVMessage message, void* data,
                                      void* user_data);

/**
 * @brief Listens for the next incoming message on the given engine.
 *
 * Callback will be invoked when a message is received or an error occurs.
 */
extern TVResult tv_message_recv(const TVEngine* engine, TVMessageRecvCallback callback,
                                void* user_data);

#endif  // TASHI_VERTEX_MESSAGE_H

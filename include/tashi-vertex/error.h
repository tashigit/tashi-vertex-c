#ifndef TASHI_VERTEX_ERROR_H
#define TASHI_VERTEX_ERROR_H

typedef enum {
  TV_OK = 0,

  /** @brief An argument provided to a function was invalid. */
  TV_ERROR_ARGUMENT = -1,

  /** @brief A required argument provided to a function was NULL. */
  TV_ERROR_ARGUMENT_NULL = -2,

  /** @brief Failed to parse a key from DER format. */
  TV_ERROR_KEY_FROM_DER = -3,

  /** @brief Failed to initialize a new TVContext. */
  TV_ERROR_CONTEXT = -4,

  /** @brief A provided buffer was too small to hold the required data. */
  TV_ERROR_BUFFER_TOO_SMALL = -5,

  /** @brief Failed to decode a Base58 string. */
  TV_ERROR_BASE58_DECODE = -6,

  /** @brief Failed to bind a socket. */
  TV_ERROR_SOCKET_BIND = -7,
} TVResult;

#endif  // TASHI_VERTEX_ERROR_H

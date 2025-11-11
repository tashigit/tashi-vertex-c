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
} TVResult;

#endif  // TASHI_VERTEX_ERROR_H

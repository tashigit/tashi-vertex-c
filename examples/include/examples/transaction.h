#ifndef EXAMPLES_TRANSACTION_H
#define EXAMPLES_TRANSACTION_H

#include <stdint.h>
#include <string.h>
#include <tashi-vertex/engine.h>
#include <tashi-vertex/transaction.h>

#include "tashi-vertex/error.h"

/**
 * @brief Sends a string as a transaction.
 */
TVResult tv_transaction_send_string(const TVEngine* engine, const char* string) {
  TVResult result = 0;
  uint8_t* buffer = NULL;
  size_t size = strlen(string);

  result = tv_transaction_allocate(size, &buffer);
  if (result < 0) {
    return result;
  }

  result = tv_transaction_send(engine, buffer, size);
  if (result < 0) {
    return result;
  }

  return TV_OK;
}

#endif  // EXAMPLES_TRANSACTION_H

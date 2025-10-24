#ifndef TASHI_VERTEX_BASE58_H
#define TASHI_VERTEX_BASE58_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Calculate the maximum length of a Base58 encoded string
 *        given the length of the input byte array.
 */
static inline size_t tv_base58_length(size_t input_len) {
  // log_2(256) / log_2(58) ≈ 1.37.  Assume 1.5 for easier calculation.
  return input_len + ((input_len + 1) / 2);
}

/**
 * @brief Encode a byte array into a Base58 string.
 */
void tv_base58_encode(const uint8_t* input, size_t input_len, char* output, size_t output_len);

#endif  // TASHI_VERTEX_BASE58_H

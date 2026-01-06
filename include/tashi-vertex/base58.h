#ifndef TASHI_VERTEX_BASE58_H
#define TASHI_VERTEX_BASE58_H

#include <stddef.h>
#include <stdint.h>
#include <tashi-vertex/error.h>

/**
 * @brief Calculates the maximum length of a Base58 encoded string
 *        given the length of the input byte array.
 */
static inline size_t tv_base58_encode_length(size_t input_len) {
  // n * log(256) / log(58) + 1
  return ((input_len * 138 / 100) + 1);
}

/**
 * @brief Encodes a byte array into a Base58 string.
 */
TVResult tv_base58_encode(const uint8_t* input, size_t input_len, char* output, size_t output_len);

/**
 * @brief Calculates the maximum length of a decoded byte array
 *        given the length of the Base58 encoded string.
 */
static inline size_t tv_base58_decode_length(size_t input_len) {
  // n * log(58) / log(256) + 1
  return ((input_len * 733 / 1000) + 1);
}

/**
 * @brief Decodes a Base58 string into a byte array.
 */
TVResult tv_base58_decode(const char* input, size_t input_len, uint8_t* output, size_t output_len);

#endif  // TASHI_VERTEX_BASE58_H

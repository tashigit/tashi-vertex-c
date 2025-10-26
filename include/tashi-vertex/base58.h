#ifndef TASHI_VERTEX_BASE58_H
#define TASHI_VERTEX_BASE58_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Calculate the maximum length of a Base58 encoded string
 *        given the length of the input byte array.
 */
static inline size_t tv_base58_encode_length(size_t input_len) {
  // n * log(256) / log(58) + 1
  return (input_len * 138 / 100 + 1);
}

/**
 * @brief Encode a byte array into a Base58 string.
 */
void tv_base58_encode(const uint8_t* input, size_t input_len, char* output, size_t output_len);

/**
 * @brief Calculate the maximum length of a decoded byte array
 *        given the length of the Base58 encoded string.
 */
static inline size_t tv_base58_decode_length(size_t input_len) {
  // n * log(58) / log(256) + 1
  return (input_len * 733 / 1000 + 1);
}

/**
 * @brief Decode a Base58 string into a byte array.
 */
void tv_base58_decode(const char* input, size_t input_len, uint8_t* output, size_t output_len);

#endif  // TASHI_VERTEX_BASE58_H

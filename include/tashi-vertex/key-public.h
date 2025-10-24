#pragma once
#ifndef TASHI_VERTEX_KEY_PUBLIC_H
#define TASHI_VERTEX_KEY_PUBLIC_H

#include <stdint.h>

#define TV_KEY_PUBLIC_DER_LENGTH 91

/**
 * @brief A public key used for verifying signatures in Tashi Vertex.
 */
typedef struct TVKeyPublic {
  uint8_t _x[32];
  uint8_t _y[32];
  uint8_t _infinity;
} TVKeyPublic;

/**
 * @brief Convert the public key to DER format.
 */
void tv_key_public_to_der(const TVKeyPublic* sec, uint8_t* out, size_t out_len);

#endif  // TASHI_VERTEX_KEY_PUBLIC_H

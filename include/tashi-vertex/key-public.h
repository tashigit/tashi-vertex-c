#ifndef TASHI_VERTEX_KEY_PUBLIC_H
#define TASHI_VERTEX_KEY_PUBLIC_H

#include <stddef.h>
#include <stdint.h>
#include <tashi-vertex/error.h>

#define TV_KEY_PUBLIC_DER_LENGTH 91

/**
 * @brief A public key used for verifying signatures in Tashi Vertex.
 */
typedef struct TVKeyPublic {
  uint8_t _material[72];
} TVKeyPublic;

/**
 * @brief Formats the public key to DER format.
 */
TVResult tv_key_public_to_der(const TVKeyPublic* pub, uint8_t* der, size_t der_len);

/**
 * @brief Parses a public key from DER format.
 */
TVResult tv_key_public_from_der(const uint8_t* der, size_t der_len, TVKeyPublic* pub);

#endif  // TASHI_VERTEX_KEY_PUBLIC_H

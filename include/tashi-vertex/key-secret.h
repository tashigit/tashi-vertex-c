#ifndef TASHI_VERTEX_KEY_SECRET_H
#define TASHI_VERTEX_KEY_SECRET_H

#include <stddef.h>
#include <stdint.h>

#define TV_KEY_SECRET_DER_LENGTH 51

struct TVKeyPublic;

/**
 * @brief A secret key used for signing transactions in Tashi Vertex.
 */
typedef struct TVKeySecret {
  uint8_t _material[32];
} TVKeySecret;

/**
 * @brief Generate a new secret key.
 *
 * This function populates the provided TVKeySecret structure with a newly
 * generated secret key suitable for signing transactions.
 */
void tv_key_secret_generate(TVKeySecret* sec);

/**
 * @brief Derive the public key from a given secret key.
 */
void tv_key_secret_to_public(const TVKeySecret* sec, TVKeyPublic* pub);

/**
 * @brief Convert the secret key to DER format.
 */
void tv_key_secret_to_der(const TVKeySecret* sec, uint8_t* out, size_t out_len);

#endif  // TASHI_VERTEX_KEY_SECRET_H

#ifndef EXAMPLES_PRINT_H
#define EXAMPLES_PRINT_H

#include <stdio.h>
#include <stdint.h>
#include <tashi-vertex/base58.h>
#include <tashi-vertex/key-public.h>
#include <tashi-vertex/key-secret.h>

static inline void print_bs58(const uint8_t* data, size_t data_len) {
  size_t bs58_len = tv_base58_encode_length(data_len) + 1;
  char b58[bs58_len];

  tv_base58_encode(data, data_len, b58, bs58_len);

  printf("%s", b58);
}

static inline void print_key_secret(const TVKeySecret* secret) {
  static uint8_t der[TV_KEY_SECRET_DER_LENGTH];
  tv_key_secret_to_der(secret, der, TV_KEY_SECRET_DER_LENGTH);

  print_bs58(der, TV_KEY_SECRET_DER_LENGTH);
}

static inline void print_key_public(const TVKeyPublic* public) {
  static uint8_t der[TV_KEY_PUBLIC_DER_LENGTH];
  tv_key_public_to_der(public, der, TV_KEY_PUBLIC_DER_LENGTH);

  print_bs58(der, TV_KEY_PUBLIC_DER_LENGTH);
}

#endif  // EXAMPLES_PRINT_H

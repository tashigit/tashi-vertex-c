#include <stdio.h>
#include <tashi-vertex/base58.h>
#include <tashi-vertex/tashi-vertex.h>

static void print_bs58(const uint8_t* data, size_t data_len) {
  size_t bs58_len = tv_base58_length(data_len) + 1;
  char b58[bs58_len];

  tv_base58_encode(data, data_len, b58, bs58_len);

  printf("%s", b58);
}

static void print_key_secret(const TVKeySecret* secret) {
  static uint8_t der[TV_KEY_SECRET_DER_LENGTH];
  tv_key_secret_to_der(secret, der, TV_KEY_SECRET_DER_LENGTH);

  print_bs58(der, TV_KEY_SECRET_DER_LENGTH);
}

static void print_key_public(const TVKeyPublic* public) {
  static uint8_t der[TV_KEY_PUBLIC_DER_LENGTH];
  tv_key_public_to_der(public, der, TV_KEY_PUBLIC_DER_LENGTH);

  print_bs58(der, TV_KEY_PUBLIC_DER_LENGTH);
}

int main() {
  // generate a new secret key to use for this node when signing transactions
  TVKeySecret secret;
  tv_key_secret_generate(&secret);

  printf(" * Generated new secret key: ");
  print_key_secret(&secret);
  printf("\n");

  // derive the corresponding public key from the secret key
  TVKeyPublic public;
  tv_key_secret_to_public(&secret, &public);

  printf(" * Derived public key: ");
  print_key_public(&public);
  printf("\n");

  // initialize a new Tashi Vertex (TV) context
  TVContext* ctx = NULL;
  tv_context_new(&ctx);

  printf(" * Initialized Tashi Vertex (starting runtime, generated keys, allocating resources)\n");

  // free the context when done to clean up
  tv_free(ctx);

  return 0;
}

/**
 * Parses either a secret key and prints both the secret and public keys
 * or parses just the public key and only prints that.
 */

#include <stdio.h>
#include <string.h>
#include <tashi-vertex/tashi-vertex.h>

#include "examples/print.h"
#include "examples/result.h"

void parse_secret(const char* secret_s) {
  TVKeySecret secret;
  TVKeyPublic public;

  // decode the base58 secret key into DER
  size_t secret_der_len = TV_KEY_SECRET_DER_LENGTH;
  uint8_t secret_der[TV_KEY_SECRET_DER_LENGTH];
  TV_TRY(tv_base58_decode(secret_s, strlen(secret_s), secret_der, &secret_der_len));

  // parse the DER into a secret key
  TV_TRY(tv_key_secret_from_der(secret_der, secret_der_len, &secret));

  // derive the corresponding public key from the secret key
  tv_key_secret_to_public(&secret, &public);

  printf("Secret: ");
  print_key_secret(&secret);
  printf("\n");

  printf("Public: ");
  print_key_public(&public);
  printf("\n");
}

void parse_public(const char* public_s) {
  TVKeyPublic public;

  // decode the base58 public key into DER
  size_t public_der_len = TV_KEY_PUBLIC_DER_LENGTH;
  uint8_t public_der[TV_KEY_PUBLIC_DER_LENGTH];
  TV_TRY(tv_base58_decode(public_s, strlen(public_s), public_der, &public_der_len));

  // parse the DER into a public key
  TV_TRY(tv_key_public_from_der(public_der, public_der_len, &public));

  printf("Public: ");
  print_key_public(&public);
  printf("\n");
}

int main(int argc, char** argv) {
  if (argc == 3) {
    TVKeySecret secret;
    TVKeyPublic public;

    if (strcmp(argv[1], "--secret") == 0) {
      parse_secret(argv[2]);

      return 0;
    }

    if (strcmp(argv[1], "--public") == 0) {
      parse_public(argv[2]);

      return 0;
    }
  }

  printf("Usage: %s --secret KEY\n", argv[0]);
  printf("   or: %s --public KEY\n", argv[0]);

  return 0;
}

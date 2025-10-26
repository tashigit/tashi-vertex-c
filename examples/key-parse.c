/**
 * Parses either a secret key and prints both the secret and public keys
 * or parses just the public key and only prints that.
 */

#include <stdio.h>
#include <string.h>
#include <tashi-vertex/tashi-vertex.h>

#include "examples/print.h"

int main(int argc, char** argv) {
  if (argc == 3) {
    TVKeySecret secret;
    TVKeyPublic public;

    if (strcmp(argv[1], "--secret") == 0) {
      // decode the base58 secret key into DER
      uint8_t secret_der[TV_KEY_SECRET_DER_LENGTH];
      tv_base58_decode(argv[2], strlen(argv[2]), secret_der, TV_KEY_SECRET_DER_LENGTH);

      // parse the DER into a secret key
      tv_key_secret_from_der(secret_der, TV_KEY_SECRET_DER_LENGTH, &secret);

      // derive the corresponding public key from the secret key
      tv_key_secret_to_public(&secret, &public);

      printf("Secret: ");
      print_key_secret(&secret);
      printf("\n");

      printf("Public: ");
      print_key_public(&public);
      printf("\n");

      return 0;
    }

    if (strcmp(argv[1], "--public") == 0) {
      // decode the base58 public key into DER
      uint8_t public_der[TV_KEY_PUBLIC_DER_LENGTH];
      tv_base58_decode(argv[2], strlen(argv[2]), public_der, TV_KEY_PUBLIC_DER_LENGTH);

      // parse the DER into a public key
      tv_key_public_from_der(public_der, TV_KEY_PUBLIC_DER_LENGTH, &public);

      printf("Public: ");
      print_key_public(&public);
      printf("\n");

      return 0;
    }
  }

  printf("Usage: %s --secret KEY\n", argv[0]);
  printf("   or: %s --public KEY\n", argv[0]);

  return 0;
}

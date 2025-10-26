#include <stdio.h>
#include <tashi-vertex/tashi-vertex.h>

#include "examples/print.h"

int main() {
  // generate a new secret key to use for this node when signing transactions
  TVKeySecret secret;
  tv_key_secret_generate(&secret);

  printf("Secret: ");
  print_key_secret(&secret);
  printf("\n");

  // derive the corresponding public key from the secret key
  TVKeyPublic public;
  tv_key_secret_to_public(&secret, &public);

  printf("Public: ");
  print_key_public(&public);
  printf("\n");

  return 0;
}

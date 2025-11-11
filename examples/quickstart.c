#include <stdio.h>
#include <tashi-vertex/tashi-vertex.h>

#include "examples/print.h"

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

  // configure execution options for Tashi Vertex (TV)
  TVOptions* options;
  tv_options_new(&options);
  tv_options_set_report_gossip_events(options, true);
  tv_options_set_fallen_behind_kick_s(options, 10);

  return 0;
}

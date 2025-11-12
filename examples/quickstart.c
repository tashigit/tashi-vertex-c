#include <stdio.h>
#include <tashi-vertex/tashi-vertex.h>

#include "examples/print.h"

TVContext* context;
TVOptions* options;

void handle_socket_bound(TVResult result, TVSocket* socket, void* user_data) {
  if (result != TV_OK) return;

  printf(" * Bound socket\n");

  tv_free(&socket);
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
  // manages async. operations and resources
  // allows for operations to complete
  tv_context_new(&context);

  // bind a new socket to listen for incoming connections in the network
  tv_socket_bind(context, "localhost:36500", handle_socket_bound, NULL);

  // configure execution options for the Tashi Vertex (TV) engine
  TVOptions* options;
  tv_options_new(&options);
  tv_options_set_report_gossip_events(options, true);
  tv_options_set_fallen_behind_kick_s(options, 10);

  tv_free(&options);
  tv_free(&context);

  return 0;
}

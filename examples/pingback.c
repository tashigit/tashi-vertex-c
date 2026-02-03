#include <stdio.h>
#include <string.h>
#include <tashi-vertex/tashi-vertex.h>

#include "examples/result.h"
#include "examples/transaction.h"

TVContext* context = NULL;  // NOLINT
TVPeers* peers = NULL;      // NOLINT
TVKeySecret secret;         // NOLINT
TVEngine* engine = NULL;    // NOLINT

// NOLINTNEXTLINE
void handle_message_recv(TVResult result, TVMessage message, void* data, void* user_data) {
  TV_TRY(result);

  switch (message) {
    case TV_MESSAGE_NONE: {
      // we are shutting down
      return;
    }

    case TV_MESSAGE_EVENT: {
      TVEvent* event = (TVEvent*)data;
      size_t transactions = tv_event_transaction_count(event);

      if (transactions == 0) {
        // ignore empty events
        break;
      }

      printf(" > Received EVENT with %zu transaction(s)\n", transactions);

      break;
    }

    case TV_MESSAGE_SYNC_POINT: {
      printf(" > Received SYNC POINT\n");

      break;
    }
  }

  // listen for the next message
  tv_message_recv(engine, handle_message_recv, NULL);
}

void handle_socket_bound(TVResult result, TVSocket* socket, void* user_data) {
  TV_TRY(result);

  printf(" :: Bound local socket\n");

  // configure execution options for the Tashi Vertex (TV) engine
  TVOptions* options = NULL;
  tv_options_new(&options);
  tv_options_set_report_gossip_events(options, true);
  tv_options_set_fallen_behind_kick_s(options, 10);

  // start the engine
  // and begin participating in the network
  // ownership of `options` is transferred to the engine
  // ownership of `peers` is transferred to the engine
  // ownership of `socket` is transferred to the engine
  // ownership of `secret` is transferred to the engine
  TV_TRY(tv_engine_start(context, &socket, &options, &secret, &peers, &engine));

  printf(" :: Started the consensus engine\n");

  // send an initial PING transaction
  TV_TRY(tv_transaction_send_string(engine, "PING"));

  // start waiting for messages
  tv_message_recv(engine, handle_message_recv, NULL);
}

int main(int argc, char** argv) {  // NOLINT
  // initialize an empty set of peers for the network
  // capacity argument is *initial* capacity, it can grow
  // its only for performance tuning as it can help avoid a reallocation
  tv_peers_new(3, &peers);

  // read arguments
  // looking for 1 public key and bind address and N peers
  // store the socket address for use after the argument parse
  const char* bind_address = NULL;
  int npeer = 0;

  // what follows is a *very* naive argument parser
  // very little error checking is done
  // this is just for demo purposes and to ensure this runs on all platforms without dependencies
  // a production application should use a proper argument parser
  for (int argi = 1; argi < argc; argi++) {
    if (strcmp(argv[argi], "-K") == 0) {
      // next argument is the secret key for THIS node
      const char* secret_s = argv[++argi];
      size_t secret_der_len = TV_KEY_SECRET_DER_LENGTH;
      uint8_t secret_der[TV_KEY_SECRET_DER_LENGTH];

      TV_TRY(tv_base58_decode(secret_s, strlen(secret_s), secret_der, &secret_der_len));
      TV_TRY(tv_key_secret_from_der(secret_der, secret_der_len, &secret));
    } else if (strcmp(argv[argi], "-P") == 0) {
      // next argument pair is a public key and address for a peer
      const char* public_s = argv[++argi];
      const char* address = argv[++argi];
      size_t public_der_len = TV_KEY_PUBLIC_DER_LENGTH;
      uint8_t public_der[TV_KEY_PUBLIC_DER_LENGTH];
      TVKeyPublic public;

      TV_TRY(tv_base58_decode(public_s, strlen(public_s), public_der, &public_der_len));
      TV_TRY(tv_key_public_from_der(public_der, public_der_len, &public));

      TV_TRY(tv_peers_insert(peers, address, &public, 0));

      npeer++;
    } else if (strcmp(argv[argi], "-B") == 0) {
      // next argument is the bind address for THIS node
      bind_address = argv[++argi];
    }
  }

  // add ourself to the peer set
  TVKeyPublic public;
  tv_key_secret_to_public(&secret, &public);
  TV_TRY(tv_peers_insert(peers, bind_address, &public, 0));

  printf(" :: Configured network for %d peers\n", npeer);

  // initialize a new Tashi Vertex (TV) context
  // manages async. operations and resources
  // allows for operations to complete
  tv_context_new(&context);

  printf(" :: Initialized runtime\n");

  // bind a new socket to listen for incoming connections in the network
  tv_socket_bind(context, bind_address, handle_socket_bound, NULL);

  // releases the context
  // waits for async. operations to complete
  tv_free(context);

  return 0;
}

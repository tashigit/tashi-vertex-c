#include <stdio.h>
#include <tashi-vertex/tashi-vertex.h>

int main() {
    // initialize a new Tashi Vertex (TV) context
    TVContext* ctx;
    tv_context_new(&ctx);

    printf(" * Initialized Tashi Vertex (starting runtime, allocating resources) \n");

    // free the context when done to clean up
    tv_free(ctx);

    return 0;
}

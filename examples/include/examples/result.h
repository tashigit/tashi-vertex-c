#ifndef EXAMPLES_RESULT_H
#define EXAMPLES_RESULT_H

#include <stdlib.h>
#include <tashi-vertex/base58.h>

#define TV_TRY(expr)                                  \
  do {                                                \
    TVResult res = (expr);                            \
    if (res < 0) {                                    \
      printf("failed at <%s> with %d\n", #expr, res); \
      exit(EXIT_FAILURE);                             \
    }                                                 \
  } while (0)

#endif  // EXAMPLES_RESULT_H

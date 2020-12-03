#if !defined(_MARTA_WRAPPER_H)
#define _MARTA_WRAPPER_H

#include "definitions.h"
#include "polybench.h"

#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

#ifndef NRUNS
#define NRUNS 10000
#endif

#define MARTA_NO_HEADER 0
#define MARTA_CSV_HEADER 1

#if defined(POLYBENCH_PAPI)
struct T {
  char *name;
  char *feat;
  long flops;
  long_long counters[128];
} values_t;

struct T values[128];

long long n_func = 0;

void update_row(char *name, char *features, long flops, int t, long_long val) {
  if (t == 0) {
    struct T tmp;
    tmp.name = name;
    tmp.feat = features;
    tmp.flops = flops;
    tmp.counters[t] = val;
    values[n_func] = tmp;
    return;
  }
  values[n_func].counters[t] = val;
}
#endif

#define PROFILE_FUNCTION_SINGLE_VAL(STEPS, X)                                  \
  {                                                                            \
    polybench_prepare_instruments;                                             \
    polybench_start_instruments;                                               \
    for (int t = 0; t < STEPS; ++t) {                                          \
      X;                                                                       \
    }                                                                          \
    polybench_stop_instruments;                                                \
    polybench_print_instruments;                                               \
  }

/**
 * Macro to encapsulate a function call in the main function to enable
 * its profiling with the PolyBench harness.
 */
#if !defined(POLYBENCH_PAPI)
#define PROFILE_FUNCTION(STEPS, X, name, features, flops, i)                   \
  {                                                                            \
    polybench_prepare_instruments;                                             \
    polybench_start_instruments;                                               \
    for (int t = 0; t < STEPS; ++t) {                                          \
      X;                                                                       \
    }                                                                          \
    polybench_stop_instruments;                                                \
    printf("%s,%s,%ld,", name, features, flops);                               \
    polybench_print_instruments_flops(flops);                                  \
  }
#else
#define PROFILE_FUNCTION(STEPS, X, name, features, flops, t)                   \
  {                                                                            \
    polybench_start_instruments_single(t);                                     \
    X;                                                                         \
    polybench_stop_instruments_single(t);                                      \
    update_row(name, features, flops, t, polybench_get_value(t));              \
    n_func++;                                                                  \
  }
#endif

/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static void print_array1d(int n, DATA_TYPE POLYBENCH_1D(y, N, n)) {
  int i;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("y");
  for (i = 0; i < n; i++) {
    if (i % 20 == 0)
      fprintf(POLYBENCH_DUMP_TARGET, "\n");
    fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, y[i]);
  }
  POLYBENCH_DUMP_END("y");
  POLYBENCH_DUMP_FINISH;
}

/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static void print_array2d(int n, DATA_TYPE POLYBENCH_2D(A, N, N, n, n)) {
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("A");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (i % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, A[i][j]);
    }
  }
  POLYBENCH_DUMP_END("A");
  POLYBENCH_DUMP_FINISH;
}

#if defined(POLYBENCH_PAPI)
char *__polybench_papi_eventlist[] = {
#include "papi_counters.list"
    NULL};
#endif

/* Array initialization: 1-dimensional */
static void init_1darray(int n, DATA_TYPE POLYBENCH_1D(x, N, n)) {
  int i;

  for (i = 0; i < n; i++) {
    x[i] = 42;
  }
}

/* Array initialization: 2-dimensional */
static void init_2darray(int n, DATA_TYPE POLYBENCH_2D(A, N, N, n, n)) {
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      A[i][j] = 42;
    }
  }
}

#define MARTA_CHECK_HEADERS(cond)\
    if ((cond != MARTA_NO_HEADER) && (cond != MARTA_CSV_HEADER)) {             \
      fprintf(stderr, "[MARTA] Bad flag for BENCHMARK_BEGIN");                 \
      exit(1);                                                                 \
    }                                                                          \

#define MARTA_BENCHMARK_BEGIN(cond)                                            \
  int main(int argc, char **argv) {                                            \
    int i = 0;                                                                 \
    int n = N;                                                                 \
    int m = M;                                                                 \
    MARTA_CHECK_HEADERS(cond);                                                 \
    if (cond)                                                                  \
      printf("name,features,flops,time,gflops\n");

#define MARTA_BENCHMARK_END                                                    \
  return 0;                                                                    \
  }

#if defined(POLYBENCH_PAPI)
#undef MARTA_BENCHMARK_BEGIN
#define MARTA_BENCHMARK_BEGIN(cond)                                            \
  int main(int argc, char **argv) {                                            \
    int i = 0;                                                                 \
    int n = N;                                                                 \
    int m = M;                                                                 \
    MARTA_CHECK_HEADERS(cond);                                                 \
    if (cond) {                                                                \
      printf("name,features,flops,");                                          \
      while (__polybench_papi_eventlist[i] != NULL) {                          \
        if (__polybench_papi_eventlist[i + 1] == NULL) {                       \
          printf("%s", __polybench_papi_eventlist[i++]);                       \
        } else {                                                               \
          printf("%s,", __polybench_papi_eventlist[i++]);                      \
        }                                                                      \
      }                                                                        \
      printf("\n");                                                            \
    }                                                                          \
    i = 0;                                                                     \
    polybench_papi_init();                                                     \
    while (__polybench_papi_eventlist[i] != NULL) {                            \
      n_func = 0;                                                              \
      polybench_prepare_instruments();

#undef MARTA_BENCHMARK_END
#define MARTA_BENCHMARK_END                                                    \
  i++;                                                                         \
  }                                                                            \
  int n_count = i;                                                             \
  for (int n = 0; n < n_func; ++n) {                                           \
    struct T val = values[n];                                                  \
    printf("%s,%s,%ld,", val.name, val.feat, val.flops);                       \
    for (int c = 0; c < n_count; ++c) {                                        \
      printf("%llu", val.counters[c]);                                         \
      if (c + 1 < n_count) {                                                   \
        printf(",");                                                           \
      }                                                                        \
    }                                                                          \
    printf("\n");                                                              \
  }                                                                            \
  polybench_papi_close();                                                      \
  return 0;                                                                    \
  }
#endif

#endif /* ! MARTA_WRAPPER_H */

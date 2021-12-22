#ifndef NO_HEADER
#include "benchmark.h"
#endif

void kernel(float *restrict A, float *restrict B, float *restrict C) {
  for (int i = 0; i < N; ++i) {
    A[i] += B[i] * C[i];
  }
}
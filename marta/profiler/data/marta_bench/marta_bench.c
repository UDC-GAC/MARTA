#ifndef NO_HEADER
#include "marta_bench.h"
#endif

void kern(float *A, float *B, float *C) {
  for (int i = 0; i < N; ++i) {
    A[i] += B[i] * C[i];
  }
}
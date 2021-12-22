
#include "multithread.h"

void kernel(float *restrict A, float *restrict B, float *restrict C) {
#pragma omp parallel for
  for (int i = 0; i < N; ++i) {
    A[i] += B[i] * C[i];
  }
}
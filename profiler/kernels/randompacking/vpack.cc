#include "vpack.h"

#define restrict __restrict

void vpack(double *restrict A, double *restrict x, double *restrict y) {
#pragma macveth
  y[5] += A[4] * x[X_0];
  y[5] += A[5] * x[X_1];
#if NPACK >= 3
  y[5] += A[6] * x[X_2];
#endif
#if NPACK >= 4
  y[5] += A[7] * x[X_3];
#endif
#pragma endmacveth
}

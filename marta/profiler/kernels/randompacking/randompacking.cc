#include "randompacking.h"

#define restrict __restrict

#ifdef NOLOOP
void vpack(double *restrict A, double *restrict x, double *restrict y)
{
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
#elif defined(LOOP1D)
void vpack(double *restrict A, double *restrict x, double *restrict y)
{
#pragma macveth
  for (int i0 = 0; i0 < UPPER_BOUND; i0 += STEP)
  {
    y[i0] += A[i0] * x[i0];
  }
#pragma endmacveth
}
#elif defined(LOOP2D)
void vpack(double *restrict A, double *restrict x, double *restrict y)
{
  int i, j;
#pragma macveth
  for (j = 0; j < UPPER_BOUND_J; j += STEP_J)
  {
    for (i = 0; i < UPPER_BOUND_I; i += STEP_I)
    {
      y[i + 2 * j + C_Y] += A[C_A + j * N + i] * x[2 * i + 3 * j + C_X];
    }
  }
#pragma endmacveth
}
#endif

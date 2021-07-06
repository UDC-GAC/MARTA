#include "codelet_2.h"

/* kernel_spmv_fragment_0 GL7d10-d1compr.spf.c */

#define restrict __restrict

void codelet(double *restrict A, double *restrict x, double *restrict y)
{
  register int i0, i1, i2, i3, i4, i5, i6;

#pragma macveth unroll i0 full
  for (i0 = 0; i0 <= 1; ++i0)
  {
    y[0 * i0 + 0] += A[i0 + 0] * x[2 * i0 + 42];
  }
  for (i0 = 0; i0 <= 1; ++i0)
  {
    y[0 * i0 + 0] += A[i0 + 2] * x[2 * i0 + 57];
  }
  for (i0 = 0; i0 <= 1; ++i0)
  {
    y[0 * i0 + 0] += A[i0 + 4] * x[4 * i0 + 47];
  }
#pragma endmacveth
}

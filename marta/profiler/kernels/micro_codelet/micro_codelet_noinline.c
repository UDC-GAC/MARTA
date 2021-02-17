#include "micro_codelet.h"

#define restrict __restrict

#ifndef MICRO_CODELET_FILE_NAME
#define MICRO_CODELET_FILE_NAME "patterns/codelet_00000001.c"
#endif

#ifndef ORIG_A
#define ORIG_A 0
#endif

#ifndef ORIG_x
#define ORIG_x 0
#endif

#ifndef ORIG_y
#define ORIG_y 0
#endif

#if defined(INTEL_COMPILER)
#define INLINE_PREFIX __forceinline
#else
#define INLINE_PREFIX inline
#endif

void codelet(double *restrict A, double *restrict x, double *restrict y)
{
  register int i, j;

#pragma macveth 
for (i = 0; i <= 36; ++i) {
    for (j = 0; j <=7; ++j) {
        y[8*i + 1*j + ORIG_y] += A[8*i + j + ORIG_A] * x[8*i + 1 + ORIG_x];
     }
}
#pragma endmacveth
}
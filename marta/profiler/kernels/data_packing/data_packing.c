#include "data_packing.h"

#define restrict __restrict

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

INLINE_PREFIX void data_packing(double *restrict A, double *restrict x, double *restrict y)
{
  register int i, j;

  

}

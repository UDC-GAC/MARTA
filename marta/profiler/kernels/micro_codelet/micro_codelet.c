#include "micro_codelet.h"

#define restrict __restrict

#ifndef MICRO_CODELET_FILE_NAME
#define MICRO_CODELET_FILE_NAME "patterns/codelet_00000000.c"
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

INLINE_PREFIX void codelet(double *restrict A, double *restrict x, double *restrict y)
{
  register int i, j;
#ifdef MACVETH
#pragma macveth 
#endif
#include MICRO_CODELET_FILE_NAME
#ifdef MACVETH
#pragma endmacveth
#endif
}

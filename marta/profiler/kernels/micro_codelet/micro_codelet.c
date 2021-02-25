#include "micro_codelet.h"

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
#include TO_STRING(MICRO_CODELET_SRC)
#ifdef MACVETH
#pragma endmacveth
#endif
}

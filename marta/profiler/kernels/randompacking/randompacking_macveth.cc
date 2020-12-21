/* begin INFO MACVETH: headers added */
#include <immintrin.h>
/* end INFO MACVETH */
#include "randompacking.h"

#define restrict __restrict

void vpack(double *restrict A, double *restrict x, double *restrict y) {
#pragma macveth
  __m128d __mv_vop2, __mv_vop0, __mv_vop1, __mv_accm0, __mv_vop3, __mv_lo,
      __mv_hi;
  __mv_accm0 = _mm_setzero_pd();
  __mv_vop0 = _mm_loadu_pd(&A[4]);
  __mv_vop1 = _mm_loadu_pd(&x[0]);
  __mv_accm0 = _mm_fmadd_pd(__mv_vop0, __mv_vop1, __mv_accm0);
  // y[5] += A[4] * x[X_0];
  __mv_hi = _mm_shuffle_pd(__mv_accm0, __mv_accm0, 0x1);
  __mv_accm0 = _mm_add_pd(__mv_accm0, __mv_hi);
  y[5] = y[5] + __mv_accm0[0];
  // y[5] += A[5] * x[X_1];
#if NPACK >= 3
  y[5] += A[6] * x[X_2];
#endif
#if NPACK >= 4
  y[5] += A[7] * x[X_3];
#endif
#pragma endmacveth
}

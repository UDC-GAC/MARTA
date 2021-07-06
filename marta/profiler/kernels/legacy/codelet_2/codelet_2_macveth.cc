/* begin INFO MACVETH: headers added */
#include <immintrin.h>
/* end INFO MACVETH */
#include "codelet_2.h"

/* kernel_spmv_fragment_0 GL7d10-d1compr.spf.c */

#define restrict __restrict

void codelet(double *restrict A, double *restrict x, double *restrict y) {
  register int i0, i1, i2, i3, i4, i5, i6;

#pragma macveth unroll i0 full
  __m128d __mv_vop2, __mv_vop0, __mv_vop1, __mv_accm0, __mv_vop9, __mv_vop5,
      __mv_vop3, __mv_vop4, __mv_vop8, __mv_vop6, __mv_vop7, __mv_lo, __mv_hi;
  __mv_accm0 = _mm_setzero_pd();
  for (i0 = 0; i0 <= 1; i0 += 2) {
    __mv_vop0 = _mm_loadu_pd(&A[(i0 + 0)]);
    __mv_vop1 =
        _mm_i64gather_pd(&x[((2 * (i0 + 0)) + 42)], _mm_set_epi64x(2, 0), 8);
    __mv_accm0 = _mm_fmadd_pd(__mv_vop0, __mv_vop1, __mv_accm0);
    // y[0 * i0 + 0] += A[i0 + 0] * x[2 * i0 + 42];
  }
  __mv_hi = _mm_shuffle_pd(__mv_accm0, __mv_accm0, 0x1);
  __mv_accm0 = _mm_add_pd(__mv_accm0, __mv_hi);
  y[0] = y[0] + __mv_accm0[0];

  __mv_accm0 = _mm_setzero_pd();
  for (i0 = 0; i0 <= 1; i0 += 2) {
    __mv_vop3 = _mm_loadu_pd(&A[((i0 + 0) + 2)]);
    __mv_vop4 =
        _mm_i64gather_pd(&x[((2 * (i0 + 0)) + 57)], _mm_set_epi64x(2, 0), 8);
    __mv_accm0 = _mm_fmadd_pd(__mv_vop3, __mv_vop4, __mv_accm0);
    // y[0 * i0 + 0] += A[i0 + 2] * x[2 * i0 + 57];
  }
  __mv_hi = _mm_shuffle_pd(__mv_accm0, __mv_accm0, 0x1);
  __mv_accm0 = _mm_add_pd(__mv_accm0, __mv_hi);
  y[0] = y[0] + __mv_accm0[0];

  __mv_accm0 = _mm_setzero_pd();
  for (i0 = 0; i0 <= 1; i0 += 2) {
    __mv_vop6 = _mm_loadu_pd(&A[((i0 + 0) + 4)]);
    __mv_vop7 =
        _mm_i64gather_pd(&x[((4 * (i0 + 0)) + 47)], _mm_set_epi64x(4, 0), 8);
    __mv_accm0 = _mm_fmadd_pd(__mv_vop6, __mv_vop7, __mv_accm0);
    // y[0 * i0 + 0] += A[i0 + 4] * x[4 * i0 + 47];
  }
  __mv_hi = _mm_shuffle_pd(__mv_accm0, __mv_accm0, 0x1);
  __mv_accm0 = _mm_add_pd(__mv_accm0, __mv_hi);
  y[0] = y[0] + __mv_accm0[0];

#pragma endmacveth
}

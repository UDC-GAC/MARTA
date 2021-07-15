/* begin INFO MACVETH: headers added */
#include <immintrin.h>
/* end INFO MACVETH */
#include "randompacking.h"

#define restrict __restrict

#ifdef NOLOOP
void vpack(double *restrict A, double *restrict x, double *restrict y) {
#pragma macveth
  __m256d __mv_vop2, __mv_vop0, __mv_vop1, __mv_accm0, __mv_vop3;
  __m128d __mv_lo256, __mv_hi256;
  __mv_accm0 = _mm256_setzero_pd();
  __mv_vop0 = _mm256_loadu_pd(&A[4]);
  __mv_vop1 = _mm256_loadu_pd(&x[4]);
  __mv_accm0 = _mm256_fmadd_pd(__mv_vop0, __mv_vop1, __mv_accm0);
  // y[5] += A[4] * x[X_0];
  __mv_lo256 = _mm256_castpd256_pd128(__mv_accm0);
  __mv_hi256 = _mm256_extractf128_pd(__mv_accm0, 0x1);
  __mv_lo256 = _mm_add_pd(__mv_lo256, __mv_hi256);
  __mv_hi256 = _mm_shuffle_pd(__mv_lo256, __mv_lo256, 0x1);
  __mv_lo256 = _mm_add_pd(__mv_lo256, __mv_hi256);
  y[5] = y[5] + __mv_lo256[0];
  // y[5] += A[5] * x[X_1];
#if NPACK >= 3
  // y[5] += A[6] * x[X_2];
#endif
#if NPACK >= 4
  // y[5] += A[7] * x[X_3];
#endif
#pragma endmacveth
}
#elif defined(LOOP1D)
void vpack(double *restrict A, double *restrict x, double *restrict y) {
#pragma macveth
  for (int i0 = 0; i0 < UPPER_BOUND; i0 += STEP) {
    y[i0] += A[i0] * x[i0];
  }
#pragma endmacveth
}
#elif defined(LOOP2D)
void vpack(double *restrict A, double *restrict x, double *restrict y) {
  int i, j;
#pragma macveth
  for (j = 0; j < UPPER_BOUND_J; j += STEP_J) {
    for (i = 0; i < UPPER_BOUND_I; i += STEP_I) {
      y[i + 2 * j + C_Y] += A[C_A + j * N + i] * x[2 * i + 3 * j + C_X];
    }
  }
#pragma endmacveth
}
#endif

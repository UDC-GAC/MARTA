/* begin INFO MACVETH: headers added */
#include <immintrin.h>
/* end INFO MACVETH */
#ifndef DATA_TYPE
#define DATA_TYPE float
#endif

#ifndef INLINE_PREFIX
#define INLINE_PREFIX __attribute__((always_inline)) inline
#endif

INLINE_PREFIX void codelet_spf(DATA_TYPE *restrict A, DATA_TYPE *restrict x,
                               DATA_TYPE *restrict y) {

  register int i, j;
  // for (i = 0; i <= 16579; ++i) {
#if defined(SCATTER_Y_0)
// LINE 5548
#pragma macveth unroll i 1 j 4
  for (i = 0; i <= 158; ++i) {
    for (j = 0; j <= 3; ++j) {
      y[8 * i + 2 * j + 851048] +=
          A[4 * i + j + 2632330] * x[8 * i + 0 * j + 5756];
    }
  }
  for (i = 0; i <= 158; ++i) {
    for (j = 0; j <= 3; ++j) {
      y[8 * i + 2 * j + 851681] +=
          A[4 * i + j + 2632966] * x[8 * i + 0 * j + 6389];
    }
  }
#pragma endmacveth
#elif defined(SCATTER_Y_1)
// LINE 5548
#pragma macveth unroll i 2 j 4
  for (i = 0; i <= 158; ++i) {
    for (j = 0; j <= 3; ++j) {
      y[8 * i + 2 * j + 851048] +=
          A[4 * i + j + 2632330] * x[8 * i + 0 * j + 5756];
    }
  }
#pragma endmacveth
#elif defined(ONE_REDUCTION_Y)
#pragma macveth unroll i 4
  __m256 __mv_vop2, __mv_vop0, __mv_vop1, __mv_accm0, __mv_vop3;
  __m128 __mv_lo256, __mv_hi256;
  __mv_accm0 = _mm256_setzero_ps();
  for (i = 0; (i + 4) <= 4; i += 4) {
    __mv_vop0 = _mm256_loadu_ps(&A[((i + 0) + 2083151)]);
    __mv_vop1 = _mm256_i32gather_ps(
        &x[((i + 0) + 27429)],
        _mm256_set_epi32(10557, 10556, 10555, 10554, 3, 2, 1, 0), 4);
    __mv_accm0 = _mm256_fmadd_ps(__mv_vop0, __mv_vop1, __mv_accm0);
    /* y[0 * i + 1] += A[i + 2083151] * x[1 * i + 27429];*/
    /* y[0 * i + 1] += A[i + 2083155] * x[1 * i + 37983];*/
  }
  __mv_lo256 = _mm256_castps256_ps128(__mv_accm0);
  __mv_hi256 = _mm256_extractf128_ps(__mv_accm0, 0x1);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  __mv_hi256 = _mm_movehl_ps(__mv_lo256, __mv_lo256);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  __mv_hi256 = _mm_shuffle_ps(__mv_lo256, __mv_lo256, 0b00001110);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  y[1] = y[1] + __mv_lo256[0];


  // for (i = 0; i <= 3; ++i) {
  //   y[0 * i + 1] += A[i + 2083155] * x[1 * i + 37983];
  // }
#pragma endmacveth
#endif
}

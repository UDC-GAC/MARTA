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
#pragma macveth unroll i 1 j 4
  __m256 __mv_vop2, __mv_vop0, __mv_vop1, __mv_vop3;
  for (i = 0; (i + 1) <= 159; i += 1) {
    for (j = 0; (j + 4) <= 4; j += 4) {
      __mv_vop3 = _mm256_i32gather_ps(
          &y[8 * i + 2 * j + 851048],
          _mm256_set_epi32(639, 637, 635, 633, 6, 4, 2, 0), 4);
      __mv_vop0 = _mm256_set_m128(_mm_loadu_ps(&A[4 * i + j + 2632330 + 636]),
                                  _mm_loadu_ps(&A[4 * i + j + 2632330]));
      __mv_vop1 = _mm256_set_ps(
          x[8 * i + 6389], x[8 * i + 6389], x[8 * i + 6389], x[8 * i + 6389],
          x[8 * i + 5756], x[8 * i + 5756], x[8 * i + 5756], x[8 * i + 5756]);
      __mv_vop3 = _mm256_fmadd_ps(__mv_vop0, __mv_vop1, __mv_vop3);
      y[(((8 * i) + (2 * (j + 0))) + 851048)] = __mv_vop3[0];
      y[(((8 * i) + (2 * (j + 1))) + 851048)] = __mv_vop3[1];
      y[(((8 * i) + (2 * (j + 2))) + 851048)] = __mv_vop3[2];
      y[(((8 * i) + (2 * (j + 3))) + 851048)] = __mv_vop3[3];
      y[(((8 * i) + (2 * (j + 0))) + 851681)] = __mv_vop3[4];
      y[(((8 * i) + (2 * (j + 1))) + 851681)] = __mv_vop3[5];
      y[(((8 * i) + (2 * (j + 2))) + 851681)] = __mv_vop3[6];
      y[(((8 * i) + (2 * (j + 3))) + 851681)] = __mv_vop3[7];
      // _mm256_i32scatter_ps(&y[8 * i + 2 * j + 851048],
      //                      _mm256_set_epi32(641, 637, 635, 633, 8, 4, 2, 0),
      //                      __mv_vop3, 4);

      /* y[8 * i + 2 * j + 851048] +=
          A[4 * i + j + 2632330] * x[8 * i + 0 * j + 5756];*/
      /* y[8 * i + 2 * j + 851681] +=
          A[4 * i + j + 2632966] * x[8 * i + 0 * j + 6389];*/
    }
  }

#pragma endmacveth
}

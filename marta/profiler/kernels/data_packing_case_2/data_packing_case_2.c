#include "data_packing_case_2.h"
#include <immintrin.h>

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

//#define SIMD_CODE

INLINE_PREFIX void data_packing_case_2(DATA_TYPE *restrict A, DATA_TYPE *restrict x, DATA_TYPE *restrict y)
{
    int I = 0;
    int J = 0;
    int I_sz=2;
    int J_sz=2;
    int I_Str=1;
    int J_Str=1;
    int Ya=1;
    int Aa=1;
    int Xa=1;
    int Yb=0;
    int Ab=0;
    int Xb=0;
    int i,j;
#ifndef SIMD_CODE
    for (i = I; i < I + I_sz; i += I_Str) {
        for (j = J; j < J + J_sz; j += J_Str) {
            y[Ya * i + Yb * j + ORIG_y] += A[Aa * i + Ab * j + ORIG_A] *
                                    x[Xa * i + Xb * j + ORIG_x];
        }
    }
    I=42;
    J=42;
    Ya=42;
    Aa=42;
    Xa=42;
    Yb=3;
    Ab=3;
    Xb=3;
    for (i = I; i < I + I_sz; i += I_Str) {
        for (j = J; j < J + J_sz; j += J_Str) {
            y[Ya * i + Yb * j + ORIG_y] += A[Aa * i + Ab * j + ORIG_A] *
                                    x[Xa * i + Xb * j + ORIG_x];
        }
    }
#else
#ifdef VERSION_NAIVE
    __m256 __mv_vop0, __mv_vop1, __mv_vop2;


    __mv_vop0 =
        _mm256_set_ps(A[1809+ORIG_A], A[1806+ORIG_A], A[1767+ORIG_A], A[1764+ORIG_A], A[1+ORIG_A], A[1+ORIG_A], A[0+ORIG_A], A[0+ORIG_A]);
    __mv_vop1 =
        _mm256_set_ps(x[1809+ORIG_x], x[1806+ORIG_x], x[1767+ORIG_x], x[1764+ORIG_x], x[1+ORIG_x], x[1+ORIG_x], x[0+ORIG_x], x[0+ORIG_x]);
    __mv_vop2 =
        _mm256_set_ps(y[1809+ORIG_y], y[1806+ORIG_y], y[1767+ORIG_y], y[1764+ORIG_y], y[1+ORIG_y], y[1+ORIG_y], y[0+ORIG_y], y[0+ORIG_y]);

    __mv_vop2 = _mm256_fmadd_ps(__mv_vop0, __mv_vop1, __mv_vop2);
    //_mm256_storeu_ps(&y[0],__mv_vop2);
    y[0] = __mv_vop2[0]+__mv_vop2[1];
    y[1] = __mv_vop2[2]+__mv_vop2[3];
    y[1764+ORIG_y] = __mv_vop2[4];
    y[1767+ORIG_y] = __mv_vop2[5];
    y[1806+ORIG_y] = __mv_vop2[6];
    y[1809+ORIG_y] = __mv_vop2[7];
#endif

    // y[0] = y[0] + A[0] * x[0]
    // y[0] = y[0] + A[0] * x[0]
    // y[1] = y[1] + A[1] * x[1]
    // y[1] = y[1] + A[1] * x[1]
    // y[1764] = y[1764] + A[1764] * x[1764]
    // y[1767] = y[1767] + A[1767] * x[1767]    
    // y[1806] = y[1806] + A[1806] * x[1806]
    // y[1809] = y[1809] + A[1809] * x[1809]

    // y[0] = A[0] * x[0] + y[0] + A[0] * x[0]
    // y[1] = A[1] * x[1] + y[1] + A[1] * x[1]
    i = 0;
    j = 0;
  __m128 __mv_vop2, __mv_vop0, __mv_vop1, __mv_accm0, __mv_vop7, __mv_vop5,
      __mv_vop3, __mv_vop4, __mv_vop6, __mv_lo, __mv_hi;
          __mv_vop0 = _mm_set_ps(A[(i + 1)], A[(i + 1)], A[(i + 0)], A[(i + 0)]);
      __mv_vop1 = _mm_set_ps(x[(i + 1)], x[(i + 1)], x[(i + 0)], x[(i + 0)]);
      __mv_accm0 = _mm_fmadd_ps(__mv_vop0, __mv_vop1, __mv_accm0);
      /* y[i + ORIG_y] += A[i + ORIG_A] * x[i + ORIG_x];*/
      __mv_vop3 = _mm_i32gather_ps(&A[1764],
                                   _mm_set_epi32(45, 42, 3, 0),4);
      __mv_vop4 = _mm_i32gather_ps(&x[1764],
                                   _mm_set_epi32(45, 42, 3, 0), 4);
      __mv_vop6 = _mm_i32gather_ps(&y[1764],
                                   _mm_set_epi32(45, 42, 3, 0), 4);
      __mv_vop6 = _mm_fmadd_ps(__mv_vop3, __mv_vop4, __mv_vop6);
      y[1764] = __mv_vop6[0];
      y[1767] = __mv_vop6[1];
      y[1806] = __mv_vop6[2];
      y[1809] = __mv_vop6[3];
    __mv_hi = _mm_movehl_ps(__mv_accm0, __mv_accm0);
    __mv_accm0 = _mm_add_ps(__mv_accm0, __mv_hi);
    __mv_hi = _mm_shuffle_ps(__mv_accm0, __mv_accm0, 0b00001110);
    __mv_accm0 = _mm_add_ps(__mv_accm0, __mv_hi);
    y[(i + 0)] = y[(i + 0)] + __mv_accm0[0];

#endif
  

}

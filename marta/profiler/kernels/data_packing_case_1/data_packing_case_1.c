#include "data_packing_case_1.h"
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

INLINE_PREFIX void data_packing_case_1(DATA_TYPE *restrict A, DATA_TYPE *restrict x,
                    DATA_TYPE *restrict y, 
                    int I0, int J0, int I_sz0, int J_sz0, int I_Str0, int J_Str0, int Ya0, int Aa0, int Xa0, int Yb0, int Ab0, int Xb0,
                    int I1, int J1, int I_sz1, int J_sz1, int I_Str1, int J_Str1, int Ya1, int Aa1, int Xa1, int Yb1, int Ab1, int Xb1
                    ) {
  int i, j;
#ifndef SIMD_CODE
  for (i = I0; i < I0 + I_sz0; i += I_Str0) {
    for (j = J0; j < J0 + J_sz0; j += J_Str0) {
      y[Ya0 * i + Yb0 * j +  ORIG_y] += A[Aa0 * i + Ab0 * j +  ORIG_A] * x[Xa0 * i + Xb0 * j + ORIG_x];
    }
  }
  // for (i = I1; i < I1 + I_sz1; i += I_Str1) {
  //   for (j = J1; j < J1 + J_sz1; j += J_Str1) {
  //     y[Ya1 * i + Yb1 * j +  ORIG_y] += A[Aa1 * i + Ab1 * j +  ORIG_A] * x[Xa1 * i + Xb1 * j + ORIG_x];
  //   }
  // }
  for (i = I1; i < I1 + I_sz0; i += I_Str0) {
     for (j = J1; j < J1 + J_sz0; j += J_Str0) {
       y[Ya0 * i + Yb0 * j +  ORIG_y] += A[Aa0 * i + Ab0 * j +  ORIG_A] * x[Xa0 * i + Xb0 * j + ORIG_x];
     }
  }
#else
// CSR model
// This code is for fusing two codelets with the same number of iterations,
// basically


#endif
}

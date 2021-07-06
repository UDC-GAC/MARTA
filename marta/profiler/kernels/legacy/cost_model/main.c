/*
 * File			: tests/perftest/randompacking/randompacking.cc
 * Author       : Marcos Horro
 * Date		    : Fri 13 Nov 2020 10:27 +01:00
 *
 * Last Modified : Fri 13 Nov 2020 10:38 +01:00
 * Modified By	 : Marcos Horro (marcos.horro@udc.gal>)
 *
 * MIT License
 *
 * Copyright (c) 2020 Colorado State University
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define DATA_TYPE_IS_FLOAT

#include "marta_wrapper.h"
#include <immintrin.h>

#if defined(FULL_128BITS) || defined(FULL_256BITS)
#include "cost_model.c"
#else
#include "cost_model_1vec.c"
//#include "cost_model_gather.c"
#endif

INLINE_PREFIX void no_simd_kernel(DATA_TYPE *restrict y, DATA_TYPE *restrict A,
                                  DATA_TYPE *restrict x) {
  y[Y_IDX_A] = y[Y_IDX_A] + A[A_IDX_A] * x[X_IDX_A];
#if X_N >= 2
  y[Y_IDX_B] = y[Y_IDX_B] + A[A_IDX_B] * x[X_IDX_B];
#endif
#if X_N >= 3
  y[Y_IDX_C] = y[Y_IDX_C] + A[A_IDX_C] * x[X_IDX_C];
#endif
#if X_N >= 4
  y[Y_IDX_D] = y[Y_IDX_D] + A[A_IDX_D] * x[X_IDX_D];
#endif
#if X_N >= 5
  y[Y_IDX_E] = y[Y_IDX_E] + A[A_IDX_E] * x[X_IDX_E];
#endif
#if X_N >= 6
  y[Y_IDX_F] = y[Y_IDX_F] + A[A_IDX_F] * x[X_IDX_F];
#endif
#if X_N >= 7
  y[Y_IDX_G] = y[Y_IDX_G] + A[A_IDX_G] * x[X_IDX_G];
#endif
#if X_N >= 8
  y[Y_IDX_H] = y[Y_IDX_H] + A[A_IDX_H] * x[X_IDX_H];
#endif
}

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);

int TSTEPS = NRUNS;

#ifdef MARTA_PARAMETRIC_LOOP
if (argc > 1) {
  TSTEPS = atoi(argv[1]);
}
#endif

// Initialization section
POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(y, DATA_TYPE, N, n);

init_1darray(n, POLYBENCH_ARRAY(A));
init_1darray(n, POLYBENCH_ARRAY(x));
init_1darray(n, POLYBENCH_ARRAY(y));

#ifdef THREE_VECTOR
__m128 tmp0, tmp1, tmp2;
#elif defined(FUSED_OP) || (defined(GATHER_EXP) && defined(B256))
__m256 tmp;
#else
__m128 tmp, tmp0, tmp1, tmp2, fma0;
__m256 tmp256, fma256, tmp2560, tmp2561, tmp2562;
#endif

polybench_start_instruments;
#pragma nounroll_and_jam
for (int t = 0; t < TSTEPS; ++t) {
#ifdef THREE_VECTOR
  DO_NOT_TOUCH(x);
  DO_NOT_TOUCH_WRITE(tmp0);
  DO_NOT_TOUCH(A);
  DO_NOT_TOUCH_WRITE(tmp1);
  DO_NOT_TOUCH(y);
  DO_NOT_TOUCH_WRITE(tmp2);
  tmp0 = cost_model_x(POLYBENCH_ARRAY(x));
  tmp1 = cost_model_A(POLYBENCH_ARRAY(A));
  tmp2 = cost_model_y(POLYBENCH_ARRAY(y));
#elif defined(FUSED_OP)
  DO_NOT_TOUCH(x);
  DO_NOT_TOUCH(A);
  DO_NOT_TOUCH(y);
  DO_NOT_TOUCH_WRITE(tmp);
  tmp = cost_model_fused(POLYBENCH_ARRAY(x));
  __m256 vA = _mm256_loadu_ps(&POLYBENCH_ARRAY(A)[0]);
  __m256 vy = _mm256_loadu_ps(&POLYBENCH_ARRAY(y)[0]);
  __m256 fma = _mm256_fmadd_ps(tmp, vA, vy);
  _mm256_storeu_ps(&POLYBENCH_ARRAY(y)[0], fma);
#elif AUTO_VEC == 1
  // DO_NOT_TOUCH(POLYBENCH_ARRAY(x));
  // DO_NOT_TOUCH(POLYBENCH_ARRAY(A));
  // DO_NOT_TOUCH_WRITE(y);
  no_simd_kernel(POLYBENCH_ARRAY(y), POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(x));
#elif defined(ONLY_PACKING_4OPS)
  DO_NOT_TOUCH(x);
  DO_NOT_TOUCH_WRITE(tmp);
  tmp = cost_model_x(POLYBENCH_ARRAY(x));
#elif defined(ONLY_PACKING_8OPS)
  DO_NOT_TOUCH(x);
  DO_NOT_TOUCH_WRITE(tmp256);
  tmp256 = cost_model_8ops(POLYBENCH_ARRAY(x));
#elif defined(ONLY_ONE_128BITS)
  DO_NOT_TOUCH(x);
  DO_NOT_TOUCH(A);
  DO_NOT_TOUCH(y);
  DO_NOT_TOUCH_WRITE(tmp0);
  tmp0 = cost_model_x_low(POLYBENCH_ARRAY(x));
  __m128 vA0 = _mm_loadu_ps(&POLYBENCH_ARRAY(A)[0]);
  __m128 vy0 = _mm_loadu_ps(&POLYBENCH_ARRAY(y)[0]);
  __m128 fma0 = _mm_fmadd_ps(tmp0, vA0, vy0);
  _mm_storeu_ps(&POLYBENCH_ARRAY(y)[0], fma0);
#elif defined(FULL_128BITS)
  DO_NOT_TOUCH(x);
  DO_NOT_TOUCH(A);
  DO_NOT_TOUCH_WRITE(y);
  tmp0 = vpack_x(POLYBENCH_ARRAY(x));
  tmp1 = vpack_A(POLYBENCH_ARRAY(A));
  tmp2 = vpack_y(POLYBENCH_ARRAY(y));
  fma0 = _mm_fmadd_ps(tmp0, tmp1, tmp2);
  vstore_y(fma0, POLYBENCH_ARRAY(y));
#elif defined(FULL_256BITS)
  DO_NOT_TOUCH(x);
  DO_NOT_TOUCH(A);
  DO_NOT_TOUCH_WRITE(y);
  tmp2560 = vpack_x_256(POLYBENCH_ARRAY(x));
  tmp2561 = vpack_A_256(POLYBENCH_ARRAY(A));
  tmp2562 = vpack_y_256(POLYBENCH_ARRAY(y));
  // #if ((Y_N == 8) && (Y_IDX_A != Y_IDX_B) && (Y_IDX_C != Y_IDX_D) &&             \
//      (Y_IDX_E != Y_IDX_F) && (Y_IDX_G != Y_IDX_H)) ||                          \
//     ((Y_N == 7) && (Y_IDX_A != Y_IDX_B) && (Y_IDX_C != Y_IDX_D) &&             \
//      (Y_IDX_E != Y_IDX_F)) ||                                                  \
//     ((Y_N == 6) && (Y_IDX_A != Y_IDX_B) && (Y_IDX_C != Y_IDX_D) &&             \
//      (Y_IDX_E != Y_IDX_F)) ||                                                  \
//     ((Y_N == 5) && (Y_IDX_A != Y_IDX_B) && (Y_IDX_C != Y_IDX_D))
  fma256 = _mm256_fmadd_ps(tmp2560, tmp2561, tmp2562);
  // #else
  //   // fma256 = _mm256_fmadd_ps(tmp2560, tmp2561, tmp2562);
  //   fma256 = _mm256_mul_ps(tmp2560, tmp2561);
  //#endif
  vstore_y_256(fma256, POLYBENCH_ARRAY(y));
#elif defined(GATHER_EXP)
  DO_NOT_TOUCH(x);
  DO_NOT_TOUCH_WRITE(tmp);
  tmp = cost_model_gather(POLYBENCH_ARRAY(x));
#else
  DO_NOT_TOUCH(x);
  DO_NOT_TOUCH(A);
  DO_NOT_TOUCH_WRITE(y);
  DO_NOT_TOUCH_WRITE(tmp0);
  DO_NOT_TOUCH_WRITE(tmp1);
  tmp0 = cost_model_x_low(POLYBENCH_ARRAY(x));
  __m128 vA0 = _mm_loadu_ps(&POLYBENCH_ARRAY(A)[0]);
  __m128 vy0 = _mm_loadu_ps(&POLYBENCH_ARRAY(y)[0]);
  __m128 fma0 = _mm_fmadd_ps(tmp0, vA0, vy0);
  _mm_storeu_ps(&POLYBENCH_ARRAY(y)[0], fma0);
  tmp1 = cost_model_x_high(POLYBENCH_ARRAY(x));
  __m128 vA1 = _mm_loadu_ps(&POLYBENCH_ARRAY(A)[4]);
  __m128 vy1 = _mm_loadu_ps(&POLYBENCH_ARRAY(y)[4]);
  __m128 fma1 = _mm_fmadd_ps(tmp1, vA1, vy1);
  _mm_storeu_ps(&POLYBENCH_ARRAY(y)[4], fma1);
#endif
  CLOBBER_MEMORY;
}
polybench_stop_instruments;
polybench_print_instruments;

if (argc >= 42) {
#if AUTO_VEC == 0
#ifndef THREE_VECTOR
  printf("tmp %f", tmp[2]);
  printf("tmp %f", tmp[1]);
  printf("tmp %f", tmp[3]);
#else
  printf("tmp %f", tmp0[2]);
  printf("tmp %f", tmp1[0]);
  printf("tmp %f", tmp2[3]);
  printf("tmp %f", y[3]);
  printf("tmp %f", y[0]);
#endif
#else
  printf("tmp %f", y[0]);
#endif
}

// Avoid DCE section
polybench_prevent_dce(print_array1d(4, POLYBENCH_ARRAY(y)));

MARTA_BENCHMARK_END;

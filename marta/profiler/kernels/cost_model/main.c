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

#ifdef FULL_128BITS
#include "cost_model_all.c"
#else
#include "cost_model_1vec.c"
#endif

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
#elif defined(FUSED_OP)
__m256 tmp;
#else
__m128 tmp, tmp0, tmp1, tmp2, fma0;
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
#elif defined(NO_SIMD)
  DO_NOT_TOUCH(x);
  DO_NOT_TOUCH(A);
  DO_NOT_TOUCH(y);
  POLYBENCH_ARRAY(y)
  [0] += POLYBENCH_ARRAY(A)[0] * POLYBENCH_ARRAY(x)[X0_ORIG + X0_IDX_A];
  POLYBENCH_ARRAY(y)
  [1] += POLYBENCH_ARRAY(A)[1] * POLYBENCH_ARRAY(x)[X0_ORIG + X0_IDX_B];
  POLYBENCH_ARRAY(y)
  [2] += POLYBENCH_ARRAY(A)[2] * POLYBENCH_ARRAY(x)[X0_ORIG + X0_IDX_C];
  POLYBENCH_ARRAY(y)
  [3] += POLYBENCH_ARRAY(A)[3] * POLYBENCH_ARRAY(x)[X0_ORIG + X0_IDX_D];
  POLYBENCH_ARRAY(y)
  [4] += POLYBENCH_ARRAY(A)[4] * POLYBENCH_ARRAY(x)[X1_ORIG + X1_IDX_A];
  POLYBENCH_ARRAY(y)
  [5] += POLYBENCH_ARRAY(A)[5] * POLYBENCH_ARRAY(x)[X1_ORIG + X1_IDX_B];
  POLYBENCH_ARRAY(y)
  [6] += POLYBENCH_ARRAY(A)[6] * POLYBENCH_ARRAY(x)[X1_ORIG + X1_IDX_C];
  POLYBENCH_ARRAY(y)
  [7] += POLYBENCH_ARRAY(A)[7] * POLYBENCH_ARRAY(x)[X1_ORIG + X1_IDX_D];
#elif defined(ONLY_PACKING)
  DO_NOT_TOUCH(x);
  DO_NOT_TOUCH_WRITE(tmp);
  tmp = cost_model_x(POLYBENCH_ARRAY(x));
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
}

// Avoid DCE section
polybench_prevent_dce(print_array1d(4, POLYBENCH_ARRAY(y)));

MARTA_BENCHMARK_END;

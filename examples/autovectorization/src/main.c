/**
 * Copyright 2021 Marcos Horro
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "marta_wrapper.h"
#include <immintrin.h>

#ifndef _UB_N
#define _UB_N POLYBENCH_LOOP_BOUND(N, n)
#endif

float kernel_reduction(int n, float *restrict A) {
  float sum = 0.0;
  for (int i = 0; i < _UB_N; ++i)
    for (int j = 0; j < _UB_N; ++j)
      sum += A[i * _UB_N + j];
  return sum;
}

static void autovect(int n, float *restrict x) {
  float sum = 0;
  for (int i = 0; i < _UB_N; ++i) {
    sum += x[i] * 42.0;
  }
  DO_NOT_TOUCH(sum);
}

#ifndef kernel
#define kernel autovect
#endif

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);
int n = N;
POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);
PROFILE_FUNCTION_LOOP(kernel(n, x), TSTEPS);
MARTA_BENCHMARK_END;

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

#if LOOP_BOUND_PARAMETRIC == 0
#define POLYBENCH_USE_SCALAR_LB
#endif

#define DATA_TYPE_IS_FLOAT

#include "marta_wrapper.h"
#include <immintrin.h>

#ifndef N
#define N 1
#endif

#define _UB_N POLYBENCH_LOOP_BOUND(N, n)

#if defined(LOOP_PARTIAL_SLP)
void KERNEL(int n, float POLYBENCH_1D(x, N, n)) {
  float sum = 0;
  sum += x[0] * 42.0f;
  for (int i = 1; i < _UB_N; ++i) {
    sum += x[i] * 42.0f;
  }
  DO_NOT_TOUCH(sum);
}
#elif defined(LOOP_SLP)
void KERNEL(int n, float POLYBENCH_1D(x, N, n)) {
  float sum = 0;
  sum += x[0] * 42.0f;
  for (int i = 1; i < _UB_N; ++i) {
    sum += x[i] * 42.0f;
  }
  sum += x[_UB_N - 1] * 42.0f;
  DO_NOT_TOUCH(sum);
}
#else
void KERNEL(int n, float POLYBENCH_1D(x, N, n)) {
  float sum = 0;
  for (int i = 0; i < _UB_N; ++i) {
    sum += x[i] * 42.0f;
  }
  DO_NOT_TOUCH(sum);
}
#endif

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);
int n = N;
POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);

init_1darray(n, POLYBENCH_ARRAY(x));

PROFILE_FUNCTION_LOOP(KERNEL(n, POLYBENCH_ARRAY(x)), TSTEPS);
MARTA_BENCHMARK_END;

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

#define DATA_TYPE_IS_FLOAT

#include "marta_wrapper.h"
#include <immintrin.h>

#ifndef N
#define N 1
#endif

#ifndef INIT_VAL
#define INIT_VAL 0
#endif

#ifndef LOOP_STEP
#define LOOP_STEP 1
#endif

#ifndef INDEX_FACTOR
#define INDEX_FACTOR 1
#endif

#ifndef LOOP_BOUND_PARAMETRIC
#define LOOP_BOUND_PARAMETRIC 0
#endif

#ifndef INIT_VAL_PARAMETRIC
#define INIT_VAL_PARAMETRIC 0
#endif

#ifndef LOOP_STEP_PARAMETRIC
#define LOOP_STEP_PARAMETRIC 0
#endif

#ifndef INDEX_FACTOR_PARAMETRIC
#define INDEX_FACTOR_PARAMETRIC 0
#endif

#if LOOP_BOUND_PARAMETRIC == 1
#define _UB_N n
#else
#define _UB_N N
#endif

#if INIT_VAL_PARAMETRIC == 1
#define _UB_INIT_VAL init_val
#else
#define _UB_INIT_VAL INIT_VAL
#endif

#if LOOP_STEP_PARAMETRIC == 1
#define _UB_LOOP_STEP loop_step
#else
#define _UB_LOOP_STEP LOOP_STEP
#endif

#if INDEX_FACTOR_PARAMETRIC == 1
#define _UB_INDEX_FACTOR index_factor
#else
#define _UB_INDEX_FACTOR INDEX_FACTOR
#endif

static void
KERNEL(int n, int init_val, int loop_step, int index_factor, DATA_TYPE *y,
       DATA_TYPE POLYBENCH_1D(x, INDEX_FACTOR *N, index_factor *n)) {
  DATA_TYPE sum = 0;
  for (int i = _UB_INIT_VAL; i < _UB_N + _UB_INIT_VAL; i += _UB_LOOP_STEP) {
    sum += x[_UB_INDEX_FACTOR * i] * 42.0f;
  }
  *y = sum;
}

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);
int n = N;
int init_val = INIT_VAL;
int loop_step = INDEX_FACTOR;
int index_factor = INDEX_FACTOR;
DATA_TYPE y = 0.0f;
POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, 32 * INDEX_FACTOR * N,
                        32 * index_factor * n);
init_1darray(32 * index_factor * n, POLYBENCH_ARRAY(x));
PROFILE_FUNCTION_LOOP(KERNEL(n, init_val, loop_step, index_factor, &y,
                             POLYBENCH_ARRAY(x)),
                      TSTEPS);
if (argc > 42) {
  printf("%f\n", y);
}
POLYBENCH_FREE_ARRAY(x);
MARTA_BENCHMARK_END;

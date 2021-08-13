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

#define _UB_N POLYBENCH_LOOP_BOUND(N, n)

static void kernel(int n, float POLYBENCH_2D(A, N, N, n, n),
                   float POLYBENCH_2D(B, N, N, n, n),
                   float POLYBENCH_2D(C, N, N, n, n)) {
  for (int i = 0; i < _UB_N; i++)
    for (int j = 0; j < _UB_N; j++)
      for (int k = 0; k < _UB_N; k++)
        A[i][j] = A[i][j] + B[i][k] * C[k][j];
}

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);
int n = N;
POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);
POLYBENCH_2D_ARRAY_DECL(B, DATA_TYPE, N, N, n, n);
POLYBENCH_2D_ARRAY_DECL(C, DATA_TYPE, N, N, n, n);
PROFILE_FUNCTION_LOOP(kernel(n, POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(B),
                             POLYBENCH_ARRAY(C)),
                      TSTEPS);
MARTA_BENCHMARK_END;

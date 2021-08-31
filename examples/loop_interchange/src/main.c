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

#if LOOP_BOUND_PARAMETRIC == 1
#define POLYBENCH_USE_SCALAR_LB
#endif

#include "marta_wrapper.h"
#include <immintrin.h>

#ifndef L
#define L 1
#endif

#ifndef M
#define M 1
#endif

#ifndef N
#define N 1
#endif

#if !defined(LOOP_2D) && !defined(LOOP_3D) && !defined(REDUCTION)
#define REDUCTION
#endif

#if !defined(ARRAY_DIM)
#define ARRAY_DIM 1
#endif

#define _UB_N POLYBENCH_LOOP_BOUND(N, n)
#define _UB_M POLYBENCH_LOOP_BOUND(M, m)
#define _UB_L POLYBENCH_LOOP_BOUND(L, l)

#ifdef LOOP_3D
static void kernel(int n, int m, int l,
#if ARRAY_DIM == 1
                   DATA_TYPE POLYBENCH_1D(A, N *N, n *n),
                   DATA_TYPE POLYBENCH_1D(B, N *L, n *l),
                   DATA_TYPE POLYBENCH_1D(C, L *M, l *m)
#else
                   DATA_TYPE POLYBENCH_2D(A, N, N, n, n),
                   DATA_TYPE POLYBENCH_2D(B, N, L, n, l),
                   DATA_TYPE POLYBENCH_2D(C, L, M, l, m)
#endif
) {
  for (int i = 0; i < _UB_N; i++)
    for (int j = 0; j < _UB_M; j++)
      for (int k = 0; k < _UB_L; k++)
#if ARRAY_DIM == 2
        A[i][j] = A[i][j] + B[i][k] * C[k][j];
#else
        A[i * _UB_N + j] =
            A[i * _UB_N + j] + B[i * _UB_N + k] * C[k * _UB_L + j];
#endif
}
#elif defined(LOOP_2D)
static void kernel(int n, int m, int l,
#if ARRAY_DIM == 1
                   DATA_TYPE POLYBENCH_1D(A, N *N, n *n),
                   DATA_TYPE POLYBENCH_1D(B, M *N, m *n),
                   DATA_TYPE POLYBENCH_1D(C, M *N, m *n)) {
#else
                   DATA_TYPE POLYBENCH_2D(A, N, N, n, n),
                   DATA_TYPE POLYBENCH_2D(B, M, N, m, n),
                   DATA_TYPE POLYBENCH_2D(C, M, N, m, n)) {
#endif
  for (int i = 0; i < _UB_N; i++)
    for (int j = 0; j < _UB_M; j++)
#if ARRAY_DIM == 2
      A[i][j] = A[i][j] + B[j][i] * C[j][i];
#else
      A[i * _UB_N + j] = A[i * _UB_N + j] + B[j * _UB_M + i] * C[j * _UB_M + i];
#endif
}
#elif defined(REDUCTION)
static void kernel(int n, DATA_TYPE *y,
#if ARRAY_DIM == 1
                   DATA_TYPE POLYBENCH_1D(A, N *N, n *n)) {
#else
                   DATA_TYPE POLYBENCH_2D(A, N, N, n, n)) {
#endif
  DATA_TYPE sum = 0.0f;
  for (int i = 0; i < _UB_N; i++) {
    for (int j = 0; j < _UB_N; j++) {
#if ARRAY_DIM == 1
      sum += A[j * _UB_N + i];
#else
      sum += A[j][i];
#endif
    }
  }
  DO_NOT_TOUCH(sum);
  *y = sum;
}
#endif

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);
int n = N;
int m = M;
int l = L;
#ifdef LOOP_3D
#if ARRAY_DIM == 1
POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N *N, n *n);
POLYBENCH_1D_ARRAY_DECL(B, DATA_TYPE, N *L, m *l);
POLYBENCH_1D_ARRAY_DECL(C, DATA_TYPE, L *M, l *m);
#else
POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);
POLYBENCH_2D_ARRAY_DECL(B, DATA_TYPE, N, L, m, l);
POLYBENCH_2D_ARRAY_DECL(C, DATA_TYPE, L, M, l, m);
#endif
#elif defined(LOOP_2D)
#if ARRAY_DIM == 1
POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N *N, n *n);
POLYBENCH_1D_ARRAY_DECL(B, DATA_TYPE, M *N, m *n);
POLYBENCH_1D_ARRAY_DECL(C, DATA_TYPE, M *N, m *n);
#else
POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);
POLYBENCH_2D_ARRAY_DECL(B, DATA_TYPE, M, N, m, n);
POLYBENCH_2D_ARRAY_DECL(C, DATA_TYPE, M, N, m, n);
#endif
#elif defined(REDUCTION)
DATA_TYPE y = 0.0f;
#if ARRAY_DIM == 1
POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N *N, n *n);
#else
POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);
#endif
#endif

#if ARRAY_DIM == 2
init_2darray(n, POLYBENCH_ARRAY(A));
#else
init_1darray(n, POLYBENCH_ARRAY(A));
#endif

#ifdef REDUCTION
PROFILE_FUNCTION_LOOP(kernel(n, &y, POLYBENCH_ARRAY(A)), TSTEPS);
if (argc > 42) {
  printf("%f\n", y);
}
POLYBENCH_FREE_ARRAY(A);

#else
PROFILE_FUNCTION_LOOP(kernel(n, m, l, POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(B),
                             POLYBENCH_ARRAY(C)),
                      TSTEPS);
POLYBENCH_FREE_ARRAY(A);
POLYBENCH_FREE_ARRAY(B);
POLYBENCH_FREE_ARRAY(C);
#endif
MARTA_BENCHMARK_END;

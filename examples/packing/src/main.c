#ifndef IDX0
#define IDX0 0
#endif

#ifndef IDX1
#define IDX1 1
#endif

#ifndef IDX2
#define IDX2 2
#endif

#ifndef IDX3
#define IDX3 3
#endif

#ifndef IDX4
#define IDX4 4
#endif

#ifndef IDX5
#define IDX5 5
#endif

#ifndef IDX6
#define IDX6 6
#endif

#ifndef IDX7
#define IDX7 7
#endif

#define DATA_TYPE_IS_FLOAT

#if !defined(NO_SIMD) && !defined(INSERTS) && !defined(INSERTS2) &&            \
    !defined(BLENDS)
#define INSERTS
#endif

#include "intrinsics_extension.h"
#include "marta_wrapper.h"
#include <immintrin.h>

void packing(DATA_TYPE *restrict A, DATA_TYPE *restrict y,
             DATA_TYPE *restrict x) {
#pragma unroll 1
  for (int i = 0; i < 1; i += 1) {
#ifdef NO_SIMD
    y[0] += A[0] * x[0];
    y[1] += A[1] * x[4];
    y[2] += A[2] * x[5];
    y[3] += A[3] * x[6];
    y[4] += A[4] * x[9];
    y[5] += A[5] * x[12];
    y[6] += A[6] * x[13];
    y[7] += A[7] * x[14];
#elif defined(INSERTS)
    __m256 vy = _mm256_loadu_ps(y);
    __m256 vA = _mm256_loadu_ps(A);
    __m128 __tmp128_0, __tmp128_1, vx_low, vx_high;
    // x[0:3]
    vx_low = _mm_loadl_pi(vx_low, &x[0]);
    __tmp128_0 = _mm_loadl_pi(vx_low, &x[5]);
    __mv_insertps(vx_low, vx_low, x[4], 1);
    __mv_insertps(__tmp128_0, __tmp128_0, x[6], 1);
    vx_low = _mm_movelh_ps(vx_low, __tmp128_0);
    // x[4:7]
    vx_high = _mm_loadl_pi(vx_high, &x[9]);
    __tmp128_0 = _mm_loadl_pi(vx_high, &x[13]);
    __mv_insertps(vx_high, vx_high, x[10], 1);
    __mv_insertps(__tmp128_0, __tmp128_0, x[14], 1);
    vx_high = _mm_movelh_ps(vx_high, __tmp128_0);
    // merge
    __m256 vx =
        _mm256_insertf128_ps(_mm256_castps128_ps256(vx_low), vx_high, 0x1);
    // fmadd
    __m256 tmp = _mm256_fmadd_ps(vA, vx, vy);
    _mm256_storeu_ps(y, tmp);
#elif defined(INSERTS2)
    __m256 vy = _mm256_loadu_ps(y);
    __m256 vA = _mm256_loadu_ps(A);
    __m128 __tmp128_0, __tmp128_1, vx_low, vx_high;
    // x[0:3]
    vx_low = _mm_loadl_pi(vx_low, &x[0]);
    __mv_insertps(vx_low, vx_low, x[4], 1);
    __mv_insertps(vx_low, vx_low, x[5], 2);
    __mv_insertps(vx_low, vx_low, x[6], 3);
    // x[4:7]
    vx_high = _mm_loadl_pi(vx_high, &x[9]);
    __mv_insertps(vx_high, vx_high, x[12], 1);
    __mv_insertps(vx_high, vx_high, x[13], 2);
    __mv_insertps(vx_high, vx_high, x[14], 3);
    // merge
    __m256 vx =
        _mm256_insertf128_ps(_mm256_castps128_ps256(vx_low), vx_high, 0x1);
    // fmadd
    __m256 tmp = _mm256_fmadd_ps(vA, vx, vy);
    _mm256_storeu_ps(y, tmp);
#elif defined(BLENDS)
    __m256 vy = _mm256_loadu_ps(y);
    __m256 vA = _mm256_loadu_ps(A);
    __m128 __tmp128_0, __tmp128_1, vx_low, vx_high;
    // x[0:3]
    vx_low = _mm_loadl_pi(vx_low, &x[0]);
    vx_high = _mm_loadl_pi(vx_high, &x[9]);
    __mv_blendps(vx_low, vx_low, x[3], 0xe);
    __mv_blendps(vx_high, vx_high, x[11], 0xe);

    // merge
    __m256 vx =
        _mm256_insertf128_ps(_mm256_castps128_ps256(vx_low), vx_high, 0x1);
    // fmadd
    __m256 tmp = _mm256_fmadd_ps(vA, vx, vy);
    _mm256_storeu_ps(y, tmp);
#endif
  }
}

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);
int n = N;
POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(y, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);
PROFILE_FUNCTION_LOOP(packing(POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(y),
                              POLYBENCH_ARRAY(x)),
                      TSTEPS);
if (argc >= 42) {
  print_array1d(n, POLYBENCH_ARRAY(y));
}
MARTA_BENCHMARK_END;

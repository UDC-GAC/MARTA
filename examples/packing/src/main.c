#define DATA_TYPE_IS_FLOAT

#if !defined(NO_SIMD) && !defined(INSERTS) && !defined(INSERTS2) &&            \
    !defined(BLENDS)
#define INSERTS
#endif

#define KERNEL_NAME exercise_macveth

#ifdef KERNEL_CSR
#undef KERNEL_NAME
#define KERNEL_NAME exercise_csr
#endif

#ifdef KERNEL_MV
#undef KERNEL_NAME
#define KERNEL_NAME exercise_macveth
#endif

#ifdef KERNEL_AUTOVEC
#undef KERNEL_NAME
#define KERNEL_NAME exercise
#endif

#define POLYBENCH_NO_FLUSH_CACHE

#ifdef POLYBENCH_CACHE_SIZE_KB
#undef POLYBENCH_CACHE_SIZE_KB
#define POLYBENCH_CACHE_SIZE_KB 100000
#endif

#ifndef OFFSET
#define OFFSET 512 * 1024
#endif

#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>
#include <stdint.h>

int random_indices[TSTEPS];

static inline void exercise_csr(DATA_TYPE *restrict A, DATA_TYPE *restrict y,
                                DATA_TYPE *restrict x, int *col, int *row_ptr,
                                int offset) {
  //#ifdef COLDCACHE
  A = A + offset;
  y = y + offset;
  x = x + offset;
  //#endif
  for (int i = 0; i < 2; ++i) {
    for (int k = row_ptr[i]; k < row_ptr[i + 1]; ++k) {
      y[i + 7685] += A[k + 122985] * x[col[k]];
    }
  }
}

static inline void exercise(DATA_TYPE *restrict A, DATA_TYPE *restrict y,
                            DATA_TYPE *restrict x, int offset,
                            int __marta_tsteps) {
  //#ifdef COLDCACHE
  A = A + offset;
  y = y + offset;
  x = x + offset;
  //#endif
  register int i0;
  for (i0 = 0; i0 <= 1; ++i0) {
    y[0 * i0 + 7685] += A[1 * i0 + 122985] * x[1 * i0 + 7590];
  }
  y[7685] += A[122987] * x[7593];
  y[7685] += A[122988] * x[7604];
  y[7685] += A[122989] * x[7628];
  y[7685] += A[122990] * x[7642];
  for (i0 = 0; i0 <= 1; ++i0) {
    y[0 * i0 + 7685] += A[1 * i0 + 122991] * x[1 * i0 + 7684];
  }
  for (i0 = 0; i0 <= 3; ++i0) {
    y[0 * i0 + 7686] += A[1 * i0 + 122993] * x[1 * i0 + 7217];
  }
  y[7686] += A[122997] * x[7222];
  y[7686] += A[122998] * x[7224];
  y[7686] += A[122999] * x[7229];
  for (i0 = 0; i0 <= 1; ++i0) {
    y[0 * i0 + 7686] += A[1 * i0 + 123000] * x[1 * i0 + 7231];
  }
  y[7686] += A[123002] * x[7235];
  y[7686] += A[123003] * x[7249];
  y[7686] += A[123004] * x[7268];
  for (i0 = 0; i0 <= 2; ++i0) {
    y[0 * i0 + 7686] += A[1 * i0 + 123005] * x[2 * i0 + 7302];
  }
  for (i0 = 0; i0 <= 1; ++i0) {
    y[0 * i0 + 7686] += A[1 * i0 + 123008] * x[1 * i0 + 7343];
  }
  y[7686] += A[123010] * x[7346];
  y[7686] += A[123011] * x[7349];
  for (i0 = 0; i0 <= 1; ++i0) {
    y[0 * i0 + 7686] += A[1 * i0 + 123012] * x[1 * i0 + 7355];
  }
  y[7686] += A[123014] * x[7381];
}

#ifdef SW_PF
#define HINT _MM_HINT_NTA
#ifndef PF_OFFSET
#define PF_OFFSET 1
#endif
#endif

static inline void exercise_macveth(DATA_TYPE *restrict A,
                                    DATA_TYPE *restrict y,
                                    DATA_TYPE *restrict x, int offset,
                                    int __marta_tsteps) {
  //#ifdef COLDCACHE
  A = A + offset;
  y = y + offset;
  x = x + offset;
//#endif
#ifdef SW_PF
  int prefetch_offset = PF_OFFSET;
  if (__marta_tsteps + prefetch_offset < TSTEPS) {
    _mm_prefetch(A - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     112976,
                 HINT); // 107.2
    _mm_prefetch(A - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     122992,
                 HINT);
    _mm_prefetch(A - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     123008,
                 HINT);
    _mm_prefetch(x - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     7216,
                 HINT);
    _mm_prefetch(x - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     7232,
                 HINT);
    _mm_prefetch(x - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     7248,
                 HINT);
    _mm_prefetch(x - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     7264,
                 HINT);
    _mm_prefetch(x - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     7296,
                 HINT);
    _mm_prefetch(x - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     7328,
                 HINT);
    _mm_prefetch(x - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     7344,
                 HINT);
    _mm_prefetch(x - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     7376,
                 HINT);
    _mm_prefetch(x - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     7584,
                 HINT);
    _mm_prefetch(x - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     7600,
                 HINT);
    _mm_prefetch(x - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     7616,
                 HINT);
    _mm_prefetch(x - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     7632,
                 HINT);
    _mm_prefetch(x - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     7680,
                 HINT);
    _mm_prefetch(y - offset + random_indices[__marta_tsteps + prefetch_offset] +
                     7680,
                 HINT);
  }
#endif

  // TOTAL: 17 cache lines (assuming everything is properly aligned, which is,
  // since we are using PolyBench's)
  // Cache lines for A (3):
  // 112976, 112992, 113008
  // Cache lines for x (13):
  // 7584,7600,7616,7632,7680
  // 7216,7232,7248,7264,7296
  // 7328,7344,7376
  // Cache lines for y (1):
  // 7680

  // for (i0 = 0; i0 <= 1; ++i0) {
  //   y[0 * i0 + 7685] += A[1 * i0 + 122985] * x[1 * i0 + 7590];
  // }
  // y[7685] += A[122987] * x[7593];
  // y[7685] += A[122988] * x[7604];
  // y[7685] += A[122989] * x[7628];
  // y[7685] += A[122990] * x[7642];
  // for (i0 = 0; i0 <= 1; ++i0) {
  //   y[0 * i0 + 7685] += A[1 * i0 + 122991] * x[1 * i0 + 7684];
  // }

  __m256 tmp0_256, tmp1_256, tmp2_256, y_0, y_1;
  __m128 tmp0_128, tmp1_128, tmp2_128, vlow, vhigh, shuf, sums;

  tmp0_256 = _mm256_loadu_ps(&A[112985]);
  tmp0_128 = _mm_loadl_pi(tmp0_128, &x[7590]);
  __mv_insertps(tmp0_128, tmp0_128, x[7593], 0x2);
  __mv_insertps(tmp0_128, tmp0_128, x[7604], 0x3);
  tmp1_128 = _mm_loadh_pi(tmp1_128, &x[7684]);
  __mv_insertps(tmp1_128, tmp1_128, x[7628], 0x0);
  __mv_insertps(tmp1_128, tmp1_128, x[7642], 0x1);
  tmp2_256 = _mm256_set_m128(tmp1_128, tmp0_128);
  y_0 = _mm256_mul_ps(tmp0_256, tmp2_256);
#ifndef FUSED
  vlow = _mm256_castps256_ps128(y_0);    // cost 0
  vhigh = _mm256_extractf128_ps(y_0, 1); // high 128
  vlow = _mm_add_ps(vlow, vhigh);        // add the low 128
  shuf = _mm_movehdup_ps(vlow);          // broadcast elements 3,1 to 2,0
  sums = _mm_add_ps(vlow, shuf);
  shuf = _mm_movehl_ps(shuf, sums); // high half -> low half
  sums = _mm_add_ss(sums, shuf);
  y[7685] += _mm_cvtss_f32(sums);
#endif
  // for (i0 = 0; i0 <= 3; ++i0) {
  //   y[0 * i0 + 7686] += A[1 * i0 + 122993] * x[1 * i0 + 7217];
  // }
  // y[7686] += A[122997] * x[7222];
  // y[7686] += A[122998] * x[7224];
  // y[7686] += A[122999] * x[7229];
  // for (i0 = 0; i0 <= 1; ++i0) {
  //   y[0 * i0 + 7686] += A[1 * i0 + 123000] * x[1 * i0 + 7231];
  // }

  tmp0_256 = _mm256_loadu_ps(&A[122993]);
  tmp0_128 = _mm_loadu_ps(&x[7217]);
  tmp1_128 = _mm_load_ss(&x[7222]);
  __mv_insertps(tmp1_128, tmp1_128, x[7224], 1);
  __mv_insertps(tmp1_128, tmp1_128, x[7229], 2);
  __mv_insertps(tmp1_128, tmp1_128, x[7231], 3);
  tmp1_256 = _mm256_set_m128(tmp1_128, tmp0_128);
  tmp0_256 = _mm256_mul_ps(tmp0_256, tmp1_256);

  // y[7686] += A[123001] * x[7232];
  // y[7686] += A[123002] * x[7235];
  // y[7686] += A[123003] * x[7249];
  // y[7686] += A[123004] * x[7268];
  // for (i0 = 0; i0 <= 2; ++i0) {
  //   y[0 * i0 + 7686] += A[1 * i0 + 123005] * x[2 * i0 + 7302];
  // }
  // y[7686] += A[123008] * x[7343];

  tmp1_256 = _mm256_loadu_ps(&A[123001]);
  tmp0_128 = _mm_load_ss(&x[7232]);
  __mv_insertps(tmp0_128, tmp0_128, x[7235], 1);
  __mv_insertps(tmp0_128, tmp0_128, x[7249], 2);
  __mv_insertps(tmp0_128, tmp0_128, x[7268], 3);
  tmp1_128 = _mm_loadu_ps(&x[7302]);
  __mv_insertps(tmp1_128, tmp1_128, x[7343], 3);
  tmp2_256 = _mm256_set_m128(tmp1_128, tmp0_128);
  tmp0_256 = _mm256_fmadd_ps(tmp1_256, tmp2_256, tmp0_256);

  // y[7686] += A[123000] * x[7344];
  // y[7686] += A[123010] * x[7346];
  // y[7686] += A[123011] * x[7349];
  // for (i0 = 0; i0 <= 1; ++i0) {
  //   y[0 * i0 + 7686] += A[1 * i0 + 123012] * x[1 * i0 + 7355];
  // }
  // y[7686] += A[123014] * x[7381];

  tmp1_256 = _mm256_maskload_ps(&A[123009],
                                _mm256_set_epi32(0, 0, -1, -1, -1, -1, -1, -1));
  tmp0_128 = _mm_load_ss(&x[7344]);
  __mv_insertps(tmp0_128, tmp0_128, x[7346], 1);
  __mv_insertps(tmp0_128, tmp0_128, x[7349], 2);
  __mv_insertps(tmp0_128, tmp0_128, x[7355], 3);
  tmp1_128 = _mm_load_ss(&x[7356]);
  __mv_insertps(tmp1_128, tmp1_128, x[7381], 1);
  tmp2_256 = _mm256_set_m128(tmp1_128, tmp0_128);
  y_1 = _mm256_fmadd_ps(tmp1_256, tmp2_256, tmp0_256);
#ifdef FUSED
  tmp1_256 = _mm256_hadd_ps(y_0, y_1);
  vlow = _mm256_castps256_ps128(tmp1_256);    // cost 0
  vhigh = _mm256_extractf128_ps(tmp1_256, 1); // high 128
#else
  vlow = _mm256_castps256_ps128(y_1);    // cost 0
  vhigh = _mm256_extractf128_ps(y_1, 1); // high 128
#endif
  vlow = _mm_add_ps(vlow, vhigh); // add the low 128
  shuf = _mm_movehdup_ps(vlow);   // broadcast elements 3,1 to 2,0
  sums = _mm_add_ps(vlow, shuf);
#ifndef FUSED
  shuf = _mm_movehl_ps(shuf, sums); // high half -> low half
  sums = _mm_add_ss(sums, shuf);
  y[7686] += _mm_cvtss_f32(sums);
#else
  y[7685] += _mm_cvtss_f32(sums);
  y[7686] += sums[2];
#endif
}

/* main */
MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);
int n = N;

/* array declaration */
POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(y, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);

/* init arrays */
init_1darray(n, POLYBENCH_ARRAY(A));
init_1darray(n, POLYBENCH_ARRAY(y));
init_1darray(n, POLYBENCH_ARRAY(x));

/* initialize random seed: */
#ifdef COLDCACHE
srand(time(NULL));
random_indices[0] = ((rand() % OFFSET) + OFFSET) % N;
for (int i = 1; i < TSTEPS; ++i) {
  random_indices[i] = (random_indices[i - 1] + (rand() % OFFSET) + OFFSET) %
                      (N - 123009) / 16 * 16;
}
#else
for (int i = 0; i < TSTEPS; ++i) {
  random_indices[0] = 0;
}
#endif

/* Flush cache; but wait for them be completed */
polybench_flush_cache();
_mm_mfence();
_mm_lfence();

#ifdef KERNEL_CSR
int col[30] = {7590, 7591, 7593, 7604, 7628, 7642, 7684, 7685, 7217, 7218,
               7219, 7220, 7222, 7224, 7229, 7231, 7232, 7235, 7249, 7268,
               7302, 7303, 7304, 7343, 7344, 7346, 7349, 7355, 7356, 7381};
int row_ptr[3] = {0, 8, 30};
#endif

if (TSTEPS == 1) {
  uint64_t start, end;
  unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

  // Warm up icache
  __asm volatile("cpuid\n\t"
                 "rdtsc\n\t"
                 : "=r"(cycles_high), "=r"(cycles_low)::"rax", "rbx", "rcx",
                   "rdx");
  __asm volatile("cpuid\n\t"
                 "lfence;rdtsc\n\t"
                 : "=r"(cycles_high), "=r"(cycles_low)::"rax", "rbx", "rcx",
                   "rdx");
  __asm volatile("cpuid\n\t"
                 "rdtsc;sfence;lfence\n\t"
                 : "=r"(cycles_high), "=r"(cycles_low)::"rax", "rbx", "rcx",
                   "rdx");
  _mm_mfence();
  // Measure
#ifdef KERNEL_CSR
  PROFILE_FUNCTION_LOOP(KERNEL_NAME(POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(y),
                                    POLYBENCH_ARRAY(x), col, row_ptr, 0),
                        TSTEPS);
#else
  PROFILE_FUNCTION_LOOP(KERNEL_NAME(POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(y),
                                    POLYBENCH_ARRAY(x), 0, 0),
                        TSTEPS);
#endif
} else {
#ifdef KERNEL_CSR
  PROFILE_FUNCTION_LOOP(exercise_csr(POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(y),
                                     POLYBENCH_ARRAY(x), col, row_ptr,
                                     random_indices[__marta_tsteps],
                                     __marta_tsteps),
                        TSTEPS);
#else
  PROFILE_FUNCTION_LOOP(
      KERNEL_NAME(POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(y), POLYBENCH_ARRAY(x),
                  // random_indices[__marta_tsteps], __marta_tsteps),
                  0, 0),
      TSTEPS);

#endif
}

// Avoid DCE
if (argc >= 42) {
  print_array1d(n, POLYBENCH_ARRAY(y));
}

// Be clean
POLYBENCH_FREE_ARRAY(A);
POLYBENCH_FREE_ARRAY(y);
POLYBENCH_FREE_ARRAY(x);
MARTA_BENCHMARK_END;

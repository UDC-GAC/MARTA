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

#include "marta_wrapper.h"
#include <immintrin.h>

#if !defined(GATHER) && !defined(SCATTER)
#define GATHER
#endif

#ifndef KERNEL
#define KERNEL gather
#endif

#ifdef SCATTER
#undef KERNEL
#define KERNEL scatter
#endif

#ifdef N
#undef N
#define N 64 * 1024 * 1024
#endif

#ifndef OFFSET
#define OFFSET 64 * 1024
#endif

#ifndef ELEMS
#define ELEMS 8
#endif

static inline void gather(float *restrict x) {
#if ELEMS > 4
  __m256i index =
      _mm256_set_epi32(IDX7, IDX6, IDX5, IDX4, IDX3, IDX2, IDX1, IDX0);
#if ELEMS == 8
  __m256 tmp = _mm256_i32gather_ps(x, index, 4);
#else
  __m256 tmp;
#if ELEMS >= 6
#define MASK_1 -1
#else
#define MASK_1 0
#endif
#if ELEMS >= 7
#define MASK_2 -1
#else
#define MASK_2 0
#endif
  __m256 mask = _mm256_set_ps(0, MASK_2, MASK_1, -1, -1, -1, -1, -1);
  tmp = _mm256_mask_i32gather_ps(tmp, x, index, mask, 4);
#endif
#else
  __m128i index = _mm_set_epi32(IDX3, IDX2, IDX1, IDX0);
#if ELEMS == 4
  __m128 tmp = _mm_i32gather_ps(x, index, 4);
#else
#if ELEMS == 3
#define MASK_2 -1
#else
#define MASK_2 0
#endif
  __m128 mask = _mm_set_ps(0, MASK_2, -1, -1);
  __m128 tmp;
  tmp = _mm_mask_i32gather_ps(tmp, x, index, mask, 4);
#endif
#endif
  DO_NOT_TOUCH(tmp);
}

static inline void scatter(float *restrict x) {
  unsigned int mask;
#if ELEMS > 4
  __m256i index =
      _mm256_set_epi32(IDX7, IDX6, IDX5, IDX4, IDX3, IDX2, IDX1, IDX0);
  __m256 tmp;
#if ELEMS == 8
  _mm256_i32scatter_ps(x, index, tmp, 4);
#else
#if ELEMS == 7
  mask = 0b01111111;
#elif ELEMS == 6
  mask = 0b00111111;
#elif ELEMS == 5
  mask = 0b00011111;
#endif
  _mm256_mask_i32scatter_ps(x, mask, index, tmp, 4);
#endif
#else
  __m128i index = _mm_set_epi32(IDX3, IDX2, IDX1, IDX0);
  __m128 tmp;
#if ELEMS == 4
  _mm_i32scatter_ps(x, index, tmp, 4);
#else
#if ELEMS == 3
  mask = 0b00000111;
#elif ELEMS == 2
  mask = 0b00000011;
#endif
  _mm_mask_i32scatter_ps(x, mask, index, tmp, 4);
#endif
#endif
  DO_NOT_TOUCH(x);
}

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);
int n = N;
POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);
init_1darray(n, POLYBENCH_ARRAY(x));
MARTA_FLUSH_CACHE;
PROFILE_FUNCTION_LOOP(KERNEL(POLYBENCH_ARRAY(x) + __marta_tsteps * OFFSET));
MARTA_BENCHMARK_END;

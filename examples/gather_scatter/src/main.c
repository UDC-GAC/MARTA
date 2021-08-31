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

void gather_scatter(float *restrict x) {
  __m256i index =
      _mm256_set_epi32(IDX7, IDX6, IDX5, IDX4, IDX3, IDX2, IDX1, IDX0);
#if defined(GATHER)
  __m256 tmp = _mm256_i32gather_ps(x, index, 4);
  DO_NOT_TOUCH(tmp);
#elif defined(SCATTER)
  __m256 tmp;
  _mm256_i32scatter_ps(x, index, tmp, 4);
  DO_NOT_TOUCH(x);
#else
#error "Need to define -DGATHER or -DSCATTER"
#endif
}

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);
int n = N;
POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);
PROFILE_FUNCTION_LOOP(gather_scatter(POLYBENCH_ARRAY(x)), TSTEPS);
MARTA_BENCHMARK_END;

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

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

void static gather(DATA_TYPE *restrict A) {
  __m256i idx_gather =
      _mm256_set_epi32(IDX7, IDX6, IDX5, IDX4, IDX3, IDX2, IDX1, IDX0);
  __m256 tmp256 = _mm256_i32gather_ps(&A[0], idx_gather, 4);
  DO_NOT_TOUCH(idx_gather);
  DO_NOT_TOUCH_XMM(tmp256);
}

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);
POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, N);
init_1darray(N, POLYBENCH_ARRAY(A));
PROFILE_FUNCTION_LOOP(gather(POLYBENCH_ARRAY(A)), TSTEPS);
MARTA_BENCHMARK_END;

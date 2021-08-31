#include "marta_wrapper.h"
#include <immintrin.h>

#ifndef IDX_A
#define IDX_A 0
#endif

void kernel(float *restrict A) {
  __m256 tmp0 = _mm256_load_ps(&A[IDX_A]);
  DO_NOT_TOUCH(tmp0);
}

MARTA_BENCHMARK_BEGIN(0);

int n = N;
POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, n);
init_1darray(n, POLYBENCH_ARRAY(A));

PROFILE_FUNCTION_LOOP(kernel(POLYBENCH_ARRAY(A)), TSTEPS);

// TODO: free memory, avoid DCE
MARTA_AVOID_DCE(POLYBENCH_ARRAY(A));
MARTA_BENCHMARK_END;
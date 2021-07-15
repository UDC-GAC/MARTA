#include "marta_wrapper.h"
#include <immintrin.h>

#ifndef IDX_A
#define IDX_A 0
#endif

void kernel(float *A) { 
    __m256 tmp0 = _mm256_load_ps(&A[IDX_A]);
    
}

MARTA_BENCHMARK_BEGIN(0);

int n = N;

// TODO: Declarations
POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(B, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(C, DATA_TYPE, N, n);

// TODO: Initialization
init_1darray(n, POLYBENCH_ARRAY(A));
init_1darray(n, POLYBENCH_ARRAY(B));
init_1darray(n, POLYBENCH_ARRAY(C));

// TODO:
PROFILE_FUNCTION_TSTEPS_LOOP(kern(POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(B),
                                  POLYBENCH_ARRAY(C)));

// TODO: free memory, avoid DCE
MARTA_AVOID_DCE(POLYBENCH_ARRAY(A));
MARTA_BENCHMARK_END;
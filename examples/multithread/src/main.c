#include "marta_wrapper.h"

#define NO_HEADER

#if defined(NO_HEADER)
#include "multithread.c"
#else
#include "multithread.h"
#endif

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

PROFILE_FUNCTION_LOOP(kernel(POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(B),
                             POLYBENCH_ARRAY(C)),
                      TSTEPS);

// TODO: free memory, avoid DCE
MARTA_AVOID_DCE(POLYBENCH_ARRAY(A));
MARTA_BENCHMARK_END;
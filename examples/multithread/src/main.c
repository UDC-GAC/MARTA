#define DATA_TYPE_IS_FLOAT

#include "marta_wrapper.h"

#define NO_HEADER

#if defined(NO_HEADER)
#include "multithread.c"
#else
#include "multithread.h"
#endif

MARTA_BENCHMARK_BEGIN(0);

int n = N;

POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(B, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(C, DATA_TYPE, N, n);

init_1darray(n, POLYBENCH_ARRAY(A));
init_1darray(n, POLYBENCH_ARRAY(B));
init_1darray(n, POLYBENCH_ARRAY(C));

MARTA_FLUSH_CACHE;

PROFILE_FUNCTION(kernel(POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(B),
                        POLYBENCH_ARRAY(C)));
MARTA_AVOID_DCE(POLYBENCH_ARRAY(A));
MARTA_BENCHMARK_END;
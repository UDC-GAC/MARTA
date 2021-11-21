#define DATA_TYPE_IS_FLOAT

#include "marta_wrapper.h"

#ifndef PACKING_TEMPLATE
#include "codes/rvp_float_4elems_4nnz_0_0_0_0.c"
#else
#include TO_STRING(PACKING_TEMPLATE)
#endif

MARTA_BENCHMARK_BEGIN(0);

int n = N;

// Declarations
POLYBENCH_1D_ARRAY_DECL(p, DATA_TYPE, N, n);

// Initialization
init_1darray(n, POLYBENCH_ARRAY(p));

PROFILE_FUNCTION_LOOP(kernel(POLYBENCH_ARRAY(p) + __marta_tsteps * N_OFFSET));

// Free memory, avoid DCE
// MARTA_AVOID_DCE(POLYBENCH_ARRAY(p));
POLYBENCH_FREE_ARRAY(p);
MARTA_BENCHMARK_END;
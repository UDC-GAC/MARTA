#include "marta_wrapper.h"

// void kernel(DATA_TYPE POLYBENCH_1D(p, N, n));
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

PROFILE_FUNCTION_LOOP(kernel(POLYBENCH_ARRAY(p)), TSTEPS);

// Free memory, avoid DCE
// MARTA_AVOID_DCE(POLYBENCH_ARRAY(p));
POLYBENCH_FREE_ARRAY(p);
MARTA_BENCHMARK_END;
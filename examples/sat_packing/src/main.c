#define DATA_TYPE_IS_FLOAT

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

PROFILE_FUNCTION_LOOP(kernel(POLYBENCH_ARRAY(p) + __marta_tsteps * OFFSET));

// Free memory, avoid DCE
// MARTA_AVOID_DCE(POLYBENCH_ARRAY(p));
POLYBENCH_FREE_ARRAY(p);
MARTA_BENCHMARK_END;
#include "kernel_redux.h"
#include "marta_wrapper.h"

MARTA_BENCHMARK_BEGIN(0);

/* Variable declaration/allocation. */
POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, M, N, m, n);
POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(y, DATA_TYPE, N, n);

/* Initialize array(s). */
init_2darray(n, POLYBENCH_ARRAY(A));
init_1darray(n, POLYBENCH_ARRAY(x));
init_1darray(n, POLYBENCH_ARRAY(y));

PROFILE_FUNCTION(nsteps,
                 KERNEL_NAME(m, n, uI, uIt, uIs, uJ, uJt, uJs,
                             POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(x),
                             POLYBENCH_ARRAY(y)),
                 FUNC_STR, "A,x,y", nsteps *FUNC_OPS * 2L, 0);

/* Prevent dead-code elimination. All live-out data must be printed
   by the function call in argument. */
polybench_prevent_dce(print_array1d(n, POLYBENCH_ARRAY(y)));
polybench_prevent_dce(print_array2d(n, POLYBENCH_ARRAY(A)));

MARTA_BENCHMARK_END;
#define DATA_TYPE_IS_FLOAT

#include "marta_wrapper.h"
#include "matrices.h"
#include <immintrin.h>

#ifdef N
#undef N
#define N 1024 * 1024 * 32
#endif

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);

int n = N;

// Initialization section

POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(y, DATA_TYPE, N, n);

init_1darray(n, POLYBENCH_ARRAY(A));
init_1darray(n, POLYBENCH_ARRAY(x));
init_1darray(n, POLYBENCH_ARRAY(y));

// if (MARTA_INTEL_FLUSH_DATA == 1) {
//   intel_clflush(POLYBENCH_ARRAY(A), N * sizeof(DATA_TYPE));
//   intel_clflush(POLYBENCH_ARRAY(x), N * sizeof(DATA_TYPE));
//   intel_clflush(POLYBENCH_ARRAY(y), N * sizeof(DATA_TYPE));
// }

polybench_flush_cache();
_mm_mfence();
_mm_lfence();

PROFILE_FUNCTION_LOOP(kernel_spmv(POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(x),
                                  POLYBENCH_ARRAY(y)));

polybench_prevent_dce(marta_print_1darray("y", n, POLYBENCH_ARRAY(y)));
// polybench_prevent_dce(marta_print_1darray("A", n, POLYBENCH_ARRAY(A)));
// polybench_prevent_dce(marta_print_1darray("x", n, POLYBENCH_ARRAY(x)));

MARTA_AVOID_DCE(y);

MARTA_BENCHMARK_END;

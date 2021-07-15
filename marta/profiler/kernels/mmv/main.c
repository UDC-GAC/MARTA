#include "marta_wrapper.h"
#include "mmv.h"

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);

int TSTEPS = NRUNS;

#ifdef MARTA_PARAMETRIC_LOOP
if (argc > 1) {
  TSTEPS = atoi(argv[1]);
}
#endif

// Initialization section

POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, (N+I0)*(M+J0), (n+I0)*(m+J0));
POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, (M+J0), (M+J0));
POLYBENCH_1D_ARRAY_DECL(y, DATA_TYPE, (N+I0), (N+I0));


/*
if (MARTA_INTEL_FLUSH_DATA == 1) {
  intel_clflush(POLYBENCH_ARRAY(A), N * sizeof(DATA_TYPE));
  intel_clflush(POLYBENCH_ARRAY(x), N * sizeof(DATA_TYPE));
  intel_clflush(POLYBENCH_ARRAY(y), N * sizeof(DATA_TYPE));
}
*/

if (TSTEPS == 1) {
  PROFILE_FUNCTION_TSTEPS_LOOP(
      kernel_mmv(POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(x), POLYBENCH_ARRAY(y)));
} else {
  PROFILE_FUNCTION_NO_LOOP(
      kernel_mmv(POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(x), POLYBENCH_ARRAY(y)));
}

MARTA_AVOID_DCE(y);

MARTA_BENCHMARK_END;

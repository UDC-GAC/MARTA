#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

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

#define DATA_TYPE_IS_FLOAT

#include "marta_wrapper.h"
#include <immintrin.h>

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);

int TSTEPS = NRUNS;

#ifdef MARTA_PARAMETRIC_LOOP
if (argc > 1) {
  TSTEPS = atoi(argv[1]);
}
#endif

// Initialization section
POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, n);

init_1darray(n, POLYBENCH_ARRAY(A));

__m256 tmp256;

polybench_start_instruments;
#pragma nounroll_and_jam
for (int t = 0; t < TSTEPS; ++t) {
  tmp256 = _mm256_i32gather_ps(
      &A[0], _mm256_set_epi32(IDX7, IDX6, IDX5, IDX4, IDX3, IDX2, IDX1, IDX0),
      4);
  CLOBBER_MEMORY;
}
polybench_stop_instruments;
polybench_print_instruments;

if (argc >= 42) {
  printf("tmp %f", tmp256[2]);
}

// Avoid DCE section
polybench_prevent_dce(print_array1d(4, POLYBENCH_ARRAY(A)));

MARTA_BENCHMARK_END;

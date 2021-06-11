#include "marta_wrapper.h"
#include "micro_ins.h"
#include <immintrin.h>
#include <unistd.h>

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);

size_t size = sizeof(float) * 1024 * 1024;
float *p = (float *)malloc(size);
posix_memalign(&p, sysconf(_SC_PAGESIZE), size);

#include FILE_DECL

polybench_start_instruments;
//#pragma nounroll_and_jam
// for (int t = 0; t < TSTEPS; ++t) {
BEGIN_LOOP(TSTEPS);
#include FILE_KERNEL
// asm volatile("shufps %xmm0, %xmm1, 0x01" :::);
END_LOOP;
//}
polybench_stop_instruments;
polybench_print_instruments;

// Sum of all temporaries and use the value to avoid DCE
#include FILE_DCE

MARTA_BENCHMARK_END;

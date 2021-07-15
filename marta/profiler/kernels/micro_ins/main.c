#include "marta_wrapper.h"
#include "micro_ins.h"
#include <immintrin.h>
#include <unistd.h>

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);

size_t size = sizeof(float) * 1024 * 1024;
float *p = (float *)malloc(size);
posix_memalign(&p, sysconf(_SC_PAGESIZE), size);

//#include FILE_DECL

//__m128 tmp0, tmp1, res0;
__m256 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;

polybench_start_instruments;
//#pragma nounroll_and_jam
// for (int t = 0; t < TSTEPS; ++t) {
BEGIN_LOOP(TSTEPS);
//#include FILE_KERNEL
#if OPTION == 1
tmp0 = _mm256_loadu_ps(&p[0]);
tmp1 = _mm256_loadu_ps(&p[17 - 1]);
tmp2 = _mm256_loadu_ps(&p[34 - 2]);
tmp3 = _mm256_loadu_ps(&p[49 - 3]);
tmp4 = _mm256_loadu_ps(&p[65 - 4]);
tmp5 = _mm256_loadu_ps(&p[73 - 5]);
tmp6 = _mm256_loadu_ps(&p[99 - 6]);
tmp7 = _mm256_loadu_ps(&p[112 - 7]);

// tmp0 = _mm256_blend_ps(tmp0, tmp1, 0x2);
// tmp2 = _mm256_blend_ps(tmp2, tmp3, 0x8);
// tmp4 = _mm256_blend_ps(tmp4, tmp5, 0x20);
// tmp6 = _mm256_blend_ps(tmp6, tmp7, 0x80);
// tmp0 = _mm256_blend_ps(tmp0, tmp2, 0xc);
// tmp4 = _mm256_blend_ps(tmp4, tmp6, 0xc0);
// tmp0 = _mm256_blend_ps(tmp0, tmp4, 0xF0);
tmp0 = _mm256_blend_ps(tmp0, tmp2, 0x2);
tmp0 = _mm256_blend_ps(tmp0, tmp2, 0x4);
tmp0 = _mm256_blend_ps(tmp0, tmp3, 0x8);
tmp0 = _mm256_blend_ps(tmp0, tmp4, 0x10);
tmp0 = _mm256_blend_ps(tmp0, tmp5, 0x20);
tmp0 = _mm256_blend_ps(tmp0, tmp6, 0x40);
tmp0 = _mm256_blend_ps(tmp0, tmp7, 0x80);
DO_NOT_TOUCH(tmp0);
#elif OPTION == 2
tmp0 = _mm256_loadu_ps(&p[0]);
tmp1 = _mm256_loadu_ps(&p[17]);
tmp2 = _mm256_loadu_ps(&p[34]);
tmp3 = _mm256_loadu_ps(&p[49]);
tmp4 = _mm256_loadu_ps(&p[65]);
tmp5 = _mm256_loadu_ps(&p[73]);
tmp6 = _mm256_loadu_ps(&p[99]);
tmp7 = _mm256_loadu_ps(&p[112]);

// tmp0 = _mm256_shuffle_ps(tmp0, tmp1, 0x0);
// tmp2 = _mm256_shuffle_ps(tmp2, tmp3, 0x0);
// tmp4 = _mm256_shuffle_ps(tmp4, tmp5, 0x0);
// tmp6 = _mm256_shuffle_ps(tmp6, tmp7, 0x0);

// tmp0 = _mm256_shuffle_ps(tmp0, tmp2, 0xc);
// tmp4 = _mm256_shuffle_ps(tmp4, tmp6, 0xc0);
// tmp0 = _mm256_shuffle_ps(tmp0, tmp4, 0xF0);
tmp0 = _mm256_shuffle_ps(tmp0, tmp2, 0x2);
tmp0 = _mm256_shuffle_ps(tmp0, tmp2, 0x4);
tmp0 = _mm256_shuffle_ps(tmp0, tmp3, 0x8);
tmp0 = _mm256_shuffle_ps(tmp0, tmp4, 0x10);
tmp0 = _mm256_shuffle_ps(tmp0, tmp5, 0x20);
tmp0 = _mm256_shuffle_ps(tmp0, tmp6, 0x40);
tmp0 = _mm256_shuffle_ps(tmp0, tmp7, 0x80);

DO_NOT_TOUCH(tmp0);
#endif
END_LOOP;
//}
polybench_stop_instruments;
polybench_print_instruments;

// Sum of all temporaries and use the value to avoid DCE
//#include FILE_DCE

MARTA_BENCHMARK_END;

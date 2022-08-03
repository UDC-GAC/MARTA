#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [32, 31, 30, 29, 28, 18, 17, 16] [1, 1, 1, 1, 0, 1, 1] (float)
    __m128 r0, r1, r2;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[28],0x000000f0);
    r2 = _mm_loadu_ps(&p[29]);
    output = _mm256_set_m128(r2,r1);
    DO_NOT_TOUCH(output);
}
    
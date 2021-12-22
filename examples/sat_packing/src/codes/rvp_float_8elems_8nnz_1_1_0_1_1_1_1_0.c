#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [32, 31, 30, 20, 19, 18, 17, 16] [1, 1, 0, 1, 1, 1, 1] (float)
    __m128 r0, r1, r2;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    r1 = _mm_load_ss(&p[20]);
    _mv_blend_mem_ps(r2,r1,p[29],0x0000000e);
    output = _mm256_set_m128(r2,r0);
    DO_NOT_TOUCH(output);
}
    
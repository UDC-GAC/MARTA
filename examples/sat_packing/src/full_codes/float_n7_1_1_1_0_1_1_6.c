#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 31, 30, 29, 28, 18, 17, 16] [1, 1, 1, 0, 1, 1] (float)
    __m128 r0, r1, r2, r3;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[28],0x000000b0);
    r2 = _mm_load_ss(&p[29]);
    _mv_blend_mem_ps(r3,r2,p[29],0x00000006);
    output = _mm256_set_m128(r3,r1);
    DO_NOT_TOUCH(output);
}
    
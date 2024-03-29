#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [59, 58, 57, 47, 37, 27, 26, 16] [1, 1, 0, 0, 0, 1, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5;
    __m256 output;
    r0 = _mm_load_ss(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[26],0x00000018);
    _mv_insert_mem_ps(r2,r1,p[27],0x00000068);
    _mv_insert_mem_ps(r3,r2,p[37],0x00000030);
    r4 = _mm_loadu_ps(&p[47]);
    _mv_blend_mem_ps(r5,r4,p[56],0x0000000e);
    output = _mm256_set_m128(r5,r3);
    DO_NOT_TOUCH(output);
}
    
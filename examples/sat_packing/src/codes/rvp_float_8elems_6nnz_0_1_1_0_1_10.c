#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 39, 29, 28, 27, 17, 16] [0, 1, 1, 0, 1] (float)
    __m128 r0, r1, r2, r3, r4;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[27],0x00000028);
    _mv_insert_mem_ps(r2,r1,p[28],0x00000030);
    _mv_blend_mem_ps(r3,_mm_set_epi32(0,0,0,0),p[29],0x0000000b);
    _mv_insert_mem_ps(r4,r3,p[39],0x0000005c);
    output = _mm256_set_m128(r4,r2);
    DO_NOT_TOUCH(output);
}
    
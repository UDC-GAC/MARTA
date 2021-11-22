#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [59, 49, 39, 29, 28, 18, 17, 16] [0, 0, 0, 1, 0, 1, 1] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6;
    __m256 output;
    _mv_blend_mem_ps(r0,_mm_set_epi32(0,0,0,0),p[16],0x00000007);
    _mv_insert_mem_ps(r1,r0,p[28],0x000000b0);
    _mv_blend_mem_ps(r2,_mm_set_epi32(0,0,0,0),p[29],0x0000000f);
    _mv_insert_mem_ps(r3,r2,p[39],0x00000014);
    _mv_insert_mem_ps(r4,r2,p[49],0x00000082);
    _mv_insert_mem_ps(r5,r4,p[59],0x0000005c);
    r6 = _mm_movelh_ps(r3,r5);
    output = _mm256_set_m128(r6,r1);
    DO_NOT_TOUCH(output);
}
    
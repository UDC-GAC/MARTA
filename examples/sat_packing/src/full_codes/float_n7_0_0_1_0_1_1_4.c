#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 49, 39, 29, 28, 18, 17, 16] [0, 0, 1, 0, 1, 1] (float)
    __m128 r0, r1, r2, r3, r4;
    __m256 output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(-1,-1,-1,-1));
    _mv_insert_mem_ps(r1,r0,p[28],0x00000030);
    _mv_blend_mem_ps(r2,_mm_set_ps(0,0,0,0),p[29],0x00000009);
    _mv_insert_mem_ps(r3,r2,p[39],0x00000014);
    _mv_insert_mem_ps(r4,r3,p[49],0x000000a8);
    output = _mm256_set_m128(r4,r1);
    DO_NOT_TOUCH(output);
}
    
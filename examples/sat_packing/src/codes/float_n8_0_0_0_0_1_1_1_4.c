#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [59, 49, 39, 29, 19, 18, 17, 16] [0, 0, 0, 0, 1, 1, 1] (float)
    __m128 r0, r1, r2, r3, r4;
    __m256 output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(-1,-1,-1,-1));
    _mv_blend_mem_ps(r1,_mm_set_ps(0,0,0,0),p[29],0x0000000f);
    _mv_insert_mem_ps(r2,r1,p[39],0x00000014);
    _mv_insert_mem_ps(r3,r2,p[49],0x00000028);
    _mv_insert_mem_ps(r4,r3,p[59],0x00000030);
    output = _mm256_set_m128(r4,r0);
    DO_NOT_TOUCH(output);
}
    
#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [50, 49, 39, 29, 28, 27, 26, 16] [1, 0, 0, 1, 1, 1, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5;
    __m256 output;
    r0 = _mm_load_ss(&p[16]);
    _mv_blend_mem_ps(r1,r0,p[25],0x0000000e);
    r2 = _mm_maskload_ps(&p[29],_mm_set_epi32(-1,0,0,-1));
    _mv_insert_mem_ps(r3,r2,p[39],0x00000094);
    _mv_insert_mem_ps(r4,r3,p[49],0x00000028);
    _mv_insert_mem_ps(r5,r4,p[50],0x00000030);
    output = _mm256_set_m128(r5,r1);
    DO_NOT_TOUCH(output);
}
    
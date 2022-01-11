#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 30, 29, 28, 27, 26, 16] [1, 1, 1, 1, 0] (float)
    __m128 r0, r1, r2;
    __m256 output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(0,-1,0,-1));
    _mv_blend_mem_ps(r1,r0,p[25],0x0000000e);
    _mv_blend_mem_ps(r2,_mm_set_ps(0,0,0,0),p[29],0x00000003);
    output = _mm256_set_m128(r2,r1);
    DO_NOT_TOUCH(output);
}
    
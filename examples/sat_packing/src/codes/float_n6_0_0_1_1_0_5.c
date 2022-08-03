#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 48, 38, 28, 27, 26, 16] [0, 0, 1, 1, 0] (float)
    __m128 r0, r1, r2, r3;
    __m256 output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(0,0,0,-1));
    _mv_blend_mem_ps(r1,r0,p[25],0x0000000e);
    _mv_blend_mem_ps(r2,_mm_set_ps(0,0,0,0),p[38],0x0000000d);
    _mv_insert_mem_ps(r3,r2,p[48],0x0000001c);
    output = _mm256_set_m128(r3,r1);
    DO_NOT_TOUCH(output);
}
    
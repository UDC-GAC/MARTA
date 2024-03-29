#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [68, 58, 57, 56, 46, 36, 26, 16] [0, 1, 1, 0, 0, 0, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5;
    __m256 output;
    _mv_blend_mem_ps(r0,_mm_set_ps(0,0,0,0),p[16],0x00000001);
    _mv_insert_mem_ps(r1,r0,p[26],0x00000014);
    _mv_insert_mem_ps(r2,r1,p[36],0x00000020);
    _mv_insert_mem_ps(r3,r2,p[46],0x000000b0);
    _mv_blend_mem_ps(r4,_mm_set_ps(0,0,0,0),p[56],0x0000000f);
    _mv_insert_mem_ps(r5,r4,p[68],0x000000b0);
    output = _mm256_set_m128(r5,r3);
    DO_NOT_TOUCH(output);
}
    
#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [68, 58, 48, 38, 28, 27, 17, 16] [0, 0, 0, 0, 1, 0, 1] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6;
    __m256 output;
    r0 = _mm_loadl_pi(_mm_set_ps(0,0,0,0),&p[16]);
    r1 = _mm_loadh_pi(r0,&p[27]);
    _mv_blend_mem_ps(r2,_mm_set_ps(0,0,0,0),p[38],0x0000000f);
    _mv_insert_mem_ps(r3,r2,p[48],0x00000090);
    _mv_insert_mem_ps(r4,r2,p[58],0x00000044);
    _mv_insert_mem_ps(r5,r4,p[68],0x00000094);
    r6 = _mm_movelh_ps(r3,r5);
    output = _mm256_set_m128(r6,r1);
    DO_NOT_TOUCH(output);
}
    
#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [68, 58, 48, 38, 37, 36, 26, 16] [0, 0, 0, 1, 1, 0, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6, r7;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[26],0x00000010);
    r2 = _mm_loadh_pi(r1,&p[36]);
    _mv_blend_mem_ps(r3,_mm_set_ps(0,0,0,0),p[38],0x00000001);
    _mv_insert_mem_ps(r4,r3,p[48],0x00000014);
    _mv_insert_mem_ps(r5,r3,p[58],0x0000000a);
    _mv_insert_mem_ps(r6,r5,p[68],0x0000001c);
    r7 = _mm_movelh_ps(r4,r6);
    output = _mm256_set_m128(r7,r2);
    DO_NOT_TOUCH(output);
}
    
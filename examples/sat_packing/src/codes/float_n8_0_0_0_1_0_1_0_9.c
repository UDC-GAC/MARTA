#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [68, 58, 48, 38, 37, 27, 26, 16] [0, 0, 0, 1, 0, 1, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6, r7, r8;
    __m256 output;
    r0 = _mm_load_ss(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[26],0x0000001c);
    _mv_insert_mem_ps(r2,r1,p[27],0x000000a8);
    _mv_insert_mem_ps(r3,r2,p[37],0x00000030);
    _mv_blend_mem_ps(r4,_mm_set_ps(0,0,0,0),p[38],0x00000005);
    _mv_insert_mem_ps(r5,r4,p[48],0x0000005c);
    _mv_insert_mem_ps(r6,r4,p[58],0x00000006);
    _mv_insert_mem_ps(r7,r6,p[68],0x00000058);
    r8 = _mm_movelh_ps(r5,r7);
    output = _mm256_set_m128(r8,r3);
    DO_NOT_TOUCH(output);
}
    
#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [86, 76, 66, 56, 46, 36, 26, 16] [0, 0, 0, 0, 0, 0, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
    __m256 output;
    _mv_blend_mem_ps(r0,_mm_set_ps(0,0,0,0),p[16],0x00000007);
    _mv_insert_mem_ps(r1,r0,p[26],0x0000001c);
    _mv_insert_mem_ps(r2,r0,p[36],0x00000004);
    _mv_insert_mem_ps(r3,r2,p[46],0x0000001c);
    r4 = _mm_movelh_ps(r1,r3);
    _mv_blend_mem_ps(r5,_mm_set_ps(0,0,0,0),p[56],0x00000007);
    _mv_insert_mem_ps(r6,r5,p[66],0x0000005c);
    _mv_insert_mem_ps(r7,r5,p[76],0x0000008c);
    _mv_insert_mem_ps(r8,r7,p[86],0x0000001c);
    r9 = _mm_movelh_ps(r6,r8);
    output = _mm256_set_m128(r9,r4);
    DO_NOT_TOUCH(output);
}
    
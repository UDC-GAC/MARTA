#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 76, 66, 56, 46, 36, 26, 16] [0, 0, 0, 0, 0, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6, r7;
    __m256 output;
    _mv_blend_mem_ps(r0,_mm_set_ps(0,0,0,0),p[16],0x0000000f);
    _mv_insert_mem_ps(r1,r0,p[26],0x00000014);
    _mv_insert_mem_ps(r2,r0,p[36],0x0000000a);
    _mv_insert_mem_ps(r3,r2,p[46],0x0000001c);
    r4 = _mm_movelh_ps(r1,r3);
    r5 = _mm_load_ss(&p[56]);
    _mv_insert_mem_ps(r6,r5,p[66],0x0000009c);
    _mv_insert_mem_ps(r7,r6,p[76],0x000000a8);
    output = _mm256_set_m128(r7,r4);
    DO_NOT_TOUCH(output);
}
    
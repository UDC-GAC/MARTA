#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 0, 47, 46, 36, 26, 16] [1, 0, 0, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5;
    __m256 output;
    _mv_blend_mem_ps(r0,_mm_set_epi32(0,0,0,0),p[16],0x0000000d);
    _mv_insert_mem_ps(r1,r0,p[26],0x00000014);
    _mv_insert_mem_ps(r2,r0,p[36],0x00000006);
    _mv_insert_mem_ps(r3,r2,p[46],0x00000010);
    r4 = _mm_movelh_ps(r1,r3);
    _mv_blend_mem_ps(r5,_mm_set_epi32(0,0,0,0),p[47],0x00000001);
    output = _mm256_set_m128(r5,r4);
    DO_NOT_TOUCH(output);
}
    
#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [59, 49, 39, 29, 28, 27, 26, 16] [0, 0, 0, 1, 1, 1, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    _mv_blend_mem_ps(r1,r0,p[25],0x0000000e);
    _mv_blend_mem_ps(r2,_mm_set_ps(0,0,0,0),p[29],0x0000000d);
    _mv_insert_mem_ps(r3,r2,p[39],0x0000001c);
    _mv_insert_mem_ps(r4,r2,p[49],0x00000008);
    _mv_insert_mem_ps(r5,r4,p[59],0x0000009c);
    r6 = _mm_movelh_ps(r3,r5);
    output = _mm256_set_m128(r6,r1);
    DO_NOT_TOUCH(output);
}
    
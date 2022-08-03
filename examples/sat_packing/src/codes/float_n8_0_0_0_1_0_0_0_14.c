#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [77, 67, 57, 47, 46, 36, 26, 16] [0, 0, 0, 1, 0, 0, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
    __m256 output;
    r0 = _mm_load_ss(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[26],0x0000009c);
    _mv_insert_mem_ps(r2,r0,p[36],0x0000000e);
    _mv_insert_mem_ps(r3,r2,p[46],0x0000005c);
    r4 = _mm_movelh_ps(r1,r3);
    _mv_blend_mem_ps(r5,_mm_set_ps(0,0,0,0),p[47],0x0000000f);
    _mv_insert_mem_ps(r6,r5,p[57],0x0000005c);
    _mv_insert_mem_ps(r7,r5,p[67],0x00000042);
    _mv_insert_mem_ps(r8,r7,p[77],0x00000054);
    r9 = _mm_movelh_ps(r6,r8);
    output = _mm256_set_m128(r9,r4);
    DO_NOT_TOUCH(output);
}
    
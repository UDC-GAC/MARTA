#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [77, 67, 57, 47, 37, 27, 17, 16] [0, 0, 0, 0, 0, 0, 1] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6, r7;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[27],0x00000068);
    _mv_insert_mem_ps(r2,r1,p[37],0x00000030);
    _mv_blend_mem_ps(r3,_mm_set_ps(0,0,0,0),p[47],0x0000000f);
    _mv_insert_mem_ps(r4,r3,p[57],0x00000054);
    _mv_insert_mem_ps(r5,r3,p[67],0x00000082);
    _mv_insert_mem_ps(r6,r5,p[77],0x00000090);
    r7 = _mm_movelh_ps(r4,r6);
    output = _mm256_set_m128(r7,r2);
    DO_NOT_TOUCH(output);
}
    
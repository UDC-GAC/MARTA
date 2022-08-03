#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 67, 57, 47, 37, 27, 17, 16] [0, 0, 0, 0, 0, 1] (float)
    __m128 r0, r1, r2, r3, r4, r5;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[27],0x000000a8);
    _mv_insert_mem_ps(r2,r1,p[37],0x00000030);
    _mv_blend_mem_ps(r3,_mm_set_ps(0,0,0,0),p[47],0x00000003);
    _mv_insert_mem_ps(r4,r3,p[57],0x00000014);
    _mv_insert_mem_ps(r5,r4,p[67],0x000000a8);
    output = _mm256_set_m128(r5,r2);
    DO_NOT_TOUCH(output);
}
    
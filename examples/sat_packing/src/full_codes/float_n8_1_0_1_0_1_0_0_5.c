#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [59, 58, 48, 47, 37, 36, 26, 16] [1, 0, 1, 0, 1, 0, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6;
    __m256 output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(-1,-1,0,-1));
    _mv_insert_mem_ps(r1,r0,p[26],0x00000098);
    _mv_insert_mem_ps(r2,r1,p[36],0x00000028);
    _mv_insert_mem_ps(r3,r2,p[37],0x000000b0);
    r4 = _mm_loadu_ps(&p[47]);
    _mv_insert_mem_ps(r5,r4,p[58],0x00000028);
    _mv_insert_mem_ps(r6,r5,p[59],0x00000030);
    output = _mm256_set_m128(r6,r3);
    DO_NOT_TOUCH(output);
}
    
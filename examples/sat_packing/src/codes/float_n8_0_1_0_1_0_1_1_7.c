#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [50, 40, 39, 29, 28, 18, 17, 16] [0, 1, 0, 1, 0, 1, 1] (float)
    __m128 r0, r1, r2, r3, r4, r5;
    __m256 output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(-1,-1,-1,-1));
    _mv_insert_mem_ps(r1,r0,p[28],0x000000b0);
    r2 = _mm_maskload_ps(&p[29],_mm_set_epi32(-1,0,0,-1));
    _mv_insert_mem_ps(r3,r2,p[39],0x00000018);
    _mv_insert_mem_ps(r4,r3,p[40],0x00000028);
    _mv_insert_mem_ps(r5,r4,p[50],0x00000070);
    output = _mm256_set_m128(r5,r1);
    DO_NOT_TOUCH(output);
}
    
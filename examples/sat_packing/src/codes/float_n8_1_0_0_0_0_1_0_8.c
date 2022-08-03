#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [68, 67, 57, 47, 37, 27, 26, 16] [1, 0, 0, 0, 0, 1, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6;
    __m256 output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(-1,0,-1,-1));
    _mv_insert_mem_ps(r1,r0,p[26],0x0000001c);
    _mv_insert_mem_ps(r2,r1,p[27],0x00000028);
    _mv_insert_mem_ps(r3,r2,p[37],0x00000030);
    r4 = _mm_maskload_ps(&p[47],_mm_set_epi32(-1,-1,0,-1));
    _mv_insert_mem_ps(r5,r4,p[57],0x00000014);
    r6 = _mm_loadh_pi(r5,&p[67]);
    output = _mm256_set_m128(r6,r3);
    DO_NOT_TOUCH(output);
}
    
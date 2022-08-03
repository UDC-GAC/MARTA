#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [59, 58, 48, 38, 37, 27, 17, 16] [1, 0, 0, 1, 0, 0, 1] (float)
    __m128 r0, r1, r2, r3, r4, r5;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[27],0x000000e8);
    _mv_insert_mem_ps(r2,r1,p[37],0x000000b0);
    r3 = _mm_maskload_ps(&p[38],_mm_set_epi32(-1,-1,0,-1));
    _mv_insert_mem_ps(r4,r3,p[48],0x00000014);
    r5 = _mm_loadh_pi(r4,&p[58]);
    output = _mm256_set_m128(r5,r2);
    DO_NOT_TOUCH(output);
}
    
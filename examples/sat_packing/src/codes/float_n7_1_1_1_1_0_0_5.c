#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 40, 39, 38, 37, 36, 26, 16] [1, 1, 1, 1, 0, 0] (float)
    __m128 r0, r1, r2, r3;
    __m256 output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(-1,-1,-1,-1));
    _mv_insert_mem_ps(r1,r0,p[26],0x00000090);
    r2 = _mm_loadh_pi(r1,&p[36]);
    _mv_blend_mem_ps(r3,_mm_set_ps(0,0,0,0),p[38],0x00000007);
    output = _mm256_set_m128(r3,r2);
    DO_NOT_TOUCH(output);
}
    
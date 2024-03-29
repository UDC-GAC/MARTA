#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [32, 31, 21, 20, 19, 18, 17, 16] [1, 0, 1, 1, 1, 1, 1] (float)
    __m128 r0, r1, r2;
    __m256 output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(-1,-1,-1,-1));
    _mv_blend_mem_ps(r1,_mm_set_ps(0,0,0,0),p[20],0x0000000f);
    r2 = _mm_loadh_pi(r1,&p[31]);
    output = _mm256_set_m128(r2,r0);
    DO_NOT_TOUCH(output);
}
    
#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 39, 38, 37, 27, 17, 16] [1, 1, 0, 0, 1] (float)
    __m128 r0, r1, r2, r3;
    __m256 output;
    r0 = _mm_loadl_pi(_mm_set_ps(0,0,0,0),&p[16]);
    _mv_insert_mem_ps(r1,r0,p[27],0x000000a0);
    _mv_insert_mem_ps(r2,r1,p[37],0x00000030);
    _mv_blend_mem_ps(r3,_mm_set_ps(0,0,0,0),p[38],0x00000003);
    output = _mm256_set_m128(r3,r2);
    DO_NOT_TOUCH(output);
}
    
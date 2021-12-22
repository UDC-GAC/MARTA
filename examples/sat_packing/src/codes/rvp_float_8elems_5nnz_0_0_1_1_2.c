#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 0, 38, 28, 18, 17, 16] [0, 0, 1, 1] (float)
    __m128 r0, r1, r2;
    __m256 output;
    _mv_blend_mem_ps(r0,_mm_set_epi32(0,0,0,0),p[16],0x00000007);
    _mv_insert_mem_ps(r1,r0,p[28],0x00000070);
    r2 = _mm_load_ss(&p[38]);
    output = _mm256_set_m128(r2,r1);
    DO_NOT_TOUCH(output);
}
    
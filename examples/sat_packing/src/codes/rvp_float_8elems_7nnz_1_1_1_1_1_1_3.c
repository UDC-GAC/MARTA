#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 22, 21, 20, 19, 18, 17, 16] [1, 1, 1, 1, 1, 1] (float)
    __m128 r0, r1;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    _mv_blend_mem_ps(r1,_mm_set_epi32(0,0,0,0),p[20],0x00000007);
    output = _mm256_set_m128(r1,r0);
    DO_NOT_TOUCH(output);
}
    
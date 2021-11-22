#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 0, 29, 19, 18, 17, 16] [0, 1, 1, 1] (float)
    __m128 r0, r1;
    __m256 output;
    _mv_blend_mem_ps(r0,_mm_set_epi32(0,0,0,0),p[16],0x0000000f);
    r1 = _mm_load_ss(&p[29]);
    output = _mm256_set_m128(r1,r0);
    DO_NOT_TOUCH(output);
}
    
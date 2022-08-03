#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 0, 29, 28, 27, 17, 16] [1, 1, 0, 1] (float)
    __m128 r0, r1, r2;
    __m256 output;
    _mv_blend_mem_ps(r0,_mm_set_ps(0,0,0,0),p[16],0x0000000f);
    r1 = _mm_loadh_pi(r0,&p[27]);
    r2 = _mm_load_ss(&p[29]);
    output = _mm256_set_m128(r2,r1);
    DO_NOT_TOUCH(output);
}
    
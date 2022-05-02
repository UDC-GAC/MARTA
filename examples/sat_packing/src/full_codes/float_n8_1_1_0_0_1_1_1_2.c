#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [41, 40, 39, 29, 19, 18, 17, 16] [1, 1, 0, 0, 1, 1, 1] (float)
    __m128 r0, r1, r2;
    __m256 output;
    _mv_blend_mem_ps(r0,_mm_set_ps(0,0,0,0),p[16],0x0000000f);
    r1 = _mm_load_ss(&p[29]);
    _mv_blend_mem_ps(r2,r1,p[38],0x0000000e);
    output = _mm256_set_m128(r2,r0);
    DO_NOT_TOUCH(output);
}
    
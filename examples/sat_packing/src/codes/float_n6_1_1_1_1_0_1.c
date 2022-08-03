#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 30, 29, 28, 27, 26, 16] [1, 1, 1, 1, 0] (float)
    __m128 r0, r1, r2;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    _mv_blend_mem_ps(r1,r0,p[25],0x0000000e);
    r2 = _mm_loadl_pi(_mm_set_ps(0,0,0,0),&p[29]);
    output = _mm256_set_m128(r2,r1);
    DO_NOT_TOUCH(output);
}
    
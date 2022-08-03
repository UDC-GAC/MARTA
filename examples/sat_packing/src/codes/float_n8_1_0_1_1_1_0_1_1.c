#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [41, 40, 30, 29, 28, 27, 17, 16] [1, 0, 1, 1, 1, 0, 1] (float)
    __m128 r0, r1, r2, r3;
    __m256 output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(-1,-1,-1,-1));
    r1 = _mm_loadh_pi(r0,&p[27]);
    r2 = _mm_loadl_pi(_mm_set_ps(0,0,0,0),&p[29]);
    r3 = _mm_loadh_pi(r2,&p[40]);
    output = _mm256_set_m128(r3,r1);
    DO_NOT_TOUCH(output);
}
    
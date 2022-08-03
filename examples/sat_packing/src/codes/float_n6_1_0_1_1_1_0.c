#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 30, 29, 19, 18, 17, 16] [1, 0, 1, 1, 1] (float)
    __m128 r0, r1;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    r1 = _mm_loadl_pi(_mm_set_ps(0,0,0,0),&p[29]);
    output = _mm256_set_m128(r1,r0);
    DO_NOT_TOUCH(output);
}
    
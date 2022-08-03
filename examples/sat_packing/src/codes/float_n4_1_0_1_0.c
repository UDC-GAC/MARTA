#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [28, 27, 17, 16] [1, 0, 1] (float)
    __m128 r0, output;
    r0 = _mm_loadl_pi(_mm_set_ps(0,0,0,0),&p[16]);
    output = _mm_loadh_pi(r0,&p[27]);
    DO_NOT_TOUCH(output);
}
    
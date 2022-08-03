#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 17, 16] [1] (float)
    __m128 output;
    output = _mm_loadl_pi(_mm_set_ps(0,0,0,0),&p[16]);
    DO_NOT_TOUCH(output);
}
    
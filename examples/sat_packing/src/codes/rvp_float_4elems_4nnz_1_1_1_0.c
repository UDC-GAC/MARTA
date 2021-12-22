#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [19, 18, 17, 16] [1, 1, 1] (float)
    __m128 output;
    output = _mm_loadu_ps(&p[16]);
    DO_NOT_TOUCH(output);
}
    
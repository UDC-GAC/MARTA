#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 0, 16] (float)
    __m128 output;
    output = _mm_load_ss(&p[16]);
    DO_NOT_TOUCH(output);
}
    
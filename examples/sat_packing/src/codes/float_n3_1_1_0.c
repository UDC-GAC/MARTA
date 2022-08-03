#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 18, 17, 16] [1, 1] (float)
    __m128 output;
    output = _mm_maskload_ps(&p[16],_mm_set_epi32(0,-1,-1,-1));
    DO_NOT_TOUCH(output);
}
    
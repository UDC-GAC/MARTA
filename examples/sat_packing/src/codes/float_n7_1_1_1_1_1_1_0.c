#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 22, 21, 20, 19, 18, 17, 16] [1, 1, 1, 1, 1, 1] (float)
    __m256 output;
    output = _mm256_maskload_ps(&p[16],_mm256_set_epi32(0,-1,-1,-1,-1,-1,-1,-1));
    DO_NOT_TOUCH(output);
}
    
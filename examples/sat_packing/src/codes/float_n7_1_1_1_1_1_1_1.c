#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 22, 21, 20, 19, 18, 17, 16] [1, 1, 1, 1, 1, 1] (float)
    __m256 output;
    _mv256_blend_mem_ps(output,_mm256_set_ps(0,0,0,0,0,0,0,0),p[16],0x0000007f);
    DO_NOT_TOUCH(output);
}
    
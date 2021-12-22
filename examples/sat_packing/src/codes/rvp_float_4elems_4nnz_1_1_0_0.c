#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [28, 27, 26, 16] [1, 1, 0] (float)
    __m128 r0, output;
    r0 = _mm_load_ss(&p[16]);
    _mv_blend_mem_ps(output,r0,p[25],0x0000000e);
    DO_NOT_TOUCH(output);
}
    
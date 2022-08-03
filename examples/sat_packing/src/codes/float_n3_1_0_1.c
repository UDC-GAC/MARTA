#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 27, 26, 16] [1, 0] (float)
    __m128 r0, output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(0,-1,-1,-1));
    _mv_blend_mem_ps(output,r0,p[25],0x00000006);
    DO_NOT_TOUCH(output);
}
    
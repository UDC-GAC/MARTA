#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 18, 17, 16] [1, 1] (float)
    __m128 output;
    _mv_blend_mem_ps(output,_mm_set_epi32(0,0,0,0),p[16],0x00000007);
    DO_NOT_TOUCH(output);
}
    
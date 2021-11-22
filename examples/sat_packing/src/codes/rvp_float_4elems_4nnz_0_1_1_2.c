#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [28, 18, 17, 16] [0, 1, 1] (float)
    __m128 r0, output;
    _mv_blend_mem_ps(r0,_mm_set_epi32(0,0,0,0),p[16],0x00000007);
    _mv_insert_mem_ps(output,r0,p[28],0x000000b0);
    DO_NOT_TOUCH(output);
}
    
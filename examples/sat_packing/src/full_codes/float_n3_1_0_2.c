#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 27, 26, 16] [1, 0] (float)
    __m128 r0, output;
    _mv_blend_mem_ps(r0,_mm_set_ps(0,0,0,0),p[16],0x00000003);
    _mv_blend_mem_ps(output,r0,p[25],0x00000006);
    DO_NOT_TOUCH(output);
}
    
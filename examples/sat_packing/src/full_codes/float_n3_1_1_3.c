#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 18, 17, 16] [1, 1] (float)
    __m128 r0, output;
    r0 = _mm_loadl_pi(_mm_set_ps(0,0,0,0),&p[16]);
    _mv_blend_mem_ps(output,r0,p[16],0x00000004);
    DO_NOT_TOUCH(output);
}
    
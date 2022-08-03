#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 18, 17, 16] [1, 1] (float)
    __m128 r0, output;
    r0 = _mm_load_ss(&p[16]);
    _mv_blend_mem_ps(output,r0,p[16],0x00000006);
    DO_NOT_TOUCH(output);
}
    
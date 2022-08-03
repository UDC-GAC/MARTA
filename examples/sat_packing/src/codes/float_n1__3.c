#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 0, 16] [] (float)
    __m128 output;
    _mv_blend_mem_ps(output,_mm_set_ps(0,0,0,0),p[16],0x00000001);
    DO_NOT_TOUCH(output);
}
    
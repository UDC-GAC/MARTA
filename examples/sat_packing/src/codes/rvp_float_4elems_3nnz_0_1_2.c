#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 27, 17, 16] [0, 1] (float)
    __m128 r0, output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(-1,-1,-1,-1));
    _mv_insert_mem_ps(output,r0,p[27],0x000000a8);
    DO_NOT_TOUCH(output);
}
    
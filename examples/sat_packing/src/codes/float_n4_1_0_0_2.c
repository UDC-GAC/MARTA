#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [37, 36, 26, 16] [1, 0, 0] (float)
    __m128 r0, r1, output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(0,-1,0,-1));
    _mv_insert_mem_ps(r1,r0,p[26],0x0000001c);
    output = _mm_loadh_pi(r1,&p[36]);
    DO_NOT_TOUCH(output);
}
    
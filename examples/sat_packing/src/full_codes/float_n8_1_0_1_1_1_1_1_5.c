#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [32, 31, 21, 20, 19, 18, 17, 16] [1, 0, 1, 1, 1, 1, 1] (float)
    __m128 r0, r1, r2, r3;
    __m256 output;
    _mv_blend_mem_ps(r0,_mm_set_ps(0,0,0,0),p[16],0x0000000f);
    r1 = _mm_loadu_ps(&p[20]);
    _mv_insert_mem_ps(r2,r1,p[31],0x000000a8);
    _mv_insert_mem_ps(r3,r2,p[32],0x00000030);
    output = _mm256_set_m128(r3,r0);
    DO_NOT_TOUCH(output);
}
    
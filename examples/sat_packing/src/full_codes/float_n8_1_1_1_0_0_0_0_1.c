#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [59, 58, 57, 56, 46, 36, 26, 16] [1, 1, 1, 0, 0, 0, 0] (float)
    __m128 r0, r1, r2, r3, r4;
    __m256 output;
    _mv_blend_mem_ps(r0,_mm_set_ps(0,0,0,0),p[16],0x00000003);
    _mv_insert_mem_ps(r1,r0,p[26],0x0000001c);
    _mv_insert_mem_ps(r2,r1,p[36],0x00000068);
    _mv_insert_mem_ps(r3,r2,p[46],0x00000030);
    r4 = _mm_loadu_ps(&p[56]);
    output = _mm256_set_m128(r4,r3);
    DO_NOT_TOUCH(output);
}
    
#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [50, 40, 30, 29, 28, 18, 17, 16] [0, 0, 1, 1, 0, 1, 1] (float)
    __m128 r0, r1, r2, r3, r4;
    __m256 output;
    _mv_blend_mem_ps(r0,_mm_set_ps(0,0,0,0),p[16],0x00000007);
    _mv_insert_mem_ps(r1,r0,p[28],0x00000030);
    r2 = _mm_loadu_ps(&p[29]);
    _mv_insert_mem_ps(r3,r2,p[40],0x00000028);
    _mv_insert_mem_ps(r4,r3,p[50],0x00000070);
    output = _mm256_set_m128(r4,r1);
    DO_NOT_TOUCH(output);
}
    
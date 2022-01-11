#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [68, 58, 48, 47, 37, 27, 26, 16] [0, 0, 1, 0, 0, 1, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[26],0x00000014);
    _mv_insert_mem_ps(r2,r1,p[27],0x00000028);
    _mv_insert_mem_ps(r3,r2,p[37],0x00000030);
    r4 = _mm_loadl_pi(_mm_set_ps(0,0,0,0),&p[47]);
    _mv_insert_mem_ps(r5,r4,p[58],0x00000028);
    _mv_insert_mem_ps(r6,r5,p[68],0x00000030);
    output = _mm256_set_m128(r6,r3);
    DO_NOT_TOUCH(output);
}
    
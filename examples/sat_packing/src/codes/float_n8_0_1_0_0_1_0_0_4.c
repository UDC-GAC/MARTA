#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [68, 58, 57, 47, 37, 36, 26, 16] [0, 1, 0, 0, 1, 0, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[26],0x00000010);
    r2 = _mm_loadh_pi(r1,&p[36]);
    r3 = _mm_loadu_ps(&p[47]);
    _mv_insert_mem_ps(r4,r3,p[57],0x00000054);
    _mv_insert_mem_ps(r5,r4,p[58],0x00000028);
    _mv_insert_mem_ps(r6,r5,p[68],0x00000030);
    output = _mm256_set_m128(r6,r2);
    DO_NOT_TOUCH(output);
}
    
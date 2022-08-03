#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [59, 58, 48, 47, 46, 36, 26, 16] [1, 0, 1, 1, 0, 0, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5;
    __m256 output;
    r0 = _mm_load_ss(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[26],0x0000001c);
    _mv_insert_mem_ps(r2,r1,p[36],0x000000e8);
    _mv_insert_mem_ps(r3,r2,p[46],0x00000030);
    r4 = _mm_loadl_pi(_mm_set_ps(0,0,0,0),&p[47]);
    r5 = _mm_loadh_pi(r4,&p[58]);
    output = _mm256_set_m128(r5,r3);
    DO_NOT_TOUCH(output);
}
    
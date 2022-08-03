#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 58, 48, 38, 28, 27, 17, 16] [0, 0, 0, 1, 0, 1] (float)
    __m128 r0, r1, r2, r3, r4;
    __m256 output;
    r0 = _mm_loadl_pi(_mm_set_ps(0,0,0,0),&p[16]);
    r1 = _mm_loadh_pi(r0,&p[27]);
    r2 = _mm_load_ss(&p[38]);
    _mv_insert_mem_ps(r3,r2,p[48],0x0000001c);
    _mv_insert_mem_ps(r4,r3,p[58],0x00000028);
    output = _mm256_set_m128(r4,r1);
    DO_NOT_TOUCH(output);
}
    
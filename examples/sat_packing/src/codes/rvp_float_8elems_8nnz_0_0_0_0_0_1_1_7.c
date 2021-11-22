#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [68, 58, 48, 38, 28, 18, 17, 16] [0, 0, 0, 0, 0, 1, 1] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6;
    __m256 output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(-1,-1,-1,-1));
    _mv_insert_mem_ps(r1,r0,p[28],0x000000f0);
    r2 = _mm_load_ss(&p[38]);
    _mv_insert_mem_ps(r3,r2,p[48],0x0000001c);
    _mv_insert_mem_ps(r4,r2,p[58],0x0000000e);
    _mv_insert_mem_ps(r5,r4,p[68],0x0000001c);
    r6 = _mm_movelh_ps(r3,r5);
    output = _mm256_set_m128(r6,r1);
    DO_NOT_TOUCH(output);
}
    
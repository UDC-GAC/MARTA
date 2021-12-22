#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [50, 49, 39, 29, 28, 27, 17, 16] [1, 0, 0, 1, 1, 0, 1] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6;
    __m256 output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(-1,-1,-1,-1));
    _mv_insert_mem_ps(r1,r0,p[27],0x000000a8);
    _mv_insert_mem_ps(r2,r1,p[28],0x00000070);
    r3 = _mm_load_ss(&p[29]);
    _mv_insert_mem_ps(r4,r3,p[39],0x00000014);
    _mv_insert_mem_ps(r5,r4,p[49],0x000000e0);
    _mv_insert_mem_ps(r6,r5,p[50],0x00000070);
    output = _mm256_set_m128(r6,r2);
    DO_NOT_TOUCH(output);
}
    
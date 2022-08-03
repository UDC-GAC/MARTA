#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 39, 38, 37, 27, 26, 16] [1, 1, 0, 1, 0] (float)
    __m128 r0, r1, r2, r3, r4;
    __m256 output;
    r0 = _mm_load_ss(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[26],0x00000014);
    _mv_insert_mem_ps(r2,r1,p[27],0x00000028);
    _mv_insert_mem_ps(r3,r2,p[37],0x00000030);
    r4 = _mm_maskload_ps(&p[38],_mm_set_epi32(0,0,-1,-1));
    output = _mm256_set_m128(r4,r3);
    DO_NOT_TOUCH(output);
}
    
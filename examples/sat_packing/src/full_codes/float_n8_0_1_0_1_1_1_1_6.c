#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [41, 31, 30, 20, 19, 18, 17, 16] [0, 1, 0, 1, 1, 1, 1] (float)
    __m128 r0, r1, r2, r3, r4;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    r1 = _mm_maskload_ps(&p[20],_mm_set_epi32(-1,0,-1,-1));
    _mv_insert_mem_ps(r2,r1,p[30],0x0000001c);
    _mv_insert_mem_ps(r3,r2,p[31],0x000000e8);
    _mv_insert_mem_ps(r4,r3,p[41],0x00000030);
    output = _mm256_set_m128(r4,r0);
    DO_NOT_TOUCH(output);
}
    
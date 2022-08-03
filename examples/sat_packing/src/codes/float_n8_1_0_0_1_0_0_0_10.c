#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [68, 67, 57, 47, 46, 36, 26, 16] [1, 0, 0, 1, 0, 0, 0] (float)
    __m128 r0, r1, r2, r3, r4, r5, r6, r7;
    __m256 output;
    r0 = _mm_load_ss(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[26],0x00000014);
    _mv_insert_mem_ps(r2,r0,p[36],0x0000008c);
    _mv_insert_mem_ps(r3,r2,p[46],0x0000005c);
    r4 = _mm_movelh_ps(r1,r3);
    r5 = _mm_maskload_ps(&p[47],_mm_set_epi32(-1,-1,0,-1));
    _mv_insert_mem_ps(r6,r5,p[57],0x00000054);
    r7 = _mm_loadh_pi(r6,&p[67]);
    output = _mm256_set_m128(r7,r4);
    DO_NOT_TOUCH(output);
}
    
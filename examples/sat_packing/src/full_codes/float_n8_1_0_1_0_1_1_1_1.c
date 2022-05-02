#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [41, 40, 30, 29, 19, 18, 17, 16] [1, 0, 1, 0, 1, 1, 1] (float)
    __m128 r0, r1, r2, r3;
    __m256 output;
    r0 = _mm_maskload_ps(&p[16],_mm_set_epi32(-1,-1,-1,-1));
    r1 = _mm_loadl_pi(_mm_set_ps(0,0,0,0),&p[29]);
    _mv_insert_mem_ps(r2,r1,p[40],0x00000028);
    _mv_insert_mem_ps(r3,r2,p[41],0x00000030);
    output = _mm256_set_m128(r3,r0);
    DO_NOT_TOUCH(output);
}
    
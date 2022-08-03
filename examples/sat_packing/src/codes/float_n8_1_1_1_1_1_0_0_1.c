#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [41, 40, 39, 38, 37, 36, 26, 16] [1, 1, 1, 1, 1, 0, 0] (float)
    __m128 r0, r1, r2, r3;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[26],0x00000010);
    r2 = _mm_loadh_pi(r1,&p[36]);
    r3 = _mm_loadu_ps(&p[38]);
    output = _mm256_set_m128(r3,r2);
    DO_NOT_TOUCH(output);
}
    
#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [59, 49, 39, 29, 19, 18, 17, 16] [0, 0, 0, 0, 1, 1, 1] (float)
    __m128 r0, r1, r2, r3, r4, r5;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    r1 = _mm_load_ss(&p[29]);
    _mv_insert_mem_ps(r2,r1,p[39],0x0000009c);
    _mv_insert_mem_ps(r3,r1,p[49],0x0000000a);
    _mv_insert_mem_ps(r4,r3,p[59],0x0000009c);
    r5 = _mm_movelh_ps(r2,r4);
    output = _mm256_set_m128(r5,r0);
    DO_NOT_TOUCH(output);
}
    
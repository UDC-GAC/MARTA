#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 30, 20, 19, 18, 17, 16] [0, 1, 1, 1, 1] (float)
    __m128 r0, r1, r2;
    __m256 output;
    r0 = _mm_loadu_ps(&p[16]);
    r1 = _mm_load_ss(&p[20]);
    _mv_insert_mem_ps(r2,r1,p[30],0x000000dc);
    output = _mm256_set_m128(r2,r0);
    DO_NOT_TOUCH(output);
}
    
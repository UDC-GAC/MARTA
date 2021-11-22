#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [37, 27, 26, 16] [0, 1, 0] (float)
    __m128 r0, r1, r2, output;
    r0 = _mm_loadu_ps(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[26],0x0000001c);
    _mv_insert_mem_ps(r2,r1,p[27],0x00000028);
    _mv_insert_mem_ps(output,r2,p[37],0x00000070);
    DO_NOT_TOUCH(output);
}
    
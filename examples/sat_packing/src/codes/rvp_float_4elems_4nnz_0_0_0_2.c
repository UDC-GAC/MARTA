#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [46, 36, 26, 16] [0, 0, 0] (float)
    __m128 r0, r1, r2, r3, output;
    r0 = _mm_load_ss(&p[16]);
    _mv_insert_mem_ps(r1,r0,p[26],0x0000005c);
    _mv_insert_mem_ps(r2,r0,p[36],0x0000004e);
    _mv_insert_mem_ps(r3,r2,p[46],0x0000001c);
    output = _mm_movelh_ps(r1,r3);
    DO_NOT_TOUCH(output);
}
    
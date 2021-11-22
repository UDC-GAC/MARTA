#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 0, 26, 16] [0] (float)
    __m128 r0, output;
    r0 = _mm_load_ss(&p[16]);
    _mv_insert_mem_ps(output,r0,p[26],0x0000009c);
    DO_NOT_TOUCH(output);
}
    
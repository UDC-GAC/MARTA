#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [37, 27, 17, 16] [0, 0, 1] (float)
    __m128 r0, r1, output;
    r0 = _mm_loadl_pi(_mm_set_ps(0,0,0,0),&p[16]);
    _mv_insert_mem_ps(r1,r0,p[27],0x00000028);
    _mv_insert_mem_ps(output,r1,p[37],0x00000030);
    DO_NOT_TOUCH(output);
}
    
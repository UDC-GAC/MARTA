#include "macveth_api.h"
#include "marta_wrapper.h"
#include <immintrin.h>

static inline void kernel(float *restrict p) {
    // [0, 27, 17, 16] [0, 1] (float)
    __m128 r0, r1, output;
    r0 = _mm_loadl_pi(_mm_set_ps(0,0,0,0),&p[16]);
    r1 = _mm_loadh_pi(r0,&p[17]);
    _mv_insert_mem_ps(output,r1,p[27],0x00000028);
    DO_NOT_TOUCH(output);
}
    
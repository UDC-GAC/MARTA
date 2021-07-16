#include "kernel.h"

P_INLINE void kernel(DATA_TYPE a, DATA_TYPE b, DATA_TYPE c) {
    a[0] += b[2] * c[4];
    a[2] += b[2] * c[4];
    a[4] += b[2] * c[4];
    a[3] += b[2] * c[4];
}
#ifndef _MMV_H
#define _MMV_H

#ifndef restrict
#define restrict __restrict
#endif

#ifndef DATA_TYPE
#define DATA_TYPE float
#endif

#ifndef I0
#define I0 0
#endif

#ifndef N
#define N 1024
#endif

#ifndef STEP_I
#define STEP_I 0
#endif

#ifndef J0
#define J0 0
#endif

#ifndef M
#define M 1024
#endif

#ifndef STEP_J
#define STEP_J 0
#endif

void kernel_mmv(DATA_TYPE *restrict A, DATA_TYPE *restrict x,
                DATA_TYPE *restrict y);

#endif
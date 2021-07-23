#include "mmv.h"

void kernel_mmv(DATA_TYPE *restrict A, DATA_TYPE *restrict x,
                DATA_TYPE *restrict y)
{
  int i, j;
  for (i = I0; i < I0 + N; i += STEP_I) {
    for (j = J0; j < J0 + M; j += STEP_J) {
      y[i] = y[i] + A[i*(I0+N) + j] * x[j];
    }
  }
}

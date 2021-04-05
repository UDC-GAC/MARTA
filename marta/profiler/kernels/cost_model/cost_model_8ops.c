#ifndef X_ORIG
#define X_ORIG 0
#endif

#ifndef X_IDX_A
#define X_IDX_A 0
#endif

#ifndef X_IDX_B
#define X_IDX_B 0
#endif

#ifndef X_IDX_C
#define X_IDX_C 0
#endif

#ifndef X_IDX_D
#define X_IDX_D 0
#endif

#ifndef X_IDX_E
#define X_IDX_E 0
#endif

#ifndef X_IDX_F
#define X_IDX_F 0
#endif

#ifndef X_IDX_G
#define X_IDX_G 0
#endif

#ifndef X_IDX_H
#define X_IDX_H 0
#endif

INLINE_PREFIX __m256 cost_model_8ops(DATA_TYPE *restrict x) {

  __m256 tmp;
#include "cost_model_vlen8.c"
  return tmp;
}
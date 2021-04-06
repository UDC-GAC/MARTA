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

#ifndef A_ORIG
#define A_ORIG 0
#endif

#ifndef A_IDX_A
#define A_IDX_A 0
#endif

#ifndef A_IDX_B
#define A_IDX_B 0
#endif

#ifndef A_IDX_C
#define A_IDX_C 0
#endif

#ifndef A_IDX_D
#define A_IDX_D 0
#endif

#ifndef Y_ORIG
#define Y_ORIG 0
#endif

#ifndef Y_IDX_A
#define Y_IDX_A 0
#endif

#ifndef Y_IDX_B
#define Y_IDX_B 0
#endif

#ifndef Y_IDX_C
#define Y_IDX_C 0
#endif

#ifndef Y_IDX_D
#define Y_IDX_D 0
#endif

// For fused domains...
#ifndef X0_ORIG
#define X0_ORIG 0
#endif

#ifndef X0_IDX_A
#define X0_IDX_A 0
#endif

#ifndef X0_IDX_B
#define X0_IDX_B 0
#endif

#ifndef X0_IDX_C
#define X0_IDX_C 0
#endif

#ifndef X0_IDX_D
#define X0_IDX_D 0
#endif

#ifndef X1_ORIG
#define X1_ORIG 0
#endif

#ifndef X1_IDX_A
#define X1_IDX_A 0
#endif

#ifndef X1_IDX_B
#define X1_IDX_B 0
#endif

#ifndef X1_IDX_C
#define X1_IDX_C 0
#endif

#ifndef X1_IDX_D
#define X1_IDX_D 0
#endif

#include "cost_model_x_parts.c"

#include "cost_model_fused.c"

INLINE_PREFIX __m128 cost_model_x(DATA_TYPE *restrict x) {

  __m128 tmp, aux0, aux1;
#include "cost_model_vlen4.c"
  return tmp;
}

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
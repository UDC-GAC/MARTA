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

INLINE_PREFIX __m128 vpack_x(DATA_TYPE *restrict x) {
  __m128 tmp, aux0, aux1;
#include "cost_model_vlen4.c"
  return tmp;
}

INLINE_PREFIX __m128 vpack_A(DATA_TYPE *restrict x) {
  __m128 tmp, aux0, aux1;
#undef X_ORIG
#undef X_IDX_A
#undef X_IDX_B
#undef X_IDX_C
#undef X_IDX_D
#define X_ORIG A_ORIG
#define X_IDX_A A_IDX_A
#define X_IDX_B A_IDX_B
#define X_IDX_C A_IDX_C
#define X_IDX_D A_IDX_D
#include "cost_model_vlen4.c"
  return tmp;
}

INLINE_PREFIX __m128 vpack_y(DATA_TYPE *restrict y) {
  __m128 tmp, aux0, aux1;
#if Y_N == 4
#if (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_B + 1 == Y_IDX_C) &&                    \
    (Y_IDX_C + 1 == Y_IDX_D)
  return _mm_loadu_ps(&y[Y_IDX_A]);
#endif
#endif
#undef X_ORIG
#undef X_IDX_A
#undef X_IDX_B
#undef X_IDX_C
#undef X_IDX_D
#define X_ORIG X_ORIG
#define X_IDX_A X_IDX_A
#define X_IDX_B X_IDX_B
#define X_IDX_C X_IDX_C
#define X_IDX_D X_IDX_D
  return tmp;
}

INLINE_PREFIX void vstore_y(__m128 vstore, DATA_TYPE *restrict y) {
#if Y_N == 4
#if (Y_IDX_A == Y_IDX_B) && (Y_IDX_A == Y_IDX_C) && (Y_IDX_A == Y_IDX_D)
  // Reduction
  __m128 __mv_hi = _mm_movehl_ps(vstore, vstore);
  vstore = _mm_add_ps(vstore, __mv_hi);
  __mv_hi = _mm_shuffle_ps(vstore, vstore, 0b00001110);
  vstore = _mm_add_ps(vstore, __mv_hi);
  y[Y_IDX_A + 4] += vstore[0];
#elif (Y_IDX_A == Y_IDX_B) && (Y_IDX_C == Y_IDX_D)
  __m128 __mv_hi = _mm_shuffle_ps(vstore, vstore, 0b11011000);
  vstore = _mm_add_ps(vstore, __mv_hi);
  y[Y_IDX_A] += vstore[0];
  y[Y_IDX_C] += vstore[2];
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_B + 1 == Y_IDX_C) &&                  \
    (Y_IDX_C + 1 == Y_IDX_D)
  // Simple
  _mm_storeu_ps(&y[Y_IDX_A + 4], vstore);
#else
  // scatter
  y[Y_IDX_A] += vstore[0];
  y[Y_IDX_B] += vstore[1];
  y[Y_IDX_C] += vstore[2];
  y[Y_IDX_D] += vstore[3];
#endif
#elif Y_N == 3
  y[Y_IDX_A] += vstore[0];
  y[Y_IDX_B] += vstore[1];
  y[Y_IDX_C] += vstore[2];
#elif Y_N == 2
  y[Y_IDX_A] += vstore[0];
  y[Y_IDX_B] += vstore[1];
#elif Y_N == 1
  y[Y_IDX_A] += vstore[0];
#endif
}
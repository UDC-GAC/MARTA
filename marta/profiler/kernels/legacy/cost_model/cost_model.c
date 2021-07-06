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

#ifndef A_IDX_E
#define A_IDX_E 0
#endif

#ifndef A_IDX_F
#define A_IDX_F 0
#endif

#ifndef A_IDX_G
#define A_IDX_G 0
#endif

#ifndef A_IDX_H
#define A_IDX_H 0
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

#ifndef Y_IDX_E
#define Y_IDX_E 0
#endif

#ifndef Y_IDX_F
#define Y_IDX_F 0
#endif

#ifndef Y_IDX_G
#define Y_IDX_G 0
#endif

#ifndef Y_IDX_H
#define Y_IDX_H 0
#endif

#ifndef X_N
#define X_N 8
#endif

#ifndef A_N
#define A_N 8
#endif

#ifndef Y_N
#define Y_N 8
#endif

#ifndef Y_OPERAND
#define Y_OPERAND 0
#endif

INLINE_PREFIX __m256 vpack_x_256(DATA_TYPE *restrict x) {
  __m256 tmp, aux0, aux1;
#undef Y_OPERAND
#define Y_OPERAND 0
#include "cost_model_vlen8.c"
  return tmp;
}

INLINE_PREFIX __m256 vpack_A_256(DATA_TYPE *restrict x) {
  __m256 tmp, aux0, aux1;
#undef X_ORIG
#undef X_IDX_A
#undef X_IDX_B
#undef X_IDX_C
#undef X_IDX_D
#undef X_IDX_E
#undef X_IDX_F
#undef X_IDX_G
#undef X_IDX_H
#undef Y_OPERAND
#define Y_OPERAND 0
#define X_ORIG A_ORIG
#define X_IDX_A A_IDX_A
#define X_IDX_B A_IDX_B
#define X_IDX_C A_IDX_C
#define X_IDX_D A_IDX_D
#define X_IDX_E A_IDX_E
#define X_IDX_F A_IDX_F
#define X_IDX_G A_IDX_G
#define X_IDX_H A_IDX_H
#include "cost_model_vlen8.c"
  return tmp;
}

INLINE_PREFIX __m256 vpack_y_256(DATA_TYPE *restrict x) {
  __m256 tmp, aux0, aux1;
#undef Y_OPERAND
#undef X_ORIG
#undef X_IDX_A
#undef X_IDX_B
#undef X_IDX_C
#undef X_IDX_D
#undef X_IDX_E
#undef X_IDX_F
#undef X_IDX_G
#undef X_IDX_H
#define Y_OPERAND 1
#define X_ORIG Y_ORIG
#define X_IDX_A Y_IDX_A
#define X_IDX_B Y_IDX_B
#define X_IDX_C Y_IDX_C
#define X_IDX_D Y_IDX_D
#define X_IDX_E Y_IDX_E
#define X_IDX_F Y_IDX_F
#define X_IDX_G Y_IDX_G
#define X_IDX_H Y_IDX_H
#include "cost_model_vlen8.c"
  return tmp;
}

INLINE_PREFIX void vstore_y_256(__m256 vstore, DATA_TYPE *restrict y) {
#if Y_N == 8
#if (Y_IDX_A == Y_IDX_B) && (Y_IDX_A == Y_IDX_C) && (Y_IDX_A == Y_IDX_D) &&    \
    (Y_IDX_A == Y_IDX_E) && (Y_IDX_A == Y_IDX_F) && (Y_IDX_A == Y_IDX_G) &&    \
    (Y_IDX_A == Y_IDX_H)
  // Reduction
  __m128 __mv_lo256 = _mm256_castps256_ps128(vstore);
  __m128 __mv_hi256 = _mm256_extractf128_ps(vstore, 0x1);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  __mv_hi256 = _mm_movehl_ps(__mv_lo256, __mv_lo256);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  __mv_hi256 = _mm_shuffle_ps(__mv_lo256, __mv_lo256, 0b00001110);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  y[Y_IDX_A] += __mv_lo256[0];
#elif (Y_IDX_A == Y_IDX_B) && (Y_IDX_A == Y_IDX_C) && (Y_IDX_A == Y_IDX_D) &&  \
    (Y_IDX_E == Y_IDX_F) && (Y_IDX_E == Y_IDX_G) && (Y_IDX_E == Y_IDX_H)
  // Reduction
  __m256 __tmp0 = _mm256_permute_ps(vstore, 0b00001110);
  __m256 __tmp1 = _mm256_add_ps(vstore, __tmp0);
  //__m256 __tmp2 = _mm256_permute_ps(__tmp1, 0b00000001);
  __m256 __tmp2 = _mm256_shuffle_ps(__tmp1, __tmp1, 0b00000001);
  __m256 __tmp3 = _mm256_add_ps(vstore, __tmp2);
  y[Y_IDX_A] += __tmp3[0];
  y[Y_IDX_E] += __tmp3[4];
#elif (Y_IDX_A == Y_IDX_B) && (Y_IDX_C == Y_IDX_D) && (Y_IDX_E == Y_IDX_F) &&  \
    (Y_IDX_G == Y_IDX_H)
  // Reduction
  __m256 __tmp0 = _mm256_permute_ps(vstore, 0b00110001);
  __m256 __tmp1 = _mm256_add_ps(vstore, __tmp0);
  y[Y_IDX_A] += __tmp1[0];
  y[Y_IDX_C] += __tmp1[2];
  y[Y_IDX_E] += __tmp1[4];
  y[Y_IDX_G] += __tmp1[6];
#elif (Y_IDX_A == Y_IDX_B) && (Y_IDX_A == Y_IDX_C) && (Y_IDX_A == Y_IDX_D)
  __m128 __mv_hi = _mm_movehl_ps(_mm256_castps256_ps128(vstore),
                                 _mm256_castps256_ps128(vstore));
  __m128 __tmp = _mm_add_ps(_mm256_castps256_ps128(vstore), __mv_hi);
  __mv_hi = _mm_shuffle_ps(__tmp, __tmp, 0b00001110);
  __tmp = _mm_add_ps(__tmp, __mv_hi);
  y[Y_IDX_A] += __tmp[0];
  _mm_i32scatter_ps(&y[Y_IDX_A],
                    _mm_set_epi32(X_IDX_H - X_IDX_A, X_IDX_G - X_IDX_A,
                                  X_IDX_F - X_IDX_A, X_IDX_E - X_IDX_A),
                    _mm256_extractf128_ps(vstore, 0x1), 4);
#elif (Y_IDX_A == Y_IDX_B) && (Y_IDX_C == Y_IDX_D) &&                          \
    (Y_IDX_E + 1 == Y_IDX_F) && (Y_IDX_G + 1 == Y_IDX_H)
  __m256 __tmp0 = _mm256_permute_ps(vstore, 0b00110001);
  __m256 __tmp1 = _mm256_add_ps(vstore, __tmp0);
  y[Y_IDX_A] += __tmp1[0];
  y[Y_IDX_C] += __tmp1[2];
  __m128 storeaux = _mm256_extractf128_ps(vstore, 0x1);
  _mm_storel_pi(&y[Y_IDX_E], storeaux);
  _mm_storeh_pi(&y[Y_IDX_G], storeaux);
#elif (Y_IDX_A == Y_IDX_B) && (Y_IDX_C == Y_IDX_D)
  __m256 __tmp0 = _mm256_permute_ps(vstore, 0b00110001);
  __m256 __tmp1 = _mm256_add_ps(vstore, __tmp0);
  y[Y_IDX_A] += __tmp1[0];
  y[Y_IDX_C] += __tmp1[2];
  _mm_i32scatter_ps(&y[Y_IDX_A],
                    _mm_set_epi32(X_IDX_H - X_IDX_A, X_IDX_G - X_IDX_A,
                                  X_IDX_F - X_IDX_A, X_IDX_E - X_IDX_A),
                    _mm256_extractf128_ps(vstore, 0x1), 4);
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_B + 1 == Y_IDX_C) &&                  \
    (Y_IDX_C + 1 == Y_IDX_D) && (Y_IDX_D + 1 == Y_IDX_E) &&                    \
    (Y_IDX_E + 1 == Y_IDX_F) && (Y_IDX_F + 1 == Y_IDX_G) &&                    \
    (Y_IDX_G + 1 == Y_IDX_H)
  // Simple
  _mm256_storeu_ps(&y[Y_IDX_A], vstore);
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_B + 1 == Y_IDX_C) &&                  \
    (Y_IDX_C + 1 == Y_IDX_D) && (Y_IDX_E + 1 == Y_IDX_F) &&                    \
    (Y_IDX_F + 1 == Y_IDX_G) && (Y_IDX_G + 1 == Y_IDX_H)
  _mm_storeu_ps(&y[Y_IDX_A], _mm256_castps256_ps128(vstore));
  _mm_storeu_ps(&y[Y_IDX_A], _mm256_extractf128_ps(vstore, 0x1));
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_C + 1 == Y_IDX_D) &&                  \
    (Y_IDX_E + 1 == Y_IDX_F) && (Y_IDX_G + 1 == Y_IDX_H)
  __m128 storeaux = _mm256_extractf128_ps(vstore, 0x1);
  _mm_storel_pi(&y[Y_IDX_A], _mm256_castps256_ps128(vstore));
  _mm_storeh_pi(&y[Y_IDX_C], _mm256_castps256_ps128(vstore));
  _mm_storel_pi(&y[Y_IDX_E], storeaux);
  _mm_storeh_pi(&y[Y_IDX_G], storeaux);
#else
  // scatter
  // y[Y_IDX_A] += vstore[0];
  // y[Y_IDX_B] += vstore[1];
  // y[Y_IDX_C] += vstore[2];
  // y[Y_IDX_D] += vstore[3];
  // y[Y_IDX_E] += vstore[4];
  // y[Y_IDX_F] += vstore[5];
  // y[Y_IDX_G] += vstore[6];
  // y[Y_IDX_H] += vstore[7];
  _mm256_i32scatter_ps(&y[Y_IDX_A],
                       _mm256_set_epi32(X_IDX_H - X_IDX_A, X_IDX_G - X_IDX_A,
                                        X_IDX_F - X_IDX_A, X_IDX_E - X_IDX_A,
                                        X_IDX_D - X_IDX_A, X_IDX_C - X_IDX_A,
                                        X_IDX_B - X_IDX_A, X_IDX_A),
                       vstore, 4);
#endif
#elif Y_N == 7
#if (Y_IDX_A == Y_IDX_B) && (Y_IDX_A == Y_IDX_C) && (Y_IDX_A == Y_IDX_D) &&    \
    (Y_IDX_A == Y_IDX_E) && (Y_IDX_A == Y_IDX_F) && (Y_IDX_A == Y_IDX_G)
  // Reduction
  __m128 __mv_lo256 = _mm256_castps256_ps128(vstore);
  __m128 __mv_hi256 = _mm256_extractf128_ps(vstore, 0x1);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  __mv_hi256 = _mm_movehl_ps(__mv_lo256, __mv_lo256);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  __mv_hi256 = _mm_shuffle_ps(__mv_lo256, __mv_lo256, 0b00001110);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  y[Y_IDX_A] += __mv_lo256[0];
#elif (Y_IDX_A == Y_IDX_B) && (Y_IDX_A == Y_IDX_C) && (Y_IDX_A == Y_IDX_D) &&  \
    (Y_IDX_E == Y_IDX_F) && (Y_IDX_E == Y_IDX_G)
  // Reduction
  __m256 __tmp0 = _mm256_permute_ps(vstore, 0b00001110);
  __m256 __tmp1 = _mm256_add_ps(vstore, __tmp0);
  __m256 __tmp2 = _mm256_permute_ps(__tmp1, 0b00000001);
  __m256 __tmp3 = _mm256_add_ps(vstore, __tmp2);
  y[Y_IDX_A] += __tmp3[0];
  y[Y_IDX_E] += __tmp3[4];
#elif (Y_IDX_A == Y_IDX_B) && (Y_IDX_C == Y_IDX_D) && (Y_IDX_E == Y_IDX_F)
  // Reduction
  __m256 __tmp0 = _mm256_permute_ps(vstore, 0b00110001);
  __m256 __tmp1 = _mm256_add_ps(vstore, __tmp0);
  y[Y_IDX_A] += __tmp1[0];
  y[Y_IDX_C] += __tmp1[2];
  y[Y_IDX_E] += __tmp1[4];
  y[Y_IDX_G] += __tmp1[6];
#elif (Y_IDX_A == Y_IDX_B) && (Y_IDX_A == Y_IDX_C) && (Y_IDX_A == Y_IDX_D)
  __m128 __mv_hi = _mm_movehl_ps(_mm256_castps256_ps128(vstore),
                                 _mm256_castps256_ps128(vstore));
  __m128 __tmp = _mm_add_ps(_mm256_castps256_ps128(vstore), __mv_hi);
  __mv_hi = _mm_shuffle_ps(__tmp, __tmp, 0b00001110);
  __tmp = _mm_add_ps(__tmp, __mv_hi);
  y[Y_IDX_A] += __tmp[0];
  _mm_mask_i32scatter_ps(&y[Y_IDX_A], 0b00000111,
                         _mm_set_epi32(X_IDX_H - X_IDX_A, X_IDX_G - X_IDX_A,
                                       X_IDX_F - X_IDX_A, X_IDX_E - X_IDX_A),
                         _mm256_extractf128_ps(vstore, 0x1), 4);
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_B + 1 == Y_IDX_C) &&                  \
    (Y_IDX_C + 1 == Y_IDX_D) && (Y_IDX_D + 1 == Y_IDX_E) &&                    \
    (Y_IDX_E + 1 == Y_IDX_F) && (Y_IDX_F + 1 == Y_IDX_G)
  // Simple
  _mm256_maskstore_ps(&y[Y_IDX_A],
                      _mm256_set_epi32(0, -1, -1, -1, -1, -1, -1, -1), vstore);
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_B + 1 == Y_IDX_C) &&                  \
    (Y_IDX_C + 1 == Y_IDX_D) && (Y_IDX_E + 1 == Y_IDX_F) &&                    \
    (Y_IDX_F + 1 == Y_IDX_G)
  _mm_storeu_ps(&y[Y_IDX_A], _mm256_castps256_ps128(vstore));
  _mm_maskstore_ps(&y[Y_IDX_A], _mm_set_epi32(0, -1, -1, -1),
                   _mm256_extractf128_ps(vstore, 0x1));
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_C + 1 == Y_IDX_D) &&                  \
    (Y_IDX_E + 1 == Y_IDX_F) && (Y_IDX_G + 1 == Y_IDX_H)
  __m128 storeaux = _mm256_extractf128_ps(vstore, 0x1);
  _mm_storel_pi(&y[Y_IDX_A], _mm256_castps256_ps128(vstore));
  _mm_storeh_pi(&y[Y_IDX_C], _mm256_castps256_ps128(vstore));
  _mm_storel_pi(&y[Y_IDX_G], storeaux);
  _mm_storeh_pi(&y[Y_IDX_H], storeaux);
#else
  // scatter
  // y[Y_IDX_A] += vstore[0];
  // y[Y_IDX_B] += vstore[1];
  // y[Y_IDX_C] += vstore[2];
  // y[Y_IDX_D] += vstore[3];
  // y[Y_IDX_E] += vstore[4];
  // y[Y_IDX_F] += vstore[5];
  // y[Y_IDX_G] += vstore[6];
  _mm256_mask_i32scatter_ps(
      &y[Y_IDX_A], 0b01111111,
      _mm256_set_epi32(X_IDX_H - X_IDX_A, X_IDX_G - X_IDX_A, X_IDX_F - X_IDX_A,
                       X_IDX_E - X_IDX_A, X_IDX_D - X_IDX_A, X_IDX_C - X_IDX_A,
                       X_IDX_B - X_IDX_A, X_IDX_A),
      vstore, 4);
#endif
#elif Y_N == 6
#if (Y_IDX_A == Y_IDX_B) && (Y_IDX_A == Y_IDX_C) && (Y_IDX_A == Y_IDX_D) &&    \
    (Y_IDX_A == Y_IDX_E) && (Y_IDX_A == Y_IDX_F)
  // Reduction
  __m128 __mv_lo256 = _mm256_castps256_ps128(vstore);
  __m128 __mv_hi256 = _mm256_extractf128_ps(vstore, 0x1);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  __mv_hi256 = _mm_movehl_ps(__mv_lo256, __mv_lo256);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  __mv_hi256 = _mm_shuffle_ps(__mv_lo256, __mv_lo256, 0b00001110);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  y[Y_IDX_A] += __mv_lo256[0];
#elif (Y_IDX_A == Y_IDX_B) && (Y_IDX_A == Y_IDX_C) && (Y_IDX_A == Y_IDX_D)
  __m128 __mv_hi = _mm_movehl_ps(_mm256_castps256_ps128(vstore),
                                 _mm256_castps256_ps128(vstore));
  __m128 __tmp = _mm_add_ps(_mm256_castps256_ps128(vstore), __mv_hi);
  __mv_hi = _mm_shuffle_ps(__tmp, __tmp, 0b00001110);
  __tmp = _mm_add_ps(__tmp, __mv_hi);
  y[Y_IDX_A] = __tmp[0];
  _mm_mask_i32scatter_ps(&y[Y_IDX_A], 0b00000011,
                         _mm_set_epi32(X_IDX_H - X_IDX_A, X_IDX_G - X_IDX_A,
                                       X_IDX_F - X_IDX_A, X_IDX_E - X_IDX_A),
                         _mm256_extractf128_ps(vstore, 0x1), 4);
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_B + 1 == Y_IDX_C) &&                  \
    (Y_IDX_C + 1 == Y_IDX_D) && (Y_IDX_D + 1 == Y_IDX_E) &&                    \
    (Y_IDX_E + 1 == Y_IDX_F)
  // Simple
  _mm256_maskstore_ps(&y[Y_IDX_A],
                      _mm256_set_epi32(0, 0, -1, -1, -1, -1, -1, -1), vstore);
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_B + 1 == Y_IDX_C) &&                  \
    (Y_IDX_C + 1 == Y_IDX_D) && (Y_IDX_E + 1 == Y_IDX_F)
  _mm_storeu_ps(&y[Y_IDX_A], _mm256_castps256_ps128(vstore));
  _mm_storel_pi(&y[Y_IDX_A], _mm256_extractf128_ps(vstore, 0x1));
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_C + 1 == Y_IDX_D) &&                  \
    (Y_IDX_E + 1 == Y_IDX_F)
  _mm_storel_pi(&y[Y_IDX_A], _mm256_castps256_ps128(vstore));
  _mm_storeh_pi(&y[Y_IDX_C], _mm256_castps256_ps128(vstore));
  _mm_storel_pi(&y[Y_IDX_G], _mm256_extractf128_ps(vstore, 0x1));
#else
  // scatter
  // y[Y_IDX_A] += vstore[0];
  // y[Y_IDX_B] += vstore[1];
  // y[Y_IDX_C] += vstore[2];
  // y[Y_IDX_D] += vstore[3];
  // y[Y_IDX_E] += vstore[4];
  // y[Y_IDX_F] += vstore[5];
  _mm256_mask_i32scatter_ps(
      &y[Y_IDX_A], 0b00111111,
      _mm256_set_epi32(X_IDX_H - X_IDX_A, X_IDX_G - X_IDX_A, X_IDX_F - X_IDX_A,
                       X_IDX_E - X_IDX_A, X_IDX_D - X_IDX_A, X_IDX_C - X_IDX_A,
                       X_IDX_B - X_IDX_A, X_IDX_A),
      vstore, 4);
#endif
#elif Y_N == 5
#if (Y_IDX_A == Y_IDX_B) && (Y_IDX_A == Y_IDX_C) && (Y_IDX_A == Y_IDX_D) &&    \
    (Y_IDX_A == Y_IDX_E)
  // Reduction
  __m128 __mv_lo256 = _mm256_castps256_ps128(vstore);
  __m128 __mv_hi256 = _mm256_extractf128_ps(vstore, 0x1);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  __mv_hi256 = _mm_movehl_ps(__mv_lo256, __mv_lo256);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  __mv_hi256 = _mm_shuffle_ps(__mv_lo256, __mv_lo256, 0b00001110);
  __mv_lo256 = _mm_add_ps(__mv_lo256, __mv_hi256);
  y[Y_IDX_A] += __mv_lo256[0];
#elif (Y_IDX_A == Y_IDX_B) && (Y_IDX_A == Y_IDX_C) && (Y_IDX_A == Y_IDX_D)
  __m128 __mv_hi = _mm_movehl_ps(_mm256_castps256_ps128(vstore),
                                 _mm256_castps256_ps128(vstore));
  __m128 __tmp = _mm_add_ps(_mm256_castps256_ps128(vstore), __mv_hi);
  __mv_hi = _mm_shuffle_ps(__tmp, __tmp, 0b00001110);
  __tmp = _mm_add_ps(__tmp, __mv_hi);
  y[Y_IDX_A] = __tmp[0];
  y[Y_IDX_E] = vstore[4];
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_B + 1 == Y_IDX_C) &&                  \
    (Y_IDX_C + 1 == Y_IDX_D) && (Y_IDX_D + 1 == Y_IDX_E)
  // Simple
  _mm256_maskstore_ps(&y[Y_IDX_A],
                      _mm256_set_epi32(0, 0, 0, -1, -1, -1, -1, -1), vstore);
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_B + 1 == Y_IDX_C) &&                  \
    (Y_IDX_C + 1 == Y_IDX_D)
  _mm_storeu_ps(&y[Y_IDX_A], _mm256_castps256_ps128(vstore));
  _mm_storel_pi(&y[Y_IDX_A], _mm256_extractf128_ps(vstore, 0x1));
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_C + 1 == Y_IDX_D)
  _mm_storel_pi(&y[Y_IDX_A], _mm256_castps256_ps128(vstore));
  _mm_storeh_pi(&y[Y_IDX_C], _mm256_castps256_ps128(vstore));
  _mm_store_ss(&y[Y_IDX_G], _mm256_extractf128_ps(vstore, 0x1));
#else
  // scatter
  // y[Y_IDX_A] += vstore[0];
  // y[Y_IDX_B] += vstore[1];
  // y[Y_IDX_C] += vstore[2];
  // y[Y_IDX_D] += vstore[3];
  // y[Y_IDX_E] += vstore[4];
  _mm256_mask_i32scatter_ps(
      &y[Y_IDX_A], 0b00011111,
      _mm256_set_epi32(X_IDX_H - X_IDX_A, X_IDX_G - X_IDX_A, X_IDX_F - X_IDX_A,
                       X_IDX_E - X_IDX_A, X_IDX_D - X_IDX_A, X_IDX_C - X_IDX_A,
                       X_IDX_B - X_IDX_A, X_IDX_A),
      vstore, 4);
#endif
#endif
}

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

INLINE_PREFIX __m128 vpack_y(DATA_TYPE *restrict x) {
  __m128 tmp, aux0, aux1;
#if (Y_IDX_A != Y_IDX_B) && (Y_IDX_C != Y_IDX_D)
#undef X_ORIG
#undef X_IDX_A
#undef X_IDX_B
#undef X_IDX_C
#undef X_IDX_D
#define X_ORIG Y_ORIG
#define X_IDX_A Y_IDX_A
#define X_IDX_B Y_IDX_B
#define X_IDX_C Y_IDX_C
#define X_IDX_D Y_IDX_D
#include "cost_model_vlen4.c"
#endif
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
  y[Y_IDX_A] += vstore[0];
#elif (Y_IDX_A == Y_IDX_B) && (Y_IDX_C == Y_IDX_D)
  __m128 __mv_hi = _mm_shuffle_ps(vstore, vstore, 0b11011000);
  vstore = _mm_add_ps(vstore, __mv_hi);
  y[Y_IDX_A] += vstore[0];
  y[Y_IDX_C] += vstore[2];
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_B + 1 == Y_IDX_C) &&                  \
    (Y_IDX_C + 1 == Y_IDX_D)
  // Simple
  _mm_storeu_ps(&y[Y_IDX_A], vstore);
#elif (Y_IDX_A + 1 == Y_IDX_B) && (Y_IDX_C + 1 == Y_IDX_D)
  _mm_storel_pi(&y[Y_IDX_A], vstore);
  _mm_storeh_pi(&y[Y_IDX_A], vstore);
#else
  // scatter
  y[Y_IDX_A] += vstore[0];
  y[Y_IDX_B] += vstore[1];
  y[Y_IDX_C] += vstore[2];
  y[Y_IDX_D] += vstore[3];
#endif
#elif Y_N == 3
#if (Y_IDX_A == Y_IDX_B) && (Y_IDX_A == Y_IDX_C)
  y[Y_IDX_A] += vstore[0] + vstore[1] + vstore[2];
#elif (Y_IDX_A == Y_IDX_B) && (Y_IDX_A != Y_IDX_C)
  y[Y_IDX_A] += vstore[0] + vstore[1];
  y[Y_IDX_C] += vstore[2];
#elif (Y_IDX_A != Y_IDX_B) && (Y_IDX_B == Y_IDX_C)
  y[Y_IDX_A] += vstore[0];
  y[Y_IDX_B] += vstore[1] + vstore[2];
#else
  y[Y_IDX_A] += vstore[0];
  y[Y_IDX_B] += vstore[1];
  y[Y_IDX_C] += vstore[2];
#endif
#elif Y_N == 2
#if (Y_IDX_A == Y_IDX_B)
  y[Y_IDX_A] += vstore[0] + vstore[1];
#else
  y[Y_IDX_A] += vstore[0];
  y[Y_IDX_B] += vstore[1];
#endif
#elif Y_N == 1
  y[Y_IDX_A] += vstore[0];
#endif
}
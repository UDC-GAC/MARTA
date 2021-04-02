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

INLINE_PREFIX __m128 cost_model_x_high(DATA_TYPE *restrict x) {
  __m128 tmp, aux0, aux1;
  // 4-elements
#if (X1_IDX_A + 1 == X1_IDX_B) && (X1_IDX_B + 1 == X1_IDX_C) &&                \
    (X1_IDX_C + 1 == X1_IDX_D)
  // e.g. [0,1,2,3]
  tmp = _mm_loadu_ps(&x[X1_ORIG + X1_IDX_A]);
#elif (X1_IDX_A + 1 == X1_IDX_B) && (X1_IDX_C + 1 == X1_IDX_D)
  // e.g. [0,1,5,6]
  aux0 = _mm_loadl_pi(aux1, &x[X1_ORIG + X1_IDX_A]);
  tmp = _mm_loadh_pi(aux0, &x[X1_ORIG + X1_IDX_C]);
#elif (X1_IDX_A + 1 == X1_IDX_B) && (X1_IDX_B + 1 == X1_IDX_C) &&              \
    (X1_IDX_C + 1 != X1_IDX_D)
  // e.g. [0,1,2,7]
  aux1 = _mm_maskload_ps(&x[X1_ORIG + X1_IDX_A], _mm_set_epi32(0, -1, -1, -1));
  aux0 = _mm_load_ss(&x[X1_ORIG + X1_IDX_D]);
  tmp = _mm_insert_ps(aux1, aux0, 0b00110000);
#elif (X1_IDX_A + 1 != X1_IDX_B) && (X1_IDX_B + 1 != X1_IDX_C) &&              \
    (X1_IDX_C + 1 == X1_IDX_D)
  tmp = _mm_loadh_pi(tmp, &x[X1_ORIG + X1_IDX_C]);
  aux0 = _mm_load_ss(&x[X1_ORIG + X1_IDX_A]);
  tmp = _mm_insert_ps(tmp, aux0, 0b00000000);
  aux1 = _mm_load_ss(&x[X1_ORIG + X1_IDX_B]);
  tmp = _mm_insert_ps(tmp, aux1, 0b00010000);
#elif (X1_IDX_A + 1 == X1_IDX_B) && (X1_IDX_B + 1 != X1_IDX_C) &&              \
    (X1_IDX_C + 1 != X1_IDX_D)
  tmp = _mm_loadl_pi(tmp, &x[X1_ORIG + X1_IDX_A]);
  aux0 = _mm_load_ss(&x[X1_ORIG + X1_IDX_C]);
  tmp = _mm_insert_ps(tmp, aux0, 0b00100000);
  aux1 = _mm_load_ss(&x[X1_ORIG + X1_IDX_D]);
  tmp = _mm_insert_ps(tmp, aux1, 0b00110000);
#else
  // e.g. [0,2,4,6]
  tmp = _mm_i32gather_ps(&x[X1_ORIG + X1_IDX_A],
                         _mm_set_epi32(X1_IDX_D - X1_IDX_A, X1_IDX_C - X1_IDX_A,
                                       X1_IDX_B - X1_IDX_A, X1_IDX_A),
                         4);
#endif
  return tmp;
}

INLINE_PREFIX __m128 cost_model_x_low(DATA_TYPE *restrict x) {
  __m128 tmp, aux0, aux1;
  // 4-elements
#if (X0_IDX_A + 1 == X0_IDX_B) && (X0_IDX_B + 1 == X0_IDX_C) &&                \
    (X0_IDX_C + 1 == X0_IDX_D)
  // e.g. [0,1,2,3]
  tmp = _mm_loadu_ps(&x[X0_ORIG + X0_IDX_A]);
#elif (X0_IDX_A + 1 == X0_IDX_B) && (X0_IDX_C + 1 == X0_IDX_D)
  // e.g. [0,1,5,6]
  aux0 = _mm_loadl_pi(aux1, &x[X0_ORIG + X0_IDX_A]);
  tmp = _mm_loadh_pi(aux0, &x[X0_ORIG + X0_IDX_C]);
#elif (X0_IDX_A + 1 == X0_IDX_B) && (X0_IDX_B + 1 == X0_IDX_C) &&              \
    (X0_IDX_C + 1 != X0_IDX_D)
  // e.g. [0,1,2,7]
  aux1 = _mm_maskload_ps(&x[X0_ORIG + X0_IDX_A], _mm_set_epi32(0, -1, -1, -1));
  aux0 = _mm_load_ss(&x[X0_ORIG + X0_IDX_D]);
  tmp = _mm_insert_ps(aux1, aux0, 0b00110000);
#elif (X0_IDX_A + 1 != X0_IDX_B) && (X0_IDX_B + 1 != X0_IDX_C) &&              \
    (X0_IDX_C + 1 == X0_IDX_D)
  tmp = _mm_loadh_pi(tmp, &x[X0_ORIG + X0_IDX_C]);
  aux0 = _mm_load_ss(&x[X0_ORIG + X0_IDX_A]);
  tmp = _mm_insert_ps(tmp, aux0, 0b00000000);
  aux1 = _mm_load_ss(&x[X0_ORIG + X0_IDX_B]);
  tmp = _mm_insert_ps(tmp, aux1, 0b00010000);
#elif (X0_IDX_A + 1 == X0_IDX_B) && (X0_IDX_B + 1 != X0_IDX_C) &&              \
    (X0_IDX_C + 1 != X0_IDX_D)
  tmp = _mm_loadl_pi(tmp, &x[X0_ORIG + X0_IDX_A]);
  aux0 = _mm_load_ss(&x[X0_ORIG + X0_IDX_C]);
  tmp = _mm_insert_ps(tmp, aux0, 0b00100000);
  aux1 = _mm_load_ss(&x[X0_ORIG + X0_IDX_D]);
  tmp = _mm_insert_ps(tmp, aux1, 0b00110000);
#else
  // e.g. [0,2,4,6]
  tmp = _mm_i32gather_ps(&x[X0_ORIG + X0_IDX_A],
                         _mm_set_epi32(X0_IDX_D - X0_IDX_A, X0_IDX_C - X0_IDX_A,
                                       X0_IDX_B - X0_IDX_A, X0_IDX_A),
                         4);
#endif
  return tmp;
}

INLINE_PREFIX __m256 cost_model_fused(DATA_TYPE *restrict x) {
  __m256 res;
  __m128 tmp, aux0, aux1;
#if CL1 == 0
  return _mm256_loadu_ps(&x[X0_ORIG + X0_IDX_A]);
#endif
// #if CL0 == 1 && CL1 == 1
//   return _mm256_insertf128_ps(
//       _mm256_castps128_ps256(_mm_loadu_ps(&x[X0_ORIG + X0_IDX_A])),
//       _mm_loadu_ps(&x[X1_ORIG + X1_IDX_A]), 1);
// #endif
// #if CL0 == 1 && CL1 != 1
//   return _mm256_insertf128_ps(
//       _mm256_castps128_ps256(_mm_loadu_ps(&x[X0_ORIG + X0_IDX_A])),
//       cost_model_x_high(x), 1);
// #endif
#if (CL0 == 4 && CL1 == 4)
  return _mm256_i32gather_ps(
      &x[X0_ORIG + X0_IDX_A],
      _mm256_set_epi32(X1_ORIG + X1_IDX_D - X0_IDX_A - X0_ORIG,
                       X1_ORIG + X1_IDX_C - X0_IDX_A - X0_ORIG,
                       X1_ORIG + X1_IDX_B - X0_IDX_A - X0_ORIG,
                       X1_ORIG + X1_IDX_A - X0_IDX_A - X0_ORIG,
                       X0_IDX_D - X0_IDX_A, X0_ORIG - X0_IDX_A,
                       X0_IDX_B - X0_IDX_A, 0),
      4);
#else
  // return _mm256_insertf128_ps(_mm256_castps128_ps256(cost_model_x_low(x)),
  //                             cost_model_x_high(x), 1);
  return _mm256_set_m128(cost_model_x_high(x), cost_model_x_low(x));

#endif
}

INLINE_PREFIX __m128 cost_model_x(DATA_TYPE *restrict x) {

  __m128 tmp, aux0, aux1;
#if X_N == 4
// 4-elements
#if (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 == X_IDX_C) &&                    \
    (X_IDX_C + 1 == X_IDX_D)
  // e.g. [0,1,2,3]
  tmp = _mm_loadu_ps(&x[X_ORIG + X_IDX_A]);
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_C + 1 == X_IDX_D)
  // e.g. [0,1,5,6]
  aux0 = _mm_loadl_pi(aux1, &x[X_ORIG + X_IDX_A]);
  tmp = _mm_loadh_pi(aux0, &x[X_ORIG + X_IDX_C]);
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 == X_IDX_C) &&                  \
    (X_IDX_C + 1 != X_IDX_D)
  // e.g. [0,1,2,7]
  aux1 = _mm_maskload_ps(&x[X_ORIG + X_IDX_A], _mm_set_epi32(0, -1, -1, -1));
  aux0 = _mm_load_ss(&x[X_ORIG + X_IDX_D]);
  tmp = _mm_insert_ps(aux1, aux0, 0b00110000);
#elif (X_IDX_A + 1 != X_IDX_B) && (X_IDX_B + 1 != X_IDX_C) &&                  \
    (X_IDX_C + 1 == X_IDX_D)
  tmp = _mm_loadh_pi(tmp, &x[X_ORIG + X_IDX_C]);
  aux0 = _mm_load_ss(&x[X_ORIG + X_IDX_A]);
  tmp = _mm_insert_ps(tmp, aux0, 0b00000000);
  aux1 = _mm_load_ss(&x[X_ORIG + X_IDX_B]);
  tmp = _mm_insert_ps(tmp, aux1, 0b00010000);
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 != X_IDX_C) &&                  \
    (X_IDX_C + 1 != X_IDX_D)
  tmp = _mm_loadl_pi(tmp, &x[X_ORIG + X_IDX_A]);
  aux0 = _mm_load_ss(&x[X_ORIG + X_IDX_C]);
  tmp = _mm_insert_ps(tmp, aux0, 0b00100000);
  aux1 = _mm_load_ss(&x[X_ORIG + X_IDX_D]);
  tmp = _mm_insert_ps(tmp, aux1, 0b00110000);
#else
  // e.g. [0,2,4,6]
  tmp = _mm_i32gather_ps(&x[X_ORIG + X_IDX_A],
                         _mm_set_epi32(X_IDX_D - X_IDX_A, X_IDX_C - X_IDX_A,
                                       X_IDX_B - X_IDX_A, X_IDX_A),
                         4);
#endif
#elif X_N == 3
// 3-elements
#if (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 == X_IDX_C)
  // e.g. [0,1,2,x]
  tmp = _mm_maskload_ps(&x[X_ORIG + X_IDX_A], _mm_set_epi32(0, -1, -1, -1));
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 != X_IDX_C)
  // e.g. [0,1,4,x], [0,1,17,x]
  aux0 = _mm_loadl_pi(aux0, &x[X_ORIG + X_IDX_A]);
  tmp = _mm_load_ss(&x[X_ORIG + X_IDX_C]);
  // insert tmp in aux0 in the third position and fourth to zero
  tmp = _mm_insert_ps(aux0, tmp, 0b00101000);
#elif (X_IDX_A + 1 != X_IDX_B) && (X_IDX_B + 1 == X_IDX_C)
  aux0 = _mm_loadh_pi(aux0, &x[X_ORIG + X_IDX_B]);
  tmp = _mm_load_ss(&x[X_ORIG + X_IDX_C]);
  // insert tmp in aux0 in the third position and fourth to zero
  tmp = _mm_insert_ps(aux0, tmp, 0b00101000);
#else
  // e.g. [0,3,7,x], [0,17,42,x]
  tmp = _mm_mask_i32gather_ps(
      _mm_setzero_ps(), &x[X_ORIG + X_IDX_A],
      _mm_set_epi32(0, X_IDX_C - X_IDX_A, X_IDX_B - X_IDX_A, X_IDX_A),
      _mm_set_ps(0, -1, -1, -1), 4);
#endif
#elif X_N == 2
// 2-elements
#if X_IDX_A + 1 == X_IDX_B
  // e.g. [0,1,x,x]
  tmp = _mm_loadl_pi(tmp, &x[X_ORIG + X_IDX_A]);
#elif X_IDX_A + 1 != X_IDX_B
  // e.g. [0,7,x,x]
  aux0 = _mm_load_ss(&x[X_ORIG + X_IDX_A]);
  tmp = _mm_load_ss(&x[X_ORIG + X_IDX_B]);
  tmp = _mm_insert_ps(aux0, tmp, 0b00011100);
#endif
#elif X_N == 1
// 1-elements
#if BROADCAST
  // e.g. [0,0,0,0]
  tmp = _mm_broadcast_ss(&x[X_ORIG + X_IDX_A]);
  // tmp = _mm_set1_ps(x[X_ORIG + X_IDX_A]); same as broadcast, or worse, in
  // some cases it is decoded as: vmovss + vshuflps
#else
  // e.g. [0,x,x,x]
  tmp = _mm_load_ss(&x[X_ORIG + X_IDX_A]);
#endif
#endif
  return tmp;
}
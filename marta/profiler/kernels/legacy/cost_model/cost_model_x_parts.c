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

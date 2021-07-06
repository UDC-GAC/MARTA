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
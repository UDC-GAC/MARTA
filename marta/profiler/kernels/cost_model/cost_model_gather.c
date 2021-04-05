#if defined(B256)
INLINE_PREFIX __m256 cost_model_gather(DATA_TYPE *restrict x) {
#else
INLINE_PREFIX __m128 cost_model_gather(DATA_TYPE *restrict x) {
#endif
#if X_N == 8
#if defined(CUSTOM_GATHER)
#else
  tmp = _mm256_i32gather_ps(
      &x[X_ORIG + X_IDX_A],
      _mm256_set_epi32(X_IDX_H - X_IDX_A, X_IDX_G - X_IDX_A, X_IDX_F - X_IDX_A,
                       X_IDX_E - X_IDX_A, X_IDX_D - X_IDX_A, X_IDX_C - X_IDX_A,
                       X_IDX_B - X_IDX_A, X_IDX_A),
      4);
#endif
#elif X_N == 4
#if defined(CUSTOM_GATHER)
#else
  tmp = _mm_i32gather_ps(&x[X_ORIG + X_IDX_A],
                         _mm_set_epi32(X_IDX_D - X_IDX_A, X_IDX_C - X_IDX_A,
                                       X_IDX_B - X_IDX_A, X_IDX_A),
                         4);
#endif
#endif
  return tmp;
}
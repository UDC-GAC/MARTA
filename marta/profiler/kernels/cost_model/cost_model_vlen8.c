#if X_N == 8
#if (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 == X_IDX_C) &&                    \
    (X_IDX_C + 1 == X_IDX_D) && (X_IDX_D + 1 == X_IDX_E) &&                    \
    (X_IDX_E + 1 == X_IDX_F) && (X_IDX_F + 1 == X_IDX_G) &&                    \
    (X_IDX_G + 1 == X_IDX_H)
// e.g. [0,1,2,3,4,5,6,7]
tmp = _mm256_loadu_ps(&x[X_ORIG + X_IDX_A]);
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 == X_IDX_C) &&                  \
    (X_IDX_C + 1 == X_IDX_D) && (X_IDX_E + 1 == X_IDX_F) &&                    \
    (X_IDX_F + 1 == X_IDX_G) && (X_IDX_G + 1 == X_IDX_H)
// e.g. [0,1,2,3,16,17,18,19]
tmp = _mm256_set_m128(_mm_loadu_ps(&x[X_ORIG + X_IDX_E]),
                      _mm_loadu_ps(&x[X_ORIG + X_IDX_A]));
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_C + 1 == X_IDX_D) &&                  \
    (X_IDX_E + 1 == X_IDX_F) && (X_IDX_G + 1 == X_IDX_H)
__m128 aux0, aux1;
aux0 = _mm_loadl_pi(aux0, &x[X_ORIG + X_IDX_A]);
aux0 = _mm_loadh_pi(aux0, &x[X_ORIG + X_IDX_C]);
aux1 = _mm_loadl_pi(aux1, &x[X_ORIG + X_IDX_E]);
aux1 = _mm_loadh_pi(aux1, &x[X_ORIG + X_IDX_G]);
tmp = _mm256_set_m128(aux1, aux0);
#else
// e.g. [0,2,4,6]
tmp = _mm256_i32gather_ps(&x[X_ORIG + X_IDX_A],
                          _mm256_set_epi32(X_IDX_H - X_IDX_A, X_IDX_G - X_IDX_A,
                                           X_IDX_F - X_IDX_A, X_IDX_E - X_IDX_A,
                                           X_IDX_D - X_IDX_A, X_IDX_C - X_IDX_A,
                                           X_IDX_B - X_IDX_A, X_IDX_A),
                          4);
#endif
#elif X_N == 7
#if (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 == X_IDX_C) &&                    \
    (X_IDX_C + 1 == X_IDX_D) && (X_IDX_D + 1 == X_IDX_E) &&                    \
    (X_IDX_E + 1 == X_IDX_F) && (X_IDX_F + 1 == X_IDX_G)
// e.g. [0,1,2,3,4,5,6,7]
tmp = _mm256_maskload_ps(&x[X_ORIG + X_IDX_A],
                         _mm256_set_epi32(0, -1, -1, -1, -1, -1, -1, -1));
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 == X_IDX_C) &&                  \
    (X_IDX_C + 1 == X_IDX_D) && (X_IDX_E + 1 == X_IDX_F) &&                    \
    (X_IDX_F + 1 == X_IDX_G)
// e.g. [0,1,2,3,16,17,18,19]
tmp = _mm256_set_m128(
    _mm_maskload_ps(&x[X_ORIG + X_IDX_E], _mm_set_epi32(0, -1, -1, -1)),
    _mm_loadu_ps(&x[X_ORIG + X_IDX_A]));
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_C + 1 == X_IDX_D) &&                  \
    (X_IDX_E + 1 == X_IDX_F)
__m128 aux0, aux1, aux2;
aux0 = _mm_loadl_pi(aux0, &x[X_ORIG + X_IDX_A]);
aux0 = _mm_loadh_pi(aux0, &x[X_ORIG + X_IDX_C]);
aux1 = _mm_loadl_pi(aux1, &x[X_ORIG + X_IDX_E]);
aux2 = _mm_load_ss(&x[X_ORIG + X_IDX_G]);
aux1 = _mm_insert_ps(aux1, aux2, 0b00101111);
tmp = _mm256_set_m128(aux1, aux0);
#else
tmp = _mm256_mask_i32gather_ps(
    tmp, &x[X_ORIG + X_IDX_A],
    _mm256_set_epi32(X_IDX_H - X_IDX_A, X_IDX_G - X_IDX_A, X_IDX_F - X_IDX_A,
                     X_IDX_E - X_IDX_A, X_IDX_D - X_IDX_A, X_IDX_C - X_IDX_A,
                     X_IDX_B - X_IDX_A, X_IDX_A),
    _mm256_set_ps(0, -1, -1, -1, -1, -1, -1, -1), 4);
#endif
#elif X_N == 6
#if (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 == X_IDX_C) &&                    \
    (X_IDX_C + 1 == X_IDX_D) && (X_IDX_D + 1 == X_IDX_E) &&                    \
    (X_IDX_E + 1 == X_IDX_F)
// e.g. [0,1,2,3,4,5,6,7]
tmp = _mm256_maskload_ps(&x[X_ORIG + X_IDX_A],
                         _mm256_set_epi32(0, 0, -1, -1, -1, -1, -1, -1));
// __m128 aux0 = _mm_loadu_ps(&x[X_ORIG + X_IDX_A]);
// __m128 aux1 = _mm_loadl_pi(aux1, &x[X_ORIG + X_IDX_E]);
// tmp = _mm256_set_m128(aux1, aux0);
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 == X_IDX_C) &&                  \
    (X_IDX_C + 1 == X_IDX_D) && (X_IDX_E + 1 == X_IDX_F)
// e.g. [0,1,2,3,16,17,18,19]
__m128 aux0;
tmp = _mm256_set_m128(_mm_loadl_pi(aux0, &x[X_ORIG + X_IDX_E]),
                      _mm_loadu_ps(&x[X_ORIG + X_IDX_A]));
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_C + 1 == X_IDX_D) &&                  \
    (X_IDX_E + 1 == X_IDX_F)
__m128 aux0, aux1, aux2;
aux0 = _mm_loadl_pi(aux0, &x[X_ORIG + X_IDX_A]);
aux0 = _mm_loadh_pi(aux0, &x[X_ORIG + X_IDX_C]);
aux1 = _mm_loadl_pi(aux1, &x[X_ORIG + X_IDX_E]);
tmp = _mm256_set_m128(aux1, aux0);
#else
tmp = _mm256_mask_i32gather_ps(
    tmp, &x[X_ORIG + X_IDX_A],
    _mm256_set_epi32(X_IDX_H - X_IDX_A, X_IDX_G - X_IDX_A, X_IDX_F - X_IDX_A,
                     X_IDX_E - X_IDX_A, X_IDX_D - X_IDX_A, X_IDX_C - X_IDX_A,
                     X_IDX_B - X_IDX_A, X_IDX_A),
    _mm256_set_ps(0, 0, -1, -1, -1, -1, -1, -1), 4);
#endif
#elif X_N == 5
#if (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 == X_IDX_C) &&                    \
    (X_IDX_C + 1 == X_IDX_D) && (X_IDX_D + 1 == X_IDX_E)
// e.g. [0,1,2,3,4,5,6,7]
tmp = _mm256_maskload_ps(&x[X_ORIG + X_IDX_A],
                         _mm256_set_epi32(0, 0, -1, -1, -1, -1, -1, -1));
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 == X_IDX_C) &&                  \
    (X_IDX_C + 1 == X_IDX_D)
// e.g. [0,1,2,3,16,17,18,19]
__m128 aux0;
tmp = _mm256_set_m128(_mm_loadl_pi(aux0, &x[X_ORIG + X_IDX_E]),
                      _mm_loadu_ps(&x[X_ORIG + X_IDX_A]));
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_C + 1 == X_IDX_D)
__m128 aux0, aux1, aux2;
aux0 = _mm_loadl_pi(aux0, &x[X_ORIG + X_IDX_A]);
aux0 = _mm_loadh_pi(aux0, &x[X_ORIG + X_IDX_C]);
aux1 = _mm_load_ss(&x[X_ORIG + X_IDX_E]);
tmp = _mm256_set_m128(aux1, aux0);
#else
tmp = _mm256_mask_i32gather_ps(
    tmp, &x[X_ORIG + X_IDX_A],
    _mm256_set_epi32(X_IDX_H - X_IDX_A, X_IDX_G - X_IDX_A, X_IDX_F - X_IDX_A,
                     X_IDX_E - X_IDX_A, X_IDX_D - X_IDX_A, X_IDX_C - X_IDX_A,
                     X_IDX_B - X_IDX_A, X_IDX_A),
    _mm256_set_ps(0, 0, 0, -1, -1, -1, -1, -1), 4);
#endif
#endif
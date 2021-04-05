    __m128 aux0, aux1;
#if X_N == 4
// 4-elements

#if (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 == X_IDX_C) &&                    \
    (X_IDX_C + 1 == X_IDX_D)
// e.g. [0,1,2,3]
tmp = _mm_loadu_ps(&x[X_IDX_A]);
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_C + 1 == X_IDX_D)
// e.g. [0,1,5,6]
aux0 = _mm_loadl_pi(aux1, &x[X_IDX_A]);
tmp = _mm_loadh_pi(aux0, &x[X_IDX_C]);
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 == X_IDX_C) &&                  \
    (X_IDX_C + 1 != X_IDX_D)
// e.g. [0,1,2,7]
aux1 = _mm_maskload_ps(&x[X_IDX_A], _mm_set_epi32(0, -1, -1, -1));
aux0 = _mm_load_ss(&x[X_IDX_D]);
tmp = _mm_insert_ps(aux1, aux0, 0b00110000);
#elif (X_IDX_A + 1 != X_IDX_B) && (X_IDX_B + 1 != X_IDX_C) &&                  \
    (X_IDX_C + 1 == X_IDX_D)
tmp = _mm_loadh_pi(tmp, &x[X_IDX_C]);
aux0 = _mm_load_ss(&x[X_IDX_A]);
tmp = _mm_insert_ps(tmp, aux0, 0b00000000);
aux1 = _mm_load_ss(&x[X_IDX_B]);
tmp = _mm_insert_ps(tmp, aux1, 0b00010000);
#elif (X_IDX_A + 1 != X_IDX_B) && (X_IDX_B + 1 != X_IDX_C) &&                  \
    (X_IDX_C + 1 != X_IDX_D)
// e.g. [0,2,4,6]
tmp = _mm_i32gather_ps(&x[X_IDX_A],
                       _mm_set_epi32(X_IDX_D - X_IDX_A, X_IDX_C - X_IDX_A,
                                     X_IDX_B - X_IDX_A, X_IDX_A),
                       4);
#endif
#elif X_N == 3
// 3-elements
#if (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 == X_IDX_C)
// e.g. [0,1,2,x]
tmp = _mm_maskload_ps(&x[X_IDX_A], _mm_set_epi32(0, -1, -1, -1));
#elif (X_IDX_A + 1 == X_IDX_B) && (X_IDX_B + 1 != X_IDX_C)
// e.g. [0,1,4,x], [0,1,17,x]
aux0 = _mm_loadl_pi(aux0, &x[X_IDX_A]);
tmp = _mm_load_ss(&x[X_IDX_C]);
// insert tmp in aux0 in the third position and fourth to zero
tmp = _mm_insert_ps(aux0, tmp, 0b00101000);
#else
// e.g. [0,3,7,x], [0,17,42,x]
tmp = _mm_mask_i32gather_ps(
    _mm_setzero_ps(), &x[X_IDX_A],
    _mm_set_epi32(0, X_IDX_C - X_IDX_A, X_IDX_B - X_IDX_A, X_IDX_A),
    _mm_set_ps(0, -1, -1, -1), 4);
#endif
#elif X_N == 2
// 2-elements
#if X_IDX_A + 1 == X_IDX_B
// e.g. [0,1,x,x]
tmp0 = _mm_loadl_pi(tmp0, &x[X_ORIG + X_IDX_A]);
tmp1 = _mm_loadl_pi(tmp1, &A[A_ORIG + A_IDX_A]);
tmp2 = _mm_loadl_pi(tmp2, &y[Y_ORIG + Y_IDX_A]);
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
tmp0 = _mm_broadcast_ss(&x[X_ORIG + X_IDX_A]);
tmp1 = _mm_broadcast_ss(&A[A_ORIG + A_IDX_A]);
tmp2 = _mm_broadcast_ss(&y[Y_ORIG + Y_IDX_A]);
// tmp = _mm_set1_ps(x[X_ORIG + X_IDX_A]); same as broadcast, or worse, in
// some cases it is decoded as: vmovss + vshuflps
#else
// e.g. [0,x,x,x]
tmp0 = _mm_load_ss(&x[X_ORIG + X_IDX_A]);
tmp1 = _mm_load_ss(&A[A_ORIG + A_IDX_A]);
tmp2 = _mm_load_ss(&y[Y_ORIG + Y_IDX_A]);
#endif
#endif
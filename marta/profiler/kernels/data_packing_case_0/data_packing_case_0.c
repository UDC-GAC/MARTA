#include "data_packing_case_0.h"
#include <immintrin.h>

#define restrict __restrict

#ifndef ORIG_A
#define ORIG_A 0
#endif

#ifndef ORIG_x
#define ORIG_x 0
#endif

#ifndef ORIG_y
#define ORIG_y 0
#endif

#if defined(INTEL_COMPILER)
#define INLINE_PREFIX __forceinline
#else
#define INLINE_PREFIX __attribute__((always_inline)) inline
#endif

#if defined(LOADU2_LOAD) && !defined(INTEL_COMPILER)
#undef LOADU2_LOAD
#define SET_LOAD
#endif

#ifdef SIMD_CODE
#define __OPTIMIZE__
#endif

//#define SIMD_CODE

INLINE_PREFIX void data_packing_case_0(DATA_TYPE *restrict A, DATA_TYPE *restrict x, DATA_TYPE *restrict y)
{
    int I = 0;
    int J = 0;
    int I_sz=2;
    int J_sz=2;
    int I_Str=1;
    int J_Str=1;
    int Ya=1;
    int Aa=1;
    int Xa=1;
    int Yb=0;
    int Ab=0;
    int Xb=0;
    int i,j;


    asm volatile("" : "+g"(y));
    asm volatile("" : "+g"(A));
    asm volatile("" : "+g"(x));
#ifndef SIMD_CODE
    for (i = I; i < I + I_sz; i += I_Str) {
        for (j = J; j < J + J_sz; j += J_Str) {
            y[Ya * i + Yb * j + ORIG_y] += A[Aa * i + Ab * j + ORIG_A] *
                                    x[Xa * i + Xb * j + ORIG_x];
        }
    }
    I = 42;
    J = 42;
    for (i = I; i < I + I_sz; i += I_Str) {
        for (j = J; j < J + J_sz; j += J_Str) {
            y[Ya * i + Yb * j + ORIG_y] += A[Aa * i + Ab * j + ORIG_A] *
                                    x[Xa * i + Xb * j + ORIG_x];
        }
    }
#else
    // Unrolling
    // y[0] = y[0] + A[0] * x[0];
    // y[0] = y[0] + A[0] * x[0];
    // y[1] = y[1] + A[1] * x[1];
    // y[1] = y[1] + A[1] * x[1];
    // y[42] = y[42] + A[42] * x[42];
    // y[42] = y[42] + A[42] * x[42];
    // y[43] = y[43] + A[43] * x[43];
    // y[43] = y[43] + A[43] * x[43];
    
    // Converted to the format
    // y[0] = (A[0]*x[0]) + (y[0] + A[0] * x[0]);
    // y[1] = (A[1]*x[1]) + (y[1] + A[1] * x[1]);
    // y[42] = (A[42]*x[42]) + (y[42] + A[42] * x[42]);
    // y[43] = (A[43]*x[43]) + (y[43] + A[43] * x[43]);

    // Psuedo-code
    // vop2 = {y[43],y[42],y[1],y[0]}
    // vop1 = {x[43],x[42],x[1],x[0]}
    // vop0 = {A[43],A[42],A[1],A[0]}
    // mul = mul(vop0,vop1);
    // fma = fma(vop0,vop1,vop2);
    // add = add(vop0,vop1,vop2);
    // store(add);

#ifdef ASM_CODE
    asm volatile(
        ""
    );
#endif 

#ifdef VERSION_HALF_VECTOR
    __m128 accm0, accm1, accm2;
    __m128 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5;

    // tmp0 = _mm_loadu_ps(&A[0]);
    // tmp1 = _mm_loadu_ps(&A[42]);
    // //tmp1 = tmp0;
    // accm0 = _mm_shuffle_ps(tmp0,tmp1,0x44);

    // tmp2 = _mm_loadu_ps(&x[0]);
    // tmp3 = _mm_loadu_ps(&x[42]);
    // //tmp3 = tmp2;
    // accm1 = _mm_shuffle_ps(tmp2,tmp3,0x44);

    // tmp4 = _mm_loadu_ps(&y[0]);
    // tmp5 = _mm_loadu_ps(&y[42]);
    // //tmp5 = tmp4;
    // accm2 = _mm_shuffle_ps(tmp4,tmp5,0x44);
    
    // This is the most flexible option

#ifdef LOAD_SET
    accm0 = _mm_set_ps(A[43],A[42],A[1],A[0]);
    accm1 = _mm_set_ps(x[43],x[42],x[1],x[0]);
    accm2 = _mm_set_ps(y[43],y[42],y[1],y[0]);
#endif

#ifdef LOAD_IN_HALVES
    tmp1 = _mm_loadl_pi(tmp1, &A[0]);
    accm0 = _mm_loadh_pi(tmp1, &A[42]);
    //accm0 = _mm_set_ps(A[43],A[42],A[1],A[0]);
    tmp3 = _mm_loadl_pi(tmp3, &x[0]);
    accm1 = _mm_loadh_pi(tmp3, &x[42]);
    //accm1 = _mm_set_ps(x[43],x[42],x[1],x[0]);
    tmp5 = _mm_loadl_pi(tmp5, &y[0]);
    accm2 = _mm_loadh_pi(tmp5, &y[42]);
    
    //accm2 = _mm_set_ps(y[43],y[42],y[1],y[0]);  
#endif

#ifdef LOAD_IN_HALVES_REG
    accm0 = _mm_loadl_pi(accm0, &A[0]);
    tmp1 = _mm_loadl_pi(tmp1, &A[42]);
    accm0 = _mm_movelh_ps(accm0,tmp1);

    accm1 = _mm_loadl_pi(accm1, &x[0]);
    tmp3 = _mm_loadl_pi(tmp3, &x[42]);
    accm1 = _mm_movelh_ps(accm1,tmp3);
    
    accm2 = _mm_loadl_pi(accm2, &y[0]);
    tmp5 = _mm_loadl_pi(tmp5, &y[42]);
    accm2 = _mm_movelh_ps(accm2,tmp5);
#endif

    __m128 mul = _mm_mul_ps(accm0,accm1);
    __m128 fma = _mm_fmadd_ps(accm0, accm1, accm2);
    __m128 add = _mm_add_ps(fma, mul);
    
    
    // UGLY HACK for scattering data: x2 vextractps
    _mm_store_sd((double *)&y[0],_mm_castps_pd(add));
    //_mm_store_sd((double *)&y[0],_mm_castps_pd(add));
    // Manual scattering, even worse
    // y[0] = add[0];
    // y[1] = add[1];
    y[42] = add[2];
    y[43] = add[3];

#endif

#ifdef VERSION_FULL_VECTOR
    __m256 __mv_vop0, __mv_vop1, __mv_vop2;
#ifdef SET_LOAD
    __mv_vop0 =
         _mm256_set_ps(A[43], A[43], A[42], A[42], A[1], A[1], A[0], A[0]);
    __mv_vop1 =
         _mm256_set_ps(x[43], x[43], x[42], x[42], x[1], x[1], x[0], x[0]);
    __mv_vop2 =
         _mm256_set_ps(y[43], y[43], y[42], y[42], y[1], y[1], y[0], y[0]);
#endif
#ifdef LOADU2_LOAD
    __mv_vop0 = _mm256_loadu2_m128(&A[42],&A[0]);
    __mv_vop0 = _mm256_permute_ps(__mv_vop0, 0x50);
    __mv_vop1 = _mm256_loadu2_m128(&x[42],&x[0]);
    __mv_vop1 = _mm256_permute_ps(__mv_vop1, 0x50);
    __mv_vop2 = _mm256_loadu2_m128(&y[42],&y[0]);
    __mv_vop2 = _mm256_permute_ps(__mv_vop2, 0x50);
#endif


    // Target operation
    __mv_vop2 = _mm256_fmadd_ps(__mv_vop0, __mv_vop1, __mv_vop2);

#ifdef CAST_HADD_STORE
    __mv_vop2 = _mm256_hadd_ps(__mv_vop2, __mv_vop2);
    // Casts are free
    _mm_store_sd((double *)&y[0],_mm_castps_pd(_mm256_castps256_ps128(__mv_vop2)));
    _mm_store_sd((double *)&y[42],_mm_castps_pd(_mm256_extractf128_ps(__mv_vop2,0x1)));
#endif

#ifdef SCATTER_HADD_STORE
    __mv_vop2 = _mm256_hadd_ps(__mv_vop2, __mv_vop2);
    y[0] = __mv_vop2[0];
    y[1] = __mv_vop2[1];
    y[42] = __mv_vop2[4];
    y[43] = __mv_vop2[5];
#endif
#endif

#endif
  
  // FLUSHING EVERYTHING TO MEMORY; GOOD BARRIER
  // https://github.com/google/benchmark/blob/d8254bb9eb5f6deeddee639d0b27347e186e0a84/include/benchmark/benchmark.h#L329
  asm volatile("" : : : "memory");
}

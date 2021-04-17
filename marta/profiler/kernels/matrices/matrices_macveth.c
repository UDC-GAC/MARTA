/* begin INFO MACVETH: headers added */
#include <immintrin.h>
/* end INFO MACVETH */
#define max(x,y)    ((x) > (y) ? (x) : (y))
#define min(x,y)    ((x) < (y) ? (x) : (y))

void kernel_spmv_fragment_0(float * restrict A, float * restrict x, float * restrict y ) {
  register int i0,i1,i2,i3,i4,i5,i6;

  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+0] += A[i0+0] * x[1*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+0] += A[i0+8] * x[1*i0+20];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+0] += A[i0+16] * x[1*i0+40];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+0] += A[i0+24] * x[1*i0+60];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+0] += A[i0+32] * x[1*i0+80];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+0] += A[i0+40] * x[1*i0+100];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+0] += A[i0+48] * x[1*i0+139];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+0] += A[i0+56] * x[1*i0+158];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+0] += A[i0+64] * x[2*i0+259];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+0] += A[i0+72] * x[2*i0+260];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+0] += A[i0+80] * x[4*i0+261];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+0] += A[i0+88] * x[4*i0+262];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+0] += A[i0+96] * x[1*i0+280];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+0] += A[i0+104] * x[1*i0+300];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+0] += A[i0+112] * x[1*i0+320];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+0] += A[i0+120] * x[1*i0+340];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+0] += A[i0+128] * x[1*i0+360];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+1] += A[i0+136] * x[4*i0+259];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+1] += A[i0+144] * x[4*i0+260];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+1] += A[i0+152] * x[4*i0+261];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+1] += A[i0+160] * x[4*i0+262];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+2] += A[i0+168] * x[4*i0+259];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+2] += A[i0+176] * x[4*i0+260];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+3] += A[i0+184] * x[1*i0+259];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+7] += A[i0+192] * x[1*i0+263];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+8] += A[i0+200] * x[1*i0+8];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+8] += A[i0+208] * x[1*i0+28];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+8] += A[i0+216] * x[1*i0+48];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+8] += A[i0+224] * x[1*i0+68];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+8] += A[i0+232] * x[1*i0+88];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+8] += A[i0+240] * x[1*i0+108];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+8] += A[i0+248] * x[1*i0+147];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+8] += A[i0+256] * x[1*i0+166];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+8] += A[i0+264] * x[1*i0+288];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+8] += A[i0+272] * x[1*i0+308];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+8] += A[i0+280] * x[1*i0+328];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+8] += A[i0+288] * x[1*i0+348];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+8] += A[i0+296] * x[1*i0+368];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+11] += A[i0+304] * x[1*i0+267];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+15] += A[i0+312] * x[1*i0+271];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+16] += A[i0+320] * x[1*i0+16];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+16] += A[i0+328] * x[1*i0+36];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+16] += A[i0+336] * x[1*i0+56];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+16] += A[i0+344] * x[1*i0+76];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+16] += A[i0+352] * x[1*i0+96];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+16] += A[i0+360] * x[1*i0+116];
  }
#pragma macveth
  __m256 __tmp0_256, __tmp1_256, __vop2, __vop0, __vop1, __vop3, __vop6, __vop4, __vop5, __vop9, __vop7, __vop8, __vop10, __vop13, __vop11, __vop12, __vop16, __vop14, __vop15, __vop17, __vop20, __vop18, __vop19, __vop21, __vop24, __vop22, __vop23, __vop25, __vop28, __vop26, __vop27, __mv_accm0, __vop29, __mv_lo256, __mv_hi256, __tmp2_256, __vop31, __vop30, __vop32, __vop35, __vop33, __vop34, __vop36, __vop38, __vop37, __vop39, __vop42, __vop40, __vop41, __vop43, __vop46, __vop44, __vop45, __vop47, __vop50, __vop48, __vop49, __vop51, __vop54, __vop52, __vop53, __mv_accm1, __vop57, __vop55, __vop56, __mv_accm2, __vop58;
__m128 __tmp0_128, __tmp1_128, __lo128, __tmp0, __tmp1, __hi128;
__vop0 = _mm256_loadu_ps(&A[2538 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&A[368]);
__vop0 = _mm256_blend_ps(__vop0, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__lo128 = _mm_loadu_ps(&x[155]);
__tmp0 = _mm_load_ss(&x[421]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&x[425], _mm_set_epi32(282, 278, 274, 270), 4);
__vop1 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&y[16]);
__tmp0 = _mm_load_ss(&y[158]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&y[162], _mm_set_epi32(158, 154, 150, 146), 4);
__vop3 = _mm256_set_m128(__hi128, __lo128);
__vop3 = _mm256_fmadd_ps(__vop0, __vop1, __vop3);
_mm_i32scatter_ps(&y[162], _mm_set_epi32(158, 154, 150, 146), _mm256_extractf128_ps(__vop3,0x1), 4);

  
  
  
  
  
  
  
#pragma endmacveth
#pragma macveth
  __vop4 = _mm256_loadu_ps(&A[2543 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&A[371]);
__vop4 = _mm256_blend_ps(__vop4, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__lo128 = _mm_loadu_ps(&x[174]);
__tmp0 = _mm_load_ss(&x[422]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&x[426], _mm_set_epi32(264, 260, 256, 252), 4);
__vop5 = _mm256_set_m128(__hi128, __lo128);
__vop3 = _mm256_fmadd_ps(__vop4, __vop5, __vop3);
_mm_i32scatter_ps(&y[162], _mm_set_epi32(158, 154, 150, 146), _mm256_extractf128_ps(__vop3,0x1), 4);

  
  
  
  
  
  
  
#pragma endmacveth
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+16] += A[i0+374] * x[2*i0+275];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+16] += A[i0+382] * x[2*i0+276];
  }
#pragma macveth
  __vop7 = _mm256_loadu_ps(&A[2564 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&A[390]);
__vop7 = _mm256_blend_ps(__vop7, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__lo128 = _mm_loadu_ps(&x[296]);
__tmp0 = _mm_load_ss(&x[419]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&x[423], _mm_set_epi32(139, 135, 131, 127), 4);
__vop8 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&y[16]);
__tmp0 = _mm_load_ss(&y[160]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&y[164], _mm_set_epi32(160, 156, 152, 148), 4);
__vop10 = _mm256_set_m128(__hi128, __lo128);
__vop10 = _mm256_fmadd_ps(__vop7, __vop8, __vop10);
_mm_i32scatter_ps(&y[164], _mm_set_epi32(160, 156, 152, 148), _mm256_extractf128_ps(__vop10,0x1), 4);

  
  
  
  
  
  
  
#pragma endmacveth
#pragma macveth
  __vop11 = _mm256_loadu_ps(&A[2569 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&A[393]);
__vop11 = _mm256_blend_ps(__vop11, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__lo128 = _mm_loadu_ps(&x[316]);
__tmp0 = _mm_load_ss(&x[420]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&x[424], _mm_set_epi32(120, 116, 112, 108), 4);
__vop12 = _mm256_set_m128(__hi128, __lo128);
__vop10 = _mm256_fmadd_ps(__vop11, __vop12, __vop10);
_mm_i32scatter_ps(&y[164], _mm_set_epi32(160, 156, 152, 148), _mm256_extractf128_ps(__vop10,0x1), 4);

  
  
  
  
  
  
  
#pragma endmacveth
#pragma macveth
  __vop14 = _mm256_loadu_ps(&A[3050 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&A[396]);
__vop14 = _mm256_blend_ps(__vop14, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__lo128 = _mm_loadu_ps(&x[336]);
__tmp0 = _mm_load_ss(&x[439]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&x[439], _mm_set_epi32(103, 103, 103, 103), 4);
__vop15 = _mm256_set_m128(__hi128, __lo128);
__vop17 = _mm256_loadu_ps(&y[233 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&y[16]);
__vop17 = _mm256_blend_ps(__vop17, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__vop17 = _mm256_fmadd_ps(__vop14, __vop15, __vop17);
_mm_storeu_ps(&y[234], _mm256_extractf128_ps(__vop17,0x1));
_mm_i32scatter_ps(&y[16], _mm_set_epi32(217, 2, 1, 0), _mm256_castps256_ps128(__vop17), 4);

  
  
  
  
  
  
  
#pragma endmacveth
#pragma macveth
  __vop18 = _mm256_loadu_ps(&A[3087 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&A[399]);
__vop18 = _mm256_blend_ps(__vop18, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__vop19 = _mm256_loadu_ps(&x[462 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&x[356]);
__vop19 = _mm256_blend_ps(__vop19, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__vop21 = _mm256_loadu_ps(&y[254 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&y[16]);
__vop21 = _mm256_blend_ps(__vop21, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__vop21 = _mm256_fmadd_ps(__vop18, __vop19, __vop21);
_mm_storeu_ps(&y[255], _mm256_extractf128_ps(__vop21,0x1));
_mm_i32scatter_ps(&y[16], _mm_set_epi32(238, 2, 1, 0), _mm256_castps256_ps128(__vop21), 4);

  
  
  
  
  
  
  
#pragma endmacveth
#pragma macveth
  __vop22 = _mm256_loadu_ps(&A[4846 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&A[402]);
__vop22 = _mm256_blend_ps(__vop22, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__lo128 = _mm_loadu_ps(&x[376]);
__tmp0 = _mm_load_ss(&x[160]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&x[164], _mm_set_epi32(12, 8, 4, 0), 4);
__vop23 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&y[16]);
__tmp0 = _mm_load_ss(&y[419]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&y[423], _mm_set_epi32(419, 415, 411, 407), 4);
__vop25 = _mm256_set_m128(__hi128, __lo128);
__vop25 = _mm256_fmadd_ps(__vop22, __vop23, __vop25);
_mm_i32scatter_ps(&y[423], _mm_set_epi32(419, 415, 411, 407), _mm256_extractf128_ps(__vop25,0x1), 4);

  
  
  
  
  
  
  
#pragma endmacveth
#pragma macveth unroll i0 4
  __mv_accm0 = _mm256_setzero_ps();
for( i0 = 0; i0 <= 3; i0 += 4 ) {
    __lo128 = _mm_loadu_ps(&A[405]);
__hi128 = _mm_loadu_ps(&A[760]);
__vop26 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&x[275]);
__hi128 = _mm_loadu_ps(&x[295]);
__vop27 = _mm256_set_m128(__hi128, __lo128);
__mv_accm0 = _mm256_fmadd_ps(__vop26, __vop27, __mv_accm0);

    
  }__tmp0_256 = _mm256_permute_ps(__mv_accm0, 0b00001110);
__tmp1_256 = _mm256_add_ps(__mv_accm0, __tmp0_256);
__tmp2_256 = _mm256_shuffle_ps(__tmp1_256, __tmp1_256, 0x01);
__mv_lo256 = _mm256_add_ps(__tmp1_256, __tmp2_256);
y[19] = y[19]+__mv_lo256[0];
y[39] = y[39]+__mv_lo256[4];

#pragma endmacveth
  for( i0 = 0; i0 <= 5; ++i0 ) {
    y[0*i0+19] += A[i0+409] * x[1*i0+440];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+20] += A[i0+415] * x[1*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+20] += A[i0+423] * x[1*i0+158];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+20] += A[i0+431] * x[1*i0+260];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+20] += A[i0+439] * x[1*i0+300];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+20] += A[i0+447] * x[1*i0+320];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+20] += A[i0+455] * x[1*i0+340];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+20] += A[i0+463] * x[1*i0+360];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+23] += A[i0+471] * x[1*i0+279];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+24] += A[i0+479] * x[1*i0+24];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+24] += A[i0+487] * x[1*i0+44];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+24] += A[i0+495] * x[1*i0+64];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+24] += A[i0+503] * x[1*i0+84];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+24] += A[i0+511] * x[1*i0+104];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+24] += A[i0+519] * x[1*i0+124];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+27] += A[i0+527] * x[1*i0+283];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+28] += A[i0+535] * x[1*i0+8];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+28] += A[i0+543] * x[1*i0+166];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+28] += A[i0+551] * x[1*i0+268];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+28] += A[i0+559] * x[1*i0+308];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+28] += A[i0+567] * x[1*i0+328];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+28] += A[i0+575] * x[1*i0+348];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+28] += A[i0+583] * x[1*i0+368];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+31] += A[i0+591] * x[1*i0+287];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+32] += A[i0+599] * x[1*i0+32];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+32] += A[i0+607] * x[1*i0+52];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+32] += A[i0+615] * x[1*i0+72];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+32] += A[i0+623] * x[1*i0+92];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+32] += A[i0+631] * x[1*i0+112];
  }
  for( i0 = 0; i0 <= 6; ++i0 ) {
    y[1*i0+32] += A[i0+639] * x[1*i0+132];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+32] += A[i0+646] * x[2*i0+291];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+32] += A[i0+654] * x[2*i0+292];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+32] += A[i0+662] * x[4*i0+293];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+32] += A[i0+670] * x[4*i0+294];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+33] += A[i0+678] * x[4*i0+291];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+33] += A[i0+686] * x[4*i0+292];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+33] += A[i0+694] * x[4*i0+293];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+33] += A[i0+702] * x[4*i0+294];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+34] += A[i0+710] * x[4*i0+291];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+34] += A[i0+718] * x[4*i0+292];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+35] += A[i0+726] * x[1*i0+291];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+36] += A[i0+734] * x[1*i0+16];
  }
#pragma macveth
  __vop30 = _mm256_loadu_ps(&A[4867 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&A[742]);
__vop30 = _mm256_blend_ps(__vop30, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__lo128 = _mm_loadu_ps(&x[174]);
__tmp0 = _mm_load_ss(&x[160]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&x[164], _mm_set_epi32(12, 8, 4, 0), 4);
__vop5 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&y[36]);
__tmp0 = _mm_load_ss(&y[420]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&y[424], _mm_set_epi32(400, 396, 392, 388), 4);
__vop32 = _mm256_set_m128(__hi128, __lo128);
__vop32 = _mm256_fmadd_ps(__vop30, __vop5, __vop32);
_mm_i32scatter_ps(&y[424], _mm_set_epi32(400, 396, 392, 388), _mm256_extractf128_ps(__vop32,0x1), 4);

  
  
  
  
  
  
  
#pragma endmacveth
#pragma macveth
  __vop33 = _mm256_loadu_ps(&A[4872 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&A[745]);
__vop33 = _mm256_blend_ps(__vop33, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__lo128 = _mm_loadu_ps(&x[276]);
__tmp0 = _mm_load_ss(&x[158]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&x[162], _mm_set_epi32(12, 8, 4, 0), 4);
__vop34 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&y[36]);
__tmp0 = _mm_load_ss(&y[421]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&y[425], _mm_set_epi32(401, 397, 393, 389), 4);
__vop36 = _mm256_set_m128(__hi128, __lo128);
__vop36 = _mm256_fmadd_ps(__vop33, __vop34, __vop36);
_mm_i32scatter_ps(&y[425], _mm_set_epi32(401, 397, 393, 389), _mm256_extractf128_ps(__vop36,0x1), 4);

  
  
  
  
  
  
  
#pragma endmacveth
#pragma macveth
  __vop37 = _mm256_loadu_ps(&A[4877 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&A[748]);
__vop37 = _mm256_blend_ps(__vop37, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__lo128 = _mm_loadu_ps(&x[316]);
__tmp0 = _mm_load_ss(&x[158]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&x[162], _mm_set_epi32(12, 8, 4, 0), 4);
__vop12 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&y[36]);
__tmp0 = _mm_load_ss(&y[422]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&y[426], _mm_set_epi32(402, 398, 394, 390), 4);
__vop39 = _mm256_set_m128(__hi128, __lo128);
__vop39 = _mm256_fmadd_ps(__vop37, __vop12, __vop39);
_mm_i32scatter_ps(&y[426], _mm_set_epi32(402, 398, 394, 390), _mm256_extractf128_ps(__vop39,0x1), 4);

  
  
  
  
  
  
  
#pragma endmacveth
#pragma macveth
  __vop40 = _mm256_loadu_ps(&A[5089 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&A[751]);
__vop40 = _mm256_blend_ps(__vop40, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__vop41 = _mm256_loadu_ps(&x[254 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&x[336]);
__vop41 = _mm256_blend_ps(__vop41, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__vop43 = _mm256_loadu_ps(&y[462 + (-3)]);
__tmp0_128 = _mm_loadu_ps(&y[36]);
__vop43 = _mm256_blend_ps(__vop43, _mm256_castps128_ps256(__tmp0_128), 0b00000111);
__vop43 = _mm256_fmadd_ps(__vop40, __vop41, __vop43);
_mm_storeu_ps(&y[463], _mm256_extractf128_ps(__vop43,0x1));
_mm_i32scatter_ps(&y[36], _mm_set_epi32(426, 2, 1, 0), _mm256_castps256_ps128(__vop43), 4);

  
  
  
  
  
  
  
#pragma endmacveth
#pragma macveth
  __vop44 = _mm256_loadu_ps(&A[754]);
__tmp0_256 = _mm256_loadu_ps(&A[1062 + (-3)]);
__vop44 = _mm256_blend_ps(__vop44, __tmp0_256, 0b00111000);
__tmp0_256 = _mm256_loadu_ps(&A[2659 + (-6)]);
__vop44 = _mm256_blend_ps(__vop44, __tmp0_256, 0b11000000);
__vop45 = _mm256_loadu_ps(&x[356]);
__tmp0_256 = _mm256_loadu_ps(&x[136 + (-3)]);
__vop45 = _mm256_blend_ps(__vop45, __tmp0_256, 0b00111000);
__tmp0_256 = _mm256_loadu_ps(&x[434 + (-6)]);
__vop45 = _mm256_blend_ps(__vop45, __tmp0_256, 0b01000000);
__tmp0_256 = _mm256_loadu_ps(&x[438 + (-7)]);
__vop45 = _mm256_blend_ps(__vop45, __tmp0_256, 0b10000000);
__vop47 = _mm256_loadu_ps(&y[36]);
__tmp0_256 = _mm256_loadu_ps(&y[56 + (-3)]);
__vop47 = _mm256_blend_ps(__vop47, __tmp0_256, 0b00111000);
__tmp0_256 = _mm256_loadu_ps(&y[172 + (-6)]);
__vop47 = _mm256_blend_ps(__vop47, __tmp0_256, 0b01000000);
__tmp0_256 = _mm256_loadu_ps(&y[175 + (-7)]);
__vop47 = _mm256_blend_ps(__vop47, __tmp0_256, 0b10000000);
__vop47 = _mm256_fmadd_ps(__vop44, __vop45, __vop47);
_mm_storel_pi(&y[57], _mm256_extractf128_ps(__vop47,0x1));
_mm_i32scatter_ps(&y[36], _mm_set_epi32(20, 2, 1, 0), _mm256_castps256_ps128(__vop47), 4);

  
  
  
  
  
  
  
#pragma endmacveth
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+36] += A[i0+757] * x[1*i0+376];
  }
  for( i0 = 0; i0 <= 5; ++i0 ) {
    y[0*i0+39] += A[i0+764] * x[1*i0+440];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+40] += A[i0+770] * x[1*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+40] += A[i0+778] * x[1*i0+40];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+40] += A[i0+786] * x[1*i0+60];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+40] += A[i0+794] * x[1*i0+80];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+40] += A[i0+802] * x[1*i0+100];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+40] += A[i0+810] * x[1*i0+120];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+40] += A[i0+818] * x[1*i0+139];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+40] += A[i0+826] * x[1*i0+260];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+40] += A[i0+834] * x[1*i0+280];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+40] += A[i0+842] * x[1*i0+320];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+40] += A[i0+850] * x[1*i0+340];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+40] += A[i0+858] * x[1*i0+360];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+43] += A[i0+866] * x[1*i0+299];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+44] += A[i0+874] * x[1*i0+24];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+47] += A[i0+882] * x[1*i0+303];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+48] += A[i0+890] * x[1*i0+8];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+48] += A[i0+898] * x[1*i0+48];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+48] += A[i0+906] * x[1*i0+68];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+48] += A[i0+914] * x[1*i0+88];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+48] += A[i0+922] * x[1*i0+108];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+48] += A[i0+930] * x[1*i0+128];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+48] += A[i0+938] * x[1*i0+147];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+48] += A[i0+946] * x[1*i0+268];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+48] += A[i0+954] * x[1*i0+288];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+48] += A[i0+962] * x[2*i0+307];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+48] += A[i0+970] * x[2*i0+308];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+48] += A[i0+978] * x[1*i0+328];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+48] += A[i0+986] * x[1*i0+348];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+48] += A[i0+994] * x[1*i0+368];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+51] += A[i0+1002] * x[1*i0+307];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+52] += A[i0+1010] * x[1*i0+32];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+55] += A[i0+1018] * x[1*i0+311];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+56] += A[i0+1026] * x[1*i0+16];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+56] += A[i0+1034] * x[1*i0+56];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+56] += A[i0+1042] * x[1*i0+76];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+56] += A[i0+1050] * x[1*i0+96];
  }
#pragma macveth unroll i0 4
  for( i0 = 0; i0 <= 3; i0 += 4 ) {
    __lo128 = _mm_loadu_ps(&A[1058]);
__hi128 = _mm_loadu_ps(&A[1670]);
__vop48 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&x[116]);
__hi128 = _mm_loadu_ps(&x[116]);
__vop49 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&y[56]);
__hi128 = _mm_loadu_ps(&y[96]);
__vop51 = _mm256_set_m128(__hi128, __lo128);
__vop51 = _mm256_fmadd_ps(__vop48, __vop49, __vop51);
_mm_storeu_ps(&y[56], _mm256_castps256_ps128(__vop51));
_mm_storeu_ps(&y[96], _mm256_extractf128_ps(__vop51,0x1));

    
  }
#pragma endmacveth
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+56] += A[i0+1065] * x[1*i0+155];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+56] += A[i0+1068] * x[1*i0+276];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+56] += A[i0+1071] * x[1*i0+296];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+56] += A[i0+1074] * x[1*i0+336];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+56] += A[i0+1077] * x[1*i0+356];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+56] += A[i0+1080] * x[1*i0+376];
  }
#pragma macveth unroll i0 4
  __mv_accm1 = _mm256_setzero_ps();
for( i0 = 0; i0 <= 3; i0 += 4 ) {
    __lo128 = _mm_loadu_ps(&A[1083]);
__hi128 = _mm_loadu_ps(&A[1769]);
__vop52 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&x[315]);
__hi128 = _mm_loadu_ps(&x[355]);
__vop53 = _mm256_set_m128(__hi128, __lo128);
__mv_accm1 = _mm256_fmadd_ps(__vop52, __vop53, __mv_accm1);

    
  }__tmp0_256 = _mm256_permute_ps(__mv_accm1, 0b00001110);
__tmp1_256 = _mm256_add_ps(__mv_accm1, __tmp0_256);
__tmp2_256 = _mm256_shuffle_ps(__tmp1_256, __tmp1_256, 0x01);
__mv_lo256 = _mm256_add_ps(__tmp1_256, __tmp2_256);
y[59] = y[59]+__mv_lo256[0];
y[99] = y[99]+__mv_lo256[4];

#pragma endmacveth
  for( i0 = 0; i0 <= 5; ++i0 ) {
    y[0*i0+59] += A[i0+1087] * x[1*i0+440];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+60] += A[i0+1093] * x[1*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+60] += A[i0+1101] * x[1*i0+40];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+60] += A[i0+1109] * x[1*i0+260];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+60] += A[i0+1117] * x[1*i0+280];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+60] += A[i0+1125] * x[1*i0+300];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+60] += A[i0+1133] * x[1*i0+340];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+60] += A[i0+1141] * x[1*i0+360];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+63] += A[i0+1149] * x[1*i0+319];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+64] += A[i0+1157] * x[1*i0+24];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+64] += A[i0+1165] * x[1*i0+64];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+64] += A[i0+1173] * x[1*i0+84];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+64] += A[i0+1181] * x[1*i0+104];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+64] += A[i0+1189] * x[2*i0+323];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+64] += A[i0+1197] * x[2*i0+324];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+64] += A[i0+1205] * x[4*i0+325];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+64] += A[i0+1213] * x[4*i0+326];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+65] += A[i0+1221] * x[4*i0+323];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+65] += A[i0+1229] * x[4*i0+324];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+65] += A[i0+1237] * x[4*i0+325];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+65] += A[i0+1245] * x[4*i0+326];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+66] += A[i0+1253] * x[4*i0+323];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+66] += A[i0+1261] * x[4*i0+324];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+67] += A[i0+1269] * x[1*i0+323];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+68] += A[i0+1277] * x[1*i0+8];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+68] += A[i0+1285] * x[1*i0+48];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+68] += A[i0+1293] * x[1*i0+268];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+68] += A[i0+1301] * x[1*i0+288];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+68] += A[i0+1309] * x[1*i0+308];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+68] += A[i0+1317] * x[1*i0+348];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+68] += A[i0+1325] * x[1*i0+368];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+71] += A[i0+1333] * x[1*i0+327];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+72] += A[i0+1341] * x[1*i0+32];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+72] += A[i0+1349] * x[1*i0+72];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+72] += A[i0+1357] * x[1*i0+92];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+72] += A[i0+1365] * x[1*i0+112];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+75] += A[i0+1373] * x[1*i0+331];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+76] += A[i0+1381] * x[1*i0+16];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+76] += A[i0+1389] * x[1*i0+56];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+76] += A[i0+1397] * x[1*i0+276];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+76] += A[i0+1400] * x[1*i0+296];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+76] += A[i0+1403] * x[1*i0+316];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+76] += A[i0+1406] * x[1*i0+356];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+76] += A[i0+1409] * x[1*i0+376];
  }
#pragma macveth unroll i0 4
  __mv_accm2 = _mm256_setzero_ps();
for( i0 = 0; i0 <= 3; i0 += 4 ) {
    __lo128 = _mm_loadu_ps(&A[1412]);
__hi128 = _mm_loadu_ps(&A[2034]);
__vop55 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&x[335]);
__hi128 = _mm_loadu_ps(&x[375]);
__vop56 = _mm256_set_m128(__hi128, __lo128);
__mv_accm2 = _mm256_fmadd_ps(__vop55, __vop56, __mv_accm2);

    
  }__tmp0_256 = _mm256_permute_ps(__mv_accm2, 0b00001110);
__tmp1_256 = _mm256_add_ps(__mv_accm2, __tmp0_256);
__tmp2_256 = _mm256_shuffle_ps(__tmp1_256, __tmp1_256, 0x01);
__mv_lo256 = _mm256_add_ps(__tmp1_256, __tmp2_256);
y[79] = y[79]+__mv_lo256[0];
y[119] = y[119]+__mv_lo256[4];

#pragma endmacveth
  for( i0 = 0; i0 <= 5; ++i0 ) {
    y[0*i0+79] += A[i0+1416] * x[1*i0+440];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+80] += A[i0+1422] * x[1*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+80] += A[i0+1430] * x[1*i0+40];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+80] += A[i0+1438] * x[1*i0+80];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+80] += A[i0+1446] * x[1*i0+100];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+80] += A[i0+1454] * x[1*i0+260];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+80] += A[i0+1462] * x[1*i0+280];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+80] += A[i0+1470] * x[1*i0+300];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+80] += A[i0+1478] * x[1*i0+320];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+80] += A[i0+1486] * x[2*i0+339];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+80] += A[i0+1494] * x[2*i0+340];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+80] += A[i0+1502] * x[1*i0+360];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+83] += A[i0+1510] * x[1*i0+339];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+84] += A[i0+1518] * x[1*i0+24];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+84] += A[i0+1526] * x[1*i0+64];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+87] += A[i0+1534] * x[1*i0+343];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+88] += A[i0+1542] * x[1*i0+8];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+88] += A[i0+1550] * x[1*i0+48];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+88] += A[i0+1558] * x[1*i0+88];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+88] += A[i0+1566] * x[1*i0+108];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+88] += A[i0+1574] * x[1*i0+268];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+88] += A[i0+1582] * x[1*i0+288];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+88] += A[i0+1590] * x[1*i0+308];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+88] += A[i0+1598] * x[1*i0+328];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+88] += A[i0+1606] * x[1*i0+368];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+91] += A[i0+1614] * x[1*i0+347];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+92] += A[i0+1622] * x[1*i0+32];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+92] += A[i0+1630] * x[1*i0+72];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+95] += A[i0+1638] * x[1*i0+351];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+96] += A[i0+1646] * x[1*i0+16];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+96] += A[i0+1654] * x[1*i0+56];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+96] += A[i0+1662] * x[1*i0+96];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+96] += A[i0+1674] * x[1*i0+276];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+96] += A[i0+1677] * x[1*i0+296];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+96] += A[i0+1680] * x[1*i0+316];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+96] += A[i0+1683] * x[1*i0+336];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+96] += A[i0+1686] * x[2*i0+355];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+96] += A[i0+1694] * x[2*i0+356];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+96] += A[i0+1702] * x[4*i0+357];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+96] += A[i0+1710] * x[4*i0+358];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+96] += A[i0+1718] * x[1*i0+376];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+97] += A[i0+1721] * x[4*i0+355];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+97] += A[i0+1729] * x[4*i0+356];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+97] += A[i0+1737] * x[4*i0+357];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+97] += A[i0+1745] * x[4*i0+358];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+98] += A[i0+1753] * x[4*i0+355];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+98] += A[i0+1761] * x[4*i0+356];
  }
  for( i0 = 0; i0 <= 5; ++i0 ) {
    y[0*i0+99] += A[i0+1773] * x[1*i0+440];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+100] += A[i0+1779] * x[1*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+100] += A[i0+1787] * x[1*i0+40];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+100] += A[i0+1795] * x[1*i0+80];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+100] += A[i0+1803] * x[1*i0+260];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+100] += A[i0+1811] * x[1*i0+280];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+100] += A[i0+1819] * x[1*i0+300];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+100] += A[i0+1827] * x[1*i0+320];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+100] += A[i0+1835] * x[1*i0+340];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+103] += A[i0+1843] * x[1*i0+359];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+104] += A[i0+1851] * x[1*i0+24];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+104] += A[i0+1859] * x[1*i0+64];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+104] += A[i0+1867] * x[1*i0+104];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+107] += A[i0+1875] * x[1*i0+363];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+108] += A[i0+1883] * x[1*i0+8];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+108] += A[i0+1891] * x[1*i0+48];
  }
}

void kernel_spmv_fragment_1(float * restrict A, float * restrict x, float * restrict y ) {
  register int i0,i1,i2,i3,i4,i5,i6;

  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+108] += A[i0+1899] * x[1*i0+88];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+108] += A[i0+1907] * x[1*i0+268];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+108] += A[i0+1915] * x[1*i0+288];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+108] += A[i0+1923] * x[1*i0+308];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+108] += A[i0+1931] * x[1*i0+328];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+108] += A[i0+1939] * x[1*i0+348];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+111] += A[i0+1947] * x[1*i0+367];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+112] += A[i0+1955] * x[1*i0+32];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+112] += A[i0+1963] * x[1*i0+72];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+112] += A[i0+1971] * x[1*i0+112];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+112] += A[i0+1979] * x[2*i0+371];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+112] += A[i0+1987] * x[2*i0+372];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+115] += A[i0+1995] * x[1*i0+371];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+116] += A[i0+2003] * x[1*i0+16];
  }
#pragma macveth unroll i0 4
  __m256 __tmp0_256, __tmp1_256, __vop2, __vop0, __vop1, __vop3, __vop6, __vop4, __vop5, __vop9, __vop7, __vop8, __vop10, __vop13, __vop11, __vop12, __vop16, __vop14, __vop15, __vop17, __vop20, __vop18, __vop19, __vop21, __vop24, __vop22, __vop23, __vop25, __vop28, __vop26, __vop27, __mv_accm0, __vop29, __mv_lo256, __mv_hi256, __tmp2_256, __vop31, __vop30, __vop32, __vop35, __vop33, __vop34, __vop36, __vop38, __vop37, __vop39, __vop42, __vop40, __vop41, __vop43, __vop46, __vop44, __vop45, __vop47, __vop50, __vop48, __vop49, __vop51, __vop54, __vop52, __vop53, __mv_accm1, __vop57, __vop55, __vop56, __mv_accm2, __vop58, __vop61, __vop59, __vop60, __vop62, __vop65, __vop63, __vop64, __vop68, __vop66, __vop67, __mv_accm3, __vop69, __vop72, __vop70, __vop71, __mv_accm4, __vop73, __vop76, __vop74, __vop75, __vop77, __vop80, __vop78, __vop79, __vop81, __vop84, __vop82, __vop83, __vop85, __vop88, __vop86, __vop87, __vop89;
__m128 __tmp0_128, __tmp1_128, __lo128, __tmp0, __tmp1, __hi128;
for( i0 = 0; i0 <= 3; i0 += 4 ) {
    __lo128 = _mm_loadu_ps(&A[2011]);
__hi128 = _mm_loadu_ps(&A[3038]);
__vop59 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&x[56]);
__hi128 = _mm_loadu_ps(&x[275]);
__vop60 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&y[116]);
__hi128 = _mm_loadu_ps(&y[233]);
__vop62 = _mm256_set_m128(__hi128, __lo128);
__vop62 = _mm256_fmadd_ps(__vop59, __vop60, __vop62);
_mm_storeu_ps(&y[116], _mm256_castps256_ps128(__vop62));
_mm_storeu_ps(&y[233], _mm256_extractf128_ps(__vop62,0x1));

    
  }
#pragma endmacveth
#pragma macveth unroll i0 4
  for( i0 = 0; i0 <= 3; i0 += 4 ) {
    __lo128 = _mm_loadu_ps(&A[2015]);
__hi128 = _mm_loadu_ps(&A[3042]);
__vop63 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&x[96]);
__hi128 = _mm_loadu_ps(&x[315]);
__vop64 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&y[116]);
__hi128 = _mm_loadu_ps(&y[233]);
__vop62 = _mm256_set_m128(__hi128, __lo128);
__vop62 = _mm256_fmadd_ps(__vop63, __vop64, __vop62);
_mm_storeu_ps(&y[116], _mm256_castps256_ps128(__vop62));
_mm_storeu_ps(&y[233], _mm256_extractf128_ps(__vop62,0x1));

    
  }
#pragma endmacveth
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+116] += A[i0+2019] * x[1*i0+276];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+116] += A[i0+2022] * x[1*i0+296];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+116] += A[i0+2025] * x[1*i0+316];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+116] += A[i0+2028] * x[1*i0+336];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+116] += A[i0+2031] * x[1*i0+356];
  }
  for( i0 = 0; i0 <= 5; ++i0 ) {
    y[0*i0+119] += A[i0+2038] * x[1*i0+440];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+120] += A[i0+2044] * x[1*i0+40];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+120] += A[i0+2052] * x[1*i0+120];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+120] += A[i0+2060] * x[1*i0+260];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+120] += A[i0+2068] * x[1*i0+280];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+120] += A[i0+2076] * x[1*i0+300];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+120] += A[i0+2084] * x[1*i0+447];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+123] += A[i0+2092] * x[1*i0+379];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+124] += A[i0+2100] * x[1*i0+24];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+127] += A[i0+2108] * x[1*i0+383];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+128] += A[i0+2116] * x[1*i0+48];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+128] += A[i0+2124] * x[1*i0+128];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+128] += A[i0+2132] * x[1*i0+268];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+128] += A[i0+2140] * x[1*i0+288];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+128] += A[i0+2148] * x[1*i0+308];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+128] += A[i0+2156] * x[4*i0+387];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+128] += A[i0+2164] * x[4*i0+388];
  }
  for( i0 = 0; i0 <= 6; ++i0 ) {
    y[4*i0+128] += A[i0+2172] * x[4*i0+389];
  }
  for( i0 = 0; i0 <= 6; ++i0 ) {
    y[4*i0+128] += A[i0+2179] * x[4*i0+390];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+128] += A[i0+2186] * x[1*i0+455];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+129] += A[i0+2194] * x[4*i0+387];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+129] += A[i0+2202] * x[4*i0+388];
  }
#pragma macveth unroll i0 4
  __mv_accm3 = _mm256_setzero_ps();
for( i0 = 0; i0 <= 1; i0 += 4 ) {
    __lo128 = _mm_loadl_pi(__lo128, &A[2210]);
__lo128 = _mm_loadh_pi(__lo128, &A[2231]);
__hi128 = _mm_loadl_pi(__hi128, &A[2440]);
__hi128 = _mm_loadh_pi(__hi128, &A[2496]);
__vop66 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadl_pi(__lo128, &x[389]);
__lo128 = _mm_loadh_pi(__lo128, &x[393]);
__hi128 = _mm_loadl_pi(__hi128, &x[413]);
__hi128 = _mm_loadh_pi(__hi128, &x[417]);
__vop67 = _mm256_set_m128(__hi128, __lo128);
__mv_accm3 = _mm256_fmadd_ps(__vop66, __vop67, __mv_accm3);

    
    
    
  }__tmp0_256 = _mm256_permute_ps(__mv_accm3, 0b00001110);
__tmp1_256 = _mm256_add_ps(__mv_accm3, __tmp0_256);
__tmp2_256 = _mm256_shuffle_ps(__tmp1_256, __tmp1_256, 0x01);
__mv_lo256 = _mm256_add_ps(__tmp1_256, __tmp2_256);
y[129] = y[129]+__mv_lo256[0];
y[133] = y[133]+__mv_lo256[2];
y[153] = y[153]+__mv_lo256[4];
y[157] = y[157]+__mv_lo256[6];

#pragma endmacveth
  for( i0 = 0; i0 <= 3; ++i0 ) {
    y[0*i0+130] += A[i0+2212] * x[1*i0+387];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+131] += A[i0+2216] * x[1*i0+387];
  }
  for( i0 = 0; i0 <= 6; ++i0 ) {
    y[1*i0+132] += A[i0+2224] * x[1*i0+32];
  }
#pragma macveth unroll i0 4
  __mv_accm4 = _mm256_setzero_ps();
for( i0 = 0; i0 <= 3; i0 += 4 ) {
    __lo128 = _mm_loadu_ps(&A[2233]);
__hi128 = _mm_loadu_ps(&A[2284]);
__vop70 = _mm256_set_m128(__hi128, __lo128);
__vop71 = _mm256_loadu_ps(&x[391]);
__mv_accm4 = _mm256_fmadd_ps(__vop70, __vop71, __mv_accm4);

    
  }__tmp0_256 = _mm256_permute_ps(__mv_accm4, 0b00001110);
__tmp1_256 = _mm256_add_ps(__mv_accm4, __tmp0_256);
__tmp2_256 = _mm256_shuffle_ps(__tmp1_256, __tmp1_256, 0x01);
__mv_lo256 = _mm256_add_ps(__tmp1_256, __tmp2_256);
y[134] = y[134]+__mv_lo256[0];
y[138] = y[138]+__mv_lo256[4];

#pragma endmacveth
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+135] += A[i0+2237] * x[1*i0+391];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+136] += A[i0+2245] * x[1*i0+56];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+136] += A[i0+2248] * x[1*i0+136];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+136] += A[i0+2256] * x[1*i0+276];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+136] += A[i0+2259] * x[1*i0+296];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+136] += A[i0+2262] * x[1*i0+316];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+136] += A[i0+2265] * x[1*i0+463];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+137] += A[i0+2268] * x[2*i0+397];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+137] += A[i0+2276] * x[2*i0+398];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+139] += A[i0+2288] * x[1*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+139] += A[i0+2296] * x[1*i0+40];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+139] += A[i0+2304] * x[1*i0+260];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+139] += A[i0+2312] * x[1*i0+280];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+139] += A[i0+2320] * x[1*i0+300];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+139] += A[i0+2328] * x[4*i0+401];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+139] += A[i0+2336] * x[4*i0+402];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+139] += A[i0+2344] * x[1*i0+447];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+142] += A[i0+2352] * x[1*i0+399];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+144] += A[i0+2360] * x[1*i0+144];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+146] += A[i0+2368] * x[1*i0+403];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+147] += A[i0+2376] * x[1*i0+8];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+147] += A[i0+2384] * x[1*i0+48];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+147] += A[i0+2392] * x[1*i0+268];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+147] += A[i0+2400] * x[1*i0+288];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+147] += A[i0+2408] * x[1*i0+308];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+147] += A[i0+2416] * x[1*i0+455];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+150] += A[i0+2424] * x[1*i0+407];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+152] += A[i0+2432] * x[1*i0+152];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+154] += A[i0+2442] * x[1*i0+411];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+155] += A[i0+2450] * x[1*i0+16];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+155] += A[i0+2453] * x[1*i0+56];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+155] += A[i0+2456] * x[1*i0+276];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+155] += A[i0+2459] * x[1*i0+296];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+155] += A[i0+2462] * x[1*i0+316];
  }
#pragma macveth
  __vop74 = _mm256_loadu_ps(&A[2465]);
__tmp0_256 = _mm256_loadu_ps(&A[4699 + (-6)]);
__vop74 = _mm256_blend_ps(__vop74, __tmp0_256, 0b11000000);
__vop75 = _mm256_i32gather_ps(&x[129], _mm256_set_epi32(0, 0, 306, 302, 298, 294, 290, 286), 4);
__lo128 = _mm_loadh_pi(__lo128, &y[389]);
__tmp0 = _mm_load_ss(&y[171]);
__hi128 = _mm_move_ss(__lo128, __tmp0);
__tmp1 = _mm_load_ss(&y[175]);
__hi128 = _mm_insert_ps(__hi128, __tmp1, 0b00010000);
__lo128 = _mm_i32gather_ps(&y[155], _mm_set_epi32(12, 8, 4, 0), 4);
__vop77 = _mm256_set_m128(__hi128, __lo128);
__vop77 = _mm256_fmadd_ps(__vop74, __vop75, __vop77);
_mm_storeh_pi(&y[389], _mm256_extractf128_ps(__vop77,0x1));
_mm_i32scatter_ps(&y[155], _mm_set_epi32(12, 8, 4, 0), _mm256_castps256_ps128(__vop77), 4);

  
  
  
  
  
  
  
#pragma endmacveth
#pragma macveth
  __vop78 = _mm256_loadu_ps(&A[2471]);
__tmp0_256 = _mm256_loadu_ps(&A[4720 + (-6)]);
__vop78 = _mm256_blend_ps(__vop78, __tmp0_256, 0b11000000);
__vop79 = _mm256_i32gather_ps(&x[133], _mm256_set_epi32(0, 0, 303, 299, 295, 291, 287, 283), 4);
__lo128 = _mm_loadh_pi(__lo128, &y[393]);
__tmp0 = _mm_load_ss(&y[171]);
__hi128 = _mm_move_ss(__lo128, __tmp0);
__tmp1 = _mm_load_ss(&y[175]);
__hi128 = _mm_insert_ps(__hi128, __tmp1, 0b00010000);
__lo128 = _mm_i32gather_ps(&y[155], _mm_set_epi32(12, 8, 4, 0), 4);
__vop81 = _mm256_set_m128(__hi128, __lo128);
__vop81 = _mm256_fmadd_ps(__vop78, __vop79, __vop81);
_mm_storeh_pi(&y[393], _mm256_extractf128_ps(__vop81,0x1));
_mm_i32scatter_ps(&y[155], _mm_set_epi32(12, 8, 4, 0), _mm256_castps256_ps128(__vop81), 4);

  
  
  
  
  
  
  
#pragma endmacveth
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+155] += A[i0+2477] * x[1*i0+463];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+156] += A[i0+2480] * x[2*i0+417];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+156] += A[i0+2488] * x[2*i0+418];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+158] += A[i0+2498] * x[1*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+158] += A[i0+2506] * x[1*i0+20];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+158] += A[i0+2514] * x[1*i0+260];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+158] += A[i0+2522] * x[1*i0+280];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+158] += A[i0+2530] * x[1*i0+300];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+158] += A[i0+2548] * x[1*i0+447];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+160] += A[i0+2556] * x[1*i0+160];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+161] += A[i0+2574] * x[1*i0+419];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+165] += A[i0+2582] * x[1*i0+423];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+166] += A[i0+2590] * x[1*i0+8];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+166] += A[i0+2598] * x[1*i0+28];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+166] += A[i0+2606] * x[1*i0+268];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+166] += A[i0+2614] * x[1*i0+288];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+166] += A[i0+2622] * x[1*i0+308];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+166] += A[i0+2630] * x[1*i0+455];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+168] += A[i0+2638] * x[1*i0+168];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+169] += A[i0+2646] * x[1*i0+427];
  }
  for( i0 = 0; i0 <= 1; ++i0 ) {
    y[0*i0+171] += A[i0+2654] * x[1*i0+433];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[2*i0+172] += A[i0+2656] * x[2*i0+433];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+173] += A[i0+2661] * x[1*i0+431];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+174] += A[i0+2669] * x[1*i0+16];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+174] += A[i0+2672] * x[1*i0+36];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+174] += A[i0+2675] * x[1*i0+276];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+174] += A[i0+2683] * x[1*i0+296];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+174] += A[i0+2691] * x[1*i0+316];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+174] += A[i0+2694] * x[1*i0+436];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+174] += A[i0+2697] * x[1*i0+463];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+176] += A[i0+2700] * x[1*i0+176];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+177] += A[i0+2708] * x[1*i0+259];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+177] += A[i0+2716] * x[1*i0+379];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+177] += A[i0+2724] * x[0*i0+439];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+182] += A[i0+2732] * x[1*i0+284];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+182] += A[i0+2740] * x[1*i0+304];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+184] += A[i0+2748] * x[1*i0+184];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+185] += A[i0+2756] * x[1*i0+267];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+185] += A[i0+2764] * x[1*i0+387];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+185] += A[i0+2772] * x[0*i0+439];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+190] += A[i0+2780] * x[1*i0+292];
  }
  for( i0 = 0; i0 <= 6; ++i0 ) {
    y[1*i0+190] += A[i0+2788] * x[1*i0+312];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+192] += A[i0+2795] * x[1*i0+192];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+193] += A[i0+2803] * x[1*i0+275];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+193] += A[i0+2811] * x[1*i0+395];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+193] += A[i0+2819] * x[0*i0+439];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+197] += A[i0+2827] * x[1*i0+259];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+198] += A[i0+2835] * x[1*i0+300];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+200] += A[i0+2843] * x[1*i0+200];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+201] += A[i0+2851] * x[1*i0+283];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+201] += A[i0+2859] * x[1*i0+403];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+201] += A[i0+2867] * x[0*i0+439];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+205] += A[i0+2875] * x[1*i0+267];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+206] += A[i0+2883] * x[1*i0+308];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+208] += A[i0+2891] * x[1*i0+208];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+209] += A[i0+2899] * x[1*i0+291];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+209] += A[i0+2907] * x[1*i0+411];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+209] += A[i0+2915] * x[0*i0+439];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+213] += A[i0+2923] * x[1*i0+275];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+214] += A[i0+2931] * x[1*i0+316];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+216] += A[i0+2934] * x[1*i0+216];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+217] += A[i0+2942] * x[1*i0+259];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+217] += A[i0+2950] * x[1*i0+299];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+217] += A[i0+2958] * x[1*i0+419];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+217] += A[i0+2966] * x[0*i0+439];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+221] += A[i0+2974] * x[1*i0+283];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+224] += A[i0+2982] * x[1*i0+224];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+225] += A[i0+2990] * x[1*i0+267];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+225] += A[i0+2998] * x[1*i0+307];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+225] += A[i0+3006] * x[1*i0+427];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+225] += A[i0+3014] * x[0*i0+439];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+229] += A[i0+3022] * x[1*i0+291];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+232] += A[i0+3030] * x[1*i0+232];
  }
#pragma macveth unroll i0 4
  for( i0 = 0; i0 <= 3; i0 += 4 ) {
    __lo128 = _mm_loadu_ps(&A[3046]);
__hi128 = _mm_loadu_ps(&A[3391]);
__vop82 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&x[435]);
__hi128 = _mm_i32gather_ps(&x[19], _mm_set_epi32(0, 0, 0, 0), 4);
__vop83 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&y[233]);
__hi128 = _mm_loadu_ps(&y[275]);
__vop85 = _mm256_set_m128(__hi128, __lo128);
__vop85 = _mm256_fmadd_ps(__vop82, __vop83, __vop85);
_mm_storeu_ps(&y[233], _mm256_castps256_ps128(__vop85));
_mm_storeu_ps(&y[275], _mm256_extractf128_ps(__vop85,0x1));

    
  }
#pragma endmacveth
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+238] += A[i0+3055] * x[1*i0+446];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+240] += A[i0+3063] * x[1*i0+240];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+246] += A[i0+3071] * x[1*i0+454];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+248] += A[i0+3079] * x[1*i0+248];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+256] += A[i0+3092] * x[1*i0+256];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+259] += A[i0+3095] * x[2*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+259] += A[i0+3103] * x[4*i0+1];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+259] += A[i0+3111] * x[4*i0+2];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+259] += A[i0+3119] * x[0*i0+3];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+259] += A[i0+3127] * x[1*i0+177];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+259] += A[i0+3135] * x[1*i0+197];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+259] += A[i0+3143] * x[1*i0+217];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+260] += A[i0+3151] * x[2*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+260] += A[i0+3159] * x[4*i0+1];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+260] += A[i0+3167] * x[4*i0+2];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+260] += A[i0+3175] * x[1*i0+20];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+260] += A[i0+3183] * x[1*i0+40];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+260] += A[i0+3191] * x[1*i0+60];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+260] += A[i0+3199] * x[1*i0+80];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+260] += A[i0+3207] * x[1*i0+100];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+260] += A[i0+3215] * x[1*i0+120];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+260] += A[i0+3223] * x[1*i0+139];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+260] += A[i0+3231] * x[1*i0+158];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+261] += A[i0+3239] * x[4*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+261] += A[i0+3247] * x[4*i0+1];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+262] += A[i0+3255] * x[4*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+262] += A[i0+3263] * x[4*i0+1];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+263] += A[i0+3271] * x[0*i0+7];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+267] += A[i0+3279] * x[0*i0+11];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+267] += A[i0+3287] * x[1*i0+185];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+267] += A[i0+3295] * x[1*i0+205];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+267] += A[i0+3303] * x[1*i0+225];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+268] += A[i0+3311] * x[1*i0+28];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+268] += A[i0+3319] * x[1*i0+48];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+268] += A[i0+3327] * x[1*i0+68];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+268] += A[i0+3335] * x[1*i0+88];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+268] += A[i0+3343] * x[1*i0+108];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+268] += A[i0+3351] * x[1*i0+128];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+268] += A[i0+3359] * x[1*i0+147];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+268] += A[i0+3367] * x[1*i0+166];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+271] += A[i0+3375] * x[0*i0+15];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+275] += A[i0+3383] * x[2*i0+16];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+275] += A[i0+3395] * x[1*i0+193];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+275] += A[i0+3403] * x[1*i0+213];
  }
#pragma macveth unroll i0 4
  for( i0 = 0; i0 <= 3; i0 += 4 ) {
    __lo128 = _mm_loadu_ps(&A[3411]);
__hi128 = _mm_loadu_ps(&A[3740]);
__vop86 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&x[233]);
__hi128 = _mm_i32gather_ps(&x[39], _mm_set_epi32(0, 0, 0, 0), 4);
__vop87 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&y[275]);
__hi128 = _mm_loadu_ps(&y[295]);
__vop89 = _mm256_set_m128(__hi128, __lo128);
__vop89 = _mm256_fmadd_ps(__vop86, __vop87, __vop89);
_mm_storeu_ps(&y[275], _mm256_castps256_ps128(__vop89));
_mm_storeu_ps(&y[295], _mm256_extractf128_ps(__vop89,0x1));

    
  }
#pragma endmacveth
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+276] += A[i0+3415] * x[2*i0+16];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+276] += A[i0+3423] * x[1*i0+36];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+276] += A[i0+3426] * x[1*i0+56];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+276] += A[i0+3429] * x[1*i0+76];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+276] += A[i0+3432] * x[1*i0+96];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+276] += A[i0+3435] * x[1*i0+116];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+276] += A[i0+3438] * x[1*i0+136];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+276] += A[i0+3441] * x[1*i0+155];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+276] += A[i0+3444] * x[1*i0+174];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+279] += A[i0+3452] * x[0*i0+23];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+280] += A[i0+3460] * x[1*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+280] += A[i0+3468] * x[1*i0+40];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+280] += A[i0+3476] * x[1*i0+60];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+280] += A[i0+3484] * x[1*i0+80];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+280] += A[i0+3492] * x[1*i0+100];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+280] += A[i0+3500] * x[1*i0+120];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+280] += A[i0+3508] * x[1*i0+139];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+280] += A[i0+3516] * x[1*i0+158];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+283] += A[i0+3524] * x[0*i0+27];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+283] += A[i0+3532] * x[1*i0+201];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+283] += A[i0+3540] * x[1*i0+221];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+284] += A[i0+3548] * x[1*i0+182];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+287] += A[i0+3556] * x[0*i0+31];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+288] += A[i0+3564] * x[1*i0+8];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+288] += A[i0+3572] * x[1*i0+48];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+288] += A[i0+3580] * x[1*i0+68];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+288] += A[i0+3588] * x[1*i0+88];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+288] += A[i0+3596] * x[1*i0+108];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+288] += A[i0+3604] * x[1*i0+128];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+288] += A[i0+3612] * x[1*i0+147];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+288] += A[i0+3620] * x[1*i0+166];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+291] += A[i0+3628] * x[2*i0+32];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+291] += A[i0+3636] * x[4*i0+33];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+291] += A[i0+3644] * x[4*i0+34];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+291] += A[i0+3652] * x[0*i0+35];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+291] += A[i0+3660] * x[1*i0+209];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+291] += A[i0+3668] * x[1*i0+229];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+292] += A[i0+3676] * x[2*i0+32];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+292] += A[i0+3684] * x[4*i0+33];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+292] += A[i0+3692] * x[4*i0+34];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+292] += A[i0+3700] * x[1*i0+190];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+293] += A[i0+3708] * x[4*i0+32];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+293] += A[i0+3716] * x[4*i0+33];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+294] += A[i0+3724] * x[4*i0+32];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+294] += A[i0+3732] * x[4*i0+33];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+296] += A[i0+3744] * x[1*i0+16];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+296] += A[i0+3747] * x[1*i0+56];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+296] += A[i0+3750] * x[1*i0+76];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+296] += A[i0+3753] * x[1*i0+96];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+296] += A[i0+3756] * x[1*i0+116];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+296] += A[i0+3759] * x[1*i0+136];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+296] += A[i0+3762] * x[1*i0+155];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+296] += A[i0+3765] * x[1*i0+174];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+299] += A[i0+3773] * x[0*i0+43];
  }
}

void kernel_spmv_fragment_2(float * restrict A, float * restrict x, float * restrict y ) {
  register int i0,i1,i2,i3,i4,i5,i6;

  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+299] += A[i0+3781] * x[1*i0+217];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+300] += A[i0+3789] * x[1*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+300] += A[i0+3797] * x[1*i0+20];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+300] += A[i0+3805] * x[1*i0+60];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+300] += A[i0+3813] * x[1*i0+80];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+300] += A[i0+3821] * x[1*i0+100];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+300] += A[i0+3829] * x[1*i0+120];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+300] += A[i0+3837] * x[1*i0+139];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+300] += A[i0+3845] * x[1*i0+158];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+300] += A[i0+3853] * x[1*i0+198];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+303] += A[i0+3861] * x[0*i0+47];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+304] += A[i0+3869] * x[1*i0+182];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+307] += A[i0+3877] * x[2*i0+48];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+307] += A[i0+3885] * x[0*i0+51];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+307] += A[i0+3893] * x[1*i0+225];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+308] += A[i0+3901] * x[1*i0+8];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+308] += A[i0+3909] * x[1*i0+28];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+308] += A[i0+3917] * x[2*i0+48];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+308] += A[i0+3925] * x[1*i0+68];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+308] += A[i0+3933] * x[1*i0+88];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+308] += A[i0+3941] * x[1*i0+108];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+308] += A[i0+3949] * x[1*i0+128];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+308] += A[i0+3957] * x[1*i0+147];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+308] += A[i0+3965] * x[1*i0+166];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+308] += A[i0+3973] * x[1*i0+206];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+311] += A[i0+3981] * x[0*i0+55];
  }
  for( i0 = 0; i0 <= 6; ++i0 ) {
    y[1*i0+312] += A[i0+3989] * x[1*i0+190];
  }
#pragma macveth unroll i0 4
  __m256 __tmp0_256, __tmp1_256, __vop2, __vop0, __vop1, __vop3, __vop6, __vop4, __vop5, __vop9, __vop7, __vop8, __vop10, __vop13, __vop11, __vop12, __vop16, __vop14, __vop15, __vop17, __vop20, __vop18, __vop19, __vop21, __vop24, __vop22, __vop23, __vop25, __vop28, __vop26, __vop27, __mv_accm0, __vop29, __mv_lo256, __mv_hi256, __tmp2_256, __vop31, __vop30, __vop32, __vop35, __vop33, __vop34, __vop36, __vop38, __vop37, __vop39, __vop42, __vop40, __vop41, __vop43, __vop46, __vop44, __vop45, __vop47, __vop50, __vop48, __vop49, __vop51, __vop54, __vop52, __vop53, __mv_accm1, __vop57, __vop55, __vop56, __mv_accm2, __vop58, __vop61, __vop59, __vop60, __vop62, __vop65, __vop63, __vop64, __vop68, __vop66, __vop67, __mv_accm3, __vop69, __vop72, __vop70, __vop71, __mv_accm4, __vop73, __vop76, __vop74, __vop75, __vop77, __vop80, __vop78, __vop79, __vop81, __vop84, __vop82, __vop83, __vop85, __vop88, __vop86, __vop87, __vop89, __vop92, __vop90, __vop91, __vop93, __vop95, __vop94, __vop96, __vop99, __vop97, __vop98, __vop100, __vop103, __vop101, __vop102, __vop104, __vop107, __vop105, __vop106, __vop108, __vop110, __vop109, __vop111, __vop113, __vop112, __vop114;
__m128 __tmp0_128, __tmp1_128, __lo128, __tmp0, __tmp1, __hi128;
for( i0 = 0; i0 <= 3; i0 += 4 ) {
    __lo128 = _mm_loadu_ps(&A[3996]);
__hi128 = _mm_loadu_ps(&A[4223]);
__vop90 = _mm256_set_m128(__hi128, __lo128);
__vop91 = _mm256_i32gather_ps(&x[59], _mm256_set_epi32(20, 20, 20, 20, 0, 0, 0, 0), 4);
__lo128 = _mm_loadu_ps(&y[315]);
__hi128 = _mm_loadu_ps(&y[335]);
__vop93 = _mm256_set_m128(__hi128, __lo128);
__vop93 = _mm256_fmadd_ps(__vop90, __vop91, __vop93);
_mm_storeu_ps(&y[315], _mm256_castps256_ps128(__vop93));
_mm_storeu_ps(&y[335], _mm256_extractf128_ps(__vop93,0x1));

    
  }
#pragma endmacveth
#pragma macveth unroll i0 4
  for( i0 = 0; i0 <= 3; i0 += 4 ) {
    __lo128 = _mm_loadu_ps(&A[4000]);
__hi128 = _mm_loadu_ps(&A[4394]);
__vop94 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&x[233]);
__hi128 = _mm_i32gather_ps(&x[99], _mm_set_epi32(0, 0, 0, 0), 4);
__vop87 = _mm256_set_m128(__hi128, __lo128);
__lo128 = _mm_loadu_ps(&y[315]);
__hi128 = _mm_loadu_ps(&y[355]);
__vop96 = _mm256_set_m128(__hi128, __lo128);
__vop96 = _mm256_fmadd_ps(__vop94, __vop87, __vop96);
_mm_storeu_ps(&y[315], _mm256_castps256_ps128(__vop96));
_mm_storeu_ps(&y[355], _mm256_extractf128_ps(__vop96,0x1));

    
  }
#pragma endmacveth
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+316] += A[i0+4004] * x[1*i0+16];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+316] += A[i0+4007] * x[1*i0+36];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+316] += A[i0+4010] * x[1*i0+76];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+316] += A[i0+4013] * x[1*i0+96];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+316] += A[i0+4016] * x[1*i0+116];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+316] += A[i0+4019] * x[1*i0+136];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+316] += A[i0+4022] * x[1*i0+155];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+316] += A[i0+4025] * x[1*i0+174];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+316] += A[i0+4028] * x[1*i0+214];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+319] += A[i0+4031] * x[0*i0+63];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+320] += A[i0+4039] * x[1*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+320] += A[i0+4047] * x[1*i0+20];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+320] += A[i0+4055] * x[1*i0+40];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+320] += A[i0+4063] * x[1*i0+80];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+320] += A[i0+4071] * x[1*i0+100];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+323] += A[i0+4079] * x[2*i0+64];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+323] += A[i0+4087] * x[4*i0+65];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+323] += A[i0+4095] * x[4*i0+66];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+323] += A[i0+4103] * x[0*i0+67];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+324] += A[i0+4111] * x[2*i0+64];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+324] += A[i0+4119] * x[4*i0+65];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+324] += A[i0+4127] * x[4*i0+66];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+325] += A[i0+4135] * x[4*i0+64];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+325] += A[i0+4143] * x[4*i0+65];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+326] += A[i0+4151] * x[4*i0+64];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+326] += A[i0+4159] * x[4*i0+65];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+327] += A[i0+4167] * x[0*i0+71];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+328] += A[i0+4175] * x[1*i0+8];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+328] += A[i0+4183] * x[1*i0+28];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+328] += A[i0+4191] * x[1*i0+48];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+328] += A[i0+4199] * x[1*i0+88];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+328] += A[i0+4207] * x[1*i0+108];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+331] += A[i0+4215] * x[0*i0+75];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+336] += A[i0+4227] * x[1*i0+16];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+336] += A[i0+4230] * x[1*i0+36];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+336] += A[i0+4233] * x[1*i0+56];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+336] += A[i0+4236] * x[1*i0+96];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+336] += A[i0+4239] * x[1*i0+116];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+339] += A[i0+4242] * x[2*i0+80];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+339] += A[i0+4250] * x[0*i0+83];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+340] += A[i0+4258] * x[1*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+340] += A[i0+4266] * x[1*i0+20];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+340] += A[i0+4274] * x[1*i0+40];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+340] += A[i0+4282] * x[1*i0+60];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+340] += A[i0+4290] * x[2*i0+80];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+340] += A[i0+4298] * x[1*i0+100];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+343] += A[i0+4306] * x[0*i0+87];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+347] += A[i0+4314] * x[0*i0+91];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+348] += A[i0+4322] * x[1*i0+8];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+348] += A[i0+4330] * x[1*i0+28];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+348] += A[i0+4338] * x[1*i0+48];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+348] += A[i0+4346] * x[1*i0+68];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+348] += A[i0+4354] * x[1*i0+108];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+351] += A[i0+4362] * x[0*i0+95];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+355] += A[i0+4370] * x[2*i0+96];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+355] += A[i0+4378] * x[4*i0+97];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+355] += A[i0+4386] * x[4*i0+98];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+356] += A[i0+4398] * x[1*i0+16];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+356] += A[i0+4401] * x[1*i0+36];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+356] += A[i0+4404] * x[1*i0+56];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+356] += A[i0+4407] * x[1*i0+76];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+356] += A[i0+4410] * x[2*i0+96];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+356] += A[i0+4418] * x[4*i0+97];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+356] += A[i0+4426] * x[4*i0+98];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+356] += A[i0+4434] * x[1*i0+116];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+357] += A[i0+4437] * x[4*i0+96];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+357] += A[i0+4445] * x[4*i0+97];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+358] += A[i0+4453] * x[4*i0+96];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+358] += A[i0+4461] * x[4*i0+97];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+359] += A[i0+4469] * x[0*i0+103];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+360] += A[i0+4477] * x[1*i0+0];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+360] += A[i0+4485] * x[1*i0+20];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+360] += A[i0+4493] * x[1*i0+40];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+360] += A[i0+4501] * x[1*i0+60];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+360] += A[i0+4509] * x[1*i0+80];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+363] += A[i0+4517] * x[0*i0+107];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+367] += A[i0+4525] * x[0*i0+111];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+368] += A[i0+4533] * x[1*i0+8];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+368] += A[i0+4541] * x[1*i0+28];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+368] += A[i0+4549] * x[1*i0+48];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+368] += A[i0+4557] * x[1*i0+68];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+368] += A[i0+4565] * x[1*i0+88];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+371] += A[i0+4573] * x[2*i0+112];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+371] += A[i0+4581] * x[0*i0+115];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+372] += A[i0+4589] * x[2*i0+112];
  }
#pragma macveth unroll i0 4
  for( i0 = 0; i0 <= 3; i0 += 4 ) {
    __lo128 = _mm_loadu_ps(&A[4597]);
__hi128 = _mm_loadu_ps(&A[4656]);
__vop97 = _mm256_set_m128(__hi128, __lo128);
__vop98 = _mm256_i32gather_ps(&x[119], _mm256_set_epi32(11, 11, 11, 11, 0, 0, 0, 0), 4);
__lo128 = _mm_loadu_ps(&y[375]);
__hi128 = _mm_loadu_ps(&y[387]);
__vop100 = _mm256_set_m128(__hi128, __lo128);
__vop100 = _mm256_fmadd_ps(__vop97, __vop98, __vop100);
_mm_storeu_ps(&y[375], _mm256_castps256_ps128(__vop100));
_mm_storeu_ps(&y[387], _mm256_extractf128_ps(__vop100,0x1));

    
  }
#pragma endmacveth
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+376] += A[i0+4601] * x[1*i0+16];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+376] += A[i0+4604] * x[1*i0+36];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+376] += A[i0+4607] * x[1*i0+56];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+376] += A[i0+4610] * x[1*i0+76];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+376] += A[i0+4613] * x[1*i0+96];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+379] += A[i0+4616] * x[0*i0+123];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+379] += A[i0+4624] * x[1*i0+177];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+383] += A[i0+4632] * x[0*i0+127];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+387] += A[i0+4640] * x[4*i0+128];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+387] += A[i0+4648] * x[4*i0+129];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+387] += A[i0+4660] * x[0*i0+131];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+387] += A[i0+4668] * x[1*i0+185];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+388] += A[i0+4676] * x[4*i0+128];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+388] += A[i0+4684] * x[4*i0+129];
  }
  for( i0 = 0; i0 <= 6; ++i0 ) {
    y[4*i0+389] += A[i0+4692] * x[4*i0+128];
  }
  for( i0 = 0; i0 <= 6; ++i0 ) {
    y[4*i0+390] += A[i0+4701] * x[4*i0+128];
  }
#pragma macveth unroll i0 4
  for( i0 = 0; i0 <= 3; i0 += 4 ) {
    __lo128 = _mm_loadu_ps(&A[4708]);
__hi128 = _mm_loadu_ps(&A[4722]);
__vop101 = _mm256_set_m128(__hi128, __lo128);
__vop102 = _mm256_i32gather_ps(&x[134], _mm256_set_epi32(4, 4, 4, 4, 0, 0, 0, 0), 4);
__vop104 = _mm256_loadu_ps(&y[391]);
__vop104 = _mm256_fmadd_ps(__vop101, __vop102, __vop104);
_mm256_storeu_ps(&y[391], __vop104);

    
  }
#pragma endmacveth
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+391] += A[i0+4712] * x[0*i0+135];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+395] += A[i0+4726] * x[1*i0+193];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+397] += A[i0+4734] * x[2*i0+137];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+398] += A[i0+4742] * x[2*i0+137];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+399] += A[i0+4750] * x[0*i0+142];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+401] += A[i0+4758] * x[4*i0+139];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[4*i0+402] += A[i0+4766] * x[4*i0+139];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+403] += A[i0+4774] * x[0*i0+146];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+403] += A[i0+4782] * x[1*i0+201];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+407] += A[i0+4790] * x[0*i0+150];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+411] += A[i0+4798] * x[0*i0+154];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+411] += A[i0+4806] * x[1*i0+209];
  }
#pragma macveth
  __vop105 = _mm256_loadu_ps(&A[4814]);
__vop106 = _mm256_i32gather_ps(&x[153], _mm256_set_epi32(22, 18, 14, 10, 6, 2, 0, 0), 4);
__lo128 = _mm_loadu_ps(&y[413]);
__tmp0 = _mm_load_ss(&y[419]);
__lo128 = _mm_insert_ps(__lo128, __tmp0, 0b00110000);
__hi128 = _mm_i32gather_ps(&y[423], _mm_set_epi32(22, 18, 14, 10), 4);
__vop108 = _mm256_set_m128(__hi128, __lo128);
__vop108 = _mm256_fmadd_ps(__vop105, __vop106, __vop108);
_mm_i32scatter_ps(&y[423], _mm_set_epi32(22, 18, 14, 10), _mm256_extractf128_ps(__vop108,0x1), 4);

  
  
  
  
  
  
  
#pragma endmacveth
#pragma macveth
  __vop109 = _mm256_loadu_ps(&A[4822]);
__tmp0_256 = _mm256_loadu_ps(&A[4836 + (-6)]);
__vop109 = _mm256_blend_ps(__vop109, __tmp0_256, 0b11000000);
__lo128 = _mm_loadh_pi(__lo128, &y[417]);
__tmp0 = _mm_load_ss(&y[432]);
__hi128 = _mm_move_ss(__lo128, __tmp0);
__tmp1 = _mm_load_ss(&y[436]);
__hi128 = _mm_insert_ps(__hi128, __tmp1, 0b00010000);
__lo128 = _mm_i32gather_ps(&y[416], _mm_set_epi32(12, 8, 4, 0), 4);
__vop111 = _mm256_set_m128(__hi128, __lo128);
__vop111 = _mm256_fmadd_ps(__vop109, __vop106, __vop111);
_mm_storeh_pi(&y[417], _mm256_extractf128_ps(__vop111,0x1));
_mm_i32scatter_ps(&y[416], _mm_set_epi32(12, 8, 4, 0), _mm256_castps256_ps128(__vop111), 4);

  
  
  
  
  
  
  
#pragma endmacveth
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+417] += A[i0+4828] * x[2*i0+156];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[2*i0+418] += A[i0+4838] * x[2*i0+156];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+419] += A[i0+4851] * x[0*i0+161];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+419] += A[i0+4859] * x[1*i0+217];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+423] += A[i0+4882] * x[0*i0+165];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+427] += A[i0+4890] * x[0*i0+169];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+427] += A[i0+4898] * x[1*i0+225];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+431] += A[i0+4906] * x[0*i0+173];
  }
#pragma macveth
  __vop112 = _mm256_loadu_ps(&A[4989 + (-2)]);
__tmp0_128 = _mm_load_ss(&A[4914]);
__vop112 = _mm256_blend_ps(__vop112, _mm256_castps128_ps256(__tmp0_128), 0b00000011);
__vop114 = _mm256_loadu_ps(&y[440 + (-2)]);
__tmp0_128 = _mm_load_ss(&y[433]);
__vop114 = _mm256_blend_ps(__vop114, _mm256_castps128_ps256(__tmp0_128), 0b00000001);
__tmp0_128 = _mm_loadu_ps(&y[438 + (-1)]);
__vop114 = _mm256_blend_ps(__vop114, _mm256_castps128_ps256(__tmp0_128), 0b00000010);
__vop114 = _mm256_fmadd_ps(__vop112, __vop106, __vop114);
_mm_storeh_pi(&y[440], _mm256_castps256_ps128(__vop114));
_mm_storeu_ps(&y[442], _mm256_extractf128_ps(__vop114,0x1));

  
  
  
  
  
  
  
#pragma endmacveth
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[2*i0+433] += A[i0+4916] * x[2*i0+172];
  }
  for( i0 = 0; i0 <= 1; ++i0 ) {
    y[0*i0+434] += A[i0+4919] * x[1*i0+171];
  }
  for( i0 = 0; i0 <= 3; ++i0 ) {
    y[1*i0+435] += A[i0+4921] * x[1*i0+233];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+436] += A[i0+4925] * x[1*i0+174];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+439] += A[i0+4928] * x[1*i0+177];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+439] += A[i0+4936] * x[1*i0+185];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+439] += A[i0+4944] * x[1*i0+193];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+439] += A[i0+4952] * x[1*i0+201];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+439] += A[i0+4960] * x[1*i0+209];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+439] += A[i0+4968] * x[1*i0+217];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[0*i0+439] += A[i0+4976] * x[1*i0+225];
  }
  for( i0 = 0; i0 <= 4; ++i0 ) {
    y[0*i0+439] += A[i0+4984] * x[1*i0+233];
  }
  for( i0 = 0; i0 <= 5; ++i0 ) {
    y[1*i0+440] += A[i0+4995] * x[0*i0+39];
  }
  for( i0 = 0; i0 <= 5; ++i0 ) {
    y[1*i0+440] += A[i0+5001] * x[0*i0+59];
  }
  for( i0 = 0; i0 <= 5; ++i0 ) {
    y[1*i0+440] += A[i0+5007] * x[0*i0+79];
  }
  for( i0 = 0; i0 <= 5; ++i0 ) {
    y[1*i0+440] += A[i0+5013] * x[0*i0+99];
  }
  for( i0 = 0; i0 <= 5; ++i0 ) {
    y[1*i0+440] += A[i0+5019] * x[0*i0+119];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+446] += A[i0+5025] * x[1*i0+238];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+447] += A[i0+5033] * x[1*i0+120];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+447] += A[i0+5041] * x[1*i0+139];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+447] += A[i0+5049] * x[1*i0+158];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+454] += A[i0+5057] * x[1*i0+246];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+455] += A[i0+5065] * x[1*i0+128];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+455] += A[i0+5073] * x[1*i0+147];
  }
  for( i0 = 0; i0 <= 7; ++i0 ) {
    y[1*i0+455] += A[i0+5081] * x[1*i0+166];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+463] += A[i0+5094] * x[1*i0+136];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+463] += A[i0+5097] * x[1*i0+155];
  }
  for( i0 = 0; i0 <= 2; ++i0 ) {
    y[1*i0+463] += A[i0+5100] * x[1*i0+174];
  }
}

void kernel_spmv( float * restrict A, float * restrict x, float * restrict y ) {
  register int i, j;

  kernel_spmv_fragment_0( A, x, y );
  kernel_spmv_fragment_1( A, x, y );
  kernel_spmv_fragment_2( A, x, y );
}

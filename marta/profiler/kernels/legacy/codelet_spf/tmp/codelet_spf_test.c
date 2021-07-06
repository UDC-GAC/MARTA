#ifndef DATA_TYPE
#define DATA_TYPE float
#endif

#ifndef INLINE_PREFIX
#define INLINE_PREFIX __attribute__((always_inline)) inline
#endif

INLINE_PREFIX void codelet_spf(DATA_TYPE *restrict A, DATA_TYPE *restrict x,
                               DATA_TYPE *restrict y) {

  register int i, j;
  // for (i = 0; i <= 16579; ++i) {
#if defined(SCATTER_Y_0)
// LINE 5548
#pragma macveth unroll i 1 j 4
  for (i = 0; i <= 158; ++i) {
    for (j = 0; j <= 3; ++j) {
      y[8 * i + 2 * j + 851048] +=
          A[4 * i + j + 2632330] * x[8 * i + 0 * j + 5756];
    }
  }
  for (i = 0; i <= 158; ++i) {
    for (j = 0; j <= 3; ++j) {
      y[8 * i + 2 * j + 851681] +=
          A[4 * i + j + 2632966] * x[8 * i + 0 * j + 6389];
    }
  }
#pragma endmacveth
#elif defined(SCATTER_Y_1)
// LINE 5548
#pragma macveth unroll i 2 j 4
  for (i = 0; i <= 158; ++i) {
    for (j = 0; j <= 3; ++j) {
      y[8 * i + 2 * j + 851048] +=
          A[4 * i + j + 2632330] * x[8 * i + 0 * j + 5756];
    }
  }
#pragma endmacveth
#elif defined(ONE_REDUCTION_Y)
#pragma macveth unroll i full
  for (i = 0; i <= 3; ++i) {
    y[0 * i + 1] += A[i + 2083151] * x[1 * i + 27429];
    y[0 * i + 1] += A[i + 2083155] * x[1 * i + 37983];
  }
  // for (i = 0; i <= 3; ++i) {
  //   y[0 * i + 1] += A[i + 2083155] * x[1 * i + 37983];
  // }
#pragma endmacveth
#endif
}

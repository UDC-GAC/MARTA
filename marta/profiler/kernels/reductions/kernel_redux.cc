#include "kernel_redux.h"

#if KERNEL == REDUX
void kernel_redux(
    int m, int n, int _uI, int _uIt, int _uIs, int _uJ, int _uJt, int _uJs,
    DATA_TYPE POLYBENCH_2D(A, M, N, m, n), DATA_TYPE POLYBENCH_1D(x, N, n),
    DATA_TYPE POLYBENCH_1D(y, N, n)
#if STMT >= 2
        ,
    DATA_TYPE POLYBENCH_2D(B, M, N, m, n), DATA_TYPE POLYBENCH_1D(w, N, n),
    DATA_TYPE POLYBENCH_1D(z, N, n)
#endif
#if STMT >= 3
        ,
    DATA_TYPE POLYBENCH_2D(C, M, N, m, n), DATA_TYPE POLYBENCH_1D(xx, N, n),
    DATA_TYPE POLYBENCH_1D(yy, N, n)
#endif
#if STMT >= 4
        ,
    DATA_TYPE POLYBENCH_2D(D, M, N, m, n), DATA_TYPE POLYBENCH_1D(ww, N, n),
    DATA_TYPE POLYBENCH_1D(zz, N, n)
#endif
) {
  int i, j;

  for (i = _uI; i < _uI + _uIt; i += _uIs) {
    for (j = _uJ; j < _uJ + _uJt; j += _uJs) {
      y[i] = y[i] + A[i][j] * x[j];
    }
  }
#if STMT >= 2
  for (i = _uI; i < _uI + _uIt; i += _uIs) {
    for (j = _uJ; j < _uJ + _uJt; j += _uJs) {
      z[i] = z[i] + B[i][j] * w[j];
    }
  }
#endif
#if STMT >= 3
  for (i = _uI; i < _uI + _uIt; i += _uIs) {
    for (j = _uJ; j < _uJ + _uJt; j += _uJs) {
      yy[i] = yy[i] + C[i][j] * xx[j];
    }
  }
#endif
#if STMT >= 4
  for (i = _uI; i < _uI + _uIt; i += _uIs) {
    for (j = _uJ; j < _uJ + _uJt; j += _uJs) {
      zz[i] = zz[i] + D[i][j] * ww[j];
    }
  }
#endif
}
#elif KERNEL == REDUXFUSED
void kernel_redux(
    int m, int n, int _uI, int _uIt, int _uIs, int _uJ, int _uJt, int _uJs,
    DATA_TYPE POLYBENCH_2D(A, M, N, m, n), DATA_TYPE POLYBENCH_1D(x, N, n),
    DATA_TYPE POLYBENCH_1D(y, N, n)
#if STMT >= 2
        ,
    DATA_TYPE POLYBENCH_2D(B, M, N, m, n), DATA_TYPE POLYBENCH_1D(w, N, n),
    DATA_TYPE POLYBENCH_1D(z, N, n)
#endif
#if STMT >= 3
        ,
    DATA_TYPE POLYBENCH_2D(C, M, N, m, n), DATA_TYPE POLYBENCH_1D(xx, N, n),
    DATA_TYPE POLYBENCH_1D(yy, N, n)
#endif
#if STMT >= 4
        ,
    DATA_TYPE POLYBENCH_2D(D, M, N, m, n), DATA_TYPE POLYBENCH_1D(ww, N, n),
    DATA_TYPE POLYBENCH_1D(zz, N, n)
#endif
) {
  int i, j;

  for (i = _uI; i < _uI + _uIt; i += _uIs) {
    for (j = _uJ; j < _uJ + _uJt; j += _uJs) {
      y[i] = y[i] + A[i][j] * x[j];
#if STMT >= 2
      z[i] = z[i] + B[i][j] * w[j];
#endif
#if STMT >= 3
      yy[i] = yy[i] + C[i][j] * xx[j];
#endif
#if STMT >= 4
      zz[i] = zz[i] + D[i][j] * ww[j];
#endif
    }
  }
}
#endif

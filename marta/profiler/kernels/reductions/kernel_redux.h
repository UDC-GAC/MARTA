#ifndef _KERNEL_H
#define _KERNEL_H
#include "definitions.h"
#include "polybench.h"

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
);

#endif

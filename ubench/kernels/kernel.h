#ifndef _KERNEL_H
#define _KERNEL_H
#include <polybench.h>
#include "definitions.h"
void kernel_spmvstyle(int m, int n,
        int _uI, int _uIt, int _uIs,
        int _uJ, int _uJt, int _uJs,
        DATA_TYPE POLYBENCH_2D(A,M,N,m,n),
        DATA_TYPE POLYBENCH_1D(x,N,n),
        DATA_TYPE POLYBENCH_1D(y,N,n));
#endif

/**
 * This version is stamped on May 10, 2016
 *
 * Contact:
 *   Louis-Noel Pouchet <pouchet.ohio-state.edu>
 *   Tomofumi Yuki <tomofumi.yuki.fr>
 *
 * Web address: http://polybench.sourceforge.net
 */
/* spmvstyle.c: this file is part of PolyBench/C */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include polybench common header. */
#include <polybench.h>

/* Include benchmark-specific header. */
#include "definitions.h"

#if KERNEL==REDUX
#include "kernel_redux.h"
#define KERNEL_NAME kernel_redux
#endif

/* Array initialization. */
static void init_arrays(int m, int n,
        DATA_TYPE POLYBENCH_2D(A,M,N,m,n),
        DATA_TYPE POLYBENCH_1D(x,N,n),
        DATA_TYPE POLYBENCH_1D(y,N,n))
{
    int i, j;
    DATA_TYPE fn;
    fn = (DATA_TYPE)n;

    for (i = 0; i < n; i++) {
        x[i] = 1 + (i / fn);
        y[i] = 2 + (i / fn);
    }
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            A[i][j] = (DATA_TYPE) ((i+j) % n) / (5*m);
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static void print_array1d(int n,
        DATA_TYPE POLYBENCH_1D(y,N,n))

{
    int i;

    POLYBENCH_DUMP_START;
    POLYBENCH_DUMP_BEGIN("y");
    for (i = 0; i < n; i++) {
        if (i % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
        fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, y[i]);
    }
    POLYBENCH_DUMP_END("y");
    POLYBENCH_DUMP_FINISH;
}

/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static void print_array2d(int n,
        DATA_TYPE POLYBENCH_2D(A,N,N,n,n))

{
    int i, j;

    POLYBENCH_DUMP_START;
    POLYBENCH_DUMP_BEGIN("A");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
            fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, A[i][j]);
        }
    }
    POLYBENCH_DUMP_END("A");
    POLYBENCH_DUMP_FINISH;
}

int main(int argc, char** argv)
{
    /* Retrieve problem size. */
    int m = M;
    int n = N;

    /* Variable declaration/allocation. */
    POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, M, N, m, n);
    POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);
    POLYBENCH_1D_ARRAY_DECL(y, DATA_TYPE, N, n);

    /* Initialize array(s). */
    init_arrays(m, n, POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(x), POLYBENCH_ARRAY(y));

#if STMT==2
    POLYBENCH_2D_ARRAY_DECL(B, DATA_TYPE, M, N, m, n);
    POLYBENCH_1D_ARRAY_DECL(w, DATA_TYPE, N, n);
    POLYBENCH_1D_ARRAY_DECL(z, DATA_TYPE, N, n);
    init_arrays(m, n, POLYBENCH_ARRAY(B), POLYBENCH_ARRAY(w), POLYBENCH_ARRAY(z));
#endif

    /* Start timer. */
    int t = 0;
    polybench_start_instruments;
    for (t = 0; t < NRUNS; ++t)
    {
        KERNEL_NAME(m, n,
                uI, uIt, uIs,
                uJ, uJt, uJs,
                POLYBENCH_ARRAY(A),
                POLYBENCH_ARRAY(x),
                POLYBENCH_ARRAY(y)
#if STMT==2
                ,POLYBENCH_ARRAY(B),
                POLYBENCH_ARRAY(w),
                POLYBENCH_ARRAY(z)
#endif
                );
    }
    /* Stop and print timer. */
    polybench_stop_instruments;
    polybench_print_instruments;

    /* Prevent dead-code elimination. All live-out data must be printed
       by the function call in argument. */
    polybench_prevent_dce(print_array1d(n, POLYBENCH_ARRAY(y)));
    polybench_prevent_dce(print_array2d(n, POLYBENCH_ARRAY(A)));

    /* Be clean. */
    POLYBENCH_FREE_ARRAY(A);
    POLYBENCH_FREE_ARRAY(x);
    POLYBENCH_FREE_ARRAY(y);

#if STMT==2
    /* Prevent dead-code elimination. All live-out data must be printed
       by the function call in argument. */
    polybench_prevent_dce(print_array1d(n, POLYBENCH_ARRAY(w)));
    polybench_prevent_dce(print_array2d(n, POLYBENCH_ARRAY(B)));
    POLYBENCH_FREE_ARRAY(B);
    POLYBENCH_FREE_ARRAY(w);
    POLYBENCH_FREE_ARRAY(z);
#endif

    return 0;
}

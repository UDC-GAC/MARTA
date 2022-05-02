/**
 * This version is stamped on May 10, 2016
 *
 * Contact:
 *   Louis-Noel Pouchet <pouchet.ohio-state.edu>
 *   Tomofumi Yuki <tomofumi.yuki.fr>
 *
 * Web address: http://polybench.sourceforge.net
 */
/* gesummv.c: this file is part of PolyBench/C */

#define DATA_TYPE_IS_FLOAT

#include "marta_wrapper.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* SuiteSparse file to read Rutherford-Boeing format */
#include <RBio.h>

/* Include polybench common header. */
#include <polybench.h>

/* Include benchmark-specific header. */
#include "gesummv.h"

/* Array initialization. */
static void init_array_spmv(char *rbpath, SuiteSparse_long *nrow,
                            SuiteSparse_long **Ai, SuiteSparse_long **Ap,
                            DATA_TYPE **A, DATA_TYPE **x, DATA_TYPE **y) {
  int i, j;
  SuiteSparse_long ret;
  char title[73];
  char key[9];
  char mtype[4];
  SuiteSparse_long ncol;
  SuiteSparse_long mkind;
  SuiteSparse_long skind;
  SuiteSparse_long asize;
  SuiteSparse_long znz;
  DATA_TYPE *Az;
  SuiteSparse_long *Zp;
  SuiteSparse_long *Zi;

  ret = RBread(rbpath, 1, 0, title, key, mtype, nrow, &ncol, &mkind, &skind,
               &asize, &znz, Ap, Ai, A, &Az, &Zp, &Zi);
  //  printf( "Returned value: %d\n", ret );
  int nnz = (*Ap)[ncol];
  //  printf( "Matrix is %d X %d with %d NNZs\n", *nrow, ncol, nnz );
  SuiteSparse_long *CSRAi =
      (SuiteSparse_long *)malloc(sizeof(SuiteSparse_long) * nnz);
  SuiteSparse_long *CSRAp =
      (SuiteSparse_long *)malloc(sizeof(SuiteSparse_long) * (*nrow + 1));
  DATA_TYPE *CSRdata = (DATA_TYPE *)malloc(sizeof(DATA_TYPE) * nnz);
  // Initialize pointer array to zero
  for (int i = 0; i < *nrow; ++i) {
    CSRAp[i] = 0;
  }
  // Add one to each entry in pointer array for each value of CSC index array
  for (int i = 0; i < nnz; ++i) {
    CSRAp[(*Ai)[i]]++;
  }
  // Cumsum to obtain Ap
  for (int i = 0, cumsum = 0; i < *nrow; ++i) {
    int temp = CSRAp[i];
    CSRAp[i] = cumsum;
    cumsum += temp;
  }
  CSRAp[*nrow] = nnz;

  for (int col = 0; col < ncol; ++col) {
    for (int jj = (*Ap)[col]; jj < (*Ap)[col + 1]; jj++) {
      int row = (*Ai)[jj];
      int dest = CSRAp[row];

      CSRAi[dest] = col;
      CSRdata[dest] = (*A)[jj];

      CSRAp[row]++;
    }
  }

  for (int row = 0, last = 0; row <= *nrow; ++row) {
    int temp = CSRAp[row];
    CSRAp[row] = last;
    last = temp;
  }

  *x = (DATA_TYPE *)malloc(sizeof(DATA_TYPE) * ncol);
  *y = (DATA_TYPE *)malloc(sizeof(DATA_TYPE) * (*nrow));

  for (i = 0; i < ncol; i++) {
    (*x)[i] = (DATA_TYPE)(i % ncol) / ncol;
  }

  for (i = 0; i < *nrow; i++) {
    (*y)[i] = SCALAR_VAL(0.0);
  }

  free(*A);
  *A = CSRdata;
  free(*Ai);
  *Ai = CSRAi;
  free(*Ap);
  *Ap = CSRAp;
}

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static void kernel_gesummv(SuiteSparse_long n, SuiteSparse_long *indices,
                           SuiteSparse_long *indptr, DATA_TYPE *A, DATA_TYPE *x,
                           DATA_TYPE *y) {
  int i, j, t;

#pragma omp parallel for private(j)
  for (i = 0; i < n; ++i) {
    y[i] = SCALAR_VAL(0.0);
    for (j = indptr[i]; j < indptr[i + 1]; ++j) {
      y[i] = A[j] * x[indices[j]] + y[i];
#ifdef TEST_DEBUG
      printf("%d:%d:%d:%lf:%lf:%lf\n", i, j, indices[j], A[j], x[indices[j]],
             y[i]);
#endif
    }
  }

#ifdef TEST_RESULTS
  for (i = 0; i < n; ++i) {
    printf("y[%d] = %lf\n", i, y[i]);
  }
#endif
}

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);
/* Retrieve problem size. */
SuiteSparse_long nrow;
/* Variable declaration/allocation. */
DATA_TYPE *A;
DATA_TYPE *x;
DATA_TYPE *y;
SuiteSparse_long *indices;
SuiteSparse_long *indptr;
char *rbpath;

if (argc < 2) {
  printf("Usage: spmv_regular <RB file>\n");
  exit(0);
}

rbpath = argv[1];

/* Initialize array(s). */
init_array_spmv(rbpath, &nrow, &indices, &indptr, &A, &x, &y);

/* Run kernel. */
PROFILE_FUNCTION(kernel_gesummv(nrow, indices, indptr, A, x, y));

/* Prevent dead-code elimination. All live-out data must be printed
   by the function call in argument. */
polybench_prevent_dce(marta_print_1darray("y", nrow, y));

/* Be clean. */
POLYBENCH_FREE_ARRAY(A);
POLYBENCH_FREE_ARRAY(x);
POLYBENCH_FREE_ARRAY(y);
MARTA_BENCHMARK_END;

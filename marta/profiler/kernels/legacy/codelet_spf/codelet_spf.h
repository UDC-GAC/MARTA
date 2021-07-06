#ifndef restrict
#define restrict __restrict
#endif

#ifndef DATA_TYPE
#define DATA_TYPE float
#endif

void kernel_spmv(DATA_TYPE *restrict A, DATA_TYPE *restrict x,
                 DATA_TYPE *restrict y);
#ifndef restrict
#define restrict __restrict
#endif

#ifndef DATA_TYPE
#define DATA_TYPE float
#endif

#define EXPAND_STRING(s) #s
#define TO_STRING(s) EXPAND_STRING(s)

void kernel_spmv(DATA_TYPE *restrict A, DATA_TYPE *restrict x,
                 DATA_TYPE *restrict y);
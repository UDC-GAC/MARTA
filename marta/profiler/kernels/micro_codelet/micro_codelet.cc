#include "micro_codelet.h"

#define restrict __restrict

#ifndef MICRO_CODELET_FILE_NAME
#define MICRO_CODELET_FILE_NAME "patterns/codelet_00000001.c"
#endif

#ifndef ORIG_A
#define ORIG_A 0
#endif

#ifndef ORIG_x
#define ORIG_x 0
#endif

#ifndef ORIG_y
#define ORIG_y 0
#endif

void codelet(double *restrict A, double *restrict x, double *restrict y)
{
  register int i, j;

//#pragma macveth unroll i full j full
#include MICRO_CODELET_FILE_NAME
  //#pragma endmacveth
}

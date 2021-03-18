#ifndef KERNEL_H
#define KERNEL_H

#define DATA_TYPE float *__restrict
#define P_INLINE inline __attribute__((always_inline))

void kernel(DATA_TYPE a, DATA_TYPE b, DATA_TYPE c);

#endif

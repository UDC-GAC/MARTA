#ifndef KERN_H
#define KERN_H

#include <stdio.h>
#include <stdlib.h>

#ifndef X_VALUE
#define X_VALUE 42
#endif

void kernel(float *restrict A, float *restrict B, float *restrict C);

#endif /* !KERN_H */
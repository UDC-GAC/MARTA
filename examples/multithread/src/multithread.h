#ifndef KERN_H
#define KERN_H

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void kernel(float *restrict A, float *restrict B, float *restrict C);

#endif /* !KERN_H */
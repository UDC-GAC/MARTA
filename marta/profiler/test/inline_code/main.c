#include <stdio.h>
#include <stdlib.h>
#include "kernel.h"

int main() {
    
    float *a = (float*)malloc(sizeof(float)*1024);
    float *b = (float*)malloc(sizeof(float)*1024);
    float *c = (float*)malloc(sizeof(float)*1024);

    #pragma no_unroll_and_jam
    for (int i = 0; i < 10000; ++i) {
        kernel(a,b,c);
    }

    printf("a[3] = %f\n", a[3]);
}
for (i = 0; i <= UB_I; ++i) {
    for (j = 0; j <=UB_J; ++j) {
        y[8*i + 1*j + ORIG_y] += A[8*i + j + ORIG_A] * x[8*i + 1*j + ORIG_x];
     }
}

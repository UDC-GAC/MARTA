/*
 * File			: tests/perftest/randompacking/randompacking.cc
 * Author       : Marcos Horro
 * Date		    : Fri 13 Nov 2020 10:27 +01:00
 *
 * Last Modified : Fri 13 Nov 2020 10:38 +01:00
 * Modified By	 : Marcos Horro (marcos.horro@udc.gal>)
 *
 * MIT License
 *
 * Copyright (c) 2020 Colorado State University
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define DATA_TYPE_IS_FLOAT

#include "marta_wrapper.h"
#include "matrices.h"
#include <immintrin.h>

#ifdef N
#undef N
#define N 1024 * 32
#endif

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);

int n = N;

// Initialization section

POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(y, DATA_TYPE, N, n);

init_1darray(n, POLYBENCH_ARRAY(A));
init_1darray(n, POLYBENCH_ARRAY(x));
init_1darray(n, POLYBENCH_ARRAY(y));

// if (MARTA_INTEL_FLUSH_DATA == 1) {
//   intel_clflush(POLYBENCH_ARRAY(A), N * sizeof(DATA_TYPE));
//   intel_clflush(POLYBENCH_ARRAY(x), N * sizeof(DATA_TYPE));
//   intel_clflush(POLYBENCH_ARRAY(y), N * sizeof(DATA_TYPE));
// }

polybench_flush_cache();
_mm_mfence();
_mm_lfence();

PROFILE_FUNCTION_LOOP(kernel_spmv(POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(x),
                                  POLYBENCH_ARRAY(y)));

polybench_prevent_dce(marta_print_1darray("y", n, POLYBENCH_ARRAY(y)));
// polybench_prevent_dce(marta_print_1darray("A", n, POLYBENCH_ARRAY(A)));
// polybench_prevent_dce(marta_print_1darray("x", n, POLYBENCH_ARRAY(x)));

MARTA_AVOID_DCE(y);

MARTA_BENCHMARK_END;

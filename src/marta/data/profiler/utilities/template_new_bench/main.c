/*
 * File			: TEMPLATE
 * Author   : Marcos Horro
 * Date		  : Fri 13 Nov 2020 10:27 +01:00
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

#include "kern.h"
#include "marta_wrapper.h"

MARTA_BENCHMARK_BEGIN(0);

// FIXME: Declare arrays
// POLYBENCH_1D_ARRAY_DECL(y, DATA_TYPE, N, n);
// POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, n);
// POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);

// FIXME: Init arrays
// init_1darray(n, POLYBENCH_ARRAY(y));
// init_1darray(n, POLYBENCH_ARRAY(A));
// init_1darray(n, POLYBENCH_ARRAY(x));

// FIXME:
int nsteps = 10000;
int flops = 42;
PROFILE_FUNCTION(nsteps, kern(), "FUNC_STR", "A,x,y", flops, 0);

// FIXME: avoid DCE printing result array
// polybench_prevent_dce(print_1darray(4, POLYBENCH_ARRAY(y)));
MARTA_BENCHMARK_END;
/**
 * Last Modified : Wed 10 Jun 2020 09:38 +02:00
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

#ifndef _VECTOR_CODELET_H
#define _VECTOR_CODELET_H

#define restrict __restrict

#ifdef N
#undef N
#define N 180358
#endif

void codelet(double *restrict A, double *restrict x, double *restrict y);

#if defined(__CODE_INLINED)

#ifdef(__INTEL_COMPILER)
#define INLINE_K __inline
#else
#define INLINE_K inline
#endif

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

INLINE_K void codelet(double *restrict A, double *restrict x, double *restrict y)
{
    register int i, j;

//#pragma macveth unroll i full j full
#include MICRO_CODELET_FILE_NAME
    //#pragma endmacveth
}
#endif

#endif

/**
 * File					 :
 * /home/markoshorro/workspace/MACVETH/tmp/cs553-hw5-alexnet/layers.h Author
 * : Marcos Horro Date					 : Wed 03 Jun 2020 11:25
 * +02:00
 *
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

#ifndef _VECTOR_RANDOM_PACKING_H
#define _VECTOR_RANDOM_PACKING_H

#define restrict __restrict

#if !defined(TWO_PACK) && !defined(THREE_PACK) && !defined(FOUR_PACK)
#define TWO_PACK
#endif

#ifndef NPACK
#define NPACK 2
#endif

#if NPACK == 2
#ifndef FUNC_NAME
#define FUNC_NAME two_vpack
#endif
#ifndef FUNC_OPS
#define FUNC_OPS 2
#endif
#ifndef FUNC_STR
#define FUNC_STR "two_pack"
#endif
#endif

#if NPACK == 3
#ifndef FUNC_NAME
#define FUNC_NAME three_vpack
#endif
#ifndef FUNC_OPS
#define FUNC_OPS 3
#endif
#ifndef FUNC_STR
#define FUNC_STR "three_pack"
#endif
#endif

#if NPACK == 4
#ifndef FUNC_NAME
#define FUNC_NAME four_vpack
#endif
#ifndef FUNC_OPS
#define FUNC_OPS 4
#endif
#ifndef FUNC_STR
#define FUNC_STR "four_pack"
#endif
#endif

#ifndef N
#define N 1024
#endif

#ifndef X_0
#define X_0 0
#endif

#ifndef X_1
#define X_1 1
#endif

#ifndef X_2
#define X_2 2
#endif

#ifndef X_3
#define X_3 3
#endif

#ifndef X_4
#define X_4 4
#endif

#ifndef X_5
#define X_5 5
#endif

#ifndef X_6
#define X_6 6
#endif

#ifndef X_7
#define X_7 7
#endif

void vpack(double *restrict A, double *restrict x, double *restrict y);

#endif

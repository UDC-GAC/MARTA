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

#ifndef _VECTOR_COST_MODEL_H
#define _VECTOR_COST_MODEL_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <immintrin.h>

#define restrict __restrict

#ifdef DATA_TYPE
#undef DATA_TYPE
#define DATA_TYPE float
#endif

#ifndef DATA_TYPE
#define DATA_TYPE float
#endif

#ifdef N
#undef N
#define N 2048
#endif

#define RET_VAL __m128
//#define RET_VAL void

RET_VAL cost_model(DATA_TYPE *restrict A, DATA_TYPE *restrict x,
                   DATA_TYPE *restrict y);

#endif

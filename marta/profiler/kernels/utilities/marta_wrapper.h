/**
 * Copyright 2019-2021 (c) Colorado State University
 * Copyright 2020-2021 (c) Universidade da Coruña
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _MARTA_WRAPPER_H
#define _MARTA_WRAPPER_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "polybench.h"

#include "polybench_definitions.h"

#include <math.h>
#include <sched.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef restrict
#define restrict __restrict
#endif

#if defined(__INTEL_COMPILER)
#define INLINE_PREFIX __forceinline
#else
#define INLINE_PREFIX __attribute__((always_inline)) inline
#endif

#if !defined(MARTA_CPU_AFFINITY)
#define MARTA_CPU_AFFINITY 3
#endif

#ifndef NRUNS
#define NRUNS 10000
#endif

#ifndef MARTA_NO_HEADER
#define MARTA_NO_HEADER 0
#endif

#ifndef MARTA_CSV_HEADER
#define MARTA_CSV_HEADER 1
#endif

#ifndef MARTA_INIT_DATA
#define MARTA_INIT_DATA 0
#endif

#ifndef MARTA_INTEL_FLUSH_DATA
#define MARTA_INTEL_FLUSH_DATA 0
#endif

/**
 * Flush cache using clflush instruction.
 * @param p memory address
 * @param allocation_size size to flush
 */
void intel_clflush(volatile void *p, unsigned int allocation_size) {
  const size_t cache_line = 64;
  const char *cp = (const char *)p;
  size_t i = 0;

  if (p == NULL || allocation_size <= 0)
    return;

  for (i = 0; i < allocation_size; i += cache_line) {
    asm volatile("clflush (%0)\n\t" : : "r"(&cp[i]) : "memory");
  }

  /* according to Intel 64 and IA-32 Architectures optimization reference
   * manual 7.4.9, this instruction is no longer required; but just in case...
   */
  asm volatile("sfence\n\t" : : : "memory");
}

/**
 *  _Pragma(X) syntax works for this type of macros >=C99. This way we avoid
 *  type of loop optimizations, such as loopnest interchange, in order to
 *  properly inline a function within this loop.
 */
#define PROFILE_FUNCTION_SINGLE_VAL(STEPS, X)                                  \
  {                                                                            \
    polybench_start_instruments;                                               \
    _Pragma("nounroll_and_jam");                                               \
    for (int t = 0; t < STEPS; ++t) {                                          \
      X;                                                                       \
    }                                                                          \
    polybench_stop_instruments;                                                \
    polybench_print_instruments;                                               \
  }

#define BEGIN_LOOP(TSTEPS)                                                     \
  asm volatile("mov %0, %%eax" : : "r"(TSTEPS) : "eax");                       \
  asm volatile("begin_loop:");

// According to Intel's optimization guide it is better to avoid dec in benefit
// of sub/add/cmp when using loops
// Intel® 64 and IA-32 Architectures Optimization Reference Manual
// https://software.intel.com/content/dam/develop/external/us/en/documents-tps/64-ia-32-architectures-optimization-manual.pdf
#define END_LOOP                                                               \
  asm volatile("sub $1, %%eax\n\t"                                             \
               "jne begin_loop"                                                \
               :                                                               \
               :                                                               \
               :);

#if defined(DEC_END_LOOP)
#undef END_LOOP
#define END_LOOP                                                               \
  asm volatile("dec %%eax\n\t"                                                 \
               "jne begin_loop"                                                \
               :                                                               \
               :                                                               \
               :);
#endif

/**
 * CLOBBER_MEMORY - Acts as a read/write memory barrier.
 */
#define CLOBBER_MEMORY asm volatile("" : : : "memory")

#define EXPAND_STRING(s) #s
#define TO_STRING(s) EXPAND_STRING(s)

/**
 * DO_NOT_TOUCH[_WRITE|_READ](x) - Avoid compiler optimizations
 * Output   : none
 * Input    : x
 * Clobber  : "memory"
 *      The "memory" clobber tells the compiler that the assembly
 *      code performs memory reads or writes to items other than those
 *      listed in the input and output operands (for example, accessing
 *      the memory pointed to by one of the input parameters). To ensure
 *      memory contains correct values, GCC may need to flush specific
 *      register values to memory before executing the asm.
 * Constraints for output parameters:
 *  "r": register allowed as input
 *  "m": memory allowed as input
 */
#if defined(__INTEL_COMPILER)
#define DO_NOT_TOUCH(var)
#define DO_NOT_TOUCH_WRITE(var)
#define DO_NOT_TOUCH_READ(var)
#else
// output: var
// +: read/write
// "x" for XMM, "t" for YMM, "g" for ZMM
#define DO_NOT_TOUCH(var)                                                      \
  asm volatile("" : "+x"(var) : /* no inputs */ : /* no clobbering */);
#define DO_NOT_TOUCH_IO(var) asm volatile("" : "+"(var)::);
//#define DO_NOT_TOUCH(var) asm volatile("" : "+m,r"(var) : : "memory")
//#define DO_NOT_TOUCH(var) asm volatile("" : : "rm"(var) : "memory")
#define DO_NOT_TOUCH_WRITE(var) asm volatile("" : : "rm"(var) : "memory")
#define DO_NOT_TOUCH_READ(var) asm volatile("" : "+r,m"(var))
#endif

#define PROFILE_FUNCTION_NO_LOOP(X)                                            \
  {                                                                            \
    polybench_start_instruments;                                               \
    X;                                                                         \
    polybench_stop_instruments;                                                \
    polybench_print_instruments;                                               \
  }

#define PROFILE_FUNCTION_TSTEPS_LOOP(X)                                        \
  {                                                                            \
    polybench_start_instruments;                                               \
    _Pragma("nounroll_and_jam");                                               \
    for (int t = 0; t < TSTEPS; ++t) {                                         \
      X;                                                                       \
    }                                                                          \
    polybench_stop_instruments;                                                \
    polybench_print_instruments;                                               \
  }

#define PROFILE_FUNCTION_SINGLE_VAL_DCE(STEPS, X, Y)                           \
  {                                                                            \
    polybench_start_instruments;                                               \
    _Pragma("nounroll_and_jam");                                               \
    for (int t = 0; t < STEPS; ++t) {                                          \
      DO_NOT_TOUCH(X);                                                         \
      DO_NOT_TOUCH(Y);                                                         \
      Y = X;                                                                   \
      CLOBBER_MEMORY;                                                          \
    }                                                                          \
    polybench_stop_instruments;                                                \
    polybench_print_instruments;                                               \
  }

/**
 * Macro to encapsulate a function call in the main function to enable
 * its profiling with the PolyBench harness.
 */
#define PROFILE_FUNCTION(STEPS, X, name, features, flops, i)                   \
  {                                                                            \
    polybench_prepare_instruments;                                             \
    polybench_start_instruments;                                               \
    for (int t = 0; t < STEPS; ++t) {                                          \
      X;                                                                       \
    }                                                                          \
    polybench_stop_instruments;                                                \
    printf("%s,%s,%ld,", name, features, flops);                               \
    polybench_print_instruments_flops(flops);                                  \
  }

/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static void print_array1d(int n, DATA_TYPE POLYBENCH_1D(y, N, n)) {
  int i;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("y");
  for (i = 0; i < n; i++) {
    if (i % 20 == 0)
      fprintf(POLYBENCH_DUMP_TARGET, "\n");
    fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, y[i]);
  }
  POLYBENCH_DUMP_END("y");
  POLYBENCH_DUMP_FINISH;
}

/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static void print_array2d(int n, DATA_TYPE POLYBENCH_2D(A, N, N, n, n)) {
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("A");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (i % 20 == 0)
        fprintf(POLYBENCH_DUMP_TARGET, "\n");
      fprintf(POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, A[i][j]);
    }
  }
  POLYBENCH_DUMP_END("A");
  POLYBENCH_DUMP_FINISH;
}

/* Array initialization: 1-dimensional */
static void init_1darray(int n, DATA_TYPE POLYBENCH_1D(x, N, n)) {
  for (int i = 0; i < n; i++) {
    x[i] = 42;
  }
}

/* Array initialization: 2-dimensional */
static void init_2darray(int n, DATA_TYPE POLYBENCH_2D(A, N, N, n, n)) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      A[i][j] = 42;
    }
  }
}

/**
 * Avoid DCE optimizations by adding a set of numbers.
 */
DATA_TYPE marta_avoid_dce_sum(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  DATA_TYPE total = 0;
  while (*fmt != '\0') {
    if (*fmt == 'd') {
      total += va_arg(args, int);
    } else {
      total += va_arg(args, double);
    }
    ++fmt;
  }
  va_end(args);
  return total;
}

#define MARTA_AVOID_DCE(...)                                                   \
  if (argc >= 42) {                                                            \
    printf("tmp %f", marta_avoid_dce_sum(0, __VA_ARGS__));                     \
  }

#define MARTA_CHECK_HEADERS(cond)                                              \
  if ((cond != MARTA_NO_HEADER) && (cond != MARTA_CSV_HEADER)) {               \
    fprintf(stderr, "[MARTA] Bad flag for BENCHMARK_BEGIN");                   \
    exit(1);                                                                   \
  }

#ifndef NRUNS
#define NRUNS 1000
#endif

#define MARTA_BENCHMARK_BEGIN(cond)                                            \
  int main(int argc, char **argv) {                                            \
    int i = 0;                                                                 \
    int n = N;                                                                 \
    int m = M;                                                                 \
    MARTA_CHECK_HEADERS(cond);                                                 \
    cpu_set_t mask;                                                            \
    CPU_ZERO(&mask);                                                           \
    CPU_SET(MARTA_CPU_AFFINITY, &mask);                                        \
    int TSTEPS = NRUNS;                                                        \
    int result = sched_setaffinity(0, sizeof(mask), &mask);

#define MARTA_BENCHMARK_END                                                    \
  return 0;                                                                    \
  }

#endif /* ! MARTA_WRAPPER_H */

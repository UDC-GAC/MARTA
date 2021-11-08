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

#include <assert.h>
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

#ifndef TSTEPS
#define TSTEPS NRUNS
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

#define MARTA_TMP_FILE "/tmp/___marta_results.txt"

#define MARTA_OPEN_RESULTS_FILE                                                \
  FILE *fp;                                                                    \
  fp = fopen(MARTA_TMP_FILE, "a");                                             \
  if (fp == NULL)                                                              \
    exit(-1);

#define MARTA_CLOSE_RESULTS_FILE fclose(fp);

void marta_print_to_file(const char *format, ...) {
  MARTA_OPEN_RESULTS_FILE;
  va_list args;
  va_start(args, format);
  vfprintf(fp, format, args);
  va_end(args);
  MARTA_CLOSE_RESULTS_FILE;
}

#define MARTA_PREPARE_INSTRUMENTS polybench_prepare_instruments()
#define MARTA_START_INSTRUMENTS polybench_start_instruments
#define MARTA_STOP_INSTRUMENTS polybench_stop_instruments
#define MARTA_PRINT_INSTRUMENTS marta_print_to_file

#ifdef POLYBENCH_PAPI
extern const unsigned int polybench_papi_eventlist[];
extern const long long polybench_papi_values[];

void marta_print_papi_to_file() {
  MARTA_OPEN_RESULTS_FILE;
  int evid;
  for (evid = 0; polybench_papi_eventlist[evid] != 0; ++evid) {
    if (polybench_papi_eventlist[evid + 1] == 0) {
      fprintf(fp, "%llu", polybench_papi_values[evid]);
    } else {
      fprintf(fp, "%llu,", polybench_papi_values[evid]);
    }
  }
  fprintf(fp, "\n");
  MARTA_CLOSE_RESULTS_FILE;
}

#undef MARTA_PRINT_INSTRUMENTS
#define MARTA_PRINT_INSTRUMENTS marta_print_papi_to_file();
#endif

#if defined(MARTA_MULTITHREAD) && !defined(_OPENMP)
#error "Compile with -fopenmp!"
#elif defined(MARTA_MULTITHREAD) && defined(_OPENMP)
#undef MARTA_START_INSTRUMENTS
#undef MARTA_STOP_INSTRUMENTS
#undef MARTA_PRINT_INSTRUMENTS
#define PW_MULTITHREAD
#include "papi_wrapper.h"
#define MARTA_PREPARE_INSTRUMENTS pw_init_instruments
#define MARTA_START_INSTRUMENTS pw_init_start_instruments
#define MARTA_STOP_INSTRUMENTS pw_stop_instruments
#define MARTA_PRINT_INSTRUMENTS pw_print_instruments
#endif

#define EXPAND_STRING(s) #s
#define TO_STRING(s) EXPAND_STRING(s)

typedef unsigned long long int _marta_cycles_t;

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
    __asm volatile("clflush (%0)\n\t" : : "r"(&cp[i]) : "memory");
  }

  /* according to Intel 64 and IA-32 Architectures optimization reference
   * manual 7.4.9, this instruction is no longer required; but just in case...
   */
  __asm volatile("sfence\n\t" : : : "memory");
}

static inline _marta_cycles_t _marta_rdtsc_start() {
  _marta_cycles_t __cycles_lo, __cycles_hi;
  __asm volatile("sfence\n\t"
                 "lfence\n\t"
                 "rdtsc\n\t"
                 : "=a"(__cycles_lo), "=d"(__cycles_hi));
  return (_marta_cycles_t)__cycles_hi << 32 | __cycles_lo;
}

static inline _marta_cycles_t _marta_rdtsc_stop() {
  _marta_cycles_t __cycles_lo, __cycles_hi;
  __asm volatile("sfence\n\t"
                 "lfence\n\t"
                 "rdtsc\n\t"
                 "lfence\n\t"
                 : "=a"(__cycles_lo), "=d"(__cycles_hi));
  return (_marta_cycles_t)__cycles_hi << 32 | __cycles_lo;
}

#ifdef MARTA_MULTITHREAD
int *__marta_rdtsc;
static inline void _marta_init_rdtsc() {
  int __nthreads = 1;
#pragma omp parallel
  {
#pragma omp master
    { __nthreads = omp_get_num_threads(); }
  }
  __marta_rdtsc = (int *)malloc(sizeof(int) * __nthreads);
#pragma omp parallel
  {
    int th = omp_get_thread_num();
    __marta_rdtsc[th] = _marta_rdtsc_start();
  }
}

static inline void _marta_finish_rdtsc() {
#pragma omp parallel
  {
    int th = omp_get_thread_num();
    __marta_rdtsc[th] = _marta_rdtsc_stop() - __marta_rdtsc[th];
  }
}

#define START_RDTSC _marta_init_rdtsc();

#define END_RDTSC _marta_finish_rdtsc();
#define PRINT_RDTSC                                                            \
  for (int __th = 0; __th < __nthreads; ++__th) {                              \
    MARTA_PRINT_INSTRUMENTS("%d,%.1F\n", __th, (double)(__marta_rdtsc[__th]));   \
  }                                                                            \
  free(__marta_rdtsc);

#else
#define START_RDTSC _marta_cycles_t __marta_t0 = _marta_rdtsc_start();
#define END_RDTSC _marta_cycles_t __marta_t1 = _marta_rdtsc_stop() - __marta_t0;
#define PRINT_RDTSC MARTA_PRINT_INSTRUMENTS("%.1F\n", (double)(__marta_t1));
#endif

#define MARTA_LOOP_ASM 0x1
#define MARTA_LOOP_C 0x2

#ifdef MARTA_LOOP_TYPE_ASM
#define MARTA_LOOP_TYPE MARTA_LOOP_ASM
#else
#define MARTA_LOOP_TYPE MARTA_LOOP_C
#endif

#if MARTA_LOOP_TYPE == MARTA_LOOP_ASM
#define INIT_BEGIN_LOOP(TSTEPS)                                                \
  __asm volatile("mov $" TO_STRING(TSTEPS) ", %%ecx" : : : "ecx");             \
  __asm volatile("begin_loop:\n");                                             \
  __asm volatile("# LLVM-MCA-BEGIN kernel");

// According to Intel's optimization guide it is better to
// avoid dec in benefit of sub/add/cmp when using loops Intel®
// 64 and IA-32 Architectures Optimization Reference Manual
// https://software.intel.com/content/dam/develop/external/us/en/documents-tps/64-ia-32-architectures-optimization-manual.pdf
#define END_LOOP                                                               \
  __asm volatile("# LLVM-MCA-END kernel");                                     \
  __asm volatile("sub $1, %%ecx\n\t"                                           \
                 "jne begin_loop\n"                                            \
                 :                                                             \
                 :                                                             \
                 :);

#if defined(DEC_END_LOOP)
#undef END_LOOP
#define END_LOOP                                                               \
  __asm volatile("# LLVM-MCA-END kernel");                                     \
  __asm volatile("" :::);                                                      \
  __asm volatile("dec %%ecx\n\t"                                               \
                 "jne begin_loop"                                              \
                 :                                                             \
                 :                                                             \
                 :);
#endif
#elif MARTA_LOOP_TYPE == MARTA_LOOP_C
#define INIT_BEGIN_LOOP(TSTEPS)                                                \
  _Pragma("nounroll_and_jam");                                                 \
  for (int __marta_tsteps = 0; __marta_tsteps < TSTEPS; ++__marta_tsteps) {    \
    __asm volatile("# LLVM-MCA-BEGIN kernel");

// According to Intel's optimization guide it is better to
// avoid dec in benefit of sub/add/cmp when using loops Intel®
// 64 and IA-32 Architectures Optimization Reference Manual
// https://software.intel.com/content/dam/develop/external/us/en/documents-tps/64-ia-32-architectures-optimization-manual.pdf
#define END_LOOP                                                               \
  __asm volatile("# LLVM-MCA-END kernel");                                     \
  }

#endif

#define INIT_BEGIN_CYCLES_LOOP(TSTEPS)                                         \
  MARTA_PREPARE_INSTRUMENTS;                                                   \
  START_RDTSC;                                                                 \
  INIT_BEGIN_LOOP(TSTEPS);

/**
 * CLOBBER_MEMORY - Acts as a read/write memory barrier.
 */
#define CLOBBER_MEMORY __asm volatile("" : : : "memory")

/**
 * DO_NOT_TOUCH[_WRITE|_READ|...](x) - Avoid compiler
 * optimizations Output   : none Input    : x Clobber  :
 * "memory" The "memory" clobber tells the compiler that the
 * assembly code performs memory reads or writes to items other
 * than those listed in the input and output operands (for
 * example, accessing the memory pointed to by one of the input
 * parameters). To ensure memory contains correct values, GCC
 * may need to flush specific register values to memory before
 * executing the asm. Constraints for output parameters: "r":
 * register allowed as input "m": memory allowed as input
 */

/* This should only work for V4FSMODE (typically xmm registers,
   but it seems to
   materizalize properly ymm and zmm registers too). */
#define DO_NOT_TOUCH_V4FSMODE(var)                                             \
  __asm volatile(""                                                            \
                 : "+x"(var)                                                   \
                 : /* no inputs */                                             \
                 : /* no clobbering */);

#define DO_NOT_TOUCH_IO(var) __asm volatile("" : "+"(var)::);
#define DO_NOT_TOUCH_WRITE(var) __asm volatile("" : : "rm"(var) : "memory")
#define DO_NOT_TOUCH_READ(var) __asm volatile("" : "+r,m"(var))
#define DO_NOT_TOUCH(var) DO_NOT_TOUCH_V4FSMODE(var)

/**
 *  _Pragma(X) syntax works for this type of macros >=C99. This way we avoid
 *  type of loop optimizations, such as loopnest interchange, in order to
 *  properly inline a function within this loop.
 */
#define PROFILE_FUNCTION_SINGLE_VAL(STEPS, X)                                  \
  {                                                                            \
    MARTA_START_INSTRUMENTS;                                                   \
    _Pragma("nounroll_and_jam");                                               \
    for (int t = 0; t < STEPS; ++t) {                                          \
      X;                                                                       \
    }                                                                          \
    MARTA_STOP_INSTRUMENTS;                                                    \
    MARTA_PRINT_INSTRUMENTS;                                                   \
  }

#define PROFILE_FUNCTION_SINGLE_VAL_DCE(STEPS, X, Y)                           \
  {                                                                            \
    MARTA_START_INSTRUMENTS;                                                   \
    _Pragma("nounroll_and_jam");                                               \
    for (int t = 0; t < STEPS; ++t) {                                          \
      DO_NOT_TOUCH(X);                                                         \
      DO_NOT_TOUCH(Y);                                                         \
      Y = X;                                                                   \
      CLOBBER_MEMORY;                                                          \
    }                                                                          \
    MARTA_STOP_INSTRUMENTS;                                                    \
    MARTA_PRINT_INSTRUMENTS;                                                   \
  }

#define PROFILE_FUNCTION_NO_LOOP(X)                                            \
  {                                                                            \
    MARTA_START_INSTRUMENTS;                                                   \
    X;                                                                         \
    MARTA_STOP_INSTRUMENTS;                                                    \
    MARTA_PRINT_INSTRUMENTS;                                                   \
  }

#define PROFILE_FUNCTION_LOOP(X, TSTEPS)                                       \
  {                                                                            \
    MARTA_START_INSTRUMENTS;                                                   \
    INIT_BEGIN_LOOP(TSTEPS);                                                   \
    X;                                                                         \
    END_LOOP;                                                                  \
    MARTA_STOP_INSTRUMENTS;                                                    \
    MARTA_PRINT_INSTRUMENTS;                                                   \
  }

#define PROFILE_FUNCTION_CYCLES_LOOP(X, TSTEPS)                                \
  {                                                                            \
    INIT_BEGIN_CYCLES_LOOP(TSTEPS)                                             \
    X;                                                                         \
    END_LOOP;                                                                  \
    END_RDTSC;                                                                 \
    PRINT_RDTSC;                                                               \
  }

#define PROFILE_FUNCTION_CYCLES_NO_LOOP(X)                                     \
  {                                                                            \
    START_RDTSC;                                                               \
    X;                                                                         \
    END_RDTSC;                                                                 \
    PRINT_RDTSC;                                                               \
  }

#ifdef MARTA_RDTSC
#undef PROFILE_FUNCTION_NO_LOOP
#undef PROFILE_FUNCTION_LOOP
#undef PROFILE_FUNCTION
#define PROFILE_FUNCTION_LOOP(X, TSTEPS) PROFILE_FUNCTION_CYCLES_LOOP(X, TSTEPS)
#define PROFILE_FUNCTION_NO_LOOP(X) PROFILE_FUNCTION_CYCLES_NO_LOOP(X)
#endif

#if TSTEPS == 1
#undef PROFILE_FUNCTION_LOOP
#define PROFILE_FUNCTION_LOOP(X, TSTEPS) PROFILE_FUNCTION_NO_LOOP(X)
#define PROFILE_FUNCTION(X) PROFILE_FUNCTION_NO_LOOP(X)
#else
#define PROFILE_FUNCTION(X) PROFILE_FUNCTION_LOOP(X)
#endif

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

#define MARTA_BENCHMARK_BEGIN(cond)                                            \
  int main(int argc, char **argv) {                                            \
    MARTA_CHECK_HEADERS(cond);                                                 \
    cpu_set_t MARTA_CPU_MASK;                                                  \
    CPU_ZERO(&MARTA_CPU_MASK);                                                 \
    CPU_SET(MARTA_CPU_AFFINITY, &MARTA_CPU_MASK);                              \
    assert(sched_setaffinity(0, sizeof(MARTA_CPU_MASK), &MARTA_CPU_MASK) ==    \
           0);                                                                 \
    unsigned int __cycles_lo;                                                  \
    unsigned int __cycles_hi;

#define MARTA_BENCHMARK_END                                                    \
  return 0;                                                                    \
  }

#endif /* ! MARTA_WRAPPER_H */

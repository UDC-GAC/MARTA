/**
 * Copyright 2021 Marcos Horro
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

#include "marta_wrapper.h"
#include <stdint.h>

// static inline void foo() { asm volatile("nop" :::); }

MARTA_BENCHMARK_BEGIN(0);

// PROFILE_FUNCTION_LOOP(asm volatile("" :::), TSTEPS);
uint64_t start, end;
unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

// Warm up icache
__asm volatile("cpuid\n\t"
               "rdtsc\n\t"
               : "=r"(cycles_high), "=r"(cycles_low)::"rax", "rbx", "rcx",
                 "rdx");
__asm volatile("cpuid\n\t"
               "lfence;rdtsc\n\t"
               : "=r"(cycles_high), "=r"(cycles_low)::"rax", "rbx", "rcx",
                 "rdx");
__asm volatile("cpuid\n\t"
               "rdtsc;sfence;lfence\n\t"
               : "=r"(cycles_high), "=r"(cycles_low)::"rax", "rbx", "rcx",
                 "rdx");
__asm volatile("cpuid\n\t");
// MEASURE

__asm volatile("cpuid\n\t"
               "rdtsc\n\t"
               "lfence\n\t"
               "mov %%edx, %0\n\t"
               "mov %%eax, %1\n\t"
               : "=r"(cycles_high), "=r"(cycles_low)::"rax", "rbx", "rcx",
                 "rdx");
__asm volatile("sfence;rdtsc\n\t"
               "mov %%edx, %0\n\t"
               "mov %%eax, %1\n\t"
               "cpuid\n\t"
               : "=r"(cycles_high1), "=r"(cycles_low1)::"rax", "rbx", "rcx",
                 "rdx");
//_mm_lfence();
start = ((uint64_t)cycles_high << 32) | cycles_low;
end = ((uint64_t)cycles_high1 << 32) | cycles_low1;
printf("%llu\n", end - start);
MARTA_BENCHMARK_END;
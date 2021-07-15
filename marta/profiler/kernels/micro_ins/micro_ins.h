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

#ifndef _CODELET_HEADER_H
#define _CODELET_HEADER_H

#define EXPAND_STRING(s) #s
#define TO_STRING(s) EXPAND_STRING(s)
#define CONCAT(A, B) A##B

#ifndef MICRO_INS
#define MICRO_INS "kernel_0_0"
#endif

#define MICRO_INS_DECL MICRO_INS.decl.c
#define MICRO_INS_SRC MICRO_INS.c
#define MICRO_INS_DCE MICRO_INS.dce.c

#define FILE_DECL TO_STRING(MICRO_INS_DECL)
#define FILE_KERNEL TO_STRING(MICRO_INS_SRC)
#define FILE_DCE TO_STRING(MICRO_INS_DCE)

#ifndef restrict
#define restrict __restrict
#endif

void codelet(double *restrict A, double *restrict x, double *restrict y);

#endif /* _CODELET_HEADER_H */

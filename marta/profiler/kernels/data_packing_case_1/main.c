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

#include "marta_wrapper.h"
#include "data_packing_case_1.h"

MARTA_BENCHMARK_BEGIN(MARTA_NO_HEADER);

// Initialization section
POLYBENCH_1D_ARRAY_DECL(y, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, n);
POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);

//init_1darray(n, POLYBENCH_ARRAY(y));
//init_1darray(n, POLYBENCH_ARRAY(A));
//init_1darray(n, POLYBENCH_ARRAY(x));

FILE* fp;
int r[24];
fp = fopen("kernels/data_packing_case_1/file.txt", "r");
if (fp == NULL) {
    perror("Failed: ");
    return 1;
}

char buffer[256];
// -1 to allow room for NULL terminator for really long string
int tmp = 0;
while (fgets(buffer, 256 - 1, fp))
{
    // Remove trailing newline
    buffer[strcspn(buffer, "\n")] = 0;
    //printf("%s\n", buffer);
    r[tmp++] = atoi(buffer);

}

fclose(fp);

// // Codelet 1
// int I0 = 0;
// int J0 = 0;

// int I_sz0=2;
// int J_sz0=2;

// int I_Str0=1;
// int J_Str0=1;

// int Ya0=1;
// int Aa0=1;
// int Xa0=1;

// int Yb0=0;
// int Ab0=0;
// int Xb0=0;

// // Codelet 2
// int I1 = 42;
// int J1 = 42;

// int I_sz1=2;
// int J_sz1=2;

// int I_Str1=1;
// int J_Str1=1;

// int Ya1=1;
// int Aa1=1;
// int Xa1=1;

// int Yb1=0;
// int Ab1=0;
// int Xb1=0;

// Codelet 1
int I0 = r[0];
int J0 = r[1];

int I_sz0=r[2];
int J_sz0=r[3];

int I_Str0=r[4];
int J_Str0=r[5];

int Ya0=r[6];
int Aa0=r[7];
int Xa0=r[8];

int Yb0=r[9];
int Ab0=r[10];
int Xb0=r[11];

// Codelet 2
int I1 = r[12];
int J1 = r[13];

int I_sz1=r[14];
int J_sz1=r[15];

int I_Str1=r[16];
int J_Str1=r[17];

int Ya1=r[18];
int Aa1=r[19];
int Xa1=r[20];

int Yb1=r[21];
int Ab1=r[22];
int Xb1=r[23];

// Kernel section
PROFILE_FUNCTION_SINGLE_VAL(NRUNS, data_packing_case_1(POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(x), POLYBENCH_ARRAY(y),
                                           I0,J0,I_sz0,J_sz0,I_Str0,J_Str0,Ya0,Aa0,Xa0,Yb0,Ab0,Xb0,
                                           I1,J1,I_sz1,J_sz1,I_Str1,J_Str1,Ya1,Aa1,Xa1,Yb1,Ab1,Xb1));

// Avoid DCE section
polybench_prevent_dce(print_array1d(4, POLYBENCH_ARRAY(y)));

MARTA_BENCHMARK_END;

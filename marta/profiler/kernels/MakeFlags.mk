################################################################################
#																			   #
# 				Generic Makefile for runing kernels in MARTA				   #
#																			   #
################################################################################

# Some useful paths
BIN_DIR=../../bin/
ASM_DIR=../../asm_codes/
USRDIR=$(HOME)

# EXPERIMENTAL: inline code
INLINE_TOOL:=python3 ../../utils/inline_code.py

# Flags for PolyBench/C
PAPI_LIB?=$(USRDIR)/lib
PAPI_INCLUDE?=$(USRDIR)/include
PAPI_FLAGS=-I$(PAPI_INCLUDE) -L$(PAPI_LIB) -lpapi
POLYBENCH_FLAGS = -I ../utilities ../utilities/polybench.c
POLY_TFLAGS= -DPOLYBENCH_TIME $(POLYBENCH_FLAGS)
POLY_RFLAGS= -DPOLYBENCH_TIME -DPOLYBENCH_CYCLE_ACCURATE_TIMER $(POLYBENCH_FLAGS)
POLY_PFLAGS= -DPOLYBENCH_PAPI $(POLYBENCH_FLAGS) $(PAPI_FLAGS)

ASM_SYNTAX?=intel

# Adding all flags
FLAGS:= $(COMMON_FLAGS) $(KERNEL_CONFIG)
FLAGS_MAIN:= $(FLAGS)
FLAGS_KERN:= $(FLAGS)
FLAGS_ASM:= $(FLAGS)

ifeq ($(COMP),icc)
	CC=icc
	CXX=icpc
	ifeq ($(AUTOVEC),true)
		FLAGS_KERN+= -vec-threshold0
	endif
	FLAGS_KERN+= -O3 
	FLAGS_MAIN+= -O3 
	FLAGS_ASM+= -O3
else ifeq ($(COMP),gcc)
	CC=gcc
	CXX=g++
	FLAGS_MAIN+= -O3 -D_GNU_SOURCE -fno-dce -fno-tree-dce -fno-tree-builtin-call-dce
	ifeq ($(AUTOVEC),true)
		FLAGS_KERN+= -ftree-vectorize
		FLAGS_MAIN+= -ftree-vectorize
	endif
	FLAGS_KERN+= -O3 -flto -fsimd-cost-model=unlimited -fvect-cost-model=unlimited
	FLAGS_ASM+= -O3 -fsimd-cost-model=unlimited -fvect-cost-model=unlimited
else ifeq ($(COMP),clang)
	CC=clang
	CXX=clang++
	FLAGS_MAIN+= -O3 -D_GNU_SOURCE -fno-dce -fno-tree-dce -fno-tree-builtin-call-dce
	ifeq ($(AUTOVEC),true)
		FLAGS_KERN+= -ftree-vectorize
		FLAGS_MAIN+= -ftree-vectorize
	endif
	FLAGS_KERN+= -O3 -flto -fsimd-cost-model=unlimited -fvect-cost-model=unlimited
	FLAGS_ASM+= -O3 -fsimd-cost-model=unlimited -fvect-cost-model=unlimited
else
	echo "Compiler unknown"
	exit 1
endif

MAIN_FILE=$(MAIN_SRC)$(MAIN_SUFFIX)

# if @ specified, then not verbose
V = 

BASENAME:=$(TARGET)

MACVETH_RULE=
ifeq ($(MACVETH),true)
	MACVETH_RULE:=macveth
	OLD_TARGET:=$(TARGET)
	TARGET:=$(TARGET)_macveth
	MACVETH_DB:=$(COMMON_FLAGS)
endif

.PHONY: all clean

KERNEL_NAME?=$(BASENAME)_$(SUFFIX_ASM)_$(COMP)
TMP_SRC?=___tmp_$(KERNEL_NAME).c
TMP_BIN?=___tmp_$(KERNEL_NAME).o

BASE_BIN_NAME?=$(BIN_DIR)$(KERNEL_NAME)
BASE_ASM_NAME?=$(ASM_DIR)$(KERNEL_NAME)

#MAIN_RULES:= $(MACVETH_RULE) asm_code kernel $(MAIN_FILE)
MAIN_RULES:= $(MACVETH_RULE) $(MAIN_FILE)

ifeq ($(COMPILE_KERNEL),true)
	MAIN_RULES+= kernel
	FLAGS_MAIN+= $(KERNEL_NAME).o
endif

ifeq ($(ASM_CODE),true)
	MAIN_RULES+= asm_code
endif


# Experimental
ifeq ($(COMPILE_ASM),true)
	MAIN_RULES+= custom_asm
endif

# Compilation targets: depending on what we are measuring
TARGETS=
ifeq ($(TIME),true)
	TARGETS+= $(BINARY_NAME)_time
endif

ifeq ($(TSC),true)
	TARGETS+= $(BINARY_NAME)_tsc
endif

ifeq ($(PAPI),true)
	TARGETS+= $(BINARY_NAME)_papi
endif

# Targets to compile
all: $(TARGETS)

macveth: 
	$(V)$(MVPATH)macveth $(MACVETH_FLAGS) $(OLD_TARGET)$(INLINE).c -o kernels/$(OLD_TARGET)/$(TARGET).c -- $(MACVETH_DB)
	
asm_code: 
	$(V)$(CC) -c $(FLAGS_ASM) $(TARGET).c -masm=$(ASM_SYNTAX) -S -o $(BASE_ASM_NAME).s

kernel:
	$(V)cp $(TARGET).c $(TMP_SRC)
	$(V)$(CC) -c $(FLAGS_KERN) $(TMP_SRC)
	$(V)mv $(TMP_BIN) $(KERNEL_NAME).o
	$(V)rm $(TMP_SRC)

custom_asm:
	$(V)$(CC) -c $(FLAGS_KERN) $(ASM_NAME).s -o $(KERNEL_NAME).o

# -DPOLYBENCH_TIME
$(BINARY_NAME)_time: $(MAIN_RULES)
	$(V)$(CC) $(FLAGS_MAIN) $(POLY_TFLAGS) $(MAIN_FILE) -o $(BASE_BIN_NAME)_time.o

# -DPOLYBENCH_TIME -DPOLYBENCH_CYCLE_ACCURATE_TIMER
$(BINARY_NAME)_tsc: $(MAIN_RULES)
	$(V)$(CC) $(FLAGS_MAIN) $(POLY_RFLAGS) $(MAIN_FILE) -o $(BASE_BIN_NAME)_tsc.o

# -DPOLYBENCH_PAPI
$(BINARY_NAME)_papi: $(MAIN_RULES)
	$(V)$(CC) $(FLAGS_MAIN) $(POLY_PFLAGS) $(MAIN_FILE) -o $(BASE_BIN_NAME)_papi.o

clean:
	find . -type f ! -name "*.c" ! -name "*.h" ! -name "*.c" ! -name "Makefile" -delete
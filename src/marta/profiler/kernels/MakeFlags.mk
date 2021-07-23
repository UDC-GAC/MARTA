################################################################################
#                                                                              #
#               Generic Makefile for runing kernels in MARTA                   #
#                                                                              #
################################################################################

# Some useful paths
PARENT_DIR=../../../../../
BIN_DIR=$(PARENT_DIR)bin/
ASM_DIR=$(PARENT_DIR)asm_codes/
DUMP_DIR=$(PARENT_DIR)dumps/
USRDIR=$(HOME)

# EXPERIMENTAL: inline code
INLINE_TOOL:=python3 ../../utils/inline_code.py

# Flags for PolyBench/C
PAPI_LIB?=$(USRDIR)/lib
PAPI_INCLUDE?=$(USRDIR)/include
PAPI_FLAGS=-I$(PAPI_INCLUDE) -L$(PAPI_LIB) -lpapi
POLYBENCH_FLAGS = -I ../utilities ../utilities/polybench.c
POLY_TFLAGS= -DPOLYBENCH_TIME $(POLYBENCH_FLAGS)
POLY_CFLAGS= -DMARTA_RDTSC $(POLYBENCH_FLAGS)
#POLY_CFLAGS= -DPOLYBENCH_TIME -DPOLYBENCH_CYCLE_ACCURATE_TIMER $(POLYBENCH_FLAGS)
POLY_PFLAGS= -DPOLYBENCH_PAPI $(POLYBENCH_FLAGS) $(PAPI_FLAGS)

ASM_SYNTAX?=intel

#MACVETH_TARGET?=$(TARGET)

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
		FLAGS_MAIN+= -vec-threshold0
		FLAGS_ASM+= -vec-threshold0
	endif
	ifeq ($(KERNEL_INLINED),true)
		FLAGS_MAIN+= -ipo
	endif
else ifeq ($(COMP),gcc)
	CC=gcc
	CXX=g++
	FLAGS_MAIN+= -fno-dce -fno-tree-dce -fno-tree-builtin-call-dce
	ifeq ($(AUTOVEC),true)
		FLAGS_KERN+= -ftree-vectorize -ftree-vectorize -fsimd-cost-model=unlimited -fvect-cost-model=unlimited
	endif
	FLAGS_ASM+= $(FLAGS_KERN)
	FLAGS_MAIN+= $(FLAGS_KERN)
	ifeq ($(KERNEL_INLINED),true)
		FLAGS_MAIN+= -flto 
	endif
else ifeq ($(COMP),clang)
	CC=clang
	CXX=clang++
	FLAGS_MAIN+= -fno-dce -fno-tree-dce -fno-tree-builtin-call-dce
	ifeq ($(AUTOVEC),true)
		FLAGS_KERN+= -ftree-vectorize -fsimd-cost-model=unlimited -fvect-cost-model=unlimited
	endif
	FLAGS_ASM+= $(FLAGS_KERN)
	FLAGS_MAIN+= $(FLAGS_KERN)
	ifeq ($(KERNEL_INLINED),true)
		FLAGS_MAIN+= -flto 
	endif
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
	OLD_TARGET:=$(MACVETH_TARGET)
	TARGET:=$(TARGET)_macveth
	MACVETH_DB:=$(COMMON_FLAGS)
endif

.PHONY: all clean

KERNEL_NAME?=$(BASENAME)_$(SUFFIX_ASM)_$(COMP)_$(COMP_FLAGS)
TMP_SRC?=___tmp_$(KERNEL_NAME).c
TMP_ASM?=___tmp_$(KERNEL_NAME).s
TMP_BIN?=___tmp_$(KERNEL_NAME).o

BASE_BIN_NAME?=$(BIN_DIR)$(KERNEL_NAME)
BASE_ASM_NAME?=$(ASM_DIR)$(KERNEL_NAME)
BASE_DUMP_NAME?=$(DUMP_DIR)$(KERNEL_NAME)

#MAIN_RULES:= $(MACVETH_RULE) asm_code kernel $(MAIN_FILE)
MAIN_RULES:= $(MACVETH_RULE) $(MAIN_FILE)

ifeq ($(COMPILE_KERNEL),true)
	ifeq ($(MACVETH),true)
		MAIN_RULES+= kernel_macveth
	else
		MAIN_RULES+= kernel
	endif
	FLAGS_MAIN+= $(KERNEL_NAME).o
endif

ifeq ($(ASM_CODE_KERNEL),true)
	MAIN_RULES+= asm_code
endif

ifeq ($(ASM_CODE_MAIN),true)
	MAIN_RULES+= asm_code_main
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

ifeq ($(DUMP),true)
	TARGETS+= $(BINARY_NAME)_dump
endif

# Targets to compile
all: $(TARGETS)

# EXPERIMENTAL - Compatibility with MACVETH
macveth:
#	$(V)$(MVPATH)macveth $(MACVETH_FLAGS) $(OLD_TARGET)$(MACVETH_SUFFIX).c -o
#	kernels/$(OLD_TARGET)/$(TARGET).c -- $(MACVETH_DB)
	$(V)$(MVPATH)macveth $(MACVETH_FLAGS) $(OLD_TARGET)$(MACVETH_SUFFIX).c -o $(TMP_SRC) -- $(MACVETH_DB) 2> ___$(SUFFIX_ASM).log

asm_code:
	$(V)$(CC) -c $(FLAGS_ASM) $(TARGET).c -masm=$(ASM_SYNTAX) -S -o $(BASE_ASM_NAME).s

asm_code_main:
	cp $(MAIN_FILE) $(TMP_SRC)
	$(V)$(CC) $(FLAGS_MAIN) $(POLY_TFLAGS) $(TMP_SRC) -masm=$(ASM_SYNTAX) -S
	mv $(TMP_ASM) $(BASE_ASM_NAME).s
	rm $(TMP_SRC)

kernel_macveth: macveth
	$(V)$(CC) -c $(FLAGS_KERN) $(TMP_SRC)
	$(V)mv $(TMP_BIN) $(KERNEL_NAME).o

kernel:
	$(V)cp $(TARGET).c $(TMP_SRC)
	$(V)$(CC) -c $(FLAGS_KERN) $(TMP_SRC)
	$(V)mv $(TMP_BIN) $(KERNEL_NAME).o
	$(V)rm $(TMP_SRC)

custom_asm:
	$(V)$(CC) -c $(FLAGS_KERN) $(ASM_NAME).s -o $(KERNEL_NAME).o

# -DPOLYBENCH_TIME (clock time)
$(BINARY_NAME)_time: $(MAIN_RULES)
	$(V)$(CC) $(FLAGS_MAIN) $(POLY_TFLAGS) $(MAIN_FILE) -o $(BASE_BIN_NAME)_time.o

# RDTSC instruction for measuring
$(BINARY_NAME)_tsc: $(MAIN_RULES)
	$(V)$(CC) $(FLAGS_MAIN) $(POLY_CFLAGS) $(MAIN_FILE) -o $(BASE_BIN_NAME)_tsc.o

# -DPOLYBENCH_PAPI (hardware counters)
$(BINARY_NAME)_papi: $(MAIN_RULES)
	$(V)$(CC) $(FLAGS_MAIN) $(POLY_PFLAGS) $(MAIN_FILE) -o $(BASE_BIN_NAME)_papi.o

# -DPOLYBENCH_DUMP_ARRAYS
$(BINARY_NAME)_dump: $(MAIN_RULES)
	$(V)$(CC) $(FLAGS_MAIN) -DPOLYBENCH_DUMP_ARRAYS $(MAIN_FILE) -o $(BASE_DUMP_NAME)_dump.o

clean:
	find . -type f ! -name "*.c" ! -name "*.h" ! -name "*.c" ! -name "Makefile" -delete
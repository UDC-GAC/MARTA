################################################################################
#                                                                              #
#               Generic Makefile for runing kernels in MARTA                   #
#                                                                              #
################################################################################

ifndef TARGET
$(error TARGET is not set)
endif

ifndef BINARY_NAME
$(error BINARY_NAME is not set)
endif

# Some useful paths
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
CUR_DIR := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

PARENT_DIR?=$(CUR_DIR)marta_profiler_data/
BIN_DIR=$(PARENT_DIR)bin/
ASM_DIR=$(PARENT_DIR)asm_codes/
DUMP_DIR=$(PARENT_DIR)dumps/
PAPI_WRAPPER_DIR:=$(CUR_DIR)utilities/papi_wrapper/lib
USRDIR=$(HOME)
TMPDIR=/tmp/

# Flags for PolyBench/C
PAPI_LIB?=$(USRDIR)/lib
PAPI_INCLUDE?=$(USRDIR)/include
PAPI_FLAGS=-I$(PAPI_INCLUDE) -L$(PAPI_LIB) -lpapi
MARTA_FLAGS= -I utilities
POLYBENCH_FLAGS = $(MARTA_FLAGS) utilities/polybench.c
ifeq ($(MULTITHREAD),true)
	POLYBENCH_FLAGS+= -DMARTA_MULTITHREAD -DPW_MULTITHREAD -DPW_CSV -DPW_FILE -DPW_FILENAME=\"/tmp/___marta_results.txt\" -DPW_NO_CSV_HEADER
endif
POLY_TFLAGS= -DPOLYBENCH_TIME $(POLYBENCH_FLAGS)
POLY_CFLAGS= -DMARTA_RDTSC $(POLYBENCH_FLAGS)
POLY_PFLAGS= -DPOLYBENCH_PAPI $(POLYBENCH_FLAGS) $(PAPI_FLAGS)
POLY_DFLAGS= -DPOLYBENCH_DUMP_ARRAYS $(POLYBENCH_FLAGS)
ifeq ($(MULTITHREAD),true)
	POLY_PFLAGS+= -I $(PAPI_WRAPPER_DIR) $(PAPI_WRAPPER_DIR)/papi_wrapper.c
endif

TIMING_FLAGS?=$(POLY_TFLAGS)

ASM_SYNTAX?=intel

# Adding all flags
FLAGS:= $(COMMON_FLAGS) $(KERNEL_CONFIG)
FLAGS_MAIN:= $(FLAGS) 
FLAGS_KERN:= $(FLAGS)
FLAGS_ASM:= $(FLAGS)

ifeq ($(LOOP_TYPE),asm)
	FLAGS_MAIN+= -ffixed-ecx -DMARTA_LOOP_TYPE_ASM 
else
	FLAGS_MAIN+= -DMARTA_LOOP_TYPE_C 
endif

ifeq ($(COMP),icc)
	CC=icc
	CXX=icpc
#  report with the loops in your code that were vectorized
	OPT_FLAGS:= -qopt-report=1 -qopt-report-phase=vec,loop 
	ifeq ($(AUTOVEC),true)
		FLAGS_KERN+= -vec-threshold0 
	endif
	FLAGS_KERN+= $(OPT_FLAGS)
	FLAGS_ASM+= $(FLAGS_KERN) $(OPT_FLAGS)
	FLAGS_MAIN+= $(FLAGS_KERN) $(OPT_FLAGS)
	ifeq ($(KERNEL_INLINED),true)
		FLAGS_MAIN+= -ipo
	endif
else ifeq ($(findstring gcc,$(COMP)),gcc)
	CC=$(COMP)
	CXX=g++
	FLAGS_MAIN+= -fno-dce -fno-tree-dce -fno-tree-builtin-call-dce 
	ifeq ($(AUTOVEC),true)
		FLAGS_KERN+= -ftree-vectorize -fsimd-cost-model=unlimited -fvect-cost-model=unlimited 
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

MAIN_FILE?=main.c

# if @ specified, then not verbose
V = 

BASENAME:=$(TARGET)

.PHONY: all clean

KERNEL_NAME?=$(BASENAME)_$(SUFFIX_ASM)_$(COMP)_$(COMP_FLAGS)

ifeq ($(COMP),icc)
	FLAGS_KERN+= -qopt-report-file=/tmp/$(KERNEL_NAME).opt
	FLAGS_MAIN+= -qopt-report-file=/tmp/$(KERNEL_NAME).opt
	FLAGS_ASM+= -qopt-report-file=/tmp/$(KERNEL_NAME).opt
else ifeq ($(findstring gcc,$(COMP)),gcc)
	FLAGS_KERN+= -fopt-info-all=/tmp/$(KERNEL_NAME).opt
	FLAGS_MAIN+= -fopt-info-all=/tmp/$(KERNEL_NAME).opt
	FLAGS_ASM+= -fopt-info-all=/tmp/$(KERNEL_NAME).opt
else ifeq ($(COMP),clang)
# TODO
	FLAGS_KERN+= -Rpass=loop-vectorize 
	FLAGS_MAIN+= -Rpass=loop-vectorize 
	FLAGS_ASM+= -Rpass=loop-vectorize 
endif

TMP_SRC?=___tmp_$(KERNEL_NAME).c
TMP_ASM?=___tmp_$(KERNEL_NAME).s
TMP_BIN?=___tmp_$(KERNEL_NAME).o

BASE_BIN_NAME?=$(BIN_DIR)$(KERNEL_NAME)
BASE_ASM_NAME?=$(ASM_DIR)$(KERNEL_NAME)
BASE_DUMP_NAME?=$(DUMP_DIR)$(KERNEL_NAME)

KERNEL_BIN_NAME?=$(BIN_DIR)$(KERNEL_NAME)_kernel.o


# Experimental compatibility with MACVETH compiler
MACVETH_RULE=
ifeq ($(MACVETH),true)
	MACVETH_RULE:=macveth
	BINARY_NAME:=$(BINARY_NAME)_macveth
	OLD_TARGET:=$(MACVETH_TARGET)
	TARGET:=$(TARGET)_macveth
	MACVETH_DB:=$(COMMON_FLAGS)
	KERNEL_BIN_NAME?=$(BIN_DIR)$(KERNEL_NAME)_kernel_macveth.o
endif

MAIN_RULES:= $(MACVETH_RULE) $(MAIN_FILE)

ifeq ($(COMPILE_KERNEL),true)
	ifeq ($(MACVETH),true)
		MAIN_RULES+= kernel_macveth
	else
		MAIN_RULES+= kernel
	endif
	FLAGS_MAIN+= $(KERNEL_BIN_NAME)
endif

ifeq ($(ASM_CODE_KERNEL),true)
	MAIN_RULES+= asm_code
endif

ifeq ($(ASM_CODE_MAIN),true)
	MAIN_RULES+= asm_code_main
endif


# Experimental
ifeq ($(COMPILE_ASM),true)
	MAIN_RULES+= asm_code_custom
endif

# Compilation targets: depending on what we are measuring
TARGETS=
ifeq ($(TIME),true)
	TARGETS+= $(BINARY_NAME)_time
endif

ifeq ($(TSC),true)
	TARGETS+= $(BINARY_NAME)_tsc
	TIMING_FLAGS=$(POLY_CFLAGS)
endif

ifeq ($(PAPI),true)
	TARGETS+= $(BINARY_NAME)_papi
	TIMING_FLAGS=$(POLY_PFLAGS)
endif

ifeq ($(DUMP),true)
	TARGETS+= $(BINARY_NAME)_dump
endif

# Targets to compile
all: $(TARGETS)

# Compatibility with MACVETH
MACVETH_FLAGS?= -misa=avx2 --simd-cost-model=unlimited --march=cascadelake
macveth:
	$(V)$(MACVETH_PATH)macveth $(MACVETH_FLAGS) $(OLD_TARGET)$(MACVETH_SUFFIX).c -o $(TMP_SRC) -- $(MACVETH_DB) 

# Compatibility with MACVETH
kernel_macveth: macveth
	$(V)$(CC) -c $(FLAGS_KERN) $(TMP_SRC)
	$(V)mv $(TMP_BIN) $(KERNEL_BIN_NAME)
	$(V)mv $(TMP_SRC) $(BIN_DIR)

# Compile kernel to assembly code
asm_code:
	$(V)$(CC) -c $(FLAGS_ASM) $(TARGET).c -masm=$(ASM_SYNTAX) -S -o $(BASE_ASM_NAME).s

# Compile main file to assembly code
asm_code_main:
	$(V)cp $(MAIN_FILE) $(TMP_SRC)
	$(V)$(CC) $(FLAGS_MAIN) $(TIMING_FLAGS) $(TMP_SRC) -masm=$(ASM_SYNTAX) -S
	$(V)mv $(TMP_ASM) $(BASE_ASM_NAME).s
	$(V)rm -f $(TMP_SRC) polybench.s

# Compile assembly code
asm_code_custom:
	$(V)$(CC) -c $(FLAGS_KERN) $(TIMING_FLAGS) $(ASM_NAME).s -o $(KERNEL_NAME).o

# Compile C/C++ kernel
kernel:
	$(V)cp $(TARGET).c $(TMP_SRC)
	$(V)$(CC) -c $(FLAGS_KERN) $(TMP_SRC)
	$(V)mv $(TMP_BIN) $(KERNEL_BIN_NAME)
	$(V)rm $(TMP_SRC)

# -DPOLYBENCH_TIME (clock time)
$(BINARY_NAME)_time: $(MAIN_RULES)
	$(V)$(CC) $(FLAGS_MAIN) $(POLY_TFLAGS) $(MAIN_FILE) -o $(BASE_BIN_NAME)_time.o

# RDTSC instruction for measuring cycles
$(BINARY_NAME)_tsc: $(MAIN_RULES)
	$(V)$(CC) $(FLAGS_MAIN) $(POLY_CFLAGS) $(MAIN_FILE) -o $(BASE_BIN_NAME)_tsc.o

# -DPOLYBENCH_PAPI (hardware counters)
$(BINARY_NAME)_papi: $(MAIN_RULES)
	$(V)$(CC) $(FLAGS_MAIN) $(POLY_PFLAGS) $(MAIN_FILE) -o $(BASE_BIN_NAME)_papi.o

# -DPOLYBENCH_DUMP_ARRAYS: sanity check when comparing versions
$(BINARY_NAME)_dump: $(MAIN_RULES)
	$(V)$(CC) $(FLAGS_MAIN) $(POLY_DFLAGS) $(MAIN_FILE) -o $(BASE_DUMP_NAME)_dump.o

clean:
	find . -type f ! -name "*.c" ! -name "*.h" ! -name "*.c" ! -name "Makefile" -delete
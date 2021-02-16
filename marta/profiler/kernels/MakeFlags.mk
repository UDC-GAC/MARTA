################################################################################
#																			   #
# 				Generic Makefile for runing kernels in MARTA				   #
#																			   #
################################################################################

# Some paths
BIN_DIR=../../bin/
ASM_DIR=../../asm_codes/
USRDIR=$(HOME)

# Flags for PolyBench/C
#PAPI_LIB?=/share/apps/papi/gnu8/6.0.0/lib
PAPI_LIB?=$(USRDIR)/lib
PAPI_INCLUDE?=$(USRDIR)/include
PAPI_FLAGS=-I$(PAPI_INCLUDE) -L$(PAPI_LIB) -lpapi
POLYBENCH_FLAGS = -I ../utilities ../utilities/polybench.c
POLY_TFLAGS= -DPOLYBENCH_TIME -DPOLYBENCH_CYCLE_ACCURATE_TIME $(POLYBENCH_FLAGS)
POLY_PFLAGS= -DPOLYBENCH_PAPI $(POLYBENCH_FLAGS) $(PAPI_FLAGS)

FLAGS=
# Hate doing if/else in Makefile, tho
ifeq ($(COMP),icc)
	CC=icc
	CXX=icpc
else ifeq ($(COMP),gcc)
	CC=gcc
	CXX=g++
else ifeq ($(COMP),clang)
	CC=clang
	CXX=clang++
endif

# Adding all flags
FLAGS+= $(KERNEL_CONFIG) $(COMMON_FLAGS)

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

UNIQUE_NAME?=$(BASENAME)_$(SUFFIX_ASM)_$(COMP)

BASE_BIN_NAME?=$(BIN_DIR)$(UNIQUE_NAME)
BASE_ASM_NAME?=$(ASM_DIR)$(UNIQUE_NAME)

all: $(BINARY_NAME)

macveth: 
	$(V)$(MVPATH)macveth $(MACVETH_FLAGS) $(OLD_TARGET)$(INLINE).c -o kernels/$(OLD_TARGET)/$(TARGET).c -- $(MACVETH_DB)
	
asm_code: 
	$(V)$(CC) -c $(FLAGS) $(TARGET).c -S -o $(BASE_ASM_NAME).s

kernel_papi:
	$(V)cp $(TARGET).c ___tmp_$(UNIQUE_NAME).c
	$(V)$(CC) -c $(POLY_PFLAGS) $(FLAGS) ___tmp_$(UNIQUE_NAME).c 
	$(V)mv ___tmp_$(UNIQUE_NAME).o $(UNIQUE_NAME)_papi.o
	$(V)rm ___tmp_$(UNIQUE_NAME).c

kernel_time:
	$(V)cp $(TARGET).c ___tmp_$(UNIQUE_NAME).c
	$(V)$(CC) -c $(POLY_TFLAGS) $(FLAGS) ___tmp_$(UNIQUE_NAME).c
	$(V)mv ___tmp_$(UNIQUE_NAME).o $(UNIQUE_NAME)_time.o
	$(V)rm ___tmp_$(UNIQUE_NAME).c

$(BINARY_NAME): $(MACVETH_RULE) asm_code kernel_papi kernel_time $(MAIN_SRC)$(MAIN_SUFFIX) 
	$(V)$(CC) $(FLAGS) $(POLY_TFLAGS) $(MAIN_FILE) $(UNIQUE_NAME)_time.o -o $(BASE_BIN_NAME)_time.o
	$(V)$(CC) $(FLAGS) $(POLY_TFLAGS) $(MAIN_FILE) $(UNIQUE_NAME)_time.o -S
	$(V)$(CC) $(FLAGS) $(POLY_PFLAGS) $(MAIN_FILE) $(UNIQUE_NAME)_papi.o -o $(BASE_BIN_NAME)_papi.o
	$(V)$(CC) $(FLAGS) $(POLY_PFLAGS) $(MAIN_FILE) $(UNIQUE_NAME)_papi.o -S
	
clean:
	find . -type f ! -name "*.c" ! -name "*.h" ! -name "*.c" ! -name "Makefile" -delete
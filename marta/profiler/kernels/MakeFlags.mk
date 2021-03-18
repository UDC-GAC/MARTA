################################################################################
#																			   #
# 				Generic Makefile for runing kernels in MARTA				   #
#																			   #
################################################################################

# Some paths
BIN_DIR=../../bin/
ASM_DIR=../../asm_codes/
USRDIR=$(HOME)

# Inline code
INLINE_TOOL:=python3 ../../utils/inline_code.py

# Flags for PolyBench/C
PAPI_LIB?=$(USRDIR)/lib
PAPI_INCLUDE?=$(USRDIR)/include
PAPI_FLAGS=-I$(PAPI_INCLUDE) -L$(PAPI_LIB) -lpapi
POLYBENCH_FLAGS = -I ../utilities ../utilities/polybench.c
POLY_TFLAGS= -DPOLYBENCH_TIME -DPOLYBENCH_CYCLE_ACCURATE_TIME $(POLYBENCH_FLAGS)
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
	FLAGS_KERN+= -O3 -ipo 
	FLAGS_MAIN+= -O3 -ipo
	FLAGS_ASM+= -O3
else ifeq ($(COMP),gcc)
	ifeq ($(GCC),10)
		CC=/home/marcos.horro/bin/gcc
	else
		CC=gcc
	endif
	CXX=g++
	FLAGS_MAIN+= -O3 -flto -fno-aggressive-loop-optimizations -fno-tree-dominator-opts -finline-functions -fno-move-loop-invariants -fno-loop-interchange 
	ifeq ($(AUTOVEC),true)
		FLAGS_KERN+= -ftree-vectorize
	endif
	FLAGS_KERN+= -O3 -flto -fsimd-cost-model=unlimited -fvect-cost-model=unlimited
	FLAGS_ASM+= -O3 -fsimd-cost-model=unlimited -fvect-cost-model=unlimited
else ifeq ($(COMP),clang)
	CC=clang
	CXX=clang++
else
	echo "Compiler unknown, using GNU/GCC"
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

UNIQUE_NAME?=$(BASENAME)_$(SUFFIX_ASM)_$(COMP)
TMP_SRC?=___tmp_$(UNIQUE_NAME).c
TMP_BIN?=___tmp_$(UNIQUE_NAME).o

BASE_BIN_NAME?=$(BIN_DIR)$(UNIQUE_NAME)
BASE_ASM_NAME?=$(ASM_DIR)$(UNIQUE_NAME)

all: $(BINARY_NAME)

macveth: 
	$(V)$(MVPATH)macveth $(MACVETH_FLAGS) $(OLD_TARGET)$(INLINE).c -o kernels/$(OLD_TARGET)/$(TARGET).c -- $(MACVETH_DB)
	
asm_code: 
	$(V)$(CC) -c $(FLAGS_ASM) $(TARGET).c -masm=$(ASM_SYNTAX) -S -o $(BASE_ASM_NAME).s

kernel:
	$(V)cp $(TARGET).c $(TMP_SRC)
	$(V)$(CC) -c $(FLAGS_KERN) $(TMP_SRC)
	$(V)mv $(TMP_BIN) $(UNIQUE_NAME).o
	$(V)rm $(TMP_SRC)

hand_asm:
	$(V)$(CC) -c $(FLAGS_KERN) test.s

#$(BINARY_NAME): $(MACVETH_RULE) asm_code kernel $(MAIN_SRC)$(MAIN_SUFFIX) 
$(BINARY_NAME): $(MACVETH_RULE) asm_code hand_asm $(MAIN_SRC)$(MAIN_SUFFIX) 
# ifeq ($(AUTOVEC), true) 
# 	$(V)$(CC) $(FLAGS_MAIN) $(POLY_TFLAGS) $(MAIN_FILE) $(UNIQUE_NAME).o -S
# 	$(V)$(INLINE_TOOL) $(MAIN_SRC).s $(BASE_ASM_NAME).s $(TARGET) $(COMP)
# 	$(V)$(CC) $(FLAGS_MAIN) $(POLY_TFLAGS) $(UNIQUE_NAME).o $(MAIN_SRC).s -o $(BASE_BIN_NAME)_time.o
# 	$(V)$(CC) $(FLAGS_MAIN) $(POLY_PFLAGS) $(MAIN_FILE) $(UNIQUE_NAME).o -S
# 	$(V)$(INLINE_TOOL) $(MAIN_SRC).s $(BASE_ASM_NAME).s $(TARGET) $(COMP)
# 	$(V)$(CC) $(FLAGS_MAIN) $(POLY_PFLAGS) $(UNIQUE_NAME).o $(MAIN_SRC).s -o $(BASE_BIN_NAME)_papi.o
# else
	#$(V)$(CC) $(FLAGS_MAIN) $(POLY_TFLAGS) $(MAIN_FILE) $(UNIQUE_NAME).o -o
	#$(BASE_BIN_NAME)_time.o
	$(V)$(CC) $(FLAGS_MAIN) $(POLY_TFLAGS) $(MAIN_FILE) test.o -o $(BASE_BIN_NAME)_time.o
	#$(V)$(CC) $(FLAGS_MAIN) $(POLY_PFLAGS) $(MAIN_FILE) $(UNIQUE_NAME).o -o
	#$(BASE_BIN_NAME)_papi.o
	$(V)$(CC) $(FLAGS_MAIN) $(POLY_PFLAGS) $(MAIN_FILE) test.o -o $(BASE_BIN_NAME)_papi.o
# endif
#$(V)$(CC) $(FLAGS_MAIN) $(POLY_PFLAGS) $(MAIN_FILE) $(UNIQUE_NAME).o -S
#$(V)mv $(UNIQUE_NAME).o $(BIN_DIR)/$(UNIQUE_NAME)_kernel.o
#(V)rm $(UNIQUE_NAME)_papi.o $(UNIQUE_NAME)_time.o


clean:
	find . -type f ! -name "*.c" ! -name "*.h" ! -name "*.c" ! -name "Makefile" -delete
#################################
# Makefile for runing kernels in MARTA
#

# Paths
BIN_DIR=../../bin/
ASM_DIR=../../asm_codes/
USRDIR=$(HOME)

# Flags for PolyBench/C
POLYBENCH_FLAGS = -I ../utilities ../utilities/polybench.c
POLY_TFLAGS= -DPOLYBENCH_TIME -DPOLYBENCH_CYCLE_ACCURATE_TIME $(POLYBENCH_FLAGS)
POLY_PFLAGS= -DPOLYBENCH_PAPI $(POLYBENCH_FLAGS) -L/share/apps/papi/gnu8/6.0.0/lib -lpapi

ifeq ($(VECT),fast)
	VF= -Ofast
else
	VECT=nofast
	VF= -O3
endif

ifeq ($(COMP),icc)
	CC=icc
	CXX=icpc
	VFLAGS= $(VF) -vec-threshold0 -qoverride-limits -march=native -mfma
else
	COMP=gcc
	CC=gcc
	CXX=g++
	VFLAGS= $(VF) -march=native -mfma -ftree-vectorize -fvect-cost-model=unlimited -fsimd-cost-model=unlimited -fprefetch-loop-arrays
	VFLAGSMV= $(VF) -march=native -mfma -ftree-vectorize
endif

VFLAGS+= $(COMMON_FLAGS)

MAIN_FILE=$(MAIN_SRC)$(MAIN_SUFFIX)
# if @ specified, then not verbose
V = 

BASENAME:=$(TARGET)

MACVETH_RULE=
ifeq ($(MACVETH),true)
	MACVETH_RULE:=macveth
	OLD_TARGET:=$(TARGET)
	TARGET:=$(TARGET)_macveth
	MACVETH_DB:=$(CUSTOM_FLAGS)
endif

.PHONY: clean

all: $(BINARY_NAME)

macveth: 
	$(V)$(MVPATH)macveth $(MACVETH_FLAGS) $(OLD_TARGET).cc -o kernels/$(OLD_TARGET)/$(TARGET).cc -- $(MACVETH_DB)
	
asm_code: 
	$(V)$(CC) -c $(VFLAGS) $(TARGET).cc -S
	$(V)mv $(TARGET).s $(ASM_DIR)$(BASENAME)$(SUFFIX_ASM).s

kernel_cyc: 
	$(V)$(CC) -c $(POLY_PFLAGS) $(VFLAGS) $(TARGET).cc 
	$(V)mv $(TARGET).o $(TARGET)cyc.o

kernel_time:
	$(V)$(CC) -c $(POLY_TFLAGS) $(VFLAGS) $(TARGET).cc
	$(V)mv $(TARGET).o $(TARGET)time.o

$(BINARY_NAME): $(MACVETH_RULE) asm_code kernel_cyc kernel_time $(MAIN_SRC)$(MAIN_SUFFIX) 
	$(V)$(CC) $(VFLAGS) $(POLY_TFLAGS) $(MAIN_FILE) $(TARGET)time.o -o $(BIN_DIR)/$(BASENAME)_time.o
	$(V)$(CC) $(VFLAGS) $(POLY_PFLAGS) $(MAIN_FILE) $(TARGET)cyc.o -o $(BIN_DIR)/$(BASENAME)_cyc.o
	
	
clean:
	find . -type f ! -name "*.cc" ! -name "*.h" ! -name "*.c" ! -name "Makefile" -delete
#################################
# Makefile for runing kernels in MARTA
#

# Paths
BINDIR=bin/
ASMDIR=asm/
USRDIR=$(HOME)

# Flags for PolyBench/C
POLYBENCH_FLAGS = -I ../utilities ../utilities/polybench.c
POLY_TFLAGS= $(POLYBENCH_FLAGS) -DPOLYBENCH_TIME -DPOLYBENCH_CYCLE_ACCURATE_TIME
POLY_PFLAGS= $(POLYBENCH_FLAGS) -DPOLYBENCH_PAPI -L/share/apps/papi/gnu8/6.0.0/lib -lpapi

MACVETH_DB=$(COMMON_FLAGS)

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

MAIN_FILE=$(MAIN_SRC)$(MAIN_SUFFIX)
# if @ specified, then not verbose
V = 

.PHONY: clean

all: $(BINARY_NAME)

macveth: 
	$(V)$(MVPATH)macveth $(MACVETH_FLAGS) $(TARGET).cc -o kernels/$(BINARY_NAME)/$(TARGET)_macveth$(SUFFIX).cc -- $(MACVETH_DB)
	
asm_code: 
	$(V)$(CXX) -c $(VFLAGS) $(TARGET).cc -fverbose-asm -fopt-info-optimized=$@.vec -S

kernel_cyc: 
	$(V)$(CXX) -c $(POLY_PFLAGS) $(VFLAGS) $(TARGET).cc
	mv $(TARGET).o $(TARGET)cyc.o

kernel_time:
	$(V)$(CXX) -c $(POLY_TFLAGS) $(VFLAGS) $(TARGET).cc
	mv $(TARGET).o $(TARGET)time.o

$(BINARY_NAME): asm_code kernel_cyc kernel_time $(MAIN_SRC)$(MAIN_SUFFIX)
	$(V)$(CXX) $(VFLAGS) $(POLY_TFLAGS) $(MAIN_FILE) $(TARGET)time.o -o $(TARGET)_time.o
	$(V)$(CXX) $(VFLAGS) $(POLY_PFLAGS) $(MAIN_FILE) $(TARGET)cyc.o -o $(TARGET)_cyc.o
	
	
clean:
	find . -type f ! -name "*.cc" ! -name "*.h" ! -name "*.c" ! -name "Makefile" -delete
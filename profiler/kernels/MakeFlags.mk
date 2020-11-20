#
# Makefile for runing kernels in MARTA
#


# Paths
BINDIR=bin/
ASMDIR=asm/
USRDIR=$(HOME)

# Flags for PolyBench/C
POLYBENCH_FLAGS = -I. -L/share/apps/papi/gnu8/6.0.0/lib -lpapi -I ../utilities ..utilities/polybench.c
POLY_TFLAGS= -DPOLYBENCH_TIME -DPOLYBENCH_CYCLE_ACCURATE_TIME $(POLYBENCH_FLAGS)
POLY_PFLAGS= -DPOLYBENCH_PAPI $(POLYBENCH_FLAGS)

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

NAME=$(COMP)_$(VECT)_$(BINARY_NAME)_$(TYPE)
MAIN_FILE=$(MAIN_SRC)$(MAIN_SUFFIX)
# if @ specified, then not verbose
V = 

.PHONY: clean

all: $(BINARY_NAME)

macveth: 
	$(V)$(MVPATH)macveth $(MACVETH_FLAGS) $(TARGET).cc -o kernels/$(BINARY_NAME)/$(TARGET)_macveth$(SUFFIX).cc -- $(MACVETH_DB)
	
asm_code: 
	$(V)$(CXX) -c $(VFLAGS) $(TARGET).cc $(POLYBENCH_FLAGS) -fverbose-asm -fopt-info-optimized=$@.vec -S

kernel:
	$(V)$(CXX) -c $(VFLAGS) $(TARGET).cc $(POLYBENCH_FLAGS) -o $(NAME).o

$(BINARY_NAME): asm_code kernel $(MAIN_SRC)$(MAIN_SUFFIX)
	
	
clean:
	find . -type f ! -name "*.cc" ! -name "*.h" ! -name "*.c" ! -name "Makefile" -delete
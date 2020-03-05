# File              : Makefile
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Lun 21 Oct 2019 12:15:02 PM MST
# Last Modified Date: Thu 14 Nov 2019 03:06:23 PM MST
# Last Modified By  : Marcos Horro <marcos.horro@udc.gal>

BINDIR=./bin
USRDIR=$(HOME)

CC=gcc
CFLAGS=-fopenmp
TFLAGS=-DPOLYBENCH_TIME -DPOLYBENCH_CYCLE_ACCURATE_TIME
PFLAGS=-DPOLYBENCH_PAPI -L$(USRDIR)/papi/src -I$(USRDIR)/papi/src -lpapi
INC_KERN=kernels
POLYINC=-I utilities -I $(INC_KERN)
POLYINCC=-I utilities -I $(INC_KERN) utilities/polybench.c
KERNEL=kernel

################################################################################
################################################################################
# - POLYBENCH_USE_C99_PROTO: Use standard C99 prototype for the functions.
#   OK, this summarizes perfectly my knowledge regarding compilers (none).
#   When enabling this flag, the preprocessor does not replace the variable
#   name in the function declaration by its known value at compilation time.
#   Thus, if --param min-vect-loop-bound=n permits, loops are always vectorized
#   (obviously enabling proper flags, e.g. -O3/-Ofast, -ftree-vectorize,
#   -fsimd-cost-model, -fvect-cost-model, -march, -mtune,...)
#   The reason for this behavior is far away from my scope...
################################################################################
################################################################################


# just in case...
ifeq ($(CC),icc)
	CFLAGS += -D__PURE_INTEL_C99_HEADERS__
endif

KFLAGS = $(CUSTOM_FLAGS) -DuI=$(uI) -DuIt=$(uIt) -DuIs=$(uIs) -DuJ=$(uJ) -DuJt=$(uJt) -DuJs=$(uJs)
SFLAGS = $(CUSTOM_FLAGS) -DNRUNS=$(NRUNS)
# if @ specified, then not verbose
SILENT = @

all: ubench
.PHONY: all
.SILENT: ubench
ubench: $(KERNEL)

%: kernels/%.c
	$(SILENT)$(CC) $(POLYINC) $(KFLAGS) $^ -c -fverbose-asm -fopt-info-optimized=$@.vec -S
	$(SILENT)cp $@.s asm_codes/$@_I$(uI)_J$(uJ)_It$(uIt)_Jt$(uJt)_Is$(uIs)_Js$(uJs).s
	$(SILENT)$(CC) $(POLYINC) $(KFLAGS) $^ -c -fopt-info-optimized=$@.vec
	$(SILENT)mv $@.o $(BINDIR)
	$(SILENT)$(CC) $(CFLAGS) $(POLYINCC) kernels/skeleton.c $(BINDIR)/$@.o $(SFLAGS) $(TFLAGS) -o $(BINDIR)/$@_time.o
	$(SILENT)$(CC) $(CFLAGS) $(POLYINCC) kernels/skeleton.c $(BINDIR)/$@.o $(SFLAGS) $(PFLAGS) -o $(BINDIR)/$@_cyc.o

clean:
	rm -f bin/* *.s *.vec *.o

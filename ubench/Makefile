# File              : Makefile
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Lun 21 Oct 2019 12:15:02 PM MST
# Last Modified Date: Thu 14 Nov 2019 03:06:23 PM MST
# Last Modified By  : Marcos Horro <marcos.horro@udc.gal>

BINDIR=./bin
USRDIR=/s/chopin/b/grad/markos11

CC=gcc
CFLAGS=-fopenmp $(BINDIR)/$(KERNEL).o
TFLAGS=-DPOLYBENCH_TIME -DPOLYBENCH_CYCLE_ACCURATE_TIME
PFLAGS=-DPOLYBENCH_PAPI -L$(USRDIR)/usr/lib -lpapi
POLYINC=-I utilities -I $(UBENCH) utilities/polybench.c
KERNEL=kernel
UBENCH=spmvstyle

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
ubench: spmv.o

spmv.o: $(UBENCH)/$(UBENCH).c $(UBENCH)/$(UBENCH).h $(UBENCH)/$(KERNEL).c
	$(SILENT)$(CC) $(POLYINC) $(KFLAGS) $(UBENCH)/$(KERNEL).c -c -fverbose-asm -fopt-info-optimized=$(KERNEL).vec -S
	$(SILENT)cp kernel.s asm_codes/kernel_I$(uI)_J$(uJ)_It$(uIt)_Jt$(uJt)_Is$(uIs)_Js$(uJs).s
	$(SILENT)$(CC) $(POLYINC) $(KFLAGS) $(UBENCH)/$(KERNEL).c -c -fopt-info-optimized=$(KERNEL).vec
	$(SILENT)mv $(KERNEL).o $(BINDIR)
	$(SILENT)$(CC) $(CFLAGS) $(POLYINC) $(UBENCH)/$(UBENCH).c $(SFLAGS) $(TFLAGS) -o $(BINDIR)/spmv_time
	$(SILENT)$(CC) $(CFLAGS) $(POLYINC) $(UBENCH)/$(UBENCH).c $(SFLAGS) $(PFLAGS) -o $(BINDIR)/spmv_cyc

clean:
	rm -f bin/*

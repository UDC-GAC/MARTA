CC=icc
CFLAGS=
TFLAGS=-DPOLYBENCH_TIME -DPOLYBENCH_CYCLE_ACCURATE_TIME
PFLAGS=-DPOLYBENCH_PAPI -lpapi
POLYINC=-I utilities -I spmvstyle utilities/polybench.c
BINDIR=./bin

# just in case...
ifeq ($(CC),icc)
	CFLAGS += -D__PURE_INTEL_C99_HEADERS__
endif

SFLAGS = $(CUSTOM_FLAGS) -DNRUNS=$(NRUNS) -DuI=$(uI) -DuIt=$(uIt) -DuIs=$(uIs) -DuJ=$(uJ) -DuJt=$(uJt) -DuJs=$(uJs)

all: ubench
.PHONY: all

#kernel: spmvstyle/kernel.c spmvstyle/kernel.h
#	$(CC) -c $(CFLAGS) $(POLYINC) spmvstyle/kernel.c 
#	mv kernel.o bin/

ubench: spmv.o

spmv.o: spmvstyle/spmvstyle.c spmvstyle/spmvstyle.h spmvstyle/kernel.c
	$(CC) $(CFLAGS) $(POLYINC) spmvstyle/spmvstyle.c $(SFLAGS) $(TFLAGS) -o $(BINDIR)/spmv_time
	$(CC) $(CFLAGS) $(POLYINC) spmvstyle/spmvstyle.c $(SFLAGS) $(PFLAGS) -o $(BINDIR)/spmv_cyc

clean:
	rm -f bin/*

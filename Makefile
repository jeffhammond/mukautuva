ifeq ($(shell uname),Darwin)
    OMPICC=/opt/homebrew/Cellar/open-mpi/4.1.4_2/bin/mpicc
    MPICHCC=/opt/homebrew/Cellar/mpich/4.1/bin/mpicc
    CC=clang
    CFLAGS=-ferror-limit=5 # Clang
    CFLAGS+=-Wno-c2x-extensions
else
    OMPICC=/usr/bin/mpicc.openmpi
    MPICHCC=/usr/bin/mpicc.mpich
    CC=gcc
    CFLAGS=-fmax-errors=5 # GCC
endif

CFLAGS	+= -g3 -O3 -Wall -Wextra #-Werror # -Wpedantic
CFLAGS	+= -fPIC
SOFLAGS	= -shared

AR	= ar
ARFLAGS	= -r

all: libs tests

tests:  header.o testconstants.x testinit.x \
	testcomm.x testwin.x testreqs.x testcoll.x testgroup.x testtypes.x testops.x

other: testmalloc.x

testmalloc.x: testmalloc.c
	$(OMPICC) $(CFLAGS) $< -o $@

libs: libmuk.a libmuk.so

%.x: %.c libmuk.so mpi.h
	$(CC) $(CFLAGS) $< -L. -lmuk -o $@

MPI_H = mpi.h mpi-constants.h mpi-handle-typedefs.h mpi-typedefs.h mpi-predefined.h mpi-prototypes.h muk-predefined.h

# this just tests if mpi.h can be compiled without errors
header.o: header.c $(MPI_H)
	$(CC) $(CFLAGS) -c $< -o $@

libmuk.a: libinit.o
	$(AR) $(ARFLAGS) $@ $^

libmuk.so: libinit.o mpich-wrap.so ompi-wrap.so
	$(CC) $(SOFLAGS) $^ -o $@

libinit.o: libinit.c muk.h muk-dl.h $(MPI_H)
	$(CC) $(CFLAGS) -c $< -o $@

libinit.i: libinit.c muk.h muk-dl.h $(MPI_H)
	$(CC) $(CFLAGS) -E $< -o $@

mpich-wrap.so: mpich-predefined.o mpich-functions.o mpich-debug.o
	$(MPICHCC) $(SOFLAGS) $^ -o $@

ompi-wrap.so: ompi-predefined.o ompi-functions.o ompi-debug.o
	$(OMPICC) $(SOFLAGS) $^ -o $@

mpich-predefined.o: impl-predefined.c muk-predefined.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-predefined.o: impl-predefined.c muk-predefined.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-functions.o: impl-functions.c
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-functions.o: impl-functions.c
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-debug.o: debug.c
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-debug.o: debug.c
	$(OMPICC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o *.x *.s *.a *.i *.so
	-rm -rf *.dSYM
	-rm -rf *.btr # backtrace


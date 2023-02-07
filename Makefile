#OMPICC=/opt/homebrew/Cellar/open-mpi/4.1.4_2/bin/mpicc
#MPICHCC=/opt/homebrew/Cellar/mpich/4.0.3/bin/mpicc
OMPICC=/usr/bin/mpicc.openmpi
MPICHCC=/usr/bin/mpicc.mpich

CC	= gcc
CFLAGS	= -g3 -O0 -Wall -Wextra -Werror
#CFLAGS	+= -ferror-limit=3 # Clang
CFLAGS	+= -fmax-errors=3 # GCC
CFLAGS	+= -fPIC
SOFLAGS	= -shared

AR	= ar
ARFLAGS	= -r

all: libs tests

tests: header.o testinit.x testcomm.x testwin.x testreqs.x testcoll.x

other: testmalloc.x

testmalloc.x: testmalloc.c
	$(OMPICC) $(CFLAGS) $< -o $@

libs: libmuk.a libmuk.so

%.x: %.c libmuk.so mpi.h
	$(CC) $(CFLAGS) $< -L. -lmuk -o $@

MPI_H = mpi.h mpi-predefined.h mpi-prototypes.h mpi-typedefs.h

# this just tests if mpi.h can be compiled without errors
header.o: header.c $(MPI_H)
	$(CC) $(CFLAGS) -c $< -o $@

libmuk.a: libinit.o
	$(AR) $(ARFLAGS) $@ $^

libmuk.so: libinit.o mpich-wrap.so ompi-wrap.so
	$(CC) $(SOFLAGS) $^ -o $@

libinit.o: libinit.c muk.h muk-dl.h #muk-mpi-typedefs.h muk-mpi-functions.h
	$(CC) $(CFLAGS) -c $< -o $@

libinit.i: libinit.c muk.h muk-dl.h #muk-mpi-typedefs.h muk-mpi-functions.h
	$(CC) $(CFLAGS) -E $< -o $@

mpich-wrap.so: mpich-predefined.o mpich-functions.o mpich-debug.o
	$(MPICHCC) $(SOFLAGS) $^ -o $@

ompi-wrap.so: ompi-predefined.o ompi-functions.o ompi-debug.o
	$(OMPICC) $(SOFLAGS) $^ -o $@

mpich-predefined.o: impl-predefined.c
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-predefined.o: impl-predefined.c
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


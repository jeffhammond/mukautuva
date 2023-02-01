#OMPICC=/opt/homebrew/Cellar/open-mpi/4.1.4_2/bin/mpicc
#MPICHCC=/opt/homebrew/Cellar/mpich/4.0.3/bin/mpicc
OMPICC=/usr/bin/mpicc.openmpi
MPICHCC=/usr/bin/mpicc.mpich

CC	= gcc
CFLAGS	= -g3 -O0 -Wall -Wextra #-Werror
#CFLAGS	+= -ferror-limit=3 # Clang
CFLAGS	+= -fmax-errors=3 # GCC
CFLAGS	+= -fPIC
SOFLAGS	= -shared

AR	= ar
ARFLAGS	= -r

all: libs tests

tests: header.o testinit.x testcomm.x

libs: libmuk.a libmuk.so #libmukompi.so libmukmpich.so

%.x: %.c libmuk.so mpi.h
	$(CC) $(CFLAGS) $< -L. -lmuk -o $@

# this just tests if mpi.h can be compiled without errors
header.o: header.c mpi.h
	$(CC) $(CFLAGS) -c $< -o $@

libmuk.a: libinit.o #wrapmuk.o
	$(AR) $(ARFLAGS) $@ $^

libmuk.so: libinit.o mpich-predefined.so ompi-predefined.so
	$(CC) $(SOFLAGS) $^ -o $@

libmukompi.so: loadompi.o wrapompi.o
	$(OMPICC) $(SOFLAGS) $^ -o $@

libmukmpich.so: loadmpich.o wrapmpich.o
	$(MPICHCC) $(SOFLAGS) $^ -o $@

libinit.o: libinit.c muk.h muk-dl.h #muk-mpi-typedefs.h muk-mpi-functions.h
	$(CC) $(CFLAGS) -c $< -o $@

libinit.i: libinit.c muk.h muk-dl.h #muk-mpi-typedefs.h muk-mpi-functions.h
	$(CC) $(CFLAGS) -E $< -o $@

wrapmuk.o: wrapmuk.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(CC) $(CFLAGS) -c $< -o $@

wrapmuk.i: wrapmuk.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(CC) $(CFLAGS) -E $< -o $@

loadmpich.o: loadmpich.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

loadmpich.i: loadmpich.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(MPICHCC) $(CFLAGS) -E $< -o $@

loadompi.o: loadompi.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

loadompi.i: loadompi.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(OMPICC) $(CFLAGS) -E $< -o $@

wrapmpich.o: wrapmpich.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

wrapmpich.i: wrapmpich.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(MPICHCC) $(CFLAGS) -E $< -o $@

wrapompi.o: wrapompi.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

wrapompi.i: wrapompi.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(OMPICC) $(CFLAGS) -E $< -o $@

mpich-predefined.so: mpich-predefined.o
	$(MPICHCC) $(SOFLAGS) $^ -o $@

ompi-predefined.so: ompi-predefined.o
	$(OMPICC) $(SOFLAGS) $^ -o $@

mpich-predefined.o: impl-predefined.c
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-predefined.o: impl-predefined.c
	$(OMPICC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o *.x *.s *.a *.i *.so
	-rm -rf *.dSYM


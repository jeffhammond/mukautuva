OMPICC=/opt/homebrew/Cellar/open-mpi/4.1.4_2/bin/mpicc
MPICHCC=/opt/homebrew/Cellar/mpich/4.0.3/bin/mpicc

CC	= clang
CFLAGS	= -g3 -O0 -Wall -Wextra #-Werror
CFLAGS	+= -ferror-limit=3
CFLAGS	+= -fPIC
SOFLAGS	= -shared

AR	= ar
ARFLAGS	= -r

all: libs tests

tests: header.o testinit.x testcomm.x

libs: libmuk.a libmuk.so libmukompi.so libmukmpich.so

%.x: %.c libmuk.so mpi.h
	$(CC) $(CFLAGS) $< -L. -lmuk -o $@

# this just tests if mpi.h can be compiled without errors
header.o: header.c mpi.h
	$(CC) $(CFLAGS) -c $< -o $@

libmuk.a: libinit.o wrapmuk.o
	$(AR) $(ARFLAGS) $@ $^

libmuk.so: libinit.o wrapmuk.o
	$(CC) $(SOFLAGS) $^ -o $@

libmukompi.so: loadompi.o wrapompi.o
	$(OMPICC) $(SOFLAGS) $^ -o $@

libmukmpich.so: loadmpich.o wrapmpich.o
	$(MPICHCC) $(SOFLAGS) $^ -o $@

libinit.o: libinit.c muk.h muk-dl.h muk-mpi-typedefs.h muk-mpi-functions.h
	$(CC) $(CFLAGS) -c $< -o $@

wrapmuk.o: wrapmuk.c muk.h muk-mpi-typedefs.h muk-mpi-functions.h
	$(CC) $(CFLAGS) -c $< -o $@

loadmpich.o: loadmpich.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

loadompi.o: loadompi.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

wrapmpich.o: wrapmpich.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

wrapompi.o: wrapompi.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o *.x *.s *.a *.so
	-rm -rf *.dSYM


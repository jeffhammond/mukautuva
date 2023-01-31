OMPICC=/opt/homebrew/Cellar/open-mpi/4.1.4_2/bin/mpicc
MPICHCC=/opt/homebrew/Cellar/mpich/4.0.3/bin/mpicc

CC	= clang
CFLAGS	= -O0 -Wall -Wextra #-Werror
CFLAGS	+= -ferror-limit=3
CFLAGS	+= -fPIC
SOFLAGS	= -shared

AR	= ar
ARFLAGS	= -r

all: header.o libmuk.a libmuk.so libmukompi.so #libmukmpich.so

# this just tests if mpi.h can be compiled without errors
header.o: header.c mpi.h
	$(CC) $(CFLAGS) -c $< -o $@

libmuk.a: libinit.o
	$(AR) $(ARFLAGS) $@ $^

libmuk.so: libinit.o
	$(CC) $(SOFLAGS) $^ -o $@

libmukompi.so: loadompi.o wrapompi.o
	$(OMPICC) $(SOFLAGS) $^ -o $@

libmukmpich.so: loadmpich.o wrapmpich.o
	$(MPICHCC) $(SOFLAGS) $^ -o $@

libinit.o: libinit.c mpi.h muk.h muk-dl.h
	$(CC) $(CFLAGS) -c $< -o $@

loadmpich.o: loadmpich. muk-mpi-typedefs.h muk-mpi-functions.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

loadompi.o: loadompi.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

wrapmpich.o: wrapmpich. muk-mpi-typedefs.h muk-mpi-functions.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

wrapompi.o: wrapompi.c muk-mpi-typedefs.h muk-mpi-functions.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o *.x *.s *.a *.so
	-rm -rf *.dSYM


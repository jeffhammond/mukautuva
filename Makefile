ifeq ($(shell uname),Darwin)
    OMPICC=/opt/homebrew/Cellar/open-mpi/4.1.4_2/bin/mpicc
    MPICHCC=/opt/homebrew/Cellar/mpich/4.1/bin/mpicc
    CC=clang
    CFLAGS=-ferror-limit=1 # Clang
    CFLAGS+=-Wno-c2x-extensions
    #CFLAGS+=-Wno-unused-function
else
    OMPICC=/usr/bin/mpicc.openmpi
    MPICHCC=/usr/bin/mpicc.mpich
    CC=gcc
    CFLAGS=-fmax-errors=1 # GCC
    #CFLAGS+=-fsanitize=address
    #CFLAGS+=-Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
endif

CFLAGS	+= -g3 -O0 -Wall -Wextra #-Werror # -Wpedantic
CFLAGS	+= -fPIC
SOFLAGS	= -shared

AR	= ar
ARFLAGS	= -r

all: libs tests

RUNTESTS = testcoll.x testcoll2.x testcomm.x testinit.x testreqs.x \
	   testwin.x testgroup.x testtypes.x testtypes2.x testops.x \
	   testbottom.x testcart.x

tests: header.o testconstants.x $(RUNTESTS)

other: testmalloc.x

testmalloc.x: testmalloc.c
	$(OMPICC) $(CFLAGS) $< -o $@

libs: libmuk.a libmuk.so

%.x: %.c libmuk.so mpi.h
	$(CC) $(CFLAGS) $< -L. -lmuk -o $@

MPI_H = mpi.h mpi-constants.h mpi-handle-typedefs.h mpi-typedefs.h mpi-predefined.h mpi-prototypes.h muk-predefined.h

IMPL_H =    impl-alltoallw.h impl-constant-conversions.h \
	    impl-fpointers.h impl-handle-conversions.h \
	    impl-linked-list.h impl-predefined-op.h \
	    impl-scalar-types.h impl-status.h

IMPL_FUNCTION_C :=  impl-functions.c impl-load-functions.c impl-keyval.c \
		    impl-constant-conversions.c impl-predefined.c \
		    impl-commgroup-functions.c impl-rma-functions.c \
		    impl-wait-functions.c impl-session-functions.c \
		    impl-file-functions.c impl-reduce-functions.c \
		    impl-type-functions.c

IMPL_FUNCTION_O := $(patsubst %.c,%.o,$(IMPL_FUNCTION_C))
MPICH_FUNCTION_O := $(subst impl,mpich,$(IMPL_FUNCTION_O))
OMPI_FUNCTION_O := $(subst impl,ompi,$(IMPL_FUNCTION_O))

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

mpich-wrap.so: $(MPICH_FUNCTION_O)
	$(MPICHCC) $(SOFLAGS) $^ -o $@

ompi-wrap.so: $(OMPI_FUNCTION_O)
	$(OMPICC) $(SOFLAGS) $^ -o $@

mpich-predefined.o: impl-predefined.c muk-predefined.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-predefined.o: impl-predefined.c muk-predefined.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-functions.o: impl-functions.c $(IMPL_H)
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-functions.o: impl-functions.c $(IMPL_H)
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-commgroup-functions.o: impl-commgroup-functions.c $(IMPL_H)
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-commgroup-functions.o: impl-commgroup-functions.c $(IMPL_H)
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-reduce-functions.o: impl-reduce-functions.c $(IMPL_H)
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-reduce-functions.o: impl-reduce-functions.c $(IMPL_H)
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-rma-functions.o: impl-rma-functions.c $(IMPL_H)
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-rma-functions.o: impl-rma-functions.c $(IMPL_H)
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-type-functions.o: impl-type-functions.c $(IMPL_H)
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-type-functions.o: impl-type-functions.c $(IMPL_H)
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-wait-functions.o: impl-wait-functions.c $(IMPL_H)
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-wait-functions.o: impl-wait-functions.c $(IMPL_H)
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-file-functions.o: impl-file-functions.c $(IMPL_H)
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-file-functions.o: impl-file-functions.c $(IMPL_H)
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-session-functions.o: impl-session-functions.c $(IMPL_H)
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-session-functions.o: impl-session-functions.c $(IMPL_H)
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-load-functions.o: impl-load-functions.c $(IMPL_H)
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-load-functions.o: impl-load-functions.c $(IMPL_H)
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-constant-conversions.o: impl-constant-conversions.c $(IMPL_H)
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-constant-conversions.o: impl-constant-conversions.c $(IMPL_H)
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-keyval.o: impl-keyval.c $(IMPL_H)
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-keyval.o: impl-keyval.c $(IMPL_H)
	$(OMPICC) $(CFLAGS) -c $< -o $@

check: $(RUNTESTS)
	./test.sh ./testcoll.x
	./test.sh ./testcoll2.x
	./test.sh ./testcomm.x
	./test.sh ./testcart.x
	./test.sh ./testgroup.x
	./test.sh ./testinit.x
	./test.sh ./testops.x
	./test.sh ./testreqs.x
	./test.sh ./testtypes.x
	./test.sh ./testtypes2.x
	./test.sh ./testwin.x
	./test.sh ./testbottom.x

clean:
	-rm -f *.o *.x *.s *.a *.i *.so
	-rm -rf *.dSYM
	-rm -rf *.btr # backtrace


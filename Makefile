ifeq ($(shell uname),Darwin)
    OMPICC=/opt/homebrew/Cellar/open-mpi/4.1.4_2/bin/mpicc
    MPICHCC=/opt/homebrew/Cellar/mpich/4.1/bin/mpicc
    CC=clang
    CFLAGS=-ferror-limit=5 # Clang
    CFLAGS+=-Wno-c2x-extensions -Wno-unused-function
else
    OMPICC=/usr/bin/mpicc.openmpi
    MPICHCC=/usr/bin/mpicc.mpich
    CC=gcc
    #CFLAGS=-fmax-errors=5 # GCC
    #CFLAGS+=-fsanitize=address
    CFLAGS+=-Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
endif

CFLAGS	+= -g3 -O0 -Wall -Wextra # -Werror # -Wpedantic
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

mpich-wrap.so: mpich-predefined.o mpich-functions.o mpich-rma-functions.o mpich-type-functions.o mpich-wait-functions.o mpich-file-functions.o mpich-load-functions.o mpich-keyval.o
	$(MPICHCC) $(SOFLAGS) $^ -o $@

ompi-wrap.so: ompi-predefined.o ompi-functions.o ompi-rma-functions.o ompi-type-functions.o ompi-wait-functions.o ompi-file-functions.o ompi-load-functions.o ompi-keyval.o
	$(OMPICC) $(SOFLAGS) $^ -o $@

mpich-predefined.o: impl-predefined.c muk-predefined.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-predefined.o: impl-predefined.c muk-predefined.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-functions.o: impl-functions.c impl-fpointers.h impl-status.h impl-handle-conversions.h \
		   impl-predefined-op.h impl-constant-conversions.h impl-alltoallw.h impl-linked-list.h \
		   wrap-handle-typedefs.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-functions.o: impl-functions.c impl-fpointers.h impl-status.h impl-handle-conversions.h \
		  impl-predefined-op.h impl-constant-conversions.h impl-alltoallw.h impl-linked-list.h \
		  wrap-handle-typedefs.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-rma-functions.o: impl-rma-functions.c impl-fpointers.h impl-status.h impl-handle-conversions.h \
		   impl-predefined-op.h impl-constant-conversions.h wrap-handle-typedefs.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-rma-functions.o: impl-rma-functions.c impl-fpointers.h impl-status.h impl-handle-conversions.h \
		  impl-predefined-op.h impl-constant-conversions.h wrap-handle-typedefs.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-type-functions.o: impl-type-functions.c impl-fpointers.h impl-status.h impl-handle-conversions.h \
		   impl-predefined-op.h impl-constant-conversions.h wrap-handle-typedefs.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-type-functions.o: impl-type-functions.c impl-fpointers.h impl-status.h impl-handle-conversions.h \
		  impl-predefined-op.h impl-constant-conversions.h wrap-handle-typedefs.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-wait-functions.o: impl-wait-functions.c impl-fpointers.h impl-status.h impl-handle-conversions.h \
		   impl-predefined-op.h impl-constant-conversions.h wrap-handle-typedefs.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-wait-functions.o: impl-wait-functions.c impl-fpointers.h impl-status.h impl-handle-conversions.h \
		  impl-predefined-op.h impl-constant-conversions.h wrap-handle-typedefs.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-file-functions.o: impl-file-functions.c impl-fpointers.h impl-status.h impl-handle-conversions.h \
		   impl-predefined-op.h impl-constant-conversions.h wrap-handle-typedefs.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-file-functions.o: impl-file-functions.c impl-fpointers.h impl-status.h impl-handle-conversions.h \
		  impl-predefined-op.h impl-constant-conversions.h wrap-handle-typedefs.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-load-functions.o: impl-load-functions.c impl-fpointers.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-load-functions.o: impl-load-functions.c impl-fpointers.h
	$(OMPICC) $(CFLAGS) -c $< -o $@

mpich-keyval.o: impl-keyval.c impl-fpointers.h
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-keyval.o: impl-keyval.c impl-fpointers.h
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


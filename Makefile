UNAME_S := $(shell uname)

ifeq ($(UNAME_S),Darwin)
    brew_prefix := $(shell brew --prefix)
    OMPICC=$(wildcard $(brew_prefix)/Cellar/open-mpi/*/bin/mpicc)
    OMPICXX=$(wildcard $(brew_prefix)/Cellar/open-mpi/*/bin/mpicxx)
    MPICHCC=$(wildcard $(brew_prefix)/Cellar/mpich/*/bin/mpicc)
    MPICHCXX=$(wildcard $(brew_prefix)/Cellar/mpich/*/bin/mpicxx)
    CC=clang
    CFLAGS=-ferror-limit=1 # Clang
    #CFLAGS+=-Wno-c2x-extensions
    #CFLAGS+=-Wno-unused-function
    #CFLAGS+=-Wno-incompatible-function-pointer-types
else
    OSID := $(shell grep '^ID=' /etc/os-release | cut -d= -f2)
    ifeq ($(OSID),ubuntu)
        OMPICC=/usr/bin/mpicc.openmpi
        OMPICXX=/usr/bin/mpicxx.openmpi
        MPICHCC=/usr/bin/mpicc.mpich
        MPICHCXX=/usr/bin/mpicxx.mpich
        CC=gcc
    endif
    ifeq ($(OSID),fedora)
        OMPICC=/usr/lib64/openmpi/bin/mpicc
        OMPICXX=/usr/lib64/openmpi/bin/mpicxx
        MPICHCC=/usr/lib64/mpich/bin/mpicc
        MPICHCXX=/usr/lib64/mpich/bin/mpicxx
        CFLAGS=-fmax-errors=1 # GCC
        #CFLAGS+= -fsanitize=address
        # these suppress true errors with callbacks
        #CFLAGS+=-Wno-incompatible-pointer-types
        #CFLAGS+=-Wno-cast-function-type
        #CFLAGS+=-Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
    endif
endif
-include Makefile.local

CFLAGS += -g -O2 -Wall -Wextra #-Werror # -Wpedantic
CFLAGS += -fPIC
CXXFLAGS = -x c++ -std=c++17

SO = $(if $(findstring Darwin,$(UNAME_S)),dylib,so)
RPATH = $(if $(findstring Darwin,$(UNAME_S)),'@rpath','$$ORIGIN')
SOFLAGS = -shared
SOLIBS =

AR      = ar
ARFLAGS = -r


all: libs tests

RUNTESTS = testcoll.x testcoll2.x testcomm.x testinit.x testreqs.x \
           testwin.x testgroup.x testtypes.x testtypes2.x testops.x \
           testbottom.x testcart.x testerrh.x

tests: header.o testconstants.x $(RUNTESTS)

other: testmalloc.x

testmalloc.x: testmalloc.c
	$(OMPICC) $(CFLAGS) $< -o $@

libs: libmuk.a libmuk.$(SO) mpich-wrap.$(SO) ompi-wrap.$(SO)

%.x: %.c libmuk.$(SO) mpi.h
	$(CC) $(CFLAGS) $< -L. -Wl,-rpath,$(RPATH) -lmuk -o $@

MPI_H = mpi.h mpi-constants.h mpi-handle-typedefs.h mpi-typedefs.h mpi-predefined.h mpi-prototypes.h mpi-fortran.h muk-predefined.h

IMPL_H =    impl-alltoallw.h impl-constant-conversions.h \
	    impl-fpointers.h impl-handle-conversions.h \
	    impl-predefined-handle.h impl-scalar-types.h \
	    impl-status.h impl-keyval-map.h

IMPL_CXX_H =	impl-keyval-map-commattr.h \
		impl-keyval-map-typeattr.h \
		impl-keyval-map-winattr.h  \
		impl-keyval-map-commerrh.h \
		impl-keyval-map-fileerrh.h \
		impl-keyval-map-fileerrh2.h \
		impl-keyval-map-winerrh.h  \
		impl-keyval-map-opuserfn.h \
		impl-keyval-map-preqa2aw.h

IMPL_FUNCTION_C :=  impl-functions.c impl-load-functions.c impl-keyval.c \
		    impl-constant-conversions.c impl-predefined.c \
		    impl-commgroup-functions.c impl-rma-functions.c \
		    impl-wait-functions.c impl-session-functions.c \
		    impl-file-functions.c impl-reduce-functions.c \
		    impl-type-functions.c impl-grequest-functions.c

IMPL_FUNCTION_O := $(patsubst %.c,%.o,$(IMPL_FUNCTION_C))
MPICH_FUNCTION_O := $(subst impl,mpich,$(IMPL_FUNCTION_O)) mpich-keyval-map.o
OMPI_FUNCTION_O := $(subst impl,ompi,$(IMPL_FUNCTION_O)) ompi-keyval-map.o

# this just tests if mpi.h can be compiled without errors
header.o: header.c $(MPI_H)
	$(CC) $(CFLAGS) -c $< -o $@

libmuk.a: libinit.o
	$(AR) $(ARFLAGS) $@ $<


ifeq ($(UNAME_S),Darwin)
libmuk.$(SO): WRAPLIBS+=-Wl,-rpath,$(RPATH)
libmuk.$(SO): WRAPLIBS+=-Wl,mpich-wrap.dylib
libmuk.$(SO): WRAPLIBS+=-Wl,ompi-wrap.dylib
endif
libmuk.$(SO): SOLIBS+=-ldl
libmuk.$(SO): libinit.o | mpich-wrap.$(SO) ompi-wrap.$(SO)
	$(CC) $< $(SOFLAGS) $(SOLIBS) $(WRAPLIBS) -o $@

libinit.o: libinit.c muk.h muk-dl.h $(MPI_H)
	$(CC) $(CFLAGS) -c $< -o $@

libinit.i: libinit.c muk.h muk-dl.h $(MPI_H)
	$(CC) $(CFLAGS) -E $< -o $@

mpich-wrap.$(SO): $(MPICH_FUNCTION_O)
	$(MPICHCXX) $(SOFLAGS) $(SOLIBS) $^ -o $@

ompi-wrap.$(SO): $(OMPI_FUNCTION_O)
	$(OMPICXX) $(SOFLAGS) $(SOLIBS) $^ -o $@

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

mpich-grequest-functions.o: impl-grequest-functions.c $(IMPL_H)
	$(MPICHCC) $(CFLAGS) -c $< -o $@

ompi-grequest-functions.o: impl-grequest-functions.c $(IMPL_H)
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

mpich-keyval-map.o: impl-keyval-map.cc $(IMPL_H) $(IMPL_CXX_H)
	$(MPICHCC) $(CXXFLAGS) $(CFLAGS) -c $< -o $@

ompi-keyval-map.o: impl-keyval-map.cc $(IMPL_H) $(IMPL_CXX_H)
	$(OMPICC) $(CXXFLAGS) $(CFLAGS) -c $< -o $@

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
	./test.sh ./testerrh.x

clean:
	-rm -f *.o *.x *.s *.a *.i *.$(SO)
	-rm -rf *.dSYM
	-rm -rf *.btr # backtrace

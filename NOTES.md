# My Tests

```
for t in testcoll.x testcomm.x testinit.x testreqs.x testwin.x testgroup.x testtypes.x ; do ./test.sh ./$t ; done
```

# OSU MPI Tests

```
wget https://mvapich.cse.ohio-state.edu/download/mvapich/osu-micro-benchmarks-7.0.1.tar.gz
cd osu*
./configure CC=gcc CXX=g++ CFLAGS=-g3 --enable-g  CPPFLAGS=-I/home/jhammond/mukautuva LDFLAGS=-L/home/jhammond/mukautuva LIBS=-lmuk && make -j8
```

Run tests:
```
for t in `find . -type f -executable -print` ; do LD_LIBRARY_PATH=/home/jhammond/mukautuva mpirun -n 2 ./$t ; done
```

At least one RMA test with Open-MPI requires `--mca osc ucx` (vader bug). https://github.com/jeffhammond/mukautuva/issues/2

MPICH with OFI requires `RDMAV_FORK_SAFE=1`. https://github.com/jeffhammond/mukautuva/issues/3

# ARMCI-MPI

Clone as a subdirectory of `./mukautuva`:
```
git clone https://github.com/pmodels/armci-mpi.git
```

Configure like this, e.g.:
```
./configure CC=gcc CFLAGS=-g3 --enable-g  CPPFLAGS=-I.. LDFLAGS=-L.. LIBS=-lmuk && make -j4 && make -j4 checkprogs
```

Currently, Mukautuva plus Open-MPI crash in `MPI_Group_translate_ranks` so we disable rank translation caching.
```
export ARMCI_CACHE_RANK_TRANSLATION=0
LD_LIBRARY_PATH=.. make check
```

Debug a single test failure like this:
```
 make checkprogs -j4 && LD_LIBRARY_PATH=.. MPI_LIB=/usr/lib/x86_64-linux-gnu/libmpich.so  mpirun.mpich -n 4 gdb  -ex "set width 1000" -ex "thread apply all bt" -ex run -ex bt -ex "set confirm off" -ex quit --args  ./tests/test_groups
 make checkprogs -j4 && LD_LIBRARY_PATH=.. MPI_LIB=/usr/lib/x86_64-linux-gnu/libmpi.so  mpirun.openmpi -n 4 gdb  -ex "set width 1000" -ex "thread apply all bt" -ex run -ex bt -ex "set confirm off" -ex quit --args  ./tests/test_groups
```

# MPICH Test Suite

This does not work.
```sh
./configure FC=false CXX=g++ CC=gcc LIBS=-lmuk CPPFLAGS=-I$HOME/mukautuva LDFLAGS=-L$HOME/mukautuva --with-mpi=/dev/null MPICC=gcc MPICXX=g++ --enable-fortran=none
```

Maybe...
```sh
./configure CC=gcc CFLAGS=-I${HOME}/mukautuva LDFLAGS="-L${HOME}/mukautuva" LIBS="-lmuk" --disable-cxx --disable-spawn --enable-strictmpi --disable-fortran MPICC=gcc MPICXX=false MPIFC=false CXX=g++ FC=gfortran
```

# Open-MPI Debug Build

```


```

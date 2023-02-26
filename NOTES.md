# General

```
export MUK_PATH=${HOME}/mukautuva
export MUK_PATH=${HOME}/Work/MPI/mukautuva
export LD_LIBRARY_PATH=${MUK_PATH}
export DYLD_LIBRARY_PATH=${MUK_PATH}
```

# My Tests

```
for t in testcoll.x testcomm.x testinit.x testreqs.x testwin.x testgroup.x testtypes.x testops.x ; do ./test.sh ./$t ; done
```

# OSU MPI Tests

```
wget https://mvapich.cse.ohio-state.edu/download/mvapich/osu-micro-benchmarks-7.0.1.tar.gz
tar -xzf osu*gz
cd osu*
./configure CC=gcc CXX=g++ CFLAGS=-g3 --enable-g  CPPFLAGS=-I${MUK_PATH} LDFLAGS=-L${MUK_PATH} LIBS=-lmuk && make -j8
```

Run tests:
```
# Linux
for t in `find . -type f -executable -print` ; do LD_LIBRARY_PATH=${MUK_PATH} mpirun -n 2 ./$t ; done
# Mac
for t in `find . -type f -perm 755  -print` ; do LD_LIBRARY_PATH=${MUK_PATH} mpirun -n 2 ./$t ; done
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
./configure CC=gcc CFLAGS=-g3 --enable-g CPPFLAGS=-I${MUK_PATH} LDFLAGS="-L${MUK_PATH} -Wl,-rpath=${MUK_PATH}" LIBS=-lmuk
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

Required on Linux with Open-MPI (see https://github.com/open-mpi/ompi/issues/7701).
```sh
export HWLOC_COMPONENTS=-gl
```

```sh
export LD_LIBRARY_PATH=${MUK_PATH}
mkdir -p ${MUK_PATH}/bin
ln -sf `which gcc` ${MUK_PATH}/bin/mpicc
```

```
wget https://www.mpich.org/static/downloads/4.1/mpich-testsuite-4.1.tar.gz
tar -xaf mpich-testsuite-4.1.tar.gz
cd mpich-testsuite-4.1/
./configure CC=gcc CXX=g++ FC=false CPPFLAGS="-I${MUK_PATH}" LDFLAGS="-L${MUK_PATH}" LIBS="-lmuk" --enable-strictmpi --with-mpi=${MUK_PATH}
```

Useful for running multiple tests manually:
```sh
find . -type f -executable -print
for t in `find . -type f -executable -print` ; do echo Starting $t && mpirun -n 4 $t ; done
```

Run tests the right way:
```
MPIEXEC="mpirun.openmpi --oversubscribe --quiet" \
./runtests -tests=testlist -maxnp=8 -verbose -showprogress -debug
```

# Intel MPI Benchmarks

```sh
git clone https://github.com/jeffhammond/mpi-benchmarks.git IMB
```

```sh
cd src_c && make -j8
# DYLD_LIBRARY_PATH=${HOME}/Work/MPI/mukautuva
for p in IMB-EXT IMB-MPI1 IMB-NBC IMB-RMA IMB-IO ; do mpirun -n 4 ./$p ; done
```

```sh
cd src_cpp && make -j8
for t in example EXT HALO IO MPI1 MT NBC RMA ; do make TARGET=$t ; done
for t in example EXT HALO MPI1 MT NBC RMA ; do mpirun -n 4 ./IMB-$t ; done
```

# Open-MPI Debug Build

```


```

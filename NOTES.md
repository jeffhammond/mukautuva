# My Tests

```
for t in testcoll.x  testcomm.x testinit.x testreqs.x testwin.x ; do ./test.sh ./$t ; done
```

# ARMCI-MPI

```
./configure CC=gcc CFLAGS=-g3 --enable-g  CPPFLAGS=-I.. LDFLAGS=-L.. LIBS=-lmuk && make -j4 && make -j4 checkprogs
 make checkprogs -j4 && LD_LIBRARY_PATH=.. MPI_LIB=/usr/lib/x86_64-linux-gnu/libmpich.so  mpirun.mpich -n 4 gdb  -ex "set width 1000" -ex "thread apply all bt" -ex run -ex bt -ex "set confirm off" -ex quit --args  ./tests/test_groups
 make checkprogs -j4 && LD_LIBRARY_PATH=.. MPI_LIB=/usr/lib/x86_64-linux-gnu/libmpi.so  mpirun.openmpi -n 4 gdb  -ex "set width 1000" -ex "thread apply all bt" -ex run -ex bt -ex "set confirm off" -ex quit --args  ./tests/test_groups
```

# MPICH Test Suite

This does not work.
```sh
./configure FC=false CXX=g++ CC=gcc LIBS=-lmuk CPPFLAGS=-I$HOME/mukautuva LDFLAGS=-L$HOME/mukautuva --with-mpi=/dev/null MPICC=gcc MPICXX=g++ --enable-fortran=none
```

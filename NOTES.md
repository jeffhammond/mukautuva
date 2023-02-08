# My Tests

```
for t in testcoll.x  testcomm.x testinit.x testreqs.x testwin.x ; do ./test.sh ./$t ; done
```

# MPICH Test Suite

This does not work.
```sh
./configure FC=false CXX=g++ CC=gcc LIBS=-lmuk CPPFLAGS=-I$HOME/mukautuva LDFLAGS=-L$HOME/mukautuva --with-mpi=/dev/null MPICC=gcc MPICXX=g++ --enable-fortran=none
```

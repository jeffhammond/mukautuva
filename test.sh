#!/bin/bash

make -j && \
MPI_LIB=/usr/lib/x86_64-linux-gnu/libmpi.so mpirun.openmpi -n 2 $1 || \
MPI_LIB=/usr/lib/x86_64-linux-gnu/libmpi.so mpirun.openmpi -n 2 gdb -ex "set width 1000" -ex "thread apply all bt" -ex run -ex bt -ex "set confirm off" -ex quit --args  $1 ; \
MPI_LIB=/usr/lib/x86_64-linux-gnu/libmpich.so mpirun.mpich -n 2 $1 || \
MPI_LIB=/usr/lib/x86_64-linux-gnu/libmpich.so mpirun.mpich -n 2 gdb -ex "set width 1000" -ex "thread apply all bt" -ex run -ex bt -ex "set confirm off" -ex quit --args $1

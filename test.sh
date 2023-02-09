#!/bin/bash

NP=4
OPTS="--mca osc ucx"

make -j $1 && \
MPI_LIB=/usr/lib/x86_64-linux-gnu/libmpi.so mpirun.openmpi ${OPTS} -n ${NP} $1 || \
MPI_LIB=/usr/lib/x86_64-linux-gnu/libmpi.so mpirun.openmpi ${OPTS} -n ${NP} gdb -ex "set width 1000" -ex "thread apply all bt" -ex run -ex bt -ex "set confirm off" -ex quit --args  $1 ; \
MPI_LIB=/usr/lib/x86_64-linux-gnu/libmpich.so mpirun.mpich -n ${NP} $1 || \
MPI_LIB=/usr/lib/x86_64-linux-gnu/libmpich.so mpirun.mpich -n ${NP} gdb -ex "set width 1000" -ex "thread apply all bt" -ex run -ex bt -ex "set confirm off" -ex quit --args $1

#!/bin/bash

if [ `uname -s` == Darwin ] ; then
    OMPIRUN=/opt/homebrew/Cellar/open-mpi/4.1.4_2/bin/mpirun
    OMPILIB=/opt/homebrew/Cellar/mpich/4.1/lib/libmpi.dylib
    MPICHRUN=/opt/homebrew/Cellar/mpich/4.1/bin/mpirun
    MPICHLIB=/opt/homebrew/Cellar/open-mpi/4.1.4_2/lib/libmpi.dylib
else
    OMPIRUN=/usr/bin/mpirun.openmpi
    OMPILIB=/usr/lib/x86_64-linux-gnu/libmpi.so
    MPICHRUN=/usr/bin/mpirun.mpich
    MPICHLIB=/usr/lib/x86_64-linux-gnu/libmpich.so
fi

NP=4
OPTS="-quiet --mca osc ucx"

make -j $1 && \
MPI_LIB=${OMPILIB} ${OMPIRUN} ${OPTS} -n ${NP} $1 || \
MPI_LIB=${OMPILIB} ${OMPIRUN} ${OPTS} -n ${NP} gdb -ex "set width 1000" -ex "thread apply all bt" -ex run -ex bt -ex "set confirm off" -ex quit --args  $1 ; \
MPI_LIB=${MPICHLIB} ${MPICHRUN} -n ${NP} $1 || \
MPI_LIB=${MPICHLIB} ${MPICHRUN} -n ${NP} gdb -ex "set width 1000" -ex "thread apply all bt" -ex run -ex bt -ex "set confirm off" -ex quit --args $1

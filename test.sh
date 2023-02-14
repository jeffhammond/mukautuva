#!/bin/bash

set -x

if [ `uname -s` == Darwin ] ; then
    OMPIRUN=/opt/homebrew/Cellar/open-mpi/4.1.4_2/bin/mpirun
    OMPILIB=/opt/homebrew/Cellar/open-mpi/4.1.4_2/lib/libmpi.dylib
    MPICHRUN=/opt/homebrew/Cellar/mpich/4.1/bin/mpirun
    MPICHLIB=/opt/homebrew/Cellar/mpich/4.1/lib/libmpi.dylib
    DBG=lldb
    DBGARGS="--one-line 'run' --one-line-on-crash 'bt' --one-line 'quit' --"
else
    OPTS="--mca osc ucx"
    OMPIRUN=/usr/bin/mpirun.openmpi
    OMPILIB=/usr/lib/x86_64-linux-gnu/libmpi.so
    MPICHRUN=/usr/bin/mpirun.mpich
    MPICHLIB=/usr/lib/x86_64-linux-gnu/libmpich.so
    DBG=gdb
    DBGARGS="-ex "set width 1000" -ex "thread apply all bt" -ex run -ex bt -ex "set confirm off" -ex quit --args"
fi

NP=2
OPTS="${OPTS} -quiet"

make -j $1 && \
MPI_LIB=${OMPILIB} ${OMPIRUN} ${OPTS} -n ${NP} $1 || \
MPI_LIB=${OMPILIB} ${OMPIRUN} ${OPTS} -n ${NP} ${DBG} ${DBGARGS} $1 ; \
MPI_LIB=${MPICHLIB} ${MPICHRUN} -n ${NP} $1 || \
MPI_LIB=${MPICHLIB} ${MPICHRUN} -n ${NP} ${DBG} ${DBGARGS} $1

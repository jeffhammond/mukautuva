#!/bin/bash

set -x

if [ `uname -s` == Darwin ] ; then
    OMPIRUN=/opt/homebrew/Cellar/open-mpi/4.1.5/bin/mpirun
    OMPILIB=/opt/homebrew/Cellar/open-mpi/4.1.5/lib/libmpi.dylib
    MPICHRUN=/opt/homebrew/Cellar/mpich/4.1.1/bin/mpirun
    MPICHLIB=/opt/homebrew/Cellar/mpich/4.1.1/lib/libmpi.dylib
    IMPIRUN=true
    IMPILIB=
    DBG=lldb
    DBGARGS="--one-line 'run' --one-line-on-crash 'bt' --one-line 'quit' --"
else
    export HWLOC_COMPONENTS=-gl
    #OPTS="--mca osc ucx"
    OMPIRUN="/usr/bin/mpirun.openmpi --tag-output"
    OMPILIB=/usr/lib/x86_64-linux-gnu/libmpi.so
    #OMPIRUN=/opt/ompi/gcc-debug/bin/mpirun
    #OMPILIB=/opt/ompi/gcc-debug/lib/libmpi.so
    MPICHRUN="/usr/bin/mpirun.mpich -l"
    MPICHLIB=/usr/lib/x86_64-linux-gnu/libmpich.so
    #MPICHRUN="/opt/mpich/gcc/debug-ch4ucx/bin/mpirun -l"
    #MPICHLIB=/opt/mpich/gcc/debug-ch4ucx/lib/libmpi.so
    IMPIRUN="/opt/intel/oneapi/mpi/2021.8.0/bin/mpirun -l"
    IMPILIB=/opt/intel/oneapi/mpi/2021.8.0/lib/debug/libmpi.so
    #IMPILIB=/opt/intel/oneapi/mpi/2021.8.0/lib/release/libmpi.so
    DBG=gdb
    DBGARGS='-ex "set width 1000" -ex "thread apply all bt" -ex run -ex bt -ex "set confirm off" -ex quit --args'
fi

NP=2
#OPTS="${OPTS} -quiet"

make -j $1 && \
MPI_LIB=${OMPILIB} ${OMPIRUN} ${OPTS} -n ${NP} $1 || \
MPI_LIB=${OMPILIB} ${OMPIRUN} ${OPTS} -n ${NP} ${DBG} ${DBGARGS} $1 ; \
MPI_LIB=${MPICHLIB} ${MPICHRUN} -n ${NP} $1 || \
MPI_LIB=${MPICHLIB} ${MPICHRUN} -n ${NP} ${DBG} ${DBGARGS} $1
MPI_LIB=${IMPILIB} ${IMPIRUN} -n ${NP} $1 || \
MPI_LIB=${IMPILIB} ${IMPIRUN} -n ${NP} ${DBG} ${DBGARGS} $1

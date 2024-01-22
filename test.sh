#!/bin/bash

set -x

if [ $(uname -s) == Darwin ]; then
    brew_prefix=$(brew --prefix)
    OMPIRUN=$(ls $brew_prefix/Cellar/open-mpi/*/bin/mpirun)
    OMPILIB=$(ls $brew_prefix/Cellar/open-mpi/*/lib/libmpi.dylib)
    MPICHRUN=$(ls $brew_prefix/Cellar/mpich/*/bin/mpirun)
    MPICHLIB=$(ls $brew_prefix/Cellar/mpich/*/lib/libmpi.dylib)
    IMPIRUN=true
    IMPILIB=
    DBG=lldb
    DBGARGS="--one-line 'run' --one-line-on-crash 'bt' --one-line 'quit' --"
else
    OSID=$(grep '^ID=' /etc/os-release | cut -d= -f2)
    export HWLOC_COMPONENTS=-gl
    if [ "$OSID" == "ubuntu" ]; then
        OMPIRUN="/usr/bin/mpirun.openmpi --tag-output"
        OMPILIB=/usr/lib/x86_64-linux-gnu/libmpi.so
        MPICHRUN="/usr/bin/mpirun.mpich -l"
        MPICHLIB=/usr/lib/x86_64-linux-gnu/libmpich.so
    fi
    if [ "$OSID" == "fedora" ]; then
        OMPIRUN="/usr/lib64/openmpi/bin/mpirun --tag-output"
        OMPILIB=/usr/lib64/openmpi/lib/libmpi.so
        MPICHRUN="/usr/lib64/mpich/bin/mpirun -l"
        MPICHLIB=/usr/lib64/mpich/lib/libmpi.so
    fi
    if [ -e /opt/intel/oneapi/mpi/latest ]; then
       IMPIRUN="/opt/intel/oneapi/mpi/latest/bin/mpirun -l"
       IMPILIB=/opt/intel/oneapi/mpi/latest/lib/libmpi.so
    fi
    #OPTS="--mca osc ucx"
    #OMPIRUN="/usr/bin/mpirun.openmpi --tag-output"
    #OMPILIB=/usr/lib/x86_64-linux-gnu/libmpi.so
    #OMPIRUN=/opt/ompi/gcc-debug/bin/mpirun
    #OMPILIB=/opt/ompi/gcc-debug/lib/libmpi.so
    #MPICHRUN="/usr/bin/mpirun.mpich -l"
    #MPICHLIB=/usr/lib/x86_64-linux-gnu/libmpich.so
    #MPICHRUN="/opt/mpich/gcc/debug-ch4ucx/bin/mpirun -l"
    #MPICHLIB=/opt/mpich/gcc/debug-ch4ucx/lib/libmpi.so
    #IMPIRUN="/opt/intel/oneapi/mpi/2021.8.0/bin/mpirun -l"
    #IMPILIB=/opt/intel/oneapi/mpi/2021.8.0/lib/debug/libmpi.so
    #IMPILIB=/opt/intel/oneapi/mpi/2021.8.0/lib/release/libmpi.so
    DBG=gdb
    DBGARGS='-ex "set width 1000" -ex "thread apply all bt" -ex run -ex bt -ex "set confirm off" -ex quit --args'
fi

if [ "$GITHUB_ACTIONS" == "true" ]; then
    DBG=false
    DBGARGS=
fi

NP=2
#OPTS="${OPTS} -quiet"

make -j $1

if [ -n "${OMPILIB}" ]; then
    MPI_LIB=${OMPILIB} ${OMPIRUN} ${OPTS} -n ${NP} $1 || \
    MPI_LIB=${OMPILIB} ${OMPIRUN} ${OPTS} -n ${NP} ${DBG} ${DBGARGS} $1 ; \
fi

if [ -n "${MPICHLIB}" ]; then
    MPI_LIB=${MPICHLIB} ${MPICHRUN} -n ${NP} $1 || \
    MPI_LIB=${MPICHLIB} ${MPICHRUN} -n ${NP} ${DBG} ${DBGARGS} $1
fi

if [ -n "${IMPILIB}" ]; then
   MPI_LIB=${IMPILIB} ${IMPIRUN} -n ${NP} $1 || \
   MPI_LIB=${IMPILIB} ${IMPIRUN} -n ${NP} ${DBG} ${DBGARGS} $1
fi

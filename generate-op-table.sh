#!/bin/bash

let c=0
for t in \
    MPI_OP_NULL \
    MPI_MAX \
    MPI_MIN \
    MPI_SUM \
    MPI_PROD \
    MPI_LAND \
    MPI_BAND \
    MPI_LOR \
    MPI_BOR \
    MPI_LXOR \
    MPI_BXOR \
    MPI_MAXLOC \
    MPI_MINLOC \
    MPI_REPLACE \
    MPI_NO_OP \
    ; do
    echo "#define ${t} ((MPI_Op)${c})"
    let c++
done

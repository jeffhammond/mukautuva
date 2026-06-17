#!/bin/bash

let c=0
for t in \
    MPI_OP_NULL \
    MPI_SUM \
    MPI_MIN \
    MPI_MAX \
    MPI_PROD \
    MPI_BAND \
    MPI_BOR \
    MPI_BXOR \
    MPI_LAND \
    MPI_LOR \
    MPI_LXOR \
    MPI_MINLOC \
    MPI_MAXLOC \
    MPI_REPLACE \
    MPI_NO_OP \
    ; do
    #echo "#define ${t} ((MPI_Op)${c})"
    u=$(echo "$t" | sed "s/MPI/MUK/")
    #echo "${t} ${u}"
# FORWARD
    echo "    else if (op.ip == (intptr_t)${u}) {
        return ${t};
    }"
# BACKWARD
#    echo "    else if (op == ${t}) {
#        wrap.ip = (intptr_t)${u};
#    }"
    let c++
done

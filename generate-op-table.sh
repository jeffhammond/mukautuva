#!/bin/bash

let c=0
for t in \
    MPI_SUM \
    MPI_NO_OP \
    MPI_REPLACE \
    MPI_MAX \
    MPI_MIN \
    MPI_LAND \
    MPI_BAND \
    MPI_LOR \
    MPI_BOR \
    MPI_LXOR \
    MPI_BXOR \
    MPI_MAXLOC \
    MPI_MINLOC \
    MPI_OP_NULL \
    MPI_PROD \
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

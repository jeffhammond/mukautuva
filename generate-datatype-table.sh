#!/bin/bash

let c=0
for t in \
    MPI_DATATYPE_NULL \
    MPI_CHAR \
    MPI_SHORT \
    MPI_INT \
    MPI_LONG \
    MPI_LONG_LONG_INT \
    MPI_LONG_LONG \
    MPI_SIGNED_CHAR \
    MPI_UNSIGNED_CHAR \
    MPI_UNSIGNED_SHORT \
    MPI_UNSIGNED \
    MPI_UNSIGNED_LONG \
    MPI_UNSIGNED_LONG_LONG \
    MPI_FLOAT \
    MPI_DOUBLE \
    MPI_LONG_DOUBLE \
    MPI_WCHAR \
    MPI_C_BOOL \
    MPI_INT8_T \
    MPI_INT16_T \
    MPI_INT32_T \
    MPI_INT64_T \
    MPI_UINT8_T \
    MPI_UINT16_T \
    MPI_UINT32_T \
    MPI_UINT64_T \
    MPI_AINT \
    MPI_COUNT \
    MPI_OFFSET \
    MPI_C_COMPLEX \
    MPI_C_FLOAT_COMPLEX \
    MPI_C_DOUBLE_COMPLEX \
    MPI_C_LONG_DOUBLE_COMPLEX \
    MPI_BYTE \
    MPI_PACKED \
    MPI_CXX_BOOL \
    MPI_CXX_FLOAT_COMPLEX \
    MPI_CXX_DOUBLE_COMPLEX \
    MPI_CXX_LONG_DOUBLE_COMPLEX \
    MPI_INTEGER \
    MPI_REAL \
    MPI_DOUBLE_PRECISION \
    MPI_COMPLEX \
    MPI_LOGICAL \
    MPI_CHARACTER \
    MPI_DOUBLE_COMPLEX \
    MPI_INTEGER1 \
    MPI_INTEGER2 \
    MPI_INTEGER4 \
    MPI_INTEGER8 \
    MPI_INTEGER16 \
    MPI_REAL2 \
    MPI_REAL4 \
    MPI_REAL8 \
    MPI_REAL16 \
    MPI_COMPLEX4 \
    MPI_COMPLEX8 \
    MPI_COMPLEX16 \
    MPI_COMPLEX32 \
    MPI_FLOAT_INT \
    MPI_DOUBLE_INT \
    MPI_LONG_INT \
    MPI_2INT \
    MPI_SHORT_INT \
    MPI_LONG_DOUBLE_INT \
    MPI_2REAL \
    MPI_2DOUBLE_PRECISION \
    MPI_2INTEGER \
    MPI_LB \
    MPI_UB \
    ; do
    #echo "#define ${t} ((MPI_Datatype)${c})"
    u=$(echo "$t" | sed "s/MPI/MUK/")
    #echo "${t} ${u}"
# FORWARD
#    echo "#ifdef ${t}
#    else if (datatype.ip == (intptr_t)${u}) {
#        return ${t};
#    }
##endif"
# BACKWARD
    echo "#ifdef ${t}
    else if (datatype == ${t}) {
        wrap.ip = (intptr_t)${u};
    }
#endif"
    let c++
done

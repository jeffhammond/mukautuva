#ifndef IMPL_ALLTOALLW_H
#define IMPL_ALLTOALLW_H

#if 0
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

#include "impl-fpointers.h"
#include "impl-handle-conversions.h"
#include "wrap-handle-typedefs.h"
#endif

static int ALLTOALLW_SETUP(bool in_place, const MPI_Comm comm, const WRAP_Datatype sendtypes[], const WRAP_Datatype recvtypes[],
                           MPI_Datatype ** impl_sendtypes, MPI_Datatype ** impl_recvtypes)
{
    int np;
    int rc = IMPL_Comm_size(comm,&np);
    if (rc != MPI_SUCCESS) {
        return MPI_ERR_INTERN;
    }

    if (!in_place) {
        *impl_sendtypes = malloc(np * sizeof(MPI_Datatype));
        if (*impl_sendtypes == NULL) return MPI_ERR_INTERN;
        for (int i=0; i<np; i++) {
            (*impl_sendtypes)[i] = CONVERT_MPI_Datatype(sendtypes[i]);
        }
    }
    *impl_recvtypes = malloc(np * sizeof(MPI_Datatype));
    if (*impl_recvtypes == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<np; i++) {
        (*impl_recvtypes)[i] = CONVERT_MPI_Datatype(recvtypes[i]);
    }
    return MPI_SUCCESS;
}

#endif

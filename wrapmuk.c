#define USE_MPI_NAMESPACE
#include "muk-mpi-typedefs.h"
#define MAKE_INTERFACE
#include "muk-mpi-functions.h"
#undef USE_MPI_NAMESPACE
#undef MAKE_INTERFACE

#define USE_MUK_NAMESPACE
#include "muk-mpi-typedefs.h"
#define MAKE_INTERFACE
#include "muk-mpi-functions.h"
#undef USE_MUK_NAMESPACE
#undef MAKE_INTERFACE

int MPI_Abort(MPI_Comm comm, int errorcode)
{
    return MUK_Abort(comm,errorcode);
}

int MPI_Comm_size(MPI_Comm comm, int * size)
{
    return MUK_Comm_size(comm,size);
}

int MPI_Comm_rank(MPI_Comm comm, int * rank)
{
    return MUK_Comm_rank(comm,rank);
}

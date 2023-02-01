#include "muk.h"

#define USE_MUK_NAMESPACE
#include "muk-mpi-typedefs.h"
#define MAKE_FUNCTION_POINTERS
#include "muk-mpi-functions.h"

int MPI_Abort(MUK_Comm comm, int errorcode)
{
    return MUK_Abort(comm,errorcode);
}

int MPI_Comm_size(MUK_Comm comm, int * size)
{
    return MUK_Comm_size(comm,size);
}

int MPI_Comm_rank(MUK_Comm comm, int * rank)
{
    return MUK_Comm_rank(comm,rank);
}

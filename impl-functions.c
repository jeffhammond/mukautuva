#include <mpi.h>

#if defined(OPEN_MPI)
typedef void* IMPL_Comm;
#elif defined(MPICH)
typedef int IMPL_Comm;
#endif

int IMPL_Abort(IMPL_Comm * comm, int errorcode)
{
    return PMPI_Abort(*comm, errorcode);
}

int IMPL_Comm_rank(IMPL_Comm * comm, int * rank)
{
    return PMPI_Comm_rank(*comm, rank);
}

int IMPL_Comm_size(IMPL_Comm * comm, int * size)
{
    return PMPI_Comm_size(*comm, size);
}

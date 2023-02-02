#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <mpi.h>

MPI_Comm IMPL_COMM_WORLD = MPI_COMM_WORLD;

#ifdef OPEN_MPI
int IMPL_Abort(void ** comm, int errorcode)
{
    return PMPI_Abort(*comm, errorcode);
}

int IMPL_Comm_rank(void ** comm, int * rank)
{
    printf("OMPI comm=0x%lx\n", (intptr_t)(*comm));
    int rc = PMPI_Comm_rank(*comm, rank);
    printf("OMPI rank=%d\n", *rank);
    return rc;
}

int IMPL_Comm_size(void ** comm, int * size)
{
    printf("OMPI comm=0x%lx\n", (intptr_t)(*comm));
    int rc = PMPI_Comm_size(*comm, size);
    printf("OMPI size=%d\n", *size);
    return rc;
}
#endif

#ifdef MPICH
int IMPL_Abort(int * comm, int errorcode)
{
    return PMPI_Abort(*comm, errorcode);
}

int IMPL_Comm_rank(int * comm, int * rank)
{
    printf("MPICH comm=0x%x\n", (int)(*comm));
    int rc = PMPI_Comm_rank(*comm, rank);
    printf("MPICH rank=%d\n", *rank);
    return rc;
}

int IMPL_Comm_size(int * comm, int * size)
{
    printf("MPICH comm=0x%x\n", (int)(*comm));
    int rc = PMPI_Comm_size(*comm, size);
    printf("MPICH size=%d\n", *size);
    return rc;
}
#endif

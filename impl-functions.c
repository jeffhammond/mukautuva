#include "muk-dl.h"

// this is the MPI implementation header
#include <mpi.h>

#if defined(OPEN_MPI)
typedef void* IMPL_Comm;
#elif defined(MPICH)
typedef int IMPL_Comm;
#endif

int (*IMPL_Comm_rank)(IMPL_Comm comm, int *rank);
int (*IMPL_Comm_size)(IMPL_Comm comm, int *size);
int (*IMPL_Abort)(IMPL_Comm comm, int errorcode);

//
// MPI_ allows profiling of the implementation, in theory,
// assuming we figure out whatever the DLL situation is there.
//
// For development, use MPI_, because that will catch problems
// where the MUK MPI symbols are confused for IMPL MPI symbols,
// which leads to infinite recursion or segfaults.
//
// Use PMPI_ in production to keep things simple.
//
#define STRINGIFY(text) #text
#ifdef USE_IMPL_PMPI_SYMBOLS
#define NIMI(text) "PMPI_" STRINGIFY(text)
#else
#define NIMI(text) "MPI_" STRINGIFY(text)
#endif

int WRAP_Load_functions(void * restrict h, int major, int minor)
{
    (void)major;
    (void)minor;
    IMPL_Abort = MUK_DLSYM(h, NIMI(Abort) );
    IMPL_Comm_rank = MUK_DLSYM(h, NIMI(Comm_rank) );
    IMPL_Comm_size = MUK_DLSYM(h, NIMI(Comm_size) );
    return 0;
}

int WRAP_Abort(IMPL_Comm * comm, int errorcode)
{
    return IMPL_Abort(*comm, errorcode);
}

int WRAP_Comm_rank(IMPL_Comm * comm, int * rank)
{
    return IMPL_Comm_rank(*comm, rank);
}

int WRAP_Comm_size(IMPL_Comm * comm, int * size)
{
    return IMPL_Comm_size(*comm, size);
}

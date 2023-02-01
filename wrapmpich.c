// we need all the typedefs and function prototypes for the MUK ABI
#define USE_MUK_NAMESPACE
#include "muk-mpi-typedefs.h"
#define MAKE_INTERFACE
#include "muk-mpi-functions.h"

// this contains predefined handles that use the MUK ABI
//#include "muk-builtin-handles.h"

// this is the OMPI header
#include <mpi.h>

typedef struct __MPICH_Status__
{
    int count_lo;
    int count_hi_and_cancelled;
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
}
MPICH_Status;

// MPICH handles are integers (except for MPI_File), so MUK handles (pointers) point to the respective MPICH handles
// muuntaa = convert
static inline MPI_Comm Muuntaa_Comm(MUK_Comm Comm) { return *(int*)Comm; }
static inline MPI_Datatype Muuntaa_Datatype(MUK_Datatype Datatype) { return *(int*)Datatype; }
static inline MPI_Errhandler Muuntaa_Errhandler(MUK_Errhandler Errhandler) { return *(int*)Errhandler; }
static inline MPI_File Muuntaa_File(MUK_File File) { return (MPI_File)File; } // exception
static inline MPI_Group Muuntaa_Group(MUK_Group Group) { return *(int*)Group; }
static inline MPI_Info Muuntaa_Info(MUK_Info Info) { return *(int*)Info; }
static inline MPI_Message Muuntaa_Message(MUK_Message Message) { return *(int*)Message; }
static inline MPI_Op Muuntaa_Op(MUK_Op Op) { return *(int*)Op; }
static inline MPI_Request Muuntaa_Request(MUK_Request Request) { return *(int*)Request; }
static inline MPI_Win Muuntaa_Win(MUK_Win Win) { return *(int*)Win; }
#if MPI_VERSION >= 4
static inline MPI_Session Muuntaa_Session(MUK_Session Session) { return *(int*)Session; }
#endif

int MUK_Abort(MUK_Comm comm, int errorcode)
{
    return MPI_Abort(Muuntaa_Comm(comm),errorcode);
}

int MUK_Comm_size(MUK_Comm comm, int * size)
{
    return MPI_Comm_size(Muuntaa_Comm(comm),size);
}

int MUK_Comm_rank(MUK_Comm comm, int * rank)
{
    return MPI_Comm_rank(Muuntaa_Comm(comm),rank);
}

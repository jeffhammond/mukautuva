#include <mpi.h>

// This file captures all of the predefined handles
// so that they can be referenced by dlsym, since
// this is not necessarily possible.
//
// MPICH, for example, defines predefined handles in
// the preprocessor, which means there are no symbols
// in the MPICH shared library.

MPI_Request IMPL_REQUEST_NULL = MPI_REQUEST_NULL;

MPI_Datatype IMPL_DATATYPE_NULL = MPI_DATATYPE_NULL;

MPI_Op IMPL_OP_NULL = MPI_OP_NULL;

MPI_Errhandler IMPL_ERRHANDLER_NULL = MPI_ERRHANDLER_NULL;

MPI_Info IMPL_INFO_NULL = MPI_INFO_NULL;

MPI_Win IMPL_WIN_NULL =  MPI_WIN_NULL;

MPI_File IMPL_FILE_NULL = MPI_FILE_NULL;

MPI_Comm IMPL_COMM_NULL  = MPI_COMM_NULL;
MPI_Comm IMPL_COMM_WORLD = MPI_COMM_WORLD;
MPI_Comm IMPL_COMM_SELF  = MPI_COMM_SELF;

MPI_Group IMPL_GROUP_NULL  = MPI_GROUP_NULL;
MPI_Group IMPL_GROUP_EMPTY = MPI_GROUP_EMPTY;

MPI_Message IMPL_MESSAGE_NULL = MPI_MESSAGE_NULL;
MPI_Message IMPL_MESSAGE_NO_PROC = MPI_MESSAGE_NO_PROC;

MPI_Status* IMPL_STATUS_IGNORE = MPI_STATUS_IGNORE;
MPI_Status* IMPL_STATUSES_IGNORE = MPI_STATUSES_IGNORE;

#if 0
int impl_mpi_comm_type_shared(void) { return MPI_COMM_TYPE_SHARED; }
int impl_mpi_comm_type_hw_guided(void) { return MPI_COMM_TYPE_HW_GUIDED; }
#endif

#ifndef MUK_MPI_HANDLE_TYPEDEFS_H
#define MUK_MPI_HANDLE_TYPEDEFS_H

#ifdef MUK_INTERNAL
typedef void * MPI_Comm;
typedef void * MPI_Datatype;
typedef void * MPI_Errhandler;
typedef void * MPI_File;
typedef void * MPI_Group;
typedef void * MPI_Info;
typedef void * MPI_Message;
typedef void * MPI_Op;
typedef void * MPI_Request;
typedef void * MPI_Session;
typedef void * MPI_Win;
#else
typedef struct MPI_ABI_Comm * MPI_Comm;
typedef struct MPI_ABI_Datatype * MPI_Datatype;
typedef struct MPI_ABI_Errhandler * MPI_Errhandler;
typedef struct MPI_ABI_File * MPI_File;
typedef struct MPI_ABI_Group * MPI_Group;
typedef struct MPI_ABI_Info * MPI_Info;
typedef struct MPI_ABI_Message * MPI_Message;
typedef struct MPI_ABI_Op * MPI_Op;
typedef struct MPI_ABI_Request * MPI_Request;
typedef struct MPI_ABI_Session * MPI_Session;
typedef struct MPI_ABI_Win * MPI_Win;
#endif

#endif

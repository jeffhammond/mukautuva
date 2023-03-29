// SPDX-License-Identifier: MIT

#ifndef MUK_MPI_HANDLE_TYPEDEFS_H
#define MUK_MPI_HANDLE_TYPEDEFS_H

#ifdef MUK_INTERNAL
#include <stddef.h>
typedef union 
{
    void *      p;
    int         i;
    intptr_t    ip;
}
MUK_Handle;
typedef MUK_Handle MPI_Comm;
typedef MUK_Handle MPI_Datatype;
typedef MUK_Handle MPI_Errhandler;
typedef MUK_Handle MPI_File;
typedef MUK_Handle MPI_Group;
typedef MUK_Handle MPI_Info;
typedef MUK_Handle MPI_Message;
typedef MUK_Handle MPI_Op;
typedef MUK_Handle MPI_Request;
typedef MUK_Handle MPI_Session;
typedef MUK_Handle MPI_Win;
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

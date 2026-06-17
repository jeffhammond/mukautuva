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
typedef MUK_Handle MPI_T_enum;
typedef MUK_Handle MPI_T_cvar_handle;
typedef MUK_Handle MPI_T_pvar_handle;
typedef MUK_Handle MPI_T_pvar_session;
typedef MUK_Handle MPI_T_event_registration;
typedef MUK_Handle MPI_T_event_instance;
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
typedef struct MPI_ABI_T_enum * MPI_T_enum;
typedef struct MPI_ABI_T_cvar_handle * MPI_T_cvar_handle;
typedef struct MPI_ABI_T_pvar_handle * MPI_T_pvar_handle;
typedef struct MPI_ABI_T_pvar_session * MPI_T_pvar_session;
typedef struct MPI_ABI_T_event_registration * MPI_T_event_registration;
typedef struct MPI_ABI_T_event_instance * MPI_T_event_instance;
#endif

#endif

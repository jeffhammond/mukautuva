#ifndef WRAP_HANDLE_TYPEDEFS_H
#define WRAP_HANDLE_TYPEDEFS_H

#include "impl-scalar-types.h"
#include "impl-status.h"

typedef union
{
    void *      p;
    int         i;
    intptr_t    ip;
}
MUK_Handle;

typedef MUK_Handle WRAP_Comm;
typedef MUK_Handle WRAP_Datatype;
typedef MUK_Handle WRAP_Errhandler;
typedef MUK_Handle WRAP_File;
typedef MUK_Handle WRAP_Group;
typedef MUK_Handle WRAP_Info;
typedef MUK_Handle WRAP_Message;
typedef MUK_Handle WRAP_Op;
typedef MUK_Handle WRAP_Request;
typedef MUK_Handle WRAP_Session;
typedef MUK_Handle WRAP_Win;

// callback typedefs
typedef void WRAP_User_function(void *invec, void *inoutvec, int *len, WRAP_Datatype *datatype);
typedef void WRAP_User_function_c(void *invec, void *inoutvec, WRAP_Count *len, WRAP_Datatype *datatype);
typedef int WRAP_Comm_copy_attr_function(WRAP_Comm oldcomm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int WRAP_Comm_delete_attr_function(WRAP_Comm comm, int comm_keyval, void *attribute_val, void *extra_state);
typedef int WRAP_Win_copy_attr_function(WRAP_Win oldwin, int win_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int WRAP_Win_delete_attr_function(WRAP_Win win, int win_keyval, void *attribute_val, void *extra_state);
typedef int WRAP_Type_copy_attr_function(WRAP_Datatype oldtype, int type_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int WRAP_Type_delete_attr_function(WRAP_Datatype datatype, int type_keyval, void *attribute_val, void *extra_state);
typedef void WRAP_Comm_errhandler_function(WRAP_Comm *comm, int *error_code, ...);
typedef void WRAP_Win_errhandler_function(WRAP_Win *win, int *error_code, ...);
typedef void WRAP_File_errhandler_function(WRAP_File *file, int *error_code, ...);
typedef void WRAP_Session_errhandler_function(WRAP_Session *session, int *error_code, ...);
typedef int WRAP_Grequest_query_function(void *extra_state, WRAP_Status *status);
typedef int WRAP_Grequest_free_function(void *extra_state);
typedef int WRAP_Grequest_cancel_function(void *extra_state, int complete);
typedef int WRAP_Datarep_extent_function(WRAP_Datatype datatype, WRAP_Aint *extent, void *extra_state);
typedef int WRAP_Datarep_conversion_function(void *userbuf, WRAP_Datatype datatype, int count, void *filebuf, WRAP_Offset position, void *extra_state);
typedef int WRAP_Datarep_conversion_function_c(void *userbuf, WRAP_Datatype datatype, WRAP_Count count, void *filebuf, WRAP_Offset position, void *extra_state);

// these are deprecated
typedef int WRAP_Copy_function(WRAP_Comm oldcomm, int keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int WRAP_Delete_function(WRAP_Comm comm, int keyval, void *attribute_val, void *extra_state);

#endif

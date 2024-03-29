// SPDX-License-Identifier: MIT

#ifndef MUK_MPI_TYPEDEFS_H
#define MUK_MPI_TYPEDEFS_H

#include <stddef.h>

// basic typedefs
typedef ptrdiff_t MPI_Aint;
typedef ptrdiff_t MPI_Count;
typedef ptrdiff_t MPI_Offset;

// deal with this later during VAPAA integration
typedef int MPI_Fint;

// status typedef
typedef struct
{
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    int __kielletty__[5];
}
MPI_Status;

// callback typedefs

// reductions
typedef void MPI_User_function(void *invec, void *inoutvec, int *len, MPI_Datatype *datatype);
typedef void MPI_User_function_c(void *invec, void *inoutvec, MPI_Count *len, MPI_Datatype *datatype);

// comm attr
typedef int MPI_Comm_copy_attr_function(MPI_Comm oldcomm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MPI_Comm_delete_attr_function(MPI_Comm comm, int comm_keyval, void *attribute_val, void *extra_state);
// these are deprecated or deleted
typedef int MPI_Copy_function(MPI_Comm oldcomm, int keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MPI_Delete_function(MPI_Comm comm, int keyval, void *attribute_val, void *extra_state);
typedef void MPI_Handler_function(MPI_Comm *comm, int *error_code,...);

// win attr
typedef int MPI_Win_copy_attr_function(MPI_Win oldwin, int win_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MPI_Win_delete_attr_function(MPI_Win win, int win_keyval, void *attribute_val, void *extra_state);

// type attr
typedef int MPI_Type_copy_attr_function(MPI_Datatype oldtype, int type_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MPI_Type_delete_attr_function(MPI_Datatype datatype, int type_keyval, void *attribute_val, void *extra_state);

// errhandler
typedef void MPI_Comm_errhandler_function(MPI_Comm *comm, int *error_code, ...);
typedef void MPI_Win_errhandler_function(MPI_Win *win, int *error_code, ...);
typedef void MPI_File_errhandler_function(MPI_File *file, int *error_code, ...);
typedef void MPI_Session_errhandler_function(MPI_Session *session, int *error_code, ...);

// grequest
typedef int MPI_Grequest_query_function(void *extra_state, MPI_Status *status);
typedef int MPI_Grequest_free_function(void *extra_state);
typedef int MPI_Grequest_cancel_function(void *extra_state, int complete);

// datarep
typedef int MPI_Datarep_extent_function(MPI_Datatype datatype, MPI_Aint *extent, void *extra_state);
typedef int MPI_Datarep_conversion_function(void *userbuf, MPI_Datatype datatype, int count, void *filebuf, MPI_Offset position, void *extra_state);
typedef int MPI_Datarep_conversion_function_c(void *userbuf, MPI_Datatype datatype, MPI_Count count, void *filebuf, MPI_Offset position, void *extra_state);

#endif

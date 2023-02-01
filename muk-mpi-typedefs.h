#ifndef MUK_MPI_TYPEDEFS_H
#define MUK_MPI_TYPEDEFS_H

#if defined(USE_MPI_NAMESPACE)
#define NIMI_SUB(text) MPI ## _ ## text
#elif defined(USE_MUK_NAMESPACE)
#define NIMI_SUB(text) MUK ## _ ## text
#else
#error Namespace substitution problem
#endif

typedef struct __MPI_Comm__         * NIMI_SUB(Comm);
typedef struct __MPI_Datatype__     * NIMI_SUB(Datatype);
typedef struct __MPI_Errhandler__   * NIMI_SUB(Errhandler);
typedef struct __MPI_File__         * NIMI_SUB(File);
typedef struct __MPI_Group__        * NIMI_SUB(Group);
typedef struct __MPI_Info__         * NIMI_SUB(Info);
typedef struct __MPI_Message__      * NIMI_SUB(Message);
typedef struct __MPI_Op__           * NIMI_SUB(Op);
typedef struct __MPI_Request__      * NIMI_SUB(Request);
typedef struct __MPI_Session__      * NIMI_SUB(Session);
typedef struct __MPI_Win__          * NIMI_SUB(Win);

typedef struct __MPI_Status__
{
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    int __kielletty__[5];
}
NIMI_SUB(Status);

#include <stddef.h>
typedef ptrdiff_t NIMI_SUB(Aint);
typedef ptrdiff_t NIMI_SUB(Count);
typedef ptrdiff_t NIMI_SUB(Offset);

// A.1.3 Prototype Definitions
typedef void NIMI_SUB(User_function)(void *invec, void *inoutvec, int *len, NIMI_SUB(Datatype) *datatype);
typedef void NIMI_SUB(User_function_c)(void *invec, void *inoutvec, NIMI_SUB(Count) *len, NIMI_SUB(Datatype) *datatype);
typedef int NIMI_SUB(Comm_copy_attr_function)(NIMI_SUB(Comm) oldcomm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int NIMI_SUB(Comm_delete_attr_function)(NIMI_SUB(Comm) comm, int comm_keyval, void *attribute_val, void *extra_state);
typedef int NIMI_SUB(Win_copy_attr_function)(NIMI_SUB(Win) oldwin, int win_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int NIMI_SUB(Win_delete_attr_function)(NIMI_SUB(Win) win, int win_keyval, void *attribute_val, void *extra_state);
typedef int NIMI_SUB(Type_copy_attr_function)(NIMI_SUB(Datatype) oldtype, int type_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int NIMI_SUB(Type_delete_attr_function)(NIMI_SUB(Datatype) datatype, int type_keyval, void *attribute_val, void *extra_state);
typedef void NIMI_SUB(Comm_errhandler_function)(NIMI_SUB(Comm) *comm, int *error_code, ...);
typedef void NIMI_SUB(Win_errhandler_function)(NIMI_SUB(Win) *win, int *error_code, ...);
typedef void NIMI_SUB(File_errhandler_function)(NIMI_SUB(File) *file, int *error_code, ...);
typedef void NIMI_SUB(Session_errhandler_function)(NIMI_SUB(Session) *session, int *error_code, ...);
typedef int NIMI_SUB(Grequest_query_function)(void *extra_state, NIMI_SUB(Status) *status);
typedef int NIMI_SUB(Grequest_free_function)(void *extra_state);
typedef int NIMI_SUB(Grequest_cancel_function)(void *extra_state, int complete);
typedef int NIMI_SUB(Datarep_extent_function)(NIMI_SUB(Datatype) datatype, NIMI_SUB(Aint) *extent, void *extra_state);
typedef int NIMI_SUB(Datarep_conversion_function)(void *userbuf, NIMI_SUB(Datatype) datatype, int count, void *filebuf, NIMI_SUB(Offset) position, void *extra_state);
typedef int NIMI_SUB(Datarep_conversion_function_c)(void *userbuf, NIMI_SUB(Datatype) datatype, NIMI_SUB(Count) count, void *filebuf, NIMI_SUB(Offset) position, void *extra_state);

#endif

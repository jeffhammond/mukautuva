#ifndef MUK_MPI_H
#define MUK_MPI_H

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
typedef int NIMI_SUB(Comm_copy_attr_function)(MPI_Comm oldcomm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int NIMI_SUB(Comm_delete_attr_function)(MPI_Comm comm, int comm_keyval, void *attribute_val, void *extra_state);
typedef int NIMI_SUB(Win_copy_attr_function)(MPI_Win oldwin, int win_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int NIMI_SUB(Win_delete_attr_function)(MPI_Win win, int win_keyval, void *attribute_val, void *extra_state);
typedef int NIMI_SUB(Type_copy_attr_function)(MPI_Datatype oldtype, int type_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int NIMI_SUB(Type_delete_attr_function)(MPI_Datatype datatype, int type_keyval, void *attribute_val, void *extra_state);
typedef void NIMI_SUB(Comm_errhandler_function)(MPI_Comm *comm, int *error_code, ...);
typedef void NIMI_SUB(Win_errhandler_function)(MPI_Win *win, int *error_code, ...);
typedef void NIMI_SUB(File_errhandler_function)(MPI_File *file, int *error_code, ...);
typedef void NIMI_SUB(Session_errhandler_function)(MPI_Session *session, int *error_code, ...);
typedef int NIMI_SUB(Grequest_query_function)(void *extra_state, NIMI_SUB(Status) *status);
typedef int NIMI_SUB(Grequest_free_function)(void *extra_state);
typedef int NIMI_SUB(Grequest_cancel_function)(void *extra_state, int complete);
typedef int NIMI_SUB(Datarep_extent_function)(MPI_Datatype datatype, NIMI_SUB(Aint) *extent, void *extra_state);
typedef int NIMI_SUB(Datarep_conversion_function)(void *userbuf, NIMI_SUB(Datatype) datatype, int count, void *filebuf, NIMI_SUB(Offset) position, void *extra_state);
typedef int NIMI_SUB(Datarep_conversion_function_c)(void *userbuf, NIMI_SUB(Datatype) datatype, NIMI_SUB(Count) count, void *filebuf, NIMI_SUB(Offset) position, void *extra_state);
#if 0
typedef void NIMI_SUB(T_event_cb_function)(MPI_T_event_instance event_instance, NIMI##_T_event_registration event_registration, NIMI##_T_cb_safety cb_safety, void *user_data);
typedef void NIMI_SUB(T_event_free_cb_function)(MPI_T_event_registration event_registration, NIMI##_T_cb_safety cb_safety, void *user_data);
typedef void NIMI_SUB(T_event_dropped_cb_function)(MPI_Count count, NIMI##_T_event_registration event_registration, int source_index, NIMI##_T_cb_safety cb_safety, void *user_data);
#endif

// A.3.7 NIMI## Environmental Management C Bindings
int NIMI_SUB(Add_error_class)(int *errorclass);
int NIMI_SUB(Add_error_code)(int errorclass, int *errorcode);
int NIMI_SUB(Add_error_string)(int errorcode, const char *string);
int NIMI_SUB(Alloc_mem)(NIMI_SUB(Aint) size, NIMI_SUB(Info) info, void *baseptr);
int NIMI_SUB(Comm_call_errhandler)(MPI_Comm comm, int errorcode);
int NIMI_SUB(Comm_create_errhandler)(MPI_Comm_errhandler_function *comm_errhandler_fn, NIMI_SUB(Errhandler) *errhandler);
int NIMI_SUB(Comm_get_errhandler)(MPI_Comm comm, NIMI_SUB(Errhandler) *errhandler);
int NIMI_SUB(Comm_set_errhandler)(MPI_Comm comm, NIMI_SUB(Errhandler) errhandler);
int NIMI_SUB(Errhandler_free)(MPI_Errhandler *errhandler);
int NIMI_SUB(Error_class)(int errorcode, int *errorclass);
int NIMI_SUB(Error_string)(int errorcode, char *string, int *resultlen);
int NIMI_SUB(File_call_errhandler)(MPI_File fh, int errorcode);
int NIMI_SUB(File_create_errhandler)(MPI_File_errhandler_function *file_errhandler_fn, NIMI_SUB(Errhandler) *errhandler);
int NIMI_SUB(File_get_errhandler)(MPI_File file, NIMI_SUB(Errhandler) *errhandler);
int NIMI_SUB(File_set_errhandler)(MPI_File file, NIMI_SUB(Errhandler) errhandler);
int NIMI_SUB(Free_mem)(void *base);
int NIMI_SUB(Get_library_version)(char *version, int *resultlen);
int NIMI_SUB(Get_processor_name)(char *name, int *resultlen);
int NIMI_SUB(Get_version)(int *version, int *subversion);
int NIMI_SUB(Session_call_errhandler)(MPI_Session session, int errorcode);
int NIMI_SUB(Session_create_errhandler)(MPI_Session_errhandler_function *session_errhandler_fn, NIMI_SUB(Errhandler) *errhandler);
int NIMI_SUB(Session_get_errhandler)(MPI_Session session, NIMI_SUB(Errhandler) *errhandler);
int NIMI_SUB(Session_set_errhandler)(MPI_Session session, NIMI_SUB(Errhandler) errhandler);
int NIMI_SUB(Win_call_errhandler)(MPI_Win win, int errorcode);
int NIMI_SUB(Win_create_errhandler)(MPI_Win_errhandler_function *win_errhandler_fn, NIMI_SUB(Errhandler) *errhandler);
int NIMI_SUB(Win_get_errhandler)(MPI_Win win, NIMI_SUB(Errhandler) *errhandler);
int NIMI_SUB(Win_set_errhandler)(MPI_Win win, NIMI_SUB(Errhandler) errhandler);
int NIMI_SUB(Info_create)(MPI_Info *info);
double NIMI_SUB(Wtime)(void);
double NIMI_SUB(Wtick)(void);

// A.3.9 Process Creation and Management C Bindings
int NIMI_SUB(Close_port)(const char *port_name);
int NIMI_SUB(Comm_disconnect)(MPI_Comm *comm);
int NIMI_SUB(Info_dup)(MPI_Info info, NIMI_SUB(Info) *newinfo);
int NIMI_SUB(Info_free)(MPI_Info *info);
int NIMI_SUB(Info_get_nkeys)(MPI_Info info, int *nkeys);
int NIMI_SUB(Info_get_nthkey)(MPI_Info info, int n, char *key);
int NIMI_SUB(Info_get_string)(MPI_Info info, const char *key, int *buflen, char *value, int *flag);
int NIMI_SUB(Info_set)(MPI_Info info, const char *key, const char *value);
int NIMI_SUB(Abort)(MPI_Comm comm, int errorcode);
int NIMI_SUB(Comm_accept)(const char *port_name, NIMI_SUB(Info) info, int root, NIMI_SUB(Comm) comm, NIMI_SUB(Comm) *newcomm);
int NIMI_SUB(Comm_connect)(const char *port_name, NIMI_SUB(Info) info, int root, NIMI_SUB(Comm) comm, NIMI_SUB(Comm) *newcomm);
int NIMI_SUB(Comm_get_parent)(MPI_Comm *parent);
int NIMI_SUB(Comm_join)(int fd, NIMI_SUB(Comm) *intercomm);
int NIMI_SUB(Comm_spawn)(const char *command, char *argv[], int maxprocs, NIMI_SUB(Info) info, int root, NIMI_SUB(Comm) comm, NIMI_SUB(Comm) *intercomm, int array_of_errcodes[]);
int NIMI_SUB(Comm_spawn_multiple)(int count, char *array_of_commands[], char **array_of_argv[], const int array_of_maxprocs[], const NIMI_SUB(Info) array_of_info[], int root, NIMI_SUB(Comm) comm, NIMI_SUB(Comm) *intercomm, int array_of_errcodes[]);
int NIMI_SUB(Finalize)(void);
int NIMI_SUB(Finalized)(int *flag);
int NIMI_SUB(Init)(int *argc, char ***argv);
int NIMI_SUB(Init_thread)(int *argc, char ***argv, int required, int *provided);
int NIMI_SUB(Initialized)(int *flag);
int NIMI_SUB(Is_thread_main)(int *flag);
int NIMI_SUB(Lookup_name)(const char *service_name, NIMI_SUB(Info) info, char *port_name);
int NIMI_SUB(Open_port)(MPI_Info info, char *port_name);
int NIMI_SUB(Publish_name)(const char *service_name, NIMI_SUB(Info) info, const char *port_name);
int NIMI_SUB(Query_thread)(int *provided);
int NIMI_SUB(Session_finalize)(MPI_Session *session);
int NIMI_SUB(Session_get_nth_pset)(MPI_Session session, NIMI_SUB(Info) info, int n, int *pset_len, char *pset_name);
int NIMI_SUB(Session_get_info)(MPI_Session session, NIMI_SUB(Info) *info_used);
int NIMI_SUB(Session_get_num_psets)(MPI_Session session, NIMI_SUB(Info) info, int *npset_names);
int NIMI_SUB(Session_get_pset_info)(MPI_Session session, const char *pset_name, NIMI_SUB(Info) *info);
int NIMI_SUB(Session_init)(MPI_Info info, NIMI_SUB(Errhandler) errhandler, NIMI_SUB(Session) *session);
int NIMI_SUB(Unpublish_name)(const char *service_name, NIMI_SUB(Info) info, const char *port_name);

#endif

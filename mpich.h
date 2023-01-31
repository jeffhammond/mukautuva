#ifndef MPICH_H
#define MPICH_H

typedef int MPICH_Comm;
typedef int MPICH_Datatype;
typedef int MPICH_Errhandler;
typedef struct __MPICH_File__ * MPICH_File;
typedef int MPICH_Group;
typedef int MPICH_Info;
typedef int MPICH_Message;
typedef int MPICH_Op;
typedef int MPICH_Request;
typedef int MPICH_Session;
typedef int MPICH_Win;

typedef struct __MPICH_Status__
{
    int count_lo;
    int count_hi_and_cancelled;
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
}
MPICH_Status;

#include <stddef.h>
typedef long MPICH_Aint;
typedef long long MPICH_Count;
typedef long long MPICH_Offset;

// A.1.3 Prototype Definitions
typedef void MPICH_User_function(void *invec, void *inoutvec, int *len, MPICH_Datatype *datatype);
typedef void MPICH_User_function_c(void *invec, void *inoutvec, MPICH_Count *len, MPICH_Datatype *datatype);
typedef int MPICH_Comm_copy_attr_function(MPICH_Comm oldcomm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MPICH_Comm_delete_attr_function(MPICH_Comm comm, int comm_keyval, void *attribute_val, void *extra_state);
typedef int MPICH_Win_copy_attr_function(MPICH_Win oldwin, int win_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MPICH_Win_delete_attr_function(MPICH_Win win, int win_keyval, void *attribute_val, void *extra_state);
typedef int MPICH_Type_copy_attr_function(MPICH_Datatype oldtype, int type_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MPICH_Type_delete_attr_function(MPICH_Datatype datatype, int type_keyval, void *attribute_val, void *extra_state);
typedef void MPICH_Comm_errhandler_function(MPICH_Comm *comm, int *error_code, ...);
typedef void MPICH_Win_errhandler_function(MPICH_Win *win, int *error_code, ...);
typedef void MPICH_File_errhandler_function(MPICH_File *file, int *error_code, ...);
typedef void MPICH_Session_errhandler_function(MPICH_Session *session, int *error_code, ...);
typedef int MPICH_Grequest_query_function(void *extra_state, MPICH_Status *status);
typedef int MPICH_Grequest_free_function(void *extra_state);
typedef int MPICH_Grequest_cancel_function(void *extra_state, int complete);
typedef int MPICH_Datarep_extent_function(MPICH_Datatype datatype, MPICH_Aint *extent, void *extra_state);
typedef int MPICH_Datarep_conversion_function(void *userbuf, MPICH_Datatype datatype, int count, void *filebuf, MPICH_Offset position, void *extra_state);
typedef int MPICH_Datarep_conversion_function_c(void *userbuf, MPICH_Datatype datatype, MPICH_Count count, void *filebuf, MPICH_Offset position, void *extra_state);
#if 0
typedef void MPICH_T_event_cb_function(MPICH_T_event_instance event_instance, MPICH_T_event_registration event_registration, MPICH_T_cb_safety cb_safety, void *user_data);
typedef void MPICH_T_event_free_cb_function(MPICH_T_event_registration event_registration, MPICH_T_cb_safety cb_safety, void *user_data);
typedef void MPICH_T_event_dropped_cb_function(MPICH_Count count, MPICH_T_event_registration event_registration, int source_index, MPICH_T_cb_safety cb_safety, void *user_data);
#endif

// VIM tip:
// s/int MPICH_\(.*\)(\(.*\));/int (*MPICH_\1)(\2);

// A.3.7 MPICH Environmental Management C Bindings
int (*MPICH_Add_error_class)(int *errorclass);
int (*MPICH_Add_error_code)(int errorclass, int *errorcode);
int (*MPICH_Add_error_string)(int errorcode, const char *string);
int (*MPICH_Alloc_mem)(MPICH_Aint size, MPICH_Info info, void *baseptr);
int (*MPICH_Comm_call_errhandler)(MPICH_Comm comm, int errorcode);
int (*MPICH_Comm_create_errhandler)(MPICH_Comm_errhandler_function *comm_errhandler_fn, MPICH_Errhandler *errhandler);
int (*MPICH_Comm_get_errhandler)(MPICH_Comm comm, MPICH_Errhandler *errhandler);
int (*MPICH_Comm_set_errhandler)(MPICH_Comm comm, MPICH_Errhandler errhandler);
int (*MPICH_Errhandler_free)(MPICH_Errhandler *errhandler);
int (*MPICH_Error_class)(int errorcode, int *errorclass);
int (*MPICH_Error_string)(int errorcode, char *string, int *resultlen);
int (*MPICH_File_call_errhandler)(MPICH_File fh, int errorcode);
int (*MPICH_File_create_errhandler)(MPICH_File_errhandler_function *file_errhandler_fn, MPICH_Errhandler *errhandler);
int (*MPICH_File_get_errhandler)(MPICH_File file, MPICH_Errhandler *errhandler);
int (*MPICH_File_set_errhandler)(MPICH_File file, MPICH_Errhandler errhandler);
int (*MPICH_Free_mem)(void *base);
int (*MPICH_Session_call_errhandler)(MPICH_Session session, int errorcode);
int (*MPICH_Session_create_errhandler)(MPICH_Session_errhandler_function *session_errhandler_fn, MPICH_Errhandler *errhandler);
int (*MPICH_Session_get_errhandler)(MPICH_Session session, MPICH_Errhandler *errhandler);
int (*MPICH_Session_set_errhandler)(MPICH_Session session, MPICH_Errhandler errhandler);
int (*MPICH_Win_call_errhandler)(MPICH_Win win, int errorcode);
int (*MPICH_Win_create_errhandler)(MPICH_Win_errhandler_function *win_errhandler_fn, MPICH_Errhandler *errhandler);
int (*MPICH_Win_get_errhandler)(MPICH_Win win, MPICH_Errhandler *errhandler);
int (*MPICH_Win_set_errhandler)(MPICH_Win win, MPICH_Errhandler errhandler);
int (*MPICH_Info_create)(MPICH_Info *info);

// technically, these are not required to be symbols, but we know they are.
// we can work around the theoretical problem if necessary.
double (*MPICH_Wtime)(void);
double (*MPICH_Wtick)(void);

// A.3.9 Process Creation and Management C Bindings
int (*MPICH_Close_port)(const char *port_name);
int (*MPICH_Comm_disconnect)(MPICH_Comm *comm);
int (*MPICH_Info_dup)(MPICH_Info info, MPICH_Info *newinfo);
int (*MPICH_Info_free)(MPICH_Info *info);
int (*MPICH_Info_get_nkeys)(MPICH_Info info, int *nkeys);
int (*MPICH_Info_get_nthkey)(MPICH_Info info, int n, char *key);
int (*MPICH_Info_get_string)(MPICH_Info info, const char *key, int *buflen, char *value, int *flag);
int (*MPICH_Info_set)(MPICH_Info info, const char *key, const char *value);
int (*MPICH_Abort)(MPICH_Comm comm, int errorcode);
int (*MPICH_Comm_accept)(const char *port_name, MPICH_Info info, int root, MPICH_Comm comm, MPICH_Comm *newcomm);
int (*MPICH_Comm_connect)(const char *port_name, MPICH_Info info, int root, MPICH_Comm comm, MPICH_Comm *newcomm);
int (*MPICH_Comm_get_parent)(MPICH_Comm *parent);
int (*MPICH_Comm_join)(int fd, MPICH_Comm *intercomm);
int (*MPICH_Comm_spawn)(const char *command, char *argv[], int maxprocs, MPICH_Info info, int root, MPICH_Comm comm, MPICH_Comm *intercomm, int array_of_errcodes[]);
int (*MPICH_Comm_spawn_multiple)(int count, char *array_of_commands[], char **array_of_argv[], const int array_of_maxprocs[], const MPICH_Info array_of_info[], int root, MPICH_Comm comm, MPICH_Comm *intercomm, int array_of_errcodes[]);
int (*MPICH_Lookup_name)(const char *service_name, MPICH_Info info, char *port_name);
int (*MPICH_Open_port)(MPICH_Info info, char *port_name);
int (*MPICH_Publish_name)(const char *service_name, MPICH_Info info, const char *port_name);
int (*MPICH_Session_finalize)(MPICH_Session *session);
int (*MPICH_Session_get_nth_pset)(MPICH_Session session, MPICH_Info info, int n, int *pset_len, char *pset_name);
int (*MPICH_Session_get_info)(MPICH_Session session, MPICH_Info *info_used);
int (*MPICH_Session_get_num_psets)(MPICH_Session session, MPICH_Info info, int *npset_names);
int (*MPICH_Session_get_pset_info)(MPICH_Session session, const char *pset_name, MPICH_Info *info);
int (*MPICH_Session_init)(MPICH_Info info, MPICH_Errhandler errhandler, MPICH_Session *session);
int (*MPICH_Unpublish_name)(const char *service_name, MPICH_Info info, const char *port_name);

#endif

#ifndef OMPI_H
#define OMPI_H

typedef void * OMPI_Comm;
typedef void * OMPI_Datatype;
typedef void * OMPI_Errhandler;
typedef void * OMPI_File;
typedef void * OMPI_Group;
typedef void * OMPI_Info;
typedef void * OMPI_Message;
typedef void * OMPI_Op;
typedef void * OMPI_Request;
typedef void * OMPI_Session;
typedef void * OMPI_Win;

typedef struct __OMPI_Status__
{
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    int _cancelled;
    size_t _ucount;
}
OMPI_Status;

// TODO these may be configurable...
typedef ptrdiff_t OMPI_Aint;
typedef long long OMPI_Count;
typedef long long OMPI_Offset;

// A.1.3 Prototype Definitions
typedef void OMPI_User_function(void *invec, void *inoutvec, int *len, OMPI_Datatype *datatype);
typedef void OMPI_User_function_c(void *invec, void *inoutvec, OMPI_Count *len, OMPI_Datatype *datatype);
typedef int OMPI_Comm_copy_attr_function(OMPI_Comm oldcomm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int OMPI_Comm_delete_attr_function(OMPI_Comm comm, int comm_keyval, void *attribute_val, void *extra_state);
typedef int OMPI_Win_copy_attr_function(OMPI_Win oldwin, int win_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int OMPI_Win_delete_attr_function(OMPI_Win win, int win_keyval, void *attribute_val, void *extra_state);
typedef int OMPI_Type_copy_attr_function(OMPI_Datatype oldtype, int type_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int OMPI_Type_delete_attr_function(OMPI_Datatype datatype, int type_keyval, void *attribute_val, void *extra_state);
typedef void OMPI_Comm_errhandler_function(OMPI_Comm *comm, int *error_code, ...);
typedef void OMPI_Win_errhandler_function(OMPI_Win *win, int *error_code, ...);
typedef void OMPI_File_errhandler_function(OMPI_File *file, int *error_code, ...);
typedef void OMPI_Session_errhandler_function(OMPI_Session *session, int *error_code, ...);
typedef int OMPI_Grequest_query_function(void *extra_state, OMPI_Status *status);
typedef int OMPI_Grequest_free_function(void *extra_state);
typedef int OMPI_Grequest_cancel_function(void *extra_state, int complete);
typedef int OMPI_Datarep_extent_function(OMPI_Datatype datatype, OMPI_Aint *extent, void *extra_state);
typedef int OMPI_Datarep_conversion_function(void *userbuf, OMPI_Datatype datatype, int count, void *filebuf, OMPI_Offset position, void *extra_state);
typedef int OMPI_Datarep_conversion_function_c(void *userbuf, OMPI_Datatype datatype, OMPI_Count count, void *filebuf, OMPI_Offset position, void *extra_state);
#if 0
typedef void OMPI_T_event_cb_function(OMPI_T_event_instance event_instance, OMPI_T_event_registration event_registration, OMPI_T_cb_safety cb_safety, void *user_data);
typedef void OMPI_T_event_free_cb_function(OMPI_T_event_registration event_registration, OMPI_T_cb_safety cb_safety, void *user_data);
typedef void OMPI_T_event_dropped_cb_function(OMPI_Count count, OMPI_T_event_registration event_registration, int source_index, OMPI_T_cb_safety cb_safety, void *user_data);
#endif

// VIM tip:
// s/int OMPI_\(.*\)(\(.*\));/int (*OMPI_\1)(\2);

// A.3.7 OMPI Environmental Management C Bindings
int (*OMPI_Add_error_class)(int *errorclass);
int (*OMPI_Add_error_code)(int errorclass, int *errorcode);
int (*OMPI_Add_error_string)(int errorcode, const char *string);
int (*OMPI_Alloc_mem)(OMPI_Aint size, OMPI_Info info, void *baseptr);
int (*OMPI_Comm_call_errhandler)(OMPI_Comm comm, int errorcode);
int (*OMPI_Comm_create_errhandler)(OMPI_Comm_errhandler_function *comm_errhandler_fn, OMPI_Errhandler *errhandler);
int (*OMPI_Comm_get_errhandler)(OMPI_Comm comm, OMPI_Errhandler *errhandler);
int (*OMPI_Comm_set_errhandler)(OMPI_Comm comm, OMPI_Errhandler errhandler);
int (*OMPI_Errhandler_free)(OMPI_Errhandler *errhandler);
int (*OMPI_Error_class)(int errorcode, int *errorclass);
int (*OMPI_Error_string)(int errorcode, char *string, int *resultlen);
int (*OMPI_File_call_errhandler)(OMPI_File fh, int errorcode);
int (*OMPI_File_create_errhandler)(OMPI_File_errhandler_function *file_errhandler_fn, OMPI_Errhandler *errhandler);
int (*OMPI_File_get_errhandler)(OMPI_File file, OMPI_Errhandler *errhandler);
int (*OMPI_File_set_errhandler)(OMPI_File file, OMPI_Errhandler errhandler);
int (*OMPI_Free_mem)(void *base);
int (*OMPI_Session_call_errhandler)(OMPI_Session session, int errorcode);
int (*OMPI_Session_create_errhandler)(OMPI_Session_errhandler_function *session_errhandler_fn, OMPI_Errhandler *errhandler);
int (*OMPI_Session_get_errhandler)(OMPI_Session session, OMPI_Errhandler *errhandler);
int (*OMPI_Session_set_errhandler)(OMPI_Session session, OMPI_Errhandler errhandler);
int (*OMPI_Win_call_errhandler)(OMPI_Win win, int errorcode);
int (*OMPI_Win_create_errhandler)(OMPI_Win_errhandler_function *win_errhandler_fn, OMPI_Errhandler *errhandler);
int (*OMPI_Win_get_errhandler)(OMPI_Win win, OMPI_Errhandler *errhandler);
int (*OMPI_Win_set_errhandler)(OMPI_Win win, OMPI_Errhandler errhandler);
int (*OMPI_Info_create)(OMPI_Info *info);

// technically, these are not required to be symbols, but we know they are.
// we can work around the theoretical problem if necessary.
double (*OMPI_Wtime)(void);
double (*OMPI_Wtick)(void);

// A.3.9 Process Creation and Management C Bindings
int (*OMPI_Close_port)(const char *port_name);
int (*OMPI_Comm_disconnect)(OMPI_Comm *comm);
int (*OMPI_Info_dup)(OMPI_Info info, OMPI_Info *newinfo);
int (*OMPI_Info_free)(OMPI_Info *info);
int (*OMPI_Info_get_nkeys)(OMPI_Info info, int *nkeys);
int (*OMPI_Info_get_nthkey)(OMPI_Info info, int n, char *key);
int (*OMPI_Info_get_string)(OMPI_Info info, const char *key, int *buflen, char *value, int *flag);
int (*OMPI_Info_set)(OMPI_Info info, const char *key, const char *value);
int (*OMPI_Abort)(OMPI_Comm comm, int errorcode);
int (*OMPI_Comm_accept)(const char *port_name, OMPI_Info info, int root, OMPI_Comm comm, OMPI_Comm *newcomm);
int (*OMPI_Comm_connect)(const char *port_name, OMPI_Info info, int root, OMPI_Comm comm, OMPI_Comm *newcomm);
int (*OMPI_Comm_get_parent)(OMPI_Comm *parent);
int (*OMPI_Comm_join)(int fd, OMPI_Comm *intercomm);
int (*OMPI_Comm_spawn)(const char *command, char *argv[], int maxprocs, OMPI_Info info, int root, OMPI_Comm comm, OMPI_Comm *intercomm, int array_of_errcodes[]);
int (*OMPI_Comm_spawn_multiple)(int count, char *array_of_commands[], char **array_of_argv[], const int array_of_maxprocs[], const OMPI_Info array_of_info[], int root, OMPI_Comm comm, OMPI_Comm *intercomm, int array_of_errcodes[]);
int (*OMPI_Lookup_name)(const char *service_name, OMPI_Info info, char *port_name);
int (*OMPI_Open_port)(OMPI_Info info, char *port_name);
int (*OMPI_Publish_name)(const char *service_name, OMPI_Info info, const char *port_name);
int (*OMPI_Session_finalize)(OMPI_Session *session);
int (*OMPI_Session_get_nth_pset)(OMPI_Session session, OMPI_Info info, int n, int *pset_len, char *pset_name);
int (*OMPI_Session_get_info)(OMPI_Session session, OMPI_Info *info_used);
int (*OMPI_Session_get_num_psets)(OMPI_Session session, OMPI_Info info, int *npset_names);
int (*OMPI_Session_get_pset_info)(OMPI_Session session, const char *pset_name, OMPI_Info *info);
int (*OMPI_Session_init)(OMPI_Info info, OMPI_Errhandler errhandler, OMPI_Session *session);
int (*OMPI_Unpublish_name)(const char *service_name, OMPI_Info info, const char *port_name);

#endif

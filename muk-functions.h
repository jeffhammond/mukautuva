#ifndef MUK_FUNCTIONS_H
#define MUK_FUNCTIONS_H

// A.3.7 MUK Environmental Management C Bindings
int (*MUK_Add_error_class)(int *errorclass);
int (*MUK_Add_error_code)(int errorclass, int *errorcode);
int (*MUK_Add_error_string)(int errorcode, const char *string);
int (*MUK_Alloc_mem)(MUK_Aint size, MUK_Info info, void *baseptr);
int (*MUK_Comm_call_errhandler)(MUK_Comm comm, int errorcode);
int (*MUK_Comm_create_errhandler)(MUK_Comm_errhandler_function *comm_errhandler_fn, MUK_Errhandler *errhandler);
int (*MUK_Comm_get_errhandler)(MUK_Comm comm, MUK_Errhandler *errhandler);
int (*MUK_Comm_set_errhandler)(MUK_Comm comm, MUK_Errhandler errhandler);
int (*MUK_Errhandler_free)(MUK_Errhandler *errhandler);
int (*MUK_Error_class)(int errorcode, int *errorclass);
int (*MUK_Error_string)(int errorcode, char *string, int *resultlen);
int (*MUK_File_call_errhandler)(MUK_File fh, int errorcode);
int (*MUK_File_create_errhandler)(MUK_File_errhandler_function *file_errhandler_fn, MUK_Errhandler *errhandler);
int (*MUK_File_get_errhandler)(MUK_File file, MUK_Errhandler *errhandler);
int (*MUK_File_set_errhandler)(MUK_File file, MUK_Errhandler errhandler);
int (*MUK_Free_mem)(void *base);
int (*MUK_Session_call_errhandler)(MUK_Session session, int errorcode);
int (*MUK_Session_create_errhandler)(MUK_Session_errhandler_function *session_errhandler_fn, MUK_Errhandler *errhandler);
int (*MUK_Session_get_errhandler)(MUK_Session session, MUK_Errhandler *errhandler);
int (*MUK_Session_set_errhandler)(MUK_Session session, MUK_Errhandler errhandler);
int (*MUK_Win_call_errhandler)(MUK_Win win, int errorcode);
int (*MUK_Win_create_errhandler)(MUK_Win_errhandler_function *win_errhandler_fn, MUK_Errhandler *errhandler);
int (*MUK_Win_get_errhandler)(MUK_Win win, MUK_Errhandler *errhandler);
int (*MUK_Win_set_errhandler)(MUK_Win win, MUK_Errhandler errhandler);
int (*MUK_Info_create)(MUK_Info *info);

// technically, these are not required to be symbols, but we know they are.
// we can work around the theoretical problem if necessary.
double (*MUK_Wtime)(void);
double (*MUK_Wtick)(void);

// A.3.9 Process Creation and Management C Bindings
int (*MUK_Close_port)(const char *port_name);
int (*MUK_Comm_disconnect)(MUK_Comm *comm);
int (*MUK_Info_dup)(MUK_Info info, MUK_Info *newinfo);
int (*MUK_Info_free)(MUK_Info *info);
int (*MUK_Info_get_nkeys)(MUK_Info info, int *nkeys);
int (*MUK_Info_get_nthkey)(MUK_Info info, int n, char *key);
int (*MUK_Info_get_string)(MUK_Info info, const char *key, int *buflen, char *value, int *flag);
int (*MUK_Info_set)(MUK_Info info, const char *key, const char *value);
int (*MUK_Abort)(MUK_Comm comm, int errorcode);
int (*MUK_Comm_accept)(const char *port_name, MUK_Info info, int root, MUK_Comm comm, MUK_Comm *newcomm);
int (*MUK_Comm_connect)(const char *port_name, MUK_Info info, int root, MUK_Comm comm, MUK_Comm *newcomm);
int (*MUK_Comm_get_parent)(MUK_Comm *parent);
int (*MUK_Comm_join)(int fd, MUK_Comm *intercomm);
int (*MUK_Comm_spawn)(const char *command, char *argv[], int maxprocs, MUK_Info info, int root, MUK_Comm comm, MUK_Comm *intercomm, int array_of_errcodes[]);
int (*MUK_Comm_spawn_multiple)(int count, char *array_of_commands[], char **array_of_argv[], const int array_of_maxprocs[], const MUK_Info array_of_info[], int root, MUK_Comm comm, MUK_Comm *intercomm, int array_of_errcodes[]);
int (*MUK_Lookup_name)(const char *service_name, MUK_Info info, char *port_name);
int (*MUK_Open_port)(MUK_Info info, char *port_name);
int (*MUK_Publish_name)(const char *service_name, MUK_Info info, const char *port_name);
int (*MUK_Session_finalize)(MUK_Session *session);
int (*MUK_Session_get_nth_pset)(MUK_Session session, MUK_Info info, int n, int *pset_len, char *pset_name);
int (*MUK_Session_get_info)(MUK_Session session, MUK_Info *info_used);
int (*MUK_Session_get_num_psets)(MUK_Session session, MUK_Info info, int *npset_names);
int (*MUK_Session_get_pset_info)(MUK_Session session, const char *pset_name, MUK_Info *info);
int (*MUK_Session_init)(MUK_Info info, MUK_Errhandler errhandler, MUK_Session *session);
int (*MUK_Unpublish_name)(const char *service_name, MUK_Info info, const char *port_name);

#endif

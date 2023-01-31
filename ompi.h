#ifndef OMPI_H
#define OMPI_H

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
int (*OMPI_Get_library_version)(char *version, int *resultlen);
int (*OMPI_Get_processor_name)(char *name, int *resultlen);
int (*OMPI_Get_version)(int *version, int *subversion);
int (*OMPI_Session_call_errhandler)(OMPI_Session session, int errorcode);
int (*OMPI_Session_create_errhandler)(OMPI_Session_errhandler_function *session_errhandler_fn, OMPI_Errhandler *errhandler);
int (*OMPI_Session_get_errhandler)(OMPI_Session session, OMPI_Errhandler *errhandler);
int (*OMPI_Session_set_errhandler)(OMPI_Session session, OMPI_Errhandler errhandler);
int (*OMPI_Win_call_errhandler)(OMPI_Win win, int errorcode);
int (*OMPI_Win_create_errhandler)(OMPI_Win_errhandler_function *win_errhandler_fn, OMPI_Errhandler *errhandler);
int (*OMPI_Win_get_errhandler)(OMPI_Win win, OMPI_Errhandler *errhandler);
int (*OMPI_Win_set_errhandler)(OMPI_Win win, OMPI_Errhandler errhandler);
int (*OMPI_Info_create)(OMPI_Info *info);

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
int (*OMPI_Finalize)(void);
int (*OMPI_Finalized)(int *flag);
int (*OMPI_Init)(int *argc, char ***argv);
int (*OMPI_Init_thread)(int *argc, char ***argv, int required, int *provided);
int (*OMPI_Initialized)(int *flag);
int (*OMPI_Is_thread_main)(int *flag);
int (*OMPI_Lookup_name)(const char *service_name, OMPI_Info info, char *port_name);
int (*OMPI_Open_port)(OMPI_Info info, char *port_name);
int (*OMPI_Publish_name)(const char *service_name, OMPI_Info info, const char *port_name);
int (*OMPI_Query_thread)(int *provided);
int (*OMPI_Session_finalize)(OMPI_Session *session);
int (*OMPI_Session_get_nth_pset)(OMPI_Session session, OMPI_Info info, int n, int *pset_len, char *pset_name);
int (*OMPI_Session_get_info)(OMPI_Session session, OMPI_Info *info_used);
int (*OMPI_Session_get_num_psets)(OMPI_Session session, OMPI_Info info, int *npset_names);
int (*OMPI_Session_get_pset_info)(OMPI_Session session, const char *pset_name, OMPI_Info *info);
int (*OMPI_Session_init)(OMPI_Info info, OMPI_Errhandler errhandler, OMPI_Session *session);
int (*OMPI_Unpublish_name)(const char *service_name, OMPI_Info info, const char *port_name);

#endif

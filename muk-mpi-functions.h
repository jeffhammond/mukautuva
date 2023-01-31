#ifndef MUK_MPI_FUNCTIONS_H
#define MUK_MPI_FUNCTIONS_H

#if defined(USE_MPI_NAMESPACE)
    #define NIMI_SUB(text) MPI ## _ ## text
    #define NIMI_FSUB(text) MPI ## _ ## text
#elif defined(USE_MUK_NAMESPACE)
    #define NIMI_SUB(text) MUK ## _ ## text
    #if defined(MAKE_INTERFACE)
        #define NIMI_FSUB(text) MUK ## _ ## text
    #elif defined(MAKE_FUNCTION_POINTERS)
        #define NIMI_FSUB(text) (*MUK ## _ ## text)
    #endif
#else
    #error Namespace substitution problem
#endif

// A.3.7 Environmental Management C Bindings
int NIMI_FSUB(Add_error_class)(int *errorclass);
int NIMI_FSUB(Add_error_code)(int errorclass, int *errorcode);
int NIMI_FSUB(Add_error_string)(int errorcode, const char *string);
int NIMI_FSUB(Alloc_mem)(NIMI_SUB(Aint) size, NIMI_SUB(Info) info, void *baseptr);
int NIMI_FSUB(Comm_call_errhandler)(NIMI_SUB(Comm) comm, int errorcode);
int NIMI_FSUB(Comm_create_errhandler)(NIMI_SUB(Comm_errhandler_function) *comm_errhandler_fn, NIMI_SUB(Errhandler) *errhandler);
int NIMI_FSUB(Comm_get_errhandler)(NIMI_SUB(Comm) comm, NIMI_SUB(Errhandler) *errhandler);
int NIMI_FSUB(Comm_set_errhandler)(NIMI_SUB(Comm) comm, NIMI_SUB(Errhandler) errhandler);
int NIMI_FSUB(Errhandler_free)(NIMI_SUB(Errhandler) *errhandler);
int NIMI_FSUB(Error_class)(int errorcode, int *errorclass);
int NIMI_FSUB(Error_string)(int errorcode, char *string, int *resultlen);
int NIMI_FSUB(File_call_errhandler)(NIMI_SUB(File) fh, int errorcode);
int NIMI_FSUB(File_create_errhandler)(NIMI_SUB(File_errhandler_function) *file_errhandler_fn, NIMI_SUB(Errhandler) *errhandler);
int NIMI_FSUB(File_get_errhandler)(NIMI_SUB(File) file, NIMI_SUB(Errhandler) *errhandler);
int NIMI_FSUB(File_set_errhandler)(NIMI_SUB(File) file, NIMI_SUB(Errhandler) errhandler);
int NIMI_FSUB(Free_mem)(void *base);
int NIMI_FSUB(Get_library_version)(char *version, int *resultlen);
int NIMI_FSUB(Get_processor_name)(char *name, int *resultlen);
int NIMI_FSUB(Get_version)(int *version, int *subversion);
int NIMI_FSUB(Session_call_errhandler)(NIMI_SUB(Session) session, int errorcode);
int NIMI_FSUB(Session_create_errhandler)(NIMI_SUB(Session_errhandler_function) *session_errhandler_fn, NIMI_SUB(Errhandler) *errhandler);
int NIMI_FSUB(Session_get_errhandler)(NIMI_SUB(Session) session, NIMI_SUB(Errhandler) *errhandler);
int NIMI_FSUB(Session_set_errhandler)(NIMI_SUB(Session) session, NIMI_SUB(Errhandler) errhandler);
int NIMI_FSUB(Win_call_errhandler)(NIMI_SUB(Win) win, int errorcode);
int NIMI_FSUB(Win_create_errhandler)(NIMI_SUB(Win_errhandler_function) *win_errhandler_fn, NIMI_SUB(Errhandler) *errhandler);
int NIMI_FSUB(Win_get_errhandler)(NIMI_SUB(Win) win, NIMI_SUB(Errhandler) *errhandler);
int NIMI_FSUB(Win_set_errhandler)(NIMI_SUB(Win) win, NIMI_SUB(Errhandler) errhandler);
int NIMI_FSUB(Info_create)(NIMI_SUB(Info) *info);
double NIMI_SUB(Wtime)(void);
double NIMI_SUB(Wtick)(void);

// A.3.9 Process Creation and Management C Bindings
int NIMI_FSUB(Close_port)(const char *port_name);
int NIMI_FSUB(Comm_disconnect)(NIMI_SUB(Comm) *comm);
int NIMI_FSUB(Info_dup)(NIMI_SUB(Info) info, NIMI_SUB(Info) *newinfo);
int NIMI_FSUB(Info_free)(NIMI_SUB(Info) *info);
int NIMI_FSUB(Info_get_nkeys)(NIMI_SUB(Info) info, int *nkeys);
int NIMI_FSUB(Info_get_nthkey)(NIMI_SUB(Info) info, int n, char *key);
int NIMI_FSUB(Info_get_string)(NIMI_SUB(Info) info, const char *key, int *buflen, char *value, int *flag);
int NIMI_FSUB(Info_set)(NIMI_SUB(Info) info, const char *key, const char *value);
int NIMI_FSUB(Abort)(NIMI_SUB(Comm) comm, int errorcode);
int NIMI_FSUB(Comm_accept)(const char *port_name, NIMI_SUB(Info) info, int root, NIMI_SUB(Comm) comm, NIMI_SUB(Comm) *newcomm);
int NIMI_FSUB(Comm_connect)(const char *port_name, NIMI_SUB(Info) info, int root, NIMI_SUB(Comm) comm, NIMI_SUB(Comm) *newcomm);
int NIMI_FSUB(Comm_get_parent)(NIMI_SUB(Comm) *parent);
int NIMI_FSUB(Comm_join)(int fd, NIMI_SUB(Comm) *intercomm);
int NIMI_FSUB(Comm_spawn)(const char *command, char *argv[], int maxprocs, NIMI_SUB(Info) info, int root, NIMI_SUB(Comm) comm, NIMI_SUB(Comm) *intercomm, int array_of_errcodes[]);
int NIMI_FSUB(Comm_spawn_multiple)(int count, char *array_of_commands[], char **array_of_argv[], const int array_of_maxprocs[], const NIMI_SUB(Info) array_of_info[], int root, NIMI_SUB(Comm) comm, NIMI_SUB(Comm) *intercomm, int array_of_errcodes[]);
int NIMI_FSUB(Finalize)(void);
int NIMI_FSUB(Finalized)(int *flag);
int NIMI_FSUB(Init)(int *argc, char ***argv);
int NIMI_FSUB(Init_thread)(int *argc, char ***argv, int required, int *provided);
int NIMI_FSUB(Initialized)(int *flag);
int NIMI_FSUB(Is_thread_main)(int *flag);
int NIMI_FSUB(Lookup_name)(const char *service_name, NIMI_SUB(Info) info, char *port_name);
int NIMI_FSUB(Open_port)(NIMI_SUB(Info) info, char *port_name);
int NIMI_FSUB(Publish_name)(const char *service_name, NIMI_SUB(Info) info, const char *port_name);
int NIMI_FSUB(Query_thread)(int *provided);
int NIMI_FSUB(Session_finalize)(NIMI_SUB(Session) *session);
int NIMI_FSUB(Session_get_nth_pset)(NIMI_SUB(Session) session, NIMI_SUB(Info) info, int n, int *pset_len, char *pset_name);
int NIMI_FSUB(Session_get_info)(NIMI_SUB(Session) session, NIMI_SUB(Info) *info_used);
int NIMI_FSUB(Session_get_num_psets)(NIMI_SUB(Session) session, NIMI_SUB(Info) info, int *npset_names);
int NIMI_FSUB(Session_get_pset_info)(NIMI_SUB(Session) session, const char *pset_name, NIMI_SUB(Info) *info);
int NIMI_FSUB(Session_init)(NIMI_SUB(Info) info, NIMI_SUB(Errhandler) errhandler, NIMI_SUB(Session) *session);
int NIMI_FSUB(Unpublish_name)(const char *service_name, NIMI_SUB(Info) info, const char *port_name);

#endif

#undef NIMI_SUB
#undef NIMI_FSUB

#if defined(USE_MPI_NAMESPACE)
    #define NIMI_SUB(text) MPI ## _ ## text
    #define NIMI_FSUB(text) int MPI ## _ ## text
#elif defined(USE_MUK_NAMESPACE)
    #define NIMI_SUB(text) MUK ## _ ## text
    #if defined(MAKE_INTERFACE)
        #define NIMI_FSUB(text) int MUK ## _ ## text
    #elif defined(MAKE_FUNCTION_POINTERS)
        #define NIMI_FSUB(text) int (*MUK ## _ ## text)
    #elif defined(MAKE_FUNCTION_POINTERS_EXTERN)
        #define NIMI_FSUB(text) extern int (*MUK ## _ ## text)
    #endif
#else
    #error Namespace substitution problem
#endif

//double NIMI_FSUB(Wtime)(void);
//double NIMI_FSUB(Wtick)(void);

// A.3.5 Groups, Contexts, Communicators, and Caching
NIMI_FSUB(Comm_compare)(NIMI_SUB(Comm) comm1, NIMI_SUB(Comm) comm2, int *result);
NIMI_FSUB(Comm_create)(NIMI_SUB(Comm) comm, NIMI_SUB(Group) group, NIMI_SUB(Comm) *newcomm);
NIMI_FSUB(Comm_create_from_group)(NIMI_SUB(Group) group, const char *stringtag, NIMI_SUB(Info) info, NIMI_SUB(Errhandler) errhandler, NIMI_SUB(Comm) *newcomm);
NIMI_FSUB(Comm_create_group)(NIMI_SUB(Comm) comm, NIMI_SUB(Group) group, int tag, NIMI_SUB(Comm) *newcomm);
NIMI_FSUB(Comm_create_keyval)(NIMI_SUB(Comm_copy_attr_function) *comm_copy_attr_fn, NIMI_SUB(Comm_delete_attr_function) *comm_delete_attr_fn, int *comm_keyval, void *extra_state);
NIMI_FSUB(Comm_delete_attr)(NIMI_SUB(Comm) comm, int comm_keyval);
NIMI_FSUB(Comm_dup)(NIMI_SUB(Comm) comm, NIMI_SUB(Comm) *newcomm);
NIMI_FSUB(COMM_DUP_FN)(NIMI_SUB(Comm) oldcomm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
NIMI_FSUB(Comm_dup_with_info)(NIMI_SUB(Comm) comm, NIMI_SUB(Info) info, NIMI_SUB(Comm) *newcomm);
NIMI_FSUB(Comm_free)(NIMI_SUB(Comm) *comm);
NIMI_FSUB(Comm_free_keyval)(int *comm_keyval);
NIMI_FSUB(Comm_get_info)(NIMI_SUB(Comm) comm, NIMI_SUB(Info) *info_used);
NIMI_FSUB(Comm_get_attr)(NIMI_SUB(Comm) comm, int comm_keyval, void *attribute_val, int *flag);
NIMI_FSUB(Comm_get_name)(NIMI_SUB(Comm) comm, char *comm_name, int *resultlen);
NIMI_FSUB(Comm_size)(NIMI_SUB(Comm) comm, int *size);
NIMI_FSUB(Comm_split)(NIMI_SUB(Comm) comm, int color, int key, NIMI_SUB(Comm) *newcomm);
NIMI_FSUB(Comm_split_type)(NIMI_SUB(Comm) comm, int split_type, int key, NIMI_SUB(Info) info, NIMI_SUB(Comm) *newcomm);
NIMI_FSUB(Comm_group)(NIMI_SUB(Comm) comm, NIMI_SUB(Group) *group);
NIMI_FSUB(Comm_idup)(NIMI_SUB(Comm) comm, NIMI_SUB(Comm) *newcomm, NIMI_SUB(Request) *request);
NIMI_FSUB(Comm_idup_with_info)(NIMI_SUB(Comm) comm, NIMI_SUB(Info) info, NIMI_SUB(Comm) *newcomm, NIMI_SUB(Request) *request);
NIMI_FSUB(COMM_NULL_COPY_FN)(NIMI_SUB(Comm) oldcomm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
NIMI_FSUB(COMM_NULL_DELETE_FN)(NIMI_SUB(Comm) comm, int comm_keyval, void *attribute_val, void *extra_state);
NIMI_FSUB(Comm_rank)(NIMI_SUB(Comm) comm, int *rank);
NIMI_FSUB(Comm_remote_group)(NIMI_SUB(Comm) comm, NIMI_SUB(Group) *group);
NIMI_FSUB(Comm_remote_size)(NIMI_SUB(Comm) comm, int *size);
NIMI_FSUB(Comm_set_attr)(NIMI_SUB(Comm) comm, int comm_keyval, void *attribute_val);
NIMI_FSUB(Comm_set_info)(NIMI_SUB(Comm) comm, NIMI_SUB(Info) info);
NIMI_FSUB(Comm_set_name)(NIMI_SUB(Comm) comm, const char *comm_name);
NIMI_FSUB(Comm_test_inter)(NIMI_SUB(Comm) comm, int *flag);
NIMI_FSUB(Group_compare)(NIMI_SUB(Group) group1, NIMI_SUB(Group) group2, int *result);
NIMI_FSUB(Group_difference)(NIMI_SUB(Group) group1, NIMI_SUB(Group) group2, NIMI_SUB(Group) *newgroup);
NIMI_FSUB(Group_excl)(NIMI_SUB(Group) group, int n, const int ranks[], NIMI_SUB(Group) *newgroup);
NIMI_FSUB(Group_free)(NIMI_SUB(Group) *group);
NIMI_FSUB(Group_from_session_pset)(NIMI_SUB(Session) session, const char *pset_name, NIMI_SUB(Group) *newgroup);
NIMI_FSUB(Group_incl)(NIMI_SUB(Group) group, int n, const int ranks[], NIMI_SUB(Group) *newgroup);
NIMI_FSUB(Group_intersection)(NIMI_SUB(Group) group1, NIMI_SUB(Group) group2, NIMI_SUB(Group) *newgroup);
NIMI_FSUB(Group_range_excl)(NIMI_SUB(Group) group, int n, int ranges[][3], NIMI_SUB(Group) *newgroup);
NIMI_FSUB(Group_range_incl)(NIMI_SUB(Group) group, int n, int ranges[][3], NIMI_SUB(Group) *newgroup);
NIMI_FSUB(Group_rank)(NIMI_SUB(Group) group, int *rank);
NIMI_FSUB(Group_size)(NIMI_SUB(Group) group, int *size);
NIMI_FSUB(Group_translate_ranks)(NIMI_SUB(Group) group1, int n, const int ranks1[], NIMI_SUB(Group) group2, int ranks2[]);
NIMI_FSUB(Group_union)(NIMI_SUB(Group) group1, NIMI_SUB(Group) group2, NIMI_SUB(Group) *newgroup);
NIMI_FSUB(Intercomm_create)(NIMI_SUB(Comm) local_comm, int local_leader, NIMI_SUB(Comm) peer_comm, int remote_leader, int tag, NIMI_SUB(Comm) *newintercomm);
NIMI_FSUB(Intercomm_create_from_groups)(NIMI_SUB(Group) local_group, int local_leader, NIMI_SUB(Group) remote_group, int remote_leader, const char *stringtag, NIMI_SUB(Info) info, NIMI_SUB(Errhandler) errhandler, NIMI_SUB(Comm) *newintercomm);
NIMI_FSUB(Intercomm_merge)(NIMI_SUB(Comm) intercomm, int high, NIMI_SUB(Comm) *newintracomm);

// A.3.7 Environmental Management C Bindings
NIMI_FSUB(Add_error_class)(int *errorclass);
NIMI_FSUB(Add_error_code)(int errorclass, int *errorcode);
NIMI_FSUB(Add_error_string)(int errorcode, const char *string);
NIMI_FSUB(Alloc_mem)(NIMI_SUB(Aint) size, NIMI_SUB(Info) info, void *baseptr);
NIMI_FSUB(Comm_call_errhandler)(NIMI_SUB(Comm) comm, int errorcode);
NIMI_FSUB(Comm_create_errhandler)(NIMI_SUB(Comm_errhandler_function) *comm_errhandler_fn, NIMI_SUB(Errhandler) *errhandler);
NIMI_FSUB(Comm_get_errhandler)(NIMI_SUB(Comm) comm, NIMI_SUB(Errhandler) *errhandler);
NIMI_FSUB(Comm_set_errhandler)(NIMI_SUB(Comm) comm, NIMI_SUB(Errhandler) errhandler);
NIMI_FSUB(Errhandler_free)(NIMI_SUB(Errhandler) *errhandler);
NIMI_FSUB(Error_class)(int errorcode, int *errorclass);
NIMI_FSUB(Error_string)(int errorcode, char *string, int *resultlen);
NIMI_FSUB(File_call_errhandler)(NIMI_SUB(File) fh, int errorcode);
NIMI_FSUB(File_create_errhandler)(NIMI_SUB(File_errhandler_function) *file_errhandler_fn, NIMI_SUB(Errhandler) *errhandler);
NIMI_FSUB(File_get_errhandler)(NIMI_SUB(File) file, NIMI_SUB(Errhandler) *errhandler);
NIMI_FSUB(File_set_errhandler)(NIMI_SUB(File) file, NIMI_SUB(Errhandler) errhandler);
NIMI_FSUB(Free_mem)(void *base);
NIMI_FSUB(Get_library_version)(char *version, int *resultlen);
NIMI_FSUB(Get_processor_name)(char *name, int *resultlen);
NIMI_FSUB(Get_version)(int *version, int *subversion);
NIMI_FSUB(Session_call_errhandler)(NIMI_SUB(Session) session, int errorcode);
NIMI_FSUB(Session_create_errhandler)(NIMI_SUB(Session_errhandler_function) *session_errhandler_fn, NIMI_SUB(Errhandler) *errhandler);
NIMI_FSUB(Session_get_errhandler)(NIMI_SUB(Session) session, NIMI_SUB(Errhandler) *errhandler);
NIMI_FSUB(Session_set_errhandler)(NIMI_SUB(Session) session, NIMI_SUB(Errhandler) errhandler);
NIMI_FSUB(Win_call_errhandler)(NIMI_SUB(Win) win, int errorcode);
NIMI_FSUB(Win_create_errhandler)(NIMI_SUB(Win_errhandler_function) *win_errhandler_fn, NIMI_SUB(Errhandler) *errhandler);
NIMI_FSUB(Win_get_errhandler)(NIMI_SUB(Win) win, NIMI_SUB(Errhandler) *errhandler);
NIMI_FSUB(Win_set_errhandler)(NIMI_SUB(Win) win, NIMI_SUB(Errhandler) errhandler);
NIMI_FSUB(Info_create)(NIMI_SUB(Info) *info);

// A.3.9 Process Creation and Management C Bindings
NIMI_FSUB(Close_port)(const char *port_name);
NIMI_FSUB(Comm_disconnect)(NIMI_SUB(Comm) *comm);
NIMI_FSUB(Info_dup)(NIMI_SUB(Info) info, NIMI_SUB(Info) *newinfo);
NIMI_FSUB(Info_free)(NIMI_SUB(Info) *info);
NIMI_FSUB(Info_get_nkeys)(NIMI_SUB(Info) info, int *nkeys);
NIMI_FSUB(Info_get_nthkey)(NIMI_SUB(Info) info, int n, char *key);
NIMI_FSUB(Info_get_string)(NIMI_SUB(Info) info, const char *key, int *buflen, char *value, int *flag);
NIMI_FSUB(Info_set)(NIMI_SUB(Info) info, const char *key, const char *value);
NIMI_FSUB(Abort)(NIMI_SUB(Comm) comm, int errorcode);
NIMI_FSUB(Comm_accept)(const char *port_name, NIMI_SUB(Info) info, int root, NIMI_SUB(Comm) comm, NIMI_SUB(Comm) *newcomm);
NIMI_FSUB(Comm_connect)(const char *port_name, NIMI_SUB(Info) info, int root, NIMI_SUB(Comm) comm, NIMI_SUB(Comm) *newcomm);
NIMI_FSUB(Comm_get_parent)(NIMI_SUB(Comm) *parent);
NIMI_FSUB(Comm_join)(int fd, NIMI_SUB(Comm) *intercomm);
NIMI_FSUB(Comm_spawn)(const char *command, char *argv[], int maxprocs, NIMI_SUB(Info) info, int root, NIMI_SUB(Comm) comm, NIMI_SUB(Comm) *intercomm, int array_of_errcodes[]);
NIMI_FSUB(Comm_spawn_multiple)(int count, char *array_of_commands[], char **array_of_argv[], const int array_of_maxprocs[], const NIMI_SUB(Info) array_of_info[], int root, NIMI_SUB(Comm) comm, NIMI_SUB(Comm) *intercomm, int array_of_errcodes[]);
NIMI_FSUB(Finalize)(void);
NIMI_FSUB(Finalized)(int *flag);
NIMI_FSUB(Init)(int *argc, char ***argv);
NIMI_FSUB(Init_thread)(int *argc, char ***argv, int required, int *provided);
NIMI_FSUB(Initialized)(int *flag);
NIMI_FSUB(Is_thread_main)(int *flag);
NIMI_FSUB(Lookup_name)(const char *service_name, NIMI_SUB(Info) info, char *port_name);
NIMI_FSUB(Open_port)(NIMI_SUB(Info) info, char *port_name);
NIMI_FSUB(Publish_name)(const char *service_name, NIMI_SUB(Info) info, const char *port_name);
NIMI_FSUB(Query_thread)(int *provided);
NIMI_FSUB(Session_finalize)(NIMI_SUB(Session) *session);
NIMI_FSUB(Session_get_nth_pset)(NIMI_SUB(Session) session, NIMI_SUB(Info) info, int n, int *pset_len, char *pset_name);
NIMI_FSUB(Session_get_info)(NIMI_SUB(Session) session, NIMI_SUB(Info) *info_used);
NIMI_FSUB(Session_get_num_psets)(NIMI_SUB(Session) session, NIMI_SUB(Info) info, int *npset_names);
NIMI_FSUB(Session_get_pset_info)(NIMI_SUB(Session) session, const char *pset_name, NIMI_SUB(Info) *info);
NIMI_FSUB(Session_init)(NIMI_SUB(Info) info, NIMI_SUB(Errhandler) errhandler, NIMI_SUB(Session) *session);
NIMI_FSUB(Unpublish_name)(const char *service_name, NIMI_SUB(Info) info, const char *port_name);

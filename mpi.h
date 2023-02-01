#include <stddef.h>

// basic typedefs
typedef ptrdiff_t MPI_Aint;
typedef ptrdiff_t MPI_Count;
typedef ptrdiff_t MPI_Offset;

// handle typedefs
typedef struct __MPI_Comm__ * MPI_Comm;
typedef struct __MPI_Datatype__ * MPI_Datatype;
typedef struct __MPI_Errhandler__ * MPI_Errhandler;
typedef struct __MPI_File__ * MPI_File;
typedef struct __MPI_Group__ * MPI_Group;
typedef struct __MPI_Info__ * MPI_Info;
typedef struct __MPI_Message__ * MPI_Message;
typedef struct __MPI_Op__ * MPI_Op;
typedef struct __MPI_Request__ * MPI_Request;
typedef struct __MPI_Session__ * MPI_Session;
typedef struct __MPI_Win__ * MPI_Win;

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
typedef void MPI_User_function(void *invec, void *inoutvec, int *len, MPI_Datatype *datatype);
typedef void MPI_User_function_c(void *invec, void *inoutvec, MPI_Count *len, MPI_Datatype *datatype);
typedef int MPI_Comm_copy_attr_function(MPI_Comm oldcomm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MPI_Comm_delete_attr_function(MPI_Comm comm, int comm_keyval, void *attribute_val, void *extra_state);
typedef int MPI_Win_copy_attr_function(MPI_Win oldwin, int win_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MPI_Win_delete_attr_function(MPI_Win win, int win_keyval, void *attribute_val, void *extra_state);
typedef int MPI_Type_copy_attr_function(MPI_Datatype oldtype, int type_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MPI_Type_delete_attr_function(MPI_Datatype datatype, int type_keyval, void *attribute_val, void *extra_state);
typedef void MPI_Comm_errhandler_function(MPI_Comm *comm, int *error_code, ...);
typedef void MPI_Win_errhandler_function(MPI_Win *win, int *error_code, ...);
typedef void MPI_File_errhandler_function(MPI_File *file, int *error_code, ...);
typedef void MPI_Session_errhandler_function(MPI_Session *session, int *error_code, ...);
typedef int MPI_Grequest_query_function(void *extra_state, MPI_Status *status);
typedef int MPI_Grequest_free_function(void *extra_state);
typedef int MPI_Grequest_cancel_function(void *extra_state, int complete);
typedef int MPI_Datarep_extent_function(MPI_Datatype datatype, MPI_Aint *extent, void *extra_state);
typedef int MPI_Datarep_conversion_function(void *userbuf, MPI_Datatype datatype, int count, void *filebuf, MPI_Offset position, void *extra_state);
typedef int MPI_Datarep_conversion_function_c(void *userbuf, MPI_Datatype datatype, MPI_Count count, void *filebuf, MPI_Offset position, void *extra_state);

// predefined handles

MPI_Request MPI_REQUEST_NULL;

MPI_Errhandler MPI_ERRHANDLER_NULL;

MPI_Info MPI_INFO_NULL;

MPI_Win MPI_WIN_NULL;

MPI_File MPI_FILE_NULL;

MPI_Comm MPI_COMM_NULL;
MPI_Comm MPI_COMM_WORLD;
MPI_Comm MPI_COMM_SELF;

MPI_Group MPI_GROUP_NULL;
MPI_Group MPI_GROUP_EMPTY;

MPI_Message MPI_MESSAGE_NULL;
MPI_Message MPI_MESSAGE_NO_PROC;

MPI_Op MPI_OP_NULL;
MPI_Op MPI_MAX;
MPI_Op MPI_MIN;
MPI_Op MPI_SUM;
MPI_Op MPI_PROD;
MPI_Op MPI_LAND;
MPI_Op MPI_BAND;
MPI_Op MPI_LOR;
MPI_Op MPI_BOR;
MPI_Op MPI_LXOR;
MPI_Op MPI_BXOR;
MPI_Op MPI_MAXLOC;
MPI_Op MPI_MINLOC;
MPI_Op MPI_REPLACE;
MPI_Op MPI_NO_OP;

MPI_Datatype MPI_DATATYPE_NULL;
MPI_Datatype MPI_BYTE;
MPI_Datatype MPI_PACKED;
MPI_Datatype MPI_CHAR;
MPI_Datatype MPI_SHORT;
MPI_Datatype MPI_INT;
MPI_Datatype MPI_LONG;
MPI_Datatype MPI_FLOAT;
MPI_Datatype MPI_DOUBLE;
MPI_Datatype MPI_LONG_DOUBLE;
MPI_Datatype MPI_UNSIGNED_CHAR;
MPI_Datatype MPI_SIGNED_CHAR;
MPI_Datatype MPI_UNSIGNED_SHORT;
MPI_Datatype MPI_UNSIGNED_LONG;
MPI_Datatype MPI_UNSIGNED;
MPI_Datatype MPI_FLOAT_INT;
MPI_Datatype MPI_DOUBLE_INT;
MPI_Datatype MPI_LONG_DOUBLE_INT;
MPI_Datatype MPI_LONG_INT;
MPI_Datatype MPI_SHORT_INT;
MPI_Datatype MPI_2INT;
MPI_Datatype MPI_WCHAR;
MPI_Datatype MPI_LONG_LONG_INT;
MPI_Datatype MPI_LONG_LONG;
MPI_Datatype MPI_UNSIGNED_LONG_LONG;
MPI_Datatype MPI_2COMPLEX;
MPI_Datatype MPI_2DOUBLE_COMPLEX;

// functions

double MPI_Wtime(void);
double MPI_Wtick(void);

int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result);
int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm);
int MPI_Comm_create_from_group(MPI_Group group, const char *stringtag, MPI_Info info, MPI_Errhandler errhandler, MPI_Comm *newcomm);
int MPI_Comm_create_group(MPI_Comm comm, MPI_Group group, int tag, MPI_Comm *newcomm);
int MPI_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state);
int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval);
int MPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm);
int MPI_COMM_DUP_FN(MPI_Comm oldcomm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
int MPI_Comm_dup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm);
int MPI_Comm_free(MPI_Comm *comm);
int MPI_Comm_free_keyval(int *comm_keyval);
int MPI_Comm_get_info(MPI_Comm comm, MPI_Info *info_used);
int MPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag);
int MPI_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen);
int MPI_Comm_size(MPI_Comm comm, int *size);
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm);
int MPI_Comm_split_type(MPI_Comm comm, int split_type, int key, MPI_Info info, MPI_Comm *newcomm);
int MPI_Comm_group(MPI_Comm comm, MPI_Group *group);
int MPI_Comm_idup(MPI_Comm comm, MPI_Comm *newcomm, MPI_Request *request);
int MPI_Comm_idup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm, MPI_Request *request);
int MPI_COMM_NULL_COPY_FN(MPI_Comm oldcomm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
int MPI_COMM_NULL_DELETE_FN(MPI_Comm comm, int comm_keyval, void *attribute_val, void *extra_state);
int MPI_Comm_rank(MPI_Comm comm, int *rank);
int MPI_Comm_remote_group(MPI_Comm comm, MPI_Group *group);
int MPI_Comm_remote_size(MPI_Comm comm, int *size);
int MPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val);
int MPI_Comm_set_info(MPI_Comm comm, MPI_Info info);
int MPI_Comm_set_name(MPI_Comm comm, const char *comm_name);
int MPI_Comm_test_inter(MPI_Comm comm, int *flag);
int MPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result);
int MPI_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
int MPI_Group_excl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup);
int MPI_Group_free(MPI_Group *group);
int MPI_Group_from_session_pset(MPI_Session session, const char *pset_name, MPI_Group *newgroup);
int MPI_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup);
int MPI_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
int MPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup);
int MPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup);
int MPI_Group_rank(MPI_Group group, int *rank);
int MPI_Group_size(MPI_Group group, int *size);
int MPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[]);
int MPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
int MPI_Intercomm_create(MPI_Comm local_comm, int local_leader, MPI_Comm peer_comm, int remote_leader, int tag, MPI_Comm *newintercomm);
int MPI_Intercomm_create_from_groups(MPI_Group local_group, int local_leader, MPI_Group remote_group, int remote_leader, const char *stringtag, MPI_Info info, MPI_Errhandler errhandler, MPI_Comm *newintercomm);
int MPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintracomm);


int MPI_Add_error_class(int *errorclass);
int MPI_Add_error_code(int errorclass, int *errorcode);
int MPI_Add_error_string(int errorcode, const char *string);
int MPI_Alloc_mem(MPI_Aint size, MPI_Info info, void *baseptr);
int MPI_Comm_call_errhandler(MPI_Comm comm, int errorcode);
int MPI_Comm_create_errhandler(MPI_Comm_errhandler_function *comm_errhandler_fn, MPI_Errhandler *errhandler);
int MPI_Comm_get_errhandler(MPI_Comm comm, MPI_Errhandler *errhandler);
int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler);
int MPI_Errhandler_free(MPI_Errhandler *errhandler);
int MPI_Error_class(int errorcode, int *errorclass);
int MPI_Error_string(int errorcode, char *string, int *resultlen);
int MPI_File_call_errhandler(MPI_File fh, int errorcode);
int MPI_File_create_errhandler(MPI_File_errhandler_function *file_errhandler_fn, MPI_Errhandler *errhandler);
int MPI_File_get_errhandler(MPI_File file, MPI_Errhandler *errhandler);
int MPI_File_set_errhandler(MPI_File file, MPI_Errhandler errhandler);
int MPI_Free_mem(void *base);
int MPI_Get_library_version(char *version, int *resultlen);
int MPI_Get_processor_name(char *name, int *resultlen);
int MPI_Get_version(int *version, int *subversion);
int MPI_Session_call_errhandler(MPI_Session session, int errorcode);
int MPI_Session_create_errhandler(MPI_Session_errhandler_function *session_errhandler_fn, MPI_Errhandler *errhandler);
int MPI_Session_get_errhandler(MPI_Session session, MPI_Errhandler *errhandler);
int MPI_Session_set_errhandler(MPI_Session session, MPI_Errhandler errhandler);
int MPI_Win_call_errhandler(MPI_Win win, int errorcode);
int MPI_Win_create_errhandler(MPI_Win_errhandler_function *win_errhandler_fn, MPI_Errhandler *errhandler);
int MPI_Win_get_errhandler(MPI_Win win, MPI_Errhandler *errhandler);
int MPI_Win_set_errhandler(MPI_Win win, MPI_Errhandler errhandler);
int MPI_Info_create(MPI_Info *info);


int MPI_Close_port(const char *port_name);
int MPI_Comm_disconnect(MPI_Comm *comm);
int MPI_Info_dup(MPI_Info info, MPI_Info *newinfo);
int MPI_Info_free(MPI_Info *info);
int MPI_Info_get_nkeys(MPI_Info info, int *nkeys);
int MPI_Info_get_nthkey(MPI_Info info, int n, char *key);
int MPI_Info_get_string(MPI_Info info, const char *key, int *buflen, char *value, int *flag);
int MPI_Info_set(MPI_Info info, const char *key, const char *value);
int MPI_Abort(MPI_Comm comm, int errorcode);
int MPI_Comm_accept(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm);
int MPI_Comm_connect(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm);
int MPI_Comm_get_parent(MPI_Comm *parent);
int MPI_Comm_join(int fd, MPI_Comm *intercomm);
int MPI_Comm_spawn(const char *command, char *argv[], int maxprocs, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *intercomm, int array_of_errcodes[]);
int MPI_Comm_spawn_multiple(int count, char *array_of_commands[], char **array_of_argv[], const int array_of_maxprocs[], const MPI_Info array_of_info[], int root, MPI_Comm comm, MPI_Comm *intercomm, int array_of_errcodes[]);
int MPI_Finalize(void);
int MPI_Finalized(int *flag);
int MPI_Init(int *argc, char ***argv);
int MPI_Init_thread(int *argc, char ***argv, int required, int *provided);
int MPI_Initialized(int *flag);
int MPI_Is_thread_main(int *flag);
int MPI_Lookup_name(const char *service_name, MPI_Info info, char *port_name);
int MPI_Open_port(MPI_Info info, char *port_name);
int MPI_Publish_name(const char *service_name, MPI_Info info, const char *port_name);
int MPI_Query_thread(int *provided);
int MPI_Session_finalize(MPI_Session *session);
int MPI_Session_get_nth_pset(MPI_Session session, MPI_Info info, int n, int *pset_len, char *pset_name);
int MPI_Session_get_info(MPI_Session session, MPI_Info *info_used);
int MPI_Session_get_num_psets(MPI_Session session, MPI_Info info, int *npset_names);
int MPI_Session_get_pset_info(MPI_Session session, const char *pset_name, MPI_Info *info);
int MPI_Session_init(MPI_Info info, MPI_Errhandler errhandler, MPI_Session *session);
int MPI_Unpublish_name(const char *service_name, MPI_Info info, const char *port_name);

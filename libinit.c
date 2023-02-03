#include "muk.h"
#include "muk-dl.h"

#if defined(__linux__) && defined(__x86_64__)
#define LIBMPI_NAME "/usr/lib/x86_64-linux-gnu/libmpi.so"
#elif defined(__MACH__)
#define LIBMPI_NAME "/opt/homebrew/lib/libmpi.dylib"
#else
#warning No default MPI library path.
#endif

Which_MPI_e whose_mpi = UNKNOWN;

typedef struct __MPI_Comm__ * MUK_Comm;
typedef struct __MPI_Datatype__ * MUK_Datatype;
typedef struct __MPI_Errhandler__ * MUK_Errhandler;
typedef struct __MPI_File__ * MUK_File;
typedef struct __MPI_Group__ * MUK_Group;
typedef struct __MPI_Info__ * MUK_Info;
typedef struct __MPI_Message__ * MUK_Message;
typedef struct __MPI_Op__ * MUK_Op;
typedef struct __MPI_Request__ * MUK_Request;
typedef struct __MPI_Session__ * MUK_Session;
typedef struct __MPI_Win__ * MUK_Win;

typedef struct
{
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    int __kielletty__[5];
}
MUK_Status;

typedef ptrdiff_t MUK_Aint;
typedef ptrdiff_t MUK_Count;
typedef ptrdiff_t MUK_Offset;

typedef void MUK_User_function(void *invec, void *inoutvec, int *len,
             MUK_Datatype *datatype);
typedef void MUK_User_function_c(void *invec, void *inoutvec,
             MUK_Count *len, MUK_Datatype *datatype);
typedef int MUK_Comm_copy_attr_function(MUK_Comm oldcomm, int comm_keyval,
             void *extra_state, void *attribute_val_in,
             void *attribute_val_out, int *flag);
typedef int MUK_Comm_delete_attr_function(MUK_Comm comm, int comm_keyval,
             void *attribute_val, void *extra_state);
typedef int MUK_Win_copy_attr_function(MUK_Win oldwin, int win_keyval,
             void *extra_state, void *attribute_val_in,
             void *attribute_val_out, int *flag);
typedef int MUK_Win_delete_attr_function(MUK_Win win, int win_keyval,
             void *attribute_val, void *extra_state);
typedef int MUK_Type_copy_attr_function(MUK_Datatype oldtype,
             int type_keyval, void *extra_state, void *attribute_val_in,
             void *attribute_val_out, int *flag);
typedef int MUK_Type_delete_attr_function(MUK_Datatype datatype,
             int type_keyval, void *attribute_val, void *extra_state);
typedef void MUK_Comm_errhandler_function(MUK_Comm *comm, int *error_code,
             ...);
typedef void MUK_Win_errhandler_function(MUK_Win *win, int *error_code,
             ...);
typedef void MUK_File_errhandler_function(MUK_File *file, int *error_code,
             ...);
typedef void MUK_Session_errhandler_function(MUK_Session *session,
             int *error_code, ...);
typedef int MUK_Grequest_query_function(void *extra_state,
             MUK_Status *status);
typedef int MUK_Grequest_free_function(void *extra_state);
typedef int MUK_Grequest_cancel_function(void *extra_state, int complete);
typedef int MUK_Datarep_extent_function(MUK_Datatype datatype,
             MUK_Aint *extent, void *extra_state);
typedef int MUK_Datarep_conversion_function(void *userbuf, MUK_Datatype datatype, int count, void *filebuf, MUK_Offset position, void *extra_state);
typedef int MUK_Datarep_conversion_function_c(void *userbuf,
             MUK_Datatype datatype, MUK_Count count, void *filebuf,
             MUK_Offset position, void *extra_state);

int (*MUK_Init)(int *argc, char ***argv);
int (*MUK_Init_thread)(int *argc, char ***argv, int required, int *provided);
int (*MUK_Initialized)(int *flag);

int (*MUK_Get_library_version)(char *version, int *resultlen);
int (*MUK_Get_processor_name)(char *name, int *resultlen);
int (*MUK_Get_version)(int *version, int *subversion);

int (*MUK_Finalize)(void);
int (*MUK_Finalized)(int *flag);

int (*MUK_Init_thread)(int *argc, char ***argv, int required, int *provided);
int (*MUK_Is_thread_main)(int *flag);
int (*MUK_Query_thread)(int *provided);

int (*MUK_Comm_rank)(MUK_Comm comm, int *rank);
int (*MUK_Comm_size)(MUK_Comm comm, int *size);
int (*MUK_Abort)(MUK_Comm comm, int errorcode);

int (*MUK_Accumulate)(const void *origin_addr, int origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win);
int (*MUK_Accumulate_c)(const void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win);
int (*MUK_Add_error_class)(int *errorclass);
int (*MUK_Add_error_code)(int errorclass, int *errorcode);
int (*MUK_Add_error_string)(int errorcode, const char *string);
int (*MUK_Address)(void *location, MUK_Aint *address);
int (*MUK_Allgather)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Allgather_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Allgather_init)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Allgather_init_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Allgatherv)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Allgatherv_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Allgatherv_init)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Allgatherv_init_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Alloc_mem)(MUK_Aint size, MUK_Info info, void *baseptr);
int (*MUK_Allreduce)(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm);
int (*MUK_Allreduce_c)(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm);
int (*MUK_Allreduce_init)(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Allreduce_init_c)(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Alltoall)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Alltoall_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Alltoall_init)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Alltoall_init_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Alltoallv)(const void *sendbuf, const int sendcounts[], const int sdispls[], MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Alltoallv_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Alltoallv_init)(const void *sendbuf, const int sendcounts[], const int sdispls[], MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Alltoallv_init_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Alltoallw)(const void *sendbuf, const int sendcounts[], const int sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm);
int (*MUK_Alltoallw_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm);
int (*MUK_Alltoallw_init)(const void *sendbuf, const int sendcounts[], const int sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Alltoallw_init_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Attr_delete)(MUK_Comm comm, int keyval);
int (*MUK_Attr_get)(MUK_Comm comm, int keyval, void *attribute_val, int *flag);
int (*MUK_Attr_put)(MUK_Comm comm, int keyval, void *attribute_val);
int (*MUK_Barrier)(MUK_Comm comm);
int (*MUK_Barrier_init)(MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Bcast)(void *buffer, int count, MUK_Datatype datatype, int root, MUK_Comm comm);
int (*MUK_Bcast_c)(void *buffer, MUK_Count count, MUK_Datatype datatype, int root, MUK_Comm comm);
int (*MUK_Bcast_init)(void *buffer, int count, MUK_Datatype datatype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Bcast_init_c)(void *buffer, MUK_Count count, MUK_Datatype datatype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Bsend)(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm);
int (*MUK_Bsend_c)(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm);
int (*MUK_Bsend_init)(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Bsend_init_c)(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Buffer_attach)(void *buffer, int size);
int (*MUK_Buffer_attach_c)(void *buffer, MUK_Count size);
int (*MUK_Buffer_detach)(void *buffer_addr, int *size);
int (*MUK_Buffer_detach_c)(void *buffer_addr, MUK_Count *size);
int (*MUK_Cancel)(MUK_Request *request);
int (*MUK_Cart_coords)(MUK_Comm comm, int rank, int maxdims, int coords[]);
int (*MUK_Cart_create)(MUK_Comm comm_old, int ndims, const int dims[], const int periods[], int reorder, MUK_Comm *comm_cart);
int (*MUK_Cart_get)(MUK_Comm comm, int maxdims, int dims[], int periods[], int coords[]);
int (*MUK_Cart_map)(MUK_Comm comm, int ndims, const int dims[], const int periods[], int *newrank);
int (*MUK_Cart_rank)(MUK_Comm comm, const int coords[], int *rank);
int (*MUK_Cart_shift)(MUK_Comm comm, int direction, int disp, int *rank_source, int *rank_dest);
int (*MUK_Cart_sub)(MUK_Comm comm, const int remain_dims[], MUK_Comm *newcomm);
int (*MUK_Cartdim_get)(MUK_Comm comm, int *ndims);
int (*MUK_Close_port)(const char *port_name);
int (*MUK_Comm_accept)(const char *port_name, MUK_Info info, int root, MUK_Comm comm, MUK_Comm *newcomm);
int (*MUK_Comm_call_errhandler)(MUK_Comm comm, int errorcode);
int (*MUK_Comm_compare)(MUK_Comm comm1, MUK_Comm comm2, int *result);
int (*MUK_Comm_connect)(const char *port_name, MUK_Info info, int root, MUK_Comm comm, MUK_Comm *newcomm);
int (*MUK_Comm_create)(MUK_Comm comm, MUK_Group group, MUK_Comm *newcomm);
int (*MUK_Comm_create_errhandler)(MUK_Comm_errhandler_function *comm_errhandler_fn, MUK_Errhandler *errhandler);
int (*MUK_Comm_create_from_group)(MUK_Group group, const char *stringtag, MUK_Info info, MUK_Errhandler errhandler, MUK_Comm *newcomm);
int (*MUK_Comm_create_group)(MUK_Comm comm, MUK_Group group, int tag, MUK_Comm *newcomm);
int (*MUK_Comm_create_keyval)(MUK_Comm_copy_attr_function *comm_copy_attr_fn, MUK_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state);
int (*MUK_Comm_delete_attr)(MUK_Comm comm, int comm_keyval);
int (*MUK_Comm_disconnect)(MUK_Comm *comm);
int (*MUK_Comm_dup)(MUK_Comm comm, MUK_Comm *newcomm);
int (*MUK_Comm_dup_with_info)(MUK_Comm comm, MUK_Info info, MUK_Comm *newcomm);
int (*MUK_Comm_free)(MUK_Comm *comm);
int (*MUK_Comm_free_keyval)(int *comm_keyval);
int (*MUK_Comm_get_attr)(MUK_Comm comm, int comm_keyval, void *attribute_val, int *flag);
int (*MUK_Comm_get_errhandler)(MUK_Comm comm, MUK_Errhandler *errhandler);
int (*MUK_Comm_get_info)(MUK_Comm comm, MUK_Info *info_used);
int (*MUK_Comm_get_name)(MUK_Comm comm, char *comm_name, int *resultlen);
int (*MUK_Comm_get_parent)(MUK_Comm *parent);
int (*MUK_Comm_group)(MUK_Comm comm, MUK_Group *group);
int (*MUK_Comm_idup)(MUK_Comm comm, MUK_Comm *newcomm, MUK_Request *request);
int (*MUK_Comm_idup_with_info)(MUK_Comm comm, MUK_Info info, MUK_Comm *newcomm, MUK_Request *request);
int (*MUK_Comm_join)(int fd, MUK_Comm *intercomm);
int (*MUK_Comm_rank)(MUK_Comm comm, int *rank);
int (*MUK_Comm_remote_group)(MUK_Comm comm, MUK_Group *group);
int (*MUK_Comm_remote_size)(MUK_Comm comm, int *size);
int (*MUK_Comm_set_attr)(MUK_Comm comm, int comm_keyval, void *attribute_val);
int (*MUK_Comm_set_errhandler)(MUK_Comm comm, MUK_Errhandler errhandler);
int (*MUK_Comm_set_info)(MUK_Comm comm, MUK_Info info);
int (*MUK_Comm_set_name)(MUK_Comm comm, const char *comm_name);
int (*MUK_Comm_size)(MUK_Comm comm, int *size);
int (*MUK_Comm_split)(MUK_Comm comm, int color, int key, MUK_Comm *newcomm);
int (*MUK_Comm_split_type)(MUK_Comm comm, int split_type, int key, MUK_Info info, MUK_Comm *newcomm);
int (*MUK_Comm_test_inter)(MUK_Comm comm, int *flag);
int (*MUK_Compare_and_swap)(const void *origin_addr, const void *compare_addr, void *result_addr, MUK_Datatype datatype, int target_rank, MUK_Aint target_disp, MUK_Win win);
int (*MUK_Dims_create)(int nnodes, int ndims, int dims[]);
int (*MUK_Dist_graph_create)(MUK_Comm comm_old, int n, const int sources[], const int degrees[], const int destinations[], const int weights[], MUK_Info info, int reorder, MUK_Comm *comm_dist_graph);
int (*MUK_Dist_graph_create_adjacent)(MUK_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], MUK_Info info, int reorder, MUK_Comm *comm_dist_graph);
int (*MUK_Dist_graph_neighbors)(MUK_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[]);
int (*MUK_Dist_graph_neighbors_count)(MUK_Comm comm, int *indegree, int *outdegree, int *weighted);
int (*MUK_Errhandler_create)(MUK_Comm_errhandler_function *comm_errhandler_fn, MUK_Errhandler *errhandler);
int (*MUK_Errhandler_free)(MUK_Errhandler *errhandler);
int (*MUK_Errhandler_get)(MUK_Comm comm, MUK_Errhandler *errhandler);
int (*MUK_Errhandler_set)(MUK_Comm comm, MUK_Errhandler errhandler);
int (*MUK_Error_class)(int errorcode, int *errorclass);
int (*MUK_Error_string)(int errorcode, char *string, int *resultlen);
int (*MUK_Exscan)(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm);
int (*MUK_Exscan_c)(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm);
int (*MUK_Exscan_init)(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Exscan_init_c)(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Fetch_and_op)(const void *origin_addr, void *result_addr, MUK_Datatype datatype, int target_rank, MUK_Aint target_disp, MUK_Op op, MUK_Win win);
int (*MUK_File_call_errhandler)(MUK_File fh, int errorcode);
int (*MUK_File_close)(MUK_File *fh);
int (*MUK_File_create_errhandler)(MUK_File_errhandler_function *file_errhandler_fn, MUK_Errhandler *errhandler);
int (*MUK_File_delete)(const char *filename, MUK_Info info);
int (*MUK_File_get_amode)(MUK_File fh, int *amode);
int (*MUK_File_get_atomicity)(MUK_File fh, int *flag);
int (*MUK_File_get_byte_offset)(MUK_File fh, MUK_Offset offset, MUK_Offset *disp);
int (*MUK_File_get_errhandler)(MUK_File file, MUK_Errhandler *errhandler);
int (*MUK_File_get_group)(MUK_File fh, MUK_Group *group);
int (*MUK_File_get_info)(MUK_File fh, MUK_Info *info_used);
int (*MUK_File_get_position)(MUK_File fh, MUK_Offset *offset);
int (*MUK_File_get_position_shared)(MUK_File fh, MUK_Offset *offset);
int (*MUK_File_get_size)(MUK_File fh, MUK_Offset *size);
int (*MUK_File_get_type_extent)(MUK_File fh, MUK_Datatype datatype, MUK_Aint *extent);
int (*MUK_File_get_type_extent_c)(MUK_File fh, MUK_Datatype datatype, MUK_Count *extent);
int (*MUK_File_get_view)(MUK_File fh, MUK_Offset *disp, MUK_Datatype *etype, MUK_Datatype *filetype, char *datarep);
int (*MUK_File_iread)(MUK_File fh, void *buf, int count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iread_all)(MUK_File fh, void *buf, int count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iread_all_c)(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iread_at)(MUK_File fh, MUK_Offset offset, void *buf, int count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iread_at_all)(MUK_File fh, MUK_Offset offset, void *buf, int count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iread_at_all_c)(MUK_File fh, MUK_Offset offset, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iread_at_c)(MUK_File fh, MUK_Offset offset, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iread_c)(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iread_shared)(MUK_File fh, void *buf, int count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iread_shared_c)(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iwrite)(MUK_File fh, const void *buf, int count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iwrite_all)(MUK_File fh, const void *buf, int count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iwrite_all_c)(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iwrite_at)(MUK_File fh, MUK_Offset offset, const void *buf, int count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iwrite_at_all)(MUK_File fh, MUK_Offset offset, const void *buf, int count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iwrite_at_all_c)(MUK_File fh, MUK_Offset offset, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iwrite_at_c)(MUK_File fh, MUK_Offset offset, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iwrite_c)(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iwrite_shared)(MUK_File fh, const void *buf, int count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_iwrite_shared_c)(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request);
int (*MUK_File_open)(MUK_Comm comm, const char *filename, int amode, MUK_Info info, MUK_File *fh);
int (*MUK_File_preallocate)(MUK_File fh, MUK_Offset size);
int (*MUK_File_read)(MUK_File fh, void *buf, int count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_read_all)(MUK_File fh, void *buf, int count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_read_all_begin)(MUK_File fh, void *buf, int count, MUK_Datatype datatype);
int (*MUK_File_read_all_begin_c)(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype);
int (*MUK_File_read_all_c)(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_read_all_end)(MUK_File fh, void *buf, MUK_Status *status);
int (*MUK_File_read_at)(MUK_File fh, MUK_Offset offset, void *buf, int count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_read_at_all)(MUK_File fh, MUK_Offset offset, void *buf, int count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_read_at_all_begin)(MUK_File fh, MUK_Offset offset, void *buf, int count, MUK_Datatype datatype);
int (*MUK_File_read_at_all_begin_c)(MUK_File fh, MUK_Offset offset, void *buf, MUK_Count count, MUK_Datatype datatype);
int (*MUK_File_read_at_all_c)(MUK_File fh, MUK_Offset offset, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_read_at_all_end)(MUK_File fh, void *buf, MUK_Status *status);
int (*MUK_File_read_at_c)(MUK_File fh, MUK_Offset offset, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_read_c)(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_read_ordered)(MUK_File fh, void *buf, int count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_read_ordered_begin)(MUK_File fh, void *buf, int count, MUK_Datatype datatype);
int (*MUK_File_read_ordered_begin_c)(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype);
int (*MUK_File_read_ordered_c)(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_read_ordered_end)(MUK_File fh, void *buf, MUK_Status *status);
int (*MUK_File_read_shared)(MUK_File fh, void *buf, int count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_read_shared_c)(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_seek)(MUK_File fh, MUK_Offset offset, int whence);
int (*MUK_File_seek_shared)(MUK_File fh, MUK_Offset offset, int whence);
int (*MUK_File_set_atomicity)(MUK_File fh, int flag);
int (*MUK_File_set_errhandler)(MUK_File file, MUK_Errhandler errhandler);
int (*MUK_File_set_info)(MUK_File fh, MUK_Info info);
int (*MUK_File_set_size)(MUK_File fh, MUK_Offset size);
int (*MUK_File_set_view)(MUK_File fh, MUK_Offset disp, MUK_Datatype etype, MUK_Datatype filetype, const char *datarep, MUK_Info info);
int (*MUK_File_sync)(MUK_File fh);
int (*MUK_File_write)(MUK_File fh, const void *buf, int count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_write_all)(MUK_File fh, const void *buf, int count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_write_all_begin)(MUK_File fh, const void *buf, int count, MUK_Datatype datatype);
int (*MUK_File_write_all_begin_c)(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype);
int (*MUK_File_write_all_c)(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_write_all_end)(MUK_File fh, const void *buf, MUK_Status *status);
int (*MUK_File_write_at)(MUK_File fh, MUK_Offset offset, const void *buf, int count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_write_at_all)(MUK_File fh, MUK_Offset offset, const void *buf, int count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_write_at_all_begin)(MUK_File fh, MUK_Offset offset, const void *buf, int count, MUK_Datatype datatype);
int (*MUK_File_write_at_all_begin_c)(MUK_File fh, MUK_Offset offset, const void *buf, MUK_Count count, MUK_Datatype datatype);
int (*MUK_File_write_at_all_c)(MUK_File fh, MUK_Offset offset, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_write_at_all_end)(MUK_File fh, const void *buf, MUK_Status *status);
int (*MUK_File_write_at_c)(MUK_File fh, MUK_Offset offset, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_write_c)(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_write_ordered)(MUK_File fh, const void *buf, int count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_write_ordered_begin)(MUK_File fh, const void *buf, int count, MUK_Datatype datatype);
int (*MUK_File_write_ordered_begin_c)(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype);
int (*MUK_File_write_ordered_c)(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_write_ordered_end)(MUK_File fh, const void *buf, MUK_Status *status);
int (*MUK_File_write_shared)(MUK_File fh, const void *buf, int count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_File_write_shared_c)(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status);
int (*MUK_Free_mem)(void *base);
int (*MUK_Gather)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm);
int (*MUK_Gather_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm);
int (*MUK_Gather_init)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Gather_init_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Gatherv)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, int root, MUK_Comm comm);
int (*MUK_Gatherv_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, int root, MUK_Comm comm);
int (*MUK_Gatherv_init)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Gatherv_init_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Get)(void *origin_addr, int origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Win win);
int (*MUK_Get_accumulate)(const void *origin_addr, int origin_count, MUK_Datatype origin_datatype, void *result_addr, int result_count, MUK_Datatype result_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win);
int (*MUK_Get_accumulate_c)(const void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, void *result_addr, MUK_Count result_count, MUK_Datatype result_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win);
int (*MUK_Get_address)(const void *location, MUK_Aint *address);
int (*MUK_Get_c)(void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Win win);
int (*MUK_Get_count)(const MUK_Status *status, MUK_Datatype datatype, int *count);
int (*MUK_Get_count_c)(const MUK_Status *status, MUK_Datatype datatype, MUK_Count *count);
int (*MUK_Get_elements)(const MUK_Status *status, MUK_Datatype datatype, int *count);
int (*MUK_Get_elements_c)(const MUK_Status *status, MUK_Datatype datatype, MUK_Count *count);
int (*MUK_Get_elements_x)(const MUK_Status *status, MUK_Datatype datatype, MUK_Count *count);
int (*MUK_Graph_create)(MUK_Comm comm_old, int nnodes, const int indx[], const int edges[], int reorder, MUK_Comm *comm_graph);
int (*MUK_Graph_get)(MUK_Comm comm, int maxindex, int maxedges, int indx[], int edges[]);
int (*MUK_Graph_map)(MUK_Comm comm, int nnodes, const int indx[], const int edges[], int *newrank);
int (*MUK_Graph_neighbors)(MUK_Comm comm, int rank, int maxneighbors, int neighbors[]);
int (*MUK_Graph_neighbors_count)(MUK_Comm comm, int rank, int *nneighbors);
int (*MUK_Graphdims_get)(MUK_Comm comm, int *nnodes, int *nedges);
int (*MUK_Grequest_complete)(MUK_Request request);
int (*MUK_Grequest_start)(MUK_Grequest_query_function *query_fn, MUK_Grequest_free_function *free_fn, MUK_Grequest_cancel_function *cancel_fn, void *extra_state, MUK_Request *request);
int (*MUK_Group_compare)(MUK_Group group1, MUK_Group group2, int *result);
int (*MUK_Group_difference)(MUK_Group group1, MUK_Group group2, MUK_Group *newgroup);
int (*MUK_Group_excl)(MUK_Group group, int n, const int ranks[], MUK_Group *newgroup);
int (*MUK_Group_free)(MUK_Group *group);
int (*MUK_Group_from_session_pset)(MUK_Session session, const char *pset_name, MUK_Group *newgroup);
int (*MUK_Group_incl)(MUK_Group group, int n, const int ranks[], MUK_Group *newgroup);
int (*MUK_Group_intersection)(MUK_Group group1, MUK_Group group2, MUK_Group *newgroup);
int (*MUK_Group_range_excl)(MUK_Group group, int n, int ranges[][3], MUK_Group *newgroup);
int (*MUK_Group_range_incl)(MUK_Group group, int n, int ranges[][3], MUK_Group *newgroup);
int (*MUK_Group_rank)(MUK_Group group, int *rank);
int (*MUK_Group_size)(MUK_Group group, int *size);
int (*MUK_Group_translate_ranks)(MUK_Group group1, int n, const int ranks1[], MUK_Group group2, int ranks2[]);
int (*MUK_Group_union)(MUK_Group group1, MUK_Group group2, MUK_Group *newgroup);
int (*MUK_Iallgather)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Iallgather_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Iallgatherv)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Iallgatherv_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Iallreduce)(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request);
int (*MUK_Iallreduce_c)(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ialltoall)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ialltoall_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ialltoallv)(const void *sendbuf, const int sendcounts[], const int sdispls[], MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ialltoallv_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ialltoallw)(const void *sendbuf, const int sendcounts[], const int sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Request *request);
int (*MUK_Ialltoallw_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Request *request);
int (*MUK_Ibarrier)(MUK_Comm comm, MUK_Request *request);
int (*MUK_Ibcast)(void *buffer, int count, MUK_Datatype datatype, int root, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ibcast_c)(void *buffer, MUK_Count count, MUK_Datatype datatype, int root, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ibsend)(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ibsend_c)(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Iexscan)(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request);
int (*MUK_Iexscan_c)(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request);
int (*MUK_Igather)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request);
int (*MUK_Igather_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request);
int (*MUK_Igatherv)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request);
int (*MUK_Igatherv_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request);
int (*MUK_Improbe)(int source, int tag, MUK_Comm comm, int *flag, MUK_Message *message, MUK_Status *status);
int (*MUK_Imrecv)(void *buf, int count, MUK_Datatype datatype, MUK_Message *message, MUK_Request *request);
int (*MUK_Imrecv_c)(void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Message *message, MUK_Request *request);
int (*MUK_Ineighbor_allgather)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ineighbor_allgather_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ineighbor_allgatherv)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ineighbor_allgatherv_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ineighbor_alltoall)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ineighbor_alltoall_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ineighbor_alltoallv)(const void *sendbuf, const int sendcounts[], const int sdispls[], MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ineighbor_alltoallv_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ineighbor_alltoallw)(const void *sendbuf, const int sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Request *request);
int (*MUK_Ineighbor_alltoallw_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Request *request);
int (*MUK_Info_create)(MUK_Info *info);
int (*MUK_Info_create_env)(int argc, char *argv[], MUK_Info *info);
int (*MUK_Info_delete)(MUK_Info info, const char *key);
int (*MUK_Info_dup)(MUK_Info info, MUK_Info *newinfo);
int (*MUK_Info_free)(MUK_Info *info);
int (*MUK_Info_get)(MUK_Info info, const char *key, int valuelen, char *value, int *flag);
int (*MUK_Info_get_nkeys)(MUK_Info info, int *nkeys);
int (*MUK_Info_get_nthkey)(MUK_Info info, int n, char *key);
int (*MUK_Info_get_string)(MUK_Info info, const char *key, int *buflen, char *value, int *flag);
int (*MUK_Info_get_valuelen)(MUK_Info info, const char *key, int *valuelen, int *flag);
int (*MUK_Info_set)(MUK_Info info, const char *key, const char *value);
int (*MUK_Intercomm_create)(MUK_Comm local_comm, int local_leader, MUK_Comm peer_comm, int remote_leader, int tag, MUK_Comm *newintercomm);
int (*MUK_Intercomm_create_from_groups)(MUK_Group local_group, int local_leader, MUK_Group remote_group, int remote_leader, const char *stringtag, MUK_Info info, MUK_Errhandler errhandler, MUK_Comm *newintercomm);
int (*MUK_Intercomm_merge)(MUK_Comm intercomm, int high, MUK_Comm *newintracomm);
int (*MUK_Iprobe)(int source, int tag, MUK_Comm comm, int *flag, MUK_Status *status);
int (*MUK_Irecv)(void *buf, int count, MUK_Datatype datatype, int source, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Irecv_c)(void *buf, MUK_Count count, MUK_Datatype datatype, int source, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ireduce)(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, int root, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ireduce_c)(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, int root, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ireduce_scatter)(const void *sendbuf, void *recvbuf, const int recvcounts[], MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ireduce_scatter_block)(const void *sendbuf, void *recvbuf, int recvcount, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ireduce_scatter_block_c)(const void *sendbuf, void *recvbuf, MUK_Count recvcount, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ireduce_scatter_c)(const void *sendbuf, void *recvbuf, const MUK_Count recvcounts[], MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request);
int (*MUK_Irsend)(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Irsend_c)(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Iscan)(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request);
int (*MUK_Iscan_c)(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request);
int (*MUK_Iscatter)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request);
int (*MUK_Iscatter_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request);
int (*MUK_Iscatterv)(const void *sendbuf, const int sendcounts[], const int displs[], MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request);
int (*MUK_Iscatterv_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint displs[], MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request);
int (*MUK_Isend)(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Isend_c)(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Isendrecv)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MUK_Datatype recvtype, int source, int recvtag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Isendrecv_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, int dest, int sendtag, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int source, int recvtag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Isendrecv_replace)(void *buf, int count, MUK_Datatype datatype, int dest, int sendtag, int source, int recvtag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Isendrecv_replace_c)(void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int sendtag, int source, int recvtag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Issend)(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Issend_c)(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
// deprecated
//int (*MUK_Keyval_create)(MUK_Copy_function *copy_fn, MUK_Delete_function *delete_fn, int *keyval, void *extra_state);
//int (*MUK_Keyval_free)(int *keyval);
int (*MUK_Lookup_name)(const char *service_name, MUK_Info info, char *port_name);
int (*MUK_Mprobe)(int source, int tag, MUK_Comm comm, MUK_Message *message, MUK_Status *status);
int (*MUK_Mrecv)(void *buf, int count, MUK_Datatype datatype, MUK_Message *message, MUK_Status *status);
int (*MUK_Mrecv_c)(void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Message *message, MUK_Status *status);
int (*MUK_Neighbor_allgather)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Neighbor_allgather_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Neighbor_allgather_init)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Neighbor_allgather_init_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Neighbor_allgatherv)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Neighbor_allgatherv_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Neighbor_allgatherv_init)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Neighbor_allgatherv_init_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Neighbor_alltoall)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Neighbor_alltoall_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Neighbor_alltoall_init)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Neighbor_alltoall_init_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Neighbor_alltoallv)(const void *sendbuf, const int sendcounts[], const int sdispls[], MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Neighbor_alltoallv_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], MUK_Datatype recvtype, MUK_Comm comm);
int (*MUK_Neighbor_alltoallv_init)(const void *sendbuf, const int sendcounts[], const int sdispls[], MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Neighbor_alltoallv_init_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Neighbor_alltoallw)(const void *sendbuf, const int sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm);
int (*MUK_Neighbor_alltoallw_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm);
int (*MUK_Neighbor_alltoallw_init)(const void *sendbuf, const int sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Neighbor_alltoallw_init_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Op_commutative)(MUK_Op op, int *commute);
int (*MUK_Op_create)(MUK_User_function *user_fn, int commute, MUK_Op *op);
int (*MUK_Op_create_c)(MUK_User_function_c *user_fn, int commute, MUK_Op *op);
int (*MUK_Op_free)(MUK_Op *op);
int (*MUK_Open_port)(MUK_Info info, char *port_name);
int (*MUK_Pack)(const void *inbuf, int incount, MUK_Datatype datatype, void *outbuf, int outsize, int *position, MUK_Comm comm);
int (*MUK_Pack_c)(const void *inbuf, MUK_Count incount, MUK_Datatype datatype, void *outbuf, MUK_Count outsize, MUK_Count *position, MUK_Comm comm);
int (*MUK_Pack_external)(const char *datarep, const void *inbuf, int incount, MUK_Datatype datatype, void *outbuf, MUK_Aint outsize, MUK_Aint *position);
int (*MUK_Pack_external_c)(const char *datarep, const void *inbuf, MUK_Count incount, MUK_Datatype datatype, void *outbuf, MUK_Count outsize, MUK_Count *position);
int (*MUK_Pack_external_size)(const char *datarep, int incount, MUK_Datatype datatype, MUK_Aint *size);
int (*MUK_Pack_external_size_c)(const char *datarep, MUK_Count incount, MUK_Datatype datatype, MUK_Count *size);
int (*MUK_Pack_size)(int incount, MUK_Datatype datatype, MUK_Comm comm, int *size);
int (*MUK_Pack_size_c)(MUK_Count incount, MUK_Datatype datatype, MUK_Comm comm, MUK_Count *size);
int (*MUK_Parrived)(MUK_Request request, int partition, int *flag);
int (*MUK_Pcontrol)(const int level, ...);
int (*MUK_Pready)(int partition, MUK_Request request);
int (*MUK_Pready_list)(int length, const int array_of_partitions[], MUK_Request request);
int (*MUK_Pready_range)(int partition_low, int partition_high, MUK_Request request);
int (*MUK_Precv_init)(void *buf, int partitions, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Probe)(int source, int tag, MUK_Comm comm, MUK_Status *status);
int (*MUK_Psend_init)(const void *buf, int partitions, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Publish_name)(const char *service_name, MUK_Info info, const char *port_name);
int (*MUK_Put)(const void *origin_addr, int origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Win win);
int (*MUK_Put_c)(const void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Win win);
int (*MUK_Raccumulate)(const void *origin_addr, int origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win, MUK_Request *request);
int (*MUK_Raccumulate_c)(const void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win, MUK_Request *request);
int (*MUK_Recv)(void *buf, int count, MUK_Datatype datatype, int source, int tag, MUK_Comm comm, MUK_Status *status);
int (*MUK_Recv_c)(void *buf, MUK_Count count, MUK_Datatype datatype, int source, int tag, MUK_Comm comm, MUK_Status *status);
int (*MUK_Recv_init)(void *buf, int count, MUK_Datatype datatype, int source, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Recv_init_c)(void *buf, MUK_Count count, MUK_Datatype datatype, int source, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Reduce)(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, int root, MUK_Comm comm);
int (*MUK_Reduce_c)(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, int root, MUK_Comm comm);
int (*MUK_Reduce_init)(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Reduce_init_c)(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Reduce_local)(const void *inbuf, void *inoutbuf, int count, MUK_Datatype datatype, MUK_Op op);
int (*MUK_Reduce_local_c)(const void *inbuf, void *inoutbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op);
int (*MUK_Reduce_scatter)(const void *sendbuf, void *recvbuf, const int recvcounts[], MUK_Datatype datatype, MUK_Op op, MUK_Comm comm);
int (*MUK_Reduce_scatter_block)(const void *sendbuf, void *recvbuf, int recvcount, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm);
int (*MUK_Reduce_scatter_block_c)(const void *sendbuf, void *recvbuf, MUK_Count recvcount, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm);
int (*MUK_Reduce_scatter_block_init)(const void *sendbuf, void *recvbuf, int recvcount, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Reduce_scatter_block_init_c)(const void *sendbuf, void *recvbuf, MUK_Count recvcount, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Reduce_scatter_c)(const void *sendbuf, void *recvbuf, const MUK_Count recvcounts[], MUK_Datatype datatype, MUK_Op op, MUK_Comm comm);
int (*MUK_Reduce_scatter_init)(const void *sendbuf, void *recvbuf, const int recvcounts[], MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Reduce_scatter_init_c)(const void *sendbuf, void *recvbuf, const MUK_Count recvcounts[], MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Register_datarep)(const char *datarep, MUK_Datarep_conversion_function *read_conversion_fn, MUK_Datarep_conversion_function *write_conversion_fn, MUK_Datarep_extent_function *dtype_file_extent_fn, void *extra_state);
int (*MUK_Register_datarep_c)(const char *datarep, MUK_Datarep_conversion_function_c *read_conversion_fn, MUK_Datarep_conversion_function_c *write_conversion_fn, MUK_Datarep_extent_function *dtype_file_extent_fn, void *extra_state);
int (*MUK_Request_free)(MUK_Request *request);
int (*MUK_Request_get_status)(MUK_Request request, int *flag, MUK_Status *status);
int (*MUK_Rget)(void *origin_addr, int origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Win win, MUK_Request *request);
int (*MUK_Rget_accumulate)(const void *origin_addr, int origin_count, MUK_Datatype origin_datatype, void *result_addr, int result_count, MUK_Datatype result_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win, MUK_Request *request);
int (*MUK_Rget_accumulate_c)(const void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, void *result_addr, MUK_Count result_count, MUK_Datatype result_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win, MUK_Request *request);
int (*MUK_Rget_c)(void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Win win, MUK_Request *request);
int (*MUK_Rput)(const void *origin_addr, int origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Win win, MUK_Request *request);
int (*MUK_Rput_c)(const void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Win win, MUK_Request *request);
int (*MUK_Rsend)(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm);
int (*MUK_Rsend_c)(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm);
int (*MUK_Rsend_init)(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Rsend_init_c)(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Scan)(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm);
int (*MUK_Scan_c)(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm);
int (*MUK_Scan_init)(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Scan_init_c)(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Scatter)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm);
int (*MUK_Scatter_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm);
int (*MUK_Scatter_init)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Scatter_init_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Scatterv)(const void *sendbuf, const int sendcounts[], const int displs[], MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm);
int (*MUK_Scatterv_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint displs[], MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm);
int (*MUK_Scatterv_init)(const void *sendbuf, const int sendcounts[], const int displs[], MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Scatterv_init_c)(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint displs[], MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request);
int (*MUK_Send)(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm);
int (*MUK_Send_c)(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm);
int (*MUK_Send_init)(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Send_init_c)(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Sendrecv)(const void *sendbuf, int sendcount, MUK_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MUK_Datatype recvtype, int source, int recvtag, MUK_Comm comm, MUK_Status *status);
int (*MUK_Sendrecv_c)(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, int dest, int sendtag, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int source, int recvtag, MUK_Comm comm, MUK_Status *status);
int (*MUK_Sendrecv_replace)(void *buf, int count, MUK_Datatype datatype, int dest, int sendtag, int source, int recvtag, MUK_Comm comm, MUK_Status *status);
int (*MUK_Sendrecv_replace_c)(void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int sendtag, int source, int recvtag, MUK_Comm comm, MUK_Status *status);
int (*MUK_Session_call_errhandler)(MUK_Session session, int errorcode);
int (*MUK_Session_create_errhandler)(MUK_Session_errhandler_function *session_errhandler_fn, MUK_Errhandler *errhandler);
int (*MUK_Session_finalize)(MUK_Session *session);
int (*MUK_Session_get_errhandler)(MUK_Session session, MUK_Errhandler *errhandler);
int (*MUK_Session_get_info)(MUK_Session session, MUK_Info *info_used);
int (*MUK_Session_get_nth_pset)(MUK_Session session, MUK_Info info, int n, int *pset_len, char *pset_name);
int (*MUK_Session_get_num_psets)(MUK_Session session, MUK_Info info, int *npset_names);
int (*MUK_Session_get_pset_info)(MUK_Session session, const char *pset_name, MUK_Info *info);
int (*MUK_Session_init)(MUK_Info info, MUK_Errhandler errhandler, MUK_Session *session);
int (*MUK_Session_set_errhandler)(MUK_Session session, MUK_Errhandler errhandler);
int (*MUK_Ssend)(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm);
int (*MUK_Ssend_c)(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm);
int (*MUK_Ssend_init)(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Ssend_init_c)(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request);
int (*MUK_Start)(MUK_Request *request);
int (*MUK_Startall)(int count, MUK_Request array_of_requests[]);
#ifdef SUPPORT_F08
int (*MUK_Status_f082c)(const MUK_F08_status *f08_status, MUK_Status *c_status);
int (*MUK_Status_f082f)(const MUK_F08_status *f08_status, MUK_Fint *f_status);
int (*MUK_Status_f2f08)(const MUK_Fint *f_status, MUK_F08_status *f08_status);
#endif
int (*MUK_Status_set_cancelled)(MUK_Status *status, int flag);
int (*MUK_Status_set_elements)(MUK_Status *status, MUK_Datatype datatype, int count);
int (*MUK_Status_set_elements_c)(MUK_Status *status, MUK_Datatype datatype, MUK_Count count);
int (*MUK_Status_set_elements_x)(MUK_Status *status, MUK_Datatype datatype, MUK_Count count);
int (*MUK_Test)(MUK_Request *request, int *flag, MUK_Status *status);
int (*MUK_Test_cancelled)(const MUK_Status *status, int *flag);
int (*MUK_Testall)(int count, MUK_Request array_of_requests[], int *flag, MUK_Status array_of_statuses[]);
int (*MUK_Testany)(int count, MUK_Request array_of_requests[], int *indx, int *flag, MUK_Status *status);
int (*MUK_Testsome)(int incount, MUK_Request array_of_requests[], int *outcount, int array_of_indices[], MUK_Status array_of_statuses[]);
int (*MUK_Topo_test)(MUK_Comm comm, int *status);
int (*MUK_Type_commit)(MUK_Datatype *datatype);
int (*MUK_Type_contiguous)(int count, MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_contiguous_c)(MUK_Count count, MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_create_darray)(int size, int rank, int ndims, const int array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_create_darray_c)(int size, int rank, int ndims, const MUK_Count array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_create_f90_complex)(int p, int r, MUK_Datatype *newtype);
int (*MUK_Type_create_f90_integer)(int r, MUK_Datatype *newtype);
int (*MUK_Type_create_f90_real)(int p, int r, MUK_Datatype *newtype);
int (*MUK_Type_create_hindexed)(int count, const int array_of_blocklengths[], const MUK_Aint array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_create_hindexed_block)(int count, int blocklength, const MUK_Aint array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_create_hindexed_block_c)(MUK_Count count, MUK_Count blocklength, const MUK_Count array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_create_hindexed_c)(MUK_Count count, const MUK_Count array_of_blocklengths[], const MUK_Count array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_create_hvector)(int count, int blocklength, MUK_Aint stride, MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_create_hvector_c)(MUK_Count count, MUK_Count blocklength, MUK_Count stride, MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_create_indexed_block)(int count, int blocklength, const int array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_create_indexed_block_c)(MUK_Count count, MUK_Count blocklength, const MUK_Count array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_create_keyval)(MUK_Type_copy_attr_function *type_copy_attr_fn, MUK_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state);
int (*MUK_Type_create_resized)(MUK_Datatype oldtype, MUK_Aint lb, MUK_Aint extent, MUK_Datatype *newtype);
int (*MUK_Type_create_resized_c)(MUK_Datatype oldtype, MUK_Count lb, MUK_Count extent, MUK_Datatype *newtype);
int (*MUK_Type_create_struct)(int count, const int array_of_blocklengths[], const MUK_Aint array_of_displacements[], const MUK_Datatype array_of_types[], MUK_Datatype *newtype);
int (*MUK_Type_create_struct_c)(MUK_Count count, const MUK_Count array_of_blocklengths[], const MUK_Count array_of_displacements[], const MUK_Datatype array_of_types[], MUK_Datatype *newtype);
int (*MUK_Type_create_subarray)(int ndims, const int array_of_sizes[], const int array_of_subsizes[], const int array_of_starts[], int order, MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_create_subarray_c)(int ndims, const MUK_Count array_of_sizes[], const MUK_Count array_of_subsizes[], const MUK_Count array_of_starts[], int order, MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_delete_attr)(MUK_Datatype datatype, int type_keyval);
int (*MUK_Type_dup)(MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_extent)(MUK_Datatype datatype, MUK_Aint *extent);
int (*MUK_Type_free)(MUK_Datatype *datatype);
int (*MUK_Type_free_keyval)(int *type_keyval);
int (*MUK_Type_get_attr)(MUK_Datatype datatype, int type_keyval, void *attribute_val, int *flag);
int (*MUK_Type_get_contents)(MUK_Datatype datatype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MUK_Aint array_of_addresses[], MUK_Datatype array_of_datatypes[]);
int (*MUK_Type_get_contents_c)(MUK_Datatype datatype, MUK_Count max_integers, MUK_Count max_addresses, MUK_Count max_large_counts, MUK_Count max_datatypes, int array_of_integers[], MUK_Aint array_of_addresses[], MUK_Count array_of_large_counts[], MUK_Datatype array_of_datatypes[]);
int (*MUK_Type_get_envelope)(MUK_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner);
int (*MUK_Type_get_envelope_c)(MUK_Datatype datatype, MUK_Count *num_integers, MUK_Count *num_addresses, MUK_Count *num_large_counts, MUK_Count *num_datatypes, int *combiner);
int (*MUK_Type_get_extent)(MUK_Datatype datatype, MUK_Aint *lb, MUK_Aint *extent);
int (*MUK_Type_get_extent_c)(MUK_Datatype datatype, MUK_Count *lb, MUK_Count *extent);
int (*MUK_Type_get_extent_x)(MUK_Datatype datatype, MUK_Count *lb, MUK_Count *extent);
int (*MUK_Type_get_name)(MUK_Datatype datatype, char *type_name, int *resultlen);
int (*MUK_Type_get_true_extent)(MUK_Datatype datatype, MUK_Aint *true_lb, MUK_Aint *true_extent);
int (*MUK_Type_get_true_extent_c)(MUK_Datatype datatype, MUK_Count *true_lb, MUK_Count *true_extent);
int (*MUK_Type_get_true_extent_x)(MUK_Datatype datatype, MUK_Count *true_lb, MUK_Count *true_extent);
int (*MUK_Type_hindexed)(int count, int array_of_blocklengths[], MUK_Aint array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_hvector)(int count, int blocklength, MUK_Aint stride, MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_indexed)(int count, const int array_of_blocklengths[], const int array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_indexed_c)(MUK_Count count, const MUK_Count array_of_blocklengths[], const MUK_Count array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_lb)(MUK_Datatype datatype, MUK_Aint *displacement);
int (*MUK_Type_match_size)(int typeclass, int size, MUK_Datatype *datatype);
int (*MUK_Type_set_attr)(MUK_Datatype datatype, int type_keyval, void *attribute_val);
int (*MUK_Type_set_name)(MUK_Datatype datatype, const char *type_name);
int (*MUK_Type_size)(MUK_Datatype datatype, int *size);
int (*MUK_Type_size_c)(MUK_Datatype datatype, MUK_Count *size);
int (*MUK_Type_size_x)(MUK_Datatype datatype, MUK_Count *size);
int (*MUK_Type_struct)(int count, int array_of_blocklengths[], MUK_Aint array_of_displacements[], MUK_Datatype array_of_types[], MUK_Datatype *newtype);
int (*MUK_Type_ub)(MUK_Datatype datatype, MUK_Aint *displacement);
int (*MUK_Type_vector)(int count, int blocklength, int stride, MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Type_vector_c)(MUK_Count count, MUK_Count blocklength, MUK_Count stride, MUK_Datatype oldtype, MUK_Datatype *newtype);
int (*MUK_Unpack)(const void *inbuf, int insize, int *position, void *outbuf, int outcount, MUK_Datatype datatype, MUK_Comm comm);
int (*MUK_Unpack_c)(const void *inbuf, MUK_Count insize, MUK_Count *position, void *outbuf, MUK_Count outcount, MUK_Datatype datatype, MUK_Comm comm);
int (*MUK_Unpack_external)(const char datarep[], const void *inbuf, MUK_Aint insize, MUK_Aint *position, void *outbuf, int outcount, MUK_Datatype datatype);
int (*MUK_Unpack_external_c)(const char datarep[], const void *inbuf, MUK_Count insize, MUK_Count *position, void *outbuf, MUK_Count outcount, MUK_Datatype datatype);
int (*MUK_Unpublish_name)(const char *service_name, MUK_Info info, const char *port_name);
int (*MUK_Wait)(MUK_Request *request, MUK_Status *status);
int (*MUK_Waitall)(int count, MUK_Request array_of_requests[], MUK_Status array_of_statuses[]);
int (*MUK_Waitany)(int count, MUK_Request array_of_requests[], int *indx, MUK_Status *status);
int (*MUK_Waitsome)(int incount, MUK_Request array_of_requests[], int *outcount, int array_of_indices[], MUK_Status array_of_statuses[]);
int (*MUK_Win_allocate)(MUK_Aint size, int disp_unit, MUK_Info info, MUK_Comm comm, void *baseptr, MUK_Win *win);
int (*MUK_Win_allocate_c)(MUK_Aint size, MUK_Aint disp_unit, MUK_Info info, MUK_Comm comm, void *baseptr, MUK_Win *win);
int (*MUK_Win_allocate_shared)(MUK_Aint size, int disp_unit, MUK_Info info, MUK_Comm comm, void *baseptr, MUK_Win *win);
int (*MUK_Win_allocate_shared_c)(MUK_Aint size, MUK_Aint disp_unit, MUK_Info info, MUK_Comm comm, void *baseptr, MUK_Win *win);
int (*MUK_Win_attach)(MUK_Win win, void *base, MUK_Aint size);
int (*MUK_Win_call_errhandler)(MUK_Win win, int errorcode);
int (*MUK_Win_complete)(MUK_Win win);
int (*MUK_Win_create)(void *base, MUK_Aint size, int disp_unit, MUK_Info info, MUK_Comm comm, MUK_Win *win);
int (*MUK_Win_create_c)(void *base, MUK_Aint size, MUK_Aint disp_unit, MUK_Info info, MUK_Comm comm, MUK_Win *win);
int (*MUK_Win_create_dynamic)(MUK_Info info, MUK_Comm comm, MUK_Win *win);
int (*MUK_Win_create_errhandler)(MUK_Win_errhandler_function *win_errhandler_fn, MUK_Errhandler *errhandler);
int (*MUK_Win_create_keyval)(MUK_Win_copy_attr_function *win_copy_attr_fn, MUK_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state);
int (*MUK_Win_delete_attr)(MUK_Win win, int win_keyval);
int (*MUK_Win_detach)(MUK_Win win, const void *base);
int (*MUK_Win_fence)(int assert, MUK_Win win);
int (*MUK_Win_flush)(int rank, MUK_Win win);
int (*MUK_Win_flush_all)(MUK_Win win);
int (*MUK_Win_flush_local)(int rank, MUK_Win win);
int (*MUK_Win_flush_local_all)(MUK_Win win);
int (*MUK_Win_free)(MUK_Win *win);
int (*MUK_Win_free_keyval)(int *win_keyval);
int (*MUK_Win_get_attr)(MUK_Win win, int win_keyval, void *attribute_val, int *flag);
int (*MUK_Win_get_errhandler)(MUK_Win win, MUK_Errhandler *errhandler);
int (*MUK_Win_get_group)(MUK_Win win, MUK_Group *group);
int (*MUK_Win_get_info)(MUK_Win win, MUK_Info *info_used);
int (*MUK_Win_get_name)(MUK_Win win, char *win_name, int *resultlen);
int (*MUK_Win_lock)(int lock_type, int rank, int assert, MUK_Win win);
int (*MUK_Win_lock_all)(int assert, MUK_Win win);
int (*MUK_Win_post)(MUK_Group group, int assert, MUK_Win win);
int (*MUK_Win_set_attr)(MUK_Win win, int win_keyval, void *attribute_val);
int (*MUK_Win_set_errhandler)(MUK_Win win, MUK_Errhandler errhandler);
int (*MUK_Win_set_info)(MUK_Win win, MUK_Info info);
int (*MUK_Win_set_name)(MUK_Win win, const char *win_name);
int (*MUK_Win_shared_query)(MUK_Win win, int rank, MUK_Aint *size, int *disp_unit, void *baseptr);
int (*MUK_Win_shared_query_c)(MUK_Win win, int rank, MUK_Aint *size, MUK_Aint *disp_unit, void *baseptr);
int (*MUK_Win_start)(MUK_Group group, int assert, MUK_Win win);
int (*MUK_Win_sync)(MUK_Win win);
int (*MUK_Win_test)(MUK_Win win, int *flag);
int (*MUK_Win_unlock)(int rank, MUK_Win win);
int (*MUK_Win_unlock_all)(MUK_Win win);
int (*MUK_Win_wait)(MUK_Win win);

MUK_Request MPI_REQUEST_NULL;

MUK_Errhandler MPI_ERRHANDLER_NULL;

MUK_Info MPI_INFO_NULL;

MUK_Win MPI_WIN_NULL;

MUK_File MPI_FILE_NULL;

MUK_Comm MPI_COMM_NULL;
MUK_Comm MPI_COMM_WORLD;
MUK_Comm MPI_COMM_SELF;

MUK_Group MPI_GROUP_NULL;
MUK_Group MPI_GROUP_EMPTY;

MUK_Message MPI_MESSAGE_NULL;
MUK_Message MPI_MESSAGE_NO_PROC;

MUK_Op MPI_OP_NULL;
MUK_Op MPI_MAX;
MUK_Op MPI_MIN;
MUK_Op MPI_SUM;
MUK_Op MPI_PROD;
MUK_Op MPI_LAND;
MUK_Op MPI_BAND;
MUK_Op MPI_LOR;
MUK_Op MPI_BOR;
MUK_Op MPI_LXOR;
MUK_Op MPI_BXOR;
MUK_Op MPI_MAXLOC;
MUK_Op MPI_MINLOC;
MUK_Op MPI_REPLACE;
MUK_Op MPI_NO_OP;

MUK_Datatype MPI_DATATYPE_NULL;
MUK_Datatype MPI_BYTE;
MUK_Datatype MPI_PACKED;
MUK_Datatype MPI_CHAR;
MUK_Datatype MPI_SHORT;
MUK_Datatype MPI_INT;
MUK_Datatype MPI_LONG;
MUK_Datatype MPI_FLOAT;
MUK_Datatype MPI_DOUBLE;
MUK_Datatype MPI_LONG_DOUBLE;
MUK_Datatype MPI_UNSIGNED_CHAR;
MUK_Datatype MPI_SIGNED_CHAR;
MUK_Datatype MPI_UNSIGNED_SHORT;
MUK_Datatype MPI_UNSIGNED_LONG;
MUK_Datatype MPI_UNSIGNED;
MUK_Datatype MPI_FLOAT_INT;
MUK_Datatype MPI_DOUBLE_INT;
MUK_Datatype MPI_LONG_DOUBLE_INT;
MUK_Datatype MPI_LONG_INT;
MUK_Datatype MPI_SHORT_INT;
MUK_Datatype MPI_2INT;
MUK_Datatype MPI_WCHAR;
MUK_Datatype MPI_LONG_LONG_INT;
MUK_Datatype MPI_LONG_LONG;
MUK_Datatype MPI_UNSIGNED_LONG_LONG;
MUK_Datatype MPI_2COMPLEX;
MUK_Datatype MPI_2DOUBLE_COMPLEX;

int (*WRAP_Load_functions)(void * restrict h, int major, int minor);

// alkaa = start
static int MUK_Alkaa(int * argc, char *** argv, int requested, int * provided)
{
    int rc;

    char * soname;
    char * env = getenv("MPI_LIB");
    if (env == NULL) {
        soname = LIBMPI_NAME;
    } else {
        soname = env;
    }
    printf("soname = %s\n", soname);

    void * h = dlopen(soname, RTLD_LAZY | RTLD_LOCAL);
    if (h == NULL) {
        printf("dlopen of %s failed: %s\n", soname, dlerror() );
        abort();
    }

    MUK_Init = MUK_DLSYM(h,"MPI_Init");
    MUK_Init_thread = MUK_DLSYM(h,"MPI_Init_thread");
    if (provided == NULL) {
        rc = MUK_Init(argc,argv);
    } else {
        rc = MUK_Init_thread(argc,argv,requested,provided);
    }

    char * wrapname;
    // figure out which library i am using
    MUK_Get_library_version = MUK_DLSYM(h,"MPI_Get_library_version");
    {
        char lib_version[16384] = {0};
        int  lib_version_length;
        rc = MUK_Get_library_version(lib_version, &lib_version_length);
        //printf("MPI_Get_library_version = %s\n", lib_version);

        char * pos;
        pos = strstr(lib_version, "Open MPI");
        if (pos != NULL) {
            whose_mpi = OMPI;
            printf("Open-MPI\n");
        }
        pos = strstr(lib_version, "MPICH");
        if (pos != NULL) {
            whose_mpi = MPICH;
            printf("MPICH\n");
        }
    if (whose_mpi == OMPI) {
        wrapname = "ompi-wrap.so";
    } else if (whose_mpi == MPICH) {
        wrapname = "mpich-wrap.so";
    }

    }

    // these are ABI-agnostic and important, so why not load them now...
    MUK_Finalize = MUK_DLSYM(h,"MPI_Finalize");
    MUK_Finalized = MUK_DLSYM(h,"MPI_Finalized");
    MUK_Initialized = MUK_DLSYM(h,"MPI_Initialized");
    MUK_Is_thread_main = MUK_DLSYM(h,"MPI_Is_thread_main");
    MUK_Query_thread = MUK_DLSYM(h,"MPI_Query_thread");
    MUK_Get_processor_name = MUK_DLSYM(h,"MPI_Get_processor_name");

    int major, minor;
    MUK_Get_version = MUK_DLSYM(h,"MPI_Get_version");
    rc = MUK_Get_version(&major, &minor);

    void * wrap_so_handle = dlopen(wrapname, RTLD_LAZY);
    if (wrap_so_handle == NULL) {
        printf("dlopen of %s failed: %s\n", wrapname, dlerror() );
        abort();
    }
    MPI_COMM_WORLD = MUK_DLSYM(wrap_so_handle,"IMPL_COMM_WORLD");

    // now we are hacking
    MUK_Abort = MUK_DLSYM(wrap_so_handle,"WRAP_Abort");
    MUK_Comm_rank = MUK_DLSYM(wrap_so_handle,"WRAP_Comm_rank");
    MUK_Comm_size = MUK_DLSYM(wrap_so_handle,"WRAP_Comm_size");
    MUK_Accumulate = MUK_DLSYM(wrap_so_handle, "WRAP_Accumulate");
    MUK_Accumulate_c = MUK_DLSYM(wrap_so_handle, "WRAP_Accumulate_c");
    MUK_Add_error_class = MUK_DLSYM(wrap_so_handle, "WRAP_Add_error_class");
    MUK_Add_error_code = MUK_DLSYM(wrap_so_handle, "WRAP_Add_error_code");
    MUK_Add_error_string = MUK_DLSYM(wrap_so_handle, "WRAP_Add_error_string");
    MUK_Address = MUK_DLSYM(wrap_so_handle, "WRAP_Address");
    MUK_Allgather = MUK_DLSYM(wrap_so_handle, "WRAP_Allgather");
    MUK_Allgather_c = MUK_DLSYM(wrap_so_handle, "WRAP_Allgather_c");
    MUK_Allgather_init = MUK_DLSYM(wrap_so_handle, "WRAP_Allgather_init");
    MUK_Allgather_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Allgather_init_c");
    MUK_Allgatherv = MUK_DLSYM(wrap_so_handle, "WRAP_Allgatherv");
    MUK_Allgatherv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Allgatherv_c");
    MUK_Allgatherv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Allgatherv_init");
    MUK_Allgatherv_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Allgatherv_init_c");
    MUK_Alloc_mem = MUK_DLSYM(wrap_so_handle, "WRAP_Alloc_mem");
    MUK_Allreduce = MUK_DLSYM(wrap_so_handle, "WRAP_Allreduce");
    MUK_Allreduce_c = MUK_DLSYM(wrap_so_handle, "WRAP_Allreduce_c");
    MUK_Allreduce_init = MUK_DLSYM(wrap_so_handle, "WRAP_Allreduce_init");
    MUK_Allreduce_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Allreduce_init_c");
    MUK_Alltoall = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoall");
    MUK_Alltoall_c = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoall_c");
    MUK_Alltoall_init = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoall_init");
    MUK_Alltoall_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoall_init_c");
    MUK_Alltoallv = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallv");
    MUK_Alltoallv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallv_c");
    MUK_Alltoallv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallv_init");
    MUK_Alltoallv_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallv_init_c");
    MUK_Alltoallw = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallw");
    MUK_Alltoallw_c = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallw_c");
    MUK_Alltoallw_init = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallw_init");
    MUK_Alltoallw_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallw_init_c");
    MUK_Attr_delete = MUK_DLSYM(wrap_so_handle, "WRAP_Attr_delete");
    MUK_Attr_get = MUK_DLSYM(wrap_so_handle, "WRAP_Attr_get");
    MUK_Attr_put = MUK_DLSYM(wrap_so_handle, "WRAP_Attr_put");
    MUK_Barrier = MUK_DLSYM(wrap_so_handle, "WRAP_Barrier");
    MUK_Barrier_init = MUK_DLSYM(wrap_so_handle, "WRAP_Barrier_init");
    MUK_Bcast = MUK_DLSYM(wrap_so_handle, "WRAP_Bcast");
    MUK_Bcast_c = MUK_DLSYM(wrap_so_handle, "WRAP_Bcast_c");
    MUK_Bcast_init = MUK_DLSYM(wrap_so_handle, "WRAP_Bcast_init");
    MUK_Bcast_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Bcast_init_c");
    MUK_Bsend = MUK_DLSYM(wrap_so_handle, "WRAP_Bsend");
    MUK_Bsend_c = MUK_DLSYM(wrap_so_handle, "WRAP_Bsend_c");
    MUK_Bsend_init = MUK_DLSYM(wrap_so_handle, "WRAP_Bsend_init");
    MUK_Bsend_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Bsend_init_c");
    MUK_Buffer_attach = MUK_DLSYM(wrap_so_handle, "WRAP_Buffer_attach");
    MUK_Buffer_attach_c = MUK_DLSYM(wrap_so_handle, "WRAP_Buffer_attach_c");
    MUK_Buffer_detach = MUK_DLSYM(wrap_so_handle, "WRAP_Buffer_detach");
    MUK_Buffer_detach_c = MUK_DLSYM(wrap_so_handle, "WRAP_Buffer_detach_c");
    MUK_Cancel = MUK_DLSYM(wrap_so_handle, "WRAP_Cancel");
    MUK_Cart_coords = MUK_DLSYM(wrap_so_handle, "WRAP_Cart_coords");
    MUK_Cart_create = MUK_DLSYM(wrap_so_handle, "WRAP_Cart_create");
    MUK_Cart_get = MUK_DLSYM(wrap_so_handle, "WRAP_Cart_get");
    MUK_Cart_map = MUK_DLSYM(wrap_so_handle, "WRAP_Cart_map");
    MUK_Cart_rank = MUK_DLSYM(wrap_so_handle, "WRAP_Cart_rank");
    MUK_Cart_shift = MUK_DLSYM(wrap_so_handle, "WRAP_Cart_shift");
    MUK_Cart_sub = MUK_DLSYM(wrap_so_handle, "WRAP_Cart_sub");
    MUK_Cartdim_get = MUK_DLSYM(wrap_so_handle, "WRAP_Cartdim_get");
    MUK_Close_port = MUK_DLSYM(wrap_so_handle, "WRAP_Close_port");
    MUK_Comm_accept = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_accept");
    MUK_Comm_call_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_call_errhandler");
    MUK_Comm_compare = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_compare");
    MUK_Comm_connect = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_connect");
    MUK_Comm_create = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_create");
    MUK_Comm_create_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_create_errhandler");
    MUK_Comm_create_from_group = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_create_from_group");
    MUK_Comm_create_group = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_create_group");
    MUK_Comm_create_keyval = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_create_keyval");
    MUK_Comm_delete_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_delete_attr");
    MUK_Comm_disconnect = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_disconnect");
    MUK_Comm_dup = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_dup");
    MUK_Comm_dup_with_info = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_dup_with_info");
    MUK_Comm_free = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_free");
    MUK_Comm_free_keyval = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_free_keyval");
    MUK_Comm_get_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_get_attr");
    MUK_Comm_get_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_get_errhandler");
    MUK_Comm_get_info = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_get_info");
    MUK_Comm_get_name = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_get_name");
    MUK_Comm_get_parent = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_get_parent");
    MUK_Comm_group = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_group");
    MUK_Comm_idup = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_idup");
    MUK_Comm_idup_with_info = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_idup_with_info");
    MUK_Comm_join = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_join");
    MUK_Comm_remote_group = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_remote_group");
    MUK_Comm_remote_size = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_remote_size");
    MUK_Comm_set_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_set_attr");
    MUK_Comm_set_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_set_errhandler");
    MUK_Comm_set_info = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_set_info");
    MUK_Comm_set_name = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_set_name");
    MUK_Comm_split = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_split");
    MUK_Comm_split_type = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_split_type");
    MUK_Comm_test_inter = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_test_inter");
    MUK_Compare_and_swap = MUK_DLSYM(wrap_so_handle, "WRAP_Compare_and_swap");
    MUK_Dims_create = MUK_DLSYM(wrap_so_handle, "WRAP_Dims_create");
    MUK_Dist_graph_create = MUK_DLSYM(wrap_so_handle, "WRAP_Dist_graph_create");
    MUK_Dist_graph_create_adjacent = MUK_DLSYM(wrap_so_handle, "WRAP_Dist_graph_create_adjacent");
    MUK_Dist_graph_neighbors = MUK_DLSYM(wrap_so_handle, "WRAP_Dist_graph_neighbors");
    MUK_Dist_graph_neighbors_count = MUK_DLSYM(wrap_so_handle, "WRAP_Dist_graph_neighbors_count");
    MUK_Errhandler_create = MUK_DLSYM(wrap_so_handle, "WRAP_Errhandler_create");
    MUK_Errhandler_free = MUK_DLSYM(wrap_so_handle, "WRAP_Errhandler_free");
    MUK_Errhandler_get = MUK_DLSYM(wrap_so_handle, "WRAP_Errhandler_get");
    MUK_Errhandler_set = MUK_DLSYM(wrap_so_handle, "WRAP_Errhandler_set");
    MUK_Error_class = MUK_DLSYM(wrap_so_handle, "WRAP_Error_class");
    MUK_Error_string = MUK_DLSYM(wrap_so_handle, "WRAP_Error_string");
    MUK_Exscan = MUK_DLSYM(wrap_so_handle, "WRAP_Exscan");
    MUK_Exscan_c = MUK_DLSYM(wrap_so_handle, "WRAP_Exscan_c");
    MUK_Exscan_init = MUK_DLSYM(wrap_so_handle, "WRAP_Exscan_init");
    MUK_Exscan_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Exscan_init_c");
    MUK_Fetch_and_op = MUK_DLSYM(wrap_so_handle, "WRAP_Fetch_and_op");
    MUK_File_call_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_File_call_errhandler");
    MUK_File_close = MUK_DLSYM(wrap_so_handle, "WRAP_File_close");
    MUK_File_create_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_File_create_errhandler");
    MUK_File_delete = MUK_DLSYM(wrap_so_handle, "WRAP_File_delete");
    MUK_File_get_amode = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_amode");
    MUK_File_get_atomicity = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_atomicity");
    MUK_File_get_byte_offset = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_byte_offset");
    MUK_File_get_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_errhandler");
    MUK_File_get_group = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_group");
    MUK_File_get_info = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_info");
    MUK_File_get_position = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_position");
    MUK_File_get_position_shared = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_position_shared");
    MUK_File_get_size = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_size");
    MUK_File_get_type_extent = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_type_extent");
    MUK_File_get_type_extent_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_type_extent_c");
    MUK_File_get_view = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_view");
    MUK_File_iread = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread");
    MUK_File_iread_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_all");
    MUK_File_iread_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_all_c");
    MUK_File_iread_at = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_at");
    MUK_File_iread_at_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_at_all");
    MUK_File_iread_at_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_at_all_c");
    MUK_File_iread_at_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_at_c");
    MUK_File_iread_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_c");
    MUK_File_iread_shared = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_shared");
    MUK_File_iread_shared_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_shared_c");
    MUK_File_iwrite = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite");
    MUK_File_iwrite_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_all");
    MUK_File_iwrite_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_all_c");
    MUK_File_iwrite_at = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_at");
    MUK_File_iwrite_at_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_at_all");
    MUK_File_iwrite_at_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_at_all_c");
    MUK_File_iwrite_at_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_at_c");
    MUK_File_iwrite_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_c");
    MUK_File_iwrite_shared = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_shared");
    MUK_File_iwrite_shared_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_shared_c");
    MUK_File_open = MUK_DLSYM(wrap_so_handle, "WRAP_File_open");
    MUK_File_preallocate = MUK_DLSYM(wrap_so_handle, "WRAP_File_preallocate");
    MUK_File_read = MUK_DLSYM(wrap_so_handle, "WRAP_File_read");
    MUK_File_read_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_all");
    MUK_File_read_all_begin = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_all_begin");
    MUK_File_read_all_begin_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_all_begin_c");
    MUK_File_read_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_all_c");
    MUK_File_read_all_end = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_all_end");
    MUK_File_read_at = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_at");
    MUK_File_read_at_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_at_all");
    MUK_File_read_at_all_begin = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_at_all_begin");
    MUK_File_read_at_all_begin_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_at_all_begin_c");
    MUK_File_read_at_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_at_all_c");
    MUK_File_read_at_all_end = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_at_all_end");
    MUK_File_read_at_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_at_c");
    MUK_File_read_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_c");
    MUK_File_read_ordered = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_ordered");
    MUK_File_read_ordered_begin = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_ordered_begin");
    MUK_File_read_ordered_begin_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_ordered_begin_c");
    MUK_File_read_ordered_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_ordered_c");
    MUK_File_read_ordered_end = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_ordered_end");
    MUK_File_read_shared = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_shared");
    MUK_File_read_shared_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_shared_c");
    MUK_File_seek = MUK_DLSYM(wrap_so_handle, "WRAP_File_seek");
    MUK_File_seek_shared = MUK_DLSYM(wrap_so_handle, "WRAP_File_seek_shared");
    MUK_File_set_atomicity = MUK_DLSYM(wrap_so_handle, "WRAP_File_set_atomicity");
    MUK_File_set_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_File_set_errhandler");
    MUK_File_set_info = MUK_DLSYM(wrap_so_handle, "WRAP_File_set_info");
    MUK_File_set_size = MUK_DLSYM(wrap_so_handle, "WRAP_File_set_size");
    MUK_File_set_view = MUK_DLSYM(wrap_so_handle, "WRAP_File_set_view");
    MUK_File_sync = MUK_DLSYM(wrap_so_handle, "WRAP_File_sync");
    MUK_File_write = MUK_DLSYM(wrap_so_handle, "WRAP_File_write");
    MUK_File_write_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_all");
    MUK_File_write_all_begin = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_all_begin");
    MUK_File_write_all_begin_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_all_begin_c");
    MUK_File_write_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_all_c");
    MUK_File_write_all_end = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_all_end");
    MUK_File_write_at = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_at");
    MUK_File_write_at_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_at_all");
    MUK_File_write_at_all_begin = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_at_all_begin");
    MUK_File_write_at_all_begin_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_at_all_begin_c");
    MUK_File_write_at_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_at_all_c");
    MUK_File_write_at_all_end = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_at_all_end");
    MUK_File_write_at_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_at_c");
    MUK_File_write_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_c");
    MUK_File_write_ordered = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_ordered");
    MUK_File_write_ordered_begin = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_ordered_begin");
    MUK_File_write_ordered_begin_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_ordered_begin_c");
    MUK_File_write_ordered_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_ordered_c");
    MUK_File_write_ordered_end = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_ordered_end");
    MUK_File_write_shared = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_shared");
    MUK_File_write_shared_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_shared_c");
    MUK_Free_mem = MUK_DLSYM(wrap_so_handle, "WRAP_Free_mem");
    MUK_Gather = MUK_DLSYM(wrap_so_handle, "WRAP_Gather");
    MUK_Gather_c = MUK_DLSYM(wrap_so_handle, "WRAP_Gather_c");
    MUK_Gather_init = MUK_DLSYM(wrap_so_handle, "WRAP_Gather_init");
    MUK_Gather_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Gather_init_c");
    MUK_Gatherv = MUK_DLSYM(wrap_so_handle, "WRAP_Gatherv");
    MUK_Gatherv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Gatherv_c");
    MUK_Gatherv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Gatherv_init");
    MUK_Gatherv_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Gatherv_init_c");
    MUK_Get = MUK_DLSYM(wrap_so_handle, "WRAP_Get");
    MUK_Get_accumulate = MUK_DLSYM(wrap_so_handle, "WRAP_Get_accumulate");
    MUK_Get_accumulate_c = MUK_DLSYM(wrap_so_handle, "WRAP_Get_accumulate_c");
    MUK_Get_address = MUK_DLSYM(wrap_so_handle, "WRAP_Get_address");
    MUK_Get_c = MUK_DLSYM(wrap_so_handle, "WRAP_Get_c");
    MUK_Get_count = MUK_DLSYM(wrap_so_handle, "WRAP_Get_count");
    MUK_Get_count_c = MUK_DLSYM(wrap_so_handle, "WRAP_Get_count_c");
    MUK_Get_elements = MUK_DLSYM(wrap_so_handle, "WRAP_Get_elements");
    MUK_Get_elements_c = MUK_DLSYM(wrap_so_handle, "WRAP_Get_elements_c");
    MUK_Get_elements_x = MUK_DLSYM(wrap_so_handle, "WRAP_Get_elements_x");
    MUK_Graph_create = MUK_DLSYM(wrap_so_handle, "WRAP_Graph_create");
    MUK_Graph_get = MUK_DLSYM(wrap_so_handle, "WRAP_Graph_get");
    MUK_Graph_map = MUK_DLSYM(wrap_so_handle, "WRAP_Graph_map");
    MUK_Graph_neighbors = MUK_DLSYM(wrap_so_handle, "WRAP_Graph_neighbors");
    MUK_Graph_neighbors_count = MUK_DLSYM(wrap_so_handle, "WRAP_Graph_neighbors_count");
    MUK_Graphdims_get = MUK_DLSYM(wrap_so_handle, "WRAP_Graphdims_get");
    MUK_Grequest_complete = MUK_DLSYM(wrap_so_handle, "WRAP_Grequest_complete");
    MUK_Grequest_start = MUK_DLSYM(wrap_so_handle, "WRAP_Grequest_start");
    MUK_Group_compare = MUK_DLSYM(wrap_so_handle, "WRAP_Group_compare");
    MUK_Group_difference = MUK_DLSYM(wrap_so_handle, "WRAP_Group_difference");
    MUK_Group_excl = MUK_DLSYM(wrap_so_handle, "WRAP_Group_excl");
    MUK_Group_free = MUK_DLSYM(wrap_so_handle, "WRAP_Group_free");
    MUK_Group_from_session_pset = MUK_DLSYM(wrap_so_handle, "WRAP_Group_from_session_pset");
    MUK_Group_incl = MUK_DLSYM(wrap_so_handle, "WRAP_Group_incl");
    MUK_Group_intersection = MUK_DLSYM(wrap_so_handle, "WRAP_Group_intersection");
    MUK_Group_range_excl = MUK_DLSYM(wrap_so_handle, "WRAP_Group_range_excl");
    MUK_Group_range_incl = MUK_DLSYM(wrap_so_handle, "WRAP_Group_range_incl");
    MUK_Group_rank = MUK_DLSYM(wrap_so_handle, "WRAP_Group_rank");
    MUK_Group_size = MUK_DLSYM(wrap_so_handle, "WRAP_Group_size");
    MUK_Group_translate_ranks = MUK_DLSYM(wrap_so_handle, "WRAP_Group_translate_ranks");
    MUK_Group_union = MUK_DLSYM(wrap_so_handle, "WRAP_Group_union");
    MUK_Iallgather = MUK_DLSYM(wrap_so_handle, "WRAP_Iallgather");
    MUK_Iallgather_c = MUK_DLSYM(wrap_so_handle, "WRAP_Iallgather_c");
    MUK_Iallgatherv = MUK_DLSYM(wrap_so_handle, "WRAP_Iallgatherv");
    MUK_Iallgatherv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Iallgatherv_c");
    MUK_Iallreduce = MUK_DLSYM(wrap_so_handle, "WRAP_Iallreduce");
    MUK_Iallreduce_c = MUK_DLSYM(wrap_so_handle, "WRAP_Iallreduce_c");
    MUK_Ialltoall = MUK_DLSYM(wrap_so_handle, "WRAP_Ialltoall");
    MUK_Ialltoall_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ialltoall_c");
    MUK_Ialltoallv = MUK_DLSYM(wrap_so_handle, "WRAP_Ialltoallv");
    MUK_Ialltoallv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ialltoallv_c");
    MUK_Ialltoallw = MUK_DLSYM(wrap_so_handle, "WRAP_Ialltoallw");
    MUK_Ialltoallw_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ialltoallw_c");
    MUK_Ibarrier = MUK_DLSYM(wrap_so_handle, "WRAP_Ibarrier");
    MUK_Ibcast = MUK_DLSYM(wrap_so_handle, "WRAP_Ibcast");
    MUK_Ibcast_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ibcast_c");
    MUK_Ibsend = MUK_DLSYM(wrap_so_handle, "WRAP_Ibsend");
    MUK_Ibsend_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ibsend_c");
    MUK_Iexscan = MUK_DLSYM(wrap_so_handle, "WRAP_Iexscan");
    MUK_Iexscan_c = MUK_DLSYM(wrap_so_handle, "WRAP_Iexscan_c");
    MUK_Igather = MUK_DLSYM(wrap_so_handle, "WRAP_Igather");
    MUK_Igather_c = MUK_DLSYM(wrap_so_handle, "WRAP_Igather_c");
    MUK_Igatherv = MUK_DLSYM(wrap_so_handle, "WRAP_Igatherv");
    MUK_Igatherv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Igatherv_c");
    MUK_Improbe = MUK_DLSYM(wrap_so_handle, "WRAP_Improbe");
    MUK_Imrecv = MUK_DLSYM(wrap_so_handle, "WRAP_Imrecv");
    MUK_Imrecv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Imrecv_c");
    MUK_Ineighbor_allgather = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_allgather");
    MUK_Ineighbor_allgather_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_allgather_c");
    MUK_Ineighbor_allgatherv = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_allgatherv");
    MUK_Ineighbor_allgatherv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_allgatherv_c");
    MUK_Ineighbor_alltoall = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_alltoall");
    MUK_Ineighbor_alltoall_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_alltoall_c");
    MUK_Ineighbor_alltoallv = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_alltoallv");
    MUK_Ineighbor_alltoallv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_alltoallv_c");
    MUK_Ineighbor_alltoallw = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_alltoallw");
    MUK_Ineighbor_alltoallw_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_alltoallw_c");
    MUK_Info_create = MUK_DLSYM(wrap_so_handle, "WRAP_Info_create");
    MUK_Info_create_env = MUK_DLSYM(wrap_so_handle, "WRAP_Info_create_env");
    MUK_Info_delete = MUK_DLSYM(wrap_so_handle, "WRAP_Info_delete");
    MUK_Info_dup = MUK_DLSYM(wrap_so_handle, "WRAP_Info_dup");
    MUK_Info_free = MUK_DLSYM(wrap_so_handle, "WRAP_Info_free");
    MUK_Info_get = MUK_DLSYM(wrap_so_handle, "WRAP_Info_get");
    MUK_Info_get_nkeys = MUK_DLSYM(wrap_so_handle, "WRAP_Info_get_nkeys");
    MUK_Info_get_nthkey = MUK_DLSYM(wrap_so_handle, "WRAP_Info_get_nthkey");
    MUK_Info_get_string = MUK_DLSYM(wrap_so_handle, "WRAP_Info_get_string");
    MUK_Info_get_valuelen = MUK_DLSYM(wrap_so_handle, "WRAP_Info_get_valuelen");
    MUK_Info_set = MUK_DLSYM(wrap_so_handle, "WRAP_Info_set");
    MUK_Intercomm_create = MUK_DLSYM(wrap_so_handle, "WRAP_Intercomm_create");
    MUK_Intercomm_create_from_groups = MUK_DLSYM(wrap_so_handle, "WRAP_Intercomm_create_from_groups");
    MUK_Intercomm_merge = MUK_DLSYM(wrap_so_handle, "WRAP_Intercomm_merge");
    MUK_Iprobe = MUK_DLSYM(wrap_so_handle, "WRAP_Iprobe");
    MUK_Irecv = MUK_DLSYM(wrap_so_handle, "WRAP_Irecv");
    MUK_Irecv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Irecv_c");
    MUK_Ireduce = MUK_DLSYM(wrap_so_handle, "WRAP_Ireduce");
    MUK_Ireduce_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ireduce_c");
    MUK_Ireduce_scatter = MUK_DLSYM(wrap_so_handle, "WRAP_Ireduce_scatter");
    MUK_Ireduce_scatter_block = MUK_DLSYM(wrap_so_handle, "WRAP_Ireduce_scatter_block");
    MUK_Ireduce_scatter_block_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ireduce_scatter_block_c");
    MUK_Ireduce_scatter_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ireduce_scatter_c");
    MUK_Irsend = MUK_DLSYM(wrap_so_handle, "WRAP_Irsend");
    MUK_Irsend_c = MUK_DLSYM(wrap_so_handle, "WRAP_Irsend_c");
    MUK_Iscan = MUK_DLSYM(wrap_so_handle, "WRAP_Iscan");
    MUK_Iscan_c = MUK_DLSYM(wrap_so_handle, "WRAP_Iscan_c");
    MUK_Iscatter = MUK_DLSYM(wrap_so_handle, "WRAP_Iscatter");
    MUK_Iscatter_c = MUK_DLSYM(wrap_so_handle, "WRAP_Iscatter_c");
    MUK_Iscatterv = MUK_DLSYM(wrap_so_handle, "WRAP_Iscatterv");
    MUK_Iscatterv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Iscatterv_c");
    MUK_Isend = MUK_DLSYM(wrap_so_handle, "WRAP_Isend");
    MUK_Isend_c = MUK_DLSYM(wrap_so_handle, "WRAP_Isend_c");
    MUK_Isendrecv = MUK_DLSYM(wrap_so_handle, "WRAP_Isendrecv");
    MUK_Isendrecv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Isendrecv_c");
    MUK_Isendrecv_replace = MUK_DLSYM(wrap_so_handle, "WRAP_Isendrecv_replace");
    MUK_Isendrecv_replace_c = MUK_DLSYM(wrap_so_handle, "WRAP_Isendrecv_replace_c");
    MUK_Issend = MUK_DLSYM(wrap_so_handle, "WRAP_Issend");
    MUK_Issend_c = MUK_DLSYM(wrap_so_handle, "WRAP_Issend_c");
#if 0
    MUK_Keyval_create = MUK_DLSYM(wrap_so_handle, "WRAP_Keyval_create");
    MUK_Keyval_free = MUK_DLSYM(wrap_so_handle, "WRAP_Keyval_free");
#endif
    MUK_Lookup_name = MUK_DLSYM(wrap_so_handle, "WRAP_Lookup_name");
    MUK_Mprobe = MUK_DLSYM(wrap_so_handle, "WRAP_Mprobe");
    MUK_Mrecv = MUK_DLSYM(wrap_so_handle, "WRAP_Mrecv");
    MUK_Mrecv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Mrecv_c");
    MUK_Neighbor_allgather = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgather");
    MUK_Neighbor_allgather_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgather_c");
    MUK_Neighbor_allgather_init = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgather_init");
    MUK_Neighbor_allgather_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgather_init_c");
    MUK_Neighbor_allgatherv = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgatherv");
    MUK_Neighbor_allgatherv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgatherv_c");
    MUK_Neighbor_allgatherv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgatherv_init");
    MUK_Neighbor_allgatherv_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgatherv_init_c");
    MUK_Neighbor_alltoall = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoall");
    MUK_Neighbor_alltoall_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoall_c");
    MUK_Neighbor_alltoall_init = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoall_init");
    MUK_Neighbor_alltoall_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoall_init_c");
    MUK_Neighbor_alltoallv = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallv");
    MUK_Neighbor_alltoallv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallv_c");
    MUK_Neighbor_alltoallv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallv_init");
    MUK_Neighbor_alltoallv_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallv_init_c");
    MUK_Neighbor_alltoallw = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallw");
    MUK_Neighbor_alltoallw_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallw_c");
    MUK_Neighbor_alltoallw_init = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallw_init");
    MUK_Neighbor_alltoallw_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallw_init_c");
    MUK_Op_commutative = MUK_DLSYM(wrap_so_handle, "WRAP_Op_commutative");
    MUK_Op_create = MUK_DLSYM(wrap_so_handle, "WRAP_Op_create");
    MUK_Op_create_c = MUK_DLSYM(wrap_so_handle, "WRAP_Op_create_c");
    MUK_Op_free = MUK_DLSYM(wrap_so_handle, "WRAP_Op_free");
    MUK_Open_port = MUK_DLSYM(wrap_so_handle, "WRAP_Open_port");
    MUK_Pack = MUK_DLSYM(wrap_so_handle, "WRAP_Pack");
    MUK_Pack_c = MUK_DLSYM(wrap_so_handle, "WRAP_Pack_c");
    MUK_Pack_external = MUK_DLSYM(wrap_so_handle, "WRAP_Pack_external");
    MUK_Pack_external_c = MUK_DLSYM(wrap_so_handle, "WRAP_Pack_external_c");
    MUK_Pack_external_size = MUK_DLSYM(wrap_so_handle, "WRAP_Pack_external_size");
    MUK_Pack_external_size_c = MUK_DLSYM(wrap_so_handle, "WRAP_Pack_external_size_c");
    MUK_Pack_size = MUK_DLSYM(wrap_so_handle, "WRAP_Pack_size");
    MUK_Pack_size_c = MUK_DLSYM(wrap_so_handle, "WRAP_Pack_size_c");
    MUK_Parrived = MUK_DLSYM(wrap_so_handle, "WRAP_Parrived");
    MUK_Pcontrol = MUK_DLSYM(wrap_so_handle, "WRAP_Pcontrol");
    MUK_Pready = MUK_DLSYM(wrap_so_handle, "WRAP_Pready");
    MUK_Pready_list = MUK_DLSYM(wrap_so_handle, "WRAP_Pready_list");
    MUK_Pready_range = MUK_DLSYM(wrap_so_handle, "WRAP_Pready_range");
    MUK_Precv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Precv_init");
    MUK_Probe = MUK_DLSYM(wrap_so_handle, "WRAP_Probe");
    MUK_Psend_init = MUK_DLSYM(wrap_so_handle, "WRAP_Psend_init");
    MUK_Publish_name = MUK_DLSYM(wrap_so_handle, "WRAP_Publish_name");
    MUK_Put = MUK_DLSYM(wrap_so_handle, "WRAP_Put");
    MUK_Put_c = MUK_DLSYM(wrap_so_handle, "WRAP_Put_c");
    MUK_Raccumulate = MUK_DLSYM(wrap_so_handle, "WRAP_Raccumulate");
    MUK_Raccumulate_c = MUK_DLSYM(wrap_so_handle, "WRAP_Raccumulate_c");
    MUK_Recv = MUK_DLSYM(wrap_so_handle, "WRAP_Recv");
    MUK_Recv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Recv_c");
    MUK_Recv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Recv_init");
    MUK_Recv_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Recv_init_c");
    MUK_Reduce = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce");
    MUK_Reduce_c = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_c");
    MUK_Reduce_init = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_init");
    MUK_Reduce_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_init_c");
    MUK_Reduce_local = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_local");
    MUK_Reduce_local_c = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_local_c");
    MUK_Reduce_scatter = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter");
    MUK_Reduce_scatter_block = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter_block");
    MUK_Reduce_scatter_block_c = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter_block_c");
    MUK_Reduce_scatter_block_init = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter_block_init");
    MUK_Reduce_scatter_block_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter_block_init_c");
    MUK_Reduce_scatter_c = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter_c");
    MUK_Reduce_scatter_init = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter_init");
    MUK_Reduce_scatter_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter_init_c");
    MUK_Register_datarep = MUK_DLSYM(wrap_so_handle, "WRAP_Register_datarep");
    MUK_Register_datarep_c = MUK_DLSYM(wrap_so_handle, "WRAP_Register_datarep_c");
    MUK_Request_free = MUK_DLSYM(wrap_so_handle, "WRAP_Request_free");
    MUK_Request_get_status = MUK_DLSYM(wrap_so_handle, "WRAP_Request_get_status");
    MUK_Rget = MUK_DLSYM(wrap_so_handle, "WRAP_Rget");
    MUK_Rget_accumulate = MUK_DLSYM(wrap_so_handle, "WRAP_Rget_accumulate");
    MUK_Rget_accumulate_c = MUK_DLSYM(wrap_so_handle, "WRAP_Rget_accumulate_c");
    MUK_Rget_c = MUK_DLSYM(wrap_so_handle, "WRAP_Rget_c");
    MUK_Rput = MUK_DLSYM(wrap_so_handle, "WRAP_Rput");
    MUK_Rput_c = MUK_DLSYM(wrap_so_handle, "WRAP_Rput_c");
    MUK_Rsend = MUK_DLSYM(wrap_so_handle, "WRAP_Rsend");
    MUK_Rsend_c = MUK_DLSYM(wrap_so_handle, "WRAP_Rsend_c");
    MUK_Rsend_init = MUK_DLSYM(wrap_so_handle, "WRAP_Rsend_init");
    MUK_Rsend_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Rsend_init_c");
    MUK_Scan = MUK_DLSYM(wrap_so_handle, "WRAP_Scan");
    MUK_Scan_c = MUK_DLSYM(wrap_so_handle, "WRAP_Scan_c");
    MUK_Scan_init = MUK_DLSYM(wrap_so_handle, "WRAP_Scan_init");
    MUK_Scan_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Scan_init_c");
    MUK_Scatter = MUK_DLSYM(wrap_so_handle, "WRAP_Scatter");
    MUK_Scatter_c = MUK_DLSYM(wrap_so_handle, "WRAP_Scatter_c");
    MUK_Scatter_init = MUK_DLSYM(wrap_so_handle, "WRAP_Scatter_init");
    MUK_Scatter_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Scatter_init_c");
    MUK_Scatterv = MUK_DLSYM(wrap_so_handle, "WRAP_Scatterv");
    MUK_Scatterv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Scatterv_c");
    MUK_Scatterv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Scatterv_init");
    MUK_Scatterv_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Scatterv_init_c");
    MUK_Send = MUK_DLSYM(wrap_so_handle, "WRAP_Send");
    MUK_Send_c = MUK_DLSYM(wrap_so_handle, "WRAP_Send_c");
    MUK_Send_init = MUK_DLSYM(wrap_so_handle, "WRAP_Send_init");
    MUK_Send_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Send_init_c");
    MUK_Sendrecv = MUK_DLSYM(wrap_so_handle, "WRAP_Sendrecv");
    MUK_Sendrecv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Sendrecv_c");
    MUK_Sendrecv_replace = MUK_DLSYM(wrap_so_handle, "WRAP_Sendrecv_replace");
    MUK_Sendrecv_replace_c = MUK_DLSYM(wrap_so_handle, "WRAP_Sendrecv_replace_c");
    MUK_Session_call_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Session_call_errhandler");
    MUK_Session_create_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Session_create_errhandler");
    MUK_Session_finalize = MUK_DLSYM(wrap_so_handle, "WRAP_Session_finalize");
    MUK_Session_get_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Session_get_errhandler");
    MUK_Session_get_info = MUK_DLSYM(wrap_so_handle, "WRAP_Session_get_info");
    MUK_Session_get_nth_pset = MUK_DLSYM(wrap_so_handle, "WRAP_Session_get_nth_pset");
    MUK_Session_get_num_psets = MUK_DLSYM(wrap_so_handle, "WRAP_Session_get_num_psets");
    MUK_Session_get_pset_info = MUK_DLSYM(wrap_so_handle, "WRAP_Session_get_pset_info");
    MUK_Session_init = MUK_DLSYM(wrap_so_handle, "WRAP_Session_init");
    MUK_Session_set_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Session_set_errhandler");
    MUK_Ssend = MUK_DLSYM(wrap_so_handle, "WRAP_Ssend");
    MUK_Ssend_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ssend_c");
    MUK_Ssend_init = MUK_DLSYM(wrap_so_handle, "WRAP_Ssend_init");
    MUK_Ssend_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ssend_init_c");
    MUK_Start = MUK_DLSYM(wrap_so_handle, "WRAP_Start");
    MUK_Startall = MUK_DLSYM(wrap_so_handle, "WRAP_Startall");
#ifdef SUPPORT_F08
    MUK_Status_f082c = MUK_DLSYM(wrap_so_handle, "WRAP_Status_f082c");
    MUK_Status_f082f = MUK_DLSYM(wrap_so_handle, "WRAP_Status_f082f");
    MUK_Status_f2f08 = MUK_DLSYM(wrap_so_handle, "WRAP_Status_f2f08");
#endif
    MUK_Status_set_cancelled = MUK_DLSYM(wrap_so_handle, "WRAP_Status_set_cancelled");
    MUK_Status_set_elements = MUK_DLSYM(wrap_so_handle, "WRAP_Status_set_elements");
    MUK_Status_set_elements_c = MUK_DLSYM(wrap_so_handle, "WRAP_Status_set_elements_c");
    MUK_Status_set_elements_x = MUK_DLSYM(wrap_so_handle, "WRAP_Status_set_elements_x");
    MUK_Test = MUK_DLSYM(wrap_so_handle, "WRAP_Test");
    MUK_Test_cancelled = MUK_DLSYM(wrap_so_handle, "WRAP_Test_cancelled");
    MUK_Testall = MUK_DLSYM(wrap_so_handle, "WRAP_Testall");
    MUK_Testany = MUK_DLSYM(wrap_so_handle, "WRAP_Testany");
    MUK_Testsome = MUK_DLSYM(wrap_so_handle, "WRAP_Testsome");
    MUK_Topo_test = MUK_DLSYM(wrap_so_handle, "WRAP_Topo_test");
    MUK_Type_commit = MUK_DLSYM(wrap_so_handle, "WRAP_Type_commit");
    MUK_Type_contiguous = MUK_DLSYM(wrap_so_handle, "WRAP_Type_contiguous");
    MUK_Type_contiguous_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_contiguous_c");
    MUK_Type_create_darray = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_darray");
    MUK_Type_create_darray_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_darray_c");
    MUK_Type_create_f90_complex = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_f90_complex");
    MUK_Type_create_f90_integer = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_f90_integer");
    MUK_Type_create_f90_real = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_f90_real");
    MUK_Type_create_hindexed = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_hindexed");
    MUK_Type_create_hindexed_block = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_hindexed_block");
    MUK_Type_create_hindexed_block_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_hindexed_block_c");
    MUK_Type_create_hindexed_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_hindexed_c");
    MUK_Type_create_hvector = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_hvector");
    MUK_Type_create_hvector_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_hvector_c");
    MUK_Type_create_indexed_block = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_indexed_block");
    MUK_Type_create_indexed_block_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_indexed_block_c");
    MUK_Type_create_keyval = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_keyval");
    MUK_Type_create_resized = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_resized");
    MUK_Type_create_resized_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_resized_c");
    MUK_Type_create_struct = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_struct");
    MUK_Type_create_struct_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_struct_c");
    MUK_Type_create_subarray = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_subarray");
    MUK_Type_create_subarray_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_subarray_c");
    MUK_Type_delete_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Type_delete_attr");
    MUK_Type_dup = MUK_DLSYM(wrap_so_handle, "WRAP_Type_dup");
    MUK_Type_extent = MUK_DLSYM(wrap_so_handle, "WRAP_Type_extent");
    MUK_Type_free = MUK_DLSYM(wrap_so_handle, "WRAP_Type_free");
    MUK_Type_free_keyval = MUK_DLSYM(wrap_so_handle, "WRAP_Type_free_keyval");
    MUK_Type_get_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_attr");
    MUK_Type_get_contents = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_contents");
    MUK_Type_get_contents_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_contents_c");
    MUK_Type_get_envelope = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_envelope");
    MUK_Type_get_envelope_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_envelope_c");
    MUK_Type_get_extent = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_extent");
    MUK_Type_get_extent_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_extent_c");
    MUK_Type_get_extent_x = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_extent_x");
    MUK_Type_get_name = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_name");
    MUK_Type_get_true_extent = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_true_extent");
    MUK_Type_get_true_extent_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_true_extent_c");
    MUK_Type_get_true_extent_x = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_true_extent_x");
    MUK_Type_hindexed = MUK_DLSYM(wrap_so_handle, "WRAP_Type_hindexed");
    MUK_Type_hvector = MUK_DLSYM(wrap_so_handle, "WRAP_Type_hvector");
    MUK_Type_indexed = MUK_DLSYM(wrap_so_handle, "WRAP_Type_indexed");
    MUK_Type_indexed_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_indexed_c");
    MUK_Type_lb = MUK_DLSYM(wrap_so_handle, "WRAP_Type_lb");
    MUK_Type_match_size = MUK_DLSYM(wrap_so_handle, "WRAP_Type_match_size");
    MUK_Type_set_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Type_set_attr");
    MUK_Type_set_name = MUK_DLSYM(wrap_so_handle, "WRAP_Type_set_name");
    MUK_Type_size = MUK_DLSYM(wrap_so_handle, "WRAP_Type_size");
    MUK_Type_size_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_size_c");
    MUK_Type_size_x = MUK_DLSYM(wrap_so_handle, "WRAP_Type_size_x");
    MUK_Type_struct = MUK_DLSYM(wrap_so_handle, "WRAP_Type_struct");
    MUK_Type_ub = MUK_DLSYM(wrap_so_handle, "WRAP_Type_ub");
    MUK_Type_vector = MUK_DLSYM(wrap_so_handle, "WRAP_Type_vector");
    MUK_Type_vector_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_vector_c");
    MUK_Unpack = MUK_DLSYM(wrap_so_handle, "WRAP_Unpack");
    MUK_Unpack_c = MUK_DLSYM(wrap_so_handle, "WRAP_Unpack_c");
    MUK_Unpack_external = MUK_DLSYM(wrap_so_handle, "WRAP_Unpack_external");
    MUK_Unpack_external_c = MUK_DLSYM(wrap_so_handle, "WRAP_Unpack_external_c");
    MUK_Unpublish_name = MUK_DLSYM(wrap_so_handle, "WRAP_Unpublish_name");
    MUK_Wait = MUK_DLSYM(wrap_so_handle, "WRAP_Wait");
    MUK_Waitall = MUK_DLSYM(wrap_so_handle, "WRAP_Waitall");
    MUK_Waitany = MUK_DLSYM(wrap_so_handle, "WRAP_Waitany");
    MUK_Waitsome = MUK_DLSYM(wrap_so_handle, "WRAP_Waitsome");
    MUK_Win_allocate = MUK_DLSYM(wrap_so_handle, "WRAP_Win_allocate");
    MUK_Win_allocate_c = MUK_DLSYM(wrap_so_handle, "WRAP_Win_allocate_c");
    MUK_Win_allocate_shared = MUK_DLSYM(wrap_so_handle, "WRAP_Win_allocate_shared");
    MUK_Win_allocate_shared_c = MUK_DLSYM(wrap_so_handle, "WRAP_Win_allocate_shared_c");
    MUK_Win_attach = MUK_DLSYM(wrap_so_handle, "WRAP_Win_attach");
    MUK_Win_call_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Win_call_errhandler");
    MUK_Win_complete = MUK_DLSYM(wrap_so_handle, "WRAP_Win_complete");
    MUK_Win_create = MUK_DLSYM(wrap_so_handle, "WRAP_Win_create");
    MUK_Win_create_c = MUK_DLSYM(wrap_so_handle, "WRAP_Win_create_c");
    MUK_Win_create_dynamic = MUK_DLSYM(wrap_so_handle, "WRAP_Win_create_dynamic");
    MUK_Win_create_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Win_create_errhandler");
    MUK_Win_create_keyval = MUK_DLSYM(wrap_so_handle, "WRAP_Win_create_keyval");
    MUK_Win_delete_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Win_delete_attr");
    MUK_Win_detach = MUK_DLSYM(wrap_so_handle, "WRAP_Win_detach");
    MUK_Win_fence = MUK_DLSYM(wrap_so_handle, "WRAP_Win_fence");
    MUK_Win_flush = MUK_DLSYM(wrap_so_handle, "WRAP_Win_flush");
    MUK_Win_flush_all = MUK_DLSYM(wrap_so_handle, "WRAP_Win_flush_all");
    MUK_Win_flush_local = MUK_DLSYM(wrap_so_handle, "WRAP_Win_flush_local");
    MUK_Win_flush_local_all = MUK_DLSYM(wrap_so_handle, "WRAP_Win_flush_local_all");
    MUK_Win_free = MUK_DLSYM(wrap_so_handle, "WRAP_Win_free");
    MUK_Win_free_keyval = MUK_DLSYM(wrap_so_handle, "WRAP_Win_free_keyval");
    MUK_Win_get_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Win_get_attr");
    MUK_Win_get_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Win_get_errhandler");
    MUK_Win_get_group = MUK_DLSYM(wrap_so_handle, "WRAP_Win_get_group");
    MUK_Win_get_info = MUK_DLSYM(wrap_so_handle, "WRAP_Win_get_info");
    MUK_Win_get_name = MUK_DLSYM(wrap_so_handle, "WRAP_Win_get_name");
    MUK_Win_lock = MUK_DLSYM(wrap_so_handle, "WRAP_Win_lock");
    MUK_Win_lock_all = MUK_DLSYM(wrap_so_handle, "WRAP_Win_lock_all");
    MUK_Win_post = MUK_DLSYM(wrap_so_handle, "WRAP_Win_post");
    MUK_Win_set_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Win_set_attr");
    MUK_Win_set_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Win_set_errhandler");
    MUK_Win_set_info = MUK_DLSYM(wrap_so_handle, "WRAP_Win_set_info");
    MUK_Win_set_name = MUK_DLSYM(wrap_so_handle, "WRAP_Win_set_name");
    MUK_Win_shared_query = MUK_DLSYM(wrap_so_handle, "WRAP_Win_shared_query");
    MUK_Win_shared_query_c = MUK_DLSYM(wrap_so_handle, "WRAP_Win_shared_query_c");
    MUK_Win_start = MUK_DLSYM(wrap_so_handle, "WRAP_Win_start");
    MUK_Win_sync = MUK_DLSYM(wrap_so_handle, "WRAP_Win_sync");
    MUK_Win_test = MUK_DLSYM(wrap_so_handle, "WRAP_Win_test");
    MUK_Win_unlock = MUK_DLSYM(wrap_so_handle, "WRAP_Win_unlock");
    MUK_Win_unlock_all = MUK_DLSYM(wrap_so_handle, "WRAP_Win_unlock_all");
    MUK_Win_wait = MUK_DLSYM(wrap_so_handle, "WRAP_Win_wait");


    WRAP_Load_functions = MUK_DLSYM(wrap_so_handle,"WRAP_Load_functions");
    rc = WRAP_Load_functions(h,major,minor);

    return rc;
}

int MPI_Init(int * argc, char *** argv)
{
    return MUK_Alkaa(argc,argv,-1,NULL);
}

int MPI_Init_thread(int * argc, char *** argv, int requested, int * provided)
{
    return MUK_Alkaa(argc,argv,requested,provided);
}

int MPI_Get_library_version(char *version, int *resultlen)
{
    return MUK_Get_library_version(version, resultlen);
}

int MPI_Finalize(void)
{
    return MUK_Finalize();
}

int MPI_Finalized(int * flag)
{
    return MUK_Finalized(flag);
}

int MPI_Initialized(int * flag)
{
    return MUK_Initialized(flag);
}

int MPI_Is_thread_main(int * flag)
{
    return MUK_Is_thread_main(flag);
}

int MPI_Query_thread(int * provided)
{
    return MUK_Query_thread(provided);
}

int MPI_Get_processor_name(char *name, int *resultlen)
{
    return MUK_Get_processor_name(name, resultlen);
}

int MPI_Get_version(int * major, int * minor)
{
    return MUK_Get_version(major, minor);
}

int MPI_Abort(MUK_Comm comm, int errorcode)
{
    return MUK_Abort(comm, errorcode);
}

int MPI_Comm_rank(MUK_Comm comm, int * rank)
{
    return MUK_Comm_rank(comm, rank);
}

int MPI_Comm_size(MUK_Comm comm, int * size)
{
    return MUK_Comm_size(comm, size);
}

int MPI_Accumulate(const void *origin_addr, int origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win)
{
    return MUK_Accumulate(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
}

int MPI_Accumulate_c(const void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win)
{
    return MUK_Accumulate_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
}

int MPI_Add_error_class(int *errorclass)
{
    return MUK_Add_error_class(errorclass);
}

int MPI_Add_error_code(int errorclass, int *errorcode)
{
    return MUK_Add_error_code(errorclass, errorcode);
}

int MPI_Add_error_string(int errorcode, const char *string)
{
    return MUK_Add_error_string(errorcode, string);
}

int MPI_Address(void *location, MUK_Aint *address)
{
    return MUK_Address(location, address);
}

int MPI_Allgather(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Allgather_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Allgather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Allgather_init(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Allgather_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Allgather_init_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Allgather_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Allgatherv(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
}

int MPI_Allgatherv_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Allgatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
}

int MPI_Allgatherv_init(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Allgatherv_init(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, info, request);
}

int MPI_Allgatherv_init_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Allgatherv_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, info, request);
}

int MPI_Alloc_mem(MUK_Aint size, MUK_Info info, void *baseptr)
{
    return MUK_Alloc_mem(size, info, baseptr);
}

int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm)
{
    return MUK_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);
}

int MPI_Allreduce_c(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm)
{
    return MUK_Allreduce_c(sendbuf, recvbuf, count, datatype, op, comm);
}

int MPI_Allreduce_init(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Allreduce_init(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int MPI_Allreduce_init_c(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Allreduce_init_c(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int MPI_Alltoall(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Alltoall_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Alltoall_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Alltoall_init(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Alltoall_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Alltoall_init_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Alltoall_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}

int MPI_Alltoallv_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Alltoallv_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}

int MPI_Alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Alltoallv_init(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, info, request);
}

int MPI_Alltoallv_init_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Alltoallv_init_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, info, request);
}

int MPI_Alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm)
{
    return MUK_Alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
}

int MPI_Alltoallw_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm)
{
    return MUK_Alltoallw_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
}

int MPI_Alltoallw_init(const void *sendbuf, const int sendcounts[], const int sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Alltoallw_init(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, info, request);
}

int MPI_Alltoallw_init_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Alltoallw_init_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, info, request);
}

int MPI_Attr_delete(MUK_Comm comm, int keyval)
{
    return MUK_Attr_delete(comm, keyval);
}

int MPI_Attr_get(MUK_Comm comm, int keyval, void *attribute_val, int *flag)
{
    return MUK_Attr_get(comm, keyval, attribute_val, flag);
}

int MPI_Attr_put(MUK_Comm comm, int keyval, void *attribute_val)
{
    return MUK_Attr_put(comm, keyval, attribute_val);
}

int MPI_Barrier(MUK_Comm comm)
{
    return MUK_Barrier(comm);
}

int MPI_Barrier_init(MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Barrier_init(comm, info, request);
}

int MPI_Bcast(void *buffer, int count, MUK_Datatype datatype, int root, MUK_Comm comm)
{
    return MUK_Bcast(buffer, count, datatype, root, comm);
}

int MPI_Bcast_c(void *buffer, MUK_Count count, MUK_Datatype datatype, int root, MUK_Comm comm)
{
    return MUK_Bcast_c(buffer, count, datatype, root, comm);
}

int MPI_Bcast_init(void *buffer, int count, MUK_Datatype datatype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Bcast_init(buffer, count, datatype, root, comm, info, request);
}

int MPI_Bcast_init_c(void *buffer, MUK_Count count, MUK_Datatype datatype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Bcast_init_c(buffer, count, datatype, root, comm, info, request);
}

int MPI_Bsend(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm)
{
    return MUK_Bsend(buf, count, datatype, dest, tag, comm);
}

int MPI_Bsend_c(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm)
{
    return MUK_Bsend_c(buf, count, datatype, dest, tag, comm);
}

int MPI_Bsend_init(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Bsend_init(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Bsend_init_c(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Bsend_init_c(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Buffer_attach(void *buffer, int size)
{
    return MUK_Buffer_attach(buffer, size);
}

int MPI_Buffer_attach_c(void *buffer, MUK_Count size)
{
    return MUK_Buffer_attach_c(buffer, size);
}

int MPI_Buffer_detach(void *buffer_addr, int *size)
{
    return MUK_Buffer_detach(buffer_addr, size);
}

int MPI_Buffer_detach_c(void *buffer_addr, MUK_Count *size)
{
    return MUK_Buffer_detach_c(buffer_addr, size);
}

int MPI_Cancel(MUK_Request *request)
{
    return MUK_Cancel(request);
}

int MPI_Cart_coords(MUK_Comm comm, int rank, int maxdims, int coords[])
{
    return MUK_Cart_coords(comm, rank, maxdims, coords);
}

int MPI_Cart_create(MUK_Comm comm_old, int ndims, const int dims[], const int periods[], int reorder, MUK_Comm *comm_cart)
{
    return MUK_Cart_create(comm_old, ndims, dims, periods, reorder, comm_cart);
}

int MPI_Cart_get(MUK_Comm comm, int maxdims, int dims[], int periods[], int coords[])
{
    return MUK_Cart_get(comm, maxdims, dims, periods, coords);
}

int MPI_Cart_map(MUK_Comm comm, int ndims, const int dims[], const int periods[], int *newrank)
{
    return MUK_Cart_map(comm, ndims, dims, periods, newrank);
}

int MPI_Cart_rank(MUK_Comm comm, const int coords[], int *rank)
{
    return MUK_Cart_rank(comm, coords, rank);
}

int MPI_Cart_shift(MUK_Comm comm, int direction, int disp, int *rank_source, int *rank_dest)
{
    return MUK_Cart_shift(comm, direction, disp, rank_source, rank_dest);
}

int MPI_Cart_sub(MUK_Comm comm, const int remain_dims[], MUK_Comm *newcomm)
{
    return MUK_Cart_sub(comm, remain_dims, newcomm);
}

int MPI_Cartdim_get(MUK_Comm comm, int *ndims)
{
    return MUK_Cartdim_get(comm, ndims);
}

int MPI_Close_port(const char *port_name)
{
    return MUK_Close_port(port_name);
}

int MPI_Comm_accept(const char *port_name, MUK_Info info, int root, MUK_Comm comm, MUK_Comm *newcomm)
{
    return MUK_Comm_accept(port_name, info, root, comm, newcomm);
}

int MPI_Comm_call_errhandler(MUK_Comm comm, int errorcode)
{
    return MUK_Comm_call_errhandler(comm, errorcode);
}

int MPI_Comm_compare(MUK_Comm comm1, MUK_Comm comm2, int *result)
{
    return MUK_Comm_compare(comm1, comm2, result);
}

int MPI_Comm_connect(const char *port_name, MUK_Info info, int root, MUK_Comm comm, MUK_Comm *newcomm)
{
    return MUK_Comm_connect(port_name, info, root, comm, newcomm);
}

int MPI_Comm_create(MUK_Comm comm, MUK_Group group, MUK_Comm *newcomm)
{
    return MUK_Comm_create(comm, group, newcomm);
}

int MPI_Comm_create_errhandler(MUK_Comm_errhandler_function *comm_errhandler_fn, MUK_Errhandler *errhandler)
{
    return MUK_Comm_create_errhandler(comm_errhandler_fn, errhandler);
}

int MPI_Comm_create_from_group(MUK_Group group, const char *stringtag, MUK_Info info, MUK_Errhandler errhandler, MUK_Comm *newcomm)
{
    return MUK_Comm_create_from_group(group, stringtag, info, errhandler, newcomm);
}

int MPI_Comm_create_group(MUK_Comm comm, MUK_Group group, int tag, MUK_Comm *newcomm)
{
    return MUK_Comm_create_group(comm, group, tag, newcomm);
}

int MPI_Comm_create_keyval(MUK_Comm_copy_attr_function *comm_copy_attr_fn, MUK_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state)
{
    return MUK_Comm_create_keyval(comm_copy_attr_fn, comm_delete_attr_fn, comm_keyval, extra_state);
}

int MPI_Comm_delete_attr(MUK_Comm comm, int comm_keyval)
{
    return MUK_Comm_delete_attr(comm, comm_keyval);
}

int MPI_Comm_disconnect(MUK_Comm *comm)
{
    return MUK_Comm_disconnect(comm);
}

int MPI_Comm_dup(MUK_Comm comm, MUK_Comm *newcomm)
{
    return MUK_Comm_dup(comm, newcomm);
}

int MPI_Comm_dup_with_info(MUK_Comm comm, MUK_Info info, MUK_Comm *newcomm)
{
    return MUK_Comm_dup_with_info(comm, info, newcomm);
}

int MPI_Comm_free(MUK_Comm *comm)
{
    return MUK_Comm_free(comm);
}

int MPI_Comm_free_keyval(int *comm_keyval)
{
    return MUK_Comm_free_keyval(comm_keyval);
}

int MPI_Comm_get_attr(MUK_Comm comm, int comm_keyval, void *attribute_val, int *flag)
{
    return MUK_Comm_get_attr(comm, comm_keyval, attribute_val, flag);
}

int MPI_Comm_get_errhandler(MUK_Comm comm, MUK_Errhandler *errhandler)
{
    return MUK_Comm_get_errhandler(comm, errhandler);
}

int MPI_Comm_get_info(MUK_Comm comm, MUK_Info *info_used)
{
    return MUK_Comm_get_info(comm, info_used);
}

int MPI_Comm_get_name(MUK_Comm comm, char *comm_name, int *resultlen)
{
    return MUK_Comm_get_name(comm, comm_name, resultlen);
}

int MPI_Comm_get_parent(MUK_Comm *parent)
{
    return MUK_Comm_get_parent(parent);
}

int MPI_Comm_group(MUK_Comm comm, MUK_Group *group)
{
    return MUK_Comm_group(comm, group);
}

int MPI_Comm_idup(MUK_Comm comm, MUK_Comm *newcomm, MUK_Request *request)
{
    return MUK_Comm_idup(comm, newcomm, request);
}

int MPI_Comm_idup_with_info(MUK_Comm comm, MUK_Info info, MUK_Comm *newcomm, MUK_Request *request)
{
    return MUK_Comm_idup_with_info(comm, info, newcomm, request);
}

int MPI_Comm_join(int fd, MUK_Comm *intercomm)
{
    return MUK_Comm_join(fd, intercomm);
}

int MPI_Comm_remote_group(MUK_Comm comm, MUK_Group *group)
{
    return MUK_Comm_remote_group(comm, group);
}

int MPI_Comm_remote_size(MUK_Comm comm, int *size)
{
    return MUK_Comm_remote_size(comm, size);
}

int MPI_Comm_set_attr(MUK_Comm comm, int comm_keyval, void *attribute_val)
{
    return MUK_Comm_set_attr(comm, comm_keyval, attribute_val);
}

int MPI_Comm_set_errhandler(MUK_Comm comm, MUK_Errhandler errhandler)
{
    return MUK_Comm_set_errhandler(comm, errhandler);
}

int MPI_Comm_set_info(MUK_Comm comm, MUK_Info info)
{
    return MUK_Comm_set_info(comm, info);
}

int MPI_Comm_set_name(MUK_Comm comm, const char *comm_name)
{
    return MUK_Comm_set_name(comm, comm_name);
}

int MPI_Comm_split(MUK_Comm comm, int color, int key, MUK_Comm *newcomm)
{
    return MUK_Comm_split(comm, color, key, newcomm);
}

int MPI_Comm_split_type(MUK_Comm comm, int split_type, int key, MUK_Info info, MUK_Comm *newcomm)
{
    return MUK_Comm_split_type(comm, split_type, key, info, newcomm);
}

int MPI_Comm_test_inter(MUK_Comm comm, int *flag)
{
    return MUK_Comm_test_inter(comm, flag);
}

int MPI_Compare_and_swap(const void *origin_addr, const void *compare_addr, void *result_addr, MUK_Datatype datatype, int target_rank, MUK_Aint target_disp, MUK_Win win)
{
    return MUK_Compare_and_swap(origin_addr, compare_addr, result_addr, datatype, target_rank, target_disp, win);
}

int MPI_Dims_create(int nnodes, int ndims, int dims[])
{
    return MUK_Dims_create(nnodes, ndims, dims);
}

int MPI_Dist_graph_create(MUK_Comm comm_old, int n, const int sources[], const int degrees[], const int destinations[], const int weights[], MUK_Info info, int reorder, MUK_Comm *comm_dist_graph)
{
    return MUK_Dist_graph_create(comm_old, n, sources, degrees, destinations, weights, info, reorder, comm_dist_graph);
}

int MPI_Dist_graph_create_adjacent(MUK_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], MUK_Info info, int reorder, MUK_Comm *comm_dist_graph)
{
    return MUK_Dist_graph_create_adjacent(comm_old, indegree, sources, sourceweights, outdegree, destinations, destweights, info, reorder, comm_dist_graph);
}

int MPI_Dist_graph_neighbors(MUK_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[])
{
    return MUK_Dist_graph_neighbors(comm, maxindegree, sources, sourceweights, maxoutdegree, destinations, destweights);
}

int MPI_Dist_graph_neighbors_count(MUK_Comm comm, int *indegree, int *outdegree, int *weighted)
{
    return MUK_Dist_graph_neighbors_count(comm, indegree, outdegree, weighted);
}

int MPI_Errhandler_create(MUK_Comm_errhandler_function *comm_errhandler_fn, MUK_Errhandler *errhandler)
{
    return MUK_Errhandler_create(comm_errhandler_fn, errhandler);
}

int MPI_Errhandler_free(MUK_Errhandler *errhandler)
{
    return MUK_Errhandler_free(errhandler);
}

int MPI_Errhandler_get(MUK_Comm comm, MUK_Errhandler *errhandler)
{
    return MUK_Errhandler_get(comm, errhandler);
}

int MPI_Errhandler_set(MUK_Comm comm, MUK_Errhandler errhandler)
{
    return MUK_Errhandler_set(comm, errhandler);
}

int MPI_Error_class(int errorcode, int *errorclass)
{
    return MUK_Error_class(errorcode, errorclass);
}

int MPI_Error_string(int errorcode, char *string, int *resultlen)
{
    return MUK_Error_string(errorcode, string, resultlen);
}

int MPI_Exscan(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm)
{
    return MUK_Exscan(sendbuf, recvbuf, count, datatype, op, comm);
}

int MPI_Exscan_c(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm)
{
    return MUK_Exscan_c(sendbuf, recvbuf, count, datatype, op, comm);
}

int MPI_Exscan_init(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Exscan_init(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int MPI_Exscan_init_c(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Exscan_init_c(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int MPI_Fetch_and_op(const void *origin_addr, void *result_addr, MUK_Datatype datatype, int target_rank, MUK_Aint target_disp, MUK_Op op, MUK_Win win)
{
    return MUK_Fetch_and_op(origin_addr, result_addr, datatype, target_rank, target_disp, op, win);
}

int MPI_File_call_errhandler(MUK_File fh, int errorcode)
{
    return MUK_File_call_errhandler(fh, errorcode);
}

int MPI_File_close(MUK_File *fh)
{
    return MUK_File_close(fh);
}

int MPI_File_create_errhandler(MUK_File_errhandler_function *file_errhandler_fn, MUK_Errhandler *errhandler)
{
    return MUK_File_create_errhandler(file_errhandler_fn, errhandler);
}

int MPI_File_delete(const char *filename, MUK_Info info)
{
    return MUK_File_delete(filename, info);
}

int MPI_File_get_amode(MUK_File fh, int *amode)
{
    return MUK_File_get_amode(fh, amode);
}

int MPI_File_get_atomicity(MUK_File fh, int *flag)
{
    return MUK_File_get_atomicity(fh, flag);
}

int MPI_File_get_byte_offset(MUK_File fh, MUK_Offset offset, MUK_Offset *disp)
{
    return MUK_File_get_byte_offset(fh, offset, disp);
}

int MPI_File_get_errhandler(MUK_File file, MUK_Errhandler *errhandler)
{
    return MUK_File_get_errhandler(file, errhandler);
}

int MPI_File_get_group(MUK_File fh, MUK_Group *group)
{
    return MUK_File_get_group(fh, group);
}

int MPI_File_get_info(MUK_File fh, MUK_Info *info_used)
{
    return MUK_File_get_info(fh, info_used);
}

int MPI_File_get_position(MUK_File fh, MUK_Offset *offset)
{
    return MUK_File_get_position(fh, offset);
}

int MPI_File_get_position_shared(MUK_File fh, MUK_Offset *offset)
{
    return MUK_File_get_position_shared(fh, offset);
}

int MPI_File_get_size(MUK_File fh, MUK_Offset *size)
{
    return MUK_File_get_size(fh, size);
}

int MPI_File_get_type_extent(MUK_File fh, MUK_Datatype datatype, MUK_Aint *extent)
{
    return MUK_File_get_type_extent(fh, datatype, extent);
}

int MPI_File_get_type_extent_c(MUK_File fh, MUK_Datatype datatype, MUK_Count *extent)
{
    return MUK_File_get_type_extent_c(fh, datatype, extent);
}

int MPI_File_get_view(MUK_File fh, MUK_Offset *disp, MUK_Datatype *etype, MUK_Datatype *filetype, char *datarep)
{
    return MUK_File_get_view(fh, disp, etype, filetype, datarep);
}

int MPI_File_iread(MUK_File fh, void *buf, int count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iread(fh, buf, count, datatype, request);
}

int MPI_File_iread_all(MUK_File fh, void *buf, int count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iread_all(fh, buf, count, datatype, request);
}

int MPI_File_iread_all_c(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iread_all_c(fh, buf, count, datatype, request);
}

int MPI_File_iread_at(MUK_File fh, MUK_Offset offset, void *buf, int count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iread_at(fh, offset, buf, count, datatype, request);
}

int MPI_File_iread_at_all(MUK_File fh, MUK_Offset offset, void *buf, int count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iread_at_all(fh, offset, buf, count, datatype, request);
}

int MPI_File_iread_at_all_c(MUK_File fh, MUK_Offset offset, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iread_at_all_c(fh, offset, buf, count, datatype, request);
}

int MPI_File_iread_at_c(MUK_File fh, MUK_Offset offset, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iread_at_c(fh, offset, buf, count, datatype, request);
}

int MPI_File_iread_c(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iread_c(fh, buf, count, datatype, request);
}

int MPI_File_iread_shared(MUK_File fh, void *buf, int count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iread_shared(fh, buf, count, datatype, request);
}

int MPI_File_iread_shared_c(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iread_shared_c(fh, buf, count, datatype, request);
}

int MPI_File_iwrite(MUK_File fh, const void *buf, int count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iwrite(fh, buf, count, datatype, request);
}

int MPI_File_iwrite_all(MUK_File fh, const void *buf, int count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iwrite_all(fh, buf, count, datatype, request);
}

int MPI_File_iwrite_all_c(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iwrite_all_c(fh, buf, count, datatype, request);
}

int MPI_File_iwrite_at(MUK_File fh, MUK_Offset offset, const void *buf, int count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iwrite_at(fh, offset, buf, count, datatype, request);
}

int MPI_File_iwrite_at_all(MUK_File fh, MUK_Offset offset, const void *buf, int count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iwrite_at_all(fh, offset, buf, count, datatype, request);
}

int MPI_File_iwrite_at_all_c(MUK_File fh, MUK_Offset offset, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iwrite_at_all_c(fh, offset, buf, count, datatype, request);
}

int MPI_File_iwrite_at_c(MUK_File fh, MUK_Offset offset, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iwrite_at_c(fh, offset, buf, count, datatype, request);
}

int MPI_File_iwrite_c(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iwrite_c(fh, buf, count, datatype, request);
}

int MPI_File_iwrite_shared(MUK_File fh, const void *buf, int count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iwrite_shared(fh, buf, count, datatype, request);
}

int MPI_File_iwrite_shared_c(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Request *request)
{
    return MUK_File_iwrite_shared_c(fh, buf, count, datatype, request);
}

int MPI_File_open(MUK_Comm comm, const char *filename, int amode, MUK_Info info, MUK_File *fh)
{
    return MUK_File_open(comm, filename, amode, info, fh);
}

int MPI_File_preallocate(MUK_File fh, MUK_Offset size)
{
    return MUK_File_preallocate(fh, size);
}

int MPI_File_read(MUK_File fh, void *buf, int count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_read(fh, buf, count, datatype, status);
}

int MPI_File_read_all(MUK_File fh, void *buf, int count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_read_all(fh, buf, count, datatype, status);
}

int MPI_File_read_all_begin(MUK_File fh, void *buf, int count, MUK_Datatype datatype)
{
    return MUK_File_read_all_begin(fh, buf, count, datatype);
}

int MPI_File_read_all_begin_c(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype)
{
    return MUK_File_read_all_begin_c(fh, buf, count, datatype);
}

int MPI_File_read_all_c(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_read_all_c(fh, buf, count, datatype, status);
}

int MPI_File_read_all_end(MUK_File fh, void *buf, MUK_Status *status)
{
    return MUK_File_read_all_end(fh, buf, status);
}

int MPI_File_read_at(MUK_File fh, MUK_Offset offset, void *buf, int count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_read_at(fh, offset, buf, count, datatype, status);
}

int MPI_File_read_at_all(MUK_File fh, MUK_Offset offset, void *buf, int count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_read_at_all(fh, offset, buf, count, datatype, status);
}

int MPI_File_read_at_all_begin(MUK_File fh, MUK_Offset offset, void *buf, int count, MUK_Datatype datatype)
{
    return MUK_File_read_at_all_begin(fh, offset, buf, count, datatype);
}

int MPI_File_read_at_all_begin_c(MUK_File fh, MUK_Offset offset, void *buf, MUK_Count count, MUK_Datatype datatype)
{
    return MUK_File_read_at_all_begin_c(fh, offset, buf, count, datatype);
}

int MPI_File_read_at_all_c(MUK_File fh, MUK_Offset offset, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_read_at_all_c(fh, offset, buf, count, datatype, status);
}

int MPI_File_read_at_all_end(MUK_File fh, void *buf, MUK_Status *status)
{
    return MUK_File_read_at_all_end(fh, buf, status);
}

int MPI_File_read_at_c(MUK_File fh, MUK_Offset offset, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_read_at_c(fh, offset, buf, count, datatype, status);
}

int MPI_File_read_c(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_read_c(fh, buf, count, datatype, status);
}

int MPI_File_read_ordered(MUK_File fh, void *buf, int count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_read_ordered(fh, buf, count, datatype, status);
}

int MPI_File_read_ordered_begin(MUK_File fh, void *buf, int count, MUK_Datatype datatype)
{
    return MUK_File_read_ordered_begin(fh, buf, count, datatype);
}

int MPI_File_read_ordered_begin_c(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype)
{
    return MUK_File_read_ordered_begin_c(fh, buf, count, datatype);
}

int MPI_File_read_ordered_c(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_read_ordered_c(fh, buf, count, datatype, status);
}

int MPI_File_read_ordered_end(MUK_File fh, void *buf, MUK_Status *status)
{
    return MUK_File_read_ordered_end(fh, buf, status);
}

int MPI_File_read_shared(MUK_File fh, void *buf, int count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_read_shared(fh, buf, count, datatype, status);
}

int MPI_File_read_shared_c(MUK_File fh, void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_read_shared_c(fh, buf, count, datatype, status);
}

int MPI_File_seek(MUK_File fh, MUK_Offset offset, int whence)
{
    return MUK_File_seek(fh, offset, whence);
}

int MPI_File_seek_shared(MUK_File fh, MUK_Offset offset, int whence)
{
    return MUK_File_seek_shared(fh, offset, whence);
}

int MPI_File_set_atomicity(MUK_File fh, int flag)
{
    return MUK_File_set_atomicity(fh, flag);
}

int MPI_File_set_errhandler(MUK_File file, MUK_Errhandler errhandler)
{
    return MUK_File_set_errhandler(file, errhandler);
}

int MPI_File_set_info(MUK_File fh, MUK_Info info)
{
    return MUK_File_set_info(fh, info);
}

int MPI_File_set_size(MUK_File fh, MUK_Offset size)
{
    return MUK_File_set_size(fh, size);
}

int MPI_File_set_view(MUK_File fh, MUK_Offset disp, MUK_Datatype etype, MUK_Datatype filetype, const char *datarep, MUK_Info info)
{
    return MUK_File_set_view(fh, disp, etype, filetype, datarep, info);
}

int MPI_File_sync(MUK_File fh)
{
    return MUK_File_sync(fh);
}

int MPI_File_write(MUK_File fh, const void *buf, int count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_write(fh, buf, count, datatype, status);
}

int MPI_File_write_all(MUK_File fh, const void *buf, int count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_write_all(fh, buf, count, datatype, status);
}

int MPI_File_write_all_begin(MUK_File fh, const void *buf, int count, MUK_Datatype datatype)
{
    return MUK_File_write_all_begin(fh, buf, count, datatype);
}

int MPI_File_write_all_begin_c(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype)
{
    return MUK_File_write_all_begin_c(fh, buf, count, datatype);
}

int MPI_File_write_all_c(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_write_all_c(fh, buf, count, datatype, status);
}

int MPI_File_write_all_end(MUK_File fh, const void *buf, MUK_Status *status)
{
    return MUK_File_write_all_end(fh, buf, status);
}

int MPI_File_write_at(MUK_File fh, MUK_Offset offset, const void *buf, int count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_write_at(fh, offset, buf, count, datatype, status);
}

int MPI_File_write_at_all(MUK_File fh, MUK_Offset offset, const void *buf, int count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_write_at_all(fh, offset, buf, count, datatype, status);
}

int MPI_File_write_at_all_begin(MUK_File fh, MUK_Offset offset, const void *buf, int count, MUK_Datatype datatype)
{
    return MUK_File_write_at_all_begin(fh, offset, buf, count, datatype);
}

int MPI_File_write_at_all_begin_c(MUK_File fh, MUK_Offset offset, const void *buf, MUK_Count count, MUK_Datatype datatype)
{
    return MUK_File_write_at_all_begin_c(fh, offset, buf, count, datatype);
}

int MPI_File_write_at_all_c(MUK_File fh, MUK_Offset offset, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_write_at_all_c(fh, offset, buf, count, datatype, status);
}

int MPI_File_write_at_all_end(MUK_File fh, const void *buf, MUK_Status *status)
{
    return MUK_File_write_at_all_end(fh, buf, status);
}

int MPI_File_write_at_c(MUK_File fh, MUK_Offset offset, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_write_at_c(fh, offset, buf, count, datatype, status);
}

int MPI_File_write_c(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_write_c(fh, buf, count, datatype, status);
}

int MPI_File_write_ordered(MUK_File fh, const void *buf, int count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_write_ordered(fh, buf, count, datatype, status);
}

int MPI_File_write_ordered_begin(MUK_File fh, const void *buf, int count, MUK_Datatype datatype)
{
    return MUK_File_write_ordered_begin(fh, buf, count, datatype);
}

int MPI_File_write_ordered_begin_c(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype)
{
    return MUK_File_write_ordered_begin_c(fh, buf, count, datatype);
}

int MPI_File_write_ordered_c(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_write_ordered_c(fh, buf, count, datatype, status);
}

int MPI_File_write_ordered_end(MUK_File fh, const void *buf, MUK_Status *status)
{
    return MUK_File_write_ordered_end(fh, buf, status);
}

int MPI_File_write_shared(MUK_File fh, const void *buf, int count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_write_shared(fh, buf, count, datatype, status);
}

int MPI_File_write_shared_c(MUK_File fh, const void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Status *status)
{
    return MUK_File_write_shared_c(fh, buf, count, datatype, status);
}

int MPI_Free_mem(void *base)
{
    return MUK_Free_mem(base);
}

int MPI_Gather(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm)
{
    return MUK_Gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int MPI_Gather_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm)
{
    return MUK_Gather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int MPI_Gather_init(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Gather_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int MPI_Gather_init_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Gather_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int MPI_Gatherv(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, int root, MUK_Comm comm)
{
    return MUK_Gatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm);
}

int MPI_Gatherv_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, int root, MUK_Comm comm)
{
    return MUK_Gatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm);
}

int MPI_Gatherv_init(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Gatherv_init(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, info, request);
}

int MPI_Gatherv_init_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Gatherv_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, info, request);
}

int MPI_Get(void *origin_addr, int origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Win win)
{
    return MUK_Get(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
}

int MPI_Get_accumulate(const void *origin_addr, int origin_count, MUK_Datatype origin_datatype, void *result_addr, int result_count, MUK_Datatype result_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win)
{
    return MUK_Get_accumulate(origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
}

int MPI_Get_accumulate_c(const void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, void *result_addr, MUK_Count result_count, MUK_Datatype result_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win)
{
    return MUK_Get_accumulate_c(origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
}

int MPI_Get_address(const void *location, MUK_Aint *address)
{
    return MUK_Get_address(location, address);
}

int MPI_Get_c(void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Win win)
{
    return MUK_Get_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
}

int MPI_Get_count(const MUK_Status *status, MUK_Datatype datatype, int *count)
{
    return MUK_Get_count(status, datatype, count);
}

int MPI_Get_count_c(const MUK_Status *status, MUK_Datatype datatype, MUK_Count *count)
{
    return MUK_Get_count_c(status, datatype, count);
}

int MPI_Get_elements(const MUK_Status *status, MUK_Datatype datatype, int *count)
{
    return MUK_Get_elements(status, datatype, count);
}

int MPI_Get_elements_c(const MUK_Status *status, MUK_Datatype datatype, MUK_Count *count)
{
    return MUK_Get_elements_c(status, datatype, count);
}

int MPI_Get_elements_x(const MUK_Status *status, MUK_Datatype datatype, MUK_Count *count)
{
    return MUK_Get_elements_x(status, datatype, count);
}

int MPI_Graph_create(MUK_Comm comm_old, int nnodes, const int indx[], const int edges[], int reorder, MUK_Comm *comm_graph)
{
    return MUK_Graph_create(comm_old, nnodes, indx, edges, reorder, comm_graph);
}

int MPI_Graph_get(MUK_Comm comm, int maxindex, int maxedges, int indx[], int edges[])
{
    return MUK_Graph_get(comm, maxindex, maxedges, indx, edges);
}

int MPI_Graph_map(MUK_Comm comm, int nnodes, const int indx[], const int edges[], int *newrank)
{
    return MUK_Graph_map(comm, nnodes, indx, edges, newrank);
}

int MPI_Graph_neighbors(MUK_Comm comm, int rank, int maxneighbors, int neighbors[])
{
    return MUK_Graph_neighbors(comm, rank, maxneighbors, neighbors);
}

int MPI_Graph_neighbors_count(MUK_Comm comm, int rank, int *nneighbors)
{
    return MUK_Graph_neighbors_count(comm, rank, nneighbors);
}

int MPI_Graphdims_get(MUK_Comm comm, int *nnodes, int *nedges)
{
    return MUK_Graphdims_get(comm, nnodes, nedges);
}

int MPI_Grequest_complete(MUK_Request request)
{
    return MUK_Grequest_complete(request);
}

int MPI_Grequest_start(MUK_Grequest_query_function *query_fn, MUK_Grequest_free_function *free_fn, MUK_Grequest_cancel_function *cancel_fn, void *extra_state, MUK_Request *request)
{
    return MUK_Grequest_start(query_fn, free_fn, cancel_fn, extra_state, request);
}

int MPI_Group_compare(MUK_Group group1, MUK_Group group2, int *result)
{
    return MUK_Group_compare(group1, group2, result);
}

int MPI_Group_difference(MUK_Group group1, MUK_Group group2, MUK_Group *newgroup)
{
    return MUK_Group_difference(group1, group2, newgroup);
}

int MPI_Group_excl(MUK_Group group, int n, const int ranks[], MUK_Group *newgroup)
{
    return MUK_Group_excl(group, n, ranks, newgroup);
}

int MPI_Group_free(MUK_Group *group)
{
    return MUK_Group_free(group);
}

int MPI_Group_from_session_pset(MUK_Session session, const char *pset_name, MUK_Group *newgroup)
{
    return MUK_Group_from_session_pset(session, pset_name, newgroup);
}

int MPI_Group_incl(MUK_Group group, int n, const int ranks[], MUK_Group *newgroup)
{
    return MUK_Group_incl(group, n, ranks, newgroup);
}

int MPI_Group_intersection(MUK_Group group1, MUK_Group group2, MUK_Group *newgroup)
{
    return MUK_Group_intersection(group1, group2, newgroup);
}

int MPI_Group_range_excl(MUK_Group group, int n, int ranges[][3], MUK_Group *newgroup)
{
    return MUK_Group_range_excl(group, n, ranges, newgroup);
}

int MPI_Group_range_incl(MUK_Group group, int n, int ranges[][3], MUK_Group *newgroup)
{
    return MUK_Group_range_incl(group, n, ranges, newgroup);
}

int MPI_Group_rank(MUK_Group group, int *rank)
{
    return MUK_Group_rank(group, rank);
}

int MPI_Group_size(MUK_Group group, int *size)
{
    return MUK_Group_size(group, size);
}

int MPI_Group_translate_ranks(MUK_Group group1, int n, const int ranks1[], MUK_Group group2, int ranks2[])
{
    return MUK_Group_translate_ranks(group1, n, ranks1, group2, ranks2);
}

int MPI_Group_union(MUK_Group group1, MUK_Group group2, MUK_Group *newgroup)
{
    return MUK_Group_union(group1, group2, newgroup);
}

int MPI_Iallgather(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Iallgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Iallgather_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Iallgather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Iallgatherv(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Iallgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
}

int MPI_Iallgatherv_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Iallgatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
}

int MPI_Iallreduce(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Iallreduce(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int MPI_Iallreduce_c(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Iallreduce_c(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int MPI_Ialltoall(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ialltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Ialltoall_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ialltoall_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Ialltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ialltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
}

int MPI_Ialltoallv_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ialltoallv_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
}

int MPI_Ialltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
}

int MPI_Ialltoallw_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ialltoallw_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
}

int MPI_Ibarrier(MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ibarrier(comm, request);
}

int MPI_Ibcast(void *buffer, int count, MUK_Datatype datatype, int root, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ibcast(buffer, count, datatype, root, comm, request);
}

int MPI_Ibcast_c(void *buffer, MUK_Count count, MUK_Datatype datatype, int root, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ibcast_c(buffer, count, datatype, root, comm, request);
}

int MPI_Ibsend(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ibsend(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Ibsend_c(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ibsend_c(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Iexscan(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Iexscan(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int MPI_Iexscan_c(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Iexscan_c(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int MPI_Igather(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Igather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int MPI_Igather_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Igather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int MPI_Igatherv(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Igatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, request);
}

int MPI_Igatherv_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Igatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, request);
}

int MPI_Improbe(int source, int tag, MUK_Comm comm, int *flag, MUK_Message *message, MUK_Status *status)
{
    return MUK_Improbe(source, tag, comm, flag, message, status);
}

int MPI_Imrecv(void *buf, int count, MUK_Datatype datatype, MUK_Message *message, MUK_Request *request)
{
    return MUK_Imrecv(buf, count, datatype, message, request);
}

int MPI_Imrecv_c(void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Message *message, MUK_Request *request)
{
    return MUK_Imrecv_c(buf, count, datatype, message, request);
}

int MPI_Ineighbor_allgather(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ineighbor_allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Ineighbor_allgather_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ineighbor_allgather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Ineighbor_allgatherv(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ineighbor_allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
}

int MPI_Ineighbor_allgatherv_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ineighbor_allgatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
}

int MPI_Ineighbor_alltoall(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ineighbor_alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Ineighbor_alltoall_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ineighbor_alltoall_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Ineighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ineighbor_alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
}

int MPI_Ineighbor_alltoallv_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ineighbor_alltoallv_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
}

int MPI_Ineighbor_alltoallw(const void *sendbuf, const int sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ineighbor_alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
}

int MPI_Ineighbor_alltoallw_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ineighbor_alltoallw_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
}

int MPI_Info_create(MUK_Info *info)
{
    return MUK_Info_create(info);
}

int MPI_Info_create_env(int argc, char *argv[], MUK_Info *info)
{
    return MUK_Info_create_env(argc, argv, info);
}

int MPI_Info_delete(MUK_Info info, const char *key)
{
    return MUK_Info_delete(info, key);
}

int MPI_Info_dup(MUK_Info info, MUK_Info *newinfo)
{
    return MUK_Info_dup(info, newinfo);
}

int MPI_Info_free(MUK_Info *info)
{
    return MUK_Info_free(info);
}

int MPI_Info_get(MUK_Info info, const char *key, int valuelen, char *value, int *flag)
{
    return MUK_Info_get(info, key, valuelen, value, flag);
}

int MPI_Info_get_nkeys(MUK_Info info, int *nkeys)
{
    return MUK_Info_get_nkeys(info, nkeys);
}

int MPI_Info_get_nthkey(MUK_Info info, int n, char *key)
{
    return MUK_Info_get_nthkey(info, n, key);
}

int MPI_Info_get_string(MUK_Info info, const char *key, int *buflen, char *value, int *flag)
{
    return MUK_Info_get_string(info, key, buflen, value, flag);
}

int MPI_Info_get_valuelen(MUK_Info info, const char *key, int *valuelen, int *flag)
{
    return MUK_Info_get_valuelen(info, key, valuelen, flag);
}

int MPI_Info_set(MUK_Info info, const char *key, const char *value)
{
    return MUK_Info_set(info, key, value);
}

int MPI_Intercomm_create(MUK_Comm local_comm, int local_leader, MUK_Comm peer_comm, int remote_leader, int tag, MUK_Comm *newintercomm)
{
    return MUK_Intercomm_create(local_comm, local_leader, peer_comm, remote_leader, tag, newintercomm);
}

int MPI_Intercomm_create_from_groups(MUK_Group local_group, int local_leader, MUK_Group remote_group, int remote_leader, const char *stringtag, MUK_Info info, MUK_Errhandler errhandler, MUK_Comm *newintercomm)
{
    return MUK_Intercomm_create_from_groups(local_group, local_leader, remote_group, remote_leader, stringtag, info, errhandler, newintercomm);
}

int MPI_Intercomm_merge(MUK_Comm intercomm, int high, MUK_Comm *newintracomm)
{
    return MUK_Intercomm_merge(intercomm, high, newintracomm);
}

int MPI_Iprobe(int source, int tag, MUK_Comm comm, int *flag, MUK_Status *status)
{
    return MUK_Iprobe(source, tag, comm, flag, status);
}

int MPI_Irecv(void *buf, int count, MUK_Datatype datatype, int source, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Irecv(buf, count, datatype, source, tag, comm, request);
}

int MPI_Irecv_c(void *buf, MUK_Count count, MUK_Datatype datatype, int source, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Irecv_c(buf, count, datatype, source, tag, comm, request);
}

int MPI_Ireduce(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, int root, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ireduce(sendbuf, recvbuf, count, datatype, op, root, comm, request);
}

int MPI_Ireduce_c(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, int root, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ireduce_c(sendbuf, recvbuf, count, datatype, op, root, comm, request);
}

int MPI_Ireduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ireduce_scatter(sendbuf, recvbuf, recvcounts, datatype, op, comm, request);
}

int MPI_Ireduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ireduce_scatter_block(sendbuf, recvbuf, recvcount, datatype, op, comm, request);
}

int MPI_Ireduce_scatter_block_c(const void *sendbuf, void *recvbuf, MUK_Count recvcount, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ireduce_scatter_block_c(sendbuf, recvbuf, recvcount, datatype, op, comm, request);
}

int MPI_Ireduce_scatter_c(const void *sendbuf, void *recvbuf, const MUK_Count recvcounts[], MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ireduce_scatter_c(sendbuf, recvbuf, recvcounts, datatype, op, comm, request);
}

int MPI_Irsend(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Irsend(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Irsend_c(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Irsend_c(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Iscan(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Iscan(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int MPI_Iscan_c(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Iscan_c(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int MPI_Iscatter(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Iscatter(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int MPI_Iscatter_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Iscatter_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int MPI_Iscatterv(const void *sendbuf, const int sendcounts[], const int displs[], MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Iscatterv(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int MPI_Iscatterv_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint displs[], MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Iscatterv_c(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int MPI_Isend(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Isend(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Isend_c(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Isend_c(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Isendrecv(const void *sendbuf, int sendcount, MUK_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MUK_Datatype recvtype, int source, int recvtag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Isendrecv(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, request);
}

int MPI_Isendrecv_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, int dest, int sendtag, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int source, int recvtag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Isendrecv_c(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, request);
}

int MPI_Isendrecv_replace(void *buf, int count, MUK_Datatype datatype, int dest, int sendtag, int source, int recvtag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Isendrecv_replace(buf, count, datatype, dest, sendtag, source, recvtag, comm, request);
}

int MPI_Isendrecv_replace_c(void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int sendtag, int source, int recvtag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Isendrecv_replace_c(buf, count, datatype, dest, sendtag, source, recvtag, comm, request);
}

int MPI_Issend(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Issend(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Issend_c(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Issend_c(buf, count, datatype, dest, tag, comm, request);
}

#if 0
int MPI_Keyval_create(MUK_Copy_function *copy_fn, MUK_Delete_function *delete_fn, int *keyval, void *extra_state)
{
    return MUK_Keyval_create(copy_fn, delete_fn, keyval, extra_state);
}

int MPI_Keyval_free(int *keyval)
{
    return MUK_Keyval_free(keyval);
}
#endif

int MPI_Lookup_name(const char *service_name, MUK_Info info, char *port_name)
{
    return MUK_Lookup_name(service_name, info, port_name);
}

int MPI_Mprobe(int source, int tag, MUK_Comm comm, MUK_Message *message, MUK_Status *status)
{
    return MUK_Mprobe(source, tag, comm, message, status);
}

int MPI_Mrecv(void *buf, int count, MUK_Datatype datatype, MUK_Message *message, MUK_Status *status)
{
    return MUK_Mrecv(buf, count, datatype, message, status);
}

int MPI_Mrecv_c(void *buf, MUK_Count count, MUK_Datatype datatype, MUK_Message *message, MUK_Status *status)
{
    return MUK_Mrecv_c(buf, count, datatype, message, status);
}

int MPI_Neighbor_allgather(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Neighbor_allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Neighbor_allgather_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Neighbor_allgather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Neighbor_allgather_init(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Neighbor_allgather_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Neighbor_allgather_init_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Neighbor_allgather_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Neighbor_allgatherv(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Neighbor_allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
}

int MPI_Neighbor_allgatherv_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Neighbor_allgatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
}

int MPI_Neighbor_allgatherv_init(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Neighbor_allgatherv_init(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, info, request);
}

int MPI_Neighbor_allgatherv_init_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint displs[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Neighbor_allgatherv_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, info, request);
}

int MPI_Neighbor_alltoall(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Neighbor_alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Neighbor_alltoall_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Neighbor_alltoall_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Neighbor_alltoall_init(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Neighbor_alltoall_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Neighbor_alltoall_init_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Neighbor_alltoall_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Neighbor_alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}

int MPI_Neighbor_alltoallv_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], MUK_Datatype recvtype, MUK_Comm comm)
{
    return MUK_Neighbor_alltoallv_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}

int MPI_Neighbor_alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], MUK_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Neighbor_alltoallv_init(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, info, request);
}

int MPI_Neighbor_alltoallv_init_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], MUK_Datatype sendtype, void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], MUK_Datatype recvtype, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Neighbor_alltoallv_init_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, info, request);
}

int MPI_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm)
{
    return MUK_Neighbor_alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
}

int MPI_Neighbor_alltoallw_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm)
{
    return MUK_Neighbor_alltoallw_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
}

int MPI_Neighbor_alltoallw_init(const void *sendbuf, const int sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Neighbor_alltoallw_init(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, info, request);
}

int MPI_Neighbor_alltoallw_init_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint sdispls[], const MUK_Datatype sendtypes[], void *recvbuf, const MUK_Count recvcounts[], const MUK_Aint rdispls[], const MUK_Datatype recvtypes[], MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Neighbor_alltoallw_init_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, info, request);
}

int MPI_Op_commutative(MUK_Op op, int *commute)
{
    return MUK_Op_commutative(op, commute);
}

int MPI_Op_create(MUK_User_function *user_fn, int commute, MUK_Op *op)
{
    return MUK_Op_create(user_fn, commute, op);
}

int MPI_Op_create_c(MUK_User_function_c *user_fn, int commute, MUK_Op *op)
{
    return MUK_Op_create_c(user_fn, commute, op);
}

int MPI_Op_free(MUK_Op *op)
{
    return MUK_Op_free(op);
}

int MPI_Open_port(MUK_Info info, char *port_name)
{
    return MUK_Open_port(info, port_name);
}

int MPI_Pack(const void *inbuf, int incount, MUK_Datatype datatype, void *outbuf, int outsize, int *position, MUK_Comm comm)
{
    return MUK_Pack(inbuf, incount, datatype, outbuf, outsize, position, comm);
}

int MPI_Pack_c(const void *inbuf, MUK_Count incount, MUK_Datatype datatype, void *outbuf, MUK_Count outsize, MUK_Count *position, MUK_Comm comm)
{
    return MUK_Pack_c(inbuf, incount, datatype, outbuf, outsize, position, comm);
}

int MPI_Pack_external(const char *datarep, const void *inbuf, int incount, MUK_Datatype datatype, void *outbuf, MUK_Aint outsize, MUK_Aint *position)
{
    return MUK_Pack_external(datarep, inbuf, incount, datatype, outbuf, outsize, position);
}

int MPI_Pack_external_c(const char *datarep, const void *inbuf, MUK_Count incount, MUK_Datatype datatype, void *outbuf, MUK_Count outsize, MUK_Count *position)
{
    return MUK_Pack_external_c(datarep, inbuf, incount, datatype, outbuf, outsize, position);
}

int MPI_Pack_external_size(const char *datarep, int incount, MUK_Datatype datatype, MUK_Aint *size)
{
    return MUK_Pack_external_size(datarep, incount, datatype, size);
}

int MPI_Pack_external_size_c(const char *datarep, MUK_Count incount, MUK_Datatype datatype, MUK_Count *size)
{
    return MUK_Pack_external_size_c(datarep, incount, datatype, size);
}

int MPI_Pack_size(int incount, MUK_Datatype datatype, MUK_Comm comm, int *size)
{
    return MUK_Pack_size(incount, datatype, comm, size);
}

int MPI_Pack_size_c(MUK_Count incount, MUK_Datatype datatype, MUK_Comm comm, MUK_Count *size)
{
    return MUK_Pack_size_c(incount, datatype, comm, size);
}

int MPI_Parrived(MUK_Request request, int partition, int *flag)
{
    return MUK_Parrived(request, partition, flag);
}

int MPI_Pcontrol(const int level, ...)
{
    return MUK_Pcontrol(level);
}

int MPI_Pready(int partition, MUK_Request request)
{
    return MUK_Pready(partition, request);
}

int MPI_Pready_list(int length, const int array_of_partitions[], MUK_Request request)
{
    return MUK_Pready_list(length, array_of_partitions, request);
}

int MPI_Pready_range(int partition_low, int partition_high, MUK_Request request)
{
    return MUK_Pready_range(partition_low, partition_high, request);
}

int MPI_Precv_init(void *buf, int partitions, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Precv_init(buf, partitions, count, datatype, dest, tag, comm, info, request);
}

int MPI_Probe(int source, int tag, MUK_Comm comm, MUK_Status *status)
{
    return MUK_Probe(source, tag, comm, status);
}

int MPI_Psend_init(const void *buf, int partitions, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Psend_init(buf, partitions, count, datatype, dest, tag, comm, info, request);
}

int MPI_Publish_name(const char *service_name, MUK_Info info, const char *port_name)
{
    return MUK_Publish_name(service_name, info, port_name);
}

int MPI_Put(const void *origin_addr, int origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Win win)
{
    return MUK_Put(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
}

int MPI_Put_c(const void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Win win)
{
    return MUK_Put_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
}

int MPI_Raccumulate(const void *origin_addr, int origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win, MUK_Request *request)
{
    return MUK_Raccumulate(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
}

int MPI_Raccumulate_c(const void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win, MUK_Request *request)
{
    return MUK_Raccumulate_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
}

int MPI_Recv(void *buf, int count, MUK_Datatype datatype, int source, int tag, MUK_Comm comm, MUK_Status *status)
{
    return MUK_Recv(buf, count, datatype, source, tag, comm, status);
}

int MPI_Recv_c(void *buf, MUK_Count count, MUK_Datatype datatype, int source, int tag, MUK_Comm comm, MUK_Status *status)
{
    return MUK_Recv_c(buf, count, datatype, source, tag, comm, status);
}

int MPI_Recv_init(void *buf, int count, MUK_Datatype datatype, int source, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Recv_init(buf, count, datatype, source, tag, comm, request);
}

int MPI_Recv_init_c(void *buf, MUK_Count count, MUK_Datatype datatype, int source, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Recv_init_c(buf, count, datatype, source, tag, comm, request);
}

int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, int root, MUK_Comm comm)
{
    return MUK_Reduce(sendbuf, recvbuf, count, datatype, op, root, comm);
}

int MPI_Reduce_c(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, int root, MUK_Comm comm)
{
    return MUK_Reduce_c(sendbuf, recvbuf, count, datatype, op, root, comm);
}

int MPI_Reduce_init(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Reduce_init(sendbuf, recvbuf, count, datatype, op, root, comm, info, request);
}

int MPI_Reduce_init_c(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Reduce_init_c(sendbuf, recvbuf, count, datatype, op, root, comm, info, request);
}

int MPI_Reduce_local(const void *inbuf, void *inoutbuf, int count, MUK_Datatype datatype, MUK_Op op)
{
    return MUK_Reduce_local(inbuf, inoutbuf, count, datatype, op);
}

int MPI_Reduce_local_c(const void *inbuf, void *inoutbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op)
{
    return MUK_Reduce_local_c(inbuf, inoutbuf, count, datatype, op);
}

int MPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MUK_Datatype datatype, MUK_Op op, MUK_Comm comm)
{
    return MUK_Reduce_scatter(sendbuf, recvbuf, recvcounts, datatype, op, comm);
}

int MPI_Reduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm)
{
    return MUK_Reduce_scatter_block(sendbuf, recvbuf, recvcount, datatype, op, comm);
}

int MPI_Reduce_scatter_block_c(const void *sendbuf, void *recvbuf, MUK_Count recvcount, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm)
{
    return MUK_Reduce_scatter_block_c(sendbuf, recvbuf, recvcount, datatype, op, comm);
}

int MPI_Reduce_scatter_block_init(const void *sendbuf, void *recvbuf, int recvcount, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Reduce_scatter_block_init(sendbuf, recvbuf, recvcount, datatype, op, comm, info, request);
}

int MPI_Reduce_scatter_block_init_c(const void *sendbuf, void *recvbuf, MUK_Count recvcount, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Reduce_scatter_block_init_c(sendbuf, recvbuf, recvcount, datatype, op, comm, info, request);
}

int MPI_Reduce_scatter_c(const void *sendbuf, void *recvbuf, const MUK_Count recvcounts[], MUK_Datatype datatype, MUK_Op op, MUK_Comm comm)
{
    return MUK_Reduce_scatter_c(sendbuf, recvbuf, recvcounts, datatype, op, comm);
}

int MPI_Reduce_scatter_init(const void *sendbuf, void *recvbuf, const int recvcounts[], MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Reduce_scatter_init(sendbuf, recvbuf, recvcounts, datatype, op, comm, info, request);
}

int MPI_Reduce_scatter_init_c(const void *sendbuf, void *recvbuf, const MUK_Count recvcounts[], MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Reduce_scatter_init_c(sendbuf, recvbuf, recvcounts, datatype, op, comm, info, request);
}

int MPI_Register_datarep(const char *datarep, MUK_Datarep_conversion_function *read_conversion_fn, MUK_Datarep_conversion_function *write_conversion_fn, MUK_Datarep_extent_function *dtype_file_extent_fn, void *extra_state)
{
    return MUK_Register_datarep(datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
}

int MPI_Register_datarep_c(const char *datarep, MUK_Datarep_conversion_function_c *read_conversion_fn, MUK_Datarep_conversion_function_c *write_conversion_fn, MUK_Datarep_extent_function *dtype_file_extent_fn, void *extra_state)
{
    return MUK_Register_datarep_c(datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
}

int MPI_Request_free(MUK_Request *request)
{
    return MUK_Request_free(request);
}

int MPI_Request_get_status(MUK_Request request, int *flag, MUK_Status *status)
{
    return MUK_Request_get_status(request, flag, status);
}

int MPI_Rget(void *origin_addr, int origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Win win, MUK_Request *request)
{
    return MUK_Rget(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win, request);
}

int MPI_Rget_accumulate(const void *origin_addr, int origin_count, MUK_Datatype origin_datatype, void *result_addr, int result_count, MUK_Datatype result_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win, MUK_Request *request)
{
    return MUK_Rget_accumulate(origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
}

int MPI_Rget_accumulate_c(const void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, void *result_addr, MUK_Count result_count, MUK_Datatype result_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Op op, MUK_Win win, MUK_Request *request)
{
    return MUK_Rget_accumulate_c(origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
}

int MPI_Rget_c(void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Win win, MUK_Request *request)
{
    return MUK_Rget_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win, request);
}

int MPI_Rput(const void *origin_addr, int origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, int target_count, MUK_Datatype target_datatype, MUK_Win win, MUK_Request *request)
{
    return MUK_Rput(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win, request);
}

int MPI_Rput_c(const void *origin_addr, MUK_Count origin_count, MUK_Datatype origin_datatype, int target_rank, MUK_Aint target_disp, MUK_Count target_count, MUK_Datatype target_datatype, MUK_Win win, MUK_Request *request)
{
    return MUK_Rput_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win, request);
}

int MPI_Rsend(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm)
{
    return MUK_Rsend(buf, count, datatype, dest, tag, comm);
}

int MPI_Rsend_c(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm)
{
    return MUK_Rsend_c(buf, count, datatype, dest, tag, comm);
}

int MPI_Rsend_init(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Rsend_init(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Rsend_init_c(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Rsend_init_c(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Scan(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm)
{
    return MUK_Scan(sendbuf, recvbuf, count, datatype, op, comm);
}

int MPI_Scan_c(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm)
{
    return MUK_Scan_c(sendbuf, recvbuf, count, datatype, op, comm);
}

int MPI_Scan_init(const void *sendbuf, void *recvbuf, int count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Scan_init(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int MPI_Scan_init_c(const void *sendbuf, void *recvbuf, MUK_Count count, MUK_Datatype datatype, MUK_Op op, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Scan_init_c(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int MPI_Scatter(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm)
{
    return MUK_Scatter(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int MPI_Scatter_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm)
{
    return MUK_Scatter_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int MPI_Scatter_init(const void *sendbuf, int sendcount, MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Scatter_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int MPI_Scatter_init_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Scatter_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int MPI_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm)
{
    return MUK_Scatterv(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int MPI_Scatterv_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint displs[], MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm)
{
    return MUK_Scatterv_c(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int MPI_Scatterv_init(const void *sendbuf, const int sendcounts[], const int displs[], MUK_Datatype sendtype, void *recvbuf, int recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Scatterv_init(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int MPI_Scatterv_init_c(const void *sendbuf, const MUK_Count sendcounts[], const MUK_Aint displs[], MUK_Datatype sendtype, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int root, MUK_Comm comm, MUK_Info info, MUK_Request *request)
{
    return MUK_Scatterv_init_c(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int MPI_Send(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm)
{
    return MUK_Send(buf, count, datatype, dest, tag, comm);
}

int MPI_Send_c(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm)
{
    return MUK_Send_c(buf, count, datatype, dest, tag, comm);
}

int MPI_Send_init(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Send_init(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Send_init_c(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Send_init_c(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Sendrecv(const void *sendbuf, int sendcount, MUK_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MUK_Datatype recvtype, int source, int recvtag, MUK_Comm comm, MUK_Status *status)
{
    return MUK_Sendrecv(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, status);
}

int MPI_Sendrecv_c(const void *sendbuf, MUK_Count sendcount, MUK_Datatype sendtype, int dest, int sendtag, void *recvbuf, MUK_Count recvcount, MUK_Datatype recvtype, int source, int recvtag, MUK_Comm comm, MUK_Status *status)
{
    return MUK_Sendrecv_c(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, status);
}

int MPI_Sendrecv_replace(void *buf, int count, MUK_Datatype datatype, int dest, int sendtag, int source, int recvtag, MUK_Comm comm, MUK_Status *status)
{
    return MUK_Sendrecv_replace(buf, count, datatype, dest, sendtag, source, recvtag, comm, status);
}

int MPI_Sendrecv_replace_c(void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int sendtag, int source, int recvtag, MUK_Comm comm, MUK_Status *status)
{
    return MUK_Sendrecv_replace_c(buf, count, datatype, dest, sendtag, source, recvtag, comm, status);
}

int MPI_Session_call_errhandler(MUK_Session session, int errorcode)
{
    return MUK_Session_call_errhandler(session, errorcode);
}

int MPI_Session_create_errhandler(MUK_Session_errhandler_function *session_errhandler_fn, MUK_Errhandler *errhandler)
{
    return MUK_Session_create_errhandler(session_errhandler_fn, errhandler);
}

int MPI_Session_finalize(MUK_Session *session)
{
    return MUK_Session_finalize(session);
}

int MPI_Session_get_errhandler(MUK_Session session, MUK_Errhandler *errhandler)
{
    return MUK_Session_get_errhandler(session, errhandler);
}

int MPI_Session_get_info(MUK_Session session, MUK_Info *info_used)
{
    return MUK_Session_get_info(session, info_used);
}

int MPI_Session_get_nth_pset(MUK_Session session, MUK_Info info, int n, int *pset_len, char *pset_name)
{
    return MUK_Session_get_nth_pset(session, info, n, pset_len, pset_name);
}

int MPI_Session_get_num_psets(MUK_Session session, MUK_Info info, int *npset_names)
{
    return MUK_Session_get_num_psets(session, info, npset_names);
}

int MPI_Session_get_pset_info(MUK_Session session, const char *pset_name, MUK_Info *info)
{
    return MUK_Session_get_pset_info(session, pset_name, info);
}

int MPI_Session_init(MUK_Info info, MUK_Errhandler errhandler, MUK_Session *session)
{
    return MUK_Session_init(info, errhandler, session);
}

int MPI_Session_set_errhandler(MUK_Session session, MUK_Errhandler errhandler)
{
    return MUK_Session_set_errhandler(session, errhandler);
}

int MPI_Ssend(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm)
{
    return MUK_Ssend(buf, count, datatype, dest, tag, comm);
}

int MPI_Ssend_c(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm)
{
    return MUK_Ssend_c(buf, count, datatype, dest, tag, comm);
}

int MPI_Ssend_init(const void *buf, int count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ssend_init(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Ssend_init_c(const void *buf, MUK_Count count, MUK_Datatype datatype, int dest, int tag, MUK_Comm comm, MUK_Request *request)
{
    return MUK_Ssend_init_c(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Start(MUK_Request *request)
{
    return MUK_Start(request);
}

int MPI_Startall(int count, MUK_Request array_of_requests[])
{
    return MUK_Startall(count, array_of_requests);
}

#ifdef SUPPORT_F08
int MPI_Status_f082c(const MUK_F08_status *f08_status, MUK_Status *c_status)
{
    return MUK_Status_f082c(f08_status, c_status);
}

int MPI_Status_f082f(const MUK_F08_status *f08_status, MUK_Fint *f_status)
{
    return MUK_Status_f082f(f08_status, f_status);
}

int MPI_Status_f2f08(const MUK_Fint *f_status, MUK_F08_status *f08_status)
{
    return MUK_Status_f2f08(f_status, f08_status);
}
#endif

int MPI_Status_set_cancelled(MUK_Status *status, int flag)
{
    return MUK_Status_set_cancelled(status, flag);
}

int MPI_Status_set_elements(MUK_Status *status, MUK_Datatype datatype, int count)
{
    return MUK_Status_set_elements(status, datatype, count);
}

int MPI_Status_set_elements_c(MUK_Status *status, MUK_Datatype datatype, MUK_Count count)
{
    return MUK_Status_set_elements_c(status, datatype, count);
}

int MPI_Status_set_elements_x(MUK_Status *status, MUK_Datatype datatype, MUK_Count count)
{
    return MUK_Status_set_elements_x(status, datatype, count);
}

int MPI_Test(MUK_Request *request, int *flag, MUK_Status *status)
{
    return MUK_Test(request, flag, status);
}

int MPI_Test_cancelled(const MUK_Status *status, int *flag)
{
    return MUK_Test_cancelled(status, flag);
}

int MPI_Testall(int count, MUK_Request array_of_requests[], int *flag, MUK_Status array_of_statuses[])
{
    return MUK_Testall(count, array_of_requests, flag, array_of_statuses);
}

int MPI_Testany(int count, MUK_Request array_of_requests[], int *indx, int *flag, MUK_Status *status)
{
    return MUK_Testany(count, array_of_requests, indx, flag, status);
}

int MPI_Testsome(int incount, MUK_Request array_of_requests[], int *outcount, int array_of_indices[], MUK_Status array_of_statuses[])
{
    return MUK_Testsome(incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
}

int MPI_Topo_test(MUK_Comm comm, int *status)
{
    return MUK_Topo_test(comm, status);
}

int MPI_Type_commit(MUK_Datatype *datatype)
{
    return MUK_Type_commit(datatype);
}

int MPI_Type_contiguous(int count, MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_contiguous(count, oldtype, newtype);
}

int MPI_Type_contiguous_c(MUK_Count count, MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_contiguous_c(count, oldtype, newtype);
}

int MPI_Type_create_darray(int size, int rank, int ndims, const int array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_create_darray(size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, order, oldtype, newtype);
}

int MPI_Type_create_darray_c(int size, int rank, int ndims, const MUK_Count array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_create_darray_c(size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, order, oldtype, newtype);
}

int MPI_Type_create_f90_complex(int p, int r, MUK_Datatype *newtype)
{
    return MUK_Type_create_f90_complex(p, r, newtype);
}

int MPI_Type_create_f90_integer(int r, MUK_Datatype *newtype)
{
    return MUK_Type_create_f90_integer(r, newtype);
}

int MPI_Type_create_f90_real(int p, int r, MUK_Datatype *newtype)
{
    return MUK_Type_create_f90_real(p, r, newtype);
}

int MPI_Type_create_hindexed(int count, const int array_of_blocklengths[], const MUK_Aint array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_create_hindexed(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int MPI_Type_create_hindexed_block(int count, int blocklength, const MUK_Aint array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_create_hindexed_block(count, blocklength, array_of_displacements, oldtype, newtype);
}

int MPI_Type_create_hindexed_block_c(MUK_Count count, MUK_Count blocklength, const MUK_Count array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_create_hindexed_block_c(count, blocklength, array_of_displacements, oldtype, newtype);
}

int MPI_Type_create_hindexed_c(MUK_Count count, const MUK_Count array_of_blocklengths[], const MUK_Count array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_create_hindexed_c(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int MPI_Type_create_hvector(int count, int blocklength, MUK_Aint stride, MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_create_hvector(count, blocklength, stride, oldtype, newtype);
}

int MPI_Type_create_hvector_c(MUK_Count count, MUK_Count blocklength, MUK_Count stride, MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_create_hvector_c(count, blocklength, stride, oldtype, newtype);
}

int MPI_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_create_indexed_block(count, blocklength, array_of_displacements, oldtype, newtype);
}

int MPI_Type_create_indexed_block_c(MUK_Count count, MUK_Count blocklength, const MUK_Count array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_create_indexed_block_c(count, blocklength, array_of_displacements, oldtype, newtype);
}

int MPI_Type_create_keyval(MUK_Type_copy_attr_function *type_copy_attr_fn, MUK_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state)
{
    return MUK_Type_create_keyval(type_copy_attr_fn, type_delete_attr_fn, type_keyval, extra_state);
}

int MPI_Type_create_resized(MUK_Datatype oldtype, MUK_Aint lb, MUK_Aint extent, MUK_Datatype *newtype)
{
    return MUK_Type_create_resized(oldtype, lb, extent, newtype);
}

int MPI_Type_create_resized_c(MUK_Datatype oldtype, MUK_Count lb, MUK_Count extent, MUK_Datatype *newtype)
{
    return MUK_Type_create_resized_c(oldtype, lb, extent, newtype);
}

int MPI_Type_create_struct(int count, const int array_of_blocklengths[], const MUK_Aint array_of_displacements[], const MUK_Datatype array_of_types[], MUK_Datatype *newtype)
{
    return MUK_Type_create_struct(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype);
}

int MPI_Type_create_struct_c(MUK_Count count, const MUK_Count array_of_blocklengths[], const MUK_Count array_of_displacements[], const MUK_Datatype array_of_types[], MUK_Datatype *newtype)
{
    return MUK_Type_create_struct_c(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype);
}

int MPI_Type_create_subarray(int ndims, const int array_of_sizes[], const int array_of_subsizes[], const int array_of_starts[], int order, MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_create_subarray(ndims, array_of_sizes, array_of_subsizes, array_of_starts, order, oldtype, newtype);
}

int MPI_Type_create_subarray_c(int ndims, const MUK_Count array_of_sizes[], const MUK_Count array_of_subsizes[], const MUK_Count array_of_starts[], int order, MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_create_subarray_c(ndims, array_of_sizes, array_of_subsizes, array_of_starts, order, oldtype, newtype);
}

int MPI_Type_delete_attr(MUK_Datatype datatype, int type_keyval)
{
    return MUK_Type_delete_attr(datatype, type_keyval);
}

int MPI_Type_dup(MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_dup(oldtype, newtype);
}

int MPI_Type_extent(MUK_Datatype datatype, MUK_Aint *extent)
{
    return MUK_Type_extent(datatype, extent);
}

int MPI_Type_free(MUK_Datatype *datatype)
{
    return MUK_Type_free(datatype);
}

int MPI_Type_free_keyval(int *type_keyval)
{
    return MUK_Type_free_keyval(type_keyval);
}

int MPI_Type_get_attr(MUK_Datatype datatype, int type_keyval, void *attribute_val, int *flag)
{
    return MUK_Type_get_attr(datatype, type_keyval, attribute_val, flag);
}

int MPI_Type_get_contents(MUK_Datatype datatype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MUK_Aint array_of_addresses[], MUK_Datatype array_of_datatypes[])
{
    return MUK_Type_get_contents(datatype, max_integers, max_addresses, max_datatypes, array_of_integers, array_of_addresses, array_of_datatypes);
}

int MPI_Type_get_contents_c(MUK_Datatype datatype, MUK_Count max_integers, MUK_Count max_addresses, MUK_Count max_large_counts, MUK_Count max_datatypes, int array_of_integers[], MUK_Aint array_of_addresses[], MUK_Count array_of_large_counts[], MUK_Datatype array_of_datatypes[])
{
    return MUK_Type_get_contents_c(datatype, max_integers, max_addresses, max_large_counts, max_datatypes, array_of_integers, array_of_addresses, array_of_large_counts, array_of_datatypes);
}

int MPI_Type_get_envelope(MUK_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner)
{
    return MUK_Type_get_envelope(datatype, num_integers, num_addresses, num_datatypes, combiner);
}

int MPI_Type_get_envelope_c(MUK_Datatype datatype, MUK_Count *num_integers, MUK_Count *num_addresses, MUK_Count *num_large_counts, MUK_Count *num_datatypes, int *combiner)
{
    return MUK_Type_get_envelope_c(datatype, num_integers, num_addresses, num_large_counts, num_datatypes, combiner);
}

int MPI_Type_get_extent(MUK_Datatype datatype, MUK_Aint *lb, MUK_Aint *extent)
{
    return MUK_Type_get_extent(datatype, lb, extent);
}

int MPI_Type_get_extent_c(MUK_Datatype datatype, MUK_Count *lb, MUK_Count *extent)
{
    return MUK_Type_get_extent_c(datatype, lb, extent);
}

int MPI_Type_get_extent_x(MUK_Datatype datatype, MUK_Count *lb, MUK_Count *extent)
{
    return MUK_Type_get_extent_x(datatype, lb, extent);
}

int MPI_Type_get_name(MUK_Datatype datatype, char *type_name, int *resultlen)
{
    return MUK_Type_get_name(datatype, type_name, resultlen);
}

int MPI_Type_get_true_extent(MUK_Datatype datatype, MUK_Aint *true_lb, MUK_Aint *true_extent)
{
    return MUK_Type_get_true_extent(datatype, true_lb, true_extent);
}

int MPI_Type_get_true_extent_c(MUK_Datatype datatype, MUK_Count *true_lb, MUK_Count *true_extent)
{
    return MUK_Type_get_true_extent_c(datatype, true_lb, true_extent);
}

int MPI_Type_get_true_extent_x(MUK_Datatype datatype, MUK_Count *true_lb, MUK_Count *true_extent)
{
    return MUK_Type_get_true_extent_x(datatype, true_lb, true_extent);
}

int MPI_Type_hindexed(int count, int array_of_blocklengths[], MUK_Aint array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_hindexed(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int MPI_Type_hvector(int count, int blocklength, MUK_Aint stride, MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_hvector(count, blocklength, stride, oldtype, newtype);
}

int MPI_Type_indexed(int count, const int array_of_blocklengths[], const int array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_indexed(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int MPI_Type_indexed_c(MUK_Count count, const MUK_Count array_of_blocklengths[], const MUK_Count array_of_displacements[], MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_indexed_c(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int MPI_Type_lb(MUK_Datatype datatype, MUK_Aint *displacement)
{
    return MUK_Type_lb(datatype, displacement);
}

int MPI_Type_match_size(int typeclass, int size, MUK_Datatype *datatype)
{
    return MUK_Type_match_size(typeclass, size, datatype);
}

int MPI_Type_set_attr(MUK_Datatype datatype, int type_keyval, void *attribute_val)
{
    return MUK_Type_set_attr(datatype, type_keyval, attribute_val);
}

int MPI_Type_set_name(MUK_Datatype datatype, const char *type_name)
{
    return MUK_Type_set_name(datatype, type_name);
}

int MPI_Type_size(MUK_Datatype datatype, int *size)
{
    return MUK_Type_size(datatype, size);
}

int MPI_Type_size_c(MUK_Datatype datatype, MUK_Count *size)
{
    return MUK_Type_size_c(datatype, size);
}

int MPI_Type_size_x(MUK_Datatype datatype, MUK_Count *size)
{
    return MUK_Type_size_x(datatype, size);
}

int MPI_Type_struct(int count, int array_of_blocklengths[], MUK_Aint array_of_displacements[], MUK_Datatype array_of_types[], MUK_Datatype *newtype)
{
    return MUK_Type_struct(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype);
}

int MPI_Type_ub(MUK_Datatype datatype, MUK_Aint *displacement)
{
    return MUK_Type_ub(datatype, displacement);
}

int MPI_Type_vector(int count, int blocklength, int stride, MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_vector(count, blocklength, stride, oldtype, newtype);
}

int MPI_Type_vector_c(MUK_Count count, MUK_Count blocklength, MUK_Count stride, MUK_Datatype oldtype, MUK_Datatype *newtype)
{
    return MUK_Type_vector_c(count, blocklength, stride, oldtype, newtype);
}

int MPI_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, MUK_Datatype datatype, MUK_Comm comm)
{
    return MUK_Unpack(inbuf, insize, position, outbuf, outcount, datatype, comm);
}

int MPI_Unpack_c(const void *inbuf, MUK_Count insize, MUK_Count *position, void *outbuf, MUK_Count outcount, MUK_Datatype datatype, MUK_Comm comm)
{
    return MUK_Unpack_c(inbuf, insize, position, outbuf, outcount, datatype, comm);
}

int MPI_Unpack_external(const char datarep[], const void *inbuf, MUK_Aint insize, MUK_Aint *position, void *outbuf, int outcount, MUK_Datatype datatype)
{
    return MUK_Unpack_external(datarep, inbuf, insize, position, outbuf, outcount, datatype);
}

int MPI_Unpack_external_c(const char datarep[], const void *inbuf, MUK_Count insize, MUK_Count *position, void *outbuf, MUK_Count outcount, MUK_Datatype datatype)
{
    return MUK_Unpack_external_c(datarep, inbuf, insize, position, outbuf, outcount, datatype);
}

int MPI_Unpublish_name(const char *service_name, MUK_Info info, const char *port_name)
{
    return MUK_Unpublish_name(service_name, info, port_name);
}

int MPI_Wait(MUK_Request *request, MUK_Status *status)
{
    return MUK_Wait(request, status);
}

int MPI_Waitall(int count, MUK_Request array_of_requests[], MUK_Status array_of_statuses[])
{
    return MUK_Waitall(count, array_of_requests, array_of_statuses);
}

int MPI_Waitany(int count, MUK_Request array_of_requests[], int *indx, MUK_Status *status)
{
    return MUK_Waitany(count, array_of_requests, indx, status);
}

int MPI_Waitsome(int incount, MUK_Request array_of_requests[], int *outcount, int array_of_indices[], MUK_Status array_of_statuses[])
{
    return MUK_Waitsome(incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
}

int MPI_Win_allocate(MUK_Aint size, int disp_unit, MUK_Info info, MUK_Comm comm, void *baseptr, MUK_Win *win)
{
    return MUK_Win_allocate(size, disp_unit, info, comm, baseptr, win);
}

int MPI_Win_allocate_c(MUK_Aint size, MUK_Aint disp_unit, MUK_Info info, MUK_Comm comm, void *baseptr, MUK_Win *win)
{
    return MUK_Win_allocate_c(size, disp_unit, info, comm, baseptr, win);
}

int MPI_Win_allocate_shared(MUK_Aint size, int disp_unit, MUK_Info info, MUK_Comm comm, void *baseptr, MUK_Win *win)
{
    return MUK_Win_allocate_shared(size, disp_unit, info, comm, baseptr, win);
}

int MPI_Win_allocate_shared_c(MUK_Aint size, MUK_Aint disp_unit, MUK_Info info, MUK_Comm comm, void *baseptr, MUK_Win *win)
{
    return MUK_Win_allocate_shared_c(size, disp_unit, info, comm, baseptr, win);
}

int MPI_Win_attach(MUK_Win win, void *base, MUK_Aint size)
{
    return MUK_Win_attach(win, base, size);
}

int MPI_Win_call_errhandler(MUK_Win win, int errorcode)
{
    return MUK_Win_call_errhandler(win, errorcode);
}

int MPI_Win_complete(MUK_Win win)
{
    return MUK_Win_complete(win);
}

int MPI_Win_create(void *base, MUK_Aint size, int disp_unit, MUK_Info info, MUK_Comm comm, MUK_Win *win)
{
    return MUK_Win_create(base, size, disp_unit, info, comm, win);
}

int MPI_Win_create_c(void *base, MUK_Aint size, MUK_Aint disp_unit, MUK_Info info, MUK_Comm comm, MUK_Win *win)
{
    return MUK_Win_create_c(base, size, disp_unit, info, comm, win);
}

int MPI_Win_create_dynamic(MUK_Info info, MUK_Comm comm, MUK_Win *win)
{
    return MUK_Win_create_dynamic(info, comm, win);
}

int MPI_Win_create_errhandler(MUK_Win_errhandler_function *win_errhandler_fn, MUK_Errhandler *errhandler)
{
    return MUK_Win_create_errhandler(win_errhandler_fn, errhandler);
}

int MPI_Win_create_keyval(MUK_Win_copy_attr_function *win_copy_attr_fn, MUK_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state)
{
    return MUK_Win_create_keyval(win_copy_attr_fn, win_delete_attr_fn, win_keyval, extra_state);
}

int MPI_Win_delete_attr(MUK_Win win, int win_keyval)
{
    return MUK_Win_delete_attr(win, win_keyval);
}

int MPI_Win_detach(MUK_Win win, const void *base)
{
    return MUK_Win_detach(win, base);
}

int MPI_Win_fence(int assert, MUK_Win win)
{
    return MUK_Win_fence(assert, win);
}

int MPI_Win_flush(int rank, MUK_Win win)
{
    return MUK_Win_flush(rank, win);
}

int MPI_Win_flush_all(MUK_Win win)
{
    return MUK_Win_flush_all(win);
}

int MPI_Win_flush_local(int rank, MUK_Win win)
{
    return MUK_Win_flush_local(rank, win);
}

int MPI_Win_flush_local_all(MUK_Win win)
{
    return MUK_Win_flush_local_all(win);
}

int MPI_Win_free(MUK_Win *win)
{
    return MUK_Win_free(win);
}

int MPI_Win_free_keyval(int *win_keyval)
{
    return MUK_Win_free_keyval(win_keyval);
}

int MPI_Win_get_attr(MUK_Win win, int win_keyval, void *attribute_val, int *flag)
{
    return MUK_Win_get_attr(win, win_keyval, attribute_val, flag);
}

int MPI_Win_get_errhandler(MUK_Win win, MUK_Errhandler *errhandler)
{
    return MUK_Win_get_errhandler(win, errhandler);
}

int MPI_Win_get_group(MUK_Win win, MUK_Group *group)
{
    return MUK_Win_get_group(win, group);
}

int MPI_Win_get_info(MUK_Win win, MUK_Info *info_used)
{
    return MUK_Win_get_info(win, info_used);
}

int MPI_Win_get_name(MUK_Win win, char *win_name, int *resultlen)
{
    return MUK_Win_get_name(win, win_name, resultlen);
}

int MPI_Win_lock(int lock_type, int rank, int assert, MUK_Win win)
{
    return MUK_Win_lock(lock_type, rank, assert, win);
}

int MPI_Win_lock_all(int assert, MUK_Win win)
{
    return MUK_Win_lock_all(assert, win);
}

int MPI_Win_post(MUK_Group group, int assert, MUK_Win win)
{
    return MUK_Win_post(group, assert, win);
}

int MPI_Win_set_attr(MUK_Win win, int win_keyval, void *attribute_val)
{
    return MUK_Win_set_attr(win, win_keyval, attribute_val);
}

int MPI_Win_set_errhandler(MUK_Win win, MUK_Errhandler errhandler)
{
    return MUK_Win_set_errhandler(win, errhandler);
}

int MPI_Win_set_info(MUK_Win win, MUK_Info info)
{
    return MUK_Win_set_info(win, info);
}

int MPI_Win_set_name(MUK_Win win, const char *win_name)
{
    return MUK_Win_set_name(win, win_name);
}

int MPI_Win_shared_query(MUK_Win win, int rank, MUK_Aint *size, int *disp_unit, void *baseptr)
{
    return MUK_Win_shared_query(win, rank, size, disp_unit, baseptr);
}

int MPI_Win_shared_query_c(MUK_Win win, int rank, MUK_Aint *size, MUK_Aint *disp_unit, void *baseptr)
{
    return MUK_Win_shared_query_c(win, rank, size, disp_unit, baseptr);
}

int MPI_Win_start(MUK_Group group, int assert, MUK_Win win)
{
    return MUK_Win_start(group, assert, win);
}

int MPI_Win_sync(MUK_Win win)
{
    return MUK_Win_sync(win);
}

int MPI_Win_test(MUK_Win win, int *flag)
{
    return MUK_Win_test(win, flag);
}

int MPI_Win_unlock(int rank, MUK_Win win)
{
    return MUK_Win_unlock(rank, win);
}

int MPI_Win_unlock_all(MUK_Win win)
{
    return MUK_Win_unlock_all(win);
}

int MPI_Win_wait(MUK_Win win)
{
    return MUK_Win_wait(win);
}


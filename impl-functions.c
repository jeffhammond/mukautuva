#include "muk-dl.h"
#include "muk-predefined.h"

// status typedef
typedef struct
{
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    int __kielletty__[5];
}
WRAP_Status;

// this is the MPI implementation header
#include <mpi.h>

// SUPPORT_F08 enables F08 stuff I am ignoring for now

#ifdef SUPPORT_F08
// status typedef
typedef struct
{
    MPI_Fint MPI_SOURCE;
    MPI_Fint MPI_TAG;
    MPI_Fint MPI_ERROR;
    MPI_Fint __kielletty__[5];
}
WRAP_F08_status;
#endif

typedef MPI_Aint IMPL_Aint;
typedef MPI_Count IMPL_Count;
typedef MPI_Offset IMPL_Offset;

// these live in impl-predefined.c
extern MPI_Request IMPL_REQUEST_NULL;
extern MPI_Datatype IMPL_DATATYPE_NULL;
extern MPI_Op IMPL_OP_NULL;
extern MPI_Errhandler IMPL_ERRHANDLER_NULL;
extern MPI_Info IMPL_INFO_NULL;
extern MPI_Win IMPL_WIN_NULL;
extern MPI_File IMPL_FILE_NULL;
extern MPI_Comm IMPL_COMM_NULL;
//extern MPI_Comm IMPL_COMM_WORLD;
//extern MPI_Comm IMPL_COMM_SELF;
extern MPI_Group IMPL_GROUP_NULL;
extern MPI_Group IMPL_GROUP_EMPTY;
extern MPI_Message IMPL_MESSAGE_NULL;
#if MPI_VERSION >= 4
extern MPI_Session IMPL_SESSION_NULL;
#endif
//extern MPI_Message IMPL_MESSAGE_NO_PROC;
extern MPI_Status* IMPL_STATUS_IGNORE;
extern MPI_Status* IMPL_STATUSES_IGNORE;

int (*IMPL_Finalized)(int * finalized);
int (*IMPL_Comm_rank)(MPI_Comm comm, int *rank);
int (*IMPL_Comm_size)(MPI_Comm comm, int *size);
int (*IMPL_Abort)(MPI_Comm comm, int errorcode);
int (*IMPL_Accumulate)(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win);
int (*IMPL_Accumulate_c)(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win);
int (*IMPL_Add_error_class)(int *errorclass);
int (*IMPL_Add_error_code)(int errorclass, int *errorcode);
int (*IMPL_Add_error_string)(int errorcode, const char *string);
int (*IMPL_Address)(void *location, MPI_Aint *address);
MPI_Aint (*IMPL_Aint_add)(MPI_Aint base, MPI_Aint disp);
MPI_Aint (*IMPL_Aint_diff)(MPI_Aint addr1, MPI_Aint addr2);
int (*IMPL_Allgather)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Allgather_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Allgather_init)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Allgather_init_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Allgatherv)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Allgatherv_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Allgatherv_init)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Allgatherv_init_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Alloc_mem)(MPI_Aint size, MPI_Info info, void *baseptr);
int (*IMPL_Allreduce)(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int (*IMPL_Allreduce_c)(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int (*IMPL_Allreduce_init)(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Allreduce_init_c)(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Alltoall)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Alltoall_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Alltoall_init)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Alltoall_init_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Alltoallv)(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Alltoallv_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Alltoallv_init)(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Alltoallv_init_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Alltoallw)(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm);
int (*IMPL_Alltoallw_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm);
int (*IMPL_Alltoallw_init)(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Alltoallw_init_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Attr_delete)(MPI_Comm comm, int keyval);
int (*IMPL_Attr_get)(MPI_Comm comm, int keyval, void *attribute_val, int *flag);
int (*IMPL_Attr_put)(MPI_Comm comm, int keyval, void *attribute_val);
int (*IMPL_Barrier)(MPI_Comm comm);
int (*IMPL_Barrier_init)(MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Bcast)(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm);
int (*IMPL_Bcast_c)(void *buffer, MPI_Count count, MPI_Datatype datatype, int root, MPI_Comm comm);
int (*IMPL_Bcast_init)(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Bcast_init_c)(void *buffer, MPI_Count count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Bsend)(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int (*IMPL_Bsend_c)(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int (*IMPL_Bsend_init)(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Bsend_init_c)(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Buffer_attach)(void *buffer, int size);
int (*IMPL_Buffer_attach_c)(void *buffer, MPI_Count size);
int (*IMPL_Buffer_detach)(void *buffer_addr, int *size);
int (*IMPL_Buffer_detach_c)(void *buffer_addr, MPI_Count *size);
int (*IMPL_Cancel)(MPI_Request *request);
int (*IMPL_Cart_coords)(MPI_Comm comm, int rank, int maxdims, int coords[]);
int (*IMPL_Cart_create)(MPI_Comm comm_old, int ndims, const int dims[], const int periods[], int reorder, MPI_Comm *comm_cart);
int (*IMPL_Cart_get)(MPI_Comm comm, int maxdims, int dims[], int periods[], int coords[]);
int (*IMPL_Cart_map)(MPI_Comm comm, int ndims, const int dims[], const int periods[], int *newrank);
int (*IMPL_Cart_rank)(MPI_Comm comm, const int coords[], int *rank);
int (*IMPL_Cart_shift)(MPI_Comm comm, int direction, int disp, int *rank_source, int *rank_dest);
int (*IMPL_Cart_sub)(MPI_Comm comm, const int remain_dims[], MPI_Comm *newcomm);
int (*IMPL_Cartdim_get)(MPI_Comm comm, int *ndims);
int (*IMPL_Close_port)(const char *port_name);
int (*IMPL_Comm_accept)(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm);
int (*IMPL_Comm_call_errhandler)(MPI_Comm comm, int errorcode);
int (*IMPL_Comm_compare)(MPI_Comm comm1, MPI_Comm comm2, int *result);
int (*IMPL_Comm_connect)(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm);
int (*IMPL_Comm_create)(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm);
int (*IMPL_Comm_create_errhandler)(MPI_Comm_errhandler_function *comm_errhandler_fn, MPI_Errhandler *errhandler);
int (*IMPL_Comm_create_from_group)(MPI_Group group, const char *stringtag, MPI_Info info, MPI_Errhandler errhandler, MPI_Comm *newcomm);
int (*IMPL_Comm_create_group)(MPI_Comm comm, MPI_Group group, int tag, MPI_Comm *newcomm);
int (*IMPL_Comm_create_keyval)(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state);
int (*IMPL_Comm_delete_attr)(MPI_Comm comm, int comm_keyval);
int (*IMPL_Comm_disconnect)(MPI_Comm *comm);
int (*IMPL_Comm_dup)(MPI_Comm comm, MPI_Comm *newcomm);
int (*IMPL_Comm_dup_with_info)(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm);
int (*IMPL_Comm_free)(MPI_Comm *comm);
int (*IMPL_Comm_free_keyval)(int *comm_keyval);
int (*IMPL_Comm_get_attr)(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag);
int (*IMPL_Comm_get_errhandler)(MPI_Comm comm, MPI_Errhandler *errhandler);
int (*IMPL_Comm_get_info)(MPI_Comm comm, MPI_Info *info_used);
int (*IMPL_Comm_get_name)(MPI_Comm comm, char *comm_name, int *resultlen);
int (*IMPL_Comm_get_parent)(MPI_Comm *parent);
int (*IMPL_Comm_group)(MPI_Comm comm, MPI_Group *group);
int (*IMPL_Comm_idup)(MPI_Comm comm, MPI_Comm *newcomm, MPI_Request *request);
int (*IMPL_Comm_idup_with_info)(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm, MPI_Request *request);
int (*IMPL_Comm_join)(int fd, MPI_Comm *intercomm);
int (*IMPL_Comm_remote_group)(MPI_Comm comm, MPI_Group *group);
int (*IMPL_Comm_remote_size)(MPI_Comm comm, int *size);
int (*IMPL_Comm_set_attr)(MPI_Comm comm, int comm_keyval, void *attribute_val);
int (*IMPL_Comm_set_errhandler)(MPI_Comm comm, MPI_Errhandler errhandler);
int (*IMPL_Comm_set_info)(MPI_Comm comm, MPI_Info info);
int (*IMPL_Comm_set_name)(MPI_Comm comm, const char *comm_name);
int (*IMPL_Comm_split)(MPI_Comm comm, int color, int key, MPI_Comm *newcomm);
int (*IMPL_Comm_split_type)(MPI_Comm comm, int split_type, int key, MPI_Info info, MPI_Comm *newcomm);
int (*IMPL_Comm_test_inter)(MPI_Comm comm, int *flag);
int (*IMPL_Compare_and_swap)(const void *origin_addr, const void *compare_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Win win);
int (*IMPL_Dims_create)(int nnodes, int ndims, int dims[]);
int (*IMPL_Dist_graph_create)(MPI_Comm comm_old, int n, const int sources[], const int degrees[], const int destinations[], const int weights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph);
int (*IMPL_Dist_graph_create_adjacent)(MPI_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph);
int (*IMPL_Dist_graph_neighbors)(MPI_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[]);
int (*IMPL_Dist_graph_neighbors_count)(MPI_Comm comm, int *indegree, int *outdegree, int *weighted);
int (*IMPL_Errhandler_create)(MPI_Comm_errhandler_function *comm_errhandler_fn, MPI_Errhandler *errhandler);
int (*IMPL_Errhandler_free)(MPI_Errhandler *errhandler);
int (*IMPL_Errhandler_get)(MPI_Comm comm, MPI_Errhandler *errhandler);
int (*IMPL_Errhandler_set)(MPI_Comm comm, MPI_Errhandler errhandler);
int (*IMPL_Error_class)(int errorcode, int *errorclass);
int (*IMPL_Error_string)(int errorcode, char *string, int *resultlen);
int (*IMPL_Exscan)(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int (*IMPL_Exscan_c)(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int (*IMPL_Exscan_init)(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Exscan_init_c)(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Fetch_and_op)(const void *origin_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Op op, MPI_Win win);
int (*IMPL_File_call_errhandler)(MPI_File fh, int errorcode);
int (*IMPL_File_close)(MPI_File *fh);
int (*IMPL_File_create_errhandler)(MPI_File_errhandler_function *file_errhandler_fn, MPI_Errhandler *errhandler);
int (*IMPL_File_delete)(const char *filename, MPI_Info info);
int (*IMPL_File_get_amode)(MPI_File fh, int *amode);
int (*IMPL_File_get_atomicity)(MPI_File fh, int *flag);
int (*IMPL_File_get_byte_offset)(MPI_File fh, MPI_Offset offset, MPI_Offset *disp);
int (*IMPL_File_get_errhandler)(MPI_File file, MPI_Errhandler *errhandler);
int (*IMPL_File_get_group)(MPI_File fh, MPI_Group *group);
int (*IMPL_File_get_info)(MPI_File fh, MPI_Info *info_used);
int (*IMPL_File_get_position)(MPI_File fh, MPI_Offset *offset);
int (*IMPL_File_get_position_shared)(MPI_File fh, MPI_Offset *offset);
int (*IMPL_File_get_size)(MPI_File fh, MPI_Offset *size);
int (*IMPL_File_get_type_extent)(MPI_File fh, MPI_Datatype datatype, MPI_Aint *extent);
int (*IMPL_File_get_type_extent_c)(MPI_File fh, MPI_Datatype datatype, MPI_Count *extent);
int (*IMPL_File_get_view)(MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep);
int (*IMPL_File_iread)(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iread_all)(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iread_all_c)(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iread_at)(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iread_at_all)(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iread_at_all_c)(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iread_at_c)(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iread_c)(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iread_shared)(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iread_shared_c)(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iwrite)(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iwrite_all)(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iwrite_all_c)(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iwrite_at)(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iwrite_at_all)(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iwrite_at_all_c)(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iwrite_at_c)(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iwrite_c)(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iwrite_shared)(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_iwrite_shared_c)(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request);
int (*IMPL_File_open)(MPI_Comm comm, const char *filename, int amode, MPI_Info info, MPI_File *fh);
int (*IMPL_File_preallocate)(MPI_File fh, MPI_Offset size);
int (*IMPL_File_read)(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_read_all)(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_read_all_begin)(MPI_File fh, void *buf, int count, MPI_Datatype datatype);
int (*IMPL_File_read_all_begin_c)(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype);
int (*IMPL_File_read_all_c)(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_read_all_end)(MPI_File fh, void *buf, MPI_Status *status);
int (*IMPL_File_read_at)(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_read_at_all)(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_read_at_all_begin)(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype);
int (*IMPL_File_read_at_all_begin_c)(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype);
int (*IMPL_File_read_at_all_c)(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_read_at_all_end)(MPI_File fh, void *buf, MPI_Status *status);
int (*IMPL_File_read_at_c)(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_read_c)(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_read_ordered)(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_read_ordered_begin)(MPI_File fh, void *buf, int count, MPI_Datatype datatype);
int (*IMPL_File_read_ordered_begin_c)(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype);
int (*IMPL_File_read_ordered_c)(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_read_ordered_end)(MPI_File fh, void *buf, MPI_Status *status);
int (*IMPL_File_read_shared)(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_read_shared_c)(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_seek)(MPI_File fh, MPI_Offset offset, int whence);
int (*IMPL_File_seek_shared)(MPI_File fh, MPI_Offset offset, int whence);
int (*IMPL_File_set_atomicity)(MPI_File fh, int flag);
int (*IMPL_File_set_errhandler)(MPI_File file, MPI_Errhandler errhandler);
int (*IMPL_File_set_info)(MPI_File fh, MPI_Info info);
int (*IMPL_File_set_size)(MPI_File fh, MPI_Offset size);
int (*IMPL_File_set_view)(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char *datarep, MPI_Info info);
int (*IMPL_File_sync)(MPI_File fh);
int (*IMPL_File_write)(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_write_all)(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_write_all_begin)(MPI_File fh, const void *buf, int count, MPI_Datatype datatype);
int (*IMPL_File_write_all_begin_c)(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype);
int (*IMPL_File_write_all_c)(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_write_all_end)(MPI_File fh, const void *buf, MPI_Status *status);
int (*IMPL_File_write_at)(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_write_at_all)(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_write_at_all_begin)(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype);
int (*IMPL_File_write_at_all_begin_c)(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype);
int (*IMPL_File_write_at_all_c)(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_write_at_all_end)(MPI_File fh, const void *buf, MPI_Status *status);
int (*IMPL_File_write_at_c)(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_write_c)(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_write_ordered)(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_write_ordered_begin)(MPI_File fh, const void *buf, int count, MPI_Datatype datatype);
int (*IMPL_File_write_ordered_begin_c)(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype);
int (*IMPL_File_write_ordered_c)(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_write_ordered_end)(MPI_File fh, const void *buf, MPI_Status *status);
int (*IMPL_File_write_shared)(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_File_write_shared_c)(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status);
int (*IMPL_Free_mem)(void *base);
int (*IMPL_Gather)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int (*IMPL_Gather_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int (*IMPL_Gather_init)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Gather_init_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Gatherv)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm);
int (*IMPL_Gatherv_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm);
int (*IMPL_Gatherv_init)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Gatherv_init_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Get)(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win);
int (*IMPL_Get_accumulate)(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win);
int (*IMPL_Get_accumulate_c)(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, void *result_addr, MPI_Count result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win);
int (*IMPL_Get_address)(const void *location, MPI_Aint *address);
int (*IMPL_Get_c)(void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win);
int (*IMPL_Get_count)(const MPI_Status *status, MPI_Datatype datatype, int *count);
int (*IMPL_Get_count_c)(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count);
int (*IMPL_Get_elements)(const MPI_Status *status, MPI_Datatype datatype, int *count);
int (*IMPL_Get_elements_c)(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count);
int (*IMPL_Get_elements_x)(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count);
int (*IMPL_Graph_create)(MPI_Comm comm_old, int nnodes, const int indx[], const int edges[], int reorder, MPI_Comm *comm_graph);
int (*IMPL_Graph_get)(MPI_Comm comm, int maxindex, int maxedges, int indx[], int edges[]);
int (*IMPL_Graph_map)(MPI_Comm comm, int nnodes, const int indx[], const int edges[], int *newrank);
int (*IMPL_Graph_neighbors)(MPI_Comm comm, int rank, int maxneighbors, int neighbors[]);
int (*IMPL_Graph_neighbors_count)(MPI_Comm comm, int rank, int *nneighbors);
int (*IMPL_Graphdims_get)(MPI_Comm comm, int *nnodes, int *nedges);
int (*IMPL_Grequest_complete)(MPI_Request request);
int (*IMPL_Grequest_start)(MPI_Grequest_query_function *query_fn, MPI_Grequest_free_function *free_fn, MPI_Grequest_cancel_function *cancel_fn, void *extra_state, MPI_Request *request);
int (*IMPL_Group_compare)(MPI_Group group1, MPI_Group group2, int *result);
int (*IMPL_Group_difference)(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
int (*IMPL_Group_excl)(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup);
int (*IMPL_Group_free)(MPI_Group *group);
#if MPI_VERSION >= 4
int (*IMPL_Group_from_session_pset)(MPI_Session session, const char *pset_name, MPI_Group *newgroup);
#endif
int (*IMPL_Group_incl)(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup);
int (*IMPL_Group_intersection)(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
int (*IMPL_Group_range_excl)(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup);
int (*IMPL_Group_range_incl)(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup);
int (*IMPL_Group_rank)(MPI_Group group, int *rank);
int (*IMPL_Group_size)(MPI_Group group, int *size);
int (*IMPL_Group_translate_ranks)(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[]);
int (*IMPL_Group_union)(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
int (*IMPL_Iallgather)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Iallgather_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Iallgatherv)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Iallgatherv_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Iallreduce)(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Iallreduce_c)(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ialltoall)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ialltoall_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ialltoallv)(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ialltoallv_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ialltoallw)(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ialltoallw_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ibarrier)(MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ibcast)(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ibcast_c)(void *buffer, MPI_Count count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ibsend)(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ibsend_c)(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Iexscan)(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Iexscan_c)(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Igather)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Igather_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Igatherv)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Igatherv_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Improbe)(int source, int tag, MPI_Comm comm, int *flag, MPI_Message *message, MPI_Status *status);
int (*IMPL_Imrecv)(void *buf, int count, MPI_Datatype datatype, MPI_Message *message, MPI_Request *request);
int (*IMPL_Imrecv_c)(void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Message *message, MPI_Request *request);
int (*IMPL_Ineighbor_allgather)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ineighbor_allgather_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ineighbor_allgatherv)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ineighbor_allgatherv_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ineighbor_alltoall)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ineighbor_alltoall_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ineighbor_alltoallv)(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ineighbor_alltoallv_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ineighbor_alltoallw)(const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ineighbor_alltoallw_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request);
int (*IMPL_Info_create)(MPI_Info *info);
int (*IMPL_Info_create_env)(int argc, char *argv[], MPI_Info *info);
int (*IMPL_Info_delete)(MPI_Info info, const char *key);
int (*IMPL_Info_dup)(MPI_Info info, MPI_Info *newinfo);
int (*IMPL_Info_free)(MPI_Info *info);
int (*IMPL_Info_get)(MPI_Info info, const char *key, int valuelen, char *value, int *flag);
int (*IMPL_Info_get_nkeys)(MPI_Info info, int *nkeys);
int (*IMPL_Info_get_nthkey)(MPI_Info info, int n, char *key);
int (*IMPL_Info_get_string)(MPI_Info info, const char *key, int *buflen, char *value, int *flag);
int (*IMPL_Info_get_valuelen)(MPI_Info info, const char *key, int *valuelen, int *flag);
int (*IMPL_Info_set)(MPI_Info info, const char *key, const char *value);
int (*IMPL_Intercomm_create)(MPI_Comm local_comm, int local_leader, MPI_Comm peer_comm, int remote_leader, int tag, MPI_Comm *newintercomm);
int (*IMPL_Intercomm_create_from_groups)(MPI_Group local_group, int local_leader, MPI_Group remote_group, int remote_leader, const char *stringtag, MPI_Info info, MPI_Errhandler errhandler, MPI_Comm *newintercomm);
int (*IMPL_Intercomm_merge)(MPI_Comm intercomm, int high, MPI_Comm *newintracomm);
int (*IMPL_Iprobe)(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status);
int (*IMPL_Irecv)(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Irecv_c)(void *buf, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ireduce)(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ireduce_c)(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ireduce_scatter)(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ireduce_scatter_block)(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ireduce_scatter_block_c)(const void *sendbuf, void *recvbuf, MPI_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ireduce_scatter_c)(const void *sendbuf, void *recvbuf, const MPI_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Irsend)(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Irsend_c)(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Iscan)(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Iscan_c)(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Iscatter)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Iscatter_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Iscatterv)(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Iscatterv_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint displs[], MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Isend)(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Isend_c)(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Isendrecv)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Isendrecv_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Isendrecv_replace)(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Isendrecv_replace_c)(void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Issend)(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Issend_c)(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Keyval_create)(MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state);
int (*IMPL_Keyval_free)(int *keyval);
int (*IMPL_Lookup_name)(const char *service_name, MPI_Info info, char *port_name);
int (*IMPL_Mprobe)(int source, int tag, MPI_Comm comm, MPI_Message *message, MPI_Status *status);
int (*IMPL_Mrecv)(void *buf, int count, MPI_Datatype datatype, MPI_Message *message, MPI_Status *status);
int (*IMPL_Mrecv_c)(void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Message *message, MPI_Status *status);
int (*IMPL_Neighbor_allgather)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Neighbor_allgather_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Neighbor_allgather_init)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Neighbor_allgather_init_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Neighbor_allgatherv)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Neighbor_allgatherv_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Neighbor_allgatherv_init)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Neighbor_allgatherv_init_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Neighbor_alltoall)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Neighbor_alltoall_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Neighbor_alltoall_init)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Neighbor_alltoall_init_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Neighbor_alltoallv)(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Neighbor_alltoallv_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm);
int (*IMPL_Neighbor_alltoallv_init)(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Neighbor_alltoallv_init_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Neighbor_alltoallw)(const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm);
int (*IMPL_Neighbor_alltoallw_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm);
int (*IMPL_Neighbor_alltoallw_init)(const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Neighbor_alltoallw_init_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Op_commutative)(MPI_Op op, int *commute);
int (*IMPL_Op_create)(MPI_User_function *user_fn, int commute, MPI_Op *op);
#if MPI_VERSION >= 4
int (*IMPL_Op_create_c)(MPI_User_function_c *user_fn, int commute, MPI_Op *op);
#endif
int (*IMPL_Op_free)(MPI_Op *op);
int (*IMPL_Open_port)(MPI_Info info, char *port_name);
int (*IMPL_Pack)(const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm);
int (*IMPL_Pack_c)(const void *inbuf, MPI_Count incount, MPI_Datatype datatype, void *outbuf, MPI_Count outsize, MPI_Count *position, MPI_Comm comm);
int (*IMPL_Pack_external)(const char *datarep, const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, MPI_Aint outsize, MPI_Aint *position);
int (*IMPL_Pack_external_c)(const char *datarep, const void *inbuf, MPI_Count incount, MPI_Datatype datatype, void *outbuf, MPI_Count outsize, MPI_Count *position);
int (*IMPL_Pack_external_size)(const char *datarep, int incount, MPI_Datatype datatype, MPI_Aint *size);
int (*IMPL_Pack_external_size_c)(const char *datarep, MPI_Count incount, MPI_Datatype datatype, MPI_Count *size);
int (*IMPL_Pack_size)(int incount, MPI_Datatype datatype, MPI_Comm comm, int *size);
int (*IMPL_Pack_size_c)(MPI_Count incount, MPI_Datatype datatype, MPI_Comm comm, MPI_Count *size);
int (*IMPL_Parrived)(MPI_Request request, int partition, int *flag);
int (*IMPL_Pcontrol)(const int level, ...);
int (*IMPL_Pready)(int partition, MPI_Request request);
int (*IMPL_Pready_list)(int length, const int array_of_partitions[], MPI_Request request);
int (*IMPL_Pready_range)(int partition_low, int partition_high, MPI_Request request);
int (*IMPL_Precv_init)(void *buf, int partitions, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Probe)(int source, int tag, MPI_Comm comm, MPI_Status *status);
int (*IMPL_Psend_init)(const void *buf, int partitions, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Publish_name)(const char *service_name, MPI_Info info, const char *port_name);
int (*IMPL_Put)(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win);
int (*IMPL_Put_c)(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win);
int (*IMPL_Raccumulate)(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request);
int (*IMPL_Raccumulate_c)(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request);
int (*IMPL_Recv)(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
int (*IMPL_Recv_c)(void *buf, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
int (*IMPL_Recv_init)(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Recv_init_c)(void *buf, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Reduce)(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
int (*IMPL_Reduce_c)(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
int (*IMPL_Reduce_init)(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Reduce_init_c)(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Reduce_local)(const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op);
int (*IMPL_Reduce_local_c)(const void *inbuf, void *inoutbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op);
int (*IMPL_Reduce_scatter)(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int (*IMPL_Reduce_scatter_block)(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int (*IMPL_Reduce_scatter_block_c)(const void *sendbuf, void *recvbuf, MPI_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int (*IMPL_Reduce_scatter_block_init)(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Reduce_scatter_block_init_c)(const void *sendbuf, void *recvbuf, MPI_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Reduce_scatter_c)(const void *sendbuf, void *recvbuf, const MPI_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int (*IMPL_Reduce_scatter_init)(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Reduce_scatter_init_c)(const void *sendbuf, void *recvbuf, const MPI_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Register_datarep)(const char *datarep, MPI_Datarep_conversion_function *read_conversion_fn, MPI_Datarep_conversion_function *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state);
#if MPI_VERSION >= 4
int (*IMPL_Register_datarep_c)(const char *datarep, MPI_Datarep_conversion_function_c *read_conversion_fn, MPI_Datarep_conversion_function_c *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state);
#endif
int (*IMPL_Request_free)(MPI_Request *request);
int (*IMPL_Request_get_status)(MPI_Request request, int *flag, MPI_Status *status);
int (*IMPL_Rget)(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request);
int (*IMPL_Rget_accumulate)(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request);
int (*IMPL_Rget_accumulate_c)(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, void *result_addr, MPI_Count result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request);
int (*IMPL_Rget_c)(void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request);
int (*IMPL_Rput)(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request);
int (*IMPL_Rput_c)(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request);
int (*IMPL_Rsend)(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int (*IMPL_Rsend_c)(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int (*IMPL_Rsend_init)(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Rsend_init_c)(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Scan)(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int (*IMPL_Scan_c)(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int (*IMPL_Scan_init)(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Scan_init_c)(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Scatter)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int (*IMPL_Scatter_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int (*IMPL_Scatter_init)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Scatter_init_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Scatterv)(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int (*IMPL_Scatterv_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint displs[], MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int (*IMPL_Scatterv_init)(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Scatterv_init_c)(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint displs[], MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request);
int (*IMPL_Send)(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int (*IMPL_Send_c)(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int (*IMPL_Send_init)(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Send_init_c)(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Sendrecv)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status);
int (*IMPL_Sendrecv_c)(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status);
int (*IMPL_Sendrecv_replace)(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status);
int (*IMPL_Sendrecv_replace_c)(void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status);
#if MPI_VERSION >= 4
int (*IMPL_Session_call_errhandler)(MPI_Session session, int errorcode);
int (*IMPL_Session_create_errhandler)(MPI_Session_errhandler_function *session_errhandler_fn, MPI_Errhandler *errhandler);
int (*IMPL_Session_finalize)(MPI_Session *session);
int (*IMPL_Session_get_errhandler)(MPI_Session session, MPI_Errhandler *errhandler);
int (*IMPL_Session_get_info)(MPI_Session session, MPI_Info *info_used);
int (*IMPL_Session_get_nth_pset)(MPI_Session session, MPI_Info info, int n, int *pset_len, char *pset_name);
int (*IMPL_Session_get_num_psets)(MPI_Session session, MPI_Info info, int *npset_names);
int (*IMPL_Session_get_pset_info)(MPI_Session session, const char *pset_name, MPI_Info *info);
int (*IMPL_Session_init)(MPI_Info info, MPI_Errhandler errhandler, MPI_Session *session);
int (*IMPL_Session_set_errhandler)(MPI_Session session, MPI_Errhandler errhandler);
#endif
int (*IMPL_Ssend)(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int (*IMPL_Ssend_c)(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int (*IMPL_Ssend_init)(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Ssend_init_c)(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int (*IMPL_Start)(MPI_Request *request);
int (*IMPL_Startall)(int count, MPI_Request array_of_requests[]);
#ifdef SUPPORT_F08
int (*IMPL_Status_f082c)(const MPI_F08_status *f08_status, MPI_Status *c_status);
int (*IMPL_Status_f082f)(const MPI_F08_status *f08_status, MPI_Fint *f_status);
int (*IMPL_Status_f2f08)(const MPI_Fint *f_status, MPI_F08_status *f08_status);
#endif
int (*IMPL_Status_set_cancelled)(MPI_Status *status, int flag);
int (*IMPL_Status_set_elements)(MPI_Status *status, MPI_Datatype datatype, int count);
int (*IMPL_Status_set_elements_c)(MPI_Status *status, MPI_Datatype datatype, MPI_Count count);
int (*IMPL_Status_set_elements_x)(MPI_Status *status, MPI_Datatype datatype, MPI_Count count);
int (*IMPL_Test)(MPI_Request *request, int *flag, MPI_Status *status);
int (*IMPL_Test_cancelled)(const MPI_Status *status, int *flag);
int (*IMPL_Testall)(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[]);
int (*IMPL_Testany)(int count, MPI_Request array_of_requests[], int *indx, int *flag, MPI_Status *status);
int (*IMPL_Testsome)(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[]);
int (*IMPL_Topo_test)(MPI_Comm comm, int *status);
int (*IMPL_Type_commit)(MPI_Datatype *datatype);
int (*IMPL_Type_contiguous)(int count, MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_contiguous_c)(MPI_Count count, MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_create_darray)(int size, int rank, int ndims, const int array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_create_darray_c)(int size, int rank, int ndims, const MPI_Count array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_create_f90_complex)(int p, int r, MPI_Datatype *newtype);
int (*IMPL_Type_create_f90_integer)(int r, MPI_Datatype *newtype);
int (*IMPL_Type_create_f90_real)(int p, int r, MPI_Datatype *newtype);
int (*IMPL_Type_create_hindexed)(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_create_hindexed_block)(int count, int blocklength, const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_create_hindexed_block_c)(MPI_Count count, MPI_Count blocklength, const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_create_hindexed_c)(MPI_Count count, const MPI_Count array_of_blocklengths[], const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_create_hvector)(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_create_hvector_c)(MPI_Count count, MPI_Count blocklength, MPI_Count stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_create_indexed_block)(int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_create_indexed_block_c)(MPI_Count count, MPI_Count blocklength, const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_create_keyval)(MPI_Type_copy_attr_function *type_copy_attr_fn, MPI_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state);
int (*IMPL_Type_create_resized)(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype);
int (*IMPL_Type_create_resized_c)(MPI_Datatype oldtype, MPI_Count lb, MPI_Count extent, MPI_Datatype *newtype);
int (*IMPL_Type_create_struct)(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype);
int (*IMPL_Type_create_struct_c)(MPI_Count count, const MPI_Count array_of_blocklengths[], const MPI_Count array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype);
int (*IMPL_Type_create_subarray)(int ndims, const int array_of_sizes[], const int array_of_subsizes[], const int array_of_starts[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_create_subarray_c)(int ndims, const MPI_Count array_of_sizes[], const MPI_Count array_of_subsizes[], const MPI_Count array_of_starts[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_delete_attr)(MPI_Datatype datatype, int type_keyval);
int (*IMPL_Type_dup)(MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_extent)(MPI_Datatype datatype, MPI_Aint *extent);
int (*IMPL_Type_free)(MPI_Datatype *datatype);
int (*IMPL_Type_free_keyval)(int *type_keyval);
int (*IMPL_Type_get_attr)(MPI_Datatype datatype, int type_keyval, void *attribute_val, int *flag);
int (*IMPL_Type_get_contents)(MPI_Datatype datatype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[]);
int (*IMPL_Type_get_contents_c)(MPI_Datatype datatype, MPI_Count max_integers, MPI_Count max_addresses, MPI_Count max_large_counts, MPI_Count max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Count array_of_large_counts[], MPI_Datatype array_of_datatypes[]);
int (*IMPL_Type_get_envelope)(MPI_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner);
int (*IMPL_Type_get_envelope_c)(MPI_Datatype datatype, MPI_Count *num_integers, MPI_Count *num_addresses, MPI_Count *num_large_counts, MPI_Count *num_datatypes, int *combiner);
int (*IMPL_Type_get_extent)(MPI_Datatype datatype, MPI_Aint *lb, MPI_Aint *extent);
int (*IMPL_Type_get_extent_c)(MPI_Datatype datatype, MPI_Count *lb, MPI_Count *extent);
int (*IMPL_Type_get_extent_x)(MPI_Datatype datatype, MPI_Count *lb, MPI_Count *extent);
int (*IMPL_Type_get_name)(MPI_Datatype datatype, char *type_name, int *resultlen);
int (*IMPL_Type_get_true_extent)(MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent);
int (*IMPL_Type_get_true_extent_c)(MPI_Datatype datatype, MPI_Count *true_lb, MPI_Count *true_extent);
int (*IMPL_Type_get_true_extent_x)(MPI_Datatype datatype, MPI_Count *true_lb, MPI_Count *true_extent);
int (*IMPL_Type_hindexed)(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_hvector)(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_indexed)(int count, const int array_of_blocklengths[], const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_indexed_c)(MPI_Count count, const MPI_Count array_of_blocklengths[], const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_lb)(MPI_Datatype datatype, MPI_Aint *displacement);
int (*IMPL_Type_match_size)(int typeclass, int size, MPI_Datatype *datatype);
int (*IMPL_Type_set_attr)(MPI_Datatype datatype, int type_keyval, void *attribute_val);
int (*IMPL_Type_set_name)(MPI_Datatype datatype, const char *type_name);
int (*IMPL_Type_size)(MPI_Datatype datatype, int *size);
int (*IMPL_Type_size_c)(MPI_Datatype datatype, MPI_Count *size);
int (*IMPL_Type_size_x)(MPI_Datatype datatype, MPI_Count *size);
int (*IMPL_Type_struct)(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype array_of_types[], MPI_Datatype *newtype);
int (*IMPL_Type_ub)(MPI_Datatype datatype, MPI_Aint *displacement);
int (*IMPL_Type_vector)(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Type_vector_c)(MPI_Count count, MPI_Count blocklength, MPI_Count stride, MPI_Datatype oldtype, MPI_Datatype *newtype);
int (*IMPL_Unpack)(const void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm);
int (*IMPL_Unpack_c)(const void *inbuf, MPI_Count insize, MPI_Count *position, void *outbuf, MPI_Count outcount, MPI_Datatype datatype, MPI_Comm comm);
int (*IMPL_Unpack_external)(const char datarep[], const void *inbuf, MPI_Aint insize, MPI_Aint *position, void *outbuf, int outcount, MPI_Datatype datatype);
int (*IMPL_Unpack_external_c)(const char datarep[], const void *inbuf, MPI_Count insize, MPI_Count *position, void *outbuf, MPI_Count outcount, MPI_Datatype datatype);
int (*IMPL_Unpublish_name)(const char *service_name, MPI_Info info, const char *port_name);
int (*IMPL_Wait)(MPI_Request *request, MPI_Status *status);
int (*IMPL_Waitall)(int count, MPI_Request array_of_requests[], MPI_Status array_of_statuses[]);
int (*IMPL_Waitany)(int count, MPI_Request array_of_requests[], int *indx, MPI_Status *status);
int (*IMPL_Waitsome)(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[]);
int (*IMPL_Win_allocate)(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win);
int (*IMPL_Win_allocate_c)(MPI_Aint size, MPI_Aint disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win);
int (*IMPL_Win_allocate_shared)(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win);
int (*IMPL_Win_allocate_shared_c)(MPI_Aint size, MPI_Aint disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win);
int (*IMPL_Win_attach)(MPI_Win win, void *base, MPI_Aint size);
int (*IMPL_Win_call_errhandler)(MPI_Win win, int errorcode);
int (*IMPL_Win_complete)(MPI_Win win);
int (*IMPL_Win_create)(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win);
int (*IMPL_Win_create_c)(void *base, MPI_Aint size, MPI_Aint disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win);
int (*IMPL_Win_create_dynamic)(MPI_Info info, MPI_Comm comm, MPI_Win *win);
int (*IMPL_Win_create_errhandler)(MPI_Win_errhandler_function *win_errhandler_fn, MPI_Errhandler *errhandler);
int (*IMPL_Win_create_keyval)(MPI_Win_copy_attr_function *win_copy_attr_fn, MPI_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state);
int (*IMPL_Win_delete_attr)(MPI_Win win, int win_keyval);
int (*IMPL_Win_detach)(MPI_Win win, const void *base);
int (*IMPL_Win_fence)(int assert, MPI_Win win);
int (*IMPL_Win_flush)(int rank, MPI_Win win);
int (*IMPL_Win_flush_all)(MPI_Win win);
int (*IMPL_Win_flush_local)(int rank, MPI_Win win);
int (*IMPL_Win_flush_local_all)(MPI_Win win);
int (*IMPL_Win_free)(MPI_Win *win);
int (*IMPL_Win_free_keyval)(int *win_keyval);
int (*IMPL_Win_get_attr)(MPI_Win win, int win_keyval, void *attribute_val, int *flag);
int (*IMPL_Win_get_errhandler)(MPI_Win win, MPI_Errhandler *errhandler);
int (*IMPL_Win_get_group)(MPI_Win win, MPI_Group *group);
int (*IMPL_Win_get_info)(MPI_Win win, MPI_Info *info_used);
int (*IMPL_Win_get_name)(MPI_Win win, char *win_name, int *resultlen);
int (*IMPL_Win_lock)(int lock_type, int rank, int assert, MPI_Win win);
int (*IMPL_Win_lock_all)(int assert, MPI_Win win);
int (*IMPL_Win_post)(MPI_Group group, int assert, MPI_Win win);
int (*IMPL_Win_set_attr)(MPI_Win win, int win_keyval, void *attribute_val);
int (*IMPL_Win_set_errhandler)(MPI_Win win, MPI_Errhandler errhandler);
int (*IMPL_Win_set_info)(MPI_Win win, MPI_Info info);
int (*IMPL_Win_set_name)(MPI_Win win, const char *win_name);
int (*IMPL_Win_shared_query)(MPI_Win win, int rank, MPI_Aint *size, int *disp_unit, void *baseptr);
int (*IMPL_Win_shared_query_c)(MPI_Win win, int rank, MPI_Aint *size, MPI_Aint *disp_unit, void *baseptr);
int (*IMPL_Win_start)(MPI_Group group, int assert, MPI_Win win);
int (*IMPL_Win_sync)(MPI_Win win);
int (*IMPL_Win_test)(MPI_Win win, int *flag);
int (*IMPL_Win_unlock)(int rank, MPI_Win win);
int (*IMPL_Win_unlock_all)(MPI_Win win);
int (*IMPL_Win_wait)(MPI_Win win);

//
// MPI_ allows profiling of the implementation, in theory,
// assuming we figure out whatever the DLL situation is there.
//
// For development, use MPI_, because that will catch problems
// where the MUK MPI symbols are confused for IMPL MPI symbols,
// which leads to infinite recursion or segfaults.
//
// Use PMPI_ in production to keep things simple.
//
#define STRINGIFY(text) #text
#ifdef USE_IMPL_PMPI_SYMBOLS
#define NIMI(text) "PMPI_" STRINGIFY(text)
#else
#define NIMI(text) "MPI_" STRINGIFY(text)
#endif

int WRAP_Load_functions(void * restrict h, int major, int minor)
{
    (void)major;
    (void)minor;
    IMPL_Finalized = MUK_DLSYM(h, NIMI(Finalized));
    IMPL_Abort = MUK_DLSYM(h, NIMI(Abort));
    IMPL_Accumulate = MUK_DLSYM(h, NIMI(Accumulate));
    IMPL_Accumulate_c = MUK_DLSYM(h, NIMI(Accumulate_c));
    IMPL_Add_error_class = MUK_DLSYM(h, NIMI(Add_error_class));
    IMPL_Add_error_code = MUK_DLSYM(h, NIMI(Add_error_code));
    IMPL_Add_error_string = MUK_DLSYM(h, NIMI(Add_error_string));
    IMPL_Address = MUK_DLSYM(h, NIMI(Address));
    IMPL_Aint_add = MUK_DLSYM(h, NIMI(Aint_add));
    IMPL_Aint_diff = MUK_DLSYM(h, NIMI(Aint_diff));
    IMPL_Allgather = MUK_DLSYM(h, NIMI(Allgather));
    IMPL_Allgather_c = MUK_DLSYM(h, NIMI(Allgather_c));
    IMPL_Allgather_init = MUK_DLSYM(h, NIMI(Allgather_init));
    IMPL_Allgather_init_c = MUK_DLSYM(h, NIMI(Allgather_init_c));
    IMPL_Allgatherv = MUK_DLSYM(h, NIMI(Allgatherv));
    IMPL_Allgatherv_c = MUK_DLSYM(h, NIMI(Allgatherv_c));
    IMPL_Allgatherv_init = MUK_DLSYM(h, NIMI(Allgatherv_init));
    IMPL_Allgatherv_init_c = MUK_DLSYM(h, NIMI(Allgatherv_init_c));
    IMPL_Alloc_mem = MUK_DLSYM(h, NIMI(Alloc_mem));
    IMPL_Allreduce = MUK_DLSYM(h, NIMI(Allreduce));
    IMPL_Allreduce_c = MUK_DLSYM(h, NIMI(Allreduce_c));
    IMPL_Allreduce_init = MUK_DLSYM(h, NIMI(Allreduce_init));
    IMPL_Allreduce_init_c = MUK_DLSYM(h, NIMI(Allreduce_init_c));
    IMPL_Alltoall = MUK_DLSYM(h, NIMI(Alltoall));
    IMPL_Alltoall_c = MUK_DLSYM(h, NIMI(Alltoall_c));
    IMPL_Alltoall_init = MUK_DLSYM(h, NIMI(Alltoall_init));
    IMPL_Alltoall_init_c = MUK_DLSYM(h, NIMI(Alltoall_init_c));
    IMPL_Alltoallv = MUK_DLSYM(h, NIMI(Alltoallv));
    IMPL_Alltoallv_c = MUK_DLSYM(h, NIMI(Alltoallv_c));
    IMPL_Alltoallv_init = MUK_DLSYM(h, NIMI(Alltoallv_init));
    IMPL_Alltoallv_init_c = MUK_DLSYM(h, NIMI(Alltoallv_init_c));
    IMPL_Alltoallw = MUK_DLSYM(h, NIMI(Alltoallw));
    IMPL_Alltoallw_c = MUK_DLSYM(h, NIMI(Alltoallw_c));
    IMPL_Alltoallw_init = MUK_DLSYM(h, NIMI(Alltoallw_init));
    IMPL_Alltoallw_init_c = MUK_DLSYM(h, NIMI(Alltoallw_init_c));
    IMPL_Attr_delete = MUK_DLSYM(h, NIMI(Attr_delete));
    IMPL_Attr_get = MUK_DLSYM(h, NIMI(Attr_get));
    IMPL_Attr_put = MUK_DLSYM(h, NIMI(Attr_put));
    IMPL_Barrier = MUK_DLSYM(h, NIMI(Barrier));
    IMPL_Barrier_init = MUK_DLSYM(h, NIMI(Barrier_init));
    IMPL_Bcast = MUK_DLSYM(h, NIMI(Bcast));
    IMPL_Bcast_c = MUK_DLSYM(h, NIMI(Bcast_c));
    IMPL_Bcast_init = MUK_DLSYM(h, NIMI(Bcast_init));
    IMPL_Bcast_init_c = MUK_DLSYM(h, NIMI(Bcast_init_c));
    IMPL_Bsend = MUK_DLSYM(h, NIMI(Bsend));
    IMPL_Bsend_c = MUK_DLSYM(h, NIMI(Bsend_c));
    IMPL_Bsend_init = MUK_DLSYM(h, NIMI(Bsend_init));
    IMPL_Bsend_init_c = MUK_DLSYM(h, NIMI(Bsend_init_c));
    IMPL_Buffer_attach = MUK_DLSYM(h, NIMI(Buffer_attach));
    IMPL_Buffer_attach_c = MUK_DLSYM(h, NIMI(Buffer_attach_c));
    IMPL_Buffer_detach = MUK_DLSYM(h, NIMI(Buffer_detach));
    IMPL_Buffer_detach_c = MUK_DLSYM(h, NIMI(Buffer_detach_c));
    IMPL_Cancel = MUK_DLSYM(h, NIMI(Cancel));
    IMPL_Cart_coords = MUK_DLSYM(h, NIMI(Cart_coords));
    IMPL_Cart_create = MUK_DLSYM(h, NIMI(Cart_create));
    IMPL_Cart_get = MUK_DLSYM(h, NIMI(Cart_get));
    IMPL_Cart_map = MUK_DLSYM(h, NIMI(Cart_map));
    IMPL_Cart_rank = MUK_DLSYM(h, NIMI(Cart_rank));
    IMPL_Cart_shift = MUK_DLSYM(h, NIMI(Cart_shift));
    IMPL_Cart_sub = MUK_DLSYM(h, NIMI(Cart_sub));
    IMPL_Cartdim_get = MUK_DLSYM(h, NIMI(Cartdim_get));
    IMPL_Close_port = MUK_DLSYM(h, NIMI(Close_port));
    IMPL_Comm_accept = MUK_DLSYM(h, NIMI(Comm_accept));
    IMPL_Comm_call_errhandler = MUK_DLSYM(h, NIMI(Comm_call_errhandler));
    IMPL_Comm_compare = MUK_DLSYM(h, NIMI(Comm_compare));
    IMPL_Comm_connect = MUK_DLSYM(h, NIMI(Comm_connect));
    IMPL_Comm_create = MUK_DLSYM(h, NIMI(Comm_create));
    IMPL_Comm_create_errhandler = MUK_DLSYM(h, NIMI(Comm_create_errhandler));
    IMPL_Comm_create_from_group = MUK_DLSYM(h, NIMI(Comm_create_from_group));
    IMPL_Comm_create_group = MUK_DLSYM(h, NIMI(Comm_create_group));
    IMPL_Comm_create_keyval = MUK_DLSYM(h, NIMI(Comm_create_keyval));
    IMPL_Comm_delete_attr = MUK_DLSYM(h, NIMI(Comm_delete_attr));
    IMPL_Comm_disconnect = MUK_DLSYM(h, NIMI(Comm_disconnect));
    IMPL_Comm_dup = MUK_DLSYM(h, NIMI(Comm_dup));
    IMPL_Comm_dup_with_info = MUK_DLSYM(h, NIMI(Comm_dup_with_info));
    IMPL_Comm_free = MUK_DLSYM(h, NIMI(Comm_free));
    IMPL_Comm_free_keyval = MUK_DLSYM(h, NIMI(Comm_free_keyval));
    IMPL_Comm_get_attr = MUK_DLSYM(h, NIMI(Comm_get_attr));
    IMPL_Comm_get_errhandler = MUK_DLSYM(h, NIMI(Comm_get_errhandler));
    IMPL_Comm_get_info = MUK_DLSYM(h, NIMI(Comm_get_info));
    IMPL_Comm_get_name = MUK_DLSYM(h, NIMI(Comm_get_name));
    IMPL_Comm_get_parent = MUK_DLSYM(h, NIMI(Comm_get_parent));
    IMPL_Comm_group = MUK_DLSYM(h, NIMI(Comm_group));
    IMPL_Comm_idup = MUK_DLSYM(h, NIMI(Comm_idup));
    IMPL_Comm_idup_with_info = MUK_DLSYM(h, NIMI(Comm_idup_with_info));
    IMPL_Comm_join = MUK_DLSYM(h, NIMI(Comm_join));
    IMPL_Comm_rank = MUK_DLSYM(h, NIMI(Comm_rank));
    IMPL_Comm_remote_group = MUK_DLSYM(h, NIMI(Comm_remote_group));
    IMPL_Comm_remote_size = MUK_DLSYM(h, NIMI(Comm_remote_size));
    IMPL_Comm_set_attr = MUK_DLSYM(h, NIMI(Comm_set_attr));
    IMPL_Comm_set_errhandler = MUK_DLSYM(h, NIMI(Comm_set_errhandler));
    IMPL_Comm_set_info = MUK_DLSYM(h, NIMI(Comm_set_info));
    IMPL_Comm_set_name = MUK_DLSYM(h, NIMI(Comm_set_name));
    IMPL_Comm_size = MUK_DLSYM(h, NIMI(Comm_size));
    IMPL_Comm_split = MUK_DLSYM(h, NIMI(Comm_split));
    IMPL_Comm_split_type = MUK_DLSYM(h, NIMI(Comm_split_type));
    IMPL_Comm_test_inter = MUK_DLSYM(h, NIMI(Comm_test_inter));
    IMPL_Compare_and_swap = MUK_DLSYM(h, NIMI(Compare_and_swap));
    IMPL_Dims_create = MUK_DLSYM(h, NIMI(Dims_create));
    IMPL_Dist_graph_create = MUK_DLSYM(h, NIMI(Dist_graph_create));
    IMPL_Dist_graph_create_adjacent = MUK_DLSYM(h, NIMI(Dist_graph_create_adjacent));
    IMPL_Dist_graph_neighbors = MUK_DLSYM(h, NIMI(Dist_graph_neighbors));
    IMPL_Dist_graph_neighbors_count = MUK_DLSYM(h, NIMI(Dist_graph_neighbors_count));
    IMPL_Errhandler_create = MUK_DLSYM(h, NIMI(Errhandler_create));
    IMPL_Errhandler_free = MUK_DLSYM(h, NIMI(Errhandler_free));
    IMPL_Errhandler_get = MUK_DLSYM(h, NIMI(Errhandler_get));
    IMPL_Errhandler_set = MUK_DLSYM(h, NIMI(Errhandler_set));
    IMPL_Error_class = MUK_DLSYM(h, NIMI(Error_class));
    IMPL_Error_string = MUK_DLSYM(h, NIMI(Error_string));
    IMPL_Exscan = MUK_DLSYM(h, NIMI(Exscan));
    IMPL_Exscan_c = MUK_DLSYM(h, NIMI(Exscan_c));
    IMPL_Exscan_init = MUK_DLSYM(h, NIMI(Exscan_init));
    IMPL_Exscan_init_c = MUK_DLSYM(h, NIMI(Exscan_init_c));
    IMPL_Fetch_and_op = MUK_DLSYM(h, NIMI(Fetch_and_op));
    IMPL_File_call_errhandler = MUK_DLSYM(h, NIMI(File_call_errhandler));
    IMPL_File_close = MUK_DLSYM(h, NIMI(File_close));
    IMPL_File_create_errhandler = MUK_DLSYM(h, NIMI(File_create_errhandler));
    IMPL_File_delete = MUK_DLSYM(h, NIMI(File_delete));
    IMPL_File_get_amode = MUK_DLSYM(h, NIMI(File_get_amode));
    IMPL_File_get_atomicity = MUK_DLSYM(h, NIMI(File_get_atomicity));
    IMPL_File_get_byte_offset = MUK_DLSYM(h, NIMI(File_get_byte_offset));
    IMPL_File_get_errhandler = MUK_DLSYM(h, NIMI(File_get_errhandler));
    IMPL_File_get_group = MUK_DLSYM(h, NIMI(File_get_group));
    IMPL_File_get_info = MUK_DLSYM(h, NIMI(File_get_info));
    IMPL_File_get_position = MUK_DLSYM(h, NIMI(File_get_position));
    IMPL_File_get_position_shared = MUK_DLSYM(h, NIMI(File_get_position_shared));
    IMPL_File_get_size = MUK_DLSYM(h, NIMI(File_get_size));
    IMPL_File_get_type_extent = MUK_DLSYM(h, NIMI(File_get_type_extent));
    IMPL_File_get_type_extent_c = MUK_DLSYM(h, NIMI(File_get_type_extent_c));
    IMPL_File_get_view = MUK_DLSYM(h, NIMI(File_get_view));
    IMPL_File_iread = MUK_DLSYM(h, NIMI(File_iread));
    IMPL_File_iread_all = MUK_DLSYM(h, NIMI(File_iread_all));
    IMPL_File_iread_all_c = MUK_DLSYM(h, NIMI(File_iread_all_c));
    IMPL_File_iread_at = MUK_DLSYM(h, NIMI(File_iread_at));
    IMPL_File_iread_at_all = MUK_DLSYM(h, NIMI(File_iread_at_all));
    IMPL_File_iread_at_all_c = MUK_DLSYM(h, NIMI(File_iread_at_all_c));
    IMPL_File_iread_at_c = MUK_DLSYM(h, NIMI(File_iread_at_c));
    IMPL_File_iread_c = MUK_DLSYM(h, NIMI(File_iread_c));
    IMPL_File_iread_shared = MUK_DLSYM(h, NIMI(File_iread_shared));
    IMPL_File_iread_shared_c = MUK_DLSYM(h, NIMI(File_iread_shared_c));
    IMPL_File_iwrite = MUK_DLSYM(h, NIMI(File_iwrite));
    IMPL_File_iwrite_all = MUK_DLSYM(h, NIMI(File_iwrite_all));
    IMPL_File_iwrite_all_c = MUK_DLSYM(h, NIMI(File_iwrite_all_c));
    IMPL_File_iwrite_at = MUK_DLSYM(h, NIMI(File_iwrite_at));
    IMPL_File_iwrite_at_all = MUK_DLSYM(h, NIMI(File_iwrite_at_all));
    IMPL_File_iwrite_at_all_c = MUK_DLSYM(h, NIMI(File_iwrite_at_all_c));
    IMPL_File_iwrite_at_c = MUK_DLSYM(h, NIMI(File_iwrite_at_c));
    IMPL_File_iwrite_c = MUK_DLSYM(h, NIMI(File_iwrite_c));
    IMPL_File_iwrite_shared = MUK_DLSYM(h, NIMI(File_iwrite_shared));
    IMPL_File_iwrite_shared_c = MUK_DLSYM(h, NIMI(File_iwrite_shared_c));
    IMPL_File_open = MUK_DLSYM(h, NIMI(File_open));
    IMPL_File_preallocate = MUK_DLSYM(h, NIMI(File_preallocate));
    IMPL_File_read = MUK_DLSYM(h, NIMI(File_read));
    IMPL_File_read_all = MUK_DLSYM(h, NIMI(File_read_all));
    IMPL_File_read_all_begin = MUK_DLSYM(h, NIMI(File_read_all_begin));
    IMPL_File_read_all_begin_c = MUK_DLSYM(h, NIMI(File_read_all_begin_c));
    IMPL_File_read_all_c = MUK_DLSYM(h, NIMI(File_read_all_c));
    IMPL_File_read_all_end = MUK_DLSYM(h, NIMI(File_read_all_end));
    IMPL_File_read_at = MUK_DLSYM(h, NIMI(File_read_at));
    IMPL_File_read_at_all = MUK_DLSYM(h, NIMI(File_read_at_all));
    IMPL_File_read_at_all_begin = MUK_DLSYM(h, NIMI(File_read_at_all_begin));
    IMPL_File_read_at_all_begin_c = MUK_DLSYM(h, NIMI(File_read_at_all_begin_c));
    IMPL_File_read_at_all_c = MUK_DLSYM(h, NIMI(File_read_at_all_c));
    IMPL_File_read_at_all_end = MUK_DLSYM(h, NIMI(File_read_at_all_end));
    IMPL_File_read_at_c = MUK_DLSYM(h, NIMI(File_read_at_c));
    IMPL_File_read_c = MUK_DLSYM(h, NIMI(File_read_c));
    IMPL_File_read_ordered = MUK_DLSYM(h, NIMI(File_read_ordered));
    IMPL_File_read_ordered_begin = MUK_DLSYM(h, NIMI(File_read_ordered_begin));
    IMPL_File_read_ordered_begin_c = MUK_DLSYM(h, NIMI(File_read_ordered_begin_c));
    IMPL_File_read_ordered_c = MUK_DLSYM(h, NIMI(File_read_ordered_c));
    IMPL_File_read_ordered_end = MUK_DLSYM(h, NIMI(File_read_ordered_end));
    IMPL_File_read_shared = MUK_DLSYM(h, NIMI(File_read_shared));
    IMPL_File_read_shared_c = MUK_DLSYM(h, NIMI(File_read_shared_c));
    IMPL_File_seek = MUK_DLSYM(h, NIMI(File_seek));
    IMPL_File_seek_shared = MUK_DLSYM(h, NIMI(File_seek_shared));
    IMPL_File_set_atomicity = MUK_DLSYM(h, NIMI(File_set_atomicity));
    IMPL_File_set_errhandler = MUK_DLSYM(h, NIMI(File_set_errhandler));
    IMPL_File_set_info = MUK_DLSYM(h, NIMI(File_set_info));
    IMPL_File_set_size = MUK_DLSYM(h, NIMI(File_set_size));
    IMPL_File_set_view = MUK_DLSYM(h, NIMI(File_set_view));
    IMPL_File_sync = MUK_DLSYM(h, NIMI(File_sync));
    IMPL_File_write = MUK_DLSYM(h, NIMI(File_write));
    IMPL_File_write_all = MUK_DLSYM(h, NIMI(File_write_all));
    IMPL_File_write_all_begin = MUK_DLSYM(h, NIMI(File_write_all_begin));
    IMPL_File_write_all_begin_c = MUK_DLSYM(h, NIMI(File_write_all_begin_c));
    IMPL_File_write_all_c = MUK_DLSYM(h, NIMI(File_write_all_c));
    IMPL_File_write_all_end = MUK_DLSYM(h, NIMI(File_write_all_end));
    IMPL_File_write_at = MUK_DLSYM(h, NIMI(File_write_at));
    IMPL_File_write_at_all = MUK_DLSYM(h, NIMI(File_write_at_all));
    IMPL_File_write_at_all_begin = MUK_DLSYM(h, NIMI(File_write_at_all_begin));
    IMPL_File_write_at_all_begin_c = MUK_DLSYM(h, NIMI(File_write_at_all_begin_c));
    IMPL_File_write_at_all_c = MUK_DLSYM(h, NIMI(File_write_at_all_c));
    IMPL_File_write_at_all_end = MUK_DLSYM(h, NIMI(File_write_at_all_end));
    IMPL_File_write_at_c = MUK_DLSYM(h, NIMI(File_write_at_c));
    IMPL_File_write_c = MUK_DLSYM(h, NIMI(File_write_c));
    IMPL_File_write_ordered = MUK_DLSYM(h, NIMI(File_write_ordered));
    IMPL_File_write_ordered_begin = MUK_DLSYM(h, NIMI(File_write_ordered_begin));
    IMPL_File_write_ordered_begin_c = MUK_DLSYM(h, NIMI(File_write_ordered_begin_c));
    IMPL_File_write_ordered_c = MUK_DLSYM(h, NIMI(File_write_ordered_c));
    IMPL_File_write_ordered_end = MUK_DLSYM(h, NIMI(File_write_ordered_end));
    IMPL_File_write_shared = MUK_DLSYM(h, NIMI(File_write_shared));
    IMPL_File_write_shared_c = MUK_DLSYM(h, NIMI(File_write_shared_c));
    IMPL_Free_mem = MUK_DLSYM(h, NIMI(Free_mem));
    IMPL_Gather = MUK_DLSYM(h, NIMI(Gather));
    IMPL_Gather_c = MUK_DLSYM(h, NIMI(Gather_c));
    IMPL_Gather_init = MUK_DLSYM(h, NIMI(Gather_init));
    IMPL_Gather_init_c = MUK_DLSYM(h, NIMI(Gather_init_c));
    IMPL_Gatherv = MUK_DLSYM(h, NIMI(Gatherv));
    IMPL_Gatherv_c = MUK_DLSYM(h, NIMI(Gatherv_c));
    IMPL_Gatherv_init = MUK_DLSYM(h, NIMI(Gatherv_init));
    IMPL_Gatherv_init_c = MUK_DLSYM(h, NIMI(Gatherv_init_c));
    IMPL_Get = MUK_DLSYM(h, NIMI(Get));
    IMPL_Get_accumulate = MUK_DLSYM(h, NIMI(Get_accumulate));
    IMPL_Get_accumulate_c = MUK_DLSYM(h, NIMI(Get_accumulate_c));
    IMPL_Get_address = MUK_DLSYM(h, NIMI(Get_address));
    IMPL_Get_c = MUK_DLSYM(h, NIMI(Get_c));
    IMPL_Get_count = MUK_DLSYM(h, NIMI(Get_count));
    IMPL_Get_count_c = MUK_DLSYM(h, NIMI(Get_count_c));
    IMPL_Get_elements = MUK_DLSYM(h, NIMI(Get_elements));
    IMPL_Get_elements_c = MUK_DLSYM(h, NIMI(Get_elements_c));
    IMPL_Get_elements_x = MUK_DLSYM(h, NIMI(Get_elements_x));
    IMPL_Graph_create = MUK_DLSYM(h, NIMI(Graph_create));
    IMPL_Graph_get = MUK_DLSYM(h, NIMI(Graph_get));
    IMPL_Graph_map = MUK_DLSYM(h, NIMI(Graph_map));
    IMPL_Graph_neighbors = MUK_DLSYM(h, NIMI(Graph_neighbors));
    IMPL_Graph_neighbors_count = MUK_DLSYM(h, NIMI(Graph_neighbors_count));
    IMPL_Graphdims_get = MUK_DLSYM(h, NIMI(Graphdims_get));
    IMPL_Grequest_complete = MUK_DLSYM(h, NIMI(Grequest_complete));
    IMPL_Grequest_start = MUK_DLSYM(h, NIMI(Grequest_start));
    IMPL_Group_compare = MUK_DLSYM(h, NIMI(Group_compare));
    IMPL_Group_difference = MUK_DLSYM(h, NIMI(Group_difference));
    IMPL_Group_excl = MUK_DLSYM(h, NIMI(Group_excl));
    IMPL_Group_free = MUK_DLSYM(h, NIMI(Group_free));
#if MPI_VERSION >= 4
    IMPL_Group_from_session_pset = MUK_DLSYM(h, NIMI(Group_from_session_pset));
#endif
    IMPL_Group_incl = MUK_DLSYM(h, NIMI(Group_incl));
    IMPL_Group_intersection = MUK_DLSYM(h, NIMI(Group_intersection));
    IMPL_Group_range_excl = MUK_DLSYM(h, NIMI(Group_range_excl));
    IMPL_Group_range_incl = MUK_DLSYM(h, NIMI(Group_range_incl));
    IMPL_Group_rank = MUK_DLSYM(h, NIMI(Group_rank));
    IMPL_Group_size = MUK_DLSYM(h, NIMI(Group_size));
    IMPL_Group_translate_ranks = MUK_DLSYM(h, NIMI(Group_translate_ranks));
    IMPL_Group_union = MUK_DLSYM(h, NIMI(Group_union));
    IMPL_Iallgather = MUK_DLSYM(h, NIMI(Iallgather));
    IMPL_Iallgather_c = MUK_DLSYM(h, NIMI(Iallgather_c));
    IMPL_Iallgatherv = MUK_DLSYM(h, NIMI(Iallgatherv));
    IMPL_Iallgatherv_c = MUK_DLSYM(h, NIMI(Iallgatherv_c));
    IMPL_Iallreduce = MUK_DLSYM(h, NIMI(Iallreduce));
    IMPL_Iallreduce_c = MUK_DLSYM(h, NIMI(Iallreduce_c));
    IMPL_Ialltoall = MUK_DLSYM(h, NIMI(Ialltoall));
    IMPL_Ialltoall_c = MUK_DLSYM(h, NIMI(Ialltoall_c));
    IMPL_Ialltoallv = MUK_DLSYM(h, NIMI(Ialltoallv));
    IMPL_Ialltoallv_c = MUK_DLSYM(h, NIMI(Ialltoallv_c));
    IMPL_Ialltoallw = MUK_DLSYM(h, NIMI(Ialltoallw));
    IMPL_Ialltoallw_c = MUK_DLSYM(h, NIMI(Ialltoallw_c));
    IMPL_Ibarrier = MUK_DLSYM(h, NIMI(Ibarrier));
    IMPL_Ibcast = MUK_DLSYM(h, NIMI(Ibcast));
    IMPL_Ibcast_c = MUK_DLSYM(h, NIMI(Ibcast_c));
    IMPL_Ibsend = MUK_DLSYM(h, NIMI(Ibsend));
    IMPL_Ibsend_c = MUK_DLSYM(h, NIMI(Ibsend_c));
    IMPL_Iexscan = MUK_DLSYM(h, NIMI(Iexscan));
    IMPL_Iexscan_c = MUK_DLSYM(h, NIMI(Iexscan_c));
    IMPL_Igather = MUK_DLSYM(h, NIMI(Igather));
    IMPL_Igather_c = MUK_DLSYM(h, NIMI(Igather_c));
    IMPL_Igatherv = MUK_DLSYM(h, NIMI(Igatherv));
    IMPL_Igatherv_c = MUK_DLSYM(h, NIMI(Igatherv_c));
    IMPL_Improbe = MUK_DLSYM(h, NIMI(Improbe));
    IMPL_Imrecv = MUK_DLSYM(h, NIMI(Imrecv));
    IMPL_Imrecv_c = MUK_DLSYM(h, NIMI(Imrecv_c));
    IMPL_Ineighbor_allgather = MUK_DLSYM(h, NIMI(Ineighbor_allgather));
    IMPL_Ineighbor_allgather_c = MUK_DLSYM(h, NIMI(Ineighbor_allgather_c));
    IMPL_Ineighbor_allgatherv = MUK_DLSYM(h, NIMI(Ineighbor_allgatherv));
    IMPL_Ineighbor_allgatherv_c = MUK_DLSYM(h, NIMI(Ineighbor_allgatherv_c));
    IMPL_Ineighbor_alltoall = MUK_DLSYM(h, NIMI(Ineighbor_alltoall));
    IMPL_Ineighbor_alltoall_c = MUK_DLSYM(h, NIMI(Ineighbor_alltoall_c));
    IMPL_Ineighbor_alltoallv = MUK_DLSYM(h, NIMI(Ineighbor_alltoallv));
    IMPL_Ineighbor_alltoallv_c = MUK_DLSYM(h, NIMI(Ineighbor_alltoallv_c));
    IMPL_Ineighbor_alltoallw = MUK_DLSYM(h, NIMI(Ineighbor_alltoallw));
    IMPL_Ineighbor_alltoallw_c = MUK_DLSYM(h, NIMI(Ineighbor_alltoallw_c));
    IMPL_Info_create = MUK_DLSYM(h, NIMI(Info_create));
    IMPL_Info_create_env = MUK_DLSYM(h, NIMI(Info_create_env));
    IMPL_Info_delete = MUK_DLSYM(h, NIMI(Info_delete));
    IMPL_Info_dup = MUK_DLSYM(h, NIMI(Info_dup));
    IMPL_Info_free = MUK_DLSYM(h, NIMI(Info_free));
    IMPL_Info_get = MUK_DLSYM(h, NIMI(Info_get));
    IMPL_Info_get_nkeys = MUK_DLSYM(h, NIMI(Info_get_nkeys));
    IMPL_Info_get_nthkey = MUK_DLSYM(h, NIMI(Info_get_nthkey));
    IMPL_Info_get_string = MUK_DLSYM(h, NIMI(Info_get_string));
    IMPL_Info_get_valuelen = MUK_DLSYM(h, NIMI(Info_get_valuelen));
    IMPL_Info_set = MUK_DLSYM(h, NIMI(Info_set));
    IMPL_Intercomm_create = MUK_DLSYM(h, NIMI(Intercomm_create));
    IMPL_Intercomm_create_from_groups = MUK_DLSYM(h, NIMI(Intercomm_create_from_groups));
    IMPL_Intercomm_merge = MUK_DLSYM(h, NIMI(Intercomm_merge));
    IMPL_Iprobe = MUK_DLSYM(h, NIMI(Iprobe));
    IMPL_Irecv = MUK_DLSYM(h, NIMI(Irecv));
    IMPL_Irecv_c = MUK_DLSYM(h, NIMI(Irecv_c));
    IMPL_Ireduce = MUK_DLSYM(h, NIMI(Ireduce));
    IMPL_Ireduce_c = MUK_DLSYM(h, NIMI(Ireduce_c));
    IMPL_Ireduce_scatter = MUK_DLSYM(h, NIMI(Ireduce_scatter));
    IMPL_Ireduce_scatter_block = MUK_DLSYM(h, NIMI(Ireduce_scatter_block));
    IMPL_Ireduce_scatter_block_c = MUK_DLSYM(h, NIMI(Ireduce_scatter_block_c));
    IMPL_Ireduce_scatter_c = MUK_DLSYM(h, NIMI(Ireduce_scatter_c));
    IMPL_Irsend = MUK_DLSYM(h, NIMI(Irsend));
    IMPL_Irsend_c = MUK_DLSYM(h, NIMI(Irsend_c));
    IMPL_Iscan = MUK_DLSYM(h, NIMI(Iscan));
    IMPL_Iscan_c = MUK_DLSYM(h, NIMI(Iscan_c));
    IMPL_Iscatter = MUK_DLSYM(h, NIMI(Iscatter));
    IMPL_Iscatter_c = MUK_DLSYM(h, NIMI(Iscatter_c));
    IMPL_Iscatterv = MUK_DLSYM(h, NIMI(Iscatterv));
    IMPL_Iscatterv_c = MUK_DLSYM(h, NIMI(Iscatterv_c));
    IMPL_Isend = MUK_DLSYM(h, NIMI(Isend));
    IMPL_Isend_c = MUK_DLSYM(h, NIMI(Isend_c));
    IMPL_Isendrecv = MUK_DLSYM(h, NIMI(Isendrecv));
    IMPL_Isendrecv_c = MUK_DLSYM(h, NIMI(Isendrecv_c));
    IMPL_Isendrecv_replace = MUK_DLSYM(h, NIMI(Isendrecv_replace));
    IMPL_Isendrecv_replace_c = MUK_DLSYM(h, NIMI(Isendrecv_replace_c));
    IMPL_Issend = MUK_DLSYM(h, NIMI(Issend));
    IMPL_Issend_c = MUK_DLSYM(h, NIMI(Issend_c));
    IMPL_Keyval_create = MUK_DLSYM(h, NIMI(Keyval_create));
    IMPL_Keyval_free = MUK_DLSYM(h, NIMI(Keyval_free));
    IMPL_Lookup_name = MUK_DLSYM(h, NIMI(Lookup_name));
    IMPL_Mprobe = MUK_DLSYM(h, NIMI(Mprobe));
    IMPL_Mrecv = MUK_DLSYM(h, NIMI(Mrecv));
    IMPL_Mrecv_c = MUK_DLSYM(h, NIMI(Mrecv_c));
    IMPL_Neighbor_allgather = MUK_DLSYM(h, NIMI(Neighbor_allgather));
    IMPL_Neighbor_allgather_c = MUK_DLSYM(h, NIMI(Neighbor_allgather_c));
    IMPL_Neighbor_allgather_init = MUK_DLSYM(h, NIMI(Neighbor_allgather_init));
    IMPL_Neighbor_allgather_init_c = MUK_DLSYM(h, NIMI(Neighbor_allgather_init_c));
    IMPL_Neighbor_allgatherv = MUK_DLSYM(h, NIMI(Neighbor_allgatherv));
    IMPL_Neighbor_allgatherv_c = MUK_DLSYM(h, NIMI(Neighbor_allgatherv_c));
    IMPL_Neighbor_allgatherv_init = MUK_DLSYM(h, NIMI(Neighbor_allgatherv_init));
    IMPL_Neighbor_allgatherv_init_c = MUK_DLSYM(h, NIMI(Neighbor_allgatherv_init_c));
    IMPL_Neighbor_alltoall = MUK_DLSYM(h, NIMI(Neighbor_alltoall));
    IMPL_Neighbor_alltoall_c = MUK_DLSYM(h, NIMI(Neighbor_alltoall_c));
    IMPL_Neighbor_alltoall_init = MUK_DLSYM(h, NIMI(Neighbor_alltoall_init));
    IMPL_Neighbor_alltoall_init_c = MUK_DLSYM(h, NIMI(Neighbor_alltoall_init_c));
    IMPL_Neighbor_alltoallv = MUK_DLSYM(h, NIMI(Neighbor_alltoallv));
    IMPL_Neighbor_alltoallv_c = MUK_DLSYM(h, NIMI(Neighbor_alltoallv_c));
    IMPL_Neighbor_alltoallv_init = MUK_DLSYM(h, NIMI(Neighbor_alltoallv_init));
    IMPL_Neighbor_alltoallv_init_c = MUK_DLSYM(h, NIMI(Neighbor_alltoallv_init_c));
    IMPL_Neighbor_alltoallw = MUK_DLSYM(h, NIMI(Neighbor_alltoallw));
    IMPL_Neighbor_alltoallw_c = MUK_DLSYM(h, NIMI(Neighbor_alltoallw_c));
    IMPL_Neighbor_alltoallw_init = MUK_DLSYM(h, NIMI(Neighbor_alltoallw_init));
    IMPL_Neighbor_alltoallw_init_c = MUK_DLSYM(h, NIMI(Neighbor_alltoallw_init_c));
    IMPL_Op_commutative = MUK_DLSYM(h, NIMI(Op_commutative));
    IMPL_Op_create = MUK_DLSYM(h, NIMI(Op_create));
#if MPI_VERSION >= 4
    IMPL_Op_create_c = MUK_DLSYM(h, NIMI(Op_create_c));
#endif
    IMPL_Op_free = MUK_DLSYM(h, NIMI(Op_free));
    IMPL_Open_port = MUK_DLSYM(h, NIMI(Open_port));
    IMPL_Pack = MUK_DLSYM(h, NIMI(Pack));
    IMPL_Pack_c = MUK_DLSYM(h, NIMI(Pack_c));
    IMPL_Pack_external = MUK_DLSYM(h, NIMI(Pack_external));
    IMPL_Pack_external_c = MUK_DLSYM(h, NIMI(Pack_external_c));
    IMPL_Pack_external_size = MUK_DLSYM(h, NIMI(Pack_external_size));
    IMPL_Pack_external_size_c = MUK_DLSYM(h, NIMI(Pack_external_size_c));
    IMPL_Pack_size = MUK_DLSYM(h, NIMI(Pack_size));
    IMPL_Pack_size_c = MUK_DLSYM(h, NIMI(Pack_size_c));
    IMPL_Parrived = MUK_DLSYM(h, NIMI(Parrived));
    IMPL_Pcontrol = MUK_DLSYM(h, NIMI(Pcontrol));
    IMPL_Pready = MUK_DLSYM(h, NIMI(Pready));
    IMPL_Pready_list = MUK_DLSYM(h, NIMI(Pready_list));
    IMPL_Pready_range = MUK_DLSYM(h, NIMI(Pready_range));
    IMPL_Precv_init = MUK_DLSYM(h, NIMI(Precv_init));
    IMPL_Probe = MUK_DLSYM(h, NIMI(Probe));
    IMPL_Psend_init = MUK_DLSYM(h, NIMI(Psend_init));
    IMPL_Publish_name = MUK_DLSYM(h, NIMI(Publish_name));
    IMPL_Put = MUK_DLSYM(h, NIMI(Put));
    IMPL_Put_c = MUK_DLSYM(h, NIMI(Put_c));
    IMPL_Raccumulate = MUK_DLSYM(h, NIMI(Raccumulate));
    IMPL_Raccumulate_c = MUK_DLSYM(h, NIMI(Raccumulate_c));
    IMPL_Recv = MUK_DLSYM(h, NIMI(Recv));
    IMPL_Recv_c = MUK_DLSYM(h, NIMI(Recv_c));
    IMPL_Recv_init = MUK_DLSYM(h, NIMI(Recv_init));
    IMPL_Recv_init_c = MUK_DLSYM(h, NIMI(Recv_init_c));
    IMPL_Reduce = MUK_DLSYM(h, NIMI(Reduce));
    IMPL_Reduce_c = MUK_DLSYM(h, NIMI(Reduce_c));
    IMPL_Reduce_init = MUK_DLSYM(h, NIMI(Reduce_init));
    IMPL_Reduce_init_c = MUK_DLSYM(h, NIMI(Reduce_init_c));
    IMPL_Reduce_local = MUK_DLSYM(h, NIMI(Reduce_local));
    IMPL_Reduce_local_c = MUK_DLSYM(h, NIMI(Reduce_local_c));
    IMPL_Reduce_scatter = MUK_DLSYM(h, NIMI(Reduce_scatter));
    IMPL_Reduce_scatter_block = MUK_DLSYM(h, NIMI(Reduce_scatter_block));
    IMPL_Reduce_scatter_block_c = MUK_DLSYM(h, NIMI(Reduce_scatter_block_c));
    IMPL_Reduce_scatter_block_init = MUK_DLSYM(h, NIMI(Reduce_scatter_block_init));
    IMPL_Reduce_scatter_block_init_c = MUK_DLSYM(h, NIMI(Reduce_scatter_block_init_c));
    IMPL_Reduce_scatter_c = MUK_DLSYM(h, NIMI(Reduce_scatter_c));
    IMPL_Reduce_scatter_init = MUK_DLSYM(h, NIMI(Reduce_scatter_init));
    IMPL_Reduce_scatter_init_c = MUK_DLSYM(h, NIMI(Reduce_scatter_init_c));
    IMPL_Register_datarep = MUK_DLSYM(h, NIMI(Register_datarep));
#if MPI_VERSION >= 4
    IMPL_Register_datarep_c = MUK_DLSYM(h, NIMI(Register_datarep_c));
#endif
    IMPL_Request_free = MUK_DLSYM(h, NIMI(Request_free));
    IMPL_Request_get_status = MUK_DLSYM(h, NIMI(Request_get_status));
    IMPL_Rget = MUK_DLSYM(h, NIMI(Rget));
    IMPL_Rget_accumulate = MUK_DLSYM(h, NIMI(Rget_accumulate));
    IMPL_Rget_accumulate_c = MUK_DLSYM(h, NIMI(Rget_accumulate_c));
    IMPL_Rget_c = MUK_DLSYM(h, NIMI(Rget_c));
    IMPL_Rput = MUK_DLSYM(h, NIMI(Rput));
    IMPL_Rput_c = MUK_DLSYM(h, NIMI(Rput_c));
    IMPL_Rsend = MUK_DLSYM(h, NIMI(Rsend));
    IMPL_Rsend_c = MUK_DLSYM(h, NIMI(Rsend_c));
    IMPL_Rsend_init = MUK_DLSYM(h, NIMI(Rsend_init));
    IMPL_Rsend_init_c = MUK_DLSYM(h, NIMI(Rsend_init_c));
    IMPL_Scan = MUK_DLSYM(h, NIMI(Scan));
    IMPL_Scan_c = MUK_DLSYM(h, NIMI(Scan_c));
    IMPL_Scan_init = MUK_DLSYM(h, NIMI(Scan_init));
    IMPL_Scan_init_c = MUK_DLSYM(h, NIMI(Scan_init_c));
    IMPL_Scatter = MUK_DLSYM(h, NIMI(Scatter));
    IMPL_Scatter_c = MUK_DLSYM(h, NIMI(Scatter_c));
    IMPL_Scatter_init = MUK_DLSYM(h, NIMI(Scatter_init));
    IMPL_Scatter_init_c = MUK_DLSYM(h, NIMI(Scatter_init_c));
    IMPL_Scatterv = MUK_DLSYM(h, NIMI(Scatterv));
    IMPL_Scatterv_c = MUK_DLSYM(h, NIMI(Scatterv_c));
    IMPL_Scatterv_init = MUK_DLSYM(h, NIMI(Scatterv_init));
    IMPL_Scatterv_init_c = MUK_DLSYM(h, NIMI(Scatterv_init_c));
    IMPL_Send = MUK_DLSYM(h, NIMI(Send));
    IMPL_Send_c = MUK_DLSYM(h, NIMI(Send_c));
    IMPL_Send_init = MUK_DLSYM(h, NIMI(Send_init));
    IMPL_Send_init_c = MUK_DLSYM(h, NIMI(Send_init_c));
    IMPL_Sendrecv = MUK_DLSYM(h, NIMI(Sendrecv));
    IMPL_Sendrecv_c = MUK_DLSYM(h, NIMI(Sendrecv_c));
    IMPL_Sendrecv_replace = MUK_DLSYM(h, NIMI(Sendrecv_replace));
    IMPL_Sendrecv_replace_c = MUK_DLSYM(h, NIMI(Sendrecv_replace_c));
#if MPI_VERSION >= 4
    IMPL_Session_call_errhandler = MUK_DLSYM(h, NIMI(Session_call_errhandler));
    IMPL_Session_create_errhandler = MUK_DLSYM(h, NIMI(Session_create_errhandler));
    IMPL_Session_finalize = MUK_DLSYM(h, NIMI(Session_finalize));
    IMPL_Session_get_errhandler = MUK_DLSYM(h, NIMI(Session_get_errhandler));
    IMPL_Session_get_info = MUK_DLSYM(h, NIMI(Session_get_info));
    IMPL_Session_get_nth_pset = MUK_DLSYM(h, NIMI(Session_get_nth_pset));
    IMPL_Session_get_num_psets = MUK_DLSYM(h, NIMI(Session_get_num_psets));
    IMPL_Session_get_pset_info = MUK_DLSYM(h, NIMI(Session_get_pset_info));
    IMPL_Session_init = MUK_DLSYM(h, NIMI(Session_init));
    IMPL_Session_set_errhandler = MUK_DLSYM(h, NIMI(Session_set_errhandler));
#endif
    IMPL_Ssend = MUK_DLSYM(h, NIMI(Ssend));
    IMPL_Ssend_c = MUK_DLSYM(h, NIMI(Ssend_c));
    IMPL_Ssend_init = MUK_DLSYM(h, NIMI(Ssend_init));
    IMPL_Ssend_init_c = MUK_DLSYM(h, NIMI(Ssend_init_c));
    IMPL_Start = MUK_DLSYM(h, NIMI(Start));
    IMPL_Startall = MUK_DLSYM(h, NIMI(Startall));
#ifdef SUPPORT_F08
    IMPL_Status_f082c = MUK_DLSYM(h, NIMI(Status_f082c));
    IMPL_Status_f082f = MUK_DLSYM(h, NIMI(Status_f082f));
    IMPL_Status_f2f08 = MUK_DLSYM(h, NIMI(Status_f2f08));
#endif
    IMPL_Status_set_cancelled = MUK_DLSYM(h, NIMI(Status_set_cancelled));
    IMPL_Status_set_elements = MUK_DLSYM(h, NIMI(Status_set_elements));
    IMPL_Status_set_elements_c = MUK_DLSYM(h, NIMI(Status_set_elements_c));
    IMPL_Status_set_elements_x = MUK_DLSYM(h, NIMI(Status_set_elements_x));
    IMPL_Test = MUK_DLSYM(h, NIMI(Test));
    IMPL_Test_cancelled = MUK_DLSYM(h, NIMI(Test_cancelled));
    IMPL_Testall = MUK_DLSYM(h, NIMI(Testall));
    IMPL_Testany = MUK_DLSYM(h, NIMI(Testany));
    IMPL_Testsome = MUK_DLSYM(h, NIMI(Testsome));
    IMPL_Topo_test = MUK_DLSYM(h, NIMI(Topo_test));
    IMPL_Type_commit = MUK_DLSYM(h, NIMI(Type_commit));
    IMPL_Type_contiguous = MUK_DLSYM(h, NIMI(Type_contiguous));
    IMPL_Type_contiguous_c = MUK_DLSYM(h, NIMI(Type_contiguous_c));
    IMPL_Type_create_darray = MUK_DLSYM(h, NIMI(Type_create_darray));
    IMPL_Type_create_darray_c = MUK_DLSYM(h, NIMI(Type_create_darray_c));
    IMPL_Type_create_f90_complex = MUK_DLSYM(h, NIMI(Type_create_f90_complex));
    IMPL_Type_create_f90_integer = MUK_DLSYM(h, NIMI(Type_create_f90_integer));
    IMPL_Type_create_f90_real = MUK_DLSYM(h, NIMI(Type_create_f90_real));
    IMPL_Type_create_hindexed = MUK_DLSYM(h, NIMI(Type_create_hindexed));
    IMPL_Type_create_hindexed_block = MUK_DLSYM(h, NIMI(Type_create_hindexed_block));
    IMPL_Type_create_hindexed_block_c = MUK_DLSYM(h, NIMI(Type_create_hindexed_block_c));
    IMPL_Type_create_hindexed_c = MUK_DLSYM(h, NIMI(Type_create_hindexed_c));
    IMPL_Type_create_hvector = MUK_DLSYM(h, NIMI(Type_create_hvector));
    IMPL_Type_create_hvector_c = MUK_DLSYM(h, NIMI(Type_create_hvector_c));
    IMPL_Type_create_indexed_block = MUK_DLSYM(h, NIMI(Type_create_indexed_block));
    IMPL_Type_create_indexed_block_c = MUK_DLSYM(h, NIMI(Type_create_indexed_block_c));
    IMPL_Type_create_keyval = MUK_DLSYM(h, NIMI(Type_create_keyval));
    IMPL_Type_create_resized = MUK_DLSYM(h, NIMI(Type_create_resized));
    IMPL_Type_create_resized_c = MUK_DLSYM(h, NIMI(Type_create_resized_c));
    IMPL_Type_create_struct = MUK_DLSYM(h, NIMI(Type_create_struct));
    IMPL_Type_create_struct_c = MUK_DLSYM(h, NIMI(Type_create_struct_c));
    IMPL_Type_create_subarray = MUK_DLSYM(h, NIMI(Type_create_subarray));
    IMPL_Type_create_subarray_c = MUK_DLSYM(h, NIMI(Type_create_subarray_c));
    IMPL_Type_delete_attr = MUK_DLSYM(h, NIMI(Type_delete_attr));
    IMPL_Type_dup = MUK_DLSYM(h, NIMI(Type_dup));
    IMPL_Type_extent = MUK_DLSYM(h, NIMI(Type_extent));
    IMPL_Type_free = MUK_DLSYM(h, NIMI(Type_free));
    IMPL_Type_free_keyval = MUK_DLSYM(h, NIMI(Type_free_keyval));
    IMPL_Type_get_attr = MUK_DLSYM(h, NIMI(Type_get_attr));
    IMPL_Type_get_contents = MUK_DLSYM(h, NIMI(Type_get_contents));
    IMPL_Type_get_contents_c = MUK_DLSYM(h, NIMI(Type_get_contents_c));
    IMPL_Type_get_envelope = MUK_DLSYM(h, NIMI(Type_get_envelope));
    IMPL_Type_get_envelope_c = MUK_DLSYM(h, NIMI(Type_get_envelope_c));
    IMPL_Type_get_extent = MUK_DLSYM(h, NIMI(Type_get_extent));
    IMPL_Type_get_extent_c = MUK_DLSYM(h, NIMI(Type_get_extent_c));
    IMPL_Type_get_extent_x = MUK_DLSYM(h, NIMI(Type_get_extent_x));
    IMPL_Type_get_name = MUK_DLSYM(h, NIMI(Type_get_name));
    IMPL_Type_get_true_extent = MUK_DLSYM(h, NIMI(Type_get_true_extent));
    IMPL_Type_get_true_extent_c = MUK_DLSYM(h, NIMI(Type_get_true_extent_c));
    IMPL_Type_get_true_extent_x = MUK_DLSYM(h, NIMI(Type_get_true_extent_x));
    IMPL_Type_hindexed = MUK_DLSYM(h, NIMI(Type_hindexed));
    IMPL_Type_hvector = MUK_DLSYM(h, NIMI(Type_hvector));
    IMPL_Type_indexed = MUK_DLSYM(h, NIMI(Type_indexed));
    IMPL_Type_indexed_c = MUK_DLSYM(h, NIMI(Type_indexed_c));
    IMPL_Type_lb = MUK_DLSYM(h, NIMI(Type_lb));
    IMPL_Type_match_size = MUK_DLSYM(h, NIMI(Type_match_size));
    IMPL_Type_set_attr = MUK_DLSYM(h, NIMI(Type_set_attr));
    IMPL_Type_set_name = MUK_DLSYM(h, NIMI(Type_set_name));
    IMPL_Type_size = MUK_DLSYM(h, NIMI(Type_size));
    IMPL_Type_size_c = MUK_DLSYM(h, NIMI(Type_size_c));
    IMPL_Type_size_x = MUK_DLSYM(h, NIMI(Type_size_x));
    IMPL_Type_struct = MUK_DLSYM(h, NIMI(Type_struct));
    IMPL_Type_ub = MUK_DLSYM(h, NIMI(Type_ub));
    IMPL_Type_vector = MUK_DLSYM(h, NIMI(Type_vector));
    IMPL_Type_vector_c = MUK_DLSYM(h, NIMI(Type_vector_c));
    IMPL_Unpack = MUK_DLSYM(h, NIMI(Unpack));
    IMPL_Unpack_c = MUK_DLSYM(h, NIMI(Unpack_c));
    IMPL_Unpack_external = MUK_DLSYM(h, NIMI(Unpack_external));
    IMPL_Unpack_external_c = MUK_DLSYM(h, NIMI(Unpack_external_c));
    IMPL_Unpublish_name = MUK_DLSYM(h, NIMI(Unpublish_name));
    IMPL_Wait = MUK_DLSYM(h, NIMI(Wait));
    IMPL_Waitall = MUK_DLSYM(h, NIMI(Waitall));
    IMPL_Waitany = MUK_DLSYM(h, NIMI(Waitany));
    IMPL_Waitsome = MUK_DLSYM(h, NIMI(Waitsome));
    IMPL_Win_allocate = MUK_DLSYM(h, NIMI(Win_allocate));
    IMPL_Win_allocate_c = MUK_DLSYM(h, NIMI(Win_allocate_c));
    IMPL_Win_allocate_shared = MUK_DLSYM(h, NIMI(Win_allocate_shared));
    IMPL_Win_allocate_shared_c = MUK_DLSYM(h, NIMI(Win_allocate_shared_c));
    IMPL_Win_attach = MUK_DLSYM(h, NIMI(Win_attach));
    IMPL_Win_call_errhandler = MUK_DLSYM(h, NIMI(Win_call_errhandler));
    IMPL_Win_complete = MUK_DLSYM(h, NIMI(Win_complete));
    IMPL_Win_create = MUK_DLSYM(h, NIMI(Win_create));
    IMPL_Win_create_c = MUK_DLSYM(h, NIMI(Win_create_c));
    IMPL_Win_create_dynamic = MUK_DLSYM(h, NIMI(Win_create_dynamic));
    IMPL_Win_create_errhandler = MUK_DLSYM(h, NIMI(Win_create_errhandler));
    IMPL_Win_create_keyval = MUK_DLSYM(h, NIMI(Win_create_keyval));
    IMPL_Win_delete_attr = MUK_DLSYM(h, NIMI(Win_delete_attr));
    IMPL_Win_detach = MUK_DLSYM(h, NIMI(Win_detach));
    IMPL_Win_fence = MUK_DLSYM(h, NIMI(Win_fence));
    IMPL_Win_flush = MUK_DLSYM(h, NIMI(Win_flush));
    IMPL_Win_flush_all = MUK_DLSYM(h, NIMI(Win_flush_all));
    IMPL_Win_flush_local = MUK_DLSYM(h, NIMI(Win_flush_local));
    IMPL_Win_flush_local_all = MUK_DLSYM(h, NIMI(Win_flush_local_all));
    IMPL_Win_free = MUK_DLSYM(h, NIMI(Win_free));
    IMPL_Win_free_keyval = MUK_DLSYM(h, NIMI(Win_free_keyval));
    IMPL_Win_get_attr = MUK_DLSYM(h, NIMI(Win_get_attr));
    IMPL_Win_get_errhandler = MUK_DLSYM(h, NIMI(Win_get_errhandler));
    IMPL_Win_get_group = MUK_DLSYM(h, NIMI(Win_get_group));
    IMPL_Win_get_info = MUK_DLSYM(h, NIMI(Win_get_info));
    IMPL_Win_get_name = MUK_DLSYM(h, NIMI(Win_get_name));
    IMPL_Win_lock = MUK_DLSYM(h, NIMI(Win_lock));
    IMPL_Win_lock_all = MUK_DLSYM(h, NIMI(Win_lock_all));
    IMPL_Win_post = MUK_DLSYM(h, NIMI(Win_post));
    IMPL_Win_set_attr = MUK_DLSYM(h, NIMI(Win_set_attr));
    IMPL_Win_set_errhandler = MUK_DLSYM(h, NIMI(Win_set_errhandler));
    IMPL_Win_set_info = MUK_DLSYM(h, NIMI(Win_set_info));
    IMPL_Win_set_name = MUK_DLSYM(h, NIMI(Win_set_name));
    IMPL_Win_shared_query = MUK_DLSYM(h, NIMI(Win_shared_query));
    IMPL_Win_shared_query_c = MUK_DLSYM(h, NIMI(Win_shared_query_c));
    IMPL_Win_start = MUK_DLSYM(h, NIMI(Win_start));
    IMPL_Win_sync = MUK_DLSYM(h, NIMI(Win_sync));
    IMPL_Win_test = MUK_DLSYM(h, NIMI(Win_test));
    IMPL_Win_unlock = MUK_DLSYM(h, NIMI(Win_unlock));
    IMPL_Win_unlock_all = MUK_DLSYM(h, NIMI(Win_unlock_all));
    IMPL_Win_wait = MUK_DLSYM(h, NIMI(Win_wait));
    return 0;
}

// constant conversions

// defined in impl-predefined.c
int ERROR_CODE_IMPL_TO_MUK(int);
int ERROR_CODE_MUK_TO_IMPL(int);
int COMBINER_CODE_IMPL_TO_MUK(int);

static inline int RANK_MUK_TO_IMPL(int rank_muk)
{
    if (rank_muk >= 0) {
        return rank_muk;
    }
    else if (rank_muk == MUK_PROC_NULL) {
        return MPI_PROC_NULL;
    }
    else if (rank_muk == MUK_ANY_SOURCE) {
        return MPI_ANY_SOURCE;
    }
    // this one only applies to intercomms
    else if (rank_muk == MUK_ROOT) {
        return MPI_ROOT;
    }
    else {
#if 1
        MUK_Warning("RANK_MUK_TO_IMPL rank=%d\n", rank_muk);
#endif
        return rank_muk;
    }
}

static inline int TAG_MUK_TO_IMPL(int tag_muk)
{
    if (tag_muk == MUK_ANY_TAG) {
        return MPI_ANY_TAG;
    } else {
        return tag_muk;
    }
}

// status conversion
static inline int UNDEFINED_IMPL_TO_MUK(int i)
{
    if (i == MPI_UNDEFINED) {
        return MUK_UNDEFINED;
    } else {
        return i;
    }
}

// status conversion
static inline int MODE_MUK_TO_IMPL(int mode_muk)
{
         if (mode_muk == MUK_MODE_APPEND)          { return MPI_MODE_APPEND; }
    else if (mode_muk == MUK_MODE_CREATE)          { return MPI_MODE_CREATE; }
    else if (mode_muk == MUK_MODE_DELETE_ON_CLOSE) { return MPI_MODE_DELETE_ON_CLOSE; }
    else if (mode_muk == MUK_MODE_EXCL)            { return MPI_MODE_EXCL; }
    else if (mode_muk == MUK_MODE_NOCHECK)         { return MPI_MODE_NOCHECK; }
    else if (mode_muk == MUK_MODE_NOPRECEDE)       { return MPI_MODE_NOPRECEDE; }
    else if (mode_muk == MUK_MODE_NOPUT)           { return MPI_MODE_NOPUT; }
    else if (mode_muk == MUK_MODE_NOSTORE)         { return MPI_MODE_NOSTORE; }
    else if (mode_muk == MUK_MODE_NOSUCCEED)       { return MPI_MODE_NOSUCCEED; }
    else if (mode_muk == MUK_MODE_RDONLY)          { return MPI_MODE_RDONLY; }
    else if (mode_muk == MUK_MODE_RDWR)            { return MPI_MODE_RDWR; }
    else if (mode_muk == MUK_MODE_SEQUENTIAL)      { return MPI_MODE_SEQUENTIAL; }
    else if (mode_muk == MUK_MODE_UNIQUE_OPEN)     { return MPI_MODE_UNIQUE_OPEN; }
    else if (mode_muk == MUK_MODE_WRONLY)          { return MPI_MODE_WRONLY; }
    else                                           { return mode_muk; }
}

// status conversion
static inline int KEY_MUK_TO_IMPL(int key_muk)
{
         if (key_muk == MUK_TAG_UB)            { return MPI_TAG_UB; }
    else if (key_muk == MUK_IO)                { return MPI_IO; }
    else if (key_muk == MUK_HOST)              { return MPI_HOST; }
    else if (key_muk == MUK_WTIME_IS_GLOBAL)   { return MPI_WTIME_IS_GLOBAL; }
    else if (key_muk == MUK_APPNUM)            { return MPI_APPNUM; }
    else if (key_muk == MUK_LASTUSEDCODE)      { return MPI_LASTUSEDCODE; }
    else if (key_muk == MUK_UNIVERSE_SIZE)     { return MPI_UNIVERSE_SIZE; }
    else if (key_muk == MUK_WIN_BASE)          { return MPI_WIN_BASE; }
    else if (key_muk == MUK_WIN_DISP_UNIT)     { return MPI_WIN_DISP_UNIT; }
    else if (key_muk == MUK_WIN_SIZE)          { return MPI_WIN_SIZE; }
    else if (key_muk == MUK_WIN_CREATE_FLAVOR) { return MPI_WIN_CREATE_FLAVOR; }
    else if (key_muk == MUK_WIN_MODEL)         { return MPI_WIN_MODEL; }
    else                                       { return key_muk; }
}

static int ALLTOALLW_SETUP(const MPI_Comm * comm, const MPI_Datatype* sendtypes[], const MPI_Datatype* recvtypes[],
                           MPI_Datatype* *impl_sendtypes, MPI_Datatype* *impl_recvtypes);

// status conversion

#include <stdlib.h>
#include <string.h>

static inline void WRAP_Status_to_MPI_Status(const WRAP_Status * w, MPI_Status * m)
{
    if ((intptr_t)w == (intptr_t)IMPL_STATUS_IGNORE) {
        //MUK_Warning("MPI_Status_to_WRAP_Status passed STATUS_IGNORE\n");
        return;
    }

    m->MPI_SOURCE = w->MPI_SOURCE;
    m->MPI_TAG    = w->MPI_TAG;
    m->MPI_ERROR  = w->MPI_ERROR;

#if defined(MPICH)
    memcpy(&(m->count_lo), w->__kielletty__, 2*sizeof(int));
#elif defined(OPEN_MPI)
    memcpy(&(m->_cancelled), w->__kielletty__, 3*sizeof(int));
#else
#error Need MPI_Status ABI support
#endif
}

static inline void MPI_Status_to_WRAP_Status(const MPI_Status * m, WRAP_Status * w)
{
    if ((intptr_t)w == (intptr_t)IMPL_STATUS_IGNORE) {
        //MUK_Warning("MPI_Status_to_WRAP_Status passed STATUS_IGNORE\n");
        return;
    }

    w->MPI_SOURCE = m->MPI_SOURCE;
    w->MPI_TAG    = m->MPI_TAG;
    w->MPI_ERROR  = m->MPI_ERROR;

#if defined(MPICH)
    memcpy(w->__kielletty__, &(m->count_lo), 2*sizeof(int));
#elif defined(OPEN_MPI)
    memcpy(w->__kielletty__, &(m->_cancelled), 3*sizeof(int));
#else
#error Need MPI_Status ABI support
#endif
}

// crazy stuff to support user-defined reductions

int TYPE_HANDLE_KEY = MPI_KEYVAL_INVALID;

void WRAP_Init_handle_key(void)
{
    int rc = IMPL_Type_create_keyval(MPI_TYPE_NULL_COPY_FN, MPI_TYPE_NULL_DELETE_FN, &TYPE_HANDLE_KEY, NULL);
    if (rc != MPI_SUCCESS) {
        MUK_Warning("IMPL_Type_create_keyval(TYPE_HANDLE_KEY) failed: %d\n", rc);
    }
}

void WRAP_Finalize_handle_key(void)
{
    int rc = MPI_SUCCESS;
    if (TYPE_HANDLE_KEY != MPI_KEYVAL_INVALID) {
        rc = IMPL_Type_free_keyval(&TYPE_HANDLE_KEY);
    }
    if (rc != MPI_SUCCESS) {
        MUK_Warning("IMPL_Type_free_keyval(TYPE_HANDLE_KEY) failed: %d\n", rc);
    }
}

static bool IS_PREDEFINED_OP(MPI_Op op)
{
    return (op == MPI_MAX || op == MPI_MIN || op == MPI_SUM || op == MPI_PROD ||
            op == MPI_LAND || op == MPI_LOR || op == MPI_LXOR ||
            op == MPI_BAND || op == MPI_BOR || op == MPI_BXOR ||
            op == MPI_MAXLOC || op == MPI_MINLOC ||
            op == MPI_REPLACE || op == MPI_NO_OP);
}

typedef void WRAP_User_function(void *invec, void *inoutvec, int *len, MPI_Datatype ** datatype);

typedef struct
{
    MPI_Datatype       * dt;
    WRAP_User_function * fp;
}
reduce_trampoline_cookie_t;

typedef struct op_fptr_pair_s
{
    // from MUK
    MPI_Op             * op;
    WRAP_User_function * fp;

    // for the linked list
    struct op_fptr_pair_s * next;
    struct op_fptr_pair_s * prev;
}
op_fptr_pair_t;

op_fptr_pair_t * op_fptr_pair_list = NULL;

static WRAP_User_function * lookup_op_pair(MPI_Op * op)
{
    WRAP_User_function * user_fn = NULL;
    op_fptr_pair_t * current = op_fptr_pair_list;
    if (op_fptr_pair_list == NULL) {
        MUK_Warning("op_fptr_pair_list is NULL - this should be impossible.\n");
    }
    while (current) {
        if (current->op == op) {
            user_fn = current->fp;
            break;
        }
        current = current->next;
    }
    return user_fn;
}

static void add_op_pair_to_list(WRAP_User_function *user_fn, MPI_Op *op)
{
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.
    op_fptr_pair_t * pair = malloc(sizeof(op_fptr_pair_t));
    pair->op = op;
    pair->fp = user_fn;
    pair->prev = NULL;
    pair->next = NULL;

    if (op_fptr_pair_list == NULL) {
        op_fptr_pair_list = pair;
    } else {
        op_fptr_pair_t * parent = op_fptr_pair_list;
        while (parent->next != NULL) {
            parent = parent->next;
        }
        parent->next = pair;
        pair->prev   = parent;
    }
}

static void remove_op_pair_from_list(MPI_Op *op)
{
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.

    // Step 1: look up op in the linked list
    op_fptr_pair_t * current = op_fptr_pair_list;
    if (op_fptr_pair_list == NULL) {
        MUK_Warning("remove_op_pair_from_list: op_fptr_pair_list is NULL - this should be impossible.\n");
    }
    while (current) {
        if (current->op == op) {
            break;
        }
        current = current->next;
    }

    // Step 2: remove current from the list
    if (current->prev == NULL) {
        MUK_Assert(current == op_fptr_pair_list);
        op_fptr_pair_list = current->next;
        if (current->next != NULL) {
            current->next->prev = NULL;
        }
    } else {
        current->prev->next = current->next;
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
    }

    // Step 3: free the memory
    free(current);
}

static reduce_trampoline_cookie_t * bake_reduce_trampoline_cookie(MPI_Op * op, MPI_Datatype * datatype, MPI_Datatype * dup)
{
    int rc;

    // Part 1: look up the user function associated with the MPI_Op argument
    WRAP_User_function * user_fn = lookup_op_pair(op);
    if (user_fn == NULL) {
        MUK_Warning("bake_reduce_trampoline_cookie: failed to find valid op<->fn mapping.\n");
        return NULL;
    }

    // Part 2: duplicate the datatype so there can be no collision of keyvals
    rc = IMPL_Type_dup(*datatype,dup);
    if (rc) {
        MUK_Warning("bake_reduce_trampoline_cookie: Type_dup failed\n");
        return NULL;
    }

    // Part 3: bake the cookie
    reduce_trampoline_cookie_t * cookie = malloc(sizeof(reduce_trampoline_cookie_t));
    cookie->dt = datatype;
    cookie->fp = user_fn;
    rc = IMPL_Type_set_attr(*dup, TYPE_HANDLE_KEY, cookie);
    if (rc) {
        MUK_Warning("bake_reduce_trampoline_cookie: Type_set_attr failed\n");
        IMPL_Type_free(dup);
        free(cookie);
        return NULL;
    }

    return cookie;
}

// This is to implement the crude garbage collector for cookies
// created by nonblocking reductions with user-defined ops,
// which cannot be freed until the user function is called
// (or else the lookup will segfault, obviously).
typedef struct req_cookie_pair_s
{
    MPI_Request                * request;
    reduce_trampoline_cookie_t * cookie;

    // for the linked list
    struct req_cookie_pair_s * next;
    struct req_cookie_pair_s * prev;
}
req_cookie_pair_t;

req_cookie_pair_t * req_cookie_pair_list = NULL;

// WRAP->IMPL functions

int WRAP_Abort(MPI_Comm *comm, int errorcode)
{
    int rc = IMPL_Abort(*comm, errorcode);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_rank(MPI_Comm *comm, int * rank)
{
    int rc = IMPL_Comm_rank(*comm, rank);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_size(MPI_Comm *comm, int * size)
{
    int rc = IMPL_Comm_size(*comm, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype *origin_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype *target_datatype, MPI_Op *op, MPI_Win *win)
{
    int rc = IMPL_Accumulate(origin_addr, origin_count, *origin_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *op, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Accumulate_c(const void *origin_addr, IMPL_Count origin_count, MPI_Datatype *origin_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype *target_datatype, MPI_Op *op, MPI_Win *win)
{
    int rc = IMPL_Accumulate_c(origin_addr, origin_count, *origin_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *op, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Add_error_class(int *errorclass)
{
    int rc = IMPL_Add_error_class(errorclass);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Add_error_code(int errorclass, int *errorcode)
{
    int rc = IMPL_Add_error_code(errorclass, errorcode);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Add_error_string(int errorcode, const char *string)
{
    int rc = IMPL_Add_error_string(errorcode, string);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Address(void *location, IMPL_Aint *address)
{
    int rc = IMPL_Address(location, address);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

MPI_Aint WRAP_Aint_add(IMPL_Aint base, IMPL_Aint disp)
{
    int rc = IMPL_Aint_add(base, disp);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

MPI_Aint WRAP_Aint_diff(IMPL_Aint addr1, IMPL_Aint addr2)
{
    int rc = IMPL_Aint_diff(addr1, addr2);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allgather(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Allgather(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allgather_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Allgather_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allgather_init(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Allgather_init(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allgather_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Allgather_init_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Allgatherv(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allgatherv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Allgatherv_c(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allgatherv_init(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Allgatherv_init(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allgatherv_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Allgatherv_init_c(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alloc_mem(IMPL_Aint size, MPI_Info *info, void *baseptr)
{
    int rc = IMPL_Alloc_mem(size, *info, baseptr);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm)
{
    int rc;
    if (IS_PREDEFINED_OP(*op)) {
        rc = IMPL_Allreduce(sendbuf, recvbuf, count, *datatype, *op, *comm);
    }
    else {
#if 1
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(op, datatype, &dup);
        if (cookie == NULL) {
            MUK_Warning("bake_reduce_trampoline_cookie failed.\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }
#else
        // Part 1: look up the user function associated with the MPI_Op argument
        WRAP_User_function * user_fn = lookup_op_pair(op);
        if (user_fn == NULL) {
            MUK_Warning("failed to find valid op<->fn mapping.\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }

        // Part 2: duplicate the datatype so there can be no collision of keyvals
        MPI_Datatype dup;
        rc = IMPL_Type_dup(*datatype,&dup);
        if (rc) {
            MUK_Warning("Type_dup failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }

        // Part 3: bake the cookie
        reduce_trampoline_cookie_t * cookie = malloc(sizeof(reduce_trampoline_cookie_t));
        cookie->dt = datatype;
        cookie->fp = user_fn;
        rc = IMPL_Type_set_attr(dup, TYPE_HANDLE_KEY, cookie);
        if (rc) {
            MUK_Warning("Type_set_attr failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }
#endif
        // do the reduction
        rc = IMPL_Allreduce(sendbuf, recvbuf, count, dup, *op, *comm);

        // clean up
        free(cookie);
        rc = IMPL_Type_free(&dup);
        if (rc) {
            MUK_Warning("Type_free failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }
    }
    end:
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allreduce_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm)
{
    int rc;
    if (IS_PREDEFINED_OP(*op)) {
        rc = IMPL_Allreduce_c(sendbuf, recvbuf, count, *datatype, *op, *comm);
    } else {
        MUK_Warning("WRAP_Allreduce_c does not implement user-defined ops.\n");
        rc = MPI_ERR_INTERN;
    }
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allreduce_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Allreduce_init(sendbuf, recvbuf, count, *datatype, *op, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allreduce_init_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Allreduce_init_c(sendbuf, recvbuf, count, *datatype, *op, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Alltoall(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alltoall_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Alltoall_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alltoall_init(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Alltoall_init(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alltoall_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Alltoall_init_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Alltoallv(sendbuf, sendcounts, sdispls, *sendtype, recvbuf, recvcounts, rdispls, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alltoallv_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Alltoallv_c(sendbuf, sendcounts, sdispls, *sendtype, recvbuf, recvcounts, rdispls, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Alltoallv_init(sendbuf, sendcounts, sdispls, *sendtype, recvbuf, recvcounts, rdispls, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alltoallv_init_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Alltoallv_init_c(sendbuf, sendcounts, sdispls, *sendtype, recvbuf, recvcounts, rdispls, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype* sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype* recvtypes[], MPI_Comm *comm)
{
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    rc = IMPL_Alltoallw(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, *comm);
    free(impl_recvtypes);
    free(impl_sendtypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alltoallw_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype* sendtypes[], void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype* recvtypes[], MPI_Comm *comm)
{
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    rc = IMPL_Alltoallw_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alltoallw_init(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype* sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype* recvtypes[], MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    *request = malloc(sizeof(MPI_Request));
    rc = IMPL_Alltoallw_init(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alltoallw_init_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype* sendtypes[], void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype* recvtypes[], MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    *request = malloc(sizeof(MPI_Request));
    rc = IMPL_Alltoallw_init_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Attr_delete(MPI_Comm *comm, int keyval)
{
    int rc = IMPL_Attr_delete(*comm, keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Attr_get(MPI_Comm *comm, int keyval, void *attribute_val, int *flag)
{
    int rc = IMPL_Attr_get(*comm, keyval, attribute_val, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Attr_put(MPI_Comm *comm, int keyval, void *attribute_val)
{
    int rc = IMPL_Attr_put(*comm, keyval, attribute_val);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Barrier(MPI_Comm *comm)
{
    int rc = IMPL_Barrier(*comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Barrier_init(MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Barrier_init(*comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Bcast(void *buffer, int count, MPI_Datatype *datatype, int root, MPI_Comm *comm)
{
    int rc = IMPL_Bcast(buffer, count, *datatype, RANK_MUK_TO_IMPL(root), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Bcast_c(void *buffer, IMPL_Count count, MPI_Datatype *datatype, int root, MPI_Comm *comm)
{
    int rc = IMPL_Bcast_c(buffer, count, *datatype, RANK_MUK_TO_IMPL(root), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Bcast_init(void *buffer, int count, MPI_Datatype *datatype, int root, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Bcast_init(buffer, count, *datatype, RANK_MUK_TO_IMPL(root), *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Bcast_init_c(void *buffer, IMPL_Count count, MPI_Datatype *datatype, int root, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Bcast_init_c(buffer, count, *datatype, RANK_MUK_TO_IMPL(root), *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Bsend(const void *buf, int count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm)
{
    int rc = IMPL_Bsend(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Bsend_c(const void *buf, IMPL_Count count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm)
{
    int rc = IMPL_Bsend_c(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Bsend_init(const void *buf, int count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Bsend_init(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Bsend_init_c(const void *buf, IMPL_Count count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Bsend_init_c(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Buffer_attach(void *buffer, int size)
{
    int rc = IMPL_Buffer_attach(buffer, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Buffer_attach_c(void *buffer, IMPL_Count size)
{
    int rc = IMPL_Buffer_attach_c(buffer, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Buffer_detach(void *buffer_addr, int *size)
{
    int rc = IMPL_Buffer_detach(buffer_addr, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Buffer_detach_c(void *buffer_addr, IMPL_Count *size)
{
    int rc = IMPL_Buffer_detach_c(buffer_addr, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cancel(MPI_Request **request)
{
    int rc = IMPL_Cancel(*request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_coords(MPI_Comm *comm, int rank, int maxdims, int coords[])
{
    int rc = IMPL_Cart_coords(*comm, rank, maxdims, coords);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_create(MPI_Comm comm_old, int ndims, const int dims[], const int periods[], int reorder, MPI_Comm **comm_cart)
{
    *comm_cart = malloc(sizeof(MPI_Comm));
    int rc = IMPL_Cart_create(comm_old, ndims, dims, periods, reorder, *comm_cart);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_get(MPI_Comm *comm, int maxdims, int dims[], int periods[], int coords[])
{
    int rc = IMPL_Cart_get(*comm, maxdims, dims, periods, coords);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_map(MPI_Comm *comm, int ndims, const int dims[], const int periods[], int *newrank)
{
    int rc = IMPL_Cart_map(*comm, ndims, dims, periods, newrank);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_rank(MPI_Comm *comm, const int coords[], int *rank)
{
    int rc = IMPL_Cart_rank(*comm, coords, rank);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_shift(MPI_Comm *comm, int direction, int disp, int *rank_source, int *rank_dest)
{
    int rc = IMPL_Cart_shift(*comm, direction, disp, rank_source, rank_dest);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_sub(MPI_Comm *comm, const int remain_dims[], MPI_Comm **newcomm)
{
    *newcomm = malloc(sizeof(MPI_Comm));
    int rc = IMPL_Cart_sub(*comm, remain_dims, *newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cartdim_get(MPI_Comm *comm, int *ndims)
{
    int rc = IMPL_Cartdim_get(*comm, ndims);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Close_port(const char *port_name)
{
    int rc = IMPL_Close_port(port_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_accept(const char *port_name, MPI_Info *info, int root, MPI_Comm *comm, MPI_Comm **newcomm)
{
    *newcomm = malloc(sizeof(MPI_Comm));
    int rc = IMPL_Comm_accept(port_name, *info, RANK_MUK_TO_IMPL(root), *comm, *newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_call_errhandler(MPI_Comm *comm, int errorcode)
{
    int rc = IMPL_Comm_call_errhandler(*comm, errorcode);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_compare(MPI_Comm *comm1, MPI_Comm *comm2, int *result)
{
    // no result conversion because MUK, MPICH and OMPI agree on this
    int rc = IMPL_Comm_compare(*comm1, *comm2, result);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_connect(const char *port_name, MPI_Info *info, int root, MPI_Comm *comm, MPI_Comm **newcomm)
{
    *newcomm = malloc(sizeof(MPI_Comm));
    int rc = IMPL_Comm_connect(port_name, *info, RANK_MUK_TO_IMPL(root), *comm, *newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_create(MPI_Comm *comm, MPI_Group *group, MPI_Comm **newcomm)
{
    *newcomm = malloc(sizeof(MPI_Comm));
    int rc = IMPL_Comm_create(*comm, *group, *newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_create_errhandler(MPI_Comm_errhandler_function *comm_errhandler_fn, MPI_Errhandler **errhandler)
{
    *errhandler = malloc(sizeof(MPI_Errhandler));
    int rc = IMPL_Comm_create_errhandler(comm_errhandler_fn, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_create_from_group(MPI_Group *group, const char *stringtag, MPI_Info *info, MPI_Errhandler *errhandler, MPI_Comm **newcomm)
{
    *newcomm = malloc(sizeof(MPI_Comm));
    int rc = IMPL_Comm_create_from_group(*group, stringtag, *info, *errhandler, *newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_create_group(MPI_Comm *comm, MPI_Group *group, int tag, MPI_Comm **newcomm)
{
    *newcomm = malloc(sizeof(MPI_Comm));
    int rc = IMPL_Comm_create_group(*comm, *group, tag, *newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state)
{
    int rc = IMPL_Comm_create_keyval(comm_copy_attr_fn, comm_delete_attr_fn, comm_keyval, extra_state);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_delete_attr(MPI_Comm *comm, int comm_keyval)
{
    int rc = IMPL_Comm_delete_attr(*comm, comm_keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_disconnect(MPI_Comm **comm)
{
    int rc = IMPL_Comm_disconnect(*comm);
    free(*comm);
    *comm = &IMPL_COMM_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_dup(MPI_Comm *comm, MPI_Comm **newcomm)
{
    *newcomm = malloc(sizeof(MPI_Comm));
    int rc = IMPL_Comm_dup(*comm, *newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_dup_with_info(MPI_Comm *comm, MPI_Info *info, MPI_Comm **newcomm)
{
    *newcomm = malloc(sizeof(MPI_Comm));
    int rc = IMPL_Comm_dup_with_info(*comm, *info, *newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_free(MPI_Comm **comm)
{
    int rc = IMPL_Comm_free(*comm);
    free(*comm);
    *comm = &IMPL_COMM_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_free_keyval(int *comm_keyval)
{
    int rc = IMPL_Comm_free_keyval(comm_keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_attr(MPI_Comm *comm, int comm_keyval, void *attribute_val, int *flag)
{
    int rc = IMPL_Comm_get_attr(*comm, KEY_MUK_TO_IMPL(comm_keyval), attribute_val, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_errhandler(MPI_Comm *comm, MPI_Errhandler **errhandler)
{
    *errhandler = malloc(sizeof(MPI_Errhandler));
    int rc = IMPL_Comm_get_errhandler(*comm, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_info(MPI_Comm *comm, MPI_Info *info_used)
{
    int rc = IMPL_Comm_get_info(*comm, info_used);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_name(MPI_Comm *comm, char *comm_name, int *resultlen)
{
    int rc = IMPL_Comm_get_name(*comm, comm_name, resultlen);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_parent(MPI_Comm *parent)
{
    int rc = IMPL_Comm_get_parent(parent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_group(MPI_Comm *comm, MPI_Group **group)
{
    *group = malloc(sizeof(MPI_Group));
    int rc = IMPL_Comm_group(*comm, *group);
#if DEBUG
    MUK_Warning("WRAP_Comm_group group=%p *group=%p **group=%lx MPI_GROUP_NULL=%lx\n",
                group,*group,(uintptr_t)**group,(uintptr_t)MPI_GROUP_NULL);
#endif
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_idup(MPI_Comm *comm, MPI_Comm **newcomm, MPI_Request **request)
{
    *newcomm = malloc(sizeof(MPI_Comm));
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Comm_idup(*comm, *newcomm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_idup_with_info(MPI_Comm *comm, MPI_Info *info, MPI_Comm **newcomm, MPI_Request **request)
{
    *newcomm = malloc(sizeof(MPI_Comm));
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Comm_idup_with_info(*comm, *info, *newcomm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_join(int fd, MPI_Comm *intercomm)
{
    int rc = IMPL_Comm_join(fd, intercomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_remote_group(MPI_Comm *comm, MPI_Group **group)
{
    *group = malloc(sizeof(MPI_Group));
    int rc = IMPL_Comm_remote_group(*comm, *group);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_remote_size(MPI_Comm *comm, int *size)
{
    int rc = IMPL_Comm_remote_size(*comm, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_set_attr(MPI_Comm *comm, int comm_keyval, void *attribute_val)
{
    int rc = IMPL_Comm_set_attr(*comm, comm_keyval, attribute_val);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_set_errhandler(MPI_Comm *comm, MPI_Errhandler *errhandler)
{
    int rc = IMPL_Comm_set_errhandler(*comm, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_set_info(MPI_Comm *comm, MPI_Info *info)
{
    int rc = IMPL_Comm_set_info(*comm, *info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_set_name(MPI_Comm *comm, const char *comm_name)
{
    int rc = IMPL_Comm_set_name(*comm, comm_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_split(MPI_Comm *comm, int color, int key, MPI_Comm **newcomm)
{
    *newcomm = malloc(sizeof(MPI_Comm));
    int rc = IMPL_Comm_split(*comm, color, key, *newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_split_type(MPI_Comm *comm, int split_type, int key, MPI_Info *info, MPI_Comm **newcomm)
{
    // this is the only place this conversion is required, so just inline it
    int impl_type = MPI_UNDEFINED;
    if (split_type == MUK_COMM_TYPE_SHARED) {
        impl_type = MPI_COMM_TYPE_SHARED;
    }
#if MPI_VERSION >= 4
    else if (split_type == MUK_COMM_TYPE_HW_UNGUIDED) {
        impl_type = MPI_COMM_TYPE_HW_UNGUIDED;
    }
    else if (split_type == MUK_COMM_TYPE_HW_GUIDED) {
        impl_type = MPI_COMM_TYPE_HW_GUIDED;
    }
#endif

    *newcomm = malloc(sizeof(MPI_Comm));
    int rc = IMPL_Comm_split_type(*comm, impl_type, key, *info, *newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_test_inter(MPI_Comm *comm, int *flag)
{
    int rc = IMPL_Comm_test_inter(*comm, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Compare_and_swap(const void *origin_addr, const void *compare_addr, void *result_addr, MPI_Datatype *datatype, int target_rank, IMPL_Aint target_disp, MPI_Win *win)
{
    int rc = IMPL_Compare_and_swap(origin_addr, compare_addr, result_addr, *datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dims_create(int nnodes, int ndims, int dims[])
{
    int rc = IMPL_Dims_create(nnodes, ndims, dims);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dist_graph_create(MPI_Comm comm_old, int n, const int sources[], const int degrees[], const int destinations[], const int weights[], MPI_Info *info, int reorder, MPI_Comm *comm_dist_graph)
{
    int rc = IMPL_Dist_graph_create(comm_old, n, sources, degrees, destinations, weights, *info, reorder, comm_dist_graph);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dist_graph_create_adjacent(MPI_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], MPI_Info *info, int reorder, MPI_Comm *comm_dist_graph)
{
    int rc = IMPL_Dist_graph_create_adjacent(comm_old, indegree, sources, sourceweights, outdegree, destinations, destweights, *info, reorder, comm_dist_graph);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dist_graph_neighbors(MPI_Comm *comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[])
{
    int rc = IMPL_Dist_graph_neighbors(*comm, maxindegree, sources, sourceweights, maxoutdegree, destinations, destweights);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dist_graph_neighbors_count(MPI_Comm *comm, int *indegree, int *outdegree, int *weighted)
{
    int rc = IMPL_Dist_graph_neighbors_count(*comm, indegree, outdegree, weighted);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Errhandler_create(MPI_Comm_errhandler_function *comm_errhandler_fn, MPI_Errhandler **errhandler)
{
    *errhandler = malloc(sizeof(MPI_Errhandler));
    int rc = IMPL_Errhandler_create(comm_errhandler_fn, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Errhandler_free(MPI_Errhandler **errhandler)
{
    int rc = IMPL_Errhandler_free(*errhandler);
    free(*errhandler);
    *errhandler = &IMPL_ERRHANDLER_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Errhandler_get(MPI_Comm *comm, MPI_Errhandler **errhandler)
{
    *errhandler = malloc(sizeof(MPI_Errhandler));
    int rc = IMPL_Errhandler_get(*comm, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Errhandler_set(MPI_Comm *comm, MPI_Errhandler *errhandler)
{
    int rc = IMPL_Errhandler_set(*comm, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Error_class(int errorcode, int *errorclass)
{
    int rc = IMPL_Error_class(errorcode, errorclass);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Error_string(int errorcode, char *string, int *resultlen)
{
    int rc = IMPL_Error_string(errorcode, string, resultlen);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Exscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm)
{
    int rc = IMPL_Exscan(sendbuf, recvbuf, count, *datatype, *op, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Exscan_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm)
{
    int rc = IMPL_Exscan_c(sendbuf, recvbuf, count, *datatype, *op, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Exscan_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Exscan_init(sendbuf, recvbuf, count, *datatype, *op, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Exscan_init_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Exscan_init_c(sendbuf, recvbuf, count, *datatype, *op, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Fetch_and_op(const void *origin_addr, void *result_addr, MPI_Datatype *datatype, int target_rank, IMPL_Aint target_disp, MPI_Op *op, MPI_Win *win)
{
    int rc = IMPL_Fetch_and_op(origin_addr, result_addr, *datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, *op, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_call_errhandler(MPI_File *fh, int errorcode)
{
    int rc = IMPL_File_call_errhandler(*fh, errorcode);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_close(MPI_File **fh)
{
    int rc = IMPL_File_close(*fh);
    free(*fh);
    *fh = &IMPL_FILE_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_create_errhandler(MPI_File_errhandler_function *file_errhandler_fn, MPI_Errhandler **errhandler)
{
    *errhandler = malloc(sizeof(MPI_Errhandler));
    int rc = IMPL_File_create_errhandler(file_errhandler_fn, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_delete(const char *filename, MPI_Info *info)
{
    int rc = IMPL_File_delete(filename, *info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_amode(MPI_File *fh, int *amode)
{
    int rc = IMPL_File_get_amode(*fh, amode);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_atomicity(MPI_File *fh, int *flag)
{
    int rc = IMPL_File_get_atomicity(*fh, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_byte_offset(MPI_File *fh, IMPL_Offset offset, IMPL_Offset *disp)
{
    int rc = IMPL_File_get_byte_offset(*fh, offset, disp);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_errhandler(MPI_File *file, MPI_Errhandler **errhandler)
{
    *errhandler = malloc(sizeof(MPI_Errhandler));
    int rc = IMPL_File_get_errhandler(*file, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_group(MPI_File *fh, MPI_Group **group)
{
    *group = malloc(sizeof(MPI_Group));
    int rc = IMPL_File_get_group(*fh, *group);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_info(MPI_File *fh, MPI_Info *info_used)
{
    int rc = IMPL_File_get_info(*fh, info_used);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_position(MPI_File *fh, IMPL_Offset *offset)
{
    int rc = IMPL_File_get_position(*fh, offset);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_position_shared(MPI_File *fh, IMPL_Offset *offset)
{
    int rc = IMPL_File_get_position_shared(*fh, offset);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_size(MPI_File *fh, IMPL_Offset *size)
{
    int rc = IMPL_File_get_size(*fh, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_type_extent(MPI_File *fh, MPI_Datatype *datatype, IMPL_Aint *extent)
{
    int rc = IMPL_File_get_type_extent(*fh, *datatype, extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_type_extent_c(MPI_File *fh, MPI_Datatype *datatype, IMPL_Count *extent)
{
    int rc = IMPL_File_get_type_extent_c(*fh, *datatype, extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_view(MPI_File *fh, IMPL_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep)
{
    int rc = IMPL_File_get_view(*fh, disp, etype, filetype, datarep);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread(MPI_File *fh, void *buf, int count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iread(*fh, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread_all(MPI_File *fh, void *buf, int count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iread_all(*fh, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread_all_c(MPI_File *fh, void *buf, IMPL_Count count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iread_all_c(*fh, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread_at(MPI_File *fh, IMPL_Offset offset, void *buf, int count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iread_at(*fh, offset, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread_at_all(MPI_File *fh, IMPL_Offset offset, void *buf, int count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iread_at_all(*fh, offset, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread_at_all_c(MPI_File *fh, IMPL_Offset offset, void *buf, IMPL_Count count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iread_at_all_c(*fh, offset, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread_at_c(MPI_File *fh, IMPL_Offset offset, void *buf, IMPL_Count count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iread_at_c(*fh, offset, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread_c(MPI_File *fh, void *buf, IMPL_Count count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iread_c(*fh, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread_shared(MPI_File *fh, void *buf, int count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iread_shared(*fh, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread_shared_c(MPI_File *fh, void *buf, IMPL_Count count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iread_shared_c(*fh, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iwrite(MPI_File *fh, const void *buf, int count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iwrite(*fh, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iwrite_all(MPI_File *fh, const void *buf, int count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iwrite_all(*fh, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iwrite_all_c(MPI_File *fh, const void *buf, IMPL_Count count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iwrite_all_c(*fh, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iwrite_at(MPI_File *fh, IMPL_Offset offset, const void *buf, int count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iwrite_at(*fh, offset, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iwrite_at_all(MPI_File *fh, IMPL_Offset offset, const void *buf, int count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iwrite_at_all(*fh, offset, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iwrite_at_all_c(MPI_File *fh, IMPL_Offset offset, const void *buf, IMPL_Count count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iwrite_at_all_c(*fh, offset, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iwrite_at_c(MPI_File *fh, IMPL_Offset offset, const void *buf, IMPL_Count count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iwrite_at_c(*fh, offset, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iwrite_c(MPI_File *fh, const void *buf, IMPL_Count count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iwrite_c(*fh, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iwrite_shared(MPI_File *fh, const void *buf, int count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iwrite_shared(*fh, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iwrite_shared_c(MPI_File *fh, const void *buf, IMPL_Count count, MPI_Datatype *datatype, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_File_iwrite_shared_c(*fh, buf, count, *datatype, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_open(MPI_Comm *comm, const char *filename, int amode, MPI_Info *info, MPI_File **fh)
{
    *fh = malloc(sizeof(MPI_File));
    int rc = IMPL_File_open(*comm, filename, amode, *info, *fh);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_preallocate(MPI_File *fh, IMPL_Offset size)
{
    int rc = IMPL_File_preallocate(*fh, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read(MPI_File *fh, void *buf, int count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_all(MPI_File *fh, void *buf, int count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_all(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_all_begin(MPI_File *fh, void *buf, int count, MPI_Datatype *datatype)
{
    int rc = IMPL_File_read_all_begin(*fh, buf, count, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_all_begin_c(MPI_File *fh, void *buf, IMPL_Count count, MPI_Datatype *datatype)
{
    int rc = IMPL_File_read_all_begin_c(*fh, buf, count, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_all_c(MPI_File *fh, void *buf, IMPL_Count count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_all_c(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_all_end(MPI_File *fh, void *buf, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_all_end(*fh, buf, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at(MPI_File *fh, IMPL_Offset offset, void *buf, int count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_at(*fh, offset, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at_all(MPI_File *fh, IMPL_Offset offset, void *buf, int count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_at_all(*fh, offset, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at_all_begin(MPI_File *fh, IMPL_Offset offset, void *buf, int count, MPI_Datatype *datatype)
{
    int rc = IMPL_File_read_at_all_begin(*fh, offset, buf, count, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at_all_begin_c(MPI_File *fh, IMPL_Offset offset, void *buf, IMPL_Count count, MPI_Datatype *datatype)
{
    int rc = IMPL_File_read_at_all_begin_c(*fh, offset, buf, count, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at_all_c(MPI_File *fh, IMPL_Offset offset, void *buf, IMPL_Count count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_at_all_c(*fh, offset, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at_all_end(MPI_File *fh, void *buf, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_at_all_end(*fh, buf, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at_c(MPI_File *fh, IMPL_Offset offset, void *buf, IMPL_Count count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_at_c(*fh, offset, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_c(MPI_File *fh, void *buf, IMPL_Count count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_c(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_ordered(MPI_File *fh, void *buf, int count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_ordered(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_ordered_begin(MPI_File *fh, void *buf, int count, MPI_Datatype *datatype)
{
    int rc = IMPL_File_read_ordered_begin(*fh, buf, count, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_ordered_begin_c(MPI_File *fh, void *buf, IMPL_Count count, MPI_Datatype *datatype)
{
    int rc = IMPL_File_read_ordered_begin_c(*fh, buf, count, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_ordered_c(MPI_File *fh, void *buf, IMPL_Count count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_ordered_c(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_ordered_end(MPI_File *fh, void *buf, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_ordered_end(*fh, buf, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_shared(MPI_File *fh, void *buf, int count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_shared(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_shared_c(MPI_File *fh, void *buf, IMPL_Count count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_shared_c(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_seek(MPI_File *fh, IMPL_Offset offset, int whence)
{
    int rc = IMPL_File_seek(*fh, offset, whence);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_seek_shared(MPI_File *fh, IMPL_Offset offset, int whence)
{
    int rc = IMPL_File_seek_shared(*fh, offset, whence);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_atomicity(MPI_File *fh, int flag)
{
    int rc = IMPL_File_set_atomicity(*fh, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_errhandler(MPI_File *file, MPI_Errhandler *errhandler)
{
    int rc = IMPL_File_set_errhandler(*file, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_info(MPI_File *fh, MPI_Info *info)
{
    int rc = IMPL_File_set_info(*fh, *info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_size(MPI_File *fh, IMPL_Offset size)
{
    int rc = IMPL_File_set_size(*fh, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_view(MPI_File *fh, IMPL_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char *datarep, MPI_Info *info)
{
    int rc = IMPL_File_set_view(*fh, disp, etype, filetype, datarep, *info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_sync(MPI_File *fh)
{
    int rc = IMPL_File_sync(*fh);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write(MPI_File *fh, const void *buf, int count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_all(MPI_File *fh, const void *buf, int count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_all(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_all_begin(MPI_File *fh, const void *buf, int count, MPI_Datatype *datatype)
{
    int rc = IMPL_File_write_all_begin(*fh, buf, count, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_all_begin_c(MPI_File *fh, const void *buf, IMPL_Count count, MPI_Datatype *datatype)
{
    int rc = IMPL_File_write_all_begin_c(*fh, buf, count, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_all_c(MPI_File *fh, const void *buf, IMPL_Count count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_all_c(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_all_end(MPI_File *fh, const void *buf, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_all_end(*fh, buf, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at(MPI_File *fh, IMPL_Offset offset, const void *buf, int count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_at(*fh, offset, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at_all(MPI_File *fh, IMPL_Offset offset, const void *buf, int count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_at_all(*fh, offset, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at_all_begin(MPI_File *fh, IMPL_Offset offset, const void *buf, int count, MPI_Datatype *datatype)
{
    int rc = IMPL_File_write_at_all_begin(*fh, offset, buf, count, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at_all_begin_c(MPI_File *fh, IMPL_Offset offset, const void *buf, IMPL_Count count, MPI_Datatype *datatype)
{
    int rc = IMPL_File_write_at_all_begin_c(*fh, offset, buf, count, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at_all_c(MPI_File *fh, IMPL_Offset offset, const void *buf, IMPL_Count count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_at_all_c(*fh, offset, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at_all_end(MPI_File *fh, const void *buf, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_at_all_end(*fh, buf, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at_c(MPI_File *fh, IMPL_Offset offset, const void *buf, IMPL_Count count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_at_c(*fh, offset, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_c(MPI_File *fh, const void *buf, IMPL_Count count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_c(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_ordered(MPI_File *fh, const void *buf, int count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_ordered(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_ordered_begin(MPI_File *fh, const void *buf, int count, MPI_Datatype *datatype)
{
    int rc = IMPL_File_write_ordered_begin(*fh, buf, count, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_ordered_begin_c(MPI_File *fh, const void *buf, IMPL_Count count, MPI_Datatype *datatype)
{
    int rc = IMPL_File_write_ordered_begin_c(*fh, buf, count, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_ordered_c(MPI_File *fh, const void *buf, IMPL_Count count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_ordered_c(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_ordered_end(MPI_File *fh, const void *buf, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_ordered_end(*fh, buf, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_shared(MPI_File *fh, const void *buf, int count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_shared(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_shared_c(MPI_File *fh, const void *buf, IMPL_Count count, MPI_Datatype *datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_shared_c(*fh, buf, count, *datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Free_mem(void *base)
{
    int rc = IMPL_Free_mem(base);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Gather(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm)
{
    int rc = IMPL_Gather(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Gather_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm)
{
    int rc = IMPL_Gather_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Gather_init(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Gather_init(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Gather_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Gather_init_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype *recvtype, int root, MPI_Comm *comm)
{
    int rc = IMPL_Gatherv(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, RANK_MUK_TO_IMPL(root), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Gatherv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype *recvtype, int root, MPI_Comm *comm)
{
    int rc = IMPL_Gatherv_c(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, RANK_MUK_TO_IMPL(root), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Gatherv_init(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Gatherv_init(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Gatherv_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Gatherv_init_c(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get(void *origin_addr, int origin_count, MPI_Datatype *origin_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype *target_datatype, MPI_Win *win)
{
    int rc = IMPL_Get(origin_addr, origin_count, *origin_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_accumulate(const void *origin_addr, int origin_count, MPI_Datatype *origin_datatype, void *result_addr, int result_count, MPI_Datatype *result_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype *target_datatype, MPI_Op *op, MPI_Win *win)
{
    int rc = IMPL_Get_accumulate(origin_addr, origin_count, *origin_datatype, result_addr, result_count, *result_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *op, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_accumulate_c(const void *origin_addr, IMPL_Count origin_count, MPI_Datatype *origin_datatype, void *result_addr, IMPL_Count result_count, MPI_Datatype *result_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype *target_datatype, MPI_Op *op, MPI_Win *win)
{
    int rc = IMPL_Get_accumulate_c(origin_addr, origin_count, *origin_datatype, result_addr, result_count, *result_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *op, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_address(const void *location, IMPL_Aint *address)
{
    int rc = IMPL_Get_address(location, address);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_c(void *origin_addr, IMPL_Count origin_count, MPI_Datatype *origin_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype *target_datatype, MPI_Win *win)
{
    int rc = IMPL_Get_c(origin_addr, origin_count, *origin_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_count(const WRAP_Status *status, MPI_Datatype *datatype, int *count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Get_count(&impl_status, *datatype, count);
    *count = UNDEFINED_IMPL_TO_MUK(*count);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_count_c(const WRAP_Status *status, MPI_Datatype *datatype, IMPL_Count *count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Get_count_c(&impl_status, *datatype, count);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_elements(const WRAP_Status *status, MPI_Datatype *datatype, int *count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Get_elements(&impl_status, *datatype, count);
    *count = UNDEFINED_IMPL_TO_MUK(*count);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_elements_c(const WRAP_Status *status, MPI_Datatype *datatype, IMPL_Count *count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Get_elements_c(&impl_status, *datatype, count);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_elements_x(const WRAP_Status *status, MPI_Datatype *datatype, IMPL_Count *count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Get_elements_x(&impl_status, *datatype, count);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_create(MPI_Comm comm_old, int nnodes, const int indx[], const int edges[], int reorder, MPI_Comm *comm_graph)
{
    int rc = IMPL_Graph_create(comm_old, nnodes, indx, edges, reorder, comm_graph);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_get(MPI_Comm *comm, int maxindex, int maxedges, int indx[], int edges[])
{
    int rc = IMPL_Graph_get(*comm, maxindex, maxedges, indx, edges);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_map(MPI_Comm *comm, int nnodes, const int indx[], const int edges[], int *newrank)
{
    int rc = IMPL_Graph_map(*comm, nnodes, indx, edges, newrank);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_neighbors(MPI_Comm *comm, int rank, int maxneighbors, int neighbors[])
{
    int rc = IMPL_Graph_neighbors(*comm, rank, maxneighbors, neighbors);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_neighbors_count(MPI_Comm *comm, int rank, int *nneighbors)
{
    int rc = IMPL_Graph_neighbors_count(*comm, rank, nneighbors);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graphdims_get(MPI_Comm *comm, int *nnodes, int *nedges)
{
    int rc = IMPL_Graphdims_get(*comm, nnodes, nedges);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Grequest_complete(MPI_Request *request)
{
    int rc = IMPL_Grequest_complete(*request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Grequest_start(MPI_Grequest_query_function *query_fn, MPI_Grequest_free_function *free_fn, MPI_Grequest_cancel_function *cancel_fn, void *extra_state, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Grequest_start(query_fn, free_fn, cancel_fn, extra_state, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_compare(MPI_Group *group1, MPI_Group *group2, int *result)
{
    int rc = IMPL_Group_compare(*group1, *group2, result);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_difference(MPI_Group *group1, MPI_Group *group2, MPI_Group **newgroup)
{
    *newgroup = malloc(sizeof(MPI_Group));
    int rc = IMPL_Group_difference(*group1, *group2, *newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_excl(MPI_Group *group, int n, const int ranks[], MPI_Group **newgroup)
{
    *newgroup = malloc(sizeof(MPI_Group));
    int rc = IMPL_Group_excl(*group, n, ranks, *newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_free(MPI_Group **group)
{
#ifdef DEBUG
    MUK_Warning("WRAP_Group_free group=%p *group=%p **group=%lx MPI_GROUP_EMPTY=%lx IMPL_GROUP_EMPTY=%lx\n",
                group,*group,(uintptr_t)**group,(uintptr_t)MPI_GROUP_EMPTY,(uintptr_t)IMPL_GROUP_EMPTY);
#endif
    int rc = IMPL_Group_free(*group);
    free(*group);
    *group = &IMPL_GROUP_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Group_from_session_pset(MPI_Session *session, const char *pset_name, MPI_Group **newgroup)
{
    *newgroup = malloc(sizeof(MPI_Group));
    int rc = IMPL_Group_from_session_pset(*session, pset_name, *newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Group_incl(MPI_Group *group, int n, const int ranks[], MPI_Group **newgroup)
{
    *newgroup = malloc(sizeof(MPI_Group));
    int rc = IMPL_Group_incl(*group, n, ranks, *newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_intersection(MPI_Group *group1, MPI_Group *group2, MPI_Group **newgroup)
{
    *newgroup = malloc(sizeof(MPI_Group));
    int rc = IMPL_Group_intersection(*group1, *group2, *newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_range_excl(MPI_Group *group, int n, int ranges[][3], MPI_Group **newgroup)
{
    *newgroup = malloc(sizeof(MPI_Group));
    int rc = IMPL_Group_range_excl(*group, n, ranges, *newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_range_incl(MPI_Group *group, int n, int ranges[][3], MPI_Group **newgroup)
{
    *newgroup = malloc(sizeof(MPI_Group));
    int rc = IMPL_Group_range_incl(*group, n, ranges, *newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_rank(MPI_Group *group, int *rank)
{
    int rc = IMPL_Group_rank(*group, rank);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_size(MPI_Group *group, int *size)
{
    int rc = IMPL_Group_size(*group, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_translate_ranks(MPI_Group *group1, int n, const int ranks1[], MPI_Group *group2, int ranks2[])
{
#ifdef DEBUG
    int me;
    IMPL_Comm_rank(MPI_COMM_WORLD,&me);

    int offset = 0;
    char * buf = calloc(1000000,1);
    offset += 1+sprintf(&buf[offset],"%d: ",me);
    offset += 1+sprintf(&buf[offset],"n=%d ", n);
    offset += 1+sprintf(&buf[offset],"ranks1[] = %p = ", ranks1);
    for (int i=0; i<n; i++) {
        offset += 1+sprintf(&buf[offset],"%d,", ranks1[i]);
    }
#endif
    int rc = IMPL_Group_translate_ranks(*group1, n, ranks1, *group2, ranks2);
#ifdef DEBUG
    offset += 1+sprintf(&buf[offset],"ranks2[] = %p = ", ranks2);
    for (int i=0; i<n; i++) {
        offset += 1+sprintf(&buf[offset],"%d,", ranks2[i]);
    }
    offset += 1+sprintf(&buf[offset],"\n");
    for (int i=0; i<offset; i++) printf("%c",buf[i]);
    fflush(0);
    free(buf);
#endif
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_union(MPI_Group *group1, MPI_Group *group2, MPI_Group **newgroup)
{
    *newgroup = malloc(sizeof(MPI_Group));
    int rc = IMPL_Group_union(*group1, *group2, *newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iallgather(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Iallgather(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iallgather_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Iallgather_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iallgatherv(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Iallgatherv(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iallgatherv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Iallgatherv_c(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iallreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Iallreduce(sendbuf, recvbuf, count, *datatype, *op, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iallreduce_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Iallreduce_c(sendbuf, recvbuf, count, *datatype, *op, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ialltoall(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ialltoall(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ialltoall_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ialltoall_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ialltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ialltoallv(sendbuf, sendcounts, sdispls, *sendtype, recvbuf, recvcounts, rdispls, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ialltoallv_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ialltoallv_c(sendbuf, sendcounts, sdispls, *sendtype, recvbuf, recvcounts, rdispls, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ialltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype* sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype* recvtypes[], MPI_Comm *comm, MPI_Request **request)
{
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    *request = malloc(sizeof(MPI_Request));
    rc = IMPL_Ialltoallw(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ialltoallw_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype* sendtypes[], void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype* recvtypes[], MPI_Comm *comm, MPI_Request **request)
{
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    *request = malloc(sizeof(MPI_Request));
    rc = IMPL_Ialltoallw_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ibarrier(MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ibarrier(*comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ibcast(void *buffer, int count, MPI_Datatype *datatype, int root, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ibcast(buffer, count, *datatype, RANK_MUK_TO_IMPL(root), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ibcast_c(void *buffer, IMPL_Count count, MPI_Datatype *datatype, int root, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ibcast_c(buffer, count, *datatype, RANK_MUK_TO_IMPL(root), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ibsend(const void *buf, int count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ibsend(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ibsend_c(const void *buf, IMPL_Count count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ibsend_c(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iexscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Iexscan(sendbuf, recvbuf, count, *datatype, *op, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iexscan_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Iexscan_c(sendbuf, recvbuf, count, *datatype, *op, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Igather(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Igather(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Igather_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Igather_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Igatherv(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Igatherv(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Igatherv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Igatherv_c(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Improbe(int source, int tag, MPI_Comm *comm, int *flag, MPI_Message **message, WRAP_Status *status)
{
    MPI_Status impl_status;
    *message = malloc(sizeof(MPI_Message));
    int rc = IMPL_Improbe(RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), *comm, flag, *message, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Imrecv(void *buf, int count, MPI_Datatype *datatype, MPI_Message **message, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Imrecv(buf, count, *datatype, *message, *request);
    free(*message);
    *message = &IMPL_MESSAGE_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Imrecv_c(void *buf, IMPL_Count count, MPI_Datatype *datatype, MPI_Message **message, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Imrecv_c(buf, count, *datatype, *message, *request);
    free(*message);
    *message = &IMPL_MESSAGE_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ineighbor_allgather(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_allgather_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ineighbor_allgather_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ineighbor_allgatherv(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_allgatherv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ineighbor_allgatherv_c(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ineighbor_alltoall(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_alltoall_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ineighbor_alltoall_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ineighbor_alltoallv(sendbuf, sendcounts, sdispls, *sendtype, recvbuf, recvcounts, rdispls, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_alltoallv_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ineighbor_alltoallv_c(sendbuf, sendcounts, sdispls, *sendtype, recvbuf, recvcounts, rdispls, *recvtype, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_alltoallw(const void *sendbuf, const int sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype* sendtypes[], void *recvbuf, const int recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype* recvtypes[], MPI_Comm *comm, MPI_Request **request)
{
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    *request = malloc(sizeof(MPI_Request));
    rc = IMPL_Ineighbor_alltoallw(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_alltoallw_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype* sendtypes[], void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype* recvtypes[], MPI_Comm *comm, MPI_Request **request)
{
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    *request = malloc(sizeof(MPI_Request));
    rc = IMPL_Ineighbor_alltoallw_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_create(MPI_Info **info)
{
    *info = malloc(sizeof(MPI_Info));
    int rc = IMPL_Info_create(*info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_create_env(int argc, char *argv[], MPI_Info **info)
{
    *info = malloc(sizeof(MPI_Info));
    int rc = IMPL_Info_create_env(argc, argv, *info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_delete(MPI_Info *info, const char *key)
{
    int rc = IMPL_Info_delete(*info, key);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_dup(MPI_Info *info, MPI_Info **newinfo)
{
    *newinfo = malloc(sizeof(MPI_Info));
    int rc = IMPL_Info_dup(*info, *newinfo);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_free(MPI_Info **info)
{
    int rc = IMPL_Info_free(*info);
    free(*info);
    *info = &IMPL_INFO_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get(MPI_Info *info, const char *key, int valuelen, char *value, int *flag)
{
    int rc = IMPL_Info_get(*info, key, valuelen, value, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get_nkeys(MPI_Info *info, int *nkeys)
{
    int rc = IMPL_Info_get_nkeys(*info, nkeys);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get_nthkey(MPI_Info *info, int n, char *key)
{
    int rc = IMPL_Info_get_nthkey(*info, n, key);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get_string(MPI_Info *info, const char *key, int *buflen, char *value, int *flag)
{
    int rc = IMPL_Info_get_string(*info, key, buflen, value, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get_valuelen(MPI_Info *info, const char *key, int *valuelen, int *flag)
{
    int rc = IMPL_Info_get_valuelen(*info, key, valuelen, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_set(MPI_Info *info, const char *key, const char *value)
{
    int rc = IMPL_Info_set(*info, key, value);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Intercomm_create(MPI_Comm *local_comm, int local_leader, MPI_Comm *peer_comm, int remote_leader, int tag, MPI_Comm **newintercomm)
{
    *newintercomm = malloc(sizeof(MPI_Comm));
    int rc = IMPL_Intercomm_create(*local_comm, local_leader, *peer_comm, remote_leader, TAG_MUK_TO_IMPL(tag), *newintercomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Intercomm_create_from_groups(MPI_Group *local_group, int local_leader, MPI_Group *remote_group, int remote_leader, const char *stringtag, MPI_Info *info, MPI_Errhandler *errhandler, MPI_Comm **newintercomm)
{
    *newintercomm = malloc(sizeof(MPI_Comm));
    int rc = IMPL_Intercomm_create_from_groups(*local_group, local_leader, *remote_group, remote_leader, stringtag, *info, *errhandler, *newintercomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Intercomm_merge(MPI_Comm *intercomm, int high, MPI_Comm **newintracomm)
{
    *newintracomm = malloc(sizeof(MPI_Comm));
    int rc = IMPL_Intercomm_merge(*intercomm, high, *newintracomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iprobe(int source, int tag, MPI_Comm *comm, int *flag, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Iprobe(RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), *comm, flag, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Irecv(void *buf, int count, MPI_Datatype *datatype, int source, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Irecv(buf, count, *datatype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Irecv_c(void *buf, IMPL_Count count, MPI_Datatype *datatype, int source, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Irecv_c(buf, count, *datatype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ireduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype *datatype, MPI_Op *op, int root, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ireduce(sendbuf, recvbuf, count, *datatype, *op, RANK_MUK_TO_IMPL(root), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ireduce_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype *datatype, MPI_Op *op, int root, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ireduce_c(sendbuf, recvbuf, count, *datatype, *op, RANK_MUK_TO_IMPL(root), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ireduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ireduce_scatter(sendbuf, recvbuf, recvcounts, *datatype, *op, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ireduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ireduce_scatter_block(sendbuf, recvbuf, recvcount, *datatype, *op, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ireduce_scatter_block_c(const void *sendbuf, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ireduce_scatter_block_c(sendbuf, recvbuf, recvcount, *datatype, *op, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ireduce_scatter_c(const void *sendbuf, void *recvbuf, const IMPL_Count recvcounts[], MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ireduce_scatter_c(sendbuf, recvbuf, recvcounts, *datatype, *op, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Irsend(const void *buf, int count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Irsend(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Irsend_c(const void *buf, IMPL_Count count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Irsend_c(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Iscan(sendbuf, recvbuf, count, *datatype, *op, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iscan_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Iscan_c(sendbuf, recvbuf, count, *datatype, *op, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iscatter(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Iscatter(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iscatter_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Iscatter_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iscatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Iscatterv(sendbuf, sendcounts, displs, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iscatterv_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint displs[], MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Iscatterv_c(sendbuf, sendcounts, displs, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Isend(const void *buf, int count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Isend(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Isend_c(const void *buf, IMPL_Count count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Isend_c(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Isendrecv(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype *recvtype, int source, int recvtag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Isendrecv(sendbuf, sendcount, *sendtype, RANK_MUK_TO_IMPL(dest), sendtag, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(source), recvtag, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Isendrecv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, int dest, int sendtag, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, int source, int recvtag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Isendrecv_c(sendbuf, sendcount, *sendtype, RANK_MUK_TO_IMPL(dest), sendtag, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(source), recvtag, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Isendrecv_replace(void *buf, int count, MPI_Datatype *datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Isendrecv_replace(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), sendtag, RANK_MUK_TO_IMPL(source), recvtag, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Isendrecv_replace_c(void *buf, IMPL_Count count, MPI_Datatype *datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Isendrecv_replace_c(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), sendtag, RANK_MUK_TO_IMPL(source), recvtag, *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Issend(const void *buf, int count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Issend(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Issend_c(const void *buf, IMPL_Count count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Issend_c(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Keyval_create(MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state)
{
    int rc = IMPL_Keyval_create(copy_fn, delete_fn, keyval, extra_state);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Keyval_free(int *keyval)
{
    int rc = IMPL_Keyval_free(keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Lookup_name(const char *service_name, MPI_Info *info, char *port_name)
{
    int rc = IMPL_Lookup_name(service_name, *info, port_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Mprobe(int source, int tag, MPI_Comm *comm, MPI_Message **message, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Mprobe(RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), *comm, *message, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Mrecv(void *buf, int count, MPI_Datatype *datatype, MPI_Message **message, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Mrecv(buf, count, *datatype, *message, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    free(*message);
    *message = &IMPL_MESSAGE_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Mrecv_c(void *buf, IMPL_Count count, MPI_Datatype *datatype, MPI_Message **message, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Mrecv_c(buf, count, *datatype, *message, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    free(*message);
    *message = &IMPL_MESSAGE_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Neighbor_allgather(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_allgather_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Neighbor_allgather_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_allgather_init(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Neighbor_allgather_init(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_allgather_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Neighbor_allgather_init_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Neighbor_allgatherv(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_allgatherv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Neighbor_allgatherv_c(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_allgatherv_init(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Neighbor_allgatherv_init(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_allgatherv_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Neighbor_allgatherv_init_c(sendbuf, sendcount, *sendtype, recvbuf, recvcounts, displs, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Neighbor_alltoall(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoall_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Neighbor_alltoall_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoall_init(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Neighbor_alltoall_init(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoall_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Neighbor_alltoall_init_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Neighbor_alltoallv(sendbuf, sendcounts, sdispls, *sendtype, recvbuf, recvcounts, rdispls, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoallv_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], MPI_Datatype *recvtype, MPI_Comm *comm)
{
    int rc = IMPL_Neighbor_alltoallv_c(sendbuf, sendcounts, sdispls, *sendtype, recvbuf, recvcounts, rdispls, *recvtype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype *sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Neighbor_alltoallv_init(sendbuf, sendcounts, sdispls, *sendtype, recvbuf, recvcounts, rdispls, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoallv_init_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], MPI_Datatype *sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], MPI_Datatype *recvtype, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Neighbor_alltoallv_init_c(sendbuf, sendcounts, sdispls, *sendtype, recvbuf, recvcounts, rdispls, *recvtype, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype* sendtypes[], void *recvbuf, const int recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype* recvtypes[], MPI_Comm *comm)
{
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    rc = IMPL_Neighbor_alltoallw(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoallw_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype* sendtypes[], void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype* recvtypes[], MPI_Comm *comm)
{
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    rc = IMPL_Neighbor_alltoallw_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoallw_init(const void *sendbuf, const int sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype* sendtypes[], void *recvbuf, const int recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype* recvtypes[], MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    *request = malloc(sizeof(MPI_Request));
    rc = IMPL_Neighbor_alltoallw_init(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoallw_init_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype* sendtypes[], void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype* recvtypes[], MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    *request = malloc(sizeof(MPI_Request));
    rc = IMPL_Neighbor_alltoallw_init_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Op_commutative(MPI_Op *op, int *commute)
{
    int rc = IMPL_Op_commutative(*op, commute);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

// not thread safe - hack that will be replaced by generating trampolines at runtime
static WRAP_User_function * user_function_address;

void trampoline(void *invec, void *inoutvec, int *len, MPI_Datatype * datatype)
{
    int rc;
    int flag;
    reduce_trampoline_cookie_t * cookie = NULL;
    rc = IMPL_Type_get_attr(*datatype, TYPE_HANDLE_KEY, &cookie, &flag);
    if (rc != MPI_SUCCESS || !flag) {
        MUK_Warning("trampoline: IMPL_Type_get_attr failed: flag=%d rc=%d\n", flag, rc);
        MPI_Abort(MPI_COMM_SELF,rc);
    }
    MPI_Datatype       * dptr = NULL;
    WRAP_User_function * fptr = NULL;
    if (flag) {
        dptr = cookie->dt;
        fptr = cookie->fp;
    }
    (*fptr)(invec,inoutvec,len,&dptr);
}

int WRAP_Op_create(WRAP_User_function *user_fn, int commute, MPI_Op **op)
{
    *op = malloc(sizeof(MPI_Op));
    user_function_address = user_fn;
    int rc = IMPL_Op_create(trampoline, commute, *op);
#if 1
    add_op_pair_to_list(user_fn, *op);
#else
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.
    op_fptr_pair_t * pair = malloc(sizeof(op_fptr_pair_t));
    pair->op = *op;
    pair->fp = user_fn;
    pair->prev = NULL;
    pair->next = NULL;

    if (op_fptr_pair_list == NULL) {
        op_fptr_pair_list = pair;
    } else {
        op_fptr_pair_t * parent = op_fptr_pair_list;
        while (parent->next != NULL) {
            parent = parent->next;
        }
        parent->next = pair;
        pair->prev   = parent;
    }
#endif
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Op_create_c(MPI_User_function_c *user_fn, int commute, MPI_Op **op)
{
    *op = malloc(sizeof(MPI_Op));
    int rc = IMPL_Op_create_c(user_fn, commute, *op);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Op_free(MPI_Op **op)
{
#if 1
    remove_op_pair_from_list(*op);
#else
    // Step 1: look up *op in the linked list
    op_fptr_pair_t * current = op_fptr_pair_list;
    if (op_fptr_pair_list == NULL) {
        MUK_Warning("Op_free: op_fptr_pair_list is NULL - this should be impossible.\n");
    }
    while (current) {
        if (current->op == *op) {
            break;
        }
        current = current->next;
    }

    // Step 2: remove current from the list
    if (current->prev == NULL) {
        MUK_Assert(current == op_fptr_pair_list);
        op_fptr_pair_list = current->next;
        if (current->next != NULL) {
            current->next->prev = NULL;
        }
    } else {
        current->prev->next = current->next;
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
    }

    // Step 3: free the memory
    free(current);
#endif
    int rc = IMPL_Op_free(*op);
    free(*op);
    *op = &IMPL_OP_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Open_port(MPI_Info *info, char *port_name)
{
    int rc = IMPL_Open_port(*info, port_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pack(const void *inbuf, int incount, MPI_Datatype *datatype, void *outbuf, int outsize, int *position, MPI_Comm *comm)
{
    int rc = IMPL_Pack(inbuf, incount, *datatype, outbuf, outsize, position, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pack_c(const void *inbuf, IMPL_Count incount, MPI_Datatype *datatype, void *outbuf, IMPL_Count outsize, IMPL_Count *position, MPI_Comm *comm)
{
    int rc = IMPL_Pack_c(inbuf, incount, *datatype, outbuf, outsize, position, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pack_external(const char *datarep, const void *inbuf, int incount, MPI_Datatype *datatype, void *outbuf, IMPL_Aint outsize, IMPL_Aint *position)
{
    int rc = IMPL_Pack_external(datarep, inbuf, incount, *datatype, outbuf, outsize, position);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pack_external_c(const char *datarep, const void *inbuf, IMPL_Count incount, MPI_Datatype *datatype, void *outbuf, IMPL_Count outsize, IMPL_Count *position)
{
    int rc = IMPL_Pack_external_c(datarep, inbuf, incount, *datatype, outbuf, outsize, position);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pack_external_size(const char *datarep, int incount, MPI_Datatype *datatype, IMPL_Aint *size)
{
    int rc = IMPL_Pack_external_size(datarep, incount, *datatype, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pack_external_size_c(const char *datarep, IMPL_Count incount, MPI_Datatype *datatype, IMPL_Count *size)
{
    int rc = IMPL_Pack_external_size_c(datarep, incount, *datatype, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pack_size(int incount, MPI_Datatype *datatype, MPI_Comm *comm, int *size)
{
    int rc = IMPL_Pack_size(incount, *datatype, *comm, size);
    *size = UNDEFINED_IMPL_TO_MUK(*size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pack_size_c(IMPL_Count incount, MPI_Datatype *datatype, MPI_Comm *comm, IMPL_Count *size)
{
    int rc = IMPL_Pack_size_c(incount, *datatype, *comm, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Parrived(MPI_Request *request, int partition, int *flag)
{
    int rc = IMPL_Parrived(*request, partition, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pcontrol(const int level, ...)
{
    int rc = IMPL_Pcontrol(level);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pready(int partition, MPI_Request *request)
{
    int rc = IMPL_Pready(partition, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pready_list(int length, const int array_of_partitions[], MPI_Request *request)
{
    int rc = IMPL_Pready_list(length, array_of_partitions, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pready_range(int partition_low, int partition_high, MPI_Request *request)
{
    int rc = IMPL_Pready_range(partition_low, partition_high, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Precv_init(void *buf, int partitions, IMPL_Count count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Precv_init(buf, partitions, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Probe(int source, int tag, MPI_Comm *comm, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Probe(RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), *comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Psend_init(const void *buf, int partitions, IMPL_Count count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Psend_init(buf, partitions, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Publish_name(const char *service_name, MPI_Info *info, const char *port_name)
{
    int rc = IMPL_Publish_name(service_name, *info, port_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Put(const void *origin_addr, int origin_count, MPI_Datatype *origin_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype *target_datatype, MPI_Win *win)
{
    int rc = IMPL_Put(origin_addr, origin_count, *origin_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Put_c(const void *origin_addr, IMPL_Count origin_count, MPI_Datatype *origin_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype *target_datatype, MPI_Win *win)
{
    int rc = IMPL_Put_c(origin_addr, origin_count, *origin_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Raccumulate(const void *origin_addr, int origin_count, MPI_Datatype *origin_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype *target_datatype, MPI_Op *op, MPI_Win *win, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Raccumulate(origin_addr, origin_count, *origin_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *op, *win, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Raccumulate_c(const void *origin_addr, IMPL_Count origin_count, MPI_Datatype *origin_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype *target_datatype, MPI_Op *op, MPI_Win *win, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Raccumulate_c(origin_addr, origin_count, *origin_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *op, *win, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Recv(void *buf, int count, MPI_Datatype *datatype, int source, int tag, MPI_Comm *comm, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Recv(buf, count, *datatype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), *comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Recv_c(void *buf, IMPL_Count count, MPI_Datatype *datatype, int source, int tag, MPI_Comm *comm, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Recv_c(buf, count, *datatype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), *comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Recv_init(void *buf, int count, MPI_Datatype *datatype, int source, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Recv_init(buf, count, *datatype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Recv_init_c(void *buf, IMPL_Count count, MPI_Datatype *datatype, int source, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Recv_init_c(buf, count, *datatype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype *datatype, MPI_Op *op, int root, MPI_Comm *comm)
{
    int rc;
    if (IS_PREDEFINED_OP(*op)) {
        rc = IMPL_Reduce(sendbuf, recvbuf, count, *datatype, *op, RANK_MUK_TO_IMPL(root), *comm);
    }
    else {
        // Part 1: look up the user function associated with the MPI_Op argument
        WRAP_User_function * user_fn = lookup_op_pair(op);
        if (user_fn == NULL) {
            MUK_Warning("failed to find valid op<->fn mapping.\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }

        // Part 2: duplicate the datatype so there can be no collision of keyvals
        MPI_Datatype dup;
        rc = IMPL_Type_dup(*datatype,&dup);
        if (rc) {
            MUK_Warning("Type_dup failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }

        // Part 3: bake the cookie
        reduce_trampoline_cookie_t * cookie = malloc(sizeof(reduce_trampoline_cookie_t));
        cookie->dt = datatype;
        cookie->fp = user_fn;
        rc = IMPL_Type_set_attr(dup, TYPE_HANDLE_KEY, cookie);
        if (rc) {
            MUK_Warning("Type_set_attr failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }

        // Part 4: do the reduction
        rc = IMPL_Reduce(sendbuf, recvbuf, count, dup, *op, RANK_MUK_TO_IMPL(root), *comm);

        // Part 5: clean up
        free(cookie);
        rc = IMPL_Type_free(&dup);
        if (rc) {
            MUK_Warning("Type_free failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }
    }
    end:
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype *datatype, MPI_Op *op, int root, MPI_Comm *comm)
{
    int rc;
    if (IS_PREDEFINED_OP(*op)) {
        rc = IMPL_Reduce_c(sendbuf, recvbuf, count, *datatype, *op, RANK_MUK_TO_IMPL(root), *comm);
    } else {
        MUK_Warning("WRAP_Reduce_c does not implement user-defined ops.\n");
        rc = MPI_ERR_INTERN;
    }
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype *datatype, MPI_Op *op, int root, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Reduce_init(sendbuf, recvbuf, count, *datatype, *op, RANK_MUK_TO_IMPL(root), *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_init_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype *datatype, MPI_Op *op, int root, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Reduce_init_c(sendbuf, recvbuf, count, *datatype, *op, RANK_MUK_TO_IMPL(root), *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_local(const void *inbuf, void *inoutbuf, int count, MPI_Datatype *datatype, MPI_Op *op)
{
    int rc;
    if (IS_PREDEFINED_OP(*op)) {
        rc = IMPL_Reduce_local(inbuf, inoutbuf, count, *datatype, *op);
    }
    else {
        // Part 1: look up the user function associated with the MPI_Op argument
        WRAP_User_function * user_fn = lookup_op_pair(op);
        if (user_fn == NULL) {
            MUK_Warning("failed to find valid op<->fn mapping.\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }

        // Part 2: duplicate the datatype so there can be no collision of keyvals
        MPI_Datatype dup;
        rc = IMPL_Type_dup(*datatype,&dup);
        if (rc) {
            MUK_Warning("Type_dup failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }

        // Part 3: bake the cookie
        reduce_trampoline_cookie_t * cookie = malloc(sizeof(reduce_trampoline_cookie_t));
        cookie->dt = datatype;
        cookie->fp = user_fn;
        rc = IMPL_Type_set_attr(dup, TYPE_HANDLE_KEY, cookie);
        if (rc) {
            MUK_Warning("Type_set_attr failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }

        // Part 4: do the reduction
        rc = IMPL_Reduce_local(inbuf, inoutbuf, count, dup, *op);

        // Part 5: clean up
        free(cookie);
        rc = IMPL_Type_free(&dup);
        if (rc) {
            MUK_Warning("Type_free failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }
    }
    end:
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_local_c(const void *inbuf, void *inoutbuf, IMPL_Count count, MPI_Datatype *datatype, MPI_Op *op)
{
    int rc;
    if (IS_PREDEFINED_OP(*op)) {
        rc = IMPL_Reduce_local_c(inbuf, inoutbuf, count, *datatype, *op);
    } else {
        MUK_Warning("WRAP_Reduce_local_c does not implement user-defined ops.\n");
        rc = MPI_ERR_INTERN;
    }
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm)
{
    int rc;
    if (IS_PREDEFINED_OP(*op)) {
        rc = IMPL_Reduce_scatter(sendbuf, recvbuf, recvcounts, *datatype, *op, *comm);
    }
    else {
        // Part 1: look up the user function associated with the MPI_Op argument
        WRAP_User_function * user_fn = lookup_op_pair(op);
        if (user_fn == NULL) {
            MUK_Warning("failed to find valid op<->fn mapping.\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }

        // Part 2: duplicate the datatype so there can be no collision of keyvals
        MPI_Datatype dup;
        rc = IMPL_Type_dup(*datatype,&dup);
        if (rc) {
            MUK_Warning("Type_dup failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }

        // Part 3: bake the cookie
        reduce_trampoline_cookie_t * cookie = malloc(sizeof(reduce_trampoline_cookie_t));
        cookie->dt = datatype;
        cookie->fp = user_fn;
        rc = IMPL_Type_set_attr(dup, TYPE_HANDLE_KEY, cookie);
        if (rc) {
            MUK_Warning("Type_set_attr failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }

        // Part 4: do the reduction
        rc = IMPL_Reduce_scatter(sendbuf, recvbuf, recvcounts, dup, *op, *comm);

        // Part 5: clean up
        free(cookie);
        rc = IMPL_Type_free(&dup);
        if (rc) {
            MUK_Warning("Type_free failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }
    }
    end:
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm)
{
    int rc;
    if (IS_PREDEFINED_OP(*op)) {
        rc = IMPL_Reduce_scatter_block(sendbuf, recvbuf, recvcount, *datatype, *op, *comm);
    }
    else {
        // Part 1: look up the user function associated with the MPI_Op argument
        WRAP_User_function * user_fn = lookup_op_pair(op);
        if (user_fn == NULL) {
            MUK_Warning("failed to find valid op<->fn mapping.\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }

        // Part 2: duplicate the datatype so there can be no collision of keyvals
        MPI_Datatype dup;
        rc = IMPL_Type_dup(*datatype,&dup);
        if (rc) {
            MUK_Warning("Type_dup failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }

        // Part 3: bake the cookie
        reduce_trampoline_cookie_t * cookie = malloc(sizeof(reduce_trampoline_cookie_t));
        cookie->dt = datatype;
        cookie->fp = user_fn;
        rc = IMPL_Type_set_attr(dup, TYPE_HANDLE_KEY, cookie);
        if (rc) {
            MUK_Warning("Type_set_attr failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }

        // Part 4: do the reduction
        rc = IMPL_Reduce_scatter_block(sendbuf, recvbuf, recvcount, dup, *op, *comm);

        // Part 5: clean up
        free(cookie);
        rc = IMPL_Type_free(&dup);
        if (rc) {
            MUK_Warning("Type_free failed\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }
    }
    end:
    return ERROR_CODE_IMPL_TO_MUK(rc);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_block_c(const void *sendbuf, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm)
{
    int rc;
    if (IS_PREDEFINED_OP(*op)) {
        rc = IMPL_Reduce_scatter_block_c(sendbuf, recvbuf, recvcount, *datatype, *op, *comm);
    } else {
        MUK_Warning("WRAP_Reduce_scatter_block_c does not implement user-defined ops.\n");
        rc = MPI_ERR_INTERN;
    }
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_block_init(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Reduce_scatter_block_init(sendbuf, recvbuf, recvcount, *datatype, *op, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_block_init_c(const void *sendbuf, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Reduce_scatter_block_init_c(sendbuf, recvbuf, recvcount, *datatype, *op, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_c(const void *sendbuf, void *recvbuf, const IMPL_Count recvcounts[], MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm)
{
    int rc;
    if (IS_PREDEFINED_OP(*op)) {
        rc = IMPL_Reduce_scatter_c(sendbuf, recvbuf, recvcounts, *datatype, *op, *comm);
    } else {
        MUK_Warning("WRAP_Reduce_scatter_c does not implement user-defined ops.\n");
        rc = MPI_ERR_INTERN;
    }
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_init(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Reduce_scatter_init(sendbuf, recvbuf, recvcounts, *datatype, *op, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_init_c(const void *sendbuf, void *recvbuf, const IMPL_Count recvcounts[], MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Reduce_scatter_init_c(sendbuf, recvbuf, recvcounts, *datatype, *op, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Register_datarep(const char *datarep, MPI_Datarep_conversion_function *read_conversion_fn, MPI_Datarep_conversion_function *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state)
{
    int rc = IMPL_Register_datarep(datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Register_datarep_c(const char *datarep, MPI_Datarep_conversion_function_c *read_conversion_fn, MPI_Datarep_conversion_function_c *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state)
{
    int rc = IMPL_Register_datarep_c(datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Request_free(MPI_Request **request)
{
    int rc = IMPL_Request_free(*request);
    free(*request);
    *request = &IMPL_REQUEST_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Request_get_status(MPI_Request *request, int *flag, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Request_get_status(*request, flag, &impl_status);
    if (*flag) {
        MPI_Status_to_WRAP_Status(&impl_status, status);
    }
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Rget(void *origin_addr, int origin_count, MPI_Datatype *origin_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype *target_datatype, MPI_Win *win, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Rget(origin_addr, origin_count, *origin_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *win, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Rget_accumulate(const void *origin_addr, int origin_count, MPI_Datatype *origin_datatype, void *result_addr, int result_count, MPI_Datatype *result_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype *target_datatype, MPI_Op *op, MPI_Win *win, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Rget_accumulate(origin_addr, origin_count, *origin_datatype, result_addr, result_count, *result_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *op, *win, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Rget_accumulate_c(const void *origin_addr, IMPL_Count origin_count, MPI_Datatype *origin_datatype, void *result_addr, IMPL_Count result_count, MPI_Datatype *result_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype *target_datatype, MPI_Op *op, MPI_Win *win, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Rget_accumulate_c(origin_addr, origin_count, *origin_datatype, result_addr, result_count, *result_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *op, *win, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Rget_c(void *origin_addr, IMPL_Count origin_count, MPI_Datatype *origin_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype *target_datatype, MPI_Win *win, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Rget_c(origin_addr, origin_count, *origin_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *win, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Rput(const void *origin_addr, int origin_count, MPI_Datatype *origin_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype *target_datatype, MPI_Win *win, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Rput(origin_addr, origin_count, *origin_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *win, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Rput_c(const void *origin_addr, IMPL_Count origin_count, MPI_Datatype *origin_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype *target_datatype, MPI_Win *win, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Rput_c(origin_addr, origin_count, *origin_datatype, RANK_MUK_TO_IMPL(target_rank), target_disp, target_count, *target_datatype, *win, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Rsend(const void *buf, int count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm)
{
    int rc = IMPL_Rsend(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Rsend_c(const void *buf, IMPL_Count count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm)
{
    int rc = IMPL_Rsend_c(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Rsend_init(const void *buf, int count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Rsend_init(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Rsend_init_c(const void *buf, IMPL_Count count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Rsend_init_c(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Scan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm)
{
    int rc = IMPL_Scan(sendbuf, recvbuf, count, *datatype, *op, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Scan_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm)
{
    int rc = IMPL_Scan_c(sendbuf, recvbuf, count, *datatype, *op, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Scan_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Scan_init(sendbuf, recvbuf, count, *datatype, *op, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Scan_init_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Scan_init_c(sendbuf, recvbuf, count, *datatype, *op, *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Scatter(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm)
{
    int rc = IMPL_Scatter(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Scatter_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm)
{
    int rc = IMPL_Scatter_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Scatter_init(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Scatter_init(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Scatter_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Scatter_init_c(sendbuf, sendcount, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm)
{
    int rc = IMPL_Scatterv(sendbuf, sendcounts, displs, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Scatterv_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint displs[], MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm)
{
    int rc = IMPL_Scatterv_c(sendbuf, sendcounts, displs, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Scatterv_init(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype *sendtype, void *recvbuf, int recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Scatterv_init(sendbuf, sendcounts, displs, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Scatterv_init_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint displs[], MPI_Datatype *sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, int root, MPI_Comm *comm, MPI_Info *info, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Scatterv_init_c(sendbuf, sendcounts, displs, *sendtype, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(root), *comm, *info, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Send(const void *buf, int count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm)
{
    int rc = IMPL_Send(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Send_c(const void *buf, IMPL_Count count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm)
{
    int rc = IMPL_Send_c(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Send_init(const void *buf, int count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Send_init(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Send_init_c(const void *buf, IMPL_Count count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Send_init_c(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype *sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype *recvtype, int source, int recvtag, MPI_Comm *comm, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Sendrecv(sendbuf, sendcount, *sendtype, RANK_MUK_TO_IMPL(dest), sendtag, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(source), recvtag, *comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Sendrecv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype *sendtype, int dest, int sendtag, void *recvbuf, IMPL_Count recvcount, MPI_Datatype *recvtype, int source, int recvtag, MPI_Comm *comm, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Sendrecv_c(sendbuf, sendcount, *sendtype, RANK_MUK_TO_IMPL(dest), sendtag, recvbuf, recvcount, *recvtype, RANK_MUK_TO_IMPL(source), recvtag, *comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Sendrecv_replace(void *buf, int count, MPI_Datatype *datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm *comm, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Sendrecv_replace(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), sendtag, RANK_MUK_TO_IMPL(source), recvtag, *comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Sendrecv_replace_c(void *buf, IMPL_Count count, MPI_Datatype *datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm *comm, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Sendrecv_replace_c(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), sendtag, RANK_MUK_TO_IMPL(source), recvtag, *comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Session_call_errhandler(MPI_Session *session, int errorcode)
{
    int rc = IMPL_Session_call_errhandler(*session, errorcode);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_create_errhandler(MPI_Session_errhandler_function *session_errhandler_fn, MPI_Errhandler **errhandler)
{
    *errhandler = malloc(sizeof(MPI_Errhandler));
    int rc = IMPL_Session_create_errhandler(session_errhandler_fn, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_finalize(MPI_Session **session)
{
    int rc = IMPL_Session_finalize(*session);
    free(*session);
    *session = &IMPL_SESSION_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_errhandler(MPI_Session *session, MPI_Errhandler **errhandler)
{
    *errhandler = malloc(sizeof(MPI_Errhandler));
    int rc = IMPL_Session_get_errhandler(*session, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_info(MPI_Session *session, MPI_Info *info_used)
{
    int rc = IMPL_Session_get_info(*session, info_used);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_nth_pset(MPI_Session *session, MPI_Info *info, int n, int *pset_len, char *pset_name)
{
    int rc = IMPL_Session_get_nth_pset(*session, *info, n, pset_len, pset_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_num_psets(MPI_Session *session, MPI_Info *info, int *npset_names)
{
    int rc = IMPL_Session_get_num_psets(*session, *info, npset_names);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_pset_info(MPI_Session *session, const char *pset_name, MPI_Info **info)
{
    *info = malloc(sizeof(MPI_Info));
    int rc = IMPL_Session_get_pset_info(*session, pset_name, *info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_init(MPI_Info *info, MPI_Errhandler *errhandler, MPI_Session **session)
{
    *session = malloc(sizeof(MPI_Session));
    int rc = IMPL_Session_init(*info, *errhandler, *session);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_set_errhandler(MPI_Session *session, MPI_Errhandler *errhandler)
{
    int rc = IMPL_Session_set_errhandler(*session, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ssend(const void *buf, int count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm)
{
    int rc = IMPL_Ssend(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ssend_c(const void *buf, IMPL_Count count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm)
{
    int rc = IMPL_Ssend_c(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ssend_init(const void *buf, int count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ssend_init(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ssend_init_c(const void *buf, IMPL_Count count, MPI_Datatype *datatype, int dest, int tag, MPI_Comm *comm, MPI_Request **request)
{
    *request = malloc(sizeof(MPI_Request));
    int rc = IMPL_Ssend_init_c(buf, count, *datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), *comm, *request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Start(MPI_Request **request)
{
    int rc = IMPL_Start(*request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Startall(int count, MPI_Request array_of_requests[])
{
    int rc = IMPL_Startall(count, array_of_requests);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#ifdef SUPPORT_F08
int WRAP_Status_f082c(const WRAP_F08_status *f08_status, WRAP_Status *c_status)
{
    int rc = IMPL_Status_f082c(f08_status, c_status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Status_f082f(const WRAP_F08_status *f08_status, MPI_Fint *f_status)
{
    int rc = IMPL_Status_f082f(f08_status, f_status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Status_f2f08(const MPI_Fint *f_status, WRAP_F08_status *f08_status)
{
    int rc = IMPL_Status_f2f08(f_status, f08_status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Status_set_cancelled(WRAP_Status *status, int flag)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Status_set_cancelled(&impl_status, flag);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Status_set_elements(WRAP_Status *status, MPI_Datatype *datatype, int count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Status_set_elements(&impl_status, *datatype, count);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Status_set_elements_c(WRAP_Status *status, MPI_Datatype *datatype, IMPL_Count count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Status_set_elements_c(&impl_status, *datatype, count);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Status_set_elements_x(WRAP_Status *status, MPI_Datatype *datatype, IMPL_Count count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Status_set_elements_x(&impl_status, *datatype, count);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Test(MPI_Request **request, int *flag, WRAP_Status *status)
{
    const bool ignore = (intptr_t)status == (intptr_t)IMPL_STATUS_IGNORE;
    MPI_Status impl_status;
    int rc = IMPL_Test(*request, flag, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (*flag) {
        free(*request);
        *request = &IMPL_REQUEST_NULL;
        if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    }
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Test_cancelled(const WRAP_Status *status, int *flag)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Test_cancelled(&impl_status, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Testall(int count, MPI_Request* array_of_requests[], int *flag, WRAP_Status array_of_statuses[])
{
    MPI_Request * impl_requests = malloc(count * sizeof(MPI_Request));
    if (impl_requests == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<count; i++) {
        impl_requests[i] = *array_of_requests[i];
    }

    const bool ignore = (intptr_t)array_of_statuses == (intptr_t)IMPL_STATUSES_IGNORE;
    MPI_Status * impl_statuses = NULL;
    if (!ignore) {
        impl_statuses = malloc(count * sizeof(MPI_Status));
        if (impl_statuses == NULL) return MPI_ERR_INTERN;
    }

    int rc = IMPL_Testall(count, impl_requests, flag, ignore ? MPI_STATUSES_IGNORE : impl_statuses);

    if (*flag) {
        for (int i=0; i<count; i++) {
            if (impl_requests[i] == MPI_REQUEST_NULL) {
                free(array_of_requests[i]);
                array_of_requests[i] = &IMPL_REQUEST_NULL;
            }
        }
    }
    free(impl_requests);

    if (!ignore) {
        for (int i=0; i<count; i++) {
            MPI_Status_to_WRAP_Status(&impl_statuses[i], &array_of_statuses[i]);
        }
        free(impl_statuses);
    }

    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Testany(int count, MPI_Request* array_of_requests[], int *indx, int *flag, WRAP_Status *status)
{
    MPI_Request * impl_requests = malloc(count * sizeof(MPI_Request));
    if (impl_requests == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<count; i++) {
        impl_requests[i] = *array_of_requests[i];
    }

    const bool ignore = (intptr_t)status == (intptr_t)IMPL_STATUS_IGNORE;
    MPI_Status impl_status;

    int rc = IMPL_Testany(count, impl_requests, indx, flag, ignore ? MPI_STATUS_IGNORE : &impl_status);

    if (*flag) {
        // If the array contains no active handles then the call returns immediately with flag = true,
        // index = MPI_UNDEFINED, and an empty status.
        if (*indx != MPI_UNDEFINED) {

            if (impl_requests[*indx] == MPI_REQUEST_NULL) {
                free(array_of_requests[*indx]);
                array_of_requests[*indx] = &IMPL_REQUEST_NULL;
            }

            if (!ignore) {
                MPI_Status_to_WRAP_Status(&impl_status, status);
            }
        }
    }

    free(impl_requests);

    *indx = UNDEFINED_IMPL_TO_MUK(*indx);

    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Testsome(int incount, MPI_Request* array_of_requests[], int *outcount, int array_of_indices[], WRAP_Status array_of_statuses[])
{
    MPI_Request * impl_requests = malloc(incount * sizeof(MPI_Request));
    if (impl_requests == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<incount; i++) {
        impl_requests[i] = *array_of_requests[i];
    }

    const bool ignore = (intptr_t)array_of_statuses == (intptr_t)IMPL_STATUSES_IGNORE;
    MPI_Status * impl_statuses = NULL;
    if (!ignore) {
        impl_statuses = malloc(incount * sizeof(MPI_Status));
        if (impl_statuses == NULL) return MPI_ERR_INTERN;
    }

    int rc = IMPL_Testsome(incount, impl_requests, outcount, array_of_indices, ignore ? MPI_STATUSES_IGNORE : impl_statuses);

    if ((*outcount > 0) && (*outcount != MPI_UNDEFINED)) {

        for (int i=0; i<*outcount; i++) {
            const int j = array_of_indices[i];
            if (impl_requests[j] == MPI_REQUEST_NULL) {
                free(array_of_requests[j]);
                array_of_requests[j] = &IMPL_REQUEST_NULL;
            }
        }

        if (!ignore) {
            for (int i=0; i<incount; i++) {
                const int j = array_of_indices[i];
                MPI_Status_to_WRAP_Status(&impl_statuses[j], &array_of_statuses[j]);
            }
        }
    }

    if (!ignore) {
        free(impl_statuses);
    }

    free(impl_requests);

    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Topo_test(MPI_Comm *comm, int *status)
{
    int rc = IMPL_Topo_test(*comm, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_commit(MPI_Datatype **datatype)
{
    int rc = IMPL_Type_commit(*datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_contiguous(int count, MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_contiguous(count, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_contiguous_c(IMPL_Count count, MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_contiguous_c(count, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_darray(int size, int rank, int ndims, const int array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    int impl_order = MPI_UNDEFINED;
    if (order == MUK_ORDER_C) {
        impl_order = MPI_ORDER_C;
    }
    else if (order == MUK_ORDER_FORTRAN) {
        impl_order = MPI_ORDER_FORTRAN;
    }
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_darray(size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, impl_order, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_darray_c(int size, int rank, int ndims, const IMPL_Count array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    int impl_order = MPI_UNDEFINED;
    if (order == MUK_ORDER_C) {
        impl_order = MPI_ORDER_C;
    }
    else if (order == MUK_ORDER_FORTRAN) {
        impl_order = MPI_ORDER_FORTRAN;
    }
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_darray_c(size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, impl_order, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_f90_complex(int p, int r, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_f90_complex(p, r, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_f90_integer(int r, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_f90_integer(r, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_f90_real(int p, int r, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_f90_real(p, r, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_hindexed(int count, const int array_of_blocklengths[], const IMPL_Aint array_of_displacements[], MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_hindexed(count, array_of_blocklengths, array_of_displacements, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_hindexed_block(int count, int blocklength, const IMPL_Aint array_of_displacements[], MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_hindexed_block(count, blocklength, array_of_displacements, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_hindexed_block_c(IMPL_Count count, IMPL_Count blocklength, const IMPL_Count array_of_displacements[], MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_hindexed_block_c(count, blocklength, array_of_displacements, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_hindexed_c(IMPL_Count count, const IMPL_Count array_of_blocklengths[], const IMPL_Count array_of_displacements[], MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_hindexed_c(count, array_of_blocklengths, array_of_displacements, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_hvector(int count, int blocklength, IMPL_Aint stride, MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_hvector(count, blocklength, stride, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_hvector_c(IMPL_Count count, IMPL_Count blocklength, IMPL_Count stride, MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_hvector_c(count, blocklength, stride, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_indexed_block(count, blocklength, array_of_displacements, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_indexed_block_c(IMPL_Count count, IMPL_Count blocklength, const IMPL_Count array_of_displacements[], MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_indexed_block_c(count, blocklength, array_of_displacements, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_keyval(MPI_Type_copy_attr_function *type_copy_attr_fn, MPI_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state)
{
    int rc = IMPL_Type_create_keyval(type_copy_attr_fn, type_delete_attr_fn, type_keyval, extra_state);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_resized(MPI_Datatype *oldtype, IMPL_Aint lb, IMPL_Aint extent, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_resized(*oldtype, lb, extent, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_resized_c(MPI_Datatype *oldtype, IMPL_Count lb, IMPL_Count extent, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_resized_c(*oldtype, lb, extent, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_struct(int count, const int array_of_blocklengths[], const IMPL_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_struct(count, array_of_blocklengths, array_of_displacements, array_of_types, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_struct_c(IMPL_Count count, const IMPL_Count array_of_blocklengths[], const IMPL_Count array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_struct_c(count, array_of_blocklengths, array_of_displacements, array_of_types, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_subarray(int ndims, const int array_of_sizes[], const int array_of_subsizes[], const int array_of_starts[], int order, MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    int impl_order = MPI_UNDEFINED;
    if (order == MUK_ORDER_C) {
        impl_order = MPI_ORDER_C;
    }
    else if (order == MUK_ORDER_FORTRAN) {
        impl_order = MPI_ORDER_FORTRAN;
    }
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_subarray(ndims, array_of_sizes, array_of_subsizes, array_of_starts, impl_order, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_subarray_c(int ndims, const IMPL_Count array_of_sizes[], const IMPL_Count array_of_subsizes[], const IMPL_Count array_of_starts[], int order, MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    int impl_order = MPI_UNDEFINED;
    if (order == MUK_ORDER_C) {
        impl_order = MPI_ORDER_C;
    }
    else if (order == MUK_ORDER_FORTRAN) {
        impl_order = MPI_ORDER_FORTRAN;
    }
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_create_subarray_c(ndims, array_of_sizes, array_of_subsizes, array_of_starts, impl_order, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_delete_attr(MPI_Datatype *datatype, int type_keyval)
{
    int rc = IMPL_Type_delete_attr(*datatype, type_keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_dup(MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_dup(*oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_extent(MPI_Datatype *datatype, IMPL_Aint *extent)
{
    int rc = IMPL_Type_extent(*datatype, extent);
    *extent = UNDEFINED_IMPL_TO_MUK(*extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_free(MPI_Datatype **datatype)
{
    int rc = IMPL_Type_free(*datatype);
    free(*datatype);
    *datatype = &IMPL_DATATYPE_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_free_keyval(int *type_keyval)
{
    int rc = IMPL_Type_free_keyval(type_keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_attr(MPI_Datatype *datatype, int type_keyval, void *attribute_val, int *flag)
{
    int rc = IMPL_Type_get_attr(*datatype, type_keyval, attribute_val, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_contents(MPI_Datatype *datatype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], IMPL_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[])
{
    int rc = IMPL_Type_get_contents(*datatype, max_integers, max_addresses, max_datatypes, array_of_integers, array_of_addresses, array_of_datatypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_contents_c(MPI_Datatype *datatype, IMPL_Count max_integers, IMPL_Count max_addresses, IMPL_Count max_large_counts, IMPL_Count max_datatypes, int array_of_integers[], IMPL_Aint array_of_addresses[], IMPL_Count array_of_large_counts[], MPI_Datatype array_of_datatypes[])
{
    int rc = IMPL_Type_get_contents_c(*datatype, max_integers, max_addresses, max_large_counts, max_datatypes, array_of_integers, array_of_addresses, array_of_large_counts, array_of_datatypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_envelope(MPI_Datatype *datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner)
{
    int rc = IMPL_Type_get_envelope(*datatype, num_integers, num_addresses, num_datatypes, combiner);
    *combiner = COMBINER_CODE_IMPL_TO_MUK(*combiner);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_envelope_c(MPI_Datatype *datatype, IMPL_Count *num_integers, IMPL_Count *num_addresses, IMPL_Count *num_large_counts, IMPL_Count *num_datatypes, int *combiner)
{
    int rc = IMPL_Type_get_envelope_c(*datatype, num_integers, num_addresses, num_large_counts, num_datatypes, combiner);
    *combiner = COMBINER_CODE_IMPL_TO_MUK(*combiner);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_extent(MPI_Datatype *datatype, IMPL_Aint *lb, IMPL_Aint *extent)
{
    int rc = IMPL_Type_get_extent(*datatype, lb, extent);
    *lb     = UNDEFINED_IMPL_TO_MUK(*lb);
    *extent = UNDEFINED_IMPL_TO_MUK(*extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_extent_c(MPI_Datatype *datatype, IMPL_Count *lb, IMPL_Count *extent)
{
    int rc = IMPL_Type_get_extent_c(*datatype, lb, extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_extent_x(MPI_Datatype *datatype, IMPL_Count *lb, IMPL_Count *extent)
{
    int rc = IMPL_Type_get_extent_x(*datatype, lb, extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_name(MPI_Datatype *datatype, char *type_name, int *resultlen)
{
    int rc = IMPL_Type_get_name(*datatype, type_name, resultlen);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_true_extent(MPI_Datatype *datatype, IMPL_Aint *true_lb, IMPL_Aint *true_extent)
{
    int rc = IMPL_Type_get_true_extent(*datatype, true_lb, true_extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_true_extent_c(MPI_Datatype *datatype, IMPL_Count *true_lb, IMPL_Count *true_extent)
{
    int rc = IMPL_Type_get_true_extent_c(*datatype, true_lb, true_extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_true_extent_x(MPI_Datatype *datatype, IMPL_Count *true_lb, IMPL_Count *true_extent)
{
    int rc = IMPL_Type_get_true_extent_x(*datatype, true_lb, true_extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_hindexed(int count, int array_of_blocklengths[], IMPL_Aint array_of_displacements[], MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    int rc = IMPL_Type_hindexed(count, array_of_blocklengths, array_of_displacements, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_hvector(int count, int blocklength, IMPL_Aint stride, MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    int rc = IMPL_Type_hvector(count, blocklength, stride, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_indexed(int count, const int array_of_blocklengths[], const int array_of_displacements[], MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_indexed(count, array_of_blocklengths, array_of_displacements, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_indexed_c(IMPL_Count count, const IMPL_Count array_of_blocklengths[], const IMPL_Count array_of_displacements[], MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_indexed_c(count, array_of_blocklengths, array_of_displacements, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_lb(MPI_Datatype *datatype, IMPL_Aint *displacement)
{
    int rc = IMPL_Type_lb(*datatype, displacement);
    *displacement = UNDEFINED_IMPL_TO_MUK(*displacement);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_match_size(int typeclass, int size, MPI_Datatype **datatype)
{
    int rc = IMPL_Type_match_size(typeclass, size, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_set_attr(MPI_Datatype *datatype, int type_keyval, void *attribute_val)
{
    int rc = IMPL_Type_set_attr(*datatype, type_keyval, attribute_val);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_set_name(MPI_Datatype *datatype, const char *type_name)
{
    int rc = IMPL_Type_set_name(*datatype, type_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_size(MPI_Datatype *datatype, int *size)
{
    int rc = IMPL_Type_size(*datatype, size);
    *size = UNDEFINED_IMPL_TO_MUK(*size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_size_c(MPI_Datatype *datatype, IMPL_Count *size)
{
    int rc = IMPL_Type_size_c(*datatype, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_size_x(MPI_Datatype *datatype, IMPL_Count *size)
{
    int rc = IMPL_Type_size_x(*datatype, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_struct(int count, int array_of_blocklengths[], IMPL_Aint array_of_displacements[], MPI_Datatype array_of_types[], MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_struct(count, array_of_blocklengths, array_of_displacements, array_of_types, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_ub(MPI_Datatype *datatype, IMPL_Aint *displacement)
{
    int rc = IMPL_Type_ub(*datatype, displacement);
    *displacement = UNDEFINED_IMPL_TO_MUK(*displacement);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_vector(int count, int blocklength, int stride, MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_vector(count, blocklength, stride, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_vector_c(IMPL_Count count, IMPL_Count blocklength, IMPL_Count stride, MPI_Datatype *oldtype, MPI_Datatype **newtype)
{
    *newtype = malloc(sizeof(MPI_Datatype));
    int rc = IMPL_Type_vector_c(count, blocklength, stride, *oldtype, *newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype *datatype, MPI_Comm *comm)
{
    int rc = IMPL_Unpack(inbuf, insize, position, outbuf, outcount, *datatype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Unpack_c(const void *inbuf, IMPL_Count insize, IMPL_Count *position, void *outbuf, IMPL_Count outcount, MPI_Datatype *datatype, MPI_Comm *comm)
{
    int rc = IMPL_Unpack_c(inbuf, insize, position, outbuf, outcount, *datatype, *comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Unpack_external(const char datarep[], const void *inbuf, IMPL_Aint insize, IMPL_Aint *position, void *outbuf, int outcount, MPI_Datatype *datatype)
{
    int rc = IMPL_Unpack_external(datarep, inbuf, insize, position, outbuf, outcount, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Unpack_external_c(const char datarep[], const void *inbuf, IMPL_Count insize, IMPL_Count *position, void *outbuf, IMPL_Count outcount, MPI_Datatype *datatype)
{
    int rc = IMPL_Unpack_external_c(datarep, inbuf, insize, position, outbuf, outcount, *datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Unpublish_name(const char *service_name, MPI_Info *info, const char *port_name)
{
    int rc = IMPL_Unpublish_name(service_name, *info, port_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Wait(MPI_Request **request, WRAP_Status *status)
{
    const bool ignore = (intptr_t)status == (intptr_t)IMPL_STATUS_IGNORE;
    MPI_Status impl_status;

    int rc = IMPL_Wait(*request, ignore ? MPI_STATUS_IGNORE : &impl_status);

    if (**request == MPI_REQUEST_NULL) {
        free(*request);
        *request = &IMPL_REQUEST_NULL;
    }

    if (!ignore) {
        MPI_Status_to_WRAP_Status(&impl_status, status);
    }

    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Waitall(int count, MPI_Request* array_of_requests[], WRAP_Status array_of_statuses[])
{
    MPI_Request * impl_requests = malloc(count * sizeof(MPI_Request));
    if (impl_requests == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<count; i++) {
        impl_requests[i] = *array_of_requests[i];
    }

    const bool ignore = (intptr_t)array_of_statuses == (intptr_t)IMPL_STATUSES_IGNORE;
    MPI_Status * impl_statuses = NULL;
    if (!ignore) {
        impl_statuses  = malloc(count * sizeof(MPI_Status));
        if (impl_statuses == NULL) return MPI_ERR_INTERN;
    }

    int rc = IMPL_Waitall(count, impl_requests, ignore ? MPI_STATUSES_IGNORE : impl_statuses);

    // Active persistent requests are marked inactive. Requests of any other type are
    // deallocated and the corresponding handles in the array are set to MPI_REQUEST_NULL.
    // The list may contain null or inactive handles. The call sets to empty the status of each such entry.
    for (int i=0; i<count; i++) {
        if (impl_requests[i] == MPI_REQUEST_NULL) {
            free(array_of_requests[i]);
            array_of_requests[i] = &IMPL_REQUEST_NULL;
        }
    }
    free(impl_requests);

    if (!ignore) {
        for (int i=0; i<count; i++) {
            MPI_Status_to_WRAP_Status(&impl_statuses[i], &array_of_statuses[i]);
        }
        free(impl_statuses);
    }

    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Waitany(int count, MPI_Request* array_of_requests[], int *indx, WRAP_Status *status)
{
    MPI_Request * impl_requests = malloc(count * sizeof(MPI_Request));
    if (impl_requests == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<count; i++) {
        impl_requests[i] = *array_of_requests[i];
    }

    const bool ignore = (intptr_t)status == (intptr_t)IMPL_STATUS_IGNORE;
    MPI_Status impl_status;

    int rc = IMPL_Waitany(count, impl_requests, indx, ignore ? MPI_STATUS_IGNORE : &impl_status);

    // If the list contains no active handles (list has length zero or all entries are null or inactive), then the call returns
    // immediately with index = MPI_UNDEFINED, and an empty status.
    if (*indx != MPI_UNDEFINED) {

        if (impl_requests[*indx] == MPI_REQUEST_NULL) {
            free(array_of_requests[*indx]);
            array_of_requests[*indx] = &IMPL_REQUEST_NULL;
        }

        if (!ignore) {
            MPI_Status_to_WRAP_Status(&impl_status, status);
        }
    }

    free(impl_requests);

    *indx = UNDEFINED_IMPL_TO_MUK(*indx);

    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Waitsome(int incount, MPI_Request* array_of_requests[], int *outcount, int array_of_indices[], WRAP_Status array_of_statuses[])
{
    MPI_Request * impl_requests = malloc(incount * sizeof(MPI_Request));
    if (impl_requests == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<incount; i++) {
        impl_requests[i] = *array_of_requests[i];
    }

    const bool ignore = (intptr_t)array_of_statuses == (intptr_t)IMPL_STATUSES_IGNORE;
    MPI_Status * impl_statuses = NULL;
    if (!ignore) {
        impl_statuses = malloc(incount * sizeof(MPI_Status));
        if (impl_statuses == NULL) return MPI_ERR_INTERN;
    }

    int rc = IMPL_Waitsome(incount, impl_requests, outcount, array_of_indices, ignore ? MPI_STATUSES_IGNORE : impl_statuses);

    if ((*outcount > 0) && (*outcount != MPI_UNDEFINED)) {

        for (int i=0; i<*outcount; i++) {
            const int j = array_of_indices[i];
            if (impl_requests[j] == MPI_REQUEST_NULL) {
                free(array_of_requests[j]);
                array_of_requests[j] = &IMPL_REQUEST_NULL;
            }
        }

        if (!ignore) {
            for (int i=0; i<incount; i++) {
                const int j = array_of_indices[i];
                MPI_Status_to_WRAP_Status(&impl_statuses[j], &array_of_statuses[j]);
            }
            free(impl_statuses);
        }
    }

    if (!ignore) {
        free(impl_statuses);
    }

    free(impl_requests);

    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_allocate(IMPL_Aint size, int disp_unit, MPI_Info *info, MPI_Comm *comm, void *baseptr, MPI_Win **win)
{
    *win = malloc(sizeof(MPI_Win));
    int rc = IMPL_Win_allocate(size, disp_unit, *info, *comm, baseptr, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_allocate_c(IMPL_Aint size, IMPL_Aint disp_unit, MPI_Info *info, MPI_Comm *comm, void *baseptr, MPI_Win **win)
{
    *win = malloc(sizeof(MPI_Win));
    int rc = IMPL_Win_allocate_c(size, disp_unit, *info, *comm, baseptr, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_allocate_shared(IMPL_Aint size, int disp_unit, MPI_Info *info, MPI_Comm *comm, void *baseptr, MPI_Win **win)
{
    *win = malloc(sizeof(MPI_Win));
    int rc = IMPL_Win_allocate_shared(size, disp_unit, *info, *comm, baseptr, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_allocate_shared_c(IMPL_Aint size, IMPL_Aint disp_unit, MPI_Info *info, MPI_Comm *comm, void *baseptr, MPI_Win **win)
{
    *win = malloc(sizeof(MPI_Win));
    int rc = IMPL_Win_allocate_shared_c(size, disp_unit, *info, *comm, baseptr, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_attach(MPI_Win *win, void *base, IMPL_Aint size)
{
    int rc = IMPL_Win_attach(*win, base, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_call_errhandler(MPI_Win *win, int errorcode)
{
    int rc = IMPL_Win_call_errhandler(*win, errorcode);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_complete(MPI_Win *win)
{
    int rc = IMPL_Win_complete(*win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_create(void *base, IMPL_Aint size, int disp_unit, MPI_Info *info, MPI_Comm *comm, MPI_Win **win)
{
    *win = malloc(sizeof(MPI_Win));
    int rc = IMPL_Win_create(base, size, disp_unit, *info, *comm, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_create_c(void *base, IMPL_Aint size, IMPL_Aint disp_unit, MPI_Info *info, MPI_Comm *comm, MPI_Win **win)
{
    *win = malloc(sizeof(MPI_Win));
    int rc = IMPL_Win_create_c(base, size, disp_unit, *info, *comm, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_create_dynamic(MPI_Info *info, MPI_Comm *comm, MPI_Win **win)
{
    *win = malloc(sizeof(MPI_Win));
    int rc = IMPL_Win_create_dynamic(*info, *comm, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_create_errhandler(MPI_Win_errhandler_function *win_errhandler_fn, MPI_Errhandler **errhandler)
{
    *errhandler = malloc(sizeof(MPI_Errhandler));
    int rc = IMPL_Win_create_errhandler(win_errhandler_fn, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_create_keyval(MPI_Win_copy_attr_function *win_copy_attr_fn, MPI_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state)
{
    int rc = IMPL_Win_create_keyval(win_copy_attr_fn, win_delete_attr_fn, win_keyval, extra_state);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_delete_attr(MPI_Win *win, int win_keyval)
{
    int rc = IMPL_Win_delete_attr(*win, win_keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_detach(MPI_Win *win, const void *base)
{
    int rc = IMPL_Win_detach(*win, base);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_fence(int assert, MPI_Win *win)
{
    //MUK_Warning("assert = %d %d\n", assert, MODE_MUK_TO_IMPL(assert));
    int rc = IMPL_Win_fence(MODE_MUK_TO_IMPL(assert), *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_flush(int rank, MPI_Win *win)
{
    int rc = IMPL_Win_flush(rank, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_flush_all(MPI_Win *win)
{
    int rc = IMPL_Win_flush_all(*win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_flush_local(int rank, MPI_Win *win)
{
    int rc = IMPL_Win_flush_local(rank, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_flush_local_all(MPI_Win *win)
{
    int rc = IMPL_Win_flush_local_all(*win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_free(MPI_Win **win)
{
    int rc = IMPL_Win_free(*win);
    free(*win);
    *win = &IMPL_WIN_NULL;
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_free_keyval(int *win_keyval)
{
    int rc = IMPL_Win_free_keyval(win_keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_get_attr(MPI_Win *win, int win_keyval, void *attribute_val, int *flag)
{
    int rc = IMPL_Win_get_attr(*win, KEY_MUK_TO_IMPL(win_keyval), attribute_val, flag);

    // this is the only place this is needed, so we inline it
    if (**(int**)attribute_val == MPI_WIN_SEPARATE) {
        **(int**)attribute_val = MUK_WIN_SEPARATE;
    } else if (**(int**)attribute_val == MPI_WIN_UNIFIED) {
        **(int**)attribute_val = MUK_WIN_UNIFIED;
    }

    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_get_errhandler(MPI_Win *win, MPI_Errhandler **errhandler)
{
    *errhandler = malloc(sizeof(MPI_Errhandler));
    int rc = IMPL_Win_get_errhandler(*win, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_get_group(MPI_Win *win, MPI_Group **group)
{
    *group = malloc(sizeof(MPI_Group));
    int rc = IMPL_Win_get_group(*win, *group);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_get_info(MPI_Win *win, MPI_Info *info_used)
{
    int rc = IMPL_Win_get_info(*win, info_used);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_get_name(MPI_Win *win, char *win_name, int *resultlen)
{
    int rc = IMPL_Win_get_name(*win, win_name, resultlen);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_lock(int lock_type, int rank, int assert, MPI_Win *win)
{
    // this is the only place this is used so we inline it
    int impl_type = MPI_UNDEFINED;
    if (lock_type == MUK_LOCK_EXCLUSIVE) {
        impl_type = MPI_LOCK_EXCLUSIVE;
    } else if (lock_type == MUK_LOCK_SHARED) {
        impl_type = MPI_LOCK_SHARED;
    }
    int rc = IMPL_Win_lock(impl_type, rank, MODE_MUK_TO_IMPL(assert), *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_lock_all(int assert, MPI_Win *win)
{
    int rc = IMPL_Win_lock_all(MODE_MUK_TO_IMPL(assert), *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_post(MPI_Group *group, int assert, MPI_Win *win)
{
    int rc = IMPL_Win_post(*group, MODE_MUK_TO_IMPL(assert), *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_set_attr(MPI_Win *win, int win_keyval, void *attribute_val)
{
    int rc = IMPL_Win_set_attr(*win, win_keyval, attribute_val);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_set_errhandler(MPI_Win *win, MPI_Errhandler *errhandler)
{
    int rc = IMPL_Win_set_errhandler(*win, *errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_set_info(MPI_Win *win, MPI_Info *info)
{
    int rc = IMPL_Win_set_info(*win, *info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_set_name(MPI_Win *win, const char *win_name)
{
    int rc = IMPL_Win_set_name(*win, win_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_shared_query(MPI_Win *win, int rank, IMPL_Aint *size, int *disp_unit, void *baseptr)
{
    int rc = IMPL_Win_shared_query(*win, rank, size, disp_unit, baseptr);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_shared_query_c(MPI_Win *win, int rank, IMPL_Aint *size, IMPL_Aint *disp_unit, void *baseptr)
{
    int rc = IMPL_Win_shared_query_c(*win, rank, size, disp_unit, baseptr);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_start(MPI_Group *group, int assert, MPI_Win *win)
{
    int rc = IMPL_Win_start(*group, MODE_MUK_TO_IMPL(assert), *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_sync(MPI_Win *win)
{
    int rc = IMPL_Win_sync(*win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_test(MPI_Win *win, int *flag)
{
    int rc = IMPL_Win_test(*win, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_unlock(int rank, MPI_Win *win)
{
    int rc = IMPL_Win_unlock(rank, *win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_unlock_all(MPI_Win *win)
{
    int rc = IMPL_Win_unlock_all(*win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_wait(MPI_Win *win)
{
    int rc = IMPL_Win_wait(*win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

static int ALLTOALLW_SETUP(const MPI_Comm * comm, const MPI_Datatype* sendtypes[], const MPI_Datatype* recvtypes[],
                           MPI_Datatype* *impl_sendtypes, MPI_Datatype* *impl_recvtypes)
{
    int np;
    int rc = IMPL_Comm_size(*comm,&np);
    if (rc != MPI_SUCCESS) {
        return MPI_ERR_INTERN;
    }
    *impl_sendtypes = malloc(np * sizeof(MPI_Datatype));
    if (impl_sendtypes == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<np; i++) {
        (*impl_sendtypes)[i] = *(sendtypes[i]);
    }
    *impl_recvtypes = malloc(np * sizeof(MPI_Datatype));
    if (impl_recvtypes == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<np; i++) {
        (*impl_recvtypes)[i] = *(recvtypes[i]);
    }
    return MPI_SUCCESS;
}

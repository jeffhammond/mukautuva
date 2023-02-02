#include "muk-dl.h"

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
    IMPL_Abort = MUK_DLSYM(h, NIMI(Abort) );
    IMPL_Comm_rank = MUK_DLSYM(h, NIMI(Comm_rank) );
    IMPL_Comm_size = MUK_DLSYM(h, NIMI(Comm_size) );
    return 0;
}

// status conversion

#include <string.h>

static inline void WRAP_Status_to_MPI_Status(const WRAP_Status * w, MPI_Status * m)
{
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

int WRAP_Abort(MPI_Comm * comm, int errorcode)
{
    return IMPL_Abort(*comm, errorcode);
}

int WRAP_Comm_rank(MPI_Comm * comm, int * rank)
{
    return IMPL_Comm_rank(*comm, rank);
}

int WRAP_Comm_size(MPI_Comm * comm, int * size)
{
    return IMPL_Comm_size(*comm, size);
}

int WRAP_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win)
{
    return IMPL_Accumulate(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
}

int WRAP_Accumulate_c(const void *origin_addr, IMPL_Count origin_count, MPI_Datatype origin_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win)
{
    return IMPL_Accumulate_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
}

int WRAP_Add_error_class(int *errorclass)
{
    return IMPL_Add_error_class(errorclass);
}

int WRAP_Add_error_code(int errorclass, int *errorcode)
{
    return IMPL_Add_error_code(errorclass, errorcode);
}

int WRAP_Add_error_string(int errorcode, const char *string)
{
    return IMPL_Add_error_string(errorcode, string);
}

int WRAP_Address(void *location, IMPL_Aint *address)
{
    return IMPL_Address(location, address);
}

MPI_Aint WRAP_Aint_add(IMPL_Aint base, IMPL_Aint disp)
{
    return IMPL_Aint_add(base, disp);
}

MPI_Aint WRAP_Aint_diff(IMPL_Aint addr1, IMPL_Aint addr2)
{
    return IMPL_Aint_diff(addr1, addr2);
}

int WRAP_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int WRAP_Allgather_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Allgather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int WRAP_Allgather_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Allgather_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int WRAP_Allgather_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Allgather_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int WRAP_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
}

int WRAP_Allgatherv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Allgatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
}

int WRAP_Allgatherv_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Allgatherv_init(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, info, request);
}

int WRAP_Allgatherv_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Allgatherv_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, info, request);
}

int WRAP_Alloc_mem(IMPL_Aint size, MPI_Info info, void *baseptr)
{
    return IMPL_Alloc_mem(size, info, baseptr);
}

int WRAP_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return IMPL_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);
}

int WRAP_Allreduce_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return IMPL_Allreduce_c(sendbuf, recvbuf, count, datatype, op, comm);
}

int WRAP_Allreduce_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Allreduce_init(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int WRAP_Allreduce_init_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Allreduce_init_c(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int WRAP_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int WRAP_Alltoall_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Alltoall_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int WRAP_Alltoall_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Alltoall_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int WRAP_Alltoall_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Alltoall_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int WRAP_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}

int WRAP_Alltoallv_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Alltoallv_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}

int WRAP_Alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Alltoallv_init(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, info, request);
}

int WRAP_Alltoallv_init_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Alltoallv_init_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, info, request);
}

int WRAP_Alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm)
{
    return IMPL_Alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
}

int WRAP_Alltoallw_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm)
{
    return IMPL_Alltoallw_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
}

int WRAP_Alltoallw_init(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Alltoallw_init(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, info, request);
}

int WRAP_Alltoallw_init_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Alltoallw_init_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, info, request);
}

int WRAP_Attr_delete(MPI_Comm comm, int keyval)
{
    return IMPL_Attr_delete(comm, keyval);
}

int WRAP_Attr_get(MPI_Comm comm, int keyval, void *attribute_val, int *flag)
{
    return IMPL_Attr_get(comm, keyval, attribute_val, flag);
}

int WRAP_Attr_put(MPI_Comm comm, int keyval, void *attribute_val)
{
    return IMPL_Attr_put(comm, keyval, attribute_val);
}

int WRAP_Barrier(MPI_Comm comm)
{
    return IMPL_Barrier(comm);
}

int WRAP_Barrier_init(MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Barrier_init(comm, info, request);
}

int WRAP_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
{
    return IMPL_Bcast(buffer, count, datatype, root, comm);
}

int WRAP_Bcast_c(void *buffer, IMPL_Count count, MPI_Datatype datatype, int root, MPI_Comm comm)
{
    return IMPL_Bcast_c(buffer, count, datatype, root, comm);
}

int WRAP_Bcast_init(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Bcast_init(buffer, count, datatype, root, comm, info, request);
}

int WRAP_Bcast_init_c(void *buffer, IMPL_Count count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Bcast_init_c(buffer, count, datatype, root, comm, info, request);
}

int WRAP_Bsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return IMPL_Bsend(buf, count, datatype, dest, tag, comm);
}

int WRAP_Bsend_c(const void *buf, IMPL_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return IMPL_Bsend_c(buf, count, datatype, dest, tag, comm);
}

int WRAP_Bsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Bsend_init(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Bsend_init_c(const void *buf, IMPL_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Bsend_init_c(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Buffer_attach(void *buffer, int size)
{
    return IMPL_Buffer_attach(buffer, size);
}

int WRAP_Buffer_attach_c(void *buffer, IMPL_Count size)
{
    return IMPL_Buffer_attach_c(buffer, size);
}

int WRAP_Buffer_detach(void *buffer_addr, int *size)
{
    return IMPL_Buffer_detach(buffer_addr, size);
}

int WRAP_Buffer_detach_c(void *buffer_addr, IMPL_Count *size)
{
    return IMPL_Buffer_detach_c(buffer_addr, size);
}

int WRAP_Cancel(MPI_Request *request)
{
    return IMPL_Cancel(request);
}

int WRAP_Cart_coords(MPI_Comm comm, int rank, int maxdims, int coords[])
{
    return IMPL_Cart_coords(comm, rank, maxdims, coords);
}

int WRAP_Cart_create(MPI_Comm comm_old, int ndims, const int dims[], const int periods[], int reorder, MPI_Comm *comm_cart)
{
    return IMPL_Cart_create(comm_old, ndims, dims, periods, reorder, comm_cart);
}

int WRAP_Cart_get(MPI_Comm comm, int maxdims, int dims[], int periods[], int coords[])
{
    return IMPL_Cart_get(comm, maxdims, dims, periods, coords);
}

int WRAP_Cart_map(MPI_Comm comm, int ndims, const int dims[], const int periods[], int *newrank)
{
    return IMPL_Cart_map(comm, ndims, dims, periods, newrank);
}

int WRAP_Cart_rank(MPI_Comm comm, const int coords[], int *rank)
{
    return IMPL_Cart_rank(comm, coords, rank);
}

int WRAP_Cart_shift(MPI_Comm comm, int direction, int disp, int *rank_source, int *rank_dest)
{
    return IMPL_Cart_shift(comm, direction, disp, rank_source, rank_dest);
}

int WRAP_Cart_sub(MPI_Comm comm, const int remain_dims[], MPI_Comm *newcomm)
{
    return IMPL_Cart_sub(comm, remain_dims, newcomm);
}

int WRAP_Cartdim_get(MPI_Comm comm, int *ndims)
{
    return IMPL_Cartdim_get(comm, ndims);
}

int WRAP_Close_port(const char *port_name)
{
    return IMPL_Close_port(port_name);
}

int WRAP_Comm_accept(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm)
{
    return IMPL_Comm_accept(port_name, info, root, comm, newcomm);
}

int WRAP_Comm_call_errhandler(MPI_Comm comm, int errorcode)
{
    return IMPL_Comm_call_errhandler(comm, errorcode);
}

int WRAP_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result)
{
    return IMPL_Comm_compare(comm1, comm2, result);
}

int WRAP_Comm_connect(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm)
{
    return IMPL_Comm_connect(port_name, info, root, comm, newcomm);
}

int WRAP_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm)
{
    return IMPL_Comm_create(comm, group, newcomm);
}

int WRAP_Comm_create_errhandler(MPI_Comm_errhandler_function *comm_errhandler_fn, MPI_Errhandler *errhandler)
{
    return IMPL_Comm_create_errhandler(comm_errhandler_fn, errhandler);
}

int WRAP_Comm_create_from_group(MPI_Group group, const char *stringtag, MPI_Info info, MPI_Errhandler errhandler, MPI_Comm *newcomm)
{
    return IMPL_Comm_create_from_group(group, stringtag, info, errhandler, newcomm);
}

int WRAP_Comm_create_group(MPI_Comm comm, MPI_Group group, int tag, MPI_Comm *newcomm)
{
    return IMPL_Comm_create_group(comm, group, tag, newcomm);
}

int WRAP_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state)
{
    return IMPL_Comm_create_keyval(comm_copy_attr_fn, comm_delete_attr_fn, comm_keyval, extra_state);
}

int WRAP_Comm_delete_attr(MPI_Comm comm, int comm_keyval)
{
    return IMPL_Comm_delete_attr(comm, comm_keyval);
}

int WRAP_Comm_disconnect(MPI_Comm *comm)
{
    return IMPL_Comm_disconnect(comm);
}

int WRAP_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm)
{
    return IMPL_Comm_dup(comm, newcomm);
}

int WRAP_Comm_dup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm)
{
    return IMPL_Comm_dup_with_info(comm, info, newcomm);
}

int WRAP_Comm_free(MPI_Comm *comm)
{
    return IMPL_Comm_free(comm);
}

int WRAP_Comm_free_keyval(int *comm_keyval)
{
    return IMPL_Comm_free_keyval(comm_keyval);
}

int WRAP_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag)
{
    return IMPL_Comm_get_attr(comm, comm_keyval, attribute_val, flag);
}

int WRAP_Comm_get_errhandler(MPI_Comm comm, MPI_Errhandler *errhandler)
{
    return IMPL_Comm_get_errhandler(comm, errhandler);
}

int WRAP_Comm_get_info(MPI_Comm comm, MPI_Info *info_used)
{
    return IMPL_Comm_get_info(comm, info_used);
}

int WRAP_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen)
{
    return IMPL_Comm_get_name(comm, comm_name, resultlen);
}

int WRAP_Comm_get_parent(MPI_Comm *parent)
{
    return IMPL_Comm_get_parent(parent);
}

int WRAP_Comm_group(MPI_Comm comm, MPI_Group *group)
{
    return IMPL_Comm_group(comm, group);
}

int WRAP_Comm_idup(MPI_Comm comm, MPI_Comm *newcomm, MPI_Request *request)
{
    return IMPL_Comm_idup(comm, newcomm, request);
}

int WRAP_Comm_idup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm, MPI_Request *request)
{
    return IMPL_Comm_idup_with_info(comm, info, newcomm, request);
}

int WRAP_Comm_join(int fd, MPI_Comm *intercomm)
{
    return IMPL_Comm_join(fd, intercomm);
}

int WRAP_Comm_remote_group(MPI_Comm comm, MPI_Group *group)
{
    return IMPL_Comm_remote_group(comm, group);
}

int WRAP_Comm_remote_size(MPI_Comm comm, int *size)
{
    return IMPL_Comm_remote_size(comm, size);
}

int WRAP_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val)
{
    return IMPL_Comm_set_attr(comm, comm_keyval, attribute_val);
}

int WRAP_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler)
{
    return IMPL_Comm_set_errhandler(comm, errhandler);
}

int WRAP_Comm_set_info(MPI_Comm comm, MPI_Info info)
{
    return IMPL_Comm_set_info(comm, info);
}

int WRAP_Comm_set_name(MPI_Comm comm, const char *comm_name)
{
    return IMPL_Comm_set_name(comm, comm_name);
}

int WRAP_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm)
{
    return IMPL_Comm_split(comm, color, key, newcomm);
}

int WRAP_Comm_split_type(MPI_Comm comm, int split_type, int key, MPI_Info info, MPI_Comm *newcomm)
{
    return IMPL_Comm_split_type(comm, split_type, key, info, newcomm);
}

int WRAP_Comm_test_inter(MPI_Comm comm, int *flag)
{
    return IMPL_Comm_test_inter(comm, flag);
}

int WRAP_Compare_and_swap(const void *origin_addr, const void *compare_addr, void *result_addr, MPI_Datatype datatype, int target_rank, IMPL_Aint target_disp, MPI_Win win)
{
    return IMPL_Compare_and_swap(origin_addr, compare_addr, result_addr, datatype, target_rank, target_disp, win);
}

int WRAP_Dims_create(int nnodes, int ndims, int dims[])
{
    return IMPL_Dims_create(nnodes, ndims, dims);
}

int WRAP_Dist_graph_create(MPI_Comm comm_old, int n, const int sources[], const int degrees[], const int destinations[], const int weights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph)
{
    return IMPL_Dist_graph_create(comm_old, n, sources, degrees, destinations, weights, info, reorder, comm_dist_graph);
}

int WRAP_Dist_graph_create_adjacent(MPI_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph)
{
    return IMPL_Dist_graph_create_adjacent(comm_old, indegree, sources, sourceweights, outdegree, destinations, destweights, info, reorder, comm_dist_graph);
}

int WRAP_Dist_graph_neighbors(MPI_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[])
{
    return IMPL_Dist_graph_neighbors(comm, maxindegree, sources, sourceweights, maxoutdegree, destinations, destweights);
}

int WRAP_Dist_graph_neighbors_count(MPI_Comm comm, int *indegree, int *outdegree, int *weighted)
{
    return IMPL_Dist_graph_neighbors_count(comm, indegree, outdegree, weighted);
}

int WRAP_Errhandler_create(MPI_Comm_errhandler_function *comm_errhandler_fn, MPI_Errhandler *errhandler)
{
    return IMPL_Errhandler_create(comm_errhandler_fn, errhandler);
}

int WRAP_Errhandler_free(MPI_Errhandler *errhandler)
{
    return IMPL_Errhandler_free(errhandler);
}

int WRAP_Errhandler_get(MPI_Comm comm, MPI_Errhandler *errhandler)
{
    return IMPL_Errhandler_get(comm, errhandler);
}

int WRAP_Errhandler_set(MPI_Comm comm, MPI_Errhandler errhandler)
{
    return IMPL_Errhandler_set(comm, errhandler);
}

int WRAP_Error_class(int errorcode, int *errorclass)
{
    return IMPL_Error_class(errorcode, errorclass);
}

int WRAP_Error_string(int errorcode, char *string, int *resultlen)
{
    return IMPL_Error_string(errorcode, string, resultlen);
}

int WRAP_Exscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return IMPL_Exscan(sendbuf, recvbuf, count, datatype, op, comm);
}

int WRAP_Exscan_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return IMPL_Exscan_c(sendbuf, recvbuf, count, datatype, op, comm);
}

int WRAP_Exscan_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Exscan_init(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int WRAP_Exscan_init_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Exscan_init_c(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int WRAP_Fetch_and_op(const void *origin_addr, void *result_addr, MPI_Datatype datatype, int target_rank, IMPL_Aint target_disp, MPI_Op op, MPI_Win win)
{
    return IMPL_Fetch_and_op(origin_addr, result_addr, datatype, target_rank, target_disp, op, win);
}

int WRAP_File_call_errhandler(MPI_File fh, int errorcode)
{
    return IMPL_File_call_errhandler(fh, errorcode);
}

int WRAP_File_close(MPI_File *fh)
{
    return IMPL_File_close(fh);
}

int WRAP_File_create_errhandler(MPI_File_errhandler_function *file_errhandler_fn, MPI_Errhandler *errhandler)
{
    return IMPL_File_create_errhandler(file_errhandler_fn, errhandler);
}

int WRAP_File_delete(const char *filename, MPI_Info info)
{
    return IMPL_File_delete(filename, info);
}

int WRAP_File_get_amode(MPI_File fh, int *amode)
{
    return IMPL_File_get_amode(fh, amode);
}

int WRAP_File_get_atomicity(MPI_File fh, int *flag)
{
    return IMPL_File_get_atomicity(fh, flag);
}

int WRAP_File_get_byte_offset(MPI_File fh, IMPL_Offset offset, IMPL_Offset *disp)
{
    return IMPL_File_get_byte_offset(fh, offset, disp);
}

int WRAP_File_get_errhandler(MPI_File file, MPI_Errhandler *errhandler)
{
    return IMPL_File_get_errhandler(file, errhandler);
}

int WRAP_File_get_group(MPI_File fh, MPI_Group *group)
{
    return IMPL_File_get_group(fh, group);
}

int WRAP_File_get_info(MPI_File fh, MPI_Info *info_used)
{
    return IMPL_File_get_info(fh, info_used);
}

int WRAP_File_get_position(MPI_File fh, IMPL_Offset *offset)
{
    return IMPL_File_get_position(fh, offset);
}

int WRAP_File_get_position_shared(MPI_File fh, IMPL_Offset *offset)
{
    return IMPL_File_get_position_shared(fh, offset);
}

int WRAP_File_get_size(MPI_File fh, IMPL_Offset *size)
{
    return IMPL_File_get_size(fh, size);
}

int WRAP_File_get_type_extent(MPI_File fh, MPI_Datatype datatype, IMPL_Aint *extent)
{
    return IMPL_File_get_type_extent(fh, datatype, extent);
}

int WRAP_File_get_type_extent_c(MPI_File fh, MPI_Datatype datatype, IMPL_Count *extent)
{
    return IMPL_File_get_type_extent_c(fh, datatype, extent);
}

int WRAP_File_get_view(MPI_File fh, IMPL_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep)
{
    return IMPL_File_get_view(fh, disp, etype, filetype, datarep);
}

int WRAP_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iread(fh, buf, count, datatype, request);
}

int WRAP_File_iread_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iread_all(fh, buf, count, datatype, request);
}

int WRAP_File_iread_all_c(MPI_File fh, void *buf, IMPL_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iread_all_c(fh, buf, count, datatype, request);
}

int WRAP_File_iread_at(MPI_File fh, IMPL_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iread_at(fh, offset, buf, count, datatype, request);
}

int WRAP_File_iread_at_all(MPI_File fh, IMPL_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iread_at_all(fh, offset, buf, count, datatype, request);
}

int WRAP_File_iread_at_all_c(MPI_File fh, IMPL_Offset offset, void *buf, IMPL_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iread_at_all_c(fh, offset, buf, count, datatype, request);
}

int WRAP_File_iread_at_c(MPI_File fh, IMPL_Offset offset, void *buf, IMPL_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iread_at_c(fh, offset, buf, count, datatype, request);
}

int WRAP_File_iread_c(MPI_File fh, void *buf, IMPL_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iread_c(fh, buf, count, datatype, request);
}

int WRAP_File_iread_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iread_shared(fh, buf, count, datatype, request);
}

int WRAP_File_iread_shared_c(MPI_File fh, void *buf, IMPL_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iread_shared_c(fh, buf, count, datatype, request);
}

int WRAP_File_iwrite(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iwrite(fh, buf, count, datatype, request);
}

int WRAP_File_iwrite_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iwrite_all(fh, buf, count, datatype, request);
}

int WRAP_File_iwrite_all_c(MPI_File fh, const void *buf, IMPL_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iwrite_all_c(fh, buf, count, datatype, request);
}

int WRAP_File_iwrite_at(MPI_File fh, IMPL_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iwrite_at(fh, offset, buf, count, datatype, request);
}

int WRAP_File_iwrite_at_all(MPI_File fh, IMPL_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iwrite_at_all(fh, offset, buf, count, datatype, request);
}

int WRAP_File_iwrite_at_all_c(MPI_File fh, IMPL_Offset offset, const void *buf, IMPL_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iwrite_at_all_c(fh, offset, buf, count, datatype, request);
}

int WRAP_File_iwrite_at_c(MPI_File fh, IMPL_Offset offset, const void *buf, IMPL_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iwrite_at_c(fh, offset, buf, count, datatype, request);
}

int WRAP_File_iwrite_c(MPI_File fh, const void *buf, IMPL_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iwrite_c(fh, buf, count, datatype, request);
}

int WRAP_File_iwrite_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iwrite_shared(fh, buf, count, datatype, request);
}

int WRAP_File_iwrite_shared_c(MPI_File fh, const void *buf, IMPL_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return IMPL_File_iwrite_shared_c(fh, buf, count, datatype, request);
}

int WRAP_File_open(MPI_Comm comm, const char *filename, int amode, MPI_Info info, MPI_File *fh)
{
    return IMPL_File_open(comm, filename, amode, info, fh);
}

int WRAP_File_preallocate(MPI_File fh, IMPL_Offset size)
{
    return IMPL_File_preallocate(fh, size);
}

int WRAP_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_all(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_read_all_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype)
{
    return IMPL_File_read_all_begin(fh, buf, count, datatype);
}

int WRAP_File_read_all_begin_c(MPI_File fh, void *buf, IMPL_Count count, MPI_Datatype datatype)
{
    return IMPL_File_read_all_begin_c(fh, buf, count, datatype);
}

int WRAP_File_read_all_c(MPI_File fh, void *buf, IMPL_Count count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_all_c(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_read_all_end(MPI_File fh, void *buf, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_all_end(fh, buf, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_read_at(MPI_File fh, IMPL_Offset offset, void *buf, int count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_at(fh, offset, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_read_at_all(MPI_File fh, IMPL_Offset offset, void *buf, int count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_at_all(fh, offset, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_read_at_all_begin(MPI_File fh, IMPL_Offset offset, void *buf, int count, MPI_Datatype datatype)
{
    return IMPL_File_read_at_all_begin(fh, offset, buf, count, datatype);
}

int WRAP_File_read_at_all_begin_c(MPI_File fh, IMPL_Offset offset, void *buf, IMPL_Count count, MPI_Datatype datatype)
{
    return IMPL_File_read_at_all_begin_c(fh, offset, buf, count, datatype);
}

int WRAP_File_read_at_all_c(MPI_File fh, IMPL_Offset offset, void *buf, IMPL_Count count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_at_all_c(fh, offset, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_read_at_all_end(MPI_File fh, void *buf, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_at_all_end(fh, buf, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_read_at_c(MPI_File fh, IMPL_Offset offset, void *buf, IMPL_Count count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_at_c(fh, offset, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_read_c(MPI_File fh, void *buf, IMPL_Count count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_c(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_read_ordered(MPI_File fh, void *buf, int count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_ordered(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_read_ordered_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype)
{
    return IMPL_File_read_ordered_begin(fh, buf, count, datatype);
}

int WRAP_File_read_ordered_begin_c(MPI_File fh, void *buf, IMPL_Count count, MPI_Datatype datatype)
{
    return IMPL_File_read_ordered_begin_c(fh, buf, count, datatype);
}

int WRAP_File_read_ordered_c(MPI_File fh, void *buf, IMPL_Count count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_ordered_c(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_read_ordered_end(MPI_File fh, void *buf, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_ordered_end(fh, buf, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_read_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_shared(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_read_shared_c(MPI_File fh, void *buf, IMPL_Count count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_read_shared_c(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_seek(MPI_File fh, IMPL_Offset offset, int whence)
{
    return IMPL_File_seek(fh, offset, whence);
}

int WRAP_File_seek_shared(MPI_File fh, IMPL_Offset offset, int whence)
{
    return IMPL_File_seek_shared(fh, offset, whence);
}

int WRAP_File_set_atomicity(MPI_File fh, int flag)
{
    return IMPL_File_set_atomicity(fh, flag);
}

int WRAP_File_set_errhandler(MPI_File file, MPI_Errhandler errhandler)
{
    return IMPL_File_set_errhandler(file, errhandler);
}

int WRAP_File_set_info(MPI_File fh, MPI_Info info)
{
    return IMPL_File_set_info(fh, info);
}

int WRAP_File_set_size(MPI_File fh, IMPL_Offset size)
{
    return IMPL_File_set_size(fh, size);
}

int WRAP_File_set_view(MPI_File fh, IMPL_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char *datarep, MPI_Info info)
{
    return IMPL_File_set_view(fh, disp, etype, filetype, datarep, info);
}

int WRAP_File_sync(MPI_File fh)
{
    return IMPL_File_sync(fh);
}

int WRAP_File_write(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_write_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_all(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_write_all_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype)
{
    return IMPL_File_write_all_begin(fh, buf, count, datatype);
}

int WRAP_File_write_all_begin_c(MPI_File fh, const void *buf, IMPL_Count count, MPI_Datatype datatype)
{
    return IMPL_File_write_all_begin_c(fh, buf, count, datatype);
}

int WRAP_File_write_all_c(MPI_File fh, const void *buf, IMPL_Count count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_all_c(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_write_all_end(MPI_File fh, const void *buf, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_all_end(fh, buf, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_write_at(MPI_File fh, IMPL_Offset offset, const void *buf, int count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_at(fh, offset, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_write_at_all(MPI_File fh, IMPL_Offset offset, const void *buf, int count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_at_all(fh, offset, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_write_at_all_begin(MPI_File fh, IMPL_Offset offset, const void *buf, int count, MPI_Datatype datatype)
{
    return IMPL_File_write_at_all_begin(fh, offset, buf, count, datatype);
}

int WRAP_File_write_at_all_begin_c(MPI_File fh, IMPL_Offset offset, const void *buf, IMPL_Count count, MPI_Datatype datatype)
{
    return IMPL_File_write_at_all_begin_c(fh, offset, buf, count, datatype);
}

int WRAP_File_write_at_all_c(MPI_File fh, IMPL_Offset offset, const void *buf, IMPL_Count count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_at_all_c(fh, offset, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_write_at_all_end(MPI_File fh, const void *buf, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_at_all_end(fh, buf, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_write_at_c(MPI_File fh, IMPL_Offset offset, const void *buf, IMPL_Count count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_at_c(fh, offset, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_write_c(MPI_File fh, const void *buf, IMPL_Count count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_c(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_write_ordered(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_ordered(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_write_ordered_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype)
{
    return IMPL_File_write_ordered_begin(fh, buf, count, datatype);
}

int WRAP_File_write_ordered_begin_c(MPI_File fh, const void *buf, IMPL_Count count, MPI_Datatype datatype)
{
    return IMPL_File_write_ordered_begin_c(fh, buf, count, datatype);
}

int WRAP_File_write_ordered_c(MPI_File fh, const void *buf, IMPL_Count count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_ordered_c(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_write_ordered_end(MPI_File fh, const void *buf, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_ordered_end(fh, buf, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_write_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_shared(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_File_write_shared_c(MPI_File fh, const void *buf, IMPL_Count count, MPI_Datatype datatype, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_File_write_shared_c(fh, buf, count, datatype, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Free_mem(void *base)
{
    return IMPL_Free_mem(base);
}

int WRAP_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return IMPL_Gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int WRAP_Gather_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return IMPL_Gather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int WRAP_Gather_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Gather_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int WRAP_Gather_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Gather_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int WRAP_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return IMPL_Gatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm);
}

int WRAP_Gatherv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return IMPL_Gatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm);
}

int WRAP_Gatherv_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Gatherv_init(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, info, request);
}

int WRAP_Gatherv_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Gatherv_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, info, request);
}

int WRAP_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win)
{
    return IMPL_Get(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
}

int WRAP_Get_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win)
{
    return IMPL_Get_accumulate(origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
}

int WRAP_Get_accumulate_c(const void *origin_addr, IMPL_Count origin_count, MPI_Datatype origin_datatype, void *result_addr, IMPL_Count result_count, MPI_Datatype result_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win)
{
    return IMPL_Get_accumulate_c(origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
}

int WRAP_Get_address(const void *location, IMPL_Aint *address)
{
    return IMPL_Get_address(location, address);
}

int WRAP_Get_c(void *origin_addr, IMPL_Count origin_count, MPI_Datatype origin_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype target_datatype, MPI_Win win)
{
    return IMPL_Get_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
}

int WRAP_Get_count(const WRAP_Status *status, MPI_Datatype datatype, int *count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    return IMPL_Get_count(&impl_status, datatype, count);
}

int WRAP_Get_count_c(const WRAP_Status *status, MPI_Datatype datatype, IMPL_Count *count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    return IMPL_Get_count_c(&impl_status, datatype, count);
}

int WRAP_Get_elements(const WRAP_Status *status, MPI_Datatype datatype, int *count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    return IMPL_Get_elements(&impl_status, datatype, count);
}

int WRAP_Get_elements_c(const WRAP_Status *status, MPI_Datatype datatype, IMPL_Count *count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    return IMPL_Get_elements_c(&impl_status, datatype, count);
}

int WRAP_Get_elements_x(const WRAP_Status *status, MPI_Datatype datatype, IMPL_Count *count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    return IMPL_Get_elements_x(&impl_status, datatype, count);
}

int WRAP_Graph_create(MPI_Comm comm_old, int nnodes, const int indx[], const int edges[], int reorder, MPI_Comm *comm_graph)
{
    return IMPL_Graph_create(comm_old, nnodes, indx, edges, reorder, comm_graph);
}

int WRAP_Graph_get(MPI_Comm comm, int maxindex, int maxedges, int indx[], int edges[])
{
    return IMPL_Graph_get(comm, maxindex, maxedges, indx, edges);
}

int WRAP_Graph_map(MPI_Comm comm, int nnodes, const int indx[], const int edges[], int *newrank)
{
    return IMPL_Graph_map(comm, nnodes, indx, edges, newrank);
}

int WRAP_Graph_neighbors(MPI_Comm comm, int rank, int maxneighbors, int neighbors[])
{
    return IMPL_Graph_neighbors(comm, rank, maxneighbors, neighbors);
}

int WRAP_Graph_neighbors_count(MPI_Comm comm, int rank, int *nneighbors)
{
    return IMPL_Graph_neighbors_count(comm, rank, nneighbors);
}

int WRAP_Graphdims_get(MPI_Comm comm, int *nnodes, int *nedges)
{
    return IMPL_Graphdims_get(comm, nnodes, nedges);
}

int WRAP_Grequest_complete(MPI_Request request)
{
    return IMPL_Grequest_complete(request);
}

int WRAP_Grequest_start(MPI_Grequest_query_function *query_fn, MPI_Grequest_free_function *free_fn, MPI_Grequest_cancel_function *cancel_fn, void *extra_state, MPI_Request *request)
{
    return IMPL_Grequest_start(query_fn, free_fn, cancel_fn, extra_state, request);
}

int WRAP_Group_compare(MPI_Group group1, MPI_Group group2, int *result)
{
    return IMPL_Group_compare(group1, group2, result);
}

int WRAP_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup)
{
    return IMPL_Group_difference(group1, group2, newgroup);
}

int WRAP_Group_excl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup)
{
    return IMPL_Group_excl(group, n, ranks, newgroup);
}

int WRAP_Group_free(MPI_Group *group)
{
    return IMPL_Group_free(group);
}

#if MPI_VERSION >= 4
int WRAP_Group_from_session_pset(MPI_Session session, const char *pset_name, MPI_Group *newgroup)
{
    return IMPL_Group_from_session_pset(session, pset_name, newgroup);
}
#endif

int WRAP_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup)
{
    return IMPL_Group_incl(group, n, ranks, newgroup);
}

int WRAP_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup)
{
    return IMPL_Group_intersection(group1, group2, newgroup);
}

int WRAP_Group_range_excl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup)
{
    return IMPL_Group_range_excl(group, n, ranges, newgroup);
}

int WRAP_Group_range_incl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup)
{
    return IMPL_Group_range_incl(group, n, ranges, newgroup);
}

int WRAP_Group_rank(MPI_Group group, int *rank)
{
    return IMPL_Group_rank(group, rank);
}

int WRAP_Group_size(MPI_Group group, int *size)
{
    return IMPL_Group_size(group, size);
}

int WRAP_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[])
{
    return IMPL_Group_translate_ranks(group1, n, ranks1, group2, ranks2);
}

int WRAP_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup)
{
    return IMPL_Group_union(group1, group2, newgroup);
}

int WRAP_Iallgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Iallgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int WRAP_Iallgather_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Iallgather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int WRAP_Iallgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Iallgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
}

int WRAP_Iallgatherv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Iallgatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
}

int WRAP_Iallreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Iallreduce(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int WRAP_Iallreduce_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Iallreduce_c(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int WRAP_Ialltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ialltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int WRAP_Ialltoall_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ialltoall_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int WRAP_Ialltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ialltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
}

int WRAP_Ialltoallv_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ialltoallv_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
}

int WRAP_Ialltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
}

int WRAP_Ialltoallw_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ialltoallw_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
}

int WRAP_Ibarrier(MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ibarrier(comm, request);
}

int WRAP_Ibcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ibcast(buffer, count, datatype, root, comm, request);
}

int WRAP_Ibcast_c(void *buffer, IMPL_Count count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ibcast_c(buffer, count, datatype, root, comm, request);
}

int WRAP_Ibsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ibsend(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Ibsend_c(const void *buf, IMPL_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ibsend_c(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Iexscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Iexscan(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int WRAP_Iexscan_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Iexscan_c(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int WRAP_Igather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Igather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int WRAP_Igather_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Igather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int WRAP_Igatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Igatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, request);
}

int WRAP_Igatherv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Igatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, request);
}

int WRAP_Improbe(int source, int tag, MPI_Comm comm, int *flag, MPI_Message *message, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Improbe(source, tag, comm, flag, message, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Imrecv(void *buf, int count, MPI_Datatype datatype, MPI_Message *message, MPI_Request *request)
{
    return IMPL_Imrecv(buf, count, datatype, message, request);
}

int WRAP_Imrecv_c(void *buf, IMPL_Count count, MPI_Datatype datatype, MPI_Message *message, MPI_Request *request)
{
    return IMPL_Imrecv_c(buf, count, datatype, message, request);
}

int WRAP_Ineighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ineighbor_allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int WRAP_Ineighbor_allgather_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ineighbor_allgather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int WRAP_Ineighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ineighbor_allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
}

int WRAP_Ineighbor_allgatherv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ineighbor_allgatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
}

int WRAP_Ineighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ineighbor_alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int WRAP_Ineighbor_alltoall_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ineighbor_alltoall_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int WRAP_Ineighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ineighbor_alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
}

int WRAP_Ineighbor_alltoallv_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ineighbor_alltoallv_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
}

int WRAP_Ineighbor_alltoallw(const void *sendbuf, const int sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ineighbor_alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
}

int WRAP_Ineighbor_alltoallw_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ineighbor_alltoallw_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
}

int WRAP_Info_create(MPI_Info *info)
{
    return IMPL_Info_create(info);
}

int WRAP_Info_create_env(int argc, char *argv[], MPI_Info *info)
{
    return IMPL_Info_create_env(argc, argv, info);
}

int WRAP_Info_delete(MPI_Info info, const char *key)
{
    return IMPL_Info_delete(info, key);
}

int WRAP_Info_dup(MPI_Info info, MPI_Info *newinfo)
{
    return IMPL_Info_dup(info, newinfo);
}

int WRAP_Info_free(MPI_Info *info)
{
    return IMPL_Info_free(info);
}

int WRAP_Info_get(MPI_Info info, const char *key, int valuelen, char *value, int *flag)
{
    return IMPL_Info_get(info, key, valuelen, value, flag);
}

int WRAP_Info_get_nkeys(MPI_Info info, int *nkeys)
{
    return IMPL_Info_get_nkeys(info, nkeys);
}

int WRAP_Info_get_nthkey(MPI_Info info, int n, char *key)
{
    return IMPL_Info_get_nthkey(info, n, key);
}

int WRAP_Info_get_string(MPI_Info info, const char *key, int *buflen, char *value, int *flag)
{
    return IMPL_Info_get_string(info, key, buflen, value, flag);
}

int WRAP_Info_get_valuelen(MPI_Info info, const char *key, int *valuelen, int *flag)
{
    return IMPL_Info_get_valuelen(info, key, valuelen, flag);
}

int WRAP_Info_set(MPI_Info info, const char *key, const char *value)
{
    return IMPL_Info_set(info, key, value);
}

int WRAP_Intercomm_create(MPI_Comm local_comm, int local_leader, MPI_Comm peer_comm, int remote_leader, int tag, MPI_Comm *newintercomm)
{
    return IMPL_Intercomm_create(local_comm, local_leader, peer_comm, remote_leader, tag, newintercomm);
}

int WRAP_Intercomm_create_from_groups(MPI_Group local_group, int local_leader, MPI_Group remote_group, int remote_leader, const char *stringtag, MPI_Info info, MPI_Errhandler errhandler, MPI_Comm *newintercomm)
{
    return IMPL_Intercomm_create_from_groups(local_group, local_leader, remote_group, remote_leader, stringtag, info, errhandler, newintercomm);
}

int WRAP_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintracomm)
{
    return IMPL_Intercomm_merge(intercomm, high, newintracomm);
}

int WRAP_Iprobe(int source, int tag, MPI_Comm comm, int *flag, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Iprobe(source, tag, comm, flag, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Irecv(buf, count, datatype, source, tag, comm, request);
}

int WRAP_Irecv_c(void *buf, IMPL_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Irecv_c(buf, count, datatype, source, tag, comm, request);
}

int WRAP_Ireduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ireduce(sendbuf, recvbuf, count, datatype, op, root, comm, request);
}

int WRAP_Ireduce_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ireduce_c(sendbuf, recvbuf, count, datatype, op, root, comm, request);
}

int WRAP_Ireduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ireduce_scatter(sendbuf, recvbuf, recvcounts, datatype, op, comm, request);
}

int WRAP_Ireduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ireduce_scatter_block(sendbuf, recvbuf, recvcount, datatype, op, comm, request);
}

int WRAP_Ireduce_scatter_block_c(const void *sendbuf, void *recvbuf, IMPL_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ireduce_scatter_block_c(sendbuf, recvbuf, recvcount, datatype, op, comm, request);
}

int WRAP_Ireduce_scatter_c(const void *sendbuf, void *recvbuf, const IMPL_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ireduce_scatter_c(sendbuf, recvbuf, recvcounts, datatype, op, comm, request);
}

int WRAP_Irsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Irsend(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Irsend_c(const void *buf, IMPL_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Irsend_c(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Iscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Iscan(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int WRAP_Iscan_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Iscan_c(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int WRAP_Iscatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Iscatter(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int WRAP_Iscatter_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Iscatter_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int WRAP_Iscatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Iscatterv(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int WRAP_Iscatterv_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint displs[], MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Iscatterv_c(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int WRAP_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Isend(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Isend_c(const void *buf, IMPL_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Isend_c(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Isendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Isendrecv(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, request);
}

int WRAP_Isendrecv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Isendrecv_c(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, request);
}

int WRAP_Isendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Isendrecv_replace(buf, count, datatype, dest, sendtag, source, recvtag, comm, request);
}

int WRAP_Isendrecv_replace_c(void *buf, IMPL_Count count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Isendrecv_replace_c(buf, count, datatype, dest, sendtag, source, recvtag, comm, request);
}

int WRAP_Issend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Issend(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Issend_c(const void *buf, IMPL_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Issend_c(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Keyval_create(MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state)
{
    return IMPL_Keyval_create(copy_fn, delete_fn, keyval, extra_state);
}

int WRAP_Keyval_free(int *keyval)
{
    return IMPL_Keyval_free(keyval);
}

int WRAP_Lookup_name(const char *service_name, MPI_Info info, char *port_name)
{
    return IMPL_Lookup_name(service_name, info, port_name);
}

int WRAP_Mprobe(int source, int tag, MPI_Comm comm, MPI_Message *message, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Mprobe(source, tag, comm, message, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Mrecv(void *buf, int count, MPI_Datatype datatype, MPI_Message *message, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Mrecv(buf, count, datatype, message, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Mrecv_c(void *buf, IMPL_Count count, MPI_Datatype datatype, MPI_Message *message, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Mrecv_c(buf, count, datatype, message, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Neighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Neighbor_allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int WRAP_Neighbor_allgather_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Neighbor_allgather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int WRAP_Neighbor_allgather_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Neighbor_allgather_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int WRAP_Neighbor_allgather_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Neighbor_allgather_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int WRAP_Neighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Neighbor_allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
}

int WRAP_Neighbor_allgatherv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Neighbor_allgatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
}

int WRAP_Neighbor_allgatherv_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Neighbor_allgatherv_init(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, info, request);
}

int WRAP_Neighbor_allgatherv_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Neighbor_allgatherv_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, info, request);
}

int WRAP_Neighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Neighbor_alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int WRAP_Neighbor_alltoall_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Neighbor_alltoall_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int WRAP_Neighbor_alltoall_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Neighbor_alltoall_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int WRAP_Neighbor_alltoall_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Neighbor_alltoall_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int WRAP_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Neighbor_alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}

int WRAP_Neighbor_alltoallv_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return IMPL_Neighbor_alltoallv_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}

int WRAP_Neighbor_alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Neighbor_alltoallv_init(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, info, request);
}

int WRAP_Neighbor_alltoallv_init_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Neighbor_alltoallv_init_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, info, request);
}

int WRAP_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm)
{
    return IMPL_Neighbor_alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
}

int WRAP_Neighbor_alltoallw_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm)
{
    return IMPL_Neighbor_alltoallw_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
}

int WRAP_Neighbor_alltoallw_init(const void *sendbuf, const int sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Neighbor_alltoallw_init(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, info, request);
}

int WRAP_Neighbor_alltoallw_init_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const IMPL_Count recvcounts[], const IMPL_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Neighbor_alltoallw_init_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, info, request);
}

int WRAP_Op_commutative(MPI_Op op, int *commute)
{
    return IMPL_Op_commutative(op, commute);
}

int WRAP_Op_create(MPI_User_function *user_fn, int commute, MPI_Op *op)
{
    return IMPL_Op_create(user_fn, commute, op);
}

#if MPI_VERSION >= 4
int WRAP_Op_create_c(MPI_User_function_c *user_fn, int commute, MPI_Op *op)
{
    return IMPL_Op_create_c(user_fn, commute, op);
}
#endif

int WRAP_Op_free(MPI_Op *op)
{
    return IMPL_Op_free(op);
}

int WRAP_Open_port(MPI_Info info, char *port_name)
{
    return IMPL_Open_port(info, port_name);
}

int WRAP_Pack(const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm)
{
    return IMPL_Pack(inbuf, incount, datatype, outbuf, outsize, position, comm);
}

int WRAP_Pack_c(const void *inbuf, IMPL_Count incount, MPI_Datatype datatype, void *outbuf, IMPL_Count outsize, IMPL_Count *position, MPI_Comm comm)
{
    return IMPL_Pack_c(inbuf, incount, datatype, outbuf, outsize, position, comm);
}

int WRAP_Pack_external(const char *datarep, const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, IMPL_Aint outsize, IMPL_Aint *position)
{
    return IMPL_Pack_external(datarep, inbuf, incount, datatype, outbuf, outsize, position);
}

int WRAP_Pack_external_c(const char *datarep, const void *inbuf, IMPL_Count incount, MPI_Datatype datatype, void *outbuf, IMPL_Count outsize, IMPL_Count *position)
{
    return IMPL_Pack_external_c(datarep, inbuf, incount, datatype, outbuf, outsize, position);
}

int WRAP_Pack_external_size(const char *datarep, int incount, MPI_Datatype datatype, IMPL_Aint *size)
{
    return IMPL_Pack_external_size(datarep, incount, datatype, size);
}

int WRAP_Pack_external_size_c(const char *datarep, IMPL_Count incount, MPI_Datatype datatype, IMPL_Count *size)
{
    return IMPL_Pack_external_size_c(datarep, incount, datatype, size);
}

int WRAP_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int *size)
{
    return IMPL_Pack_size(incount, datatype, comm, size);
}

int WRAP_Pack_size_c(IMPL_Count incount, MPI_Datatype datatype, MPI_Comm comm, IMPL_Count *size)
{
    return IMPL_Pack_size_c(incount, datatype, comm, size);
}

int WRAP_Parrived(MPI_Request request, int partition, int *flag)
{
    return IMPL_Parrived(request, partition, flag);
}

int WRAP_Pcontrol(const int level, ...)
{
    return IMPL_Pcontrol(level);
}

int WRAP_Pready(int partition, MPI_Request request)
{
    return IMPL_Pready(partition, request);
}

int WRAP_Pready_list(int length, const int array_of_partitions[], MPI_Request request)
{
    return IMPL_Pready_list(length, array_of_partitions, request);
}

int WRAP_Pready_range(int partition_low, int partition_high, MPI_Request request)
{
    return IMPL_Pready_range(partition_low, partition_high, request);
}

int WRAP_Precv_init(void *buf, int partitions, IMPL_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Precv_init(buf, partitions, count, datatype, dest, tag, comm, info, request);
}

int WRAP_Probe(int source, int tag, MPI_Comm comm, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Probe(source, tag, comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Psend_init(const void *buf, int partitions, IMPL_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Psend_init(buf, partitions, count, datatype, dest, tag, comm, info, request);
}

int WRAP_Publish_name(const char *service_name, MPI_Info info, const char *port_name)
{
    return IMPL_Publish_name(service_name, info, port_name);
}

int WRAP_Put(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win)
{
    return IMPL_Put(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
}

int WRAP_Put_c(const void *origin_addr, IMPL_Count origin_count, MPI_Datatype origin_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype target_datatype, MPI_Win win)
{
    return IMPL_Put_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
}

int WRAP_Raccumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request)
{
    return IMPL_Raccumulate(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
}

int WRAP_Raccumulate_c(const void *origin_addr, IMPL_Count origin_count, MPI_Datatype origin_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request)
{
    return IMPL_Raccumulate_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
}

int WRAP_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Recv(buf, count, datatype, source, tag, comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Recv_c(void *buf, IMPL_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Recv_c(buf, count, datatype, source, tag, comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Recv_init(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Recv_init(buf, count, datatype, source, tag, comm, request);
}

int WRAP_Recv_init_c(void *buf, IMPL_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Recv_init_c(buf, count, datatype, source, tag, comm, request);
}

int WRAP_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
{
    return IMPL_Reduce(sendbuf, recvbuf, count, datatype, op, root, comm);
}

int WRAP_Reduce_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
{
    return IMPL_Reduce_c(sendbuf, recvbuf, count, datatype, op, root, comm);
}

int WRAP_Reduce_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Reduce_init(sendbuf, recvbuf, count, datatype, op, root, comm, info, request);
}

int WRAP_Reduce_init_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Reduce_init_c(sendbuf, recvbuf, count, datatype, op, root, comm, info, request);
}

int WRAP_Reduce_local(const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op)
{
    return IMPL_Reduce_local(inbuf, inoutbuf, count, datatype, op);
}

int WRAP_Reduce_local_c(const void *inbuf, void *inoutbuf, IMPL_Count count, MPI_Datatype datatype, MPI_Op op)
{
    return IMPL_Reduce_local_c(inbuf, inoutbuf, count, datatype, op);
}

int WRAP_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return IMPL_Reduce_scatter(sendbuf, recvbuf, recvcounts, datatype, op, comm);
}

int WRAP_Reduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return IMPL_Reduce_scatter_block(sendbuf, recvbuf, recvcount, datatype, op, comm);
}

int WRAP_Reduce_scatter_block_c(const void *sendbuf, void *recvbuf, IMPL_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return IMPL_Reduce_scatter_block_c(sendbuf, recvbuf, recvcount, datatype, op, comm);
}

int WRAP_Reduce_scatter_block_init(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Reduce_scatter_block_init(sendbuf, recvbuf, recvcount, datatype, op, comm, info, request);
}

int WRAP_Reduce_scatter_block_init_c(const void *sendbuf, void *recvbuf, IMPL_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Reduce_scatter_block_init_c(sendbuf, recvbuf, recvcount, datatype, op, comm, info, request);
}

int WRAP_Reduce_scatter_c(const void *sendbuf, void *recvbuf, const IMPL_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return IMPL_Reduce_scatter_c(sendbuf, recvbuf, recvcounts, datatype, op, comm);
}

int WRAP_Reduce_scatter_init(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Reduce_scatter_init(sendbuf, recvbuf, recvcounts, datatype, op, comm, info, request);
}

int WRAP_Reduce_scatter_init_c(const void *sendbuf, void *recvbuf, const IMPL_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Reduce_scatter_init_c(sendbuf, recvbuf, recvcounts, datatype, op, comm, info, request);
}

int WRAP_Register_datarep(const char *datarep, MPI_Datarep_conversion_function *read_conversion_fn, MPI_Datarep_conversion_function *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state)
{
    return IMPL_Register_datarep(datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
}

#if MPI_VERSION >= 4
int WRAP_Register_datarep_c(const char *datarep, MPI_Datarep_conversion_function_c *read_conversion_fn, MPI_Datarep_conversion_function_c *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state)
{
    return IMPL_Register_datarep_c(datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
}
#endif

int WRAP_Request_free(MPI_Request *request)
{
    return IMPL_Request_free(request);
}

int WRAP_Request_get_status(MPI_Request request, int *flag, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Request_get_status(request, flag, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Rget(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request)
{
    return IMPL_Rget(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win, request);
}

int WRAP_Rget_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request)
{
    return IMPL_Rget_accumulate(origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
}

int WRAP_Rget_accumulate_c(const void *origin_addr, IMPL_Count origin_count, MPI_Datatype origin_datatype, void *result_addr, IMPL_Count result_count, MPI_Datatype result_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request)
{
    return IMPL_Rget_accumulate_c(origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
}

int WRAP_Rget_c(void *origin_addr, IMPL_Count origin_count, MPI_Datatype origin_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request)
{
    return IMPL_Rget_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win, request);
}

int WRAP_Rput(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, IMPL_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request)
{
    return IMPL_Rput(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win, request);
}

int WRAP_Rput_c(const void *origin_addr, IMPL_Count origin_count, MPI_Datatype origin_datatype, int target_rank, IMPL_Aint target_disp, IMPL_Count target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request)
{
    return IMPL_Rput_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win, request);
}

int WRAP_Rsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return IMPL_Rsend(buf, count, datatype, dest, tag, comm);
}

int WRAP_Rsend_c(const void *buf, IMPL_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return IMPL_Rsend_c(buf, count, datatype, dest, tag, comm);
}

int WRAP_Rsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Rsend_init(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Rsend_init_c(const void *buf, IMPL_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Rsend_init_c(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Scan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return IMPL_Scan(sendbuf, recvbuf, count, datatype, op, comm);
}

int WRAP_Scan_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return IMPL_Scan_c(sendbuf, recvbuf, count, datatype, op, comm);
}

int WRAP_Scan_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Scan_init(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int WRAP_Scan_init_c(const void *sendbuf, void *recvbuf, IMPL_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Scan_init_c(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int WRAP_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return IMPL_Scatter(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int WRAP_Scatter_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return IMPL_Scatter_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int WRAP_Scatter_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Scatter_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int WRAP_Scatter_init_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Scatter_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int WRAP_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return IMPL_Scatterv(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int WRAP_Scatterv_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint displs[], MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return IMPL_Scatterv_c(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int WRAP_Scatterv_init(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Scatterv_init(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int WRAP_Scatterv_init_c(const void *sendbuf, const IMPL_Count sendcounts[], const IMPL_Aint displs[], MPI_Datatype sendtype, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return IMPL_Scatterv_init_c(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int WRAP_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return IMPL_Send(buf, count, datatype, dest, tag, comm);
}

int WRAP_Send_c(const void *buf, IMPL_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return IMPL_Send_c(buf, count, datatype, dest, tag, comm);
}

int WRAP_Send_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Send_init(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Send_init_c(const void *buf, IMPL_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Send_init_c(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Sendrecv(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Sendrecv_c(const void *sendbuf, IMPL_Count sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, IMPL_Count recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Sendrecv_c(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Sendrecv_replace(buf, count, datatype, dest, sendtag, source, recvtag, comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Sendrecv_replace_c(void *buf, IMPL_Count count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Sendrecv_replace_c(buf, count, datatype, dest, sendtag, source, recvtag, comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

#if MPI_VERSION >= 4
int WRAP_Session_call_errhandler(MPI_Session session, int errorcode)
{
    return IMPL_Session_call_errhandler(session, errorcode);
}

int WRAP_Session_create_errhandler(MPI_Session_errhandler_function *session_errhandler_fn, MPI_Errhandler *errhandler)
{
    return IMPL_Session_create_errhandler(session_errhandler_fn, errhandler);
}

int WRAP_Session_finalize(MPI_Session *session)
{
    return IMPL_Session_finalize(session);
}

int WRAP_Session_get_errhandler(MPI_Session session, MPI_Errhandler *errhandler)
{
    return IMPL_Session_get_errhandler(session, errhandler);
}

int WRAP_Session_get_info(MPI_Session session, MPI_Info *info_used)
{
    return IMPL_Session_get_info(session, info_used);
}

int WRAP_Session_get_nth_pset(MPI_Session session, MPI_Info info, int n, int *pset_len, char *pset_name)
{
    return IMPL_Session_get_nth_pset(session, info, n, pset_len, pset_name);
}

int WRAP_Session_get_num_psets(MPI_Session session, MPI_Info info, int *npset_names)
{
    return IMPL_Session_get_num_psets(session, info, npset_names);
}

int WRAP_Session_get_pset_info(MPI_Session session, const char *pset_name, MPI_Info *info)
{
    return IMPL_Session_get_pset_info(session, pset_name, info);
}

int WRAP_Session_init(MPI_Info info, MPI_Errhandler errhandler, MPI_Session *session)
{
    return IMPL_Session_init(info, errhandler, session);
}

int WRAP_Session_set_errhandler(MPI_Session session, MPI_Errhandler errhandler)
{
    return IMPL_Session_set_errhandler(session, errhandler);
}
#endif

int WRAP_Ssend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return IMPL_Ssend(buf, count, datatype, dest, tag, comm);
}

int WRAP_Ssend_c(const void *buf, IMPL_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return IMPL_Ssend_c(buf, count, datatype, dest, tag, comm);
}

int WRAP_Ssend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ssend_init(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Ssend_init_c(const void *buf, IMPL_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return IMPL_Ssend_init_c(buf, count, datatype, dest, tag, comm, request);
}

int WRAP_Start(MPI_Request *request)
{
    return IMPL_Start(request);
}

int WRAP_Startall(int count, MPI_Request array_of_requests[])
{
    return IMPL_Startall(count, array_of_requests);
}

#ifdef SUPPORT_F08
int WRAP_Status_f082c(const WRAP_F08_status *f08_status, WRAP_Status *c_status)
{
    return IMPL_Status_f082c(f08_status, c_status);
}

int WRAP_Status_f082f(const WRAP_F08_status *f08_status, MPI_Fint *f_status)
{
    return IMPL_Status_f082f(f08_status, f_status);
}

int WRAP_Status_f2f08(const MPI_Fint *f_status, WRAP_F08_status *f08_status)
{
    return IMPL_Status_f2f08(f_status, f08_status);
}
#endif

int WRAP_Status_set_cancelled(WRAP_Status *status, int flag)
{
    return IMPL_Status_set_cancelled(status, flag);
}

int WRAP_Status_set_elements(WRAP_Status *status, MPI_Datatype datatype, int count)
{
    return IMPL_Status_set_elements(status, datatype, count);
}

int WRAP_Status_set_elements_c(WRAP_Status *status, MPI_Datatype datatype, IMPL_Count count)
{
    return IMPL_Status_set_elements_c(status, datatype, count);
}

int WRAP_Status_set_elements_x(WRAP_Status *status, MPI_Datatype datatype, IMPL_Count count)
{
    return IMPL_Status_set_elements_x(status, datatype, count);
}

int WRAP_Test(MPI_Request *request, int *flag, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Test(request, flag, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Test_cancelled(const WRAP_Status *status, int *flag)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    return IMPL_Test_cancelled(&impl_status, flag);
}

int WRAP_Testall(int count, MPI_Request array_of_requests[], int *flag, WRAP_Status array_of_statuses[])
{
    return IMPL_Testall(count, array_of_requests, flag, array_of_statuses);
}

int WRAP_Testany(int count, MPI_Request array_of_requests[], int *indx, int *flag, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Testany(count, array_of_requests, indx, flag, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Testsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], WRAP_Status array_of_statuses[])
{
    return IMPL_Testsome(incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
}

int WRAP_Topo_test(MPI_Comm comm, int *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Topo_test(comm, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Type_commit(MPI_Datatype *datatype)
{
    return IMPL_Type_commit(datatype);
}

int WRAP_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_contiguous(count, oldtype, newtype);
}

int WRAP_Type_contiguous_c(IMPL_Count count, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_contiguous_c(count, oldtype, newtype);
}

int WRAP_Type_create_darray(int size, int rank, int ndims, const int array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_create_darray(size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, order, oldtype, newtype);
}

int WRAP_Type_create_darray_c(int size, int rank, int ndims, const IMPL_Count array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_create_darray_c(size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, order, oldtype, newtype);
}

int WRAP_Type_create_f90_complex(int p, int r, MPI_Datatype *newtype)
{
    return IMPL_Type_create_f90_complex(p, r, newtype);
}

int WRAP_Type_create_f90_integer(int r, MPI_Datatype *newtype)
{
    return IMPL_Type_create_f90_integer(r, newtype);
}

int WRAP_Type_create_f90_real(int p, int r, MPI_Datatype *newtype)
{
    return IMPL_Type_create_f90_real(p, r, newtype);
}

int WRAP_Type_create_hindexed(int count, const int array_of_blocklengths[], const IMPL_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_create_hindexed(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int WRAP_Type_create_hindexed_block(int count, int blocklength, const IMPL_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_create_hindexed_block(count, blocklength, array_of_displacements, oldtype, newtype);
}

int WRAP_Type_create_hindexed_block_c(IMPL_Count count, IMPL_Count blocklength, const IMPL_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_create_hindexed_block_c(count, blocklength, array_of_displacements, oldtype, newtype);
}

int WRAP_Type_create_hindexed_c(IMPL_Count count, const IMPL_Count array_of_blocklengths[], const IMPL_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_create_hindexed_c(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int WRAP_Type_create_hvector(int count, int blocklength, IMPL_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_create_hvector(count, blocklength, stride, oldtype, newtype);
}

int WRAP_Type_create_hvector_c(IMPL_Count count, IMPL_Count blocklength, IMPL_Count stride, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_create_hvector_c(count, blocklength, stride, oldtype, newtype);
}

int WRAP_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_create_indexed_block(count, blocklength, array_of_displacements, oldtype, newtype);
}

int WRAP_Type_create_indexed_block_c(IMPL_Count count, IMPL_Count blocklength, const IMPL_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_create_indexed_block_c(count, blocklength, array_of_displacements, oldtype, newtype);
}

int WRAP_Type_create_keyval(MPI_Type_copy_attr_function *type_copy_attr_fn, MPI_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state)
{
    return IMPL_Type_create_keyval(type_copy_attr_fn, type_delete_attr_fn, type_keyval, extra_state);
}

int WRAP_Type_create_resized(MPI_Datatype oldtype, IMPL_Aint lb, IMPL_Aint extent, MPI_Datatype *newtype)
{
    return IMPL_Type_create_resized(oldtype, lb, extent, newtype);
}

int WRAP_Type_create_resized_c(MPI_Datatype oldtype, IMPL_Count lb, IMPL_Count extent, MPI_Datatype *newtype)
{
    return IMPL_Type_create_resized_c(oldtype, lb, extent, newtype);
}

int WRAP_Type_create_struct(int count, const int array_of_blocklengths[], const IMPL_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype)
{
    return IMPL_Type_create_struct(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype);
}

int WRAP_Type_create_struct_c(IMPL_Count count, const IMPL_Count array_of_blocklengths[], const IMPL_Count array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype)
{
    return IMPL_Type_create_struct_c(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype);
}

int WRAP_Type_create_subarray(int ndims, const int array_of_sizes[], const int array_of_subsizes[], const int array_of_starts[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_create_subarray(ndims, array_of_sizes, array_of_subsizes, array_of_starts, order, oldtype, newtype);
}

int WRAP_Type_create_subarray_c(int ndims, const IMPL_Count array_of_sizes[], const IMPL_Count array_of_subsizes[], const IMPL_Count array_of_starts[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_create_subarray_c(ndims, array_of_sizes, array_of_subsizes, array_of_starts, order, oldtype, newtype);
}

int WRAP_Type_delete_attr(MPI_Datatype datatype, int type_keyval)
{
    return IMPL_Type_delete_attr(datatype, type_keyval);
}

int WRAP_Type_dup(MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_dup(oldtype, newtype);
}

int WRAP_Type_extent(MPI_Datatype datatype, IMPL_Aint *extent)
{
    return IMPL_Type_extent(datatype, extent);
}

int WRAP_Type_free(MPI_Datatype *datatype)
{
    return IMPL_Type_free(datatype);
}

int WRAP_Type_free_keyval(int *type_keyval)
{
    return IMPL_Type_free_keyval(type_keyval);
}

int WRAP_Type_get_attr(MPI_Datatype datatype, int type_keyval, void *attribute_val, int *flag)
{
    return IMPL_Type_get_attr(datatype, type_keyval, attribute_val, flag);
}

int WRAP_Type_get_contents(MPI_Datatype datatype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], IMPL_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[])
{
    return IMPL_Type_get_contents(datatype, max_integers, max_addresses, max_datatypes, array_of_integers, array_of_addresses, array_of_datatypes);
}

int WRAP_Type_get_contents_c(MPI_Datatype datatype, IMPL_Count max_integers, IMPL_Count max_addresses, IMPL_Count max_large_counts, IMPL_Count max_datatypes, int array_of_integers[], IMPL_Aint array_of_addresses[], IMPL_Count array_of_large_counts[], MPI_Datatype array_of_datatypes[])
{
    return IMPL_Type_get_contents_c(datatype, max_integers, max_addresses, max_large_counts, max_datatypes, array_of_integers, array_of_addresses, array_of_large_counts, array_of_datatypes);
}

int WRAP_Type_get_envelope(MPI_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner)
{
    return IMPL_Type_get_envelope(datatype, num_integers, num_addresses, num_datatypes, combiner);
}

int WRAP_Type_get_envelope_c(MPI_Datatype datatype, IMPL_Count *num_integers, IMPL_Count *num_addresses, IMPL_Count *num_large_counts, IMPL_Count *num_datatypes, int *combiner)
{
    return IMPL_Type_get_envelope_c(datatype, num_integers, num_addresses, num_large_counts, num_datatypes, combiner);
}

int WRAP_Type_get_extent(MPI_Datatype datatype, IMPL_Aint *lb, IMPL_Aint *extent)
{
    return IMPL_Type_get_extent(datatype, lb, extent);
}

int WRAP_Type_get_extent_c(MPI_Datatype datatype, IMPL_Count *lb, IMPL_Count *extent)
{
    return IMPL_Type_get_extent_c(datatype, lb, extent);
}

int WRAP_Type_get_extent_x(MPI_Datatype datatype, IMPL_Count *lb, IMPL_Count *extent)
{
    return IMPL_Type_get_extent_x(datatype, lb, extent);
}

int WRAP_Type_get_name(MPI_Datatype datatype, char *type_name, int *resultlen)
{
    return IMPL_Type_get_name(datatype, type_name, resultlen);
}

int WRAP_Type_get_true_extent(MPI_Datatype datatype, IMPL_Aint *true_lb, IMPL_Aint *true_extent)
{
    return IMPL_Type_get_true_extent(datatype, true_lb, true_extent);
}

int WRAP_Type_get_true_extent_c(MPI_Datatype datatype, IMPL_Count *true_lb, IMPL_Count *true_extent)
{
    return IMPL_Type_get_true_extent_c(datatype, true_lb, true_extent);
}

int WRAP_Type_get_true_extent_x(MPI_Datatype datatype, IMPL_Count *true_lb, IMPL_Count *true_extent)
{
    return IMPL_Type_get_true_extent_x(datatype, true_lb, true_extent);
}

int WRAP_Type_hindexed(int count, int array_of_blocklengths[], IMPL_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_hindexed(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int WRAP_Type_hvector(int count, int blocklength, IMPL_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_hvector(count, blocklength, stride, oldtype, newtype);
}

int WRAP_Type_indexed(int count, const int array_of_blocklengths[], const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_indexed(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int WRAP_Type_indexed_c(IMPL_Count count, const IMPL_Count array_of_blocklengths[], const IMPL_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_indexed_c(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int WRAP_Type_lb(MPI_Datatype datatype, IMPL_Aint *displacement)
{
    return IMPL_Type_lb(datatype, displacement);
}

int WRAP_Type_match_size(int typeclass, int size, MPI_Datatype *datatype)
{
    return IMPL_Type_match_size(typeclass, size, datatype);
}

int WRAP_Type_set_attr(MPI_Datatype datatype, int type_keyval, void *attribute_val)
{
    return IMPL_Type_set_attr(datatype, type_keyval, attribute_val);
}

int WRAP_Type_set_name(MPI_Datatype datatype, const char *type_name)
{
    return IMPL_Type_set_name(datatype, type_name);
}

int WRAP_Type_size(MPI_Datatype datatype, int *size)
{
    return IMPL_Type_size(datatype, size);
}

int WRAP_Type_size_c(MPI_Datatype datatype, IMPL_Count *size)
{
    return IMPL_Type_size_c(datatype, size);
}

int WRAP_Type_size_x(MPI_Datatype datatype, IMPL_Count *size)
{
    return IMPL_Type_size_x(datatype, size);
}

int WRAP_Type_struct(int count, int array_of_blocklengths[], IMPL_Aint array_of_displacements[], MPI_Datatype array_of_types[], MPI_Datatype *newtype)
{
    return IMPL_Type_struct(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype);
}

int WRAP_Type_ub(MPI_Datatype datatype, IMPL_Aint *displacement)
{
    return IMPL_Type_ub(datatype, displacement);
}

int WRAP_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_vector(count, blocklength, stride, oldtype, newtype);
}

int WRAP_Type_vector_c(IMPL_Count count, IMPL_Count blocklength, IMPL_Count stride, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return IMPL_Type_vector_c(count, blocklength, stride, oldtype, newtype);
}

int WRAP_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm)
{
    return IMPL_Unpack(inbuf, insize, position, outbuf, outcount, datatype, comm);
}

int WRAP_Unpack_c(const void *inbuf, IMPL_Count insize, IMPL_Count *position, void *outbuf, IMPL_Count outcount, MPI_Datatype datatype, MPI_Comm comm)
{
    return IMPL_Unpack_c(inbuf, insize, position, outbuf, outcount, datatype, comm);
}

int WRAP_Unpack_external(const char datarep[], const void *inbuf, IMPL_Aint insize, IMPL_Aint *position, void *outbuf, int outcount, MPI_Datatype datatype)
{
    return IMPL_Unpack_external(datarep, inbuf, insize, position, outbuf, outcount, datatype);
}

int WRAP_Unpack_external_c(const char datarep[], const void *inbuf, IMPL_Count insize, IMPL_Count *position, void *outbuf, IMPL_Count outcount, MPI_Datatype datatype)
{
    return IMPL_Unpack_external_c(datarep, inbuf, insize, position, outbuf, outcount, datatype);
}

int WRAP_Unpublish_name(const char *service_name, MPI_Info info, const char *port_name)
{
    return IMPL_Unpublish_name(service_name, info, port_name);
}

int WRAP_Wait(MPI_Request *request, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Wait(request, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Waitall(int count, MPI_Request array_of_requests[], WRAP_Status array_of_statuses[])
{
    return IMPL_Waitall(count, array_of_requests, array_of_statuses);
}

int WRAP_Waitany(int count, MPI_Request array_of_requests[], int *indx, WRAP_Status *status)
{
    MPI_Status impl_status;
    int rc = IMPL_Waitany(count, array_of_requests, indx, &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return rc;
}

int WRAP_Waitsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], WRAP_Status array_of_statuses[])
{
    return IMPL_Waitsome(incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
}

int WRAP_Win_allocate(IMPL_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win)
{
    return IMPL_Win_allocate(size, disp_unit, info, comm, baseptr, win);
}

int WRAP_Win_allocate_c(IMPL_Aint size, IMPL_Aint disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win)
{
    return IMPL_Win_allocate_c(size, disp_unit, info, comm, baseptr, win);
}

int WRAP_Win_allocate_shared(IMPL_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win)
{
    return IMPL_Win_allocate_shared(size, disp_unit, info, comm, baseptr, win);
}

int WRAP_Win_allocate_shared_c(IMPL_Aint size, IMPL_Aint disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win)
{
    return IMPL_Win_allocate_shared_c(size, disp_unit, info, comm, baseptr, win);
}

int WRAP_Win_attach(MPI_Win win, void *base, IMPL_Aint size)
{
    return IMPL_Win_attach(win, base, size);
}

int WRAP_Win_call_errhandler(MPI_Win win, int errorcode)
{
    return IMPL_Win_call_errhandler(win, errorcode);
}

int WRAP_Win_complete(MPI_Win win)
{
    return IMPL_Win_complete(win);
}

int WRAP_Win_create(void *base, IMPL_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win)
{
    return IMPL_Win_create(base, size, disp_unit, info, comm, win);
}

int WRAP_Win_create_c(void *base, IMPL_Aint size, IMPL_Aint disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win)
{
    return IMPL_Win_create_c(base, size, disp_unit, info, comm, win);
}

int WRAP_Win_create_dynamic(MPI_Info info, MPI_Comm comm, MPI_Win *win)
{
    return IMPL_Win_create_dynamic(info, comm, win);
}

int WRAP_Win_create_errhandler(MPI_Win_errhandler_function *win_errhandler_fn, MPI_Errhandler *errhandler)
{
    return IMPL_Win_create_errhandler(win_errhandler_fn, errhandler);
}

int WRAP_Win_create_keyval(MPI_Win_copy_attr_function *win_copy_attr_fn, MPI_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state)
{
    return IMPL_Win_create_keyval(win_copy_attr_fn, win_delete_attr_fn, win_keyval, extra_state);
}

int WRAP_Win_delete_attr(MPI_Win win, int win_keyval)
{
    return IMPL_Win_delete_attr(win, win_keyval);
}

int WRAP_Win_detach(MPI_Win win, const void *base)
{
    return IMPL_Win_detach(win, base);
}

int WRAP_Win_fence(int assert, MPI_Win win)
{
    return IMPL_Win_fence(assert, win);
}

int WRAP_Win_flush(int rank, MPI_Win win)
{
    return IMPL_Win_flush(rank, win);
}

int WRAP_Win_flush_all(MPI_Win win)
{
    return IMPL_Win_flush_all(win);
}

int WRAP_Win_flush_local(int rank, MPI_Win win)
{
    return IMPL_Win_flush_local(rank, win);
}

int WRAP_Win_flush_local_all(MPI_Win win)
{
    return IMPL_Win_flush_local_all(win);
}

int WRAP_Win_free(MPI_Win *win)
{
    return IMPL_Win_free(win);
}

int WRAP_Win_free_keyval(int *win_keyval)
{
    return IMPL_Win_free_keyval(win_keyval);
}

int WRAP_Win_get_attr(MPI_Win win, int win_keyval, void *attribute_val, int *flag)
{
    return IMPL_Win_get_attr(win, win_keyval, attribute_val, flag);
}

int WRAP_Win_get_errhandler(MPI_Win win, MPI_Errhandler *errhandler)
{
    return IMPL_Win_get_errhandler(win, errhandler);
}

int WRAP_Win_get_group(MPI_Win win, MPI_Group *group)
{
    return IMPL_Win_get_group(win, group);
}

int WRAP_Win_get_info(MPI_Win win, MPI_Info *info_used)
{
    return IMPL_Win_get_info(win, info_used);
}

int WRAP_Win_get_name(MPI_Win win, char *win_name, int *resultlen)
{
    return IMPL_Win_get_name(win, win_name, resultlen);
}

int WRAP_Win_lock(int lock_type, int rank, int assert, MPI_Win win)
{
    return IMPL_Win_lock(lock_type, rank, assert, win);
}

int WRAP_Win_lock_all(int assert, MPI_Win win)
{
    return IMPL_Win_lock_all(assert, win);
}

int WRAP_Win_post(MPI_Group group, int assert, MPI_Win win)
{
    return IMPL_Win_post(group, assert, win);
}

int WRAP_Win_set_attr(MPI_Win win, int win_keyval, void *attribute_val)
{
    return IMPL_Win_set_attr(win, win_keyval, attribute_val);
}

int WRAP_Win_set_errhandler(MPI_Win win, MPI_Errhandler errhandler)
{
    return IMPL_Win_set_errhandler(win, errhandler);
}

int WRAP_Win_set_info(MPI_Win win, MPI_Info info)
{
    return IMPL_Win_set_info(win, info);
}

int WRAP_Win_set_name(MPI_Win win, const char *win_name)
{
    return IMPL_Win_set_name(win, win_name);
}

int WRAP_Win_shared_query(MPI_Win win, int rank, IMPL_Aint *size, int *disp_unit, void *baseptr)
{
    return IMPL_Win_shared_query(win, rank, size, disp_unit, baseptr);
}

int WRAP_Win_shared_query_c(MPI_Win win, int rank, IMPL_Aint *size, IMPL_Aint *disp_unit, void *baseptr)
{
    return IMPL_Win_shared_query_c(win, rank, size, disp_unit, baseptr);
}

int WRAP_Win_start(MPI_Group group, int assert, MPI_Win win)
{
    return IMPL_Win_start(group, assert, win);
}

int WRAP_Win_sync(MPI_Win win)
{
    return IMPL_Win_sync(win);
}

int WRAP_Win_test(MPI_Win win, int *flag)
{
    return IMPL_Win_test(win, flag);
}

int WRAP_Win_unlock(int rank, MPI_Win win)
{
    return IMPL_Win_unlock(rank, win);
}

int WRAP_Win_unlock_all(MPI_Win win)
{
    return IMPL_Win_unlock_all(win);
}

int WRAP_Win_wait(MPI_Win win)
{
    return IMPL_Win_wait(win);
}


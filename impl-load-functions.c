// SPDX-License-Identifier: MIT

#include "muk-dl.h"

#define MUK_EXTERN
#include "impl-fpointers.h"
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
    IMPL_Abort = MUK_DLSYM(h, NIMI(Abort));
    IMPL_Accumulate = MUK_DLSYM(h, NIMI(Accumulate));
    IMPL_Accumulate_c = MUK_DLSYM(h, NIMI(Accumulate_c));
#if 0
    IMPL_Add_error_class = MUK_DLSYM(h, NIMI(Add_error_class));
    IMPL_Add_error_code = MUK_DLSYM(h, NIMI(Add_error_code));
    IMPL_Add_error_string = MUK_DLSYM(h, NIMI(Add_error_string));
#endif
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
    IMPL_Comm_spawn = MUK_DLSYM(h, NIMI(Comm_spawn));
    IMPL_Comm_spawn_multiple = MUK_DLSYM(h, NIMI(Comm_spawn_multiple));
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
    // these are loaded directly into MUK *and* here because both need them
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


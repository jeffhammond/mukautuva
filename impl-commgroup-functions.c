#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define OMPI_WANT_MPI_INTERFACE_WARNING 0
#include <mpi.h>

#include "muk-predefined.h"

#include "impl-scalar-types.h"
#include "wrap-handle-typedefs.h"

#define MUK_EXTERN extern
#include "impl-fpointers.h"
#include "impl-linked-list.h"
#include "impl-constant-conversions.h"
#include "impl-handle-conversions.h"

// WRAP->IMPL functions

int WRAP_Cart_coords(WRAP_Comm comm, int rank, int maxdims, int coords[])
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Cart_coords(impl_comm, rank, maxdims, coords);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_create(WRAP_Comm comm_old, int ndims, const int dims[], const int periods[], int reorder, WRAP_Comm *comm_cart)
{
    MPI_Comm impl_comm_old = CONVERT_MPI_Comm(comm_old);
    MPI_Comm impl_comm_cart;
    int rc = IMPL_Cart_create(impl_comm_old, ndims, dims, periods, reorder, &impl_comm_cart);
    *comm_cart = OUTPUT_MPI_Comm(impl_comm_cart);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_get(WRAP_Comm comm, int maxdims, int dims[], int periods[], int coords[])
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Cart_get(impl_comm, maxdims, dims, periods, coords);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_map(WRAP_Comm comm, int ndims, const int dims[], const int periods[], int *newrank)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Cart_map(impl_comm, ndims, dims, periods, newrank);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_rank(WRAP_Comm comm, const int coords[], int *rank)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Cart_rank(impl_comm, coords, rank);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_shift(WRAP_Comm comm, int direction, int disp, int *rank_source, int *rank_dest)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int impl_rank_source, impl_rank_dest;
    int rc = IMPL_Cart_shift(impl_comm, direction, disp, &impl_rank_source, &impl_rank_dest);
    *rank_source = RANK_MUK_TO_IMPL(impl_rank_source);
    *rank_dest   = RANK_MUK_TO_IMPL(impl_rank_dest);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_sub(WRAP_Comm comm, const int remain_dims[], WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Cart_sub(impl_comm, remain_dims, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cartdim_get(WRAP_Comm comm, int *ndims)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Cartdim_get(impl_comm, ndims);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_accept(const char *port_name, WRAP_Info info, int root, WRAP_Comm comm, WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_accept(port_name, impl_info, root, impl_comm, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_call_errhandler(WRAP_Comm comm, int errorcode)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_call_errhandler(impl_comm, errorcode);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_compare(WRAP_Comm comm1, WRAP_Comm comm2, int *result)
{
    MPI_Comm impl_comm1 = CONVERT_MPI_Comm(comm1);
    MPI_Comm impl_comm2 = CONVERT_MPI_Comm(comm2);
    int rc = IMPL_Comm_compare(impl_comm1, impl_comm2, result);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_connect(const char *port_name, WRAP_Info info, int root, WRAP_Comm comm, WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_connect(port_name, impl_info, root, impl_comm, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_create(WRAP_Comm comm, WRAP_Group group, WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_create(impl_comm, impl_group, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_create_errhandler(WRAP_Comm_errhandler_function *comm_errhandler_fn, WRAP_Errhandler *errhandler)
{
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_Comm_create_errhandler(comm_errhandler_fn, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_create_from_group(WRAP_Group group, const char *stringtag, WRAP_Info info, WRAP_Errhandler errhandler, WRAP_Comm *newcomm)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_create_from_group(impl_group, stringtag, impl_info, impl_errhandler, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_create_group(WRAP_Comm comm, WRAP_Group group, int tag, WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_create_group(impl_comm, impl_group, tag, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_create_keyval(WRAP_Comm_copy_attr_function *comm_copy_attr_fn, WRAP_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state)
{
    MPI_Comm_copy_attr_function * impl_comm_copy_attr_fn = (MPI_Comm_copy_attr_function*)comm_copy_attr_fn;
    if ((intptr_t)comm_copy_attr_fn == (intptr_t)MUK_COMM_NULL_COPY_FN) {
        impl_comm_copy_attr_fn = MPI_COMM_NULL_COPY_FN;
    } else {
        printf("%s : %d FIXME\n",__func__,__LINE__);
    }
    MPI_Comm_delete_attr_function * impl_comm_delete_attr_fn = (MPI_Comm_delete_attr_function*)comm_delete_attr_fn;
    if ((intptr_t)comm_delete_attr_fn == (intptr_t)MUK_COMM_NULL_DELETE_FN) {
        impl_comm_delete_attr_fn = MPI_COMM_NULL_DELETE_FN;
    } else {
        printf("%s : %d FIXME\n",__func__,__LINE__);
    }
    int rc = IMPL_Comm_create_keyval(impl_comm_copy_attr_fn, impl_comm_delete_attr_fn, comm_keyval, extra_state);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_delete_attr(WRAP_Comm comm, int comm_keyval)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_delete_attr(impl_comm, comm_keyval);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_free_keyval(int *comm_keyval)
{
    int rc = IMPL_Comm_free_keyval(comm_keyval);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_attr(WRAP_Comm comm, int comm_keyval, void *attribute_val, int *flag)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_get_attr(impl_comm, KEY_MUK_TO_IMPL(comm_keyval), attribute_val, flag);
    if (comm_keyval == MUK_HOST) {
        **(int**)attribute_val = RANK_IMPL_TO_MUK(**(int**)attribute_val);
    }
#if 0
    // FIXME for comm if necessary
    // this is the only place this is needed, so we inline it
    if (**(int**)attribute_val == MPI_WIN_SEPARATE) {
        **(int**)attribute_val = MUK_WIN_SEPARATE;
    } else if (**(int**)attribute_val == MPI_WIN_UNIFIED) {
        **(int**)attribute_val = MUK_WIN_UNIFIED;
    }
#endif
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_set_attr(WRAP_Comm comm, int comm_keyval, void *attribute_val)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_set_attr(impl_comm, comm_keyval, attribute_val);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

// deleted versions of the above
int WRAP_Keyval_create(WRAP_Copy_function *copy_fn, WRAP_Delete_function *delete_fn, int *keyval, void *extra_state)
{
    MPI_Copy_function * impl_copy_fn = (MPI_Copy_function*)copy_fn;
    if ((intptr_t)copy_fn == (intptr_t)MUK_NULL_COPY_FN) {
        impl_copy_fn = MPI_NULL_COPY_FN;
    } else {
        printf("%s : %d FIXME\n",__func__,__LINE__);
    }
    MPI_Delete_function * impl_delete_fn = (MPI_Delete_function*)delete_fn;
    if ((intptr_t)delete_fn == (intptr_t)MUK_NULL_DELETE_FN) {
        impl_delete_fn = MPI_NULL_DELETE_FN;
    } else {
        printf("%s : %d FIXME\n",__func__,__LINE__);
    }
    int rc = IMPL_Keyval_create(impl_copy_fn, impl_delete_fn, keyval, extra_state);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Keyval_free(int *keyval)
{
    int rc = IMPL_Keyval_free(keyval);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Attr_delete(WRAP_Comm comm, int keyval)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Attr_delete(impl_comm, keyval);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Attr_get(WRAP_Comm comm, int keyval, void *attribute_val, int *flag)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Attr_get(impl_comm, KEY_MUK_TO_IMPL(keyval), attribute_val, flag);
    if (keyval == MUK_HOST) {
        **(int**)attribute_val = RANK_IMPL_TO_MUK(**(int**)attribute_val);
    }
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Attr_put(WRAP_Comm comm, int keyval, void *attribute_val)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Attr_put(impl_comm, keyval, attribute_val);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_disconnect(WRAP_Comm *comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(*comm);
    remove_errhandler_by_object(Comm,impl_comm,MPI_FILE_NULL,MPI_WIN_NULL);
    int rc = IMPL_Comm_disconnect(&impl_comm);
    *comm = OUTPUT_MPI_Comm(impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_dup(WRAP_Comm comm, WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_dup(impl_comm, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_dup_with_info(WRAP_Comm comm, WRAP_Info info, WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_dup_with_info(impl_comm, impl_info, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_free(WRAP_Comm *comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(*comm);
    remove_errhandler_by_object(Comm,impl_comm,MPI_FILE_NULL,MPI_WIN_NULL);
    int rc = IMPL_Comm_free(&impl_comm);
    *comm = OUTPUT_MPI_Comm(impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_errhandler(WRAP_Comm comm, WRAP_Errhandler *errhandler)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_Comm_get_errhandler(impl_comm, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_info(WRAP_Comm comm, WRAP_Info *info_used)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info_used;
    int rc = IMPL_Comm_get_info(impl_comm, &impl_info_used);
    *info_used = OUTPUT_MPI_Info(impl_info_used);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_name(WRAP_Comm comm, char *comm_name, int *resultlen)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_get_name(impl_comm, comm_name, resultlen);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_parent(WRAP_Comm *parent)
{
    MPI_Comm impl_parent;
    int rc = IMPL_Comm_get_parent(&impl_parent);
    *parent = OUTPUT_MPI_Comm(impl_parent);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_group(WRAP_Comm comm, WRAP_Group *group)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Group impl_group;
    int rc = IMPL_Comm_group(impl_comm, &impl_group);
    *group = OUTPUT_MPI_Group(impl_group);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_idup(WRAP_Comm comm, WRAP_Comm *newcomm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Comm impl_newcomm;
    MPI_Request impl_request;
    int rc = IMPL_Comm_idup(impl_comm, &impl_newcomm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_idup_with_info(WRAP_Comm comm, WRAP_Info info, WRAP_Comm *newcomm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_idup_with_info(impl_comm, impl_info, &impl_newcomm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_join(int fd, WRAP_Comm *intercomm)
{
    MPI_Comm impl_intercomm;
    int rc = IMPL_Comm_join(fd, &impl_intercomm);
    *intercomm = OUTPUT_MPI_Comm(impl_intercomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_rank(WRAP_Comm comm, int *rank)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_rank(impl_comm, rank);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_remote_group(WRAP_Comm comm, WRAP_Group *group)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Group impl_group;
    int rc = IMPL_Comm_remote_group(impl_comm, &impl_group);
    *group = OUTPUT_MPI_Group(impl_group);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_remote_size(WRAP_Comm comm, int *size)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_remote_size(impl_comm, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_set_errhandler(WRAP_Comm comm, WRAP_Errhandler errhandler)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    int rc = IMPL_Comm_set_errhandler(impl_comm, impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_set_info(WRAP_Comm comm, WRAP_Info info)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Comm_set_info(impl_comm, impl_info);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_set_name(WRAP_Comm comm, const char *comm_name)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_set_name(impl_comm, comm_name);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_size(WRAP_Comm comm, int *size)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_size(impl_comm, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_split(WRAP_Comm comm, int color, int key, WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_split(impl_comm, color, key, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_split_type(WRAP_Comm comm, int split_type, int key, WRAP_Info info, WRAP_Comm *newcomm)
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
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_split_type(impl_comm, impl_type, key, impl_info, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_test_inter(WRAP_Comm comm, int *flag)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_test_inter(impl_comm, flag);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dims_create(int nnodes, int ndims, int dims[])
{
    int rc = IMPL_Dims_create(nnodes, ndims, dims);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dist_graph_create(WRAP_Comm comm_old, int n, const int sources[], const int degrees[], const int destinations[], const int weights[], WRAP_Info info, int reorder, WRAP_Comm *comm_dist_graph, const int * mpich_unweighted, const int * mpich_weights_empty)
{
    MPI_Comm impl_comm_old = CONVERT_MPI_Comm(comm_old);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_comm_dist_graph;
    const int * impl_weights = WEIGHTS_MUK_TO_IMPL(weights, mpich_unweighted, mpich_weights_empty);
    int rc = IMPL_Dist_graph_create(impl_comm_old, n, sources, degrees, destinations, impl_weights, impl_info, reorder, &impl_comm_dist_graph);
    *comm_dist_graph = OUTPUT_MPI_Comm(impl_comm_dist_graph);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dist_graph_create_adjacent(WRAP_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], WRAP_Info info, int reorder, WRAP_Comm *comm_dist_graph, const int * mpich_unweighted, const int * mpich_weights_empty)
{
    MPI_Comm impl_comm_old = CONVERT_MPI_Comm(comm_old);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_comm_dist_graph;
    const int * impl_sourceweights = WEIGHTS_MUK_TO_IMPL(sourceweights, mpich_unweighted, mpich_weights_empty);
    const int * impl_destweights   = WEIGHTS_MUK_TO_IMPL(destweights, mpich_unweighted, mpich_weights_empty);
    int rc = IMPL_Dist_graph_create_adjacent(impl_comm_old, indegree, sources, impl_sourceweights, outdegree, destinations, impl_destweights, impl_info, reorder, &impl_comm_dist_graph);
    *comm_dist_graph = OUTPUT_MPI_Comm(impl_comm_dist_graph);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dist_graph_neighbors(WRAP_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[])
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Dist_graph_neighbors(impl_comm, maxindegree, sources, sourceweights, maxoutdegree, destinations, destweights);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dist_graph_neighbors_count(WRAP_Comm comm, int *indegree, int *outdegree, int *weighted)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Dist_graph_neighbors_count(impl_comm, indegree, outdegree, weighted);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_create(WRAP_Comm comm_old, int nnodes, const int indx[], const int edges[], int reorder, WRAP_Comm *comm_graph)
{
    MPI_Comm impl_comm_old = CONVERT_MPI_Comm(comm_old);
    MPI_Comm impl_comm_graph;
    int rc = IMPL_Graph_create(impl_comm_old, nnodes, indx, edges, reorder, &impl_comm_graph);
    *comm_graph = OUTPUT_MPI_Comm(impl_comm_graph);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_get(WRAP_Comm comm, int maxindex, int maxedges, int indx[], int edges[])
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Graph_get(impl_comm, maxindex, maxedges, indx, edges);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_map(WRAP_Comm comm, int nnodes, const int indx[], const int edges[], int *newrank)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int impl_newrank;
    int rc = IMPL_Graph_map(impl_comm, nnodes, indx, edges, &impl_newrank);
    if (impl_newrank == MPI_UNDEFINED) {
        *newrank = MUK_UNDEFINED;
    } else {
        *newrank = impl_newrank;
    }
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_neighbors(WRAP_Comm comm, int rank, int maxneighbors, int neighbors[])
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Graph_neighbors(impl_comm, rank, maxneighbors, neighbors);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_neighbors_count(WRAP_Comm comm, int rank, int *nneighbors)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Graph_neighbors_count(impl_comm, rank, nneighbors);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graphdims_get(WRAP_Comm comm, int *nnodes, int *nedges)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Graphdims_get(impl_comm, nnodes, nedges);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_compare(WRAP_Group group1, WRAP_Group group2, int *result)
{
    MPI_Group impl_group1 = CONVERT_MPI_Group(group1);
    MPI_Group impl_group2 = CONVERT_MPI_Group(group2);
    int rc = IMPL_Group_compare(impl_group1, impl_group2, result);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_difference(WRAP_Group group1, WRAP_Group group2, WRAP_Group *newgroup)
{
    MPI_Group impl_group1 = CONVERT_MPI_Group(group1);
    MPI_Group impl_group2 = CONVERT_MPI_Group(group2);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_difference(impl_group1, impl_group2, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_excl(WRAP_Group group, int n, const int ranks[], WRAP_Group *newgroup)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_excl(impl_group, n, ranks, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_free(WRAP_Group *group)
{
    MPI_Group impl_group = CONVERT_MPI_Group(*group);
    int rc = IMPL_Group_free(&impl_group);
    *group = OUTPUT_MPI_Group(impl_group);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Group_from_session_pset(WRAP_Session session, const char *pset_name, WRAP_Group *newgroup)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_from_session_pset(impl_session, pset_name, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Group_incl(WRAP_Group group, int n, const int ranks[], WRAP_Group *newgroup)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_incl(impl_group, n, ranks, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_intersection(WRAP_Group group1, WRAP_Group group2, WRAP_Group *newgroup)
{
    MPI_Group impl_group1 = CONVERT_MPI_Group(group1);
    MPI_Group impl_group2 = CONVERT_MPI_Group(group2);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_intersection(impl_group1, impl_group2, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_range_excl(WRAP_Group group, int n, int ranges[][3], WRAP_Group *newgroup)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_range_excl(impl_group, n, ranges, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_range_incl(WRAP_Group group, int n, int ranges[][3], WRAP_Group *newgroup)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_range_incl(impl_group, n, ranges, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_rank(WRAP_Group group, int *rank)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    int rc = IMPL_Group_rank(impl_group, rank);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_size(WRAP_Group group, int *size)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    int rc = IMPL_Group_size(impl_group, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_translate_ranks(WRAP_Group group1, int n, const int ranks1[], WRAP_Group group2, int ranks2[])
{
    int rc;
    // MPI_PROC_NULL is a valid rank for input to MPI_GROUP_TRANSLATE_RANKS,
    // which returns MPI_PROC_NULL as the translated rank.
    MPI_Group impl_group1 = CONVERT_MPI_Group(group1);
    MPI_Group impl_group2 = CONVERT_MPI_Group(group2);
    int * impl_ranks1 = calloc(n,sizeof(int));
    if (impl_ranks1 == NULL) {
        rc = MPI_ERR_INTERN;
        goto end;
    }
    for (int i=0; i<n; i++) {
        impl_ranks1[i] = RANK_MUK_TO_IMPL(ranks1[i]);
    }
    int * impl_ranks2 = calloc(n,sizeof(int));
    if (impl_ranks2 == NULL) {
        rc = MPI_ERR_INTERN;
        goto end;
    }
    rc = IMPL_Group_translate_ranks(impl_group1, n, impl_ranks1, impl_group2, impl_ranks2);
    for (int i=0; i<n; i++) {
        ranks2[i] = RANK_IMPL_TO_MUK(impl_ranks2[i]);
    }
    free(impl_ranks1);
    free(impl_ranks2);
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_union(WRAP_Group group1, WRAP_Group group2, WRAP_Group *newgroup)
{
    MPI_Group impl_group1 = CONVERT_MPI_Group(group1);
    MPI_Group impl_group2 = CONVERT_MPI_Group(group2);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_union(impl_group1, impl_group2, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Intercomm_create(WRAP_Comm local_comm, int local_leader, WRAP_Comm peer_comm, int remote_leader, int tag, WRAP_Comm *newintercomm)
{
    MPI_Comm impl_local_comm = CONVERT_MPI_Comm(local_comm);
    MPI_Comm impl_peer_comm = CONVERT_MPI_Comm(peer_comm);
    MPI_Comm impl_newintercomm;
    int rc = IMPL_Intercomm_create(impl_local_comm, local_leader, impl_peer_comm, remote_leader, tag, &impl_newintercomm);
    *newintercomm = OUTPUT_MPI_Comm(impl_newintercomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Intercomm_create_from_groups(WRAP_Group local_group, int local_leader, WRAP_Group remote_group, int remote_leader, const char *stringtag, WRAP_Info info, WRAP_Errhandler errhandler, WRAP_Comm *newintercomm)
{
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    MPI_Group impl_local_group = CONVERT_MPI_Group(local_group);
    MPI_Group impl_remote_group = CONVERT_MPI_Group(remote_group);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_newintercomm;
    int rc = IMPL_Intercomm_create_from_groups(impl_local_group, local_leader, impl_remote_group, remote_leader, stringtag, impl_info, impl_errhandler, &impl_newintercomm);
    *newintercomm = OUTPUT_MPI_Comm(impl_newintercomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Intercomm_merge(WRAP_Comm intercomm, int high, WRAP_Comm *newintracomm)
{
    MPI_Comm impl_intercomm = CONVERT_MPI_Comm(intercomm);
    MPI_Comm impl_newintracomm;
    int rc = IMPL_Intercomm_merge(impl_intercomm, high, &impl_newintracomm);
    *newintracomm = OUTPUT_MPI_Comm(impl_newintracomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Topo_test(WRAP_Comm comm, int *status)
{
    // The output value status is one of the following:
    // MPI_GRAPH    MPI_CART    MPI_DIST_GRAPH    MPI_UNDEFINED
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int impl_status;
    int rc = IMPL_Topo_test(impl_comm, &impl_status);
    // This is the only place we need this, so inline it.
    if (impl_status == MPI_GRAPH) {
        *status = MUK_GRAPH;
    }
    else if (impl_status == MPI_CART) {
        *status = MUK_CART;
    }
    else if (impl_status == MPI_DIST_GRAPH) {
        *status = MUK_DIST_GRAPH;
    }
    else if (impl_status == MPI_UNDEFINED) {
        *status = MUK_UNDEFINED;
    }
    else {
        printf("WRAP_Topo_test invalid status: %d\n", impl_status);
        *status = MUK_UNDEFINED;
    }
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Lookup_name(const char *service_name, WRAP_Info info, char *port_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Lookup_name(service_name, impl_info, port_name);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Publish_name(const char *service_name, WRAP_Info info, const char *port_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Publish_name(service_name, impl_info, port_name);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Unpublish_name(const char *service_name, WRAP_Info info, const char *port_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Unpublish_name(service_name, impl_info, port_name);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Open_port(WRAP_Info info, char *port_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Open_port(impl_info, port_name);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Close_port(const char *port_name)
{
    int rc = IMPL_Close_port(port_name);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}


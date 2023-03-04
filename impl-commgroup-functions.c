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
#include "impl-constant-conversions.h"
#include "impl-handle-conversions.h"
#include "impl-predefined-handle.h"
#include "impl-keyval-map.h"

extern int COMM_EH_HANDLE_KEY;

// WRAP->IMPL functions

// used by WRAP_Comm_create_errhandler

void comm_errhandler_trampoline(MPI_Comm *comm, int *errorcode, ...)
{
    int rc;
    int flag;
    WRAP_Comm_errhandler_function * fp = NULL;
    rc = IMPL_Comm_get_attr(*comm, COMM_EH_HANDLE_KEY, &fp, &flag);
    if (rc != MPI_SUCCESS || !flag) {
        printf("%s: IMPL_Comm_get_attr failed: flag=%d rc=%d\n", __func__, flag, rc);
    }
    WRAP_Comm wrap_comm = OUTPUT_MPI_Comm(*comm);
    (*fp)(&wrap_comm,errorcode);
}

// used by WRAP_Comm_create_keyval

int copy_attr_trampoline(MPI_Comm impl_comm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag)
{
    WRAP_Comm_copy_attr_function * comm_copy_attr_fn;
    int rc = find_comm_keyval_callbacks(comm_keyval, &comm_copy_attr_fn, NULL);
    if (rc==0) {
        printf("%s: find_comm_keyval_callbacks failed for comm_keyval=%d\n",__func__,comm_keyval);
        return MPI_ERR_INTERN;
    }
    if ((intptr_t)comm_copy_attr_fn == (intptr_t)MPI_COMM_NULL_COPY_FN) {
#ifdef DEBUG
        printf("%s: find_comm_keyval_callbacks found MPI_COMM_NULL_COPY_FN for comm_keyval=%d\n",__func__,comm_keyval);
#endif
        *flag = 0;
        return MPI_SUCCESS;
    }
    else if ((intptr_t)comm_copy_attr_fn == (intptr_t)MPI_COMM_DUP_FN) {
#ifdef DEBUG
        printf("%s: find_comm_keyval_callbacks found MPI_COMM_DUP_FN for comm_keyval=%d\n",__func__,comm_keyval);
#endif
        *(void**)attribute_val_out = attribute_val_in;
        *flag = 1;
        return MPI_SUCCESS;
    }
    else {
#ifdef DEBUG
        printf("%s: find_comm_keyval_callbacks found comm_copy_attr_fn=%p for comm_keyval=%d\n",
                __func__,comm_copy_attr_fn,comm_keyval);
#endif
        WRAP_Comm wrap_comm = OUTPUT_MPI_Comm(impl_comm);
        rc = (*comm_copy_attr_fn)(wrap_comm, comm_keyval, extra_state, attribute_val_in, attribute_val_out, flag);
        return RETURN_CODE_MUK_TO_IMPL(rc);
    }
}

int delete_attr_trampoline(MPI_Comm impl_comm, int comm_keyval, void *attribute_val, void *extra_state)
{
    WRAP_Comm_delete_attr_function * comm_delete_attr_fn;
    int rc = find_comm_keyval_callbacks(comm_keyval, NULL, &comm_delete_attr_fn);
    if (rc==0) {
        printf("%s: find_comm_keyval_callbacks failed for comm_keyval=%d\n",__func__,comm_keyval);
        return MPI_ERR_INTERN;
    }
    if ((intptr_t)comm_delete_attr_fn == (intptr_t)MPI_COMM_NULL_DELETE_FN) {
#ifdef DEBUG
        printf("%s: find_comm_keyval_callbacks found MPI_COMM_NULL_DELETE_FN for comm_keyval=%d\n",__func__,comm_keyval);
#endif
        return MPI_SUCCESS;
    }
    else {
#ifdef DEBUG
        printf("%s: find_comm_keyval_callbacks found comm_copy_attr_fn=%p for comm_keyval=%d\n",
                __func__,comm_copy_attr_fn,comm_keyval);
#endif
        WRAP_Comm wrap_comm = OUTPUT_MPI_Comm(impl_comm);
        rc = (*comm_delete_attr_fn)(wrap_comm, comm_keyval, attribute_val, extra_state);
        return RETURN_CODE_MUK_TO_IMPL(rc);
    }
}

int WRAP_Comm_create_errhandler(WRAP_Comm_errhandler_function *comm_errhandler_fn, WRAP_Errhandler *errhandler)
{
    MPI_Errhandler impl_errhandler;
    //int rc = IMPL_Comm_create_errhandler(comm_errhandler_fn, &impl_errhandler);
    int rc = IMPL_Comm_create_errhandler(comm_errhandler_trampoline, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    add_comm_errhandler_callback(impl_errhandler, comm_errhandler_fn);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_set_errhandler(WRAP_Comm comm, WRAP_Errhandler errhandler)
{
    int rc;
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    rc = IMPL_Comm_set_errhandler(impl_comm, impl_errhandler);
    if (!IS_PREDEFINED_ERRHANDLER(impl_errhandler))
    {
        WRAP_Comm_errhandler_function * comm_errhandler_fn;
        if (find_comm_errhandler_callback(impl_errhandler, &comm_errhandler_fn)) {
            rc = IMPL_Comm_set_attr(impl_comm, COMM_EH_HANDLE_KEY, comm_errhandler_fn);
            if (rc) {
                printf("%s: Comm_set_attr failed\n",__func__);
                goto end;
            }
        }
        else {
            printf("%s: lookup_comm_err_pair failed to find a callback for errhandler=%lx\n",
                   __func__, (intptr_t)impl_errhandler);
        }
    }
    end:
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

int WRAP_Comm_call_errhandler(WRAP_Comm comm, int errorcode)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_call_errhandler(impl_comm, errorcode);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if 0
// obsolete versions
// we just map the outer MPI symbols to the new API in libinit.c so we can ignore these.

int WRAP_Errhandler_create(WRAP_Comm_errhandler_function *comm_errhandler_fn, WRAP_Errhandler *errhandler)
{
    MPI_Errhandler impl_errhandler;
    //int rc = IMPL_Errhandler_create(comm_errhandler_fn, &impl_errhandler);
    int rc = IMPL_Errhandler_create(comm_errhandler_trampoline, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Errhandler_set(WRAP_Comm comm, WRAP_Errhandler errhandler)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    int rc = IMPL_Errhandler_set(impl_comm, impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Errhandler_get(WRAP_Comm comm, WRAP_Errhandler *errhandler)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_Errhandler_get(impl_comm, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

// regular functionality

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
    int rc = IMPL_Comm_accept(port_name, impl_info, RANK_MUK_TO_IMPL(root), impl_comm, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
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
    int rc = IMPL_Comm_connect(port_name, impl_info, RANK_MUK_TO_IMPL(root), impl_comm, &impl_newcomm);
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

int WRAP_Comm_create_keyval(WRAP_Comm_copy_attr_function *comm_copy_attr_fn, WRAP_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state)
{
    bool needs_trampoline = false;
    MPI_Comm_copy_attr_function * impl_comm_copy_attr_fn;
    if ((intptr_t)comm_copy_attr_fn == (intptr_t)MUK_COMM_NULL_COPY_FN) {
        impl_comm_copy_attr_fn = MPI_COMM_NULL_COPY_FN;
    }
    else if ((intptr_t)comm_copy_attr_fn == (intptr_t)MUK_COMM_DUP_FN) {
        impl_comm_copy_attr_fn = MPI_COMM_DUP_FN;
    }
    else {
        needs_trampoline = true;
        impl_comm_copy_attr_fn = copy_attr_trampoline;
    }
    MPI_Comm_delete_attr_function * impl_comm_delete_attr_fn;
    if ((intptr_t)comm_delete_attr_fn == (intptr_t)MUK_COMM_NULL_DELETE_FN) {
        impl_comm_delete_attr_fn = MPI_COMM_NULL_DELETE_FN;
    }
    else {
        needs_trampoline = true;
        impl_comm_delete_attr_fn = delete_attr_trampoline;
    }
    int rc = IMPL_Comm_create_keyval(impl_comm_copy_attr_fn, impl_comm_delete_attr_fn, comm_keyval, extra_state);
    if (rc) goto end;
    if (needs_trampoline) {
        int rc = add_comm_keyval_callbacks(*comm_keyval, comm_copy_attr_fn, comm_delete_attr_fn);
        if (rc==0) rc = MPI_ERR_INTERN;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_delete_attr(WRAP_Comm comm, int comm_keyval)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_delete_attr(impl_comm, comm_keyval);
    if (rc) goto end;
    rc = remove_comm_keyval_callbacks(comm_keyval);
    if (rc==0) rc = MPI_ERR_INTERN;
    end:
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
    // MPI_TAG_UB and MPI_WTIME_IS_GLOBAL should not require conversion
    if (comm_keyval == MUK_HOST) {
        **(int**)attribute_val = RANK_IMPL_TO_MUK(**(int**)attribute_val);
    }
    if (comm_keyval == MUK_IO) {
        **(int**)attribute_val = RANK_IMPL_TO_MUK(**(int**)attribute_val);
    }
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_set_attr(WRAP_Comm comm, int comm_keyval, void *attribute_val)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_set_attr(impl_comm, comm_keyval, attribute_val);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if 0
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
#endif

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

int WRAP_Comm_free(WRAP_Comm *comm)
{
    int rc;
    MPI_Comm impl_comm = CONVERT_MPI_Comm(*comm);
    rc = IMPL_Comm_free(&impl_comm);
    *comm = OUTPUT_MPI_Comm(impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_disconnect(WRAP_Comm *comm)
{
    int rc;
    MPI_Comm impl_comm = CONVERT_MPI_Comm(*comm);
    rc = IMPL_Comm_disconnect(&impl_comm);
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

// these are only used below so we leave them here

static inline bool IS_ARGV_NULL(char * argv[])
{
    return ((intptr_t)argv == (intptr_t)MUK_ARGV_NULL);
}

static inline bool IS_ARGVS_NULL(char ** array_of_argv[])
{
    return ((intptr_t)array_of_argv == (intptr_t)MUK_ARGVS_NULL);
}

static inline bool IS_ERRCODES_IGNORE(int * array_of_errcodes)
{
    return ((intptr_t)array_of_errcodes == (intptr_t)MUK_ERRCODES_IGNORE);
}

int WRAP_Comm_spawn(const char *command, char *argv[], int maxprocs, WRAP_Info info, int root, WRAP_Comm comm, WRAP_Comm *intercomm, int * array_of_errcodes)
{
    bool ignore_argv = IS_ARGV_NULL(argv);
    bool ignore_errc = IS_ERRCODES_IGNORE(array_of_errcodes);
    int rc;
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Comm impl_intercomm;
    rc = IMPL_Comm_spawn(command, ignore_argv ? MPI_ARGV_NULL : argv, maxprocs, impl_info, RANK_MUK_TO_IMPL(root), impl_comm, &impl_intercomm, ignore_errc ? MPI_ERRCODES_IGNORE : array_of_errcodes);
    *intercomm = OUTPUT_MPI_Comm(impl_intercomm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_spawn_multiple(int count, char *array_of_commands[], char **array_of_argv[], const int array_of_maxprocs[], const WRAP_Info array_of_info[], int root, WRAP_Comm comm, WRAP_Comm *intercomm, int * array_of_errcodes)
{
    bool ignore_argv = IS_ARGVS_NULL(array_of_argv);
    bool ignore_errc = IS_ERRCODES_IGNORE(array_of_errcodes);
    int rc;
    MPI_Info * impl_array_of_info = calloc(count, sizeof(MPI_Info));
    if (impl_array_of_info == NULL) {
        rc = MPI_ERR_INTERN;
        goto end;
    }
    for (int i=0; i<count; i++) {
         impl_array_of_info[i] = CONVERT_MPI_Info(array_of_info[i]);
    }
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Comm impl_intercomm;
    rc = IMPL_Comm_spawn_multiple(count, array_of_commands, ignore_argv ? MPI_ARGVS_NULL : array_of_argv, array_of_maxprocs, impl_array_of_info, RANK_MUK_TO_IMPL(root), impl_comm, &impl_intercomm, ignore_errc ? MPI_ERRCODES_IGNORE : array_of_errcodes);
    *intercomm = OUTPUT_MPI_Comm(impl_intercomm);
    free(impl_array_of_info);
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

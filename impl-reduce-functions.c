#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include <mpi.h>

//#include "muk-dl.h"
#include "muk-predefined.h"

//#include "impl-scalar-types.h"
//#include "impl-status.h"
//#include "wrap-handle-typedefs.h"

#define MUK_EXTERN extern
#include "impl-fpointers.h"
#include "impl-predefined-handle.h"
#include "impl-constant-conversions.h"
#include "impl-handle-conversions.h"
#include "impl-keyval-map.h"
extern int TYPE_ATTR_FOR_USER_OP_FN;

void reduce_trampoline(void *invec, void *inoutvec, int *len, MPI_Datatype * datatype)
{
    int rc;
    // because this is _only_ called with a dupe of the original type,
    // we can remove that from the cookie and get it this way instead
    MPI_Datatype parent_datatype;
    {
        int ni, na, nd, combiner;
        rc = IMPL_Type_get_envelope(*datatype, &ni, &na, &nd, &combiner);
        if (rc || (ni != 0) || (na != 0) || (nd != 1) || (combiner != MPI_COMBINER_DUP)) {
            printf("%s: IMPL_Type_get_envelope failed to do the right thing"
                   "rc=%d ni=%d na=%d nd=%d combiner=%d\n", __func__, rc, ni, na, nd, combiner);
        }
        rc = IMPL_Type_get_contents(*datatype, ni, na, nd, NULL, NULL, &parent_datatype);
#if 0
        printf("%s: *datatype=%lx parent_datatype=%lx\n", __func__, (intptr_t)*datatype, (intptr_t)parent_datatype);
#endif
    }
    int flag;
    WRAP_User_function* user_fn;
    rc = IMPL_Type_get_attr(*datatype, TYPE_ATTR_FOR_USER_OP_FN, &user_fn, &flag);
    if (rc != MPI_SUCCESS || !flag) {
        printf("%s: IMPL_Type_get_attr failed: flag=%d rc=%d\n", __func__, flag, rc);
        MPI_Abort(MPI_COMM_SELF,rc);
    }
    WRAP_Datatype wrap_type = OUTPUT_MPI_Datatype(parent_datatype);
    (*user_fn)(invec,inoutvec,len,&wrap_type);
    // parent_datatype is derived datatype returned by Type_get_contents and must be freed
    rc = IMPL_Type_free(&parent_datatype);
}

void reduce_trampoline_c(void *invec, void *inoutvec, MPI_Count *len, MPI_Datatype * datatype)
{
    int rc;
    // because this is _only_ called with a dupe of the original type,
    // we can remove that from the cookie and get it this way instead
    MPI_Datatype parent_datatype;
    {
        MPI_Count ni, na, nd, nc;
        int combiner;
        rc = IMPL_Type_get_envelope_c(*datatype, &ni, &na, &nc, &nd, &combiner);
        if (rc || (ni != 0) || (na != 0) || (nc != 0) || (nd != 1) || (combiner != MPI_COMBINER_DUP)) {
            printf("%s: IMPL_Type_get_envelope_c failed to do the right thing"
                   "rc=%d ni=%lld na=%lld nc=%lld nd=%lld combiner=%d\n", __func__,
                    rc, (long long)ni, (long long)na, (long long)nc, (long long)nd, combiner);
        }
        rc = IMPL_Type_get_contents_c(*datatype, ni, na, nc, nd, NULL, NULL, NULL, &parent_datatype);
#if 0
        printf("%s: *datatype=%lx parent_datatype=%lx\n", __func__, (intptr_t)*datatype, (intptr_t)parent_datatype);
#endif
    }
    int flag;
    WRAP_User_function_c* user_fn;
    rc = IMPL_Type_get_attr(*datatype, TYPE_ATTR_FOR_USER_OP_FN, &user_fn, &flag);
    if (rc != MPI_SUCCESS || !flag) {
        printf("%s: IMPL_Type_get_attr failed: flag=%d rc=%d\n", __func__, flag, rc);
        MPI_Abort(MPI_COMM_SELF,rc);
    }
    WRAP_Datatype wrap_type = OUTPUT_MPI_Datatype(parent_datatype);
    (*user_fn)(invec,inoutvec,len,&wrap_type);
    // parent_datatype is derived datatype returned by Type_get_contents and must be freed
    rc = IMPL_Type_free(&parent_datatype);
}

// WRAP->IMPL functions

int WRAP_Op_commutative(WRAP_Op op, int *commute)
{
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Op_commutative(impl_op, commute);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Op_create(WRAP_User_function *user_fn, int commute, WRAP_Op *op)
{
    MPI_Op impl_op;
    int rc = IMPL_Op_create(reduce_trampoline, commute, &impl_op);
    if (rc) goto end;
    *op = OUTPUT_MPI_Op(impl_op);
    add_comm_op_callback(impl_op, user_fn, NULL);
    //if (rc==0) { rc = MPI_ERR_INTERN; }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Op_create_c(WRAP_User_function_c *user_fn, int commute, WRAP_Op *op)
{
    MPI_Op impl_op;
    int rc = IMPL_Op_create_c(reduce_trampoline_c, commute, &impl_op);
    if (rc) goto end;
    *op = OUTPUT_MPI_Op(impl_op);
    add_comm_op_callback(impl_op, NULL, user_fn);
    //if (rc==0) { rc = MPI_ERR_INTERN; }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Op_free(WRAP_Op *op)
{
    MPI_Op impl_op = CONVERT_MPI_Op(*op);
    int rc = IMPL_Op_free(&impl_op);
    *op = OUTPUT_MPI_Op(impl_op);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_local(const void *inbuf, void *inoutbuf, int count, WRAP_Datatype datatype, WRAP_Op op)
{
    const bool in_place = IS_IN_PLACE(inbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce_local(in_place ? MPI_IN_PLACE : inbuf, inoutbuf, count, impl_datatype, impl_op);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Reduce_local(in_place ? MPI_IN_PLACE : inbuf, inoutbuf, count, dup, impl_op);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_local_c(const void *inbuf, void *inoutbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op)
{
    const bool in_place = IS_IN_PLACE(inbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce_local_c(in_place ? MPI_IN_PLACE : inbuf, inoutbuf, count, impl_datatype, impl_op);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Reduce_local_c(in_place ? MPI_IN_PLACE : inbuf, inoutbuf, count, dup, impl_op);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allreduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Allreduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Allreduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allreduce_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Allreduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Allreduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iallreduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Iallreduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Iallreduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iallreduce_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Iallreduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Iallreduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Allreduce_init(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Info     impl_info     = CONVERT_MPI_Info(info);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Allreduce_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Allreduce_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, impl_info, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Allreduce_init_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Info     impl_info     = CONVERT_MPI_Info(info);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Allreduce_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Allreduce_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, impl_info,  &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Reduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, RANK_MUK_TO_IMPL(root), impl_comm);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Reduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, RANK_MUK_TO_IMPL(root), impl_comm);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, RANK_MUK_TO_IMPL(root), impl_comm);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Reduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, RANK_MUK_TO_IMPL(root), impl_comm);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ireduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Ireduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Ireduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ireduce_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Ireduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Ireduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Reduce_init(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Info     impl_info     = CONVERT_MPI_Info(info);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Reduce_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_init_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Info     impl_info     = CONVERT_MPI_Info(info);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Reduce_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce_scatter(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Reduce_scatter(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, dup, impl_op, impl_comm);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_c(const void *sendbuf, void *recvbuf, const WRAP_Count recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce_scatter_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Reduce_scatter_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, dup, impl_op, impl_comm);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ireduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Ireduce_scatter(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Ireduce_scatter(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, dup, impl_op, impl_comm, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ireduce_scatter_c(const void *sendbuf, void *recvbuf, const WRAP_Count recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Ireduce_scatter_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Ireduce_scatter_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, dup, impl_op, impl_comm, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Reduce_scatter_init(const void *sendbuf, void *recvbuf, const int recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Info     impl_info     = CONVERT_MPI_Info(info);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce_scatter_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Reduce_scatter_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, dup, impl_op, impl_comm, impl_info, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Reduce_scatter_init_c(const void *sendbuf, void *recvbuf, const WRAP_Count recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Info     impl_info     = CONVERT_MPI_Info(info);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce_scatter_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Reduce_scatter_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, dup, impl_op, impl_comm, impl_info, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Reduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce_scatter_block(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Reduce_scatter_block(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, dup, impl_op, impl_comm);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_block_c(const void *sendbuf, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce_scatter_block_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Reduce_scatter_block_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, dup, impl_op, impl_comm);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ireduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Ireduce_scatter_block(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Ireduce_scatter_block(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, dup, impl_op, impl_comm, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ireduce_scatter_block_c(const void *sendbuf, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Ireduce_scatter_block_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Ireduce_scatter_block_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, dup, impl_op, impl_comm, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Reduce_scatter_block_init(const void *sendbuf, void *recvbuf, int recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Info     impl_info     = CONVERT_MPI_Info(info);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce_scatter_block_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Reduce_scatter_block_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, dup, impl_op, impl_comm, impl_info, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Reduce_scatter_block_init_c(const void *sendbuf, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Info     impl_info     = CONVERT_MPI_Info(info);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce_scatter_block_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Reduce_scatter_block_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, dup, impl_op, impl_comm, impl_info, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Scan(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Scan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Scan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scan_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Scan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Scan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Iscan(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Iscan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Iscan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iscan_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Iscan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Iscan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Scan_init(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Info     impl_info     = CONVERT_MPI_Info(info);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Scan_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Scan_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, impl_info, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scan_init_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Info     impl_info     = CONVERT_MPI_Info(info);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Scan_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Scan_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, impl_info, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Exscan(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Exscan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Exscan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Exscan_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Exscan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Exscan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Iexscan(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Iexscan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Iexscan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iexscan_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Iexscan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Iexscan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Exscan_init(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Info     impl_info     = CONVERT_MPI_Info(info);
    MPI_Request  impl_request   = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Exscan_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function* user_fn;
        rc = find_comm_op_callback(impl_op, &user_fn, NULL);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Exscan_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, impl_info, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Exscan_init_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op       impl_op       = CONVERT_MPI_Op(op);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Info     impl_info     = CONVERT_MPI_Info(info);
    MPI_Request  impl_request  = MPI_REQUEST_NULL;
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Exscan_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    }
    else {
        MPI_Datatype dup;
        rc = IMPL_Type_dup(impl_datatype,&dup);
        if (rc) goto end;

        WRAP_User_function_c* user_fn;
        rc = find_comm_op_callback(impl_op, NULL, &user_fn);
        if (rc==0) { rc = MPI_ERR_INTERN; goto end; }

        rc = IMPL_Type_set_attr(dup, TYPE_ATTR_FOR_USER_OP_FN, user_fn);
        if (rc) goto end;

        rc = IMPL_Exscan_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, impl_info, &impl_request);
        if (rc) goto end;

        rc = IMPL_Type_free(&dup);
        if (rc) goto end;
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

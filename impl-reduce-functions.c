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
#include "impl-linked-list.h"
#include "impl-constant-conversions.h"
#include "impl-handle-conversions.h"

// impl-functions.c
//extern op_fptr_pair_t    * op_fptr_pair_list;
//extern req_cookie_pair_t * req_cookie_pair_list;

void reduce_trampoline(void *invec, void *inoutvec, int *len, MPI_Datatype * datatype)
{
    int rc;
    int flag;
    reduce_trampoline_cookie_t * cookie = NULL;
    rc = IMPL_Type_get_attr(*datatype, TYPE_HANDLE_KEY, &cookie, &flag);
    if (rc != MPI_SUCCESS || !flag) {
        printf("%s: IMPL_Type_get_attr failed: flag=%d rc=%d\n", __func__, flag, rc);
        MPI_Abort(MPI_COMM_SELF,rc);
    }
    MPI_Datatype         dt = MPI_DATATYPE_NULL;
    WRAP_User_function * fp = NULL;
    if (flag) {
        dt = cookie->dt;
        fp = cookie->fp.fp_i;
    }
    WRAP_Datatype wrap_type = OUTPUT_MPI_Datatype(dt);
    (*fp)(invec,inoutvec,len,&wrap_type);
}

void reduce_trampoline_c(void *invec, void *inoutvec, MPI_Count *len, MPI_Datatype * datatype)
{
    int rc;
    int flag;
    reduce_trampoline_cookie_t * cookie = NULL;
    rc = IMPL_Type_get_attr(*datatype, TYPE_HANDLE_KEY, &cookie, &flag);
    if (rc != MPI_SUCCESS || !flag) {
        printf("%s: IMPL_Type_get_attr failed: flag=%d rc=%d\n", __func__, flag, rc);
        MPI_Abort(MPI_COMM_SELF,rc);
    }
    MPI_Datatype           dt = MPI_DATATYPE_NULL;
    WRAP_User_function_c * fp = NULL;
    if (flag) {
        dt = cookie->dt;
        fp = cookie->fp.fp_c;
    }
    WRAP_Datatype wrap_type = OUTPUT_MPI_Datatype(dt);
    (*fp)(invec,inoutvec,len,&wrap_type);
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
    *op = OUTPUT_MPI_Op(impl_op);
    add_op_pair_to_list(false, impl_op, user_fn, NULL);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Op_create_c(WRAP_User_function_c *user_fn, int commute, WRAP_Op *op)
{
    MPI_Op impl_op;
    int rc = IMPL_Op_create_c(reduce_trampoline_c, commute, &impl_op);
    *op = OUTPUT_MPI_Op(impl_op);
    add_op_pair_to_list(true, impl_op, NULL, user_fn);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Op_free(WRAP_Op *op)
{
    MPI_Op impl_op = CONVERT_MPI_Op(*op);
    remove_op_pair_from_list(impl_op);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce_local(in_place ? MPI_IN_PLACE : inbuf, inoutbuf, count, dup, impl_op);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce_local_c(in_place ? MPI_IN_PLACE : inbuf, inoutbuf, count, dup, impl_op);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Allreduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Allreduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Iallreduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, &impl_request);
        // cleanup
        cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Iallreduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, &impl_request);
        // cleanup
        cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Allreduce_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, impl_info, &impl_request);
        // cleanup
        // FIXME leak everything because otherwise persistent reductions crash.
        //cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Allreduce_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, impl_info,  &impl_request);
        // cleanup
        // FIXME leak everything because otherwise persistent reductions crash.
        //cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, RANK_MUK_TO_IMPL(root), impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, RANK_MUK_TO_IMPL(root), impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Ireduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
        // cleanup
        cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Ireduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
        // cleanup
        cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
        // cleanup
        // FIXME leak everything because otherwise persistent reductions crash.
        //cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
        // cleanup
        // FIXME leak everything because otherwise persistent reductions crash.
        //cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce_scatter(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, dup, impl_op, impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce_scatter_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, dup, impl_op, impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Ireduce_scatter(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, dup, impl_op, impl_comm, &impl_request);
        // cleanup
        cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Ireduce_scatter_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, dup, impl_op, impl_comm, &impl_request);
        // cleanup
        cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce_scatter_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, dup, impl_op, impl_comm, impl_info, &impl_request);
        // cleanup
        // FIXME leak everything because otherwise persistent reductions crash.
        //cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce_scatter_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, dup, impl_op, impl_comm, impl_info, &impl_request);
        // cleanup
        // FIXME leak everything because otherwise persistent reductions crash.
        //cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce_scatter_block(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, dup, impl_op, impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce_scatter_block_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, dup, impl_op, impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Ireduce_scatter_block(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, dup, impl_op, impl_comm, &impl_request);
        // cleanup
        cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Ireduce_scatter_block_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, dup, impl_op, impl_comm, &impl_request);
        // cleanup
        cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce_scatter_block_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, dup, impl_op, impl_comm, impl_info, &impl_request);
        // cleanup
        // FIXME leak everything because otherwise persistent reductions crash.
        //cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce_scatter_block_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, dup, impl_op, impl_comm, impl_info, &impl_request);
        // cleanup
        // FIXME leak everything because otherwise persistent reductions crash.
        //cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Scan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Scan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Iscan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, &impl_request);
        // cleanup
        cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Iscan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, &impl_request);
        // cleanup
        cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Scan_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, impl_info, &impl_request);
        // cleanup
        // FIXME leak everything because otherwise persistent reductions crash.
        //cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Scan_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, impl_info, &impl_request);
        // cleanup
        // FIXME leak everything because otherwise persistent reductions crash.
        //cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Exscan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Exscan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Iexscan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, &impl_request);
        // cleanup
        cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Iexscan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, &impl_request);
        // cleanup
        cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Exscan_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, impl_info, &impl_request);
        // cleanup
        // FIXME leak everything because otherwise persistent reductions crash.
        //cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
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
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, impl_datatype, &dup);
        if (cookie == NULL) {
            printf("%s: cookied failed to bake.\n",__func__);
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Exscan_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, impl_info, &impl_request);
        // cleanup
        // FIXME leak everything because otherwise persistent reductions crash.
        //cleanup_ireduce_trampoline_cookie(cookie, impl_request, &dup);
    }
    end:
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

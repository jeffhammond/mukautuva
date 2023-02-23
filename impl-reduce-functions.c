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
#include "impl-predefined-op.h"
#include "impl-linked-list.h"
#include "impl-constant-conversions.h"
#include "impl-handle-conversions.h"

op_fptr_pair_t * op_fptr_pair_list = NULL;
req_cookie_pair_t * req_cookie_pair_list = NULL;

void trampoline(void *invec, void *inoutvec, int *len, MPI_Datatype * datatype)
{
    int rc;
    (void)rc;
    (void)invec;
    (void)inoutvec;
    (void)len;
    (void)datatype;
#if 0
    int flag;
    reduce_trampoline_cookie_t * cookie = NULL;
    rc = IMPL_Type_get_attr(*datatype, TYPE_HANDLE_KEY, &cookie, &flag);
    if (rc != MPI_SUCCESS || !flag) {
        printf("trampoline: IMPL_Type_get_attr failed: flag=%d rc=%d\n", flag, rc);
        MPI_Abort(MPI_COMM_SELF,rc);
    }
    MPI_Datatype       * dptr = NULL;
    WRAP_User_function * fptr = NULL;
    if (flag) {
        dptr = cookie->dt;
        fptr = cookie->fp;
    }
    (*fptr)(invec,inoutvec,len,&dptr);
#endif
}

void trampoline_c(void *invec, void *inoutvec, MPI_Count *len, MPI_Datatype * datatype)
{
    int rc;
    (void)rc;
    (void)invec;
    (void)inoutvec;
    (void)len;
    (void)datatype;
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
    int rc = IMPL_Op_create(trampoline, commute, &impl_op);
    *op = OUTPUT_MPI_Op(impl_op);
    (void)user_fn;
    //add_op_pair_to_list(user_fn, impl_op);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Op_create_c(WRAP_User_function_c *user_fn, int commute, WRAP_Op *op)
{
    MPI_Op impl_op;
    int rc = IMPL_Op_create_c(trampoline_c, commute, &impl_op);
    *op = OUTPUT_MPI_Op(impl_op);
    (void)user_fn;
    //add_op_pair_to_list(user_fn, impl_op);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Op_free(WRAP_Op *op)
{
    //remove_op_pair_from_list(*op);
    MPI_Op impl_op;
    int rc = IMPL_Op_free(&impl_op);
    *op = OUTPUT_MPI_Op(impl_op);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allreduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Allreduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    }
#if 0
    else {
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(impl_op, datatype, &dup);
        if (cookie == NULL) {
            printf("WRAP_Allreduce: cookie failed to bake.\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Allreduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
    }
    end:
#endif
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allreduce_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Allreduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allreduce_init(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Allreduce_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Allreduce_init_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Allreduce_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Iallreduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Iallreduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
#if 0
    *request = malloc(sizeof(MPI_Request));
    int rc;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Iallreduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    }
    else {
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(op, datatype, &dup);
        if (cookie == NULL) {
            printf("WRAP_Iallreduce: cookie failed to bake.\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Iallreduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, impl_comm, &impl_request);
        // cleanup
        cleanup_ireduce_trampoline_cookie(cookie, *request, &dup);
    }
    end:
    *request = OUTPUT_MPI_REQUEST(impl_request);
#endif
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iallreduce_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Iallreduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ireduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        MPI_Request impl_request;
        rc = IMPL_Ireduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, root, impl_comm, &impl_request);
        *request = OUTPUT_MPI_Request(impl_request);
    }
#if 0
    else {
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(op, datatype, &dup);
        if (cookie == NULL) {
            printf("WRAP_Ireduce: cookie failed to bake.\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        MPI_Request impl_request;
    rc = IMPL_Ireduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, impl_op, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
        // cleanup
        cleanup_ireduce_trampoline_cookie(cookie, *request, &dup);
    }
    end:
#endif
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ireduce_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Ireduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, root, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ireduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Ireduce_scatter(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ireduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Ireduce_scatter_block(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ireduce_scatter_block_c(const void *sendbuf, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Ireduce_scatter_block_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_Ireduce_scatter_c(const void *sendbuf, void *recvbuf, const WRAP_Count recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Ireduce_scatter_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Reduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, RANK_MUK_TO_IMPL(root), impl_comm);
    }
#if 0
    else {
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(op, datatype, &dup);
        if (cookie == NULL) {
            printf("WRAP_Reduce: cookie failed to bake.\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, dup, *op, RANK_MUK_TO_IMPL(root), impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
    }
    end:
#endif
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, root, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_init(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Reduce_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, root, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_init_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Reduce_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, root, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_local(const void *inbuf, void *inoutbuf, int count, WRAP_Datatype datatype, WRAP_Op op)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_local(inbuf, inoutbuf, count, impl_datatype, impl_op);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_local_c(const void *inbuf, void *inoutbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_local_c(inbuf, inoutbuf, count, impl_datatype, impl_op);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_scatter(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_scatter_block(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_block_c(const void *sendbuf, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_scatter_block_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_block_init(const void *sendbuf, void *recvbuf, int recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Reduce_scatter_block_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Reduce_scatter_block_init_c(const void *sendbuf, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Reduce_scatter_block_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Reduce_scatter_c(const void *sendbuf, void *recvbuf, const WRAP_Count recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_scatter_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_init(const void *sendbuf, void *recvbuf, const int recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Reduce_scatter_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Reduce_scatter_init_c(const void *sendbuf, void *recvbuf, const WRAP_Count recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Reduce_scatter_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Iscan(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Iscan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iscan_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Iscan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Exscan(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Exscan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Exscan_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Exscan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Exscan_init(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Exscan_init(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Exscan_init_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Exscan_init_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Iexscan(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Iexscan(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iexscan_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Iexscan_c(in_place ? MPI_IN_PLACE : sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Scan(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Scan(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scan_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Scan_c(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Scan_init(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Scan_init(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scan_init_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Scan_init_c(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif


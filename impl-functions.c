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

#include "impl-scalar-types.h"
#include "wrap-handle-typedefs.h"

#define MUK_EXTERN extern
#include "impl-fpointers.h"
#include "impl-status.h"
#include "impl-predefined-op.h"
#include "impl-linked-list.h"
#include "impl-constant-conversions.h"
#include "impl-handle-conversions.h"
#include "impl-alltoallw.h"

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

int WRAP_Abort(WRAP_Comm comm, int errorcode)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Abort(impl_comm, errorcode);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Add_error_class(int *errorclass)
{
    int rc = IMPL_Add_error_class(errorclass);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Add_error_code(int errorclass, int *errorcode)
{
    int rc = IMPL_Add_error_code(errorclass, errorcode);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Add_error_string(int errorcode, const char *string)
{
    int rc = IMPL_Add_error_string(errorcode, string);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Address(void *location, WRAP_Aint *address)
{
    int rc = IMPL_Address(location, address);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

MPI_Aint WRAP_Aint_add(WRAP_Aint base, WRAP_Aint disp)
{
    int rc = IMPL_Aint_add(base, disp);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

MPI_Aint WRAP_Aint_diff(WRAP_Aint addr1, WRAP_Aint addr2)
{
    int rc = IMPL_Aint_diff(addr1, addr2);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allgather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Allgather(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Allgather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Allgather_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Allgather_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Allgather_init(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Allgather_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Allgather_init_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Allgatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Allgatherv(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Allgatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Allgatherv_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Allgatherv_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Allgatherv_init(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Allgatherv_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Allgatherv_init_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Alloc_mem(WRAP_Aint size, WRAP_Info info, void *baseptr)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Alloc_mem(size, impl_info, baseptr);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allreduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Allreduce(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
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
        rc = IMPL_Allreduce(sendbuf, recvbuf, count, dup, impl_op, impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
    }
    end:
#endif
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allreduce_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Allreduce_c(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allreduce_init(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Allreduce_init(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Allreduce_init_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Allreduce_init_c(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Alltoall(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Alltoall(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Alltoall_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Alltoall_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Alltoall_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Alltoall_init(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Alltoall_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Alltoall_init_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Alltoallv(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Alltoallv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Alltoallv_c(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Alltoallv_init(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Alltoallv_init_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Alltoallv_init_c(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    rc = IMPL_Alltoallw(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm);
    if (sendtypes != NULL) free(impl_sendtypes);
    free(impl_recvtypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Alltoallw_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    rc = IMPL_Alltoallw_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm);
    if (sendtypes != NULL) free(impl_sendtypes);
    free(impl_recvtypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Alltoallw_init(const void *sendbuf, const int sendcounts[], const int sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    MPI_Request impl_request;
    rc = IMPL_Alltoallw_init(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    if (sendtypes != NULL) free(impl_sendtypes);
    free(impl_recvtypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alltoallw_init_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    MPI_Request impl_request;
    rc = IMPL_Alltoallw_init_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    if (sendtypes != NULL) free(impl_sendtypes);
    free(impl_recvtypes);
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
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Attr_put(WRAP_Comm comm, int keyval, void *attribute_val)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Attr_put(impl_comm, keyval, attribute_val);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Barrier(WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Barrier(impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Barrier_init(WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Barrier_init(impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Bcast(void *buffer, int count, WRAP_Datatype datatype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Bcast(buffer, count, impl_datatype, root, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Bcast_c(void *buffer, WRAP_Count count, WRAP_Datatype datatype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Bcast_c(buffer, count, impl_datatype, root, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Bcast_init(void *buffer, int count, WRAP_Datatype datatype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Bcast_init(buffer, count, impl_datatype, root, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Bcast_init_c(void *buffer, WRAP_Count count, WRAP_Datatype datatype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Bcast_init_c(buffer, count, impl_datatype, root, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Bsend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Bsend(buf, count, impl_datatype, dest, tag, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Bsend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Bsend_c(buf, count, impl_datatype, dest, tag, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Bsend_init(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Bsend_init(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Bsend_init_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Bsend_init_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Buffer_attach(void *buffer, int size)
{
    int rc = IMPL_Buffer_attach(buffer, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Buffer_attach_c(void *buffer, WRAP_Count size)
{
    int rc = IMPL_Buffer_attach_c(buffer, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Buffer_detach(void *buffer_addr, int *size)
{
    int rc = IMPL_Buffer_detach(buffer_addr, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Buffer_detach_c(void *buffer_addr, WRAP_Count *size)
{
    int rc = IMPL_Buffer_detach_c(buffer_addr, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

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
    int rc = IMPL_Cart_shift(impl_comm, direction, disp, rank_source, rank_dest);
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

int WRAP_Close_port(const char *port_name)
{
    int rc = IMPL_Close_port(port_name);
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

#if 0
int WRAP_Comm_create_errhandler(WRAP_Comm_errhandler_function *comm_errhandler_fn, WRAP_Errhandler *errhandler)
{
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_Comm_create_errhandler(comm_errhandler_fn, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

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

#if 0
int WRAP_Comm_create_keyval(WRAP_Comm_copy_attr_function *comm_copy_attr_fn, WRAP_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state)
{
    int rc = IMPL_Comm_create_keyval(comm_copy_attr_fn, comm_delete_attr_fn, comm_keyval, extra_state);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Comm_delete_attr(WRAP_Comm comm, int comm_keyval)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_delete_attr(impl_comm, comm_keyval);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_disconnect(WRAP_Comm *comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(*comm);
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
    int rc = IMPL_Comm_free(&impl_comm);
    *comm = OUTPUT_MPI_Comm(impl_comm);
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
    int rc = IMPL_Comm_get_attr(impl_comm, comm_keyval, attribute_val, flag);
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

int WRAP_Comm_set_attr(WRAP_Comm comm, int comm_keyval, void *attribute_val)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_set_attr(impl_comm, comm_keyval, attribute_val);
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

int WRAP_Dist_graph_create(WRAP_Comm comm_old, int n, const int sources[], const int degrees[], const int destinations[], const int weights[], WRAP_Info info, int reorder, WRAP_Comm *comm_dist_graph)
{
    MPI_Comm impl_comm_old = CONVERT_MPI_Comm(comm_old);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_comm_dist_graph;
    int rc = IMPL_Dist_graph_create(impl_comm_old, n, sources, degrees, destinations, weights, impl_info, reorder, &impl_comm_dist_graph);
    *comm_dist_graph = OUTPUT_MPI_Comm(impl_comm_dist_graph);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dist_graph_create_adjacent(WRAP_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], WRAP_Info info, int reorder, WRAP_Comm *comm_dist_graph)
{
    MPI_Comm impl_comm_old = CONVERT_MPI_Comm(comm_old);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_comm_dist_graph;
    int rc = IMPL_Dist_graph_create_adjacent(impl_comm_old, indegree, sources, sourceweights, outdegree, destinations, destweights, impl_info, reorder, &impl_comm_dist_graph);
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

#if 0
int WRAP_Errhandler_create(WRAP_Comm_errhandler_function *comm_errhandler_fn, WRAP_Errhandler *errhandler)
{
    int rc = IMPL_Errhandler_create(comm_errhandler_fn, errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Errhandler_free(WRAP_Errhandler *errhandler)
{
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_Errhandler_free(&impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
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

int WRAP_Errhandler_set(WRAP_Comm comm, WRAP_Errhandler errhandler)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    int rc = IMPL_Errhandler_set(impl_comm, impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Error_class(int errorcode, int *errorclass)
{
    int rc = IMPL_Error_class(errorcode, errorclass);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Error_string(int errorcode, char *string, int *resultlen)
{
    int rc = IMPL_Error_string(errorcode, string, resultlen);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Exscan(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Exscan(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Exscan_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Exscan_c(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Exscan_init(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Exscan_init(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Exscan_init_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Exscan_init_c(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Free_mem(void *base)
{
    int rc = IMPL_Free_mem(base);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Gather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Gather(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Gather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Gather_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Gather_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Gather_init(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Gather_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Gather_init_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Gatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Gatherv(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, root, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Gatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Gatherv_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, root, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Gatherv_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Gatherv_init(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, root, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Gatherv_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Gatherv_init_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, root, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Get_address(const void *location, WRAP_Aint *address)
{
    int rc = IMPL_Get_address(location, address);
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
    int rc = IMPL_Graph_map(impl_comm, nnodes, indx, edges, newrank);
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

int WRAP_Grequest_complete(WRAP_Request request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(request);
    int rc = IMPL_Grequest_complete(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if 0
int WRAP_Grequest_start(WRAP_Grequest_query_function *query_fn, WRAP_Grequest_free_function *free_fn, WRAP_Grequest_cancel_function *cancel_fn, void *extra_state, WRAP_Request *request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(*request);
    int rc = IMPL_Grequest_start(query_fn, free_fn, cancel_fn, extra_state, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

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
    MPI_Group impl_group1 = CONVERT_MPI_Group(group1);
    MPI_Group impl_group2 = CONVERT_MPI_Group(group2);
    int rc = IMPL_Group_translate_ranks(impl_group1, n, ranks1, impl_group2, ranks2);
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

int WRAP_Iallgather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Iallgather(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iallgather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Iallgather_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Iallgatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Iallgatherv(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iallgatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Iallgatherv_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Iallreduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Iallreduce(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
#if 0
    *request = malloc(sizeof(MPI_Request));
    int rc;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Iallreduce(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
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
        rc = IMPL_Iallreduce(sendbuf, recvbuf, count, dup, impl_op, impl_comm, &impl_request);
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
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Iallreduce_c(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ialltoall(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Ialltoall(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ialltoall_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Ialltoall_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ialltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Ialltoallv(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ialltoallv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Ialltoallv_c(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ialltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Ialltoallw(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // THIS IS ILLEGAL - FIX IT
    //if (sendtypes != NULL) free(impl_sendtypes);
    //free(impl_recvtypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ialltoallw_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Ialltoallw_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // THIS IS ILLEGAL - FIX IT
    //if (sendtypes != NULL) free(impl_sendtypes);
    //free(impl_recvtypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ibarrier(WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ibarrier(impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ibcast(void *buffer, int count, WRAP_Datatype datatype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Ibcast(buffer, count, impl_datatype, root, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ibcast_c(void *buffer, WRAP_Count count, WRAP_Datatype datatype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Ibcast_c(buffer, count, impl_datatype, root, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ibsend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Ibsend(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ibsend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Ibsend_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Iexscan(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Iexscan(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iexscan_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Iexscan_c(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Igather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Igather(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Igather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Igather_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Igatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Igatherv(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, root, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Igatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Igatherv_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, root, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Improbe(int source, int tag, WRAP_Comm comm, int *flag, WRAP_Message *message, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Message impl_message;
    MPI_Status impl_status;
    int rc = IMPL_Improbe(RANK_MUK_TO_IMPL(source), tag, impl_comm, flag, &impl_message, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    *message = OUTPUT_MPI_Message(impl_message);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Imrecv(void *buf, int count, WRAP_Datatype datatype, WRAP_Message *message, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Message impl_message;
    MPI_Request impl_request;
    int rc = IMPL_Imrecv(buf, count, impl_datatype, &impl_message, &impl_request);
    *message = OUTPUT_MPI_Message(impl_message);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Imrecv_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Message *message, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Message impl_message;
    MPI_Request impl_request;
    int rc = IMPL_Imrecv_c(buf, count, impl_datatype, &impl_message, &impl_request);
    *message = OUTPUT_MPI_Message(impl_message);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_allgather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_allgather(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ineighbor_allgather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_allgather_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ineighbor_allgatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_allgatherv(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ineighbor_allgatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_allgatherv_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ineighbor_alltoall(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_alltoall(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ineighbor_alltoall_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_alltoall_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ineighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_alltoallv(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ineighbor_alltoallv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_alltoallv_c(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ineighbor_alltoallw(const void *sendbuf, const int sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Ineighbor_alltoallw(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // THIS IS ILLEGAL - FIX IT
    //if (sendtypes != NULL) free(impl_sendtypes);
    //free(impl_recvtypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_alltoallw_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Ineighbor_alltoallw_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // THIS IS ILLEGAL - FIX IT
    //if (sendtypes != NULL) free(impl_sendtypes);
    //free(impl_recvtypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_create(WRAP_Info *info)
{
    MPI_Info impl_info;
    int rc = IMPL_Info_create(&impl_info);
    *info = OUTPUT_MPI_Info(impl_info);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_create_env(int argc, char *argv[], WRAP_Info *info)
{
    MPI_Info impl_info;
    int rc = IMPL_Info_create_env(argc, argv, &impl_info);
    *info = OUTPUT_MPI_Info(impl_info);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_delete(WRAP_Info info, const char *key)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Info_delete(impl_info, key);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_dup(WRAP_Info info, WRAP_Info *newinfo)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Info impl_newinfo;
    int rc = IMPL_Info_dup(impl_info, &impl_newinfo);
    *newinfo = OUTPUT_MPI_Info(impl_newinfo);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_free(WRAP_Info *info)
{
    MPI_Info impl_info = CONVERT_MPI_Info(*info);
    int rc = IMPL_Info_free(&impl_info);
    *info = OUTPUT_MPI_Info(impl_info);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get(WRAP_Info info, const char *key, int valuelen, char *value, int *flag)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Info_get(impl_info, key, valuelen, value, flag);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get_nkeys(WRAP_Info info, int *nkeys)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Info_get_nkeys(impl_info, nkeys);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get_nthkey(WRAP_Info info, int n, char *key)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Info_get_nthkey(impl_info, n, key);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get_string(WRAP_Info info, const char *key, int *buflen, char *value, int *flag)
{
    int rc;
#if MPI_VERSION >= 4
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    rc = IMPL_Info_get_string(impl_info, key, buflen, value, flag);
#else
    printf("MPI_Info_get_string is missing\n");
    (void)info;
    (void)key;
    (void)buflen;
    (void)value;
    (void)flag;
    rc = MPI_ERR_INTERN;
#endif
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get_valuelen(WRAP_Info info, const char *key, int *valuelen, int *flag)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Info_get_valuelen(impl_info, key, valuelen, flag);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_set(WRAP_Info info, const char *key, const char *value)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Info_set(impl_info, key, value);
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

int WRAP_Iprobe(int source, int tag, WRAP_Comm comm, int *flag, WRAP_Status *status)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_Iprobe(RANK_MUK_TO_IMPL(source), tag, impl_comm, flag, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Irecv(void *buf, int count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Irecv(buf, count, impl_datatype, RANK_MUK_TO_IMPL(source), tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Irecv_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Irecv_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(source), tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ireduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        MPI_Request impl_request;
        rc = IMPL_Ireduce(sendbuf, recvbuf, count, impl_datatype, impl_op, root, impl_comm, &impl_request);
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
    rc = IMPL_Ireduce(sendbuf, recvbuf, count, dup, impl_op, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
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
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Ireduce_c(sendbuf, recvbuf, count, impl_datatype, impl_op, root, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ireduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Ireduce_scatter(sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ireduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Ireduce_scatter_block(sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ireduce_scatter_block_c(const void *sendbuf, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Ireduce_scatter_block_c(sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_Ireduce_scatter_c(const void *sendbuf, void *recvbuf, const WRAP_Count recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Ireduce_scatter_c(sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Irsend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Irsend(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Irsend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Irsend_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Iscan(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Iscan(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iscan_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Iscan_c(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Iscatter(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Iscatter(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iscatter_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Iscatter_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Iscatterv(const void *sendbuf, const int sendcounts[], const int displs[], WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Iscatterv(sendbuf, sendcounts, displs, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iscatterv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint displs[], WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Iscatterv_c(sendbuf, sendcounts, displs, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Isend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Isend(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Isend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Isend_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Isendrecv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int source, int recvtag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Isendrecv(sendbuf, sendcount, impl_sendtype, dest, sendtag, recvbuf, recvcount, impl_recvtype, source, recvtag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Isendrecv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, int dest, int sendtag, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int source, int recvtag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Isendrecv_c(sendbuf, sendcount, impl_sendtype, dest, sendtag, recvbuf, recvcount, impl_recvtype, source, recvtag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Isendrecv_replace(void *buf, int count, WRAP_Datatype datatype, int dest, int sendtag, int source, int recvtag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Isendrecv_replace(buf, count, impl_datatype, dest, sendtag, source, recvtag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Isendrecv_replace_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int sendtag, int source, int recvtag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Isendrecv_replace_c(buf, count, impl_datatype, dest, sendtag, source, recvtag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Issend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Issend(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Issend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Issend_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

#if 0
int WRAP_Keyval_create(WRAP_Copy_function *copy_fn, WRAP_Delete_function *delete_fn, int *keyval, void *extra_state)
{
    int rc = IMPL_Keyval_create(copy_fn, delete_fn, keyval, extra_state);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Keyval_free(int *keyval)
{
    int rc = IMPL_Keyval_free(keyval);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Lookup_name(const char *service_name, WRAP_Info info, char *port_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Lookup_name(service_name, impl_info, port_name);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Mprobe(int source, int tag, WRAP_Comm comm, WRAP_Message *message, WRAP_Status *status)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Message impl_message;
    MPI_Status impl_status;
    int rc = IMPL_Mprobe(RANK_MUK_TO_IMPL(source), tag, impl_comm, &impl_message, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    *message = OUTPUT_MPI_Message(impl_message);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Mrecv(void *buf, int count, WRAP_Datatype datatype, WRAP_Message *message, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Message impl_message;
    MPI_Status impl_status;
    int rc = IMPL_Mrecv(buf, count, impl_datatype, &impl_message, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    *message = OUTPUT_MPI_Message(impl_message);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Mrecv_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Message *message, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Message impl_message;
    MPI_Status impl_status;
    int rc = IMPL_Mrecv_c(buf, count, impl_datatype, &impl_message, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    *message = OUTPUT_MPI_Message(impl_message);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_allgather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_allgather(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_allgather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_allgather_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_allgather_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_allgather_init(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_allgather_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_allgather_init_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_allgatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_allgatherv(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_allgatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_allgatherv_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_allgatherv_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_allgatherv_init(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_allgatherv_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_allgatherv_init_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_alltoall(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_alltoall(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_alltoall_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_alltoall_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_alltoall_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_alltoall_init(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_alltoall_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_alltoall_init_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_alltoallv(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_alltoallv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_alltoallv_c(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_alltoallv_init(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_alltoallv_init_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_alltoallv_init_c(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    rc = IMPL_Neighbor_alltoallw(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm);
    if (sendtypes != NULL) free(impl_sendtypes);
    free(impl_recvtypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoallw_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    rc = IMPL_Neighbor_alltoallw_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm);
    if (sendtypes != NULL) free(impl_sendtypes);
    free(impl_recvtypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoallw_init(const void *sendbuf, const int sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Neighbor_alltoallw_init(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // THIS IS ILLEGAL - FIX IT
    //if (sendtypes != NULL) free(impl_sendtypes);
    //free(impl_recvtypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoallw_init_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Neighbor_alltoallw_init_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // THIS IS ILLEGAL - FIX IT
    //if (sendtypes != NULL) free(impl_sendtypes);
    //free(impl_recvtypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

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

int WRAP_Open_port(WRAP_Info info, char *port_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Open_port(impl_info, port_name);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pack(const void *inbuf, int incount, WRAP_Datatype datatype, void *outbuf, int outsize, int *position, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack(inbuf, incount, impl_datatype, outbuf, outsize, position, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Pack_c(const void *inbuf, WRAP_Count incount, WRAP_Datatype datatype, void *outbuf, WRAP_Count outsize, WRAP_Count *position, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack_c(inbuf, incount, impl_datatype, outbuf, outsize, position, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Pack_external(const char *datarep, const void *inbuf, int incount, WRAP_Datatype datatype, void *outbuf, WRAP_Aint outsize, WRAP_Aint *position)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack_external(datarep, inbuf, incount, impl_datatype, outbuf, outsize, position);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Pack_external_c(const char *datarep, const void *inbuf, WRAP_Count incount, WRAP_Datatype datatype, void *outbuf, WRAP_Count outsize, WRAP_Count *position)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack_external_c(datarep, inbuf, incount, impl_datatype, outbuf, outsize, position);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Pack_external_size(const char *datarep, int incount, WRAP_Datatype datatype, WRAP_Aint *size)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack_external_size(datarep, incount, impl_datatype, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Pack_external_size_c(const char *datarep, WRAP_Count incount, WRAP_Datatype datatype, WRAP_Count *size)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack_external_size_c(datarep, incount, impl_datatype, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Pack_size(int incount, WRAP_Datatype datatype, WRAP_Comm comm, int *size)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack_size(incount, impl_datatype, impl_comm, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Pack_size_c(WRAP_Count incount, WRAP_Datatype datatype, WRAP_Comm comm, WRAP_Count *size)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack_size_c(incount, impl_datatype, impl_comm, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Parrived(WRAP_Request request, int partition, int *flag)
{
    MPI_Request impl_request = CONVERT_MPI_Request(request);
    int rc = IMPL_Parrived(impl_request, partition, flag);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pcontrol(const int level, ...)
{
    int rc = IMPL_Pcontrol(level);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pready(int partition, WRAP_Request request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(request);
    int rc = IMPL_Pready(partition, impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pready_list(int length, const int array_of_partitions[], WRAP_Request request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(request);
    int rc = IMPL_Pready_list(length, array_of_partitions, impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pready_range(int partition_low, int partition_high, WRAP_Request request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(request);
    int rc = IMPL_Pready_range(partition_low, partition_high, impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Precv_init(void *buf, int partitions, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Precv_init(buf, partitions, count, impl_datatype, dest, tag, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Probe(int source, int tag, WRAP_Comm comm, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Status impl_status;
    int rc = IMPL_Probe(source, tag, impl_comm, &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Psend_init(const void *buf, int partitions, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Psend_init(buf, partitions, count, impl_datatype, dest, tag, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Publish_name(const char *service_name, WRAP_Info info, const char *port_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Publish_name(service_name, impl_info, port_name);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Recv(void *buf, int count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status;
    int rc = IMPL_Recv(buf, count, impl_datatype, source, tag, impl_comm, &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Recv_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Status *status)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_Recv_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(source), tag, impl_comm, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Recv_init(void *buf, int count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Recv_init(buf, count, impl_datatype, source, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Recv_init_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Recv_init_c(buf, count, impl_datatype, source, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Reduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = MPI_SUCCESS;
    if (IS_PREDEFINED_OP(impl_op)) {
        rc = IMPL_Reduce(sendbuf, recvbuf, count, impl_datatype, impl_op, RANK_MUK_TO_IMPL(root), impl_comm);
    }
#if 0
    else {
        // bake the cookie
        MPI_Datatype dup;
        reduce_trampoline_cookie_t * cookie = bake_reduce_trampoline_cookie(op, datatype, &dup);
        if (cookie == NULL) {
            printf("WRAP_Allreduce: cookie failed to bake.\n");
            rc = MPI_ERR_INTERN;
            goto end;
        }
        // do the reduction
        rc = IMPL_Reduce(sendbuf, recvbuf, count, dup, *op, RANK_MUK_TO_IMPL(root), impl_comm);
        // cleanup
        cleanup_reduce_trampoline_cookie(cookie, &dup);
    }
    end:
#endif
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_c(sendbuf, recvbuf, count, impl_datatype, impl_op, root, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_init(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Reduce_init(sendbuf, recvbuf, count, impl_datatype, impl_op, root, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_init_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Reduce_init_c(sendbuf, recvbuf, count, impl_datatype, impl_op, root, impl_comm, impl_info, &impl_request);
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
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_scatter(sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_scatter_block(sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_block_c(const void *sendbuf, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_scatter_block_c(sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_block_init(const void *sendbuf, void *recvbuf, int recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Reduce_scatter_block_init(sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Reduce_scatter_block_init_c(const void *sendbuf, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Reduce_scatter_block_init_c(sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Reduce_scatter_c(const void *sendbuf, void *recvbuf, const WRAP_Count recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_scatter_c(sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_init(const void *sendbuf, void *recvbuf, const int recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Reduce_scatter_init(sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Reduce_scatter_init_c(const void *sendbuf, void *recvbuf, const WRAP_Count recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Reduce_scatter_init_c(sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

#if 0
int WRAP_Register_datarep(const char *datarep, WRAP_Datarep_conversion_function *read_conversion_fn, WRAP_Datarep_conversion_function *write_conversion_fn, WRAP_Datarep_extent_function *dtype_file_extent_fn, void *extra_state)
{
    int rc = IMPL_Register_datarep(datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Register_datarep_c(const char *datarep, WRAP_Datarep_conversion_function_c *read_conversion_fn, WRAP_Datarep_conversion_function_c *write_conversion_fn, WRAP_Datarep_extent_function *dtype_file_extent_fn, void *extra_state)
{
    int rc = IMPL_Register_datarep_c(datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif
#endif

int WRAP_Rsend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Rsend(buf, count, impl_datatype, dest, tag, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Rsend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Rsend_c(buf, count, impl_datatype, dest, tag, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Rsend_init(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Rsend_init(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Rsend_init_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Rsend_init_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
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

int WRAP_Scatter(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Scatter(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scatter_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Scatter_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Scatter_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Scatter_init(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scatter_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Scatter_init_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Scatterv(sendbuf, sendcounts, displs, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scatterv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint displs[], WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Scatterv_c(sendbuf, sendcounts, displs, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Scatterv_init(const void *sendbuf, const int sendcounts[], const int displs[], WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Scatterv_init(sendbuf, sendcounts, displs, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scatterv_init_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint displs[], WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Scatterv_init_c(sendbuf, sendcounts, displs, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Send(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Send(buf, count, impl_datatype, dest, tag, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Send_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Send_c(buf, count, impl_datatype, dest, tag, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Send_init(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Send_init(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Send_init_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Send_init_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Sendrecv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int source, int recvtag, WRAP_Comm comm, WRAP_Status *status)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_Sendrecv(sendbuf, sendcount, impl_sendtype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(sendtag), recvbuf, recvcount, impl_recvtype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(recvtag), impl_comm, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Sendrecv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, int dest, int sendtag, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int source, int recvtag, WRAP_Comm comm, WRAP_Status *status)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_Sendrecv_c(sendbuf, sendcount, impl_sendtype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(sendtag), recvbuf, recvcount, impl_recvtype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(recvtag), impl_comm, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Sendrecv_replace(void *buf, int count, WRAP_Datatype datatype, int dest, int sendtag, int source, int recvtag, WRAP_Comm comm, WRAP_Status *status)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_Sendrecv_replace(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(sendtag), RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(recvtag), impl_comm, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Sendrecv_replace_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int sendtag, int source, int recvtag, WRAP_Comm comm, WRAP_Status *status)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_Sendrecv_replace_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(sendtag), RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(recvtag), impl_comm, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Session_call_errhandler(WRAP_Session session, int errorcode)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    int rc = IMPL_Session_call_errhandler(impl_session, errorcode);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if 0
int WRAP_Session_create_errhandler(WRAP_Session_errhandler_function *session_errhandler_fn, WRAP_Errhandler *errhandler)
{
    int rc = IMPL_Session_create_errhandler(session_errhandler_fn, errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Session_finalize(WRAP_Session *session)
{
    MPI_Session impl_session = CONVERT_MPI_Session(*session);
    int rc = IMPL_Session_finalize(&impl_session);
    *session = OUTPUT_MPI_Session(impl_session);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_errhandler(WRAP_Session session, WRAP_Errhandler *errhandler)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_Session_get_errhandler(impl_session, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_info(WRAP_Session session, WRAP_Info *info_used)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    MPI_Info impl_info_used;
    int rc = IMPL_Session_get_info(impl_session, &impl_info_used);
    *info_used = OUTPUT_MPI_Info(impl_info_used);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_nth_pset(WRAP_Session session, WRAP_Info info, int n, int *pset_len, char *pset_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    int rc = IMPL_Session_get_nth_pset(impl_session, impl_info, n, pset_len, pset_name);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_num_psets(WRAP_Session session, WRAP_Info info, int *npset_names)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    int rc = IMPL_Session_get_num_psets(impl_session, impl_info, npset_names);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_pset_info(WRAP_Session session, const char *pset_name, WRAP_Info *info)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    MPI_Info impl_info;
    int rc = IMPL_Session_get_pset_info(impl_session, pset_name, &impl_info);
    *info = OUTPUT_MPI_Info(impl_info);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_init(WRAP_Info info, WRAP_Errhandler errhandler, WRAP_Session *session)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    MPI_Session impl_session = CONVERT_MPI_Session(*session);
    int rc = IMPL_Session_init(impl_info, impl_errhandler, &impl_session);
    *session = OUTPUT_MPI_Session(impl_session);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_set_errhandler(WRAP_Session session, WRAP_Errhandler errhandler)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    int rc = IMPL_Session_set_errhandler(impl_session, impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ssend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Ssend(buf, count, impl_datatype, dest, tag, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ssend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Ssend_c(buf, count, impl_datatype, dest, tag, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ssend_init(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Ssend_init(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ssend_init_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Ssend_init_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Topo_test(WRAP_Comm comm, int *status)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Topo_test(impl_comm, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, WRAP_Datatype datatype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Unpack(inbuf, insize, position, outbuf, outcount, impl_datatype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Unpack_c(const void *inbuf, WRAP_Count insize, WRAP_Count *position, void *outbuf, WRAP_Count outcount, WRAP_Datatype datatype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Unpack_c(inbuf, insize, position, outbuf, outcount, impl_datatype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Unpack_external(const char datarep[], const void *inbuf, WRAP_Aint insize, WRAP_Aint *position, void *outbuf, int outcount, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Unpack_external(datarep, inbuf, insize, position, outbuf, outcount, impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Unpack_external_c(const char datarep[], const void *inbuf, WRAP_Count insize, WRAP_Count *position, void *outbuf, WRAP_Count outcount, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Unpack_external_c(datarep, inbuf, insize, position, outbuf, outcount, impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Unpublish_name(const char *service_name, WRAP_Info info, const char *port_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Unpublish_name(service_name, impl_info, port_name);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

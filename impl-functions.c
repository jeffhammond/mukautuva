#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include <mpi.h>
typedef ptrdiff_t WRAP_Aint;
typedef ptrdiff_t WRAP_Count;
typedef ptrdiff_t WRAP_Offset;
typedef MPI_Aint   IMPL_Aint;
typedef MPI_Count  IMPL_Count;
typedef MPI_Offset IMPL_Offset;

//#include "muk-dl.h"
#include "muk-predefined.h"

#include "wrap-handle-typedefs.h"

#define MUK_EXTERN extern
#include "impl-fpointers.h"
#include "impl-status.h"
#include "impl-predefined-op.h"
#include "impl-linked-list.h"
#include "impl-constant-conversions.h"
#include "impl-handle-conversions.h"
#include "impl-alltoallw.h"

void trampoline(void *invec, void *inoutvec, int *len, MPI_Datatype * datatype)
{
    int rc;
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
}

// WRAP->IMPL functions

int WRAP_Abort(WRAP_Comm comm, int errorcode)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Abort(impl_comm, errorcode);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Accumulate(const void *origin_addr, int origin_count, WRAP_Datatype origin_datatype, int target_rank, IMPL_Aint target_disp, int target_count, WRAP_Datatype target_datatype, WRAP_Op op, WRAP_Win win)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Accumulate(origin_addr, origin_count, impl_origin_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_op, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Accumulate_c(const void *origin_addr, WRAP_Count origin_count, WRAP_Datatype origin_datatype, int target_rank, WRAP_Aint target_disp, WRAP_Count target_count, WRAP_Datatype target_datatype, WRAP_Op op, WRAP_Win win)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Accumulate_c(origin_addr, origin_count, impl_origin_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_op, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

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

int WRAP_Address(void *location, WRAP_Aint *address)
{
    int rc = IMPL_Address(location, address);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

MPI_Aint WRAP_Aint_add(WRAP_Aint base, WRAP_Aint disp)
{
    int rc = IMPL_Aint_add(base, disp);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

MPI_Aint WRAP_Aint_diff(WRAP_Aint addr1, WRAP_Aint addr2)
{
    int rc = IMPL_Aint_diff(addr1, addr2);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allgather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Allgather(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Allgather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Allgather_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Allgatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Allgatherv(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Allgatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Allgatherv_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Alloc_mem(WRAP_Aint size, WRAP_Info info, void *baseptr)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Alloc_mem(size, impl_info, baseptr);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allreduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc;
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Allreduce_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Allreduce_c(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Alltoall(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Alltoall(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Alltoall_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Alltoall_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Alltoallv(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Alltoallv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Alltoallv_c(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    rc = IMPL_Alltoallw(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm);
    if (sendtypes != NULL) free(impl_sendtypes);
    free(impl_recvtypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    rc = IMPL_Alltoallw_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm);
    if (sendtypes != NULL) free(impl_sendtypes);
    free(impl_recvtypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Attr_delete(WRAP_Comm comm, int keyval)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Attr_delete(impl_comm, keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Attr_get(WRAP_Comm comm, int keyval, void *attribute_val, int *flag)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Attr_get(impl_comm, keyval, attribute_val, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Attr_put(WRAP_Comm comm, int keyval, void *attribute_val)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Attr_put(impl_comm, keyval, attribute_val);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Barrier(WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Barrier(impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Barrier_init(WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Barrier_init(impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Bcast(void *buffer, int count, WRAP_Datatype datatype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Bcast(buffer, count, impl_datatype, root, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Bcast_c(void *buffer, WRAP_Count count, WRAP_Datatype datatype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Bcast_c(buffer, count, impl_datatype, root, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Bsend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Bsend(buf, count, impl_datatype, dest, tag, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Bsend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Bsend_c(buf, count, impl_datatype, dest, tag, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Bsend_init(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Bsend_init(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Bsend_init_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Bsend_init_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Buffer_attach(void *buffer, int size)
{
    int rc = IMPL_Buffer_attach(buffer, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Buffer_attach_c(void *buffer, WRAP_Count size)
{
    int rc = IMPL_Buffer_attach_c(buffer, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Buffer_detach(void *buffer_addr, int *size)
{
    int rc = IMPL_Buffer_detach(buffer_addr, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Buffer_detach_c(void *buffer_addr, WRAP_Count *size)
{
    int rc = IMPL_Buffer_detach_c(buffer_addr, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Cancel(WRAP_Request *request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(*request);
    int rc = IMPL_Cancel(&impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // It is erroneous to call MPI_REQUEST_FREE or MPI_CANCEL for a request
    // associated with a nonblocking collective operation.
    //remove_cookie_pair_from_list(*request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_coords(WRAP_Comm comm, int rank, int maxdims, int coords[])
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Cart_coords(impl_comm, rank, maxdims, coords);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_create(WRAP_Comm comm_old, int ndims, const int dims[], const int periods[], int reorder, WRAP_Comm *comm_cart)
{
    MPI_Comm impl_comm_old = CONVERT_MPI_Comm(comm_old);
    MPI_Comm impl_comm_cart;
    int rc = IMPL_Cart_create(impl_comm_old, ndims, dims, periods, reorder, &impl_comm_cart);
    *comm_cart = OUTPUT_MPI_Comm(impl_comm_cart);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_get(WRAP_Comm comm, int maxdims, int dims[], int periods[], int coords[])
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Cart_get(impl_comm, maxdims, dims, periods, coords);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_map(WRAP_Comm comm, int ndims, const int dims[], const int periods[], int *newrank)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Cart_map(impl_comm, ndims, dims, periods, newrank);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_rank(WRAP_Comm comm, const int coords[], int *rank)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Cart_rank(impl_comm, coords, rank);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_shift(WRAP_Comm comm, int direction, int disp, int *rank_source, int *rank_dest)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Cart_shift(impl_comm, direction, disp, rank_source, rank_dest);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cart_sub(WRAP_Comm comm, const int remain_dims[], WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Cart_sub(impl_comm, remain_dims, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Cartdim_get(WRAP_Comm comm, int *ndims)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Cartdim_get(impl_comm, ndims);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Close_port(const char *port_name)
{
    int rc = IMPL_Close_port(port_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_accept(const char *port_name, WRAP_Info info, int root, WRAP_Comm comm, WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_accept(port_name, impl_info, root, impl_comm, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_call_errhandler(WRAP_Comm comm, int errorcode)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_call_errhandler(impl_comm, errorcode);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_compare(WRAP_Comm comm1, WRAP_Comm comm2, int *result)
{
    MPI_Comm impl_comm1 = CONVERT_MPI_Comm(comm1);
    MPI_Comm impl_comm2 = CONVERT_MPI_Comm(comm2);
    int rc = IMPL_Comm_compare(impl_comm1, impl_comm2, result);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_connect(const char *port_name, WRAP_Info info, int root, WRAP_Comm comm, WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_connect(port_name, impl_info, root, impl_comm, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_create(WRAP_Comm comm, WRAP_Group group, WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_create(impl_comm, impl_group, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if 0
int WRAP_Comm_create_errhandler(WRAP_Comm_errhandler_function *comm_errhandler_fn, WRAP_Errhandler *errhandler)
{
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_Comm_create_errhandler(comm_errhandler_fn, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_create_group(WRAP_Comm comm, WRAP_Group group, int tag, WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_create_group(impl_comm, impl_group, tag, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if 0
int WRAP_Comm_create_keyval(WRAP_Comm_copy_attr_function *comm_copy_attr_fn, WRAP_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state)
{
    int rc = IMPL_Comm_create_keyval(comm_copy_attr_fn, comm_delete_attr_fn, comm_keyval, extra_state);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Comm_delete_attr(WRAP_Comm comm, int comm_keyval)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_delete_attr(impl_comm, comm_keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_disconnect(WRAP_Comm *comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(*comm);
    int rc = IMPL_Comm_disconnect(&impl_comm);
    *comm = OUTPUT_MPI_Comm(impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_dup(WRAP_Comm comm, WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_dup(impl_comm, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_dup_with_info(WRAP_Comm comm, WRAP_Info info, WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_dup_with_info(impl_comm, impl_info, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_free(WRAP_Comm *comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(*comm);
    int rc = IMPL_Comm_free(&impl_comm);
    *comm = OUTPUT_MPI_Comm(impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_free_keyval(int *comm_keyval)
{
    int rc = IMPL_Comm_free_keyval(comm_keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_attr(WRAP_Comm comm, int comm_keyval, void *attribute_val, int *flag)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_get_attr(impl_comm, comm_keyval, attribute_val, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_errhandler(WRAP_Comm comm, WRAP_Errhandler *errhandler)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_Comm_get_errhandler(impl_comm, &impl_errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_info(WRAP_Comm comm, WRAP_Info *info_used)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info_used;
    int rc = IMPL_Comm_get_info(impl_comm, &impl_info_used);
    *info_used = OUTPUT_MPI_Info(impl_info_used);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_name(WRAP_Comm comm, char *comm_name, int *resultlen)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_get_name(impl_comm, comm_name, resultlen);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_get_parent(WRAP_Comm *parent)
{
    MPI_Comm impl_parent;
    int rc = IMPL_Comm_get_parent(&impl_parent);
    *parent = OUTPUT_MPI_Comm(impl_parent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_group(WRAP_Comm comm, WRAP_Group *group)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Group impl_group;
    int rc = IMPL_Comm_group(impl_comm, &impl_group);
    *group = OUTPUT_MPI_Group(impl_group);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_idup(WRAP_Comm comm, WRAP_Comm *newcomm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Comm impl_newcomm;
    MPI_Request impl_request;
    int rc = IMPL_Comm_idup(impl_comm, &impl_newcomm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_join(int fd, WRAP_Comm *intercomm)
{
    MPI_Comm impl_intercomm;
    int rc = IMPL_Comm_join(fd, &impl_intercomm);
    *intercomm = OUTPUT_MPI_Comm(impl_intercomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_rank(WRAP_Comm comm, int *rank)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_rank(impl_comm, rank);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_remote_group(WRAP_Comm comm, WRAP_Group *group)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Group impl_group;
    int rc = IMPL_Comm_remote_group(impl_comm, &impl_group);
    *group = OUTPUT_MPI_Group(impl_group);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_remote_size(WRAP_Comm comm, int *size)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_remote_size(impl_comm, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_set_attr(WRAP_Comm comm, int comm_keyval, void *attribute_val)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_set_attr(impl_comm, comm_keyval, attribute_val);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_set_errhandler(WRAP_Comm comm, WRAP_Errhandler errhandler)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    int rc = IMPL_Comm_set_errhandler(impl_comm, impl_errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_set_info(WRAP_Comm comm, WRAP_Info info)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Comm_set_info(impl_comm, impl_info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_set_name(WRAP_Comm comm, const char *comm_name)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_set_name(impl_comm, comm_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_size(WRAP_Comm comm, int *size)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_size(impl_comm, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_split(WRAP_Comm comm, int color, int key, WRAP_Comm *newcomm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Comm impl_newcomm;
    int rc = IMPL_Comm_split(impl_comm, color, key, &impl_newcomm);
    *newcomm = OUTPUT_MPI_Comm(impl_newcomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Comm_test_inter(WRAP_Comm comm, int *flag)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Comm_test_inter(impl_comm, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Compare_and_swap(const void *origin_addr, const void *compare_addr, void *result_addr, WRAP_Datatype datatype, int target_rank, WRAP_Aint target_disp, WRAP_Win win)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Compare_and_swap(origin_addr, compare_addr, result_addr, impl_datatype, target_rank, target_disp, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dims_create(int nnodes, int ndims, int dims[])
{
    int rc = IMPL_Dims_create(nnodes, ndims, dims);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dist_graph_create(WRAP_Comm comm_old, int n, const int sources[], const int degrees[], const int destinations[], const int weights[], WRAP_Info info, int reorder, WRAP_Comm *comm_dist_graph)
{
    MPI_Comm impl_comm_old = CONVERT_MPI_Comm(comm_old);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_comm_dist_graph;
    int rc = IMPL_Dist_graph_create(impl_comm_old, n, sources, degrees, destinations, weights, impl_info, reorder, &impl_comm_dist_graph);
    *comm_dist_graph = OUTPUT_MPI_Comm(impl_comm_dist_graph);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dist_graph_create_adjacent(WRAP_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], WRAP_Info info, int reorder, WRAP_Comm *comm_dist_graph)
{
    MPI_Comm impl_comm_old = CONVERT_MPI_Comm(comm_old);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Comm impl_comm_dist_graph;
    int rc = IMPL_Dist_graph_create_adjacent(impl_comm_old, indegree, sources, sourceweights, outdegree, destinations, destweights, impl_info, reorder, &impl_comm_dist_graph);
    *comm_dist_graph = OUTPUT_MPI_Comm(impl_comm_dist_graph);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dist_graph_neighbors(WRAP_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[])
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Dist_graph_neighbors(impl_comm, maxindegree, sources, sourceweights, maxoutdegree, destinations, destweights);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Dist_graph_neighbors_count(WRAP_Comm comm, int *indegree, int *outdegree, int *weighted)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Dist_graph_neighbors_count(impl_comm, indegree, outdegree, weighted);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if 0
int WRAP_Errhandler_create(WRAP_Comm_errhandler_function *comm_errhandler_fn, WRAP_Errhandler *errhandler)
{
    int rc = IMPL_Errhandler_create(comm_errhandler_fn, errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Errhandler_free(WRAP_Errhandler *errhandler)
{
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_Errhandler_free(&impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Errhandler_get(WRAP_Comm comm, WRAP_Errhandler *errhandler)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_Errhandler_get(impl_comm, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Errhandler_set(WRAP_Comm comm, WRAP_Errhandler errhandler)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    int rc = IMPL_Errhandler_set(impl_comm, impl_errhandler);
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

int WRAP_Exscan(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Exscan(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Exscan_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Exscan_c(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Fetch_and_op(const void *origin_addr, void *result_addr, WRAP_Datatype datatype, int target_rank, WRAP_Aint target_disp, WRAP_Op op, WRAP_Win win)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Fetch_and_op(origin_addr, result_addr, impl_datatype, target_rank, target_disp, impl_op, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_call_errhandler(WRAP_File fh, int errorcode)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_call_errhandler(impl_fh, errorcode);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_close(WRAP_File *fh)
{
    MPI_File impl_fh;
    int rc = IMPL_File_close(&impl_fh);
    *fh = OUTPUT_MPI_File(impl_fh);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if 0
int WRAP_File_create_errhandler(WRAP_File_errhandler_function *file_errhandler_fn, WRAP_Errhandler *errhandler)
{
    int rc = IMPL_File_create_errhandler(file_errhandler_fn, errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_delete(const char *filename, WRAP_Info info)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_File_delete(filename, impl_info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_amode(WRAP_File fh, int *amode)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int impl_amode;
    int rc = IMPL_File_get_amode(impl_fh, &impl_amode);
    *amode = IO_MODE_IMPL_TO_MUK(impl_amode);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_atomicity(WRAP_File fh, int *flag)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_get_atomicity(impl_fh, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_byte_offset(WRAP_File fh, WRAP_Offset offset, WRAP_Offset *disp)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_get_byte_offset(impl_fh, offset, disp);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_errhandler(WRAP_File file, WRAP_Errhandler *errhandler)
{
    MPI_File impl_file = CONVERT_MPI_File(file);
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_File_get_errhandler(impl_file, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_group(WRAP_File fh, WRAP_Group *group)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Group impl_group;
    int rc = IMPL_File_get_group(impl_fh, &impl_group);
    *group = OUTPUT_MPI_Group(impl_group);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_info(WRAP_File fh, WRAP_Info *info_used)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Info impl_info_used;
    int rc = IMPL_File_get_info(impl_fh, &impl_info_used);
    *info_used = OUTPUT_MPI_Info(impl_info_used);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_position(WRAP_File fh, WRAP_Offset *offset)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_get_position(impl_fh, offset);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_position_shared(WRAP_File fh, WRAP_Offset *offset)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_get_position_shared(impl_fh, offset);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_size(WRAP_File fh, WRAP_Offset *size)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_get_size(impl_fh, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_type_extent(WRAP_File fh, WRAP_Datatype datatype, WRAP_Aint *extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_get_type_extent(impl_fh, impl_datatype, extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_get_type_extent_c(WRAP_File fh, WRAP_Datatype datatype, WRAP_Count *extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_get_type_extent_c(impl_fh, impl_datatype, extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_get_view(WRAP_File fh, WRAP_Offset *disp, WRAP_Datatype *etype, WRAP_Datatype *filetype, char *datarep)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_etype, impl_filetype;
    int rc = IMPL_File_get_view(impl_fh, disp, &impl_etype, &impl_filetype, datarep);
    *etype = OUTPUT_MPI_Datatype(impl_etype);
    *filetype = OUTPUT_MPI_Datatype(impl_filetype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iread(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread_all(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_all(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_iread_all_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_all_c(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_iread_at(WRAP_File fh, WRAP_Offset offset, void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_at(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread_at_all(WRAP_File fh, WRAP_Offset offset, void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_at_all(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_iread_at_all_c(WRAP_File fh, WRAP_Offset offset, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_at_all_c(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_File_iread_at_c(WRAP_File fh, WRAP_Offset offset, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_at_c(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_File_iread_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_c(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_iread_shared(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_shared(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_iread_shared_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_shared_c(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_iwrite(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iwrite_all(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_all(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_iwrite_all_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_all_c(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_iwrite_at(WRAP_File fh, WRAP_Offset offset, const void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_at(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iwrite_at_all(WRAP_File fh, WRAP_Offset offset, const void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_at_all(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_iwrite_at_all_c(WRAP_File fh, WRAP_Offset offset, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_at_all_c(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_File_iwrite_at_c(WRAP_File fh, WRAP_Offset offset, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_at_c(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_File_iwrite_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_c(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_iwrite_shared(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_shared(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_iwrite_shared_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_shared_c(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_open(WRAP_Comm comm, const char *filename, int amode, WRAP_Info info, WRAP_File *fh)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_File impl_fh;
    int rc = IMPL_File_open(impl_comm, filename, amode, impl_info, &impl_fh);
    *fh = OUTPUT_MPI_File(impl_fh);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_preallocate(WRAP_File fh, WRAP_Offset size)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_preallocate(impl_fh, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_all(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read_all(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_all_begin(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_read_all_begin(impl_fh, buf, count, impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_read_all_begin_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_read_all_begin_c(impl_fh, buf, count, impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_read_all_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read_all_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_all_end(WRAP_File fh, void *buf, WRAP_Status *status)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read_all_end(impl_fh, buf, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at(WRAP_File fh, WRAP_Offset offset, void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read_at(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at_all(WRAP_File fh, WRAP_Offset offset, void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read_at_all(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at_all_begin(WRAP_File fh, WRAP_Offset offset, void *buf, int count, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_read_at_all_begin(impl_fh, offset, buf, count, impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_read_at_all_begin_c(WRAP_File fh, WRAP_Offset offset, void *buf, WRAP_Count count, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_read_at_all_begin_c(impl_fh, offset, buf, count, impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_read_at_all_c(WRAP_File fh, WRAP_Offset offset, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read_at_all_c(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at_all_end(WRAP_File fh, void *buf, WRAP_Status *status)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read_at_all_end(impl_fh, buf, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at_c(WRAP_File fh, WRAP_Offset offset, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read_at_c(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_ordered(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read_ordered(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_ordered_begin(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_read_ordered_begin(impl_fh, buf, count, impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_read_ordered_begin_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_read_ordered_begin_c(impl_fh, buf, count, impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_read_ordered_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read_ordered_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_ordered_end(WRAP_File fh, void *buf, WRAP_Status *status)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read_ordered_end(impl_fh, buf, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_shared(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read_shared(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_shared_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_read_shared_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_seek(WRAP_File fh, WRAP_Offset offset, int whence)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_seek(impl_fh, offset, whence);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_seek_shared(WRAP_File fh, WRAP_Offset offset, int whence)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_seek_shared(impl_fh, offset, whence);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_atomicity(WRAP_File fh, int flag)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_set_atomicity(impl_fh, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_errhandler(WRAP_File file, WRAP_Errhandler errhandler)
{
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    MPI_File impl_file = CONVERT_MPI_File(file);
    int rc = IMPL_File_set_errhandler(impl_file, impl_errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_info(WRAP_File fh, WRAP_Info info)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_File_set_info(impl_fh, impl_info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_size(WRAP_File fh, WRAP_Offset size)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_set_size(impl_fh, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_view(WRAP_File fh, WRAP_Offset disp, WRAP_Datatype etype, WRAP_Datatype filetype, const char *datarep, WRAP_Info info)
{
    MPI_Datatype impl_etype = CONVERT_MPI_Datatype(etype);
    MPI_Datatype impl_filetype = CONVERT_MPI_Datatype(filetype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_File_set_view(impl_fh, disp, impl_etype, impl_filetype, datarep, impl_info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_sync(WRAP_File fh)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_sync(impl_fh);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_all(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write_all(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_all_begin(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_write_all_begin(impl_fh, buf, count, impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_write_all_begin_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_write_all_begin_c(impl_fh, buf, count, impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_write_all_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write_all_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_all_end(WRAP_File fh, const void *buf, WRAP_Status *status)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write_all_end(impl_fh, buf, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at(WRAP_File fh, WRAP_Offset offset, const void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write_at(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at_all(WRAP_File fh, WRAP_Offset offset, const void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write_at_all(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at_all_begin(WRAP_File fh, WRAP_Offset offset, const void *buf, int count, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_write_at_all_begin(impl_fh, offset, buf, count, impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_write_at_all_begin_c(WRAP_File fh, WRAP_Offset offset, const void *buf, WRAP_Count count, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_write_at_all_begin_c(impl_fh, offset, buf, count, impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_write_at_all_c(WRAP_File fh, WRAP_Offset offset, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write_at_all_c(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at_all_end(WRAP_File fh, const void *buf, WRAP_Status *status)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write_at_all_end(impl_fh, buf, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at_c(WRAP_File fh, WRAP_Offset offset, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write_at_c(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_ordered(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write_ordered(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_ordered_begin(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_write_ordered_begin(impl_fh, buf, count, impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_write_ordered_begin_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_write_ordered_begin_c(impl_fh, buf, count, impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_write_ordered_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write_ordered_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_ordered_end(WRAP_File fh, const void *buf, WRAP_Status *status)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write_ordered_end(impl_fh, buf, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_shared(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write_shared(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_shared_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_File_write_shared_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Free_mem(void *base)
{
    int rc = IMPL_Free_mem(base);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Gather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Gather(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Gather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Gather_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Gatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Gatherv(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, root, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Gatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Gatherv_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, root, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Get(void *origin_addr, int origin_count, WRAP_Datatype origin_datatype, int target_rank, WRAP_Aint target_disp, int target_count, WRAP_Datatype target_datatype, WRAP_Win win)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
#if MPI_VERSION >= 4
    int rc = IMPL_Get(origin_addr, origin_count, impl_origin_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_accumulate(const void *origin_addr, int origin_count, WRAP_Datatype origin_datatype, void *result_addr, int result_count, WRAP_Datatype result_datatype, int target_rank, WRAP_Aint target_disp, int target_count, WRAP_Datatype target_datatype, WRAP_Op op, WRAP_Win win)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_result_datatype = CONVERT_MPI_Datatype(result_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Get_accumulate(origin_addr, origin_count, impl_origin_datatype, result_addr, result_count, impl_result_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_op, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_accumulate_c(const void *origin_addr, WRAP_Count origin_count, WRAP_Datatype origin_datatype, void *result_addr, WRAP_Count result_count, WRAP_Datatype result_datatype, int target_rank, WRAP_Aint target_disp, WRAP_Count target_count, WRAP_Datatype target_datatype, WRAP_Op op, WRAP_Win win)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_result_datatype = CONVERT_MPI_Datatype(result_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Get_accumulate_c(origin_addr, origin_count, impl_origin_datatype, result_addr, result_count, impl_result_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_op, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Get_address(const void *location, WRAP_Aint *address)
{
    int rc = IMPL_Get_address(location, address);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Get_c(void *origin_addr, WRAP_Count origin_count, WRAP_Datatype origin_datatype, int target_rank, WRAP_Aint target_disp, WRAP_Count target_count, WRAP_Datatype target_datatype, WRAP_Win win)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Get_c(origin_addr, origin_count, impl_origin_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Get_count(const WRAP_Status *status, WRAP_Datatype datatype, int *count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Get_count(&impl_status, impl_datatype, count);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_count_c(const WRAP_Status *status, WRAP_Datatype datatype, WRAP_Count *count)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Get_count_c(&impl_status, impl_datatype, count);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_elements(const WRAP_Status *status, WRAP_Datatype datatype, int *count)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Get_elements(&impl_status, impl_datatype, count);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_elements_c(const WRAP_Status *status, WRAP_Datatype datatype, WRAP_Count *count)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Get_elements_c(&impl_status, impl_datatype, count);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_elements_x(const WRAP_Status *status, WRAP_Datatype datatype, WRAP_Count *count)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Get_elements_x(&impl_status, impl_datatype, count);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_create(WRAP_Comm comm_old, int nnodes, const int indx[], const int edges[], int reorder, WRAP_Comm *comm_graph)
{
    MPI_Comm impl_comm_old = CONVERT_MPI_Comm(comm_old);
    MPI_Comm impl_comm_graph;
    int rc = IMPL_Graph_create(impl_comm_old, nnodes, indx, edges, reorder, &impl_comm_graph);
    *comm_graph = OUTPUT_MPI_Comm(impl_comm_graph);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_get(WRAP_Comm comm, int maxindex, int maxedges, int indx[], int edges[])
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Graph_get(impl_comm, maxindex, maxedges, indx, edges);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_map(WRAP_Comm comm, int nnodes, const int indx[], const int edges[], int *newrank)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Graph_map(impl_comm, nnodes, indx, edges, newrank);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_neighbors(WRAP_Comm comm, int rank, int maxneighbors, int neighbors[])
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Graph_neighbors(impl_comm, rank, maxneighbors, neighbors);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graph_neighbors_count(WRAP_Comm comm, int rank, int *nneighbors)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Graph_neighbors_count(impl_comm, rank, nneighbors);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Graphdims_get(WRAP_Comm comm, int *nnodes, int *nedges)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Graphdims_get(impl_comm, nnodes, nedges);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Grequest_complete(WRAP_Request request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(request);
    int rc = IMPL_Grequest_complete(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if 0
int WRAP_Grequest_start(WRAP_Grequest_query_function *query_fn, WRAP_Grequest_free_function *free_fn, WRAP_Grequest_cancel_function *cancel_fn, void *extra_state, WRAP_Request *request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(*request);
    int rc = IMPL_Grequest_start(query_fn, free_fn, cancel_fn, extra_state, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Group_compare(WRAP_Group group1, WRAP_Group group2, int *result)
{
    MPI_Group impl_group1 = CONVERT_MPI_Group(group1);
    MPI_Group impl_group2 = CONVERT_MPI_Group(group2);
    int rc = IMPL_Group_compare(impl_group1, impl_group2, result);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_difference(WRAP_Group group1, WRAP_Group group2, WRAP_Group *newgroup)
{
    MPI_Group impl_group1 = CONVERT_MPI_Group(group1);
    MPI_Group impl_group2 = CONVERT_MPI_Group(group2);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_difference(impl_group1, impl_group2, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_excl(WRAP_Group group, int n, const int ranks[], WRAP_Group *newgroup)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_excl(impl_group, n, ranks, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_free(WRAP_Group *group)
{
    MPI_Group impl_group;
    int rc = IMPL_Group_free(&impl_group);
    *group = OUTPUT_MPI_Group(impl_group);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Group_from_session_pset(WRAP_Session session, const char *pset_name, WRAP_Group *newgroup)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_from_session_pset(impl_session, pset_name, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Group_incl(WRAP_Group group, int n, const int ranks[], WRAP_Group *newgroup)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_incl(impl_group, n, ranks, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_intersection(WRAP_Group group1, WRAP_Group group2, WRAP_Group *newgroup)
{
    MPI_Group impl_group1 = CONVERT_MPI_Group(group1);
    MPI_Group impl_group2 = CONVERT_MPI_Group(group2);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_intersection(impl_group1, impl_group2, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_range_excl(WRAP_Group group, int n, int ranges[][3], WRAP_Group *newgroup)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_range_excl(impl_group, n, ranges, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_range_incl(WRAP_Group group, int n, int ranges[][3], WRAP_Group *newgroup)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_range_incl(impl_group, n, ranges, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_rank(WRAP_Group group, int *rank)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    int rc = IMPL_Group_rank(impl_group, rank);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_size(WRAP_Group group, int *size)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    int rc = IMPL_Group_size(impl_group, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_translate_ranks(WRAP_Group group1, int n, const int ranks1[], WRAP_Group group2, int ranks2[])
{
    MPI_Group impl_group1 = CONVERT_MPI_Group(group1);
    MPI_Group impl_group2 = CONVERT_MPI_Group(group2);
    int rc = IMPL_Group_translate_ranks(impl_group1, n, ranks1, impl_group2, ranks2);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Group_union(WRAP_Group group1, WRAP_Group group2, WRAP_Group *newgroup)
{
    MPI_Group impl_group1 = CONVERT_MPI_Group(group1);
    MPI_Group impl_group2 = CONVERT_MPI_Group(group2);
    MPI_Group impl_newgroup;
    int rc = IMPL_Group_union(impl_group1, impl_group2, &impl_newgroup);
    *newgroup = OUTPUT_MPI_Group(impl_newgroup);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iallgather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Iallgather(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Ialltoallw(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // THIS IS ILLEGAL - FIX IT
    //if (sendtypes != NULL) free(impl_sendtypes);
    //free(impl_recvtypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ialltoallw_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Ialltoallw_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // THIS IS ILLEGAL - FIX IT
    //if (sendtypes != NULL) free(impl_sendtypes);
    //free(impl_recvtypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ibarrier(WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ibarrier(impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ibcast(void *buffer, int count, WRAP_Datatype datatype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Ibcast(buffer, count, impl_datatype, root, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ibcast_c(void *buffer, WRAP_Count count, WRAP_Datatype datatype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Ibcast_c(buffer, count, impl_datatype, root, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ibsend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Ibsend(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ibsend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Ibsend_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Imrecv(void *buf, int count, WRAP_Datatype datatype, WRAP_Message *message, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Message impl_message;
    MPI_Request impl_request;
    int rc = IMPL_Imrecv(buf, count, impl_datatype, &impl_message, &impl_request);
    *message = OUTPUT_MPI_Message(impl_message);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Imrecv_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Message *message, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Message impl_message;
    MPI_Request impl_request;
    int rc = IMPL_Imrecv_c(buf, count, impl_datatype, &impl_message, &impl_request);
    *message = OUTPUT_MPI_Message(impl_message);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_allgather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_allgather(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Ineighbor_alltoallw(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // THIS IS ILLEGAL - FIX IT
    //if (sendtypes != NULL) free(impl_sendtypes);
    //free(impl_recvtypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_alltoallw_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Ineighbor_alltoallw_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // THIS IS ILLEGAL - FIX IT
    //if (sendtypes != NULL) free(impl_sendtypes);
    //free(impl_recvtypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_create(WRAP_Info *info)
{
    MPI_Info impl_info;
    int rc = IMPL_Info_create(&impl_info);
    *info = OUTPUT_MPI_Info(impl_info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_create_env(int argc, char *argv[], WRAP_Info *info)
{
    MPI_Info impl_info;
    int rc = IMPL_Info_create_env(argc, argv, &impl_info);
    *info = OUTPUT_MPI_Info(impl_info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_delete(WRAP_Info info, const char *key)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Info_delete(impl_info, key);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_dup(WRAP_Info info, WRAP_Info *newinfo)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Info impl_newinfo;
    int rc = IMPL_Info_dup(impl_info, &impl_newinfo);
    *newinfo = OUTPUT_MPI_Info(impl_newinfo);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_free(WRAP_Info *info)
{
    MPI_Info impl_info = CONVERT_MPI_Info(*info);
    int rc = IMPL_Info_free(&impl_info);
    *info = OUTPUT_MPI_Info(impl_info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get(WRAP_Info info, const char *key, int valuelen, char *value, int *flag)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Info_get(impl_info, key, valuelen, value, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get_nkeys(WRAP_Info info, int *nkeys)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Info_get_nkeys(impl_info, nkeys);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get_nthkey(WRAP_Info info, int n, char *key)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Info_get_nthkey(impl_info, n, key);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get_string(WRAP_Info info, const char *key, int *buflen, char *value, int *flag)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc;
#if MPI_VERSION >= 4
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_get_valuelen(WRAP_Info info, const char *key, int *valuelen, int *flag)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Info_get_valuelen(impl_info, key, valuelen, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Info_set(WRAP_Info info, const char *key, const char *value)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Info_set(impl_info, key, value);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Intercomm_create(WRAP_Comm local_comm, int local_leader, WRAP_Comm peer_comm, int remote_leader, int tag, WRAP_Comm *newintercomm)
{
    MPI_Comm impl_local_comm = CONVERT_MPI_Comm(local_comm);
    MPI_Comm impl_peer_comm = CONVERT_MPI_Comm(peer_comm);
    MPI_Comm impl_newintercomm;
    int rc = IMPL_Intercomm_create(impl_local_comm, local_leader, impl_peer_comm, remote_leader, tag, &impl_newintercomm);
    *newintercomm = OUTPUT_MPI_Comm(impl_newintercomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Intercomm_merge(WRAP_Comm intercomm, int high, WRAP_Comm *newintracomm)
{
    MPI_Comm impl_intercomm = CONVERT_MPI_Comm(intercomm);
    MPI_Comm impl_newintracomm;
    int rc = IMPL_Intercomm_merge(impl_intercomm, high, &impl_newintracomm);
    *newintracomm = OUTPUT_MPI_Comm(impl_newintracomm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iprobe(int source, int tag, WRAP_Comm comm, int *flag, WRAP_Status *status)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_Iprobe(RANK_MUK_TO_IMPL(source), tag, impl_comm, flag, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Irecv(void *buf, int count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Irecv(buf, count, impl_datatype, RANK_MUK_TO_IMPL(source), tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Irecv_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Irecv_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(source), tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ireduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc;
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ireduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Request impl_request;
    int rc = IMPL_Ireduce_scatter_block(sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Irsend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Irsend(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Irsend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Irsend_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Isend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Isend(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Isend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Isend_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Isendrecv_replace(void *buf, int count, WRAP_Datatype datatype, int dest, int sendtag, int source, int recvtag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Isendrecv_replace(buf, count, impl_datatype, dest, sendtag, source, recvtag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Isendrecv_replace_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int sendtag, int source, int recvtag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Isendrecv_replace_c(buf, count, impl_datatype, dest, sendtag, source, recvtag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Issend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Issend(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Issend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Issend_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

#if 0
int WRAP_Keyval_create(WRAP_Copy_function *copy_fn, WRAP_Delete_function *delete_fn, int *keyval, void *extra_state)
{
    int rc = IMPL_Keyval_create(copy_fn, delete_fn, keyval, extra_state);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Keyval_free(int *keyval)
{
    int rc = IMPL_Keyval_free(keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Lookup_name(const char *service_name, WRAP_Info info, char *port_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Lookup_name(service_name, impl_info, port_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_allgather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_allgather(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_allgather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_allgather_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_allgatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_allgatherv(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_allgatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_allgatherv_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_alltoall(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_alltoall(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_alltoall_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_alltoall_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_alltoallv(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_alltoallv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Neighbor_alltoallv_c(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    rc = IMPL_Neighbor_alltoallw(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm);
    if (sendtypes != NULL) free(impl_sendtypes);
    free(impl_recvtypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_alltoallw_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype * impl_sendtypes;
    MPI_Datatype * impl_recvtypes;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    rc = IMPL_Neighbor_alltoallw_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm);
    if (sendtypes != NULL) free(impl_sendtypes);
    free(impl_recvtypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Neighbor_alltoallw_init(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // THIS IS ILLEGAL - FIX IT
    //if (sendtypes != NULL) free(impl_sendtypes);
    //free(impl_recvtypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
        return ERROR_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Neighbor_alltoallw_init_c(sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // THIS IS ILLEGAL - FIX IT
    //if (sendtypes != NULL) free(impl_sendtypes);
    //free(impl_recvtypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Op_commutative(WRAP_Op op, int *commute)
{
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Op_commutative(impl_op, commute);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Op_create(WRAP_User_function *user_fn, int commute, WRAP_Op *op)
{
    MPI_Op impl_op;
    int rc = IMPL_Op_create(trampoline, commute, &impl_op);
    *op = OUTPUT_MPI_Op(impl_op);
    add_op_pair_to_list(user_fn, impl_op);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Op_create_c(WRAP_User_function_c *user_fn, int commute, WRAP_Op *op)
{
    MPI_Op impl_op;
    int rc = IMPL_Op_create_c(trampoline_c, commute, &impl_op);
    *op = OUTPUT_MPI_Op(impl_op);
    //add_op_pair_to_list(user_fn, impl_op);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Op_free(WRAP_Op *op)
{
    //remove_op_pair_from_list(*op);
    MPI_Op impl_op;
    int rc = IMPL_Op_free(&impl_op);
    *op = OUTPUT_MPI_Op(impl_op);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Open_port(WRAP_Info info, char *port_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Open_port(impl_info, port_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pack(const void *inbuf, int incount, WRAP_Datatype datatype, void *outbuf, int outsize, int *position, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack(inbuf, incount, impl_datatype, outbuf, outsize, position, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Pack_c(const void *inbuf, WRAP_Count incount, WRAP_Datatype datatype, void *outbuf, WRAP_Count outsize, WRAP_Count *position, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack_c(inbuf, incount, impl_datatype, outbuf, outsize, position, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Pack_external(const char *datarep, const void *inbuf, int incount, WRAP_Datatype datatype, void *outbuf, WRAP_Aint outsize, WRAP_Aint *position)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack_external(datarep, inbuf, incount, impl_datatype, outbuf, outsize, position);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Pack_external_c(const char *datarep, const void *inbuf, WRAP_Count incount, WRAP_Datatype datatype, void *outbuf, WRAP_Count outsize, WRAP_Count *position)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack_external_c(datarep, inbuf, incount, impl_datatype, outbuf, outsize, position);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Pack_external_size(const char *datarep, int incount, WRAP_Datatype datatype, WRAP_Aint *size)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack_external_size(datarep, incount, impl_datatype, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Pack_external_size_c(const char *datarep, WRAP_Count incount, WRAP_Datatype datatype, WRAP_Count *size)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack_external_size_c(datarep, incount, impl_datatype, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Pack_size(int incount, WRAP_Datatype datatype, WRAP_Comm comm, int *size)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack_size(incount, impl_datatype, impl_comm, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Pack_size_c(WRAP_Count incount, WRAP_Datatype datatype, WRAP_Comm comm, WRAP_Count *size)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Pack_size_c(incount, impl_datatype, impl_comm, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Parrived(WRAP_Request request, int partition, int *flag)
{
    MPI_Request impl_request = CONVERT_MPI_Request(request);
    int rc = IMPL_Parrived(impl_request, partition, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pcontrol(const int level, ...)
{
    int rc = IMPL_Pcontrol(level);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pready(int partition, WRAP_Request request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(request);
    int rc = IMPL_Pready(partition, impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pready_list(int length, const int array_of_partitions[], WRAP_Request request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(request);
    int rc = IMPL_Pready_list(length, array_of_partitions, impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Pready_range(int partition_low, int partition_high, WRAP_Request request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(request);
    int rc = IMPL_Pready_range(partition_low, partition_high, impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Precv_init(void *buf, int partitions, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Precv_init(buf, partitions, count, impl_datatype, dest, tag, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Probe(int source, int tag, WRAP_Comm comm, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Status impl_status;
    int rc = IMPL_Probe(source, tag, impl_comm, &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Psend_init(const void *buf, int partitions, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Psend_init(buf, partitions, count, impl_datatype, dest, tag, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Publish_name(const char *service_name, WRAP_Info info, const char *port_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Publish_name(service_name, impl_info, port_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Put(const void *origin_addr, int origin_count, WRAP_Datatype origin_datatype, int target_rank, WRAP_Aint target_disp, int target_count, WRAP_Datatype target_datatype, WRAP_Win win)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Put(origin_addr, origin_count, impl_origin_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Put_c(const void *origin_addr, WRAP_Count origin_count, WRAP_Datatype origin_datatype, int target_rank, WRAP_Aint target_disp, WRAP_Count target_count, WRAP_Datatype target_datatype, WRAP_Win win)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Put_c(origin_addr, origin_count, impl_origin_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Raccumulate(const void *origin_addr, int origin_count, WRAP_Datatype origin_datatype, int target_rank, WRAP_Aint target_disp, int target_count, WRAP_Datatype target_datatype, WRAP_Op op, WRAP_Win win, WRAP_Request *request)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    MPI_Request impl_request;
    int rc = IMPL_Raccumulate(origin_addr, origin_count, impl_origin_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_op, impl_win, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Raccumulate_c(const void *origin_addr, WRAP_Count origin_count, WRAP_Datatype origin_datatype, int target_rank, WRAP_Aint target_disp, WRAP_Count target_count, WRAP_Datatype target_datatype, WRAP_Op op, WRAP_Win win, WRAP_Request *request)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    MPI_Request impl_request;
    int rc = IMPL_Raccumulate_c(origin_addr, origin_count, impl_origin_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_op, impl_win, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Recv(void *buf, int count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status;
    int rc = IMPL_Recv(buf, count, impl_datatype, source, tag, impl_comm, &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Recv_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Status *status)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_Recv_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(source), tag, impl_comm, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Recv_init(void *buf, int count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Recv_init(buf, count, impl_datatype, source, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Recv_init_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Recv_init_c(buf, count, impl_datatype, source, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Reduce(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc;
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_c(sendbuf, recvbuf, count, impl_datatype, impl_op, root, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_local(const void *inbuf, void *inoutbuf, int count, WRAP_Datatype datatype, WRAP_Op op)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_local(inbuf, inoutbuf, count, impl_datatype, impl_op);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_local_c(const void *inbuf, void *inoutbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_local_c(inbuf, inoutbuf, count, impl_datatype, impl_op);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_scatter(sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_scatter_block(sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Reduce_scatter_block_c(const void *sendbuf, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_scatter_block_c(sendbuf, recvbuf, recvcount, impl_datatype, impl_op, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Reduce_scatter_c(const void *sendbuf, void *recvbuf, const WRAP_Count recvcounts[], WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Reduce_scatter_c(sendbuf, recvbuf, recvcounts, impl_datatype, impl_op, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

#if 0
int WRAP_Register_datarep(const char *datarep, WRAP_Datarep_conversion_function *read_conversion_fn, WRAP_Datarep_conversion_function *write_conversion_fn, WRAP_Datarep_extent_function *dtype_file_extent_fn, void *extra_state)
{
    int rc = IMPL_Register_datarep(datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Register_datarep_c(const char *datarep, WRAP_Datarep_conversion_function_c *read_conversion_fn, WRAP_Datarep_conversion_function_c *write_conversion_fn, WRAP_Datarep_extent_function *dtype_file_extent_fn, void *extra_state)
{
    int rc = IMPL_Register_datarep_c(datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif
#endif

int WRAP_Request_free(WRAP_Request *request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(*request);
    int rc = IMPL_Request_free(&impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // It is erroneous to call MPI_REQUEST_FREE or MPI_CANCEL for a request
    // associated with a nonblocking collective operation.
    //remove_cookie_pair_from_list(*request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Request_get_status(WRAP_Request request, int *flag, WRAP_Status *status)
{
    MPI_Request impl_request = CONVERT_MPI_Request(request);
    MPI_Status impl_status;
    if (impl_request == MPI_REQUEST_NULL) {
        *flag = 1;
        WRAP_Status_empty(false,status);
        return MPI_SUCCESS;
    }
    int rc = IMPL_Request_get_status(impl_request, flag, &impl_status);
    if (*flag) {
        MPI_Status_to_WRAP_Status(&impl_status, status);
    }
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Rget(void *origin_addr, int origin_count, WRAP_Datatype origin_datatype, int target_rank, WRAP_Aint target_disp, int target_count, WRAP_Datatype target_datatype, WRAP_Win win, WRAP_Request *request)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    MPI_Request impl_request;
    int rc = IMPL_Rget(origin_addr, origin_count, impl_origin_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_win, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Rget_accumulate(const void *origin_addr, int origin_count, WRAP_Datatype origin_datatype, void *result_addr, int result_count, WRAP_Datatype result_datatype, int target_rank, WRAP_Aint target_disp, int target_count, WRAP_Datatype target_datatype, WRAP_Op op, WRAP_Win win, WRAP_Request *request)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_result_datatype = CONVERT_MPI_Datatype(result_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    MPI_Request impl_request;
    int rc = IMPL_Rget_accumulate(origin_addr, origin_count, impl_origin_datatype, result_addr, result_count, impl_result_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_op, impl_win, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Rget_accumulate_c(const void *origin_addr, WRAP_Count origin_count, WRAP_Datatype origin_datatype, void *result_addr, WRAP_Count result_count, WRAP_Datatype result_datatype, int target_rank, WRAP_Aint target_disp, WRAP_Count target_count, WRAP_Datatype target_datatype, WRAP_Op op, WRAP_Win win, WRAP_Request *request)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_result_datatype = CONVERT_MPI_Datatype(result_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    MPI_Request impl_request;
    int rc = IMPL_Rget_accumulate_c(origin_addr, origin_count, impl_origin_datatype, result_addr, result_count, impl_result_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_op, impl_win, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_Rget_c(void *origin_addr, WRAP_Count origin_count, WRAP_Datatype origin_datatype, int target_rank, WRAP_Aint target_disp, WRAP_Count target_count, WRAP_Datatype target_datatype, WRAP_Win win, WRAP_Request *request)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    MPI_Request impl_request;
    int rc = IMPL_Rget_c(origin_addr, origin_count, impl_origin_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_win, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Rput(const void *origin_addr, int origin_count, WRAP_Datatype origin_datatype, int target_rank, WRAP_Aint target_disp, int target_count, WRAP_Datatype target_datatype, WRAP_Win win, WRAP_Request *request)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    MPI_Request impl_request;
    int rc = IMPL_Rput(origin_addr, origin_count, impl_origin_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_win, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Rput_c(const void *origin_addr, WRAP_Count origin_count, WRAP_Datatype origin_datatype, int target_rank, WRAP_Aint target_disp, WRAP_Count target_count, WRAP_Datatype target_datatype, WRAP_Win win, WRAP_Request *request)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    MPI_Request impl_request;
    int rc = IMPL_Rput_c(origin_addr, origin_count, impl_origin_datatype, target_rank, target_disp, target_count, impl_target_datatype, impl_win, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Rsend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Rsend(buf, count, impl_datatype, dest, tag, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Rsend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Rsend_c(buf, count, impl_datatype, dest, tag, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Rsend_init(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Rsend_init(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Rsend_init_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Rsend_init_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Scan(const void *sendbuf, void *recvbuf, int count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Scan(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scan_c(const void *sendbuf, void *recvbuf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Op op, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    int rc = IMPL_Scan_c(sendbuf, recvbuf, count, impl_datatype, impl_op, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Scatter(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Scatter(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scatter_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Scatter_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Scatterv(sendbuf, sendcounts, displs, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scatterv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint displs[], WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    int rc = IMPL_Scatterv_c(sendbuf, sendcounts, displs, impl_sendtype, recvbuf, recvcount, impl_recvtype, root, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Send(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Send(buf, count, impl_datatype, dest, tag, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Send_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Send_c(buf, count, impl_datatype, dest, tag, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Send_init(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Send_init(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Send_init_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Send_init_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
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
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Sendrecv_replace(void *buf, int count, WRAP_Datatype datatype, int dest, int sendtag, int source, int recvtag, WRAP_Comm comm, WRAP_Status *status)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_Sendrecv_replace(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(sendtag), RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(recvtag), impl_comm, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Sendrecv_replace_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int sendtag, int source, int recvtag, WRAP_Comm comm, WRAP_Status *status)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;
    int rc = IMPL_Sendrecv_replace_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(sendtag), RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(recvtag), impl_comm, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Session_call_errhandler(WRAP_Session session, int errorcode)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    int rc = IMPL_Session_call_errhandler(impl_session, errorcode);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if 0
int WRAP_Session_create_errhandler(WRAP_Session_errhandler_function *session_errhandler_fn, WRAP_Errhandler *errhandler)
{
    int rc = IMPL_Session_create_errhandler(session_errhandler_fn, errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Session_finalize(WRAP_Session *session)
{
    MPI_Session impl_session = CONVERT_MPI_Session(*session);
    int rc = IMPL_Session_finalize(&impl_session);
    *session = OUTPUT_MPI_Session(impl_session);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_errhandler(WRAP_Session session, WRAP_Errhandler *errhandler)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_Session_get_errhandler(impl_session, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_info(WRAP_Session session, WRAP_Info *info_used)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    MPI_Info impl_info_used;
    int rc = IMPL_Session_get_info(impl_session, &impl_info_used);
    *info_used = OUTPUT_MPI_Info(impl_info_used);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_nth_pset(WRAP_Session session, WRAP_Info info, int n, int *pset_len, char *pset_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    int rc = IMPL_Session_get_nth_pset(impl_session, impl_info, n, pset_len, pset_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_num_psets(WRAP_Session session, WRAP_Info info, int *npset_names)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    int rc = IMPL_Session_get_num_psets(impl_session, impl_info, npset_names);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_pset_info(WRAP_Session session, const char *pset_name, WRAP_Info *info)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    MPI_Info impl_info;
    int rc = IMPL_Session_get_pset_info(impl_session, pset_name, &impl_info);
    *info = OUTPUT_MPI_Info(impl_info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_init(WRAP_Info info, WRAP_Errhandler errhandler, WRAP_Session *session)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    MPI_Session impl_session = CONVERT_MPI_Session(*session);
    int rc = IMPL_Session_init(impl_info, impl_errhandler, &impl_session);
    *session = OUTPUT_MPI_Session(impl_session);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_set_errhandler(WRAP_Session session, WRAP_Errhandler errhandler)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    int rc = IMPL_Session_set_errhandler(impl_session, impl_errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ssend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Ssend(buf, count, impl_datatype, dest, tag, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ssend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Ssend_c(buf, count, impl_datatype, dest, tag, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ssend_init(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Ssend_init(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ssend_init_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_Ssend_init_c(buf, count, impl_datatype, dest, tag, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Start(WRAP_Request *request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(*request);
    int rc = IMPL_Start(&impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Startall(int count, WRAP_Request array_of_requests[])
{
    MPI_Request * impl_array_of_requests = malloc(count * sizeof(MPI_Request));
    for (int i=0; i<count; i++) {
        impl_array_of_requests[i] = CONVERT_MPI_Request(array_of_requests[i]);
    }
    int rc = IMPL_Startall(count, impl_array_of_requests);
    for (int i=0; i<count; i++) {
        array_of_requests[i] = OUTPUT_MPI_Request(impl_array_of_requests[i]);
    }
    free(impl_array_of_requests);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#ifdef SUPPORT_F08
int WRAP_Status_f082c(const WRAP_F08_status *f08_status, WRAP_Status *c_status)
{
    int rc = IMPL_Status_f082c(f08_status, c_status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Status_f082f(const WRAP_F08_status *f08_status, WRAP_Fint *f_status)
{
    int rc = IMPL_Status_f082f(f08_status, f_status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Status_f2f08(const WRAP_Fint *f_status, WRAP_F08_status *f08_status)
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

int WRAP_Status_set_elements(WRAP_Status *status, WRAP_Datatype datatype, int count)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Status_set_elements(&impl_status, impl_datatype, count);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Status_set_elements_c(WRAP_Status *status, WRAP_Datatype datatype, WRAP_Count count)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Status_set_elements_c(&impl_status, impl_datatype, count);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Status_set_elements_x(WRAP_Status *status, WRAP_Datatype datatype, WRAP_Count count)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Status_set_elements_x(&impl_status, impl_datatype, count);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Test(WRAP_Request *request, int *flag, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Request impl_request = CONVERT_MPI_Request(*request);
    MPI_Status impl_status;
    int rc = IMPL_Test(&impl_request, flag, ignore ? MPI_STATUS_IGNORE : &impl_status);
    *request = OUTPUT_MPI_Request(impl_request);
#if 0
    if (**request == MPI_REQUEST_NULL) {
        //printf("WRAP_Test: request=%p *request=%p **request=MPI_REQUEST_NULL\n", request, *request);
        *flag = 1;
        WRAP_Status_empty(ignore,status);
        return MPI_SUCCESS;
    }

    MPI_Status impl_status;
    int rc = IMPL_Test(*request, flag, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (*flag) {
        remove_cookie_pair_from_list(*request);
        free(*request);
        *request = &IMPL_REQUEST_NULL;
        if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    }
#endif
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Test_cancelled(const WRAP_Status *status, int *flag)
{
    MPI_Status impl_status;
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Test_cancelled(&impl_status, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Testall(int count, WRAP_Request array_of_requests[], int *flag, WRAP_Status *array_of_statuses)
{
    //int rc = IMPL_Testall(count, array_of_requests, flag, array_of_statuses);
#if 0
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
                remove_cookie_pair_from_list(array_of_requests[i]);
                if (*array_of_requests[i] != MPI_REQUEST_NULL) {
                    free(array_of_requests[i]);
                }
                array_of_requests[i] = &IMPL_REQUEST_NULL;
            }
        }
    }
    free(impl_requests);

    // need to WRAP_Status_empty(status) somewhere here when request is null

    if (!ignore) {
        for (int i=0; i<count; i++) {
            MPI_Status_to_WRAP_Status(&impl_statuses[i], &array_of_statuses[i]);
        }
        free(impl_statuses);
    }
#endif
    //return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Testany(int count, WRAP_Request array_of_requests[], int *indx, int *flag, WRAP_Status *status)
{
    //int rc = IMPL_Testany(count, array_of_requests, indx, flag, status);
#if 0
    MPI_Request * impl_requests = malloc(count * sizeof(MPI_Request));
    if (impl_requests == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<count; i++) {
        impl_requests[i] = *array_of_requests[i];
    }

    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;

    int rc = IMPL_Testany(count, impl_requests, indx, flag, ignore ? MPI_STATUS_IGNORE : &impl_status);

    if (*flag) {
        // If the array contains no active handles then the call returns immediately with flag = true,
        // index = MPI_UNDEFINED, and an empty status.
        if (*indx != MPI_UNDEFINED) {

            if (impl_requests[*indx] == MPI_REQUEST_NULL) {
                remove_cookie_pair_from_list(array_of_requests[*indx]);
                if (*array_of_requests[*indx] != MPI_REQUEST_NULL) {
                    free(array_of_requests[*indx]);
                }
                array_of_requests[*indx] = &IMPL_REQUEST_NULL;
            }

            // need to WRAP_Status_empty(status) somewhere here when request is null

            if (!ignore) {
                MPI_Status_to_WRAP_Status(&impl_status, status);
            }
        }
    }

    free(impl_requests);
#endif
    //return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Testsome(int incount, WRAP_Request array_of_requests[], int *outcount, int array_of_indices[], WRAP_Status *array_of_statuses)
{
    //int rc = IMPL_Testsome(incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
#if 0
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
                remove_cookie_pair_from_list(array_of_requests[j]);
                if (*array_of_requests[j] != MPI_REQUEST_NULL) {
                    free(array_of_requests[j]);
                }
                array_of_requests[j] = &IMPL_REQUEST_NULL;
            }
        }

        // need to WRAP_Status_empty(status) somewhere here when request is null

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
#endif
    //return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Topo_test(WRAP_Comm comm, int *status)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Topo_test(impl_comm, status);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_commit(WRAP_Datatype *datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(*datatype);
    int rc = IMPL_Type_commit(&impl_datatype);
    *datatype = OUTPUT_MPI_Datatype(impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_contiguous(int count, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_contiguous(count, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_contiguous_c(WRAP_Count count, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_contiguous_c(count, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_create_darray(int size, int rank, int ndims, const int array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    int impl_order = MPI_UNDEFINED;
    if (order == MUK_ORDER_C) {
        impl_order = MPI_ORDER_C;
    }
    else if (order == MUK_ORDER_FORTRAN) {
        impl_order = MPI_ORDER_FORTRAN;
    }
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_darray(size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, impl_order, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_darray_c(int size, int rank, int ndims, const WRAP_Count array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    int impl_order = MPI_UNDEFINED;
    if (order == MUK_ORDER_C) {
        impl_order = MPI_ORDER_C;
    }
    else if (order == MUK_ORDER_FORTRAN) {
        impl_order = MPI_ORDER_FORTRAN;
    }
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_darray_c(size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, impl_order, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_f90_complex(int p, int r, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_f90_complex(p, r, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_f90_integer(int r, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_f90_integer(r, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_f90_real(int p, int r, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_f90_real(p, r, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_hindexed(int count, const int array_of_blocklengths[], const WRAP_Aint array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_hindexed(count, array_of_blocklengths, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_hindexed_block(int count, int blocklength, const WRAP_Aint array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_hindexed_block(count, blocklength, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_create_hindexed_block_c(WRAP_Count count, WRAP_Count blocklength, const WRAP_Count array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_hindexed_block_c(count, blocklength, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_Type_create_hindexed_c(WRAP_Count count, const WRAP_Count array_of_blocklengths[], const WRAP_Count array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_hindexed_c(count, array_of_blocklengths, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_create_hvector(int count, int blocklength, WRAP_Aint stride, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_hvector(count, blocklength, stride, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_create_hvector_c(WRAP_Count count, WRAP_Count blocklength, WRAP_Count stride, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_hvector_c(count, blocklength, stride, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_indexed_block(count, blocklength, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_create_indexed_block_c(WRAP_Count count, WRAP_Count blocklength, const WRAP_Count array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_indexed_block_c(count, blocklength, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

#if 0
int WRAP_Type_create_keyval(WRAP_Type_copy_attr_function *type_copy_attr_fn, WRAP_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state)
{
    int rc = IMPL_Type_create_keyval(type_copy_attr_fn, type_delete_attr_fn, type_keyval, extra_state);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_create_resized(WRAP_Datatype oldtype, WRAP_Aint lb, WRAP_Aint extent, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_resized(impl_oldtype, lb, extent, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_create_resized_c(WRAP_Datatype oldtype, WRAP_Count lb, WRAP_Count extent, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_resized_c(impl_oldtype, lb, extent, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_create_struct(int count, const int array_of_blocklengths[], const WRAP_Aint array_of_displacements[], const WRAP_Datatype array_of_types[], WRAP_Datatype *newtype)
{
    MPI_Datatype * impl_array_of_types = malloc(count * sizeof(MPI_Datatype));
    for (int i=0; i<count; i++) {
        impl_array_of_types[i] = CONVERT_MPI_Datatype(array_of_types[i]);
    }
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_struct(count, array_of_blocklengths, array_of_displacements, impl_array_of_types, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    free(impl_array_of_types);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_create_struct_c(WRAP_Count count, const WRAP_Count array_of_blocklengths[], const WRAP_Count array_of_displacements[], const WRAP_Datatype array_of_types[], WRAP_Datatype *newtype)
{
    MPI_Datatype * impl_array_of_types = malloc(count * sizeof(MPI_Datatype));
    for (MPI_Count i=0; i<count; i++) {
        impl_array_of_types[i] = CONVERT_MPI_Datatype(array_of_types[i]);
    }
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_struct_c(count, array_of_blocklengths, array_of_displacements, impl_array_of_types, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    free(impl_array_of_types);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_create_subarray(int ndims, const int array_of_sizes[], const int array_of_subsizes[], const int array_of_starts[], int order, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    int impl_order = MPI_UNDEFINED;
    if (order == MUK_ORDER_C) {
        impl_order = MPI_ORDER_C;
    }
    else if (order == MUK_ORDER_FORTRAN) {
        impl_order = MPI_ORDER_FORTRAN;
    }
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_subarray(ndims, array_of_sizes, array_of_subsizes, array_of_starts, impl_order, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_subarray_c(int ndims, const WRAP_Count array_of_sizes[], const WRAP_Count array_of_subsizes[], const WRAP_Count array_of_starts[], int order, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    int impl_order = MPI_UNDEFINED;
    if (order == MUK_ORDER_C) {
        impl_order = MPI_ORDER_C;
    }
    else if (order == MUK_ORDER_FORTRAN) {
        impl_order = MPI_ORDER_FORTRAN;
    }
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_subarray_c(ndims, array_of_sizes, array_of_subsizes, array_of_starts, impl_order, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_delete_attr(WRAP_Datatype datatype, int type_keyval)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_delete_attr(impl_datatype, type_keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_dup(WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_dup(impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_extent(WRAP_Datatype datatype, WRAP_Aint *extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_extent(impl_datatype, extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_free(WRAP_Datatype *datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(*datatype);
    int rc = IMPL_Type_free(&impl_datatype);
    *datatype = OUTPUT_MPI_Datatype(impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_free_keyval(int *type_keyval)
{
    int rc = IMPL_Type_free_keyval(type_keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_attr(WRAP_Datatype datatype, int type_keyval, void *attribute_val, int *flag)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_attr(impl_datatype, type_keyval, attribute_val, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_contents(WRAP_Datatype datatype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], WRAP_Aint array_of_addresses[], WRAP_Datatype array_of_datatypes[])
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Datatype * impl_array_of_datatypes = malloc(max_datatypes * sizeof(MPI_Datatype));
    int rc = IMPL_Type_get_contents(impl_datatype, max_integers, max_addresses, max_datatypes, array_of_integers, array_of_addresses, impl_array_of_datatypes);
    for (int i=0; i<max_datatypes; i++) {
        array_of_datatypes[i] = OUTPUT_MPI_Datatype(impl_array_of_datatypes[i]);
    }
    free(impl_array_of_datatypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_get_contents_c(WRAP_Datatype datatype, WRAP_Count max_integers, WRAP_Count max_addresses, WRAP_Count max_large_counts, WRAP_Count max_datatypes, int array_of_integers[], WRAP_Aint array_of_addresses[], WRAP_Count array_of_large_counts[], WRAP_Datatype array_of_datatypes[])
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Datatype * impl_array_of_datatypes = malloc(max_datatypes * sizeof(MPI_Datatype));
    int rc = IMPL_Type_get_contents_c(impl_datatype, max_integers, max_addresses, max_large_counts, max_datatypes, array_of_integers, array_of_addresses, array_of_large_counts, impl_array_of_datatypes);
    for (int i=0; i<max_datatypes; i++) {
        array_of_datatypes[i] = OUTPUT_MPI_Datatype(impl_array_of_datatypes[i]);
    }
    free(impl_array_of_datatypes);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_get_envelope(WRAP_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_envelope(impl_datatype, num_integers, num_addresses, num_datatypes, combiner);
    *combiner = COMBINER_CODE_IMPL_TO_MUK(*combiner);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_get_envelope_c(WRAP_Datatype datatype, WRAP_Count *num_integers, WRAP_Count *num_addresses, WRAP_Count *num_large_counts, WRAP_Count *num_datatypes, int *combiner)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_envelope_c(impl_datatype, num_integers, num_addresses, num_large_counts, num_datatypes, combiner);
    *combiner = COMBINER_CODE_IMPL_TO_MUK(*combiner);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_get_extent(WRAP_Datatype datatype, WRAP_Aint *lb, WRAP_Aint *extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_extent(impl_datatype, lb, extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_get_extent_c(WRAP_Datatype datatype, WRAP_Count *lb, WRAP_Count *extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_extent_c(impl_datatype, lb, extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_get_extent_x(WRAP_Datatype datatype, WRAP_Count *lb, WRAP_Count *extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_extent_x(impl_datatype, lb, extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_name(WRAP_Datatype datatype, char *type_name, int *resultlen)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_name(impl_datatype, type_name, resultlen);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_true_extent(WRAP_Datatype datatype, WRAP_Aint *true_lb, WRAP_Aint *true_extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_true_extent(impl_datatype, true_lb, true_extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_get_true_extent_c(WRAP_Datatype datatype, WRAP_Count *true_lb, WRAP_Count *true_extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_true_extent_c(impl_datatype, true_lb, true_extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_get_true_extent_x(WRAP_Datatype datatype, WRAP_Count *true_lb, WRAP_Count *true_extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_true_extent_x(impl_datatype, true_lb, true_extent);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_hindexed(int count, int array_of_blocklengths[], WRAP_Aint array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_hindexed(count, array_of_blocklengths, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_hvector(int count, int blocklength, WRAP_Aint stride, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_hvector(count, blocklength, stride, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_indexed(int count, const int array_of_blocklengths[], const int array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_indexed(count, array_of_blocklengths, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_indexed_c(WRAP_Count count, const WRAP_Count array_of_blocklengths[], const WRAP_Count array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_indexed_c(count, array_of_blocklengths, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_lb(WRAP_Datatype datatype, WRAP_Aint *displacement)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_lb(impl_datatype, displacement);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_match_size(int typeclass, int size, WRAP_Datatype *datatype)
{
    MPI_Datatype impl_datatype;
    int impl_typeclass;
    if (typeclass == MUK_TYPECLASS_INTEGER) {
        impl_typeclass = MPI_TYPECLASS_INTEGER;
    }
    else if (typeclass == MUK_TYPECLASS_REAL) {
        impl_typeclass = MPI_TYPECLASS_REAL;
    }
    else if (typeclass == MUK_TYPECLASS_COMPLEX) {
        impl_typeclass = MPI_TYPECLASS_COMPLEX;
    }
    else {
        printf("Unknown typeclass: %d\n", typeclass);
        impl_typeclass = MPI_UNDEFINED;
    }
    int rc = IMPL_Type_match_size(impl_typeclass, size, &impl_datatype);
    *datatype = OUTPUT_MPI_Datatype(impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_set_attr(WRAP_Datatype datatype, int type_keyval, void *attribute_val)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_set_attr(impl_datatype, type_keyval, attribute_val);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_set_name(WRAP_Datatype datatype, const char *type_name)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_set_name(impl_datatype, type_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_size(WRAP_Datatype datatype, int *size)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_size(impl_datatype, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_size_c(WRAP_Datatype datatype, WRAP_Count *size)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_size_c(impl_datatype, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_size_x(WRAP_Datatype datatype, WRAP_Count *size)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_size_x(impl_datatype, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_struct(int count, int array_of_blocklengths[], WRAP_Aint array_of_displacements[], WRAP_Datatype array_of_types[], WRAP_Datatype *newtype)
{
    MPI_Datatype * impl_array_of_types = malloc(count * sizeof(MPI_Datatype));
    for (int i=0; i<count; i++) {
        impl_array_of_types[i] = CONVERT_MPI_Datatype(array_of_types[i]);
    }
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_struct(count, array_of_blocklengths, array_of_displacements, impl_array_of_types, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    free(impl_array_of_types);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_ub(WRAP_Datatype datatype, WRAP_Aint *displacement)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_ub(impl_datatype, displacement);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_vector(int count, int blocklength, int stride, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_vector(count, blocklength, stride, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_vector_c(WRAP_Count count, WRAP_Count blocklength, WRAP_Count stride, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_vector_c(count, blocklength, stride, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, WRAP_Datatype datatype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Unpack(inbuf, insize, position, outbuf, outcount, impl_datatype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Unpack_c(const void *inbuf, WRAP_Count insize, WRAP_Count *position, void *outbuf, WRAP_Count outcount, WRAP_Datatype datatype, WRAP_Comm comm)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Unpack_c(inbuf, insize, position, outbuf, outcount, impl_datatype, impl_comm);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Unpack_external(const char datarep[], const void *inbuf, WRAP_Aint insize, WRAP_Aint *position, void *outbuf, int outcount, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Unpack_external(datarep, inbuf, insize, position, outbuf, outcount, impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Unpack_external_c(const char datarep[], const void *inbuf, WRAP_Count insize, WRAP_Count *position, void *outbuf, WRAP_Count outcount, WRAP_Datatype datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Unpack_external_c(datarep, inbuf, insize, position, outbuf, outcount, impl_datatype);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Unpublish_name(const char *service_name, WRAP_Info info, const char *port_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_Unpublish_name(service_name, impl_info, port_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Wait(WRAP_Request *request, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Request impl_request = CONVERT_MPI_Request(*request);
    MPI_Status impl_status;
    int rc = IMPL_Wait(&impl_request, ignore ? MPI_STATUS_IGNORE : &impl_status);
    *request = OUTPUT_MPI_Request(impl_request);
#if 0
    const bool ignore = IS_STATUS_IGNORE(status);

    if (**request == MPI_REQUEST_NULL) {
        //printf("WRAP_Wait: request=%p *request=%p **request=MPI_REQUEST_NULL\n", request, *request);
        WRAP_Status_empty(ignore,status);
        return MPI_SUCCESS;
    }

    MPI_Status impl_status;

    int rc = IMPL_Wait(*request, ignore ? MPI_STATUS_IGNORE : &impl_status);

    *request = OUTPUT_MPI_REQUEST(impl_request);

    if (!ignore) {
        MPI_Status_to_WRAP_Status(&impl_status, status);
    }
#endif
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Waitall(int count, WRAP_Request array_of_requests[], WRAP_Status *array_of_statuses)
{
    //int rc = IMPL_Waitall(count, array_of_requests, array_of_statuses);
#if 0
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
            remove_cookie_pair_from_list(array_of_requests[i]);
            if (*array_of_requests[i] != MPI_REQUEST_NULL) {
                free(array_of_requests[i]);
            }
            array_of_requests[i] = &IMPL_REQUEST_NULL;
        }
    }
    free(impl_requests);

    // need to WRAP_Status_empty(status) somewhere here when request is null

    if (!ignore) {
        for (int i=0; i<count; i++) {
            MPI_Status_to_WRAP_Status(&impl_statuses[i], &array_of_statuses[i]);
        }
        free(impl_statuses);
    }
#endif
    //return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Waitany(int count, WRAP_Request array_of_requests[], int *indx, WRAP_Status *status)
{
    //int rc = IMPL_Waitany(count, array_of_requests, indx, status);
#if 0
    MPI_Request * impl_requests = malloc(count * sizeof(MPI_Request));
    if (impl_requests == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<count; i++) {
        impl_requests[i] = *array_of_requests[i];
    }

    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Status impl_status;

    int rc = IMPL_Waitany(count, impl_requests, indx, ignore ? MPI_STATUS_IGNORE : &impl_status);

    // If the list contains no active handles (list has length zero or all entries are null or inactive), then the call returns
    // immediately with index = MPI_UNDEFINED, and an empty status.
    if (*indx != MPI_UNDEFINED) {

        if (impl_requests[*indx] == MPI_REQUEST_NULL) {
            remove_cookie_pair_from_list(array_of_requests[*indx]);
            if (*array_of_requests[*indx] != MPI_REQUEST_NULL) {
                free(array_of_requests[*indx]);
            }
            array_of_requests[*indx] = &IMPL_REQUEST_NULL;
        }

        // need to WRAP_Status_empty(status) somewhere here when request is null

        if (!ignore) {
            MPI_Status_to_WRAP_Status(&impl_status, status);
        }
    }

    free(impl_requests);
#endif
    //return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Waitsome(int incount, WRAP_Request array_of_requests[], int *outcount, int array_of_indices[], WRAP_Status *array_of_statuses)
{
    //int rc = IMPL_Waitsome(incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
#if 0
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
                remove_cookie_pair_from_list(array_of_requests[j]);
                if (*array_of_requests[j] != MPI_REQUEST_NULL) {
                    free(array_of_requests[j]);
                }
                array_of_requests[j] = &IMPL_REQUEST_NULL;
            }
        }

        // need to WRAP_Status_empty(status) somewhere here when request is null

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
#endif
    //return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_allocate(WRAP_Aint size, int disp_unit, WRAP_Info info, WRAP_Comm comm, void *baseptr, WRAP_Win *win)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Win  impl_win;
    int rc = IMPL_Win_allocate(size, disp_unit, impl_info, impl_comm, baseptr, &impl_win);
    *win = OUTPUT_MPI_Win(impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Win_allocate_c(WRAP_Aint size, WRAP_Aint disp_unit, WRAP_Info info, WRAP_Comm comm, void *baseptr, WRAP_Win *win)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Win  impl_win;
    int rc = IMPL_Win_allocate_c(size, disp_unit, impl_info, impl_comm, baseptr, &impl_win);
    *win = OUTPUT_MPI_Win(impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Win_allocate_shared(WRAP_Aint size, int disp_unit, WRAP_Info info, WRAP_Comm comm, void *baseptr, WRAP_Win *win)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Win  impl_win;
    int rc = IMPL_Win_allocate_shared(size, disp_unit, impl_info, impl_comm, baseptr, &impl_win);
    *win = OUTPUT_MPI_Win(impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Win_allocate_shared_c(WRAP_Aint size, WRAP_Aint disp_unit, WRAP_Info info, WRAP_Comm comm, void *baseptr, WRAP_Win *win)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Win  impl_win;
    int rc = IMPL_Win_allocate_shared_c(size, disp_unit, impl_info, impl_comm, baseptr, &impl_win);
    *win = OUTPUT_MPI_Win(impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Win_attach(WRAP_Win win, void *base, WRAP_Aint size)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_attach(impl_win, base, size);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_call_errhandler(WRAP_Win win, int errorcode)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_call_errhandler(impl_win, errorcode);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_complete(WRAP_Win win)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_complete(impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_create(void *base, WRAP_Aint size, int disp_unit, WRAP_Info info, WRAP_Comm comm, WRAP_Win *win)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Win  impl_win;
    int rc = IMPL_Win_create(base, size, disp_unit, impl_info, impl_comm, &impl_win);
    *win = OUTPUT_MPI_Win(impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Win_create_c(void *base, WRAP_Aint size, WRAP_Aint disp_unit, WRAP_Info info, WRAP_Comm comm, WRAP_Win *win)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Win  impl_win;
    int rc = IMPL_Win_create_c(base, size, disp_unit, impl_info, impl_comm, &impl_win);
    *win = OUTPUT_MPI_Win(impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Win_create_dynamic(WRAP_Info info, WRAP_Comm comm, WRAP_Win *win)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Win  impl_win;
    int rc = IMPL_Win_create_dynamic(impl_info, impl_comm, &impl_win);
    *win = OUTPUT_MPI_Win(impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if 0
int WRAP_Win_create_errhandler(WRAP_Win_errhandler_function *win_errhandler_fn, WRAP_Errhandler *errhandler)
{
    int rc = IMPL_Win_create_errhandler(win_errhandler_fn, errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_create_keyval(WRAP_Win_copy_attr_function *win_copy_attr_fn, WRAP_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state)
{
    int rc = IMPL_Win_create_keyval(win_copy_attr_fn, win_delete_attr_fn, win_keyval, extra_state);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Win_delete_attr(WRAP_Win win, int win_keyval)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_delete_attr(impl_win, win_keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_detach(WRAP_Win win, const void *base)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_detach(impl_win, base);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_fence(int assert, WRAP_Win win)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_fence(assert, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_flush(int rank, WRAP_Win win)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_flush(rank, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_flush_all(WRAP_Win win)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_flush_all(impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_flush_local(int rank, WRAP_Win win)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_flush_local(rank, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_flush_local_all(WRAP_Win win)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_flush_local_all(impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_free(WRAP_Win *win)
{
    MPI_Win impl_win = CONVERT_MPI_Win(*win);
    int rc = IMPL_Win_free(&impl_win);
    *win = OUTPUT_MPI_Win(impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_free_keyval(int *win_keyval)
{
    int rc = IMPL_Win_free_keyval(win_keyval);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_get_attr(WRAP_Win win, int win_keyval, void *attribute_val, int *flag)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_get_attr(impl_win, win_keyval, attribute_val, flag);
    // this is the only place this is needed, so we inline it
    if (**(int**)attribute_val == MPI_WIN_SEPARATE) {
        **(int**)attribute_val = MUK_WIN_SEPARATE;
    } else if (**(int**)attribute_val == MPI_WIN_UNIFIED) {
        **(int**)attribute_val = MUK_WIN_UNIFIED;
    }
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_get_errhandler(WRAP_Win win, WRAP_Errhandler *errhandler)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_Win_get_errhandler(impl_win, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_get_group(WRAP_Win win, WRAP_Group *group)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    MPI_Group impl_group;
    int rc = IMPL_Win_get_group(impl_win, &impl_group);
    *group = OUTPUT_MPI_Group(impl_group);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_get_info(WRAP_Win win, WRAP_Info *info_used)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    MPI_Info impl_info_used;
    int rc = IMPL_Win_get_info(impl_win, &impl_info_used);
    *info_used = OUTPUT_MPI_Info(impl_info_used);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_get_name(WRAP_Win win, char *win_name, int *resultlen)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_get_name(impl_win, win_name, resultlen);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_lock(int lock_type, int rank, int assert, WRAP_Win win)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    // this is the only place this is used so we inline it
    int impl_type = MPI_UNDEFINED;
    if (lock_type == MUK_LOCK_EXCLUSIVE) {
        impl_type = MPI_LOCK_EXCLUSIVE;
    } else if (lock_type == MUK_LOCK_SHARED) {
        impl_type = MPI_LOCK_SHARED;
    }
    int rc = IMPL_Win_lock(impl_type, rank, assert, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_lock_all(int assert, WRAP_Win win)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_lock_all(assert, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_post(WRAP_Group group, int assert, WRAP_Win win)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_post(impl_group, assert, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_set_attr(WRAP_Win win, int win_keyval, void *attribute_val)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_set_attr(impl_win, win_keyval, attribute_val);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_set_errhandler(WRAP_Win win, WRAP_Errhandler errhandler)
{
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_set_errhandler(impl_win, impl_errhandler);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_set_info(WRAP_Win win, WRAP_Info info)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_set_info(impl_win, impl_info);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_set_name(WRAP_Win win, const char *win_name)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_set_name(impl_win, win_name);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_shared_query(WRAP_Win win, int rank, WRAP_Aint *size, int *disp_unit, void *baseptr)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_shared_query(impl_win, rank, size, disp_unit, baseptr);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Win_shared_query_c(WRAP_Win win, int rank, WRAP_Aint *size, WRAP_Aint *disp_unit, void *baseptr)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_shared_query_c(impl_win, rank, size, disp_unit, baseptr);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Win_start(WRAP_Group group, int assert, WRAP_Win win)
{
    MPI_Group impl_group = CONVERT_MPI_Group(group);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_start(impl_group, assert, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_sync(WRAP_Win win)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_sync(impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_test(WRAP_Win win, int *flag)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_test(impl_win, flag);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_unlock(int rank, WRAP_Win win)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_unlock(rank, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_unlock_all(WRAP_Win win)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_unlock_all(impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Win_wait(WRAP_Win win)
{
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Win_wait(impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include <mpi.h>

#include "muk-predefined.h"

#define MUK_EXTERN extern
#include "impl-fpointers.h"
#include "impl-linked-list.h"
#include "impl-constant-conversions.h"
#include "impl-handle-conversions.h"
#include "impl-alltoallw.h"

op_fptr_pair_t        * op_fptr_pair_list        = NULL;
req_cookie_pair_t     * req_cookie_pair_list     = NULL;
req_alltoallw_pair_t  * req_alltoallw_pair_list  = NULL;
comm_errh_fptr_pair_t * comm_errh_fptr_pair_list = NULL;
file_errh_fptr_pair_t * file_errh_fptr_pair_list = NULL;
win_errh_fptr_pair_t  * win_errh_fptr_pair_list  = NULL;

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
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Allgather(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Allgather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Allgather_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Allgather_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Allgather_init(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Allgather_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Allgather_init_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Allgatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Allgatherv(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Allgatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Allgatherv_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Allgatherv_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Allgatherv_init(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Allgatherv_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Allgatherv_init_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, impl_info, &impl_request);
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

int WRAP_Free_mem(void *base)
{
    int rc = IMPL_Free_mem(base);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Alltoall(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Alltoall(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Alltoall_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Alltoall_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Alltoall_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Alltoall_init(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Alltoall_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Alltoall_init_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Alltoallv(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Alltoallv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Alltoallv_c(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Alltoallv_init(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Alltoallv_init_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Alltoallv_init_c(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype * impl_sendtypes = NULL;
    MPI_Datatype * impl_recvtypes = NULL;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        printf("ALLTOALLW_SETUP failed: %d\n",rc);
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    rc = IMPL_Alltoallw(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm);
    if (sendtypes != NULL) free(impl_sendtypes);
    free(impl_recvtypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Alltoallw_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Datatype * impl_sendtypes = NULL;
    MPI_Datatype * impl_recvtypes = NULL;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    rc = IMPL_Alltoallw_c(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm);
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
    MPI_Datatype * impl_sendtypes = NULL;
    MPI_Datatype * impl_recvtypes = NULL;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    MPI_Request impl_request;
    rc = IMPL_Alltoallw_init(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, impl_info, &impl_request);
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
    MPI_Datatype * impl_sendtypes = NULL;
    MPI_Datatype * impl_recvtypes = NULL;
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    MPI_Request impl_request;
    rc = IMPL_Alltoallw_init_c(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    if (sendtypes != NULL) free(impl_sendtypes);
    free(impl_recvtypes);
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
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Bcast(buffer, count, impl_datatype, RANK_MUK_TO_IMPL(root), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Bcast_c(void *buffer, WRAP_Count count, WRAP_Datatype datatype, int root, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Bcast_c(buffer, count, impl_datatype, RANK_MUK_TO_IMPL(root), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Bcast_init(void *buffer, int count, WRAP_Datatype datatype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Bcast_init(buffer, count, impl_datatype, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Bcast_init_c(void *buffer, WRAP_Count count, WRAP_Datatype datatype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Bcast_init_c(buffer, count, impl_datatype, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Bsend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Bsend(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Bsend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Bsend_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Bsend_init(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Bsend_init(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Bsend_init_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Bsend_init_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
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

int WRAP_Errhandler_free(WRAP_Errhandler *errhandler)
{
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(*errhandler);
    //remove_errhandler(impl_errhandler);
    int rc = IMPL_Errhandler_free(&impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
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

int WRAP_Gather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Gather(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Gather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Gather_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Gather_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Gather_init(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Gather_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Gather_init_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Gatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Gatherv(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Gatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Gatherv_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Gatherv_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Gatherv_init(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Gatherv_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Gatherv_init_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Get_address(const void *location, WRAP_Aint *address)
{
    int rc = IMPL_Get_address(location, address);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Grequest_complete(WRAP_Request request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(request);
    int rc = IMPL_Grequest_complete(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Grequest_start(WRAP_Grequest_query_function *query_fn, WRAP_Grequest_free_function *free_fn, WRAP_Grequest_cancel_function *cancel_fn, void *extra_state, WRAP_Request *request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(*request);
    int rc = IMPL_Grequest_start(query_fn, free_fn, cancel_fn, extra_state, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Iallgather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Iallgather(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iallgather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Iallgather_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Iallgatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Iallgatherv(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iallgatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Iallgatherv_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ialltoall(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ialltoall(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ialltoall_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ialltoall_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ialltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ialltoallv(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ialltoallv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ialltoallv_c(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ialltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype * impl_sendtypes = NULL;
    MPI_Datatype * impl_recvtypes = NULL;
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Ialltoallw(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // THIS IS ILLEGAL - FIX IT
    //if (sendtypes != NULL) free(impl_sendtypes);
    //free(impl_recvtypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ialltoallw_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype * impl_sendtypes = NULL;
    MPI_Datatype * impl_recvtypes = NULL;
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Ialltoallw_c(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, &impl_request);
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
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ibcast(buffer, count, impl_datatype, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ibcast_c(void *buffer, WRAP_Count count, WRAP_Datatype datatype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ibcast_c(buffer, count, impl_datatype, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ibsend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ibsend(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ibsend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ibsend_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Igather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Igather(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Igather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Igather_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Igatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Igatherv(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Igatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    const bool   in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm     impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request  impl_request;
    int rc = IMPL_Igatherv_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Improbe(int source, int tag, WRAP_Comm comm, int *flag, WRAP_Message *message, WRAP_Status *status)
{
    const bool  ignore = IS_STATUS_IGNORE(status);
    MPI_Comm    impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Message impl_message  = CONVERT_MPI_Message(*message);;
    MPI_Status  impl_status = {0};
    int rc = IMPL_Improbe(RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), impl_comm, flag, &impl_message, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    *message = OUTPUT_MPI_Message(impl_message);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Imrecv(void *buf, int count, WRAP_Datatype datatype, WRAP_Message *message, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Message  impl_message  = CONVERT_MPI_Message(*message);;
    MPI_Request  impl_request;
    int rc = IMPL_Imrecv(buf, count, impl_datatype, &impl_message, &impl_request);
    *message = OUTPUT_MPI_Message(impl_message);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Imrecv_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Message *message, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Message  impl_message  = CONVERT_MPI_Message(*message);;
    MPI_Request  impl_request;
    int rc = IMPL_Imrecv_c(buf, count, impl_datatype, &impl_message, &impl_request);
    *message = OUTPUT_MPI_Message(impl_message);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_allgather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool   in_place      = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm     impl_comm     = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_allgather(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ineighbor_allgather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_allgather_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ineighbor_allgatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_allgatherv(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ineighbor_allgatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_allgatherv_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ineighbor_alltoall(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_alltoall(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ineighbor_alltoall_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_alltoall_c(in_place ? MPI_IN_PLACE : sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ineighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_alltoallv(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ineighbor_alltoallv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ineighbor_alltoallv_c(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ineighbor_alltoallw(const void *sendbuf, const int sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype * impl_sendtypes = NULL;
    MPI_Datatype * impl_recvtypes = NULL;
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Ineighbor_alltoallw(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    // THIS IS ILLEGAL - FIX IT
    //if (sendtypes != NULL) free(impl_sendtypes);
    //free(impl_recvtypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ineighbor_alltoallw_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], const WRAP_Datatype sendtypes[], void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], const WRAP_Datatype recvtypes[], WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(sendbuf);
    MPI_Datatype * impl_sendtypes = NULL;
    MPI_Datatype * impl_recvtypes = NULL;
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = ALLTOALLW_SETUP(in_place, impl_comm, sendtypes, recvtypes, &impl_sendtypes, &impl_recvtypes);
    if (rc != MPI_SUCCESS) {
        return RETURN_CODE_IMPL_TO_MUK(rc);
    }
    MPI_Request impl_request;
    rc = IMPL_Ineighbor_alltoallw_c(in_place ? MPI_IN_PLACE : sendbuf, sendcounts, sdispls, impl_sendtypes, recvbuf, recvcounts, rdispls, impl_recvtypes, impl_comm, &impl_request);
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
#elif 1
    MPI_Info impl_info = CONVERT_MPI_Info(info);

    // valuelen does not include the null terminator
    int valuelen;
    rc = IMPL_Info_get_valuelen(impl_info, key, &valuelen, flag);
    if (!flag) goto end;

    const int inbuflen = *buflen;

    // In C, buflen includes the required space for the null terminator.
    *buflen = valuelen + 1;

    // The MPI_INFO_GET_STRING function can be used to obtain the size of the
    // required buffer for a value string by setting the buflen to 0.
    if (inbuflen == 0) goto end;

    rc = IMPL_Info_get(impl_info, key, inbuflen, value, flag);
    if (!flag) goto end;
    end:
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

int WRAP_Iprobe(int source, int tag, WRAP_Comm comm, int *flag, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Status impl_status = {0};
    int rc = IMPL_Iprobe(RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), impl_comm, flag, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Irecv(void *buf, int count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Irecv(buf, count, impl_datatype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Irecv_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Irecv_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Irsend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Irsend(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Irsend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Irsend_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Iscatter(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(recvbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Iscatter(sendbuf, sendcount, impl_sendtype, in_place ? MPI_IN_PLACE : recvbuf,recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iscatter_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(recvbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Iscatter_c(sendbuf, sendcount, impl_sendtype, in_place ? MPI_IN_PLACE : recvbuf,recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Iscatterv(const void *sendbuf, const int sendcounts[], const int displs[], WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(recvbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Iscatterv(sendbuf, sendcounts, displs, impl_sendtype, in_place ? MPI_IN_PLACE : recvbuf,recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Iscatterv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint displs[], WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(recvbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Iscatterv_c(sendbuf, sendcounts, displs, impl_sendtype, in_place ? MPI_IN_PLACE : recvbuf,recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Isend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Isend(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Isend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Isend_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_Isendrecv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int source, int recvtag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Isendrecv(sendbuf, sendcount, impl_sendtype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(sendtag), recvbuf, recvcount, impl_recvtype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(recvtag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_Isendrecv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, int dest, int sendtag, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int source, int recvtag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Isendrecv_c(sendbuf, sendcount, impl_sendtype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(sendtag), recvbuf, recvcount, impl_recvtype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(recvtag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_Isendrecv_replace(void *buf, int count, WRAP_Datatype datatype, int dest, int sendtag, int source, int recvtag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Isendrecv_replace(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(sendtag), RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(recvtag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_Isendrecv_replace_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int sendtag, int source, int recvtag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Isendrecv_replace_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(sendtag), RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(recvtag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Issend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Issend(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Issend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Issend_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Mprobe(int source, int tag, WRAP_Comm comm, WRAP_Message *message, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Message impl_message;
    MPI_Status impl_status = {0};
    int rc = IMPL_Mprobe(RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_message, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    *message = OUTPUT_MPI_Message(impl_message);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Mrecv(void *buf, int count, WRAP_Datatype datatype, WRAP_Message *message, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Message  impl_message  = CONVERT_MPI_Message(*message);;
    MPI_Status impl_status = {0};
    int rc = IMPL_Mrecv(buf, count, impl_datatype, &impl_message, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    *message = OUTPUT_MPI_Message(impl_message);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Mrecv_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Message *message, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Message  impl_message  = CONVERT_MPI_Message(*message);;
    MPI_Status impl_status = {0};
    int rc = IMPL_Mrecv_c(buf, count, impl_datatype, &impl_message, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    *message = OUTPUT_MPI_Message(impl_message);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Neighbor_allgather(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Neighbor_allgather(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_allgather_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Neighbor_allgather_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_allgather_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_allgather_init(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_allgather_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_allgather_init_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_allgatherv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Neighbor_allgatherv(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_allgatherv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Neighbor_allgatherv_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_allgatherv_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_allgatherv_init(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_allgatherv_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint displs[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_allgatherv_init_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcounts, displs, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_alltoall(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Neighbor_alltoall(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_alltoall_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Neighbor_alltoall_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_alltoall_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_alltoall_init(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_alltoall_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_alltoall_init_c(sendbuf, sendcount, impl_sendtype, recvbuf, recvcount, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Neighbor_alltoallv(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_alltoallv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Neighbor_alltoallv_c(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Neighbor_alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], WRAP_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Neighbor_alltoallv_init(sendbuf, sendcounts, sdispls, impl_sendtype, recvbuf, recvcounts, rdispls, impl_recvtype, impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Neighbor_alltoallv_init_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint sdispls[], WRAP_Datatype sendtype, void *recvbuf, const WRAP_Count recvcounts[], const WRAP_Aint rdispls[], WRAP_Datatype recvtype, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
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
    MPI_Datatype * impl_sendtypes = NULL;
    MPI_Datatype * impl_recvtypes = NULL;
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
    MPI_Datatype * impl_sendtypes = NULL;
    MPI_Datatype * impl_recvtypes = NULL;
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
    MPI_Datatype * impl_sendtypes = NULL;
    MPI_Datatype * impl_recvtypes = NULL;
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
    MPI_Datatype * impl_sendtypes = NULL;
    MPI_Datatype * impl_recvtypes = NULL;
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

int WRAP_Pack(const void *inbuf, int incount, WRAP_Datatype datatype, void *outbuf, int outsize, int *position, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Pack(inbuf, incount, impl_datatype, outbuf, outsize, position, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Pack_c(const void *inbuf, WRAP_Count incount, WRAP_Datatype datatype, void *outbuf, WRAP_Count outsize, WRAP_Count *position, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
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
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Pack_size(incount, impl_datatype, impl_comm, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Pack_size_c(WRAP_Count incount, WRAP_Datatype datatype, WRAP_Comm comm, WRAP_Count *size)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
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
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Precv_init(buf, partitions, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Probe(int source, int tag, WRAP_Comm comm, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Status impl_status = {0};
    int rc = IMPL_Probe(RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Psend_init(const void *buf, int partitions, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Psend_init(buf, partitions, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Recv(void *buf, int count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Status impl_status = {0};
    int rc = IMPL_Recv(buf, count, impl_datatype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Recv_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Status impl_status = {0};
    int rc = IMPL_Recv_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), impl_comm, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Recv_init(void *buf, int count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Recv_init(buf, count, impl_datatype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Recv_init_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int source, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Recv_init_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
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
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Rsend(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Rsend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Rsend_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Rsend_init(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Rsend_init(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Rsend_init_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Rsend_init_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Scatter(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(recvbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Scatter(sendbuf, sendcount, impl_sendtype, in_place ? MPI_IN_PLACE : recvbuf, recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scatter_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(recvbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Scatter_c(sendbuf, sendcount, impl_sendtype, in_place ? MPI_IN_PLACE : recvbuf,recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Scatter_init(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(recvbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Scatter_init(sendbuf, sendcount, impl_sendtype, in_place ? MPI_IN_PLACE : recvbuf,recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scatter_init_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(recvbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Scatter_init_c(sendbuf, sendcount, impl_sendtype, in_place ? MPI_IN_PLACE : recvbuf,recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(recvbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Scatterv(sendbuf, sendcounts, displs, impl_sendtype, in_place ? MPI_IN_PLACE : recvbuf,recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scatterv_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint displs[], WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm)
{
    const bool in_place = IS_IN_PLACE(recvbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Scatterv_c(sendbuf, sendcounts, displs, impl_sendtype, in_place ? MPI_IN_PLACE : recvbuf,recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Scatterv_init(const void *sendbuf, const int sendcounts[], const int displs[], WRAP_Datatype sendtype, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(recvbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Scatterv_init(sendbuf, sendcounts, displs, impl_sendtype, in_place ? MPI_IN_PLACE : recvbuf,recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Scatterv_init_c(const void *sendbuf, const WRAP_Count sendcounts[], const WRAP_Aint displs[], WRAP_Datatype sendtype, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int root, WRAP_Comm comm, WRAP_Info info, WRAP_Request *request)
{
    const bool in_place = IS_IN_PLACE(recvbuf);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Request impl_request;
    int rc = IMPL_Scatterv_init_c(sendbuf, sendcounts, displs, impl_sendtype, in_place ? MPI_IN_PLACE : recvbuf,recvcount, impl_recvtype, RANK_MUK_TO_IMPL(root), impl_comm, impl_info, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Send(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Send(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Send_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Send_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Send_init(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Send_init(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Send_init_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Send_init_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Sendrecv(const void *sendbuf, int sendcount, WRAP_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, WRAP_Datatype recvtype, int source, int recvtag, WRAP_Comm comm, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Status impl_status = {0};
    int rc = IMPL_Sendrecv(sendbuf, sendcount, impl_sendtype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(sendtag), recvbuf, recvcount, impl_recvtype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(recvtag), impl_comm, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Sendrecv_c(const void *sendbuf, WRAP_Count sendcount, WRAP_Datatype sendtype, int dest, int sendtag, void *recvbuf, WRAP_Count recvcount, WRAP_Datatype recvtype, int source, int recvtag, WRAP_Comm comm, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Datatype impl_sendtype = CONVERT_MPI_Datatype(sendtype);
    MPI_Datatype impl_recvtype = CONVERT_MPI_Datatype(recvtype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Status impl_status = {0};
    int rc = IMPL_Sendrecv_c(sendbuf, sendcount, impl_sendtype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(sendtag), recvbuf, recvcount, impl_recvtype, RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(recvtag), impl_comm, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Sendrecv_replace(void *buf, int count, WRAP_Datatype datatype, int dest, int sendtag, int source, int recvtag, WRAP_Comm comm, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Status impl_status = {0};
    int rc = IMPL_Sendrecv_replace(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(sendtag), RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(recvtag), impl_comm, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Sendrecv_replace_c(void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int sendtag, int source, int recvtag, WRAP_Comm comm, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Status impl_status = {0};
    int rc = IMPL_Sendrecv_replace_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(sendtag), RANK_MUK_TO_IMPL(source), TAG_MUK_TO_IMPL(recvtag), impl_comm, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Ssend(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Ssend(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ssend_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Ssend_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Ssend_init(const void *buf, int count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ssend_init(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Ssend_init_c(const void *buf, WRAP_Count count, WRAP_Datatype datatype, int dest, int tag, WRAP_Comm comm, WRAP_Request *request)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Request impl_request;
    int rc = IMPL_Ssend_init_c(buf, count, impl_datatype, RANK_MUK_TO_IMPL(dest), TAG_MUK_TO_IMPL(tag), impl_comm, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, WRAP_Datatype datatype, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    int rc = IMPL_Unpack(inbuf, insize, position, outbuf, outcount, impl_datatype, impl_comm);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Unpack_c(const void *inbuf, WRAP_Count insize, WRAP_Count *position, void *outbuf, WRAP_Count outcount, WRAP_Datatype datatype, WRAP_Comm comm)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
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

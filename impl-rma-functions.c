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
#include "impl-constant-conversions.h"
#include "impl-handle-conversions.h"

// WRAP->IMPL functions

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

int WRAP_Compare_and_swap(const void *origin_addr, const void *compare_addr, void *result_addr, WRAP_Datatype datatype, int target_rank, WRAP_Aint target_disp, WRAP_Win win)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Compare_and_swap(origin_addr, compare_addr, result_addr, impl_datatype, target_rank, target_disp, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Fetch_and_op(const void *origin_addr, void *result_addr, WRAP_Datatype datatype, int target_rank, WRAP_Aint target_disp, WRAP_Op op, WRAP_Win win)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Op impl_op = CONVERT_MPI_Op(op);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
    int rc = IMPL_Fetch_and_op(origin_addr, result_addr, impl_datatype, target_rank, target_disp, impl_op, impl_win);
    return ERROR_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get(void *origin_addr, int origin_count, WRAP_Datatype origin_datatype, int target_rank, WRAP_Aint target_disp, int target_count, WRAP_Datatype target_datatype, WRAP_Win win)
{
    MPI_Datatype impl_origin_datatype = CONVERT_MPI_Datatype(origin_datatype);
    MPI_Datatype impl_target_datatype = CONVERT_MPI_Datatype(target_datatype);
    MPI_Win impl_win = CONVERT_MPI_Win(win);
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

#if MPI_VERSION >= 4
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
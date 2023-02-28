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
#include "impl-constant-conversions.h"
#include "impl-handle-conversions.h"

int WRAP_File_call_errhandler(WRAP_File fh, int errorcode)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_call_errhandler(impl_fh, errorcode);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_close(WRAP_File *fh)
{
    MPI_File impl_fh = CONVERT_MPI_File(*fh);
    int rc = IMPL_File_close(&impl_fh);
    *fh = OUTPUT_MPI_File(impl_fh);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_create_errhandler(WRAP_File_errhandler_function *file_errhandler_fn, WRAP_Errhandler *errhandler)
{
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_File_create_errhandler(file_errhandler_fn, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_delete(const char *filename, WRAP_Info info)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_File_delete(filename, impl_info);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_amode(WRAP_File fh, int *amode)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int impl_amode;
    int rc = IMPL_File_get_amode(impl_fh, &impl_amode);
    *amode = IO_MODE_IMPL_TO_MUK(impl_amode);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_atomicity(WRAP_File fh, int *flag)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_get_atomicity(impl_fh, flag);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_byte_offset(WRAP_File fh, WRAP_Offset offset, WRAP_Offset *disp)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_get_byte_offset(impl_fh, offset, disp);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_errhandler(WRAP_File file, WRAP_Errhandler *errhandler)
{
    MPI_File impl_file = CONVERT_MPI_File(file);
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_File_get_errhandler(impl_file, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_group(WRAP_File fh, WRAP_Group *group)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Group impl_group;
    int rc = IMPL_File_get_group(impl_fh, &impl_group);
    *group = OUTPUT_MPI_Group(impl_group);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_info(WRAP_File fh, WRAP_Info *info_used)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Info impl_info_used;
    int rc = IMPL_File_get_info(impl_fh, &impl_info_used);
    *info_used = OUTPUT_MPI_Info(impl_info_used);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_position(WRAP_File fh, WRAP_Offset *offset)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_get_position(impl_fh, offset);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_position_shared(WRAP_File fh, WRAP_Offset *offset)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_get_position_shared(impl_fh, offset);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_size(WRAP_File fh, WRAP_Offset *size)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_get_size(impl_fh, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_get_type_extent(WRAP_File fh, WRAP_Datatype datatype, WRAP_Aint *extent)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_File_get_type_extent(impl_fh, impl_datatype, extent);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_get_type_extent_c(WRAP_File fh, WRAP_Datatype datatype, WRAP_Count *extent)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_File_get_type_extent_c(impl_fh, impl_datatype, extent);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_get_view(WRAP_File fh, WRAP_Offset *disp, WRAP_Datatype *etype, WRAP_Datatype *filetype, char *datarep)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_etype, impl_filetype;
    int rc = IMPL_File_get_view(impl_fh, disp, &impl_etype, &impl_filetype, datarep);
    *etype = OUTPUT_MPI_Datatype(impl_etype);
    *filetype = OUTPUT_MPI_Datatype(impl_filetype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iread(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread_all(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_all(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_iread_all_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_all_c(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_iread_at(WRAP_File fh, WRAP_Offset offset, void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_at(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iread_at_all(WRAP_File fh, WRAP_Offset offset, void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_at_all(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_iread_at_all_c(WRAP_File fh, WRAP_Offset offset, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_at_all_c(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_File_iread_at_c(WRAP_File fh, WRAP_Offset offset, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_at_c(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_File_iread_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_c(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_iread_shared(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_shared(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_iread_shared_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iread_shared_c(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_iwrite(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iwrite_all(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_all(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_iwrite_all_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_all_c(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_iwrite_at(WRAP_File fh, WRAP_Offset offset, const void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_at(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_iwrite_at_all(WRAP_File fh, WRAP_Offset offset, const void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_at_all(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_iwrite_at_all_c(WRAP_File fh, WRAP_Offset offset, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_at_all_c(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_File_iwrite_at_c(WRAP_File fh, WRAP_Offset offset, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_at_c(impl_fh, offset, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_File_iwrite_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_c(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_iwrite_shared(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_shared(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_iwrite_shared_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Request *request)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Request impl_request;
    int rc = IMPL_File_iwrite_shared_c(impl_fh, buf, count, impl_datatype, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_open(WRAP_Comm comm, const char *filename, int amode, WRAP_Info info, WRAP_File *fh)
{
    MPI_Comm impl_comm = CONVERT_MPI_Comm(comm);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_File impl_fh;
    int rc = IMPL_File_open(impl_comm, filename, IO_MODE_MUK_TO_IMPL(amode), impl_info, &impl_fh);
    *fh = OUTPUT_MPI_File(impl_fh);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_preallocate(WRAP_File fh, WRAP_Offset size)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_preallocate(impl_fh, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_all(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read_all(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_all_begin(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_File_read_all_begin(impl_fh, buf, count, impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_read_all_begin_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_File_read_all_begin_c(impl_fh, buf, count, impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_read_all_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read_all_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_all_end(WRAP_File fh, void *buf, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read_all_end(impl_fh, buf, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at(WRAP_File fh, WRAP_Offset offset, void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read_at(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at_all(WRAP_File fh, WRAP_Offset offset, void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read_at_all(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at_all_begin(WRAP_File fh, WRAP_Offset offset, void *buf, int count, WRAP_Datatype datatype)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_File_read_at_all_begin(impl_fh, offset, buf, count, impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_read_at_all_begin_c(WRAP_File fh, WRAP_Offset offset, void *buf, WRAP_Count count, WRAP_Datatype datatype)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_File_read_at_all_begin_c(impl_fh, offset, buf, count, impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_read_at_all_c(WRAP_File fh, WRAP_Offset offset, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read_at_all_c(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at_all_end(WRAP_File fh, void *buf, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read_at_all_end(impl_fh, buf, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_at_c(WRAP_File fh, WRAP_Offset offset, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read_at_c(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_ordered(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read_ordered(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_ordered_begin(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_File_read_ordered_begin(impl_fh, buf, count, impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_read_ordered_begin_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_File_read_ordered_begin_c(impl_fh, buf, count, impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_read_ordered_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read_ordered_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_ordered_end(WRAP_File fh, void *buf, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read_ordered_end(impl_fh, buf, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_shared(WRAP_File fh, void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read_shared(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_read_shared_c(WRAP_File fh, void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_read_shared_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_seek(WRAP_File fh, WRAP_Offset offset, int whence)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_seek(impl_fh, offset, whence);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_seek_shared(WRAP_File fh, WRAP_Offset offset, int whence)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_seek_shared(impl_fh, offset, whence);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_atomicity(WRAP_File fh, int flag)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_set_atomicity(impl_fh, flag);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_errhandler(WRAP_File file, WRAP_Errhandler errhandler)
{
    MPI_File impl_file = CONVERT_MPI_File(file);
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    int rc = IMPL_File_set_errhandler(impl_file, impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_info(WRAP_File fh, WRAP_Info info)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_File_set_info(impl_fh, impl_info);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_size(WRAP_File fh, WRAP_Offset size)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_set_size(impl_fh, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_set_view(WRAP_File fh, WRAP_Offset disp, WRAP_Datatype etype, WRAP_Datatype filetype, const char *datarep, WRAP_Info info)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_etype = CONVERT_MPI_Datatype(etype);
    MPI_Datatype impl_filetype = CONVERT_MPI_Datatype(filetype);
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    int rc = IMPL_File_set_view(impl_fh, disp, impl_etype, impl_filetype, datarep, impl_info);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_sync(WRAP_File fh)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    int rc = IMPL_File_sync(impl_fh);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_all(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write_all(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_all_begin(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_File_write_all_begin(impl_fh, buf, count, impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_write_all_begin_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_File_write_all_begin_c(impl_fh, buf, count, impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_write_all_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write_all_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_all_end(WRAP_File fh, const void *buf, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write_all_end(impl_fh, buf, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at(WRAP_File fh, WRAP_Offset offset, const void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write_at(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at_all(WRAP_File fh, WRAP_Offset offset, const void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write_at_all(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at_all_begin(WRAP_File fh, WRAP_Offset offset, const void *buf, int count, WRAP_Datatype datatype)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_File_write_at_all_begin(impl_fh, offset, buf, count, impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_write_at_all_begin_c(WRAP_File fh, WRAP_Offset offset, const void *buf, WRAP_Count count, WRAP_Datatype datatype)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_File_write_at_all_begin_c(impl_fh, offset, buf, count, impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_write_at_all_c(WRAP_File fh, WRAP_Offset offset, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write_at_all_c(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at_all_end(WRAP_File fh, const void *buf, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write_at_all_end(impl_fh, buf, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_at_c(WRAP_File fh, WRAP_Offset offset, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write_at_c(impl_fh, offset, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_ordered(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write_ordered(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_ordered_begin(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_File_write_ordered_begin(impl_fh, buf, count, impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_File_write_ordered_begin_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype)
{
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_File_write_ordered_begin_c(impl_fh, buf, count, impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_File_write_ordered_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write_ordered_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_ordered_end(WRAP_File fh, const void *buf, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write_ordered_end(impl_fh, buf, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_shared(WRAP_File fh, const void *buf, int count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write_shared(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_File_write_shared_c(WRAP_File fh, const void *buf, WRAP_Count count, WRAP_Datatype datatype, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_File impl_fh = CONVERT_MPI_File(fh);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    int rc = IMPL_File_write_shared_c(impl_fh, buf, count, impl_datatype, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

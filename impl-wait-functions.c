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
#include "impl-keyval-map.h"

int WRAP_Cancel(WRAP_Request *request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(*request);
    int rc = IMPL_Cancel(&impl_request);
    // It is erroneous to call MPI_REQUEST_FREE or MPI_CANCEL for a request
    // associated with a nonblocking collective operation.
    //remove_cookie_pair_from_list(CONVERT_MPI_Request(*request));
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_count(const WRAP_Status *status, WRAP_Datatype datatype, int *count)
{
    MPI_Status impl_status = {0};
    WRAP_Status_to_MPI_Status(status, &impl_status);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Get_count(&impl_status, impl_datatype, count);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_count_c(const WRAP_Status *status, WRAP_Datatype datatype, WRAP_Count *count)
{
    MPI_Status impl_status = {0};
    WRAP_Status_to_MPI_Status(status, &impl_status);
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Get_count_c(&impl_status, impl_datatype, count);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_elements(const WRAP_Status *status, WRAP_Datatype datatype, int *count)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Get_elements(&impl_status, impl_datatype, count);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_elements_c(const WRAP_Status *status, WRAP_Datatype datatype, WRAP_Count *count)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Get_elements_c(&impl_status, impl_datatype, count);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Get_elements_x(const WRAP_Status *status, WRAP_Datatype datatype, WRAP_Count *count)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Get_elements_x(&impl_status, impl_datatype, count);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Request_free(WRAP_Request *request)
{
    int rc;
    MPI_Request impl_request = CONVERT_MPI_Request(*request);
    // look up the request before it is freed, because that will change it to MPI_REQUEST_NULL
    {
        MPI_Datatype * sendtypes = NULL;
        MPI_Datatype * recvtypes = NULL;
        int found = find_persistent_request_alltoallw_buffers(impl_request, &sendtypes, &recvtypes);
        if (found) {
            if (sendtypes != NULL) {
                free(sendtypes);
                sendtypes = NULL;
            }
            if (recvtypes != NULL) {
                free(recvtypes);
                recvtypes = NULL;
            }
            remove_persistent_request_alltoallw_buffers(impl_request);
        }
    }
    rc = IMPL_Request_free(&impl_request);
    if (rc) goto end;
    // It is erroneous to call MPI_REQUEST_FREE or MPI_CANCEL for a request
    // associated with a nonblocking collective operation.
    *request = OUTPUT_MPI_Request(impl_request);
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Request_get_status(WRAP_Request request, int *flag, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Request impl_request = CONVERT_MPI_Request(request);
    MPI_Status impl_status = {0};
    if (impl_request == MPI_REQUEST_NULL) {
        *flag = 1;
        if (!ignore) WRAP_Status_empty(false,status);
        return MPI_SUCCESS;
    }
    int rc = IMPL_Request_get_status(impl_request, flag, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (*flag) {
        if (!ignore) MPI_Status_to_WRAP_Status(&impl_status, status);
    }
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Start(WRAP_Request *request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(*request);
    int rc = IMPL_Start(&impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Startall(int count, WRAP_Request array_of_requests[])
{
    MPI_Request * impl_array_of_requests = calloc(count,sizeof(MPI_Request));
    for (int i=0; i<count; i++) {
        impl_array_of_requests[i] = CONVERT_MPI_Request(array_of_requests[i]);
    }
    int rc = IMPL_Startall(count, impl_array_of_requests);
    for (int i=0; i<count; i++) {
        array_of_requests[i] = OUTPUT_MPI_Request(impl_array_of_requests[i]);
    }
    free(impl_array_of_requests);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#ifdef SUPPORT_F08
int WRAP_Status_f082c(const WRAP_F08_status *f08_status, WRAP_Status *c_status)
{
    int rc = IMPL_Status_f082c(f08_status, c_status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Status_f082f(const WRAP_F08_status *f08_status, WRAP_Fint *f_status)
{
    int rc = IMPL_Status_f082f(f08_status, f_status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Status_f2f08(const WRAP_Fint *f_status, WRAP_F08_status *f08_status)
{
    int rc = IMPL_Status_f2f08(f_status, f08_status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Status_set_cancelled(WRAP_Status *status, int flag)
{
    MPI_Status impl_status = {0};
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Status_set_cancelled(&impl_status, flag);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Status_set_elements(WRAP_Status *status, WRAP_Datatype datatype, int count)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Status_set_elements(&impl_status, impl_datatype, count);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Status_set_elements_c(WRAP_Status *status, WRAP_Datatype datatype, WRAP_Count count)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Status_set_elements_c(&impl_status, impl_datatype, count);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Status_set_elements_x(WRAP_Status *status, WRAP_Datatype datatype, WRAP_Count count)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Status impl_status = {0};
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Status_set_elements_x(&impl_status, impl_datatype, count);
    MPI_Status_to_WRAP_Status(&impl_status, status);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Test(WRAP_Request *request, int *flag, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Request impl_request = CONVERT_MPI_Request(*request);
    MPI_Status impl_status = {0};
    int rc = IMPL_Test(&impl_request, flag, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (*flag) {
        if (!ignore) {
            MPI_Status_to_WRAP_Status(&impl_status, status);
        }
        //remove_cookie_pair_from_list(CONVERT_MPI_Request(*request));
        *request = OUTPUT_MPI_Request(impl_request);
    }
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Test_cancelled(const WRAP_Status *status, int *flag)
{
    MPI_Status impl_status = {0};
    WRAP_Status_to_MPI_Status(status, &impl_status);
    int rc = IMPL_Test_cancelled(&impl_status, flag);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Testall(int count, WRAP_Request array_of_requests[], int *flag, WRAP_Status *array_of_statuses)
{
    const bool ignore = IS_STATUSES_IGNORE(array_of_statuses);

    MPI_Request * impl_requests = calloc(count,sizeof(MPI_Request));
    if (impl_requests == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<count; i++) {
        impl_requests[i] = CONVERT_MPI_Request(array_of_requests[i]);
    }

    MPI_Status * impl_statuses = NULL;
    if (!ignore) {
        impl_statuses = calloc(count, sizeof(MPI_Status));
        if (impl_statuses == NULL) return MPI_ERR_INTERN;
    }

    int rc = IMPL_Testall(count, impl_requests, flag, ignore ? MPI_STATUSES_IGNORE : impl_statuses);

    if (*flag) {
        for (int i=0; i<count; i++) {
            if (!ignore) {
                MPI_Status_to_WRAP_Status(&impl_statuses[i], &array_of_statuses[i]);
            }
            if (impl_requests[i] == MPI_REQUEST_NULL) {
                //remove_cookie_pair_from_list(CONVERT_MPI_Request(array_of_requests[i]));
            }
            array_of_requests[i] = OUTPUT_MPI_Request(impl_requests[i]);
        }
    }

    free(impl_requests);
    if (!ignore) free(impl_statuses);

    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Testany(int count, WRAP_Request array_of_requests[], int *indx, int *flag, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);

    MPI_Request * impl_requests = calloc(count,sizeof(MPI_Request));
    if (impl_requests == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<count; i++) {
        impl_requests[i] = CONVERT_MPI_Request(array_of_requests[i]);
    }

    MPI_Status impl_status = {0};
    int rc = IMPL_Testany(count, impl_requests, indx, flag, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (*flag) {
        // If the array contains no active handles then the call returns immediately
        // with flag = true, index = MPI_UNDEFINED, and an empty status.
        if (*indx != MPI_UNDEFINED) {
            if (!ignore) {
                MPI_Status_to_WRAP_Status(&impl_status, status);
            }
            if (impl_requests[*indx] == MPI_REQUEST_NULL) {
                //remove_cookie_pair_from_list(CONVERT_MPI_Request(array_of_requests[*indx]));
            }
            array_of_requests[*indx] = OUTPUT_MPI_Request(impl_requests[*indx]);
        }
    }

    free(impl_requests);

    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Testsome(int incount, WRAP_Request array_of_requests[], int *outcount, int array_of_indices[], WRAP_Status *array_of_statuses)
{
    const bool ignore = IS_STATUSES_IGNORE(array_of_statuses);

    MPI_Request * impl_requests = calloc(incount,sizeof(MPI_Request));
    if (impl_requests == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<incount; i++) {
        impl_requests[i] = CONVERT_MPI_Request(array_of_requests[i]);
    }

    MPI_Status * impl_statuses = NULL;
    if (!ignore) {
        impl_statuses = calloc(incount, sizeof(MPI_Status));
        if (impl_statuses == NULL) return MPI_ERR_INTERN;
    }

    int rc = IMPL_Testsome(incount, impl_requests, outcount, array_of_indices, ignore ? MPI_STATUSES_IGNORE : impl_statuses);

    if ((*outcount > 0) && (*outcount != MPI_UNDEFINED)) {
        for (int i=0; i<*outcount; i++) {
            const int j = array_of_indices[i];
            if (!ignore) {
                MPI_Status_to_WRAP_Status(&impl_statuses[j], &array_of_statuses[j]);
            }
            if (impl_requests[j] == MPI_REQUEST_NULL) {
                //remove_cookie_pair_from_list(CONVERT_MPI_Request(array_of_requests[j]));
            }
            array_of_requests[j] = OUTPUT_MPI_Request(impl_requests[j]);
        }
    }

    free(impl_requests);
    if (!ignore) free(impl_statuses);

    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Wait(WRAP_Request *request, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);
    MPI_Request impl_request = CONVERT_MPI_Request(*request);
    MPI_Status impl_status = {0};
    int rc = IMPL_Wait(&impl_request, ignore ? MPI_STATUS_IGNORE : &impl_status);
    if (!ignore) {
        MPI_Status_to_WRAP_Status(&impl_status, status);
    }
    //remove_cookie_pair_from_list(CONVERT_MPI_Request(*request));
    *request = OUTPUT_MPI_Request(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Waitall(int count, WRAP_Request array_of_requests[], WRAP_Status *array_of_statuses)
{
    const bool ignore = IS_STATUSES_IGNORE(array_of_statuses);

    MPI_Request * impl_requests = calloc(count,sizeof(MPI_Request));
    if (impl_requests == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<count; i++) {
        impl_requests[i] = CONVERT_MPI_Request(array_of_requests[i]);
    }

    MPI_Status * impl_statuses = NULL;
    if (!ignore) {
        impl_statuses = calloc(count, sizeof(MPI_Status));
        if (impl_statuses == NULL) return MPI_ERR_INTERN;
    }

    int rc = IMPL_Waitall(count, impl_requests, ignore ? MPI_STATUSES_IGNORE : impl_statuses);

    // Active persistent requests are marked inactive. Requests of any other type are
    // deallocated and the corresponding handles in the array are set to MPI_REQUEST_NULL.
    // The list may contain null or inactive handles. The call sets to empty the status of
    // each such entry.
    for (int i=0; i<count; i++) {
        if (!ignore) {
            MPI_Status_to_WRAP_Status(&impl_statuses[i], &array_of_statuses[i]);
        }
        if (impl_requests[i] == MPI_REQUEST_NULL) {
            //remove_cookie_pair_from_list(CONVERT_MPI_Request(array_of_requests[i]));
        }
        array_of_requests[i] = OUTPUT_MPI_Request(impl_requests[i]);
    }

    free(impl_requests);
    if (!ignore) free(impl_statuses);

    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Waitany(int count, WRAP_Request array_of_requests[], int *indx, WRAP_Status *status)
{
    const bool ignore = IS_STATUS_IGNORE(status);

    MPI_Request * impl_requests = calloc(count,sizeof(MPI_Request));
    if (impl_requests == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<count; i++) {
        impl_requests[i] = CONVERT_MPI_Request(array_of_requests[i]);
    }

    MPI_Status impl_status = {0};
    int rc = IMPL_Waitany(count, impl_requests, indx, ignore ? MPI_STATUS_IGNORE : &impl_status);

    // If the list contains no active handles (list has length zero
    // or all entries are null or inactive), then the call returns
    // immediately with index = MPI_UNDEFINED, and an empty status.
    if (*indx != MPI_UNDEFINED) {
        if (!ignore) {
            MPI_Status_to_WRAP_Status(&impl_status, status);
        }
        if (impl_requests[*indx] == MPI_REQUEST_NULL) {
            //remove_cookie_pair_from_list(CONVERT_MPI_Request(array_of_requests[*indx]));
        }
        array_of_requests[*indx] = OUTPUT_MPI_Request(impl_requests[*indx]);
    }

    free(impl_requests);

    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Waitsome(int incount, WRAP_Request array_of_requests[], int *outcount, int array_of_indices[], WRAP_Status *array_of_statuses)
{
    const bool ignore = IS_STATUSES_IGNORE(array_of_statuses);

    MPI_Request * impl_requests = calloc(incount,sizeof(MPI_Request));
    if (impl_requests == NULL) return MPI_ERR_INTERN;
    for (int i=0; i<incount; i++) {
        impl_requests[i] = CONVERT_MPI_Request(array_of_requests[i]);
    }

    MPI_Status * impl_statuses = NULL;
    if (!ignore) {
        impl_statuses = calloc(incount, sizeof(MPI_Status));
        if (impl_statuses == NULL) return MPI_ERR_INTERN;
    }

    int rc = IMPL_Waitsome(incount, impl_requests, outcount, array_of_indices, ignore ? MPI_STATUSES_IGNORE : impl_statuses);

    if ((*outcount > 0) && (*outcount != MPI_UNDEFINED)) {
        for (int i=0; i<*outcount; i++) {
            const int j = array_of_indices[i];
            if (!ignore) {
                MPI_Status_to_WRAP_Status(&impl_statuses[j], &array_of_statuses[j]);
            }
            if (impl_requests[j] == MPI_REQUEST_NULL) {
                //remove_cookie_pair_from_list(CONVERT_MPI_Request(array_of_requests[j]));
            }
            array_of_requests[j] = OUTPUT_MPI_Request(impl_requests[j]);
        }
    }

    free(impl_requests);
    if (!ignore) free(impl_statuses);

    return RETURN_CODE_IMPL_TO_MUK(rc);
}

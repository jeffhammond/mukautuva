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

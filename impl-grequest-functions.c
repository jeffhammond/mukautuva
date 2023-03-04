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
//#include "impl-constant-conversions.h"
#include "impl-handle-conversions.h"
//#include "impl-keyval-map.h"
#include "impl-status.h"

typedef struct
{
    void * user_state;
    WRAP_Grequest_query_function  * query_fn;
    WRAP_Grequest_free_function   * free_fn;
    WRAP_Grequest_cancel_function * cancel_fn;
}
grequest_wrapped_state;

int query_trampoline(void * extra_state, MPI_Status * impl_status)
{
    grequest_wrapped_state * wrapped_state = (grequest_wrapped_state*)extra_state;
    void * user_state = wrapped_state->user_state;
    WRAP_Grequest_query_function* query_fn = wrapped_state->query_fn;
    WRAP_Status wrap_status;
    MPI_Status_to_WRAP_Status(impl_status, &wrap_status);
    int rc = (*query_fn)(user_state, &wrap_status);
    WRAP_Status_to_MPI_Status(&wrap_status, impl_status);
    return RETURN_CODE_MUK_TO_IMPL(rc);
}

int free_trampoline(void *extra_state)
{
    grequest_wrapped_state * wrapped_state = (grequest_wrapped_state*)extra_state;
    void * user_state = wrapped_state->user_state;
    WRAP_Grequest_free_function* free_fn = wrapped_state->free_fn;
    int rc = (*free_fn)(user_state);
    return RETURN_CODE_MUK_TO_IMPL(rc);
}

int cancel_trampoline(void *extra_state, int complete)
{
    grequest_wrapped_state * wrapped_state = (grequest_wrapped_state*)extra_state;
    void * user_state = wrapped_state->user_state;
    WRAP_Grequest_cancel_function* cancel_fn = wrapped_state->cancel_fn;
    int rc = (*cancel_fn)(user_state, complete);
    return RETURN_CODE_MUK_TO_IMPL(rc);
}


// WRAP->IMPL functions

int WRAP_Grequest_complete(WRAP_Request request)
{
    MPI_Request impl_request = CONVERT_MPI_Request(request);
    int rc = IMPL_Grequest_complete(impl_request);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Grequest_start(WRAP_Grequest_query_function *query_fn, WRAP_Grequest_free_function *free_fn, WRAP_Grequest_cancel_function *cancel_fn, void *user_state, WRAP_Request *request)
{
    int rc;
    MPI_Request impl_request = CONVERT_MPI_Request(*request);

    grequest_wrapped_state * wrapped_state = calloc(1,sizeof(grequest_wrapped_state));
    if (wrapped_state == NULL) {
        rc = MPI_ERR_INTERN;
        goto end;
    }

    wrapped_state->user_state  = user_state;
    wrapped_state->query_fn    = query_fn;
    wrapped_state->free_fn     = free_fn;
    wrapped_state->cancel_fn   = cancel_fn;

    MPI_Grequest_query_function  * impl_query_fn  = query_trampoline;
    MPI_Grequest_free_function   * impl_free_fn   = free_trampoline;
    MPI_Grequest_cancel_function * impl_cancel_fn = cancel_trampoline;

    rc = IMPL_Grequest_start(impl_query_fn, impl_free_fn, impl_cancel_fn, wrapped_state, &impl_request);
    *request = OUTPUT_MPI_Request(impl_request);
    end:
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

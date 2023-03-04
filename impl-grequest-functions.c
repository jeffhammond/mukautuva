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
#include "impl-constant-conversions.h"
#include "impl-handle-conversions.h"
#include "impl-keyval-map.h"

// WRAP->IMPL functions

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

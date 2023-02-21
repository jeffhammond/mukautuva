#include <stdio.h>

#include <mpi.h>

#define MUK_EXTERN extern
#include "impl-fpointers.h"

int TYPE_HANDLE_KEY = MPI_KEYVAL_INVALID;

void WRAP_Init_handle_key(void)
{
    int rc = IMPL_Type_create_keyval(MPI_TYPE_NULL_COPY_FN, MPI_TYPE_NULL_DELETE_FN, &TYPE_HANDLE_KEY, NULL);
    if (rc != MPI_SUCCESS) {
        printf("IMPL_Type_create_keyval(TYPE_HANDLE_KEY) failed: %d\n", rc);
    }
}

void WRAP_Finalize_handle_key(void)
{
    int rc = MPI_SUCCESS;
    if (TYPE_HANDLE_KEY != MPI_KEYVAL_INVALID) {
        rc = IMPL_Type_free_keyval(&TYPE_HANDLE_KEY);
    }
    if (rc != MPI_SUCCESS) {
        printf("IMPL_Type_free_keyval(TYPE_HANDLE_KEY) failed: %d\n", rc);
    }
}


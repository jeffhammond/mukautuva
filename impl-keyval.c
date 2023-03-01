#include <stdio.h>

#include <mpi.h>

#define MUK_EXTERN extern
#include "impl-fpointers.h"

// for user-defined reductions
int TYPE_HANDLE_KEY = MPI_KEYVAL_INVALID;

// for errhandlers
int TYPE_EH_HANDLE_KEY = MPI_KEYVAL_INVALID;
int COMM_EH_HANDLE_KEY = MPI_KEYVAL_INVALID;
int WIN_EH_HANDLE_KEY  = MPI_KEYVAL_INVALID;

void WRAP_Init_handle_key(void)
{
    int rc;
    rc = IMPL_Type_create_keyval(MPI_TYPE_NULL_COPY_FN, MPI_TYPE_NULL_DELETE_FN, &TYPE_HANDLE_KEY, NULL);
    if (rc != MPI_SUCCESS) {
        printf("IMPL_Type_create_keyval(TYPE_HANDLE_KEY) failed: %d\n", rc);
    }
    rc = IMPL_Type_create_keyval(MPI_TYPE_NULL_COPY_FN, MPI_TYPE_NULL_DELETE_FN, &TYPE_EH_HANDLE_KEY, NULL);
    if (rc != MPI_SUCCESS) {
        printf("IMPL_Type_create_keyval(TYPE_EH_HANDLE_KEY) failed: %d\n", rc);
    }
    rc = IMPL_Comm_create_keyval(MPI_COMM_NULL_COPY_FN, MPI_COMM_NULL_DELETE_FN, &COMM_EH_HANDLE_KEY, NULL);
    if (rc != MPI_SUCCESS) {
        printf("IMPL_Comm_create_keyval(COMM_EH_HANDLE_KEY) failed: %d\n", rc);
    }
    rc = IMPL_Win_create_keyval(MPI_WIN_NULL_COPY_FN, MPI_WIN_NULL_DELETE_FN, &WIN_EH_HANDLE_KEY, NULL);
    if (rc != MPI_SUCCESS) {
        printf("IMPL_Win_create_keyval(WIN_EH_HANDLE_KEY) failed: %d\n", rc);
    }
}

void WRAP_Finalize_handle_key(void)
{
    int rc = MPI_SUCCESS;
    if (TYPE_HANDLE_KEY != MPI_KEYVAL_INVALID) {
        rc = IMPL_Type_free_keyval(&TYPE_HANDLE_KEY);
        if (rc != MPI_SUCCESS) {
            printf("IMPL_Type_free_keyval(TYPE_HANDLE_KEY) failed: %d\n", rc);
        }
    }
    if (TYPE_EH_HANDLE_KEY != MPI_KEYVAL_INVALID) {
        rc = IMPL_Type_free_keyval(&TYPE_EH_HANDLE_KEY);
        if (rc != MPI_SUCCESS) {
            printf("IMPL_Type_free_keyval(TYPE_EH_HANDLE_KEY) failed: %d\n", rc);
        }
    }
    if (COMM_EH_HANDLE_KEY != MPI_KEYVAL_INVALID) {
        rc = IMPL_Comm_free_keyval(&COMM_EH_HANDLE_KEY);
        if (rc != MPI_SUCCESS) {
            printf("IMPL_Comm_free_keyval(COMM_EH_HANDLE_KEY) failed: %d\n", rc);
        }
    }
    if (WIN_EH_HANDLE_KEY != MPI_KEYVAL_INVALID) {
        rc = IMPL_Win_free_keyval(&WIN_EH_HANDLE_KEY);
        if (rc != MPI_SUCCESS) {
            printf("IMPL_Win_free_keyval(WIN_EH_HANDLE_KEY) failed: %d\n", rc);
        }
    }
}

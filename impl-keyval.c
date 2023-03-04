#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <mpi.h>

#define MUK_EXTERN extern
#include "impl-fpointers.h"

// for user-defined reductions
int TYPE_ATTR_FOR_USER_OP_FN = MPI_KEYVAL_INVALID;
int COMM_EH_HANDLE_KEY = MPI_KEYVAL_INVALID;
int WIN_EH_HANDLE_KEY = MPI_KEYVAL_INVALID;

void WRAP_Init_handle_key(void)
{
    int rc;
    rc = IMPL_Type_create_keyval(MPI_TYPE_NULL_COPY_FN, MPI_TYPE_NULL_DELETE_FN, &TYPE_ATTR_FOR_USER_OP_FN, NULL);
    if (rc != MPI_SUCCESS) {
        printf("IMPL_Type_create_keyval(TYPE_ATTR_FOR_USER_OP_FN) failed: %d\n", rc);
    }
    // use the DUP copy function so that the attribute containing the errh callback fptr is copied
    // to the new communicator.  we need to remember to delete the cookie when the comm/win objects are freed.
    //rc = IMPL_Comm_create_keyval(MPI_COMM_DUP_FN, comm_delete_cookie, &COMM_EH_HANDLE_KEY, NULL);
    rc = IMPL_Comm_create_keyval(MPI_COMM_DUP_FN, MPI_COMM_NULL_DELETE_FN, &COMM_EH_HANDLE_KEY, NULL);
    if (rc != MPI_SUCCESS) {
        printf("IMPL_Comm_create_keyval(COMM_EH_HANDLE_KEY) failed: %d\n", rc);
    }
    //printf("%s: COMM_EH_HANDLE_KEY=%x\n", __func__, COMM_EH_HANDLE_KEY);
    //rc = IMPL_Win_create_keyval(MPI_WIN_DUP_FN, win_delete_cookie, &WIN_EH_HANDLE_KEY, NULL);
    rc = IMPL_Win_create_keyval(MPI_WIN_DUP_FN, MPI_WIN_NULL_DELETE_FN, &WIN_EH_HANDLE_KEY, NULL);
    if (rc != MPI_SUCCESS) {
        printf("IMPL_Win_create_keyval(WIN_EH_HANDLE_KEY) failed: %d\n", rc);
    }
    //printf("%s: WIN_EH_HANDLE_KEY=%x\n", __func__, WIN_EH_HANDLE_KEY);
}

void WRAP_Finalize_handle_key(void)
{
    int rc = MPI_SUCCESS;
    if (TYPE_ATTR_FOR_USER_OP_FN != MPI_KEYVAL_INVALID) {
        rc = IMPL_Type_free_keyval(&TYPE_ATTR_FOR_USER_OP_FN);
        if (rc != MPI_SUCCESS) {
            printf("IMPL_Type_free_keyval(TYPE_ATTR_FOR_USER_OP_FN) failed: %d\n", rc);
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

#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

#define MUK_EXTERN extern
#include "impl-fpointers.h"

// for user-defined reductions
int TYPE_HANDLE_KEY = MPI_KEYVAL_INVALID;
int COMM_EH_HANDLE_KEY = MPI_KEYVAL_INVALID;
int WIN_EH_HANDLE_KEY = MPI_KEYVAL_INVALID;

int comm_delete_cookie(MPI_Comm comm, int comm_keyval, void *attribute_val, void *extra_state)
{
    if (comm_keyval == COMM_EH_HANDLE_KEY) {
        if (attribute_val == NULL) {
            printf("%s: attribute_val=%p comm=%lx comm_keyval=%d\n",
                   __func__, attribute_val, (intptr_t)comm, comm_keyval);
        }
        else {
            free(attribute_val);
        }
    } else {
        printf("%s: I have no idea how this happened. comm=%lx comm_keyval=%d COMM_EH_HANDLE_KEY=%d\n",
               __func__, (intptr_t)comm, comm_keyval, COMM_EH_HANDLE_KEY);
    }
    (void)extra_state;
    return MPI_SUCCESS;
}

int win_delete_cookie(MPI_Win win, int win_keyval, void *attribute_val, void *extra_state)
{
    if (win_keyval == WIN_EH_HANDLE_KEY) {
        if (attribute_val == NULL) {
            printf("%s: attribute_val=%p win=%lx win_keyval=%d\n",
                   __func__, attribute_val, (intptr_t)win, win_keyval);
        }
        else {
            free(attribute_val);
        }
    } else {
        printf("%s: I have no idea how this happened. win=%lx win_keyval=%d WIN_EH_HANDLE_KEY=%d\n",
               __func__, (intptr_t)win, win_keyval, WIN_EH_HANDLE_KEY);
    }
    (void)extra_state;
    return MPI_SUCCESS;
}

void WRAP_Init_handle_key(void)
{
    int rc;
    rc = IMPL_Type_create_keyval(MPI_TYPE_NULL_COPY_FN, MPI_TYPE_NULL_DELETE_FN, &TYPE_HANDLE_KEY, NULL);
    if (rc != MPI_SUCCESS) {
        printf("IMPL_Type_create_keyval(TYPE_HANDLE_KEY) failed: %d\n", rc);
    }
    // use the DUP copy function so that the attribute containing the errh callback fptr is copied
    // to the new communicator.  we need to remember to delete the cookie when the comm/win objects are freed.
    rc = IMPL_Comm_create_keyval(MPI_COMM_DUP_FN, comm_delete_cookie, &COMM_EH_HANDLE_KEY, NULL);
    if (rc != MPI_SUCCESS) {
        printf("IMPL_Comm_create_keyval(COMM_EH_HANDLE_KEY) failed: %d\n", rc);
    }
    rc = IMPL_Win_create_keyval(MPI_WIN_DUP_FN, win_delete_cookie, &WIN_EH_HANDLE_KEY, NULL);
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

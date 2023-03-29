// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef NOWRAP
#include <mpi.h>
#else
#include "mpi.h"
#endif

void callback(MPI_Comm * comm, int *err, ...)
{
    (void)comm;
    (void)err;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    MPI_Errhandler errh;
    MPI_Comm_create_errhandler(callback, &errh);

    MPI_Comm_set_errhandler(MPI_COMM_WORLD, errh);

    MPI_Comm_call_errhandler(MPI_COMM_WORLD,99);

    MPI_Comm dup;
    MPI_Comm_dup(MPI_COMM_WORLD,&dup);

    MPI_Errhandler temp0;
    MPI_Comm_get_errhandler(MPI_COMM_WORLD,&temp0);

    MPI_Errhandler temp1;
    MPI_Comm_get_errhandler(dup,&temp1);

    MPI_Comm_free(&dup);

    MPI_Errhandler_free(&temp0);

    MPI_Errhandler_free(&temp1);

    MPI_Errhandler_free(&errh);

#if 0
    MPI_Errhandler_free(&errh);
#endif
    MPI_Finalize();
    return 0;
}

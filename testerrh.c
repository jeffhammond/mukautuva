#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef NOWRAP
#include <mpi.h>
#else
#include "mpi.h"
#endif

void callback(MPI_Comm * comm, int *err)
{
#if 0
    printf("HI\n");
    fflush(0);
    printf("callback *comm=%lx *err=%d\n",(intptr_t)*comm,*err);
    fflush(0);
    printf("BYE\n");
    fflush(0);
    return;
#endif
    (void)comm;
    (void)err;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    MPI_Errhandler errh;
    MPI_Comm_create_errhandler(callback, &errh);
    printf("C errh=%lx\n",(intptr_t)errh);

    MPI_Comm_set_errhandler(MPI_COMM_WORLD, errh);
    printf("S errh=%lx\n",(intptr_t)errh);

    MPI_Comm_call_errhandler(MPI_COMM_WORLD,99);

    MPI_Comm dup;
    MPI_Comm_dup(MPI_COMM_WORLD,&dup);

    MPI_Errhandler temp0;
    MPI_Comm_get_errhandler(MPI_COMM_WORLD,&temp0);
    printf("G temp0=%lx\n",(intptr_t)temp0);

    MPI_Errhandler temp1;
    MPI_Comm_get_errhandler(dup,&temp1);
    printf("G temp1=%lx\n",(intptr_t)temp1);

    MPI_Comm_free(&dup);

    MPI_Errhandler_free(&temp0);
    printf("F temp0=%lx\n",(intptr_t)temp0);

    MPI_Errhandler_free(&temp1);
    printf("F temp1=%lx\n",(intptr_t)temp1);

    MPI_Errhandler_free(&errh);
    printf("F errh=%lx\n",(intptr_t)errh);

#if 0
    MPI_Errhandler_free(&errh);
    printf("F errh=%lx\n",(intptr_t)errh);
#endif
    MPI_Finalize();
    return 0;
}

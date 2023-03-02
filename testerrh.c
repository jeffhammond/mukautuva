#include <stdio.h>
#include <stdlib.h>

#ifdef NOWRAP
#include <mpi.h>
#else
#include "mpi.h"
#endif

void callback(MPI_Comm * comm, int *err, ...)
{
    printf("callback\n");
    return;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    MPI_Errhandler errh;
    MPI_Comm_create_errhandler(callback, &errh);
    printf("C errh=%x\n",errh);

    MPI_Comm_set_errhandler(MPI_COMM_WORLD, errh);
    printf("S errh=%x\n",errh);

    MPI_Comm dup;
    MPI_Comm_dup(MPI_COMM_WORLD,&dup);

    MPI_Errhandler temp0;
    MPI_Comm_get_errhandler(MPI_COMM_WORLD,&temp0);
    printf("G temp0=%x\n",temp0);

    MPI_Errhandler temp1;
    MPI_Comm_get_errhandler(dup,&temp1);
    printf("G temp1=%x\n",temp1);

    MPI_Comm_free(&dup);

    MPI_Errhandler_free(&temp0);
    printf("F temp0=%x\n",temp0);

    MPI_Errhandler_free(&temp1);
    printf("F temp1=%x\n",temp1);

    MPI_Errhandler_free(&errh);
    printf("F errh=%x\n",errh);

    MPI_Errhandler_free(&errh);
    printf("F errh=%x\n",errh);

    MPI_Finalize();
    return 0;
}

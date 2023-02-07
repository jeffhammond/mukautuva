#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#ifdef NOWRAP
#include <mpi.h>
#else
#include "mpi.h"
#endif

int main(int argc, char* argv[])
{
    int rc;
    rc = MPI_Init(&argc,&argv);

    int flag;
    rc = MPI_Initialized(&flag);
    printf("is init? %d\n", flag);
    rc = MPI_Finalized(&flag);
    printf("is final? %d\n", flag);
    rc = MPI_Is_thread_main(&flag);
    printf("is thread main? %d\n", flag);

    printf("all done\n");

    rc = MPI_Finalize();

    return rc;
}

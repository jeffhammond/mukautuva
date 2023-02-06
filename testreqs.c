#include <stdio.h>
#include <stdint.h>
#ifdef NOWRAP
#include <mpi.h>
#else
#include "mpi.h"
#endif

int main(int argc, char* argv[])
{
    int rc;
    rc = MPI_Init(&argc,&argv);

    int me, np;
    MPI_Comm_rank(MPI_COMM_WORLD,&me);
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    printf("i am %d of %d\n", me, np);

    {
        MPI_Request r;
        MPI_Ibarrier(MPI_COMM_WORLD,&r);
        MPI_Wait(&r,MPI_STATUS_IGNORE);

        MPI_Ibarrier(MPI_COMM_WORLD,&r);
        MPI_Waitall(1,&r,MPI_STATUS_IGNORE);

        // this does not set index properly
        int index = 1<<30;
        MPI_Ibarrier(MPI_COMM_WORLD,&r);
        MPI_Waitany(1,&r,&index,MPI_STATUS_IGNORE);
        printf("index=%d\n", index);

        int flag = 0;
        MPI_Ibarrier(MPI_COMM_WORLD,&r);
        while (!flag) {
            MPI_Test(&r,&flag,MPI_STATUS_IGNORE);
        }
    }

    if (me==0) printf("all done\n");

    rc = MPI_Finalize();

    return rc;
}

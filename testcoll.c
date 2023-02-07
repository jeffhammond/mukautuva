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

#define N 10

int main(int argc, char* argv[])
{
    int rc;
    rc = MPI_Init(&argc,&argv);

    int me, np;
    MPI_Comm_rank(MPI_COMM_WORLD,&me);
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    printf("I am %d of %d\n", me, np);

    {
        int x[N];
        int y[N];
        for (size_t i=0; i<N; i++) {
            x[i] = i;
            y[i] = -1;
        }
        MPI_Allreduce(x,y,N,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
        printf("y=");
        for (size_t i=0; i<N; i++) {
            printf("%d,",y[i]);
        }
        printf("\n");
    }
    fflush(0);
    MPI_Barrier(MPI_COMM_WORLD);

    {
        int x[N] = { 10 };
        for (size_t i=0; i<N; i++) {
            x[i] = i;
        }
        MPI_Allreduce(MPI_IN_PLACE,x,N,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
        printf("x=");
        for (size_t i=0; i<N; i++) {
            printf("%d,",x[i]);
        }
        printf("\n");
    }

    fflush(0);
    usleep(1);
    MPI_Barrier(MPI_COMM_WORLD);
    if (me==0) printf("all done\n");

    rc = MPI_Finalize();

    return rc;
}

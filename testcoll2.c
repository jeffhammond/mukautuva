// SPDX-License-Identifier: MIT

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

    int n = (argc > 1) ? atoi(argv[1]) : 1000;

    int me, np;
    MPI_Comm_rank(MPI_COMM_WORLD,&me);
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    //printf("I am %d of %d\n", me, np);
    if (me==0) printf("nonblocking collectives: %d iterations\n", n);

    {
        if (me==0) printf("MPI_Ibcast\n");

        MPI_Request * r = calloc(n,sizeof(MPI_Request));
        int * x = calloc(n,sizeof(int));
        for (int i=0; i<n; i++) {
            x[i] =  np - me;
        }

        for (int i=0; i<n; i++)
        {
            MPI_Ibcast(&x[i], 1, MPI_INT, 0, MPI_COMM_WORLD, &r[i]);
        }

        MPI_Barrier(MPI_COMM_WORLD);

        for (int i=0; i<n; i++)
        {
            MPI_Wait(&r[i],MPI_STATUS_IGNORE);
            // verify that waiting on MPI_REQUEST_NULL is okay
            MPI_Wait(&r[i],MPI_STATUS_IGNORE);
        }

        int errors = 0;
        for (int i=0; i<n; i++) {
            errors += (x[i] !=  np);
        }
        if (errors) {
            printf("errors: %d\n", errors);
            fflush(0);
            for (int i=0; i<n; i++) {
                printf("x[%d] = %d\n",i,x[i]);
            }
            fflush(0);
            usleep(1);
            MPI_Abort(MPI_COMM_WORLD,errors);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    fflush(0);
    usleep(1);
    MPI_Barrier(MPI_COMM_WORLD);
    if (me==0) printf("all done\n");

    rc = MPI_Finalize();

    return rc;
}

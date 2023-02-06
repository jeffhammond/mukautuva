#include <stdio.h>
#include <stdint.h>
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

    int me, np;
    MPI_Comm_rank(MPI_COMM_WORLD,&me);
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    printf("i am %d of %d\n", me, np);
    fflush(0);
    MPI_Barrier(MPI_COMM_WORLD);
    usleep(1);

    if (0)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Ibarrier\n");
        fflush(0);

        MPI_Request r;
        MPI_Ibarrier(MPI_COMM_WORLD,&r);
        MPI_Wait(&r,MPI_STATUS_IGNORE);

        MPI_Ibarrier(MPI_COMM_WORLD,&r);
        MPI_Waitall(1,&r,MPI_STATUS_IGNORE);
    }

    if (0)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Isend+Irecv+Waitall\n");
        fflush(0);

        int buffer[2] = { me };
        MPI_Request r[2];
        MPI_Isend(&buffer[0], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[0]);
        MPI_Irecv(&buffer[1], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[1]);
        MPI_Waitall(2,r,MPI_STATUS_IGNORE);
    }

    if (0)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Isend+Recv(s)+Waitall\n");
        fflush(0);

        int buffer[2] = { me };
        MPI_Request r = MPI_REQUEST_NULL;
        MPI_Status s;
        memset(&s,255,sizeof(MPI_Status));
        MPI_Isend(&buffer[0], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r);
        MPI_Recv(&buffer[1], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &s);
        MPI_Wait(&r,MPI_STATUS_IGNORE);

        int rcount = -1;
        MPI_Get_count(&s, MPI_INT, &rcount);
        printf("[%d]: SOURCE=%d TAG=%d ERROR=%d count=%d\n",
                me, s.MPI_SOURCE, s.MPI_TAG, s.MPI_ERROR, rcount);
    }

    if (0)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Isend+Irecv+Wait+Wait(s)\n");
        fflush(0);

        int buffer[2] = { me };
        MPI_Request r[2] = { MPI_REQUEST_NULL };
        MPI_Status s;
        memset(&s,255,sizeof(MPI_Status));
        MPI_Isend(&buffer[0], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[0]);
        MPI_Irecv(&buffer[1], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[1]);
        MPI_Wait(&r[1],&s);
        MPI_Wait(&r[0],MPI_STATUS_IGNORE);

        // Error codes belonging to the error class MPI_ERR_IN_STATUS should be returned
        // only by the MPI completion functions that take arrays of MPI_Status. For the
        // functions that take a single MPI_Status argument, the error code is returned
        // by the function, and the value of the MPI_ERROR field in the MPI_Status argument
        // is undefined (see 3.2.5).
        int rcount = -1;
        MPI_Get_count(&s, MPI_INT, &rcount);
        printf("[%d]: SOURCE=%d TAG=%d count=%d\n",
                me, s.MPI_SOURCE, s.MPI_TAG, rcount);
    }

    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Isend+Irecv+Waitall(s)\n");
        fflush(0);

        int buffer[2] = { me };
        MPI_Request r[2] = { MPI_REQUEST_NULL };
        MPI_Status s[2];
        memset(&s,255,2*sizeof(MPI_Status));
        MPI_Isend(&buffer[0], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[0]);
        MPI_Irecv(&buffer[1], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[1]);
        MPI_Waitall(2,r,s);

        // Error codes belonging to the error class MPI_ERR_IN_STATUS should be returned
        // only by the MPI completion functions that take arrays of MPI_Status. For the
        // functions that take a single MPI_Status argument, the error code is returned
        // by the function, and the value of the MPI_ERROR field in the MPI_Status argument
        // is undefined (see 3.2.5).
        int rcount = -3;
        MPI_Get_count(&s[1], MPI_INT, &rcount);
        printf("[%d]: SOURCE=%d TAG=%d ERROR=%d count=%d\n",
                me, s[1].MPI_SOURCE, s[1].MPI_TAG, s[1].MPI_ERROR, rcount);
    }

    {
#if 0
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
#endif
    }

    fflush(0);
    usleep(1);
    MPI_Barrier(MPI_COMM_WORLD);
    if (me==0) printf("all done\n");

    rc = MPI_Finalize();

    return rc;
}

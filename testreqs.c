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

    int me, np;
    MPI_Comm_rank(MPI_COMM_WORLD,&me);
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    printf("I am %d of %d\n", me, np);
    fflush(0);
    MPI_Barrier(MPI_COMM_WORLD);
    usleep(1);

    if (1)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Ibarrier+...\n");
        fflush(0);

        MPI_Request r;
        int flag;

        MPI_Ibarrier(MPI_COMM_WORLD,&r);
        MPI_Wait(&r,MPI_STATUS_IGNORE);
        if (r != MPI_REQUEST_NULL) {
            printf("freed request is not null\n");
            printf("%d: request=0x%lx MPI_REQUEST_NULL=0x%lx\n", me, (intptr_t)r, (intptr_t)MPI_REQUEST_NULL);
            MPI_Abort(MPI_COMM_WORLD,1);
        }

        MPI_Ibarrier(MPI_COMM_WORLD,&r);
        MPI_Waitall(1,&r,MPI_STATUSES_IGNORE);
        if (r != MPI_REQUEST_NULL) {
            printf("freed request is not null\n");
            printf("%d: request=0x%lx MPI_REQUEST_NULL=0x%lx\n", me, (intptr_t)r, (intptr_t)MPI_REQUEST_NULL);
            MPI_Abort(MPI_COMM_WORLD,1);
        }

        MPI_Ibarrier(MPI_COMM_WORLD,&r);
        flag = 0;
        while (!flag) {
            MPI_Test(&r,&flag,MPI_STATUS_IGNORE);
        }
        if (r != MPI_REQUEST_NULL) {
            printf("freed request is not null\n");
            printf("%d: request=0x%lx MPI_REQUEST_NULL=0x%lx\n", me, (intptr_t)r, (intptr_t)MPI_REQUEST_NULL);
            MPI_Abort(MPI_COMM_WORLD,1);
        }

        MPI_Ibarrier(MPI_COMM_WORLD,&r);
        flag = 0;
        while (!flag) {
            MPI_Testall(1,&r,&flag,MPI_STATUSES_IGNORE);
        }
        if (r != MPI_REQUEST_NULL) {
            printf("freed request is not null\n");
            printf("%d: request=0x%lx MPI_REQUEST_NULL=0x%lx\n", me, (intptr_t)r, (intptr_t)MPI_REQUEST_NULL);
            MPI_Abort(MPI_COMM_WORLD,1);
        }
    }

    if (1)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Isend+Irecv+Waitall\n");
        fflush(0);

        int buffer[2] = { me };
        MPI_Request r[2];
        MPI_Isend(&buffer[0], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[0]);
        MPI_Irecv(&buffer[1], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[1]);
        MPI_Waitall(2,r,MPI_STATUSES_IGNORE);
    }

    if (1)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Isend+Recv(s)+Wait\n");
        fflush(0);

        int buffer[2] = { me };
        MPI_Request r = MPI_REQUEST_NULL;
        MPI_Status s;
        memset(&s,255,sizeof(MPI_Status));
        MPI_Isend(&buffer[0], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r);
        MPI_Recv(&buffer[1], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &s);
        MPI_Wait(&r,MPI_STATUS_IGNORE);

        int rcount = -3;
        MPI_Get_count(&s, MPI_INT, &rcount);
        if ((s.MPI_SOURCE != me) || (s.MPI_TAG != 99) || (rcount != 1)) {
            printf("[%d]: SOURCE=%d TAG=%d count=%d\n",
                    me, s.MPI_SOURCE, s.MPI_TAG, rcount);
            MPI_Abort(MPI_COMM_WORLD,1);
        }
    }

    if (1)
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

        int rcount = -3;
        MPI_Get_count(&s, MPI_INT, &rcount);
        if ((s.MPI_SOURCE != me) || (s.MPI_TAG != 99) || (rcount != 1)) {
            printf("[%d]: SOURCE=%d TAG=%d count=%d\n",
                    me, s.MPI_SOURCE, s.MPI_TAG, rcount);
            MPI_Abort(MPI_COMM_WORLD,1);
        }
    }

    if (1)
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

        int rcount = -3;
        MPI_Get_count(&s[1], MPI_INT, &rcount);
        if ((s[1].MPI_SOURCE != me) || (s[1].MPI_TAG != 99) || (rcount != 1)) {
            printf("[%d]: SOURCE=%d TAG=%d count=%d\n",
                    me, s[1].MPI_SOURCE, s[1].MPI_TAG, rcount);
            MPI_Abort(MPI_COMM_WORLD,1);
        }
    }

    if (1)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Isend+Irecv+Testall(s)\n");
        fflush(0);

        int buffer[2] = { me };
        MPI_Request r[2] = { MPI_REQUEST_NULL };
        MPI_Status s[2];
        memset(&s,255,2*sizeof(MPI_Status));
        MPI_Isend(&buffer[0], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[0]);
        MPI_Irecv(&buffer[1], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[1]);

        int flag = 0;
        while (!flag) {
            MPI_Testall(2,r,&flag,s);
        }

        int rcount = -3;
        MPI_Get_count(&s[1], MPI_INT, &rcount);
        if ((s[1].MPI_SOURCE != me) || (s[1].MPI_TAG != 99) || (rcount != 1)) {
            printf("[%d]: SOURCE=%d TAG=%d count=%d\n",
                    me, s[1].MPI_SOURCE, s[1].MPI_TAG, rcount);
            MPI_Abort(MPI_COMM_WORLD,1);
        }
    }

    if (1)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Isend+Irecv+Waitall\n");
        fflush(0);

        // MPICH fails around 131072 (https://github.com/pmodels/mpich/issues/6389)
        const int n = 100000;

        int * buffer = calloc(2*n,sizeof(int));
        for (int i=0; i<n; i++) {
            buffer[i]   =  i;    // send
            buffer[n+i] = -1000; // recv 
        }    
        MPI_Request * r = calloc(2*n,sizeof(MPI_Request));

        for (int i=0; i<n; i++) {
            MPI_Isend(&buffer[i], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[i]);
            MPI_Irecv(&buffer[n+i], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[n+i]);
        }
        MPI_Waitall(2*n,r,MPI_STATUSES_IGNORE);

        free(buffer);
        free(r);
    }

    if (1)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Isend+Irecv+Testall\n");
        fflush(0);

        // MPICH fails around 131072 (https://github.com/pmodels/mpich/issues/6389)
        const int n = 100000;

        int * buffer = calloc(2*n,sizeof(int));
        for (int i=0; i<n; i++) {
            buffer[i]   =  i;    // send
            buffer[n+i] = -1000; // recv 
        }    
        MPI_Request * r = calloc(2*n,sizeof(MPI_Request));

        for (int i=0; i<n; i++) {
            MPI_Isend(&buffer[i], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[i]);
            MPI_Irecv(&buffer[n+i], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[n+i]);
        }
        int flag = 0;
        while (!flag) {
            MPI_Testall(2*n,r,&flag,MPI_STATUSES_IGNORE);
        }

        free(buffer);
        free(r);
    }

    if (1)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Isend+Irecv+Waitany\n");
        fflush(0);

        const int n = 1000;

        int * buffer = calloc(2*n,sizeof(int));
        for (int i=0; i<n; i++) {
            buffer[i]   =  i;    // send
            buffer[n+i] = -1000; // recv 
        }    
        MPI_Request * r = calloc(2*n,sizeof(MPI_Request));

        for (int i=0; i<n; i++) {
            MPI_Isend(&buffer[i], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[i]);
            MPI_Irecv(&buffer[n+i], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[n+i]);
        }

        int indx=-3, done=0;
        while (done < 2*n) {
            MPI_Waitany(2*n,r,&indx,MPI_STATUSES_IGNORE);
            done++;
        }

        free(buffer);
        free(r);
    }

    if (1)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Isend+Irecv+Testany\n");
        fflush(0);

        const int n = 1000;

        int * buffer = calloc(2*n,sizeof(int));
        for (int i=0; i<n; i++) {
            buffer[i]   =  i;    // send
            buffer[n+i] = -1000; // recv 
        }    
        MPI_Request * r = calloc(2*n,sizeof(MPI_Request));

        for (int i=0; i<n; i++) {
            MPI_Isend(&buffer[i], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[i]);
            MPI_Irecv(&buffer[n+i], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[n+i]);
        }

        int flag=0, indx=-3, done=0;
        while (done < 2*n) {
            MPI_Testany(2*n,r,&indx,&flag,MPI_STATUSES_IGNORE);
            if (flag) done++;
        }

        free(buffer);
        free(r);
    }

    if (1)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Isend+Irecv+Waitsome\n");
        fflush(0);

        const int n = 1000;

        int * buffer = calloc(2*n,sizeof(int));
        for (int i=0; i<n; i++) {
            buffer[i]   =  i;    // send
            buffer[n+i] = -1000; // recv 
        }    
        MPI_Request * r = calloc(2*n,sizeof(MPI_Request));

        for (int i=0; i<n; i++) {
            MPI_Isend(&buffer[i], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[i]);
            MPI_Irecv(&buffer[n+i], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[n+i]);
        }

        int done=0, outcount=0;
        int * indx = calloc(2*n,sizeof(int));
        while (done < 2*n) {
            MPI_Waitsome(2*n,r,&outcount,indx,MPI_STATUSES_IGNORE);
            done += outcount;
        }

        free(indx);
        free(buffer);
        free(r);
    }

    if (1)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        fflush(0);
        if (me==0) printf("Isend+Irecv+Testsome\n");
        fflush(0);

        const int n = 1000;

        int * buffer = calloc(2*n,sizeof(int));
        for (int i=0; i<n; i++) {
            buffer[i]   =  i;    // send
            buffer[n+i] = -1000; // recv 
        }    
        MPI_Request * r = calloc(2*n,sizeof(MPI_Request));

        for (int i=0; i<n; i++) {
            MPI_Isend(&buffer[i], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[i]);
            MPI_Irecv(&buffer[n+i], 1, MPI_INT, me, 99, MPI_COMM_WORLD, &r[n+i]);
        }

        int done=0, outcount=0;
        int * indx = calloc(2*n,sizeof(int));
        while (done < 2*n) {
            MPI_Testsome(2*n,r,&outcount,indx,MPI_STATUSES_IGNORE);
            done += outcount;
        }

        free(indx);
        free(buffer);
        free(r);
    }

    fflush(0);
    usleep(1);
    MPI_Barrier(MPI_COMM_WORLD);
    if (me==0) printf("all done\n");

    rc = MPI_Finalize();

    return rc;
}

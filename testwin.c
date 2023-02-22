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

    MPI_Win a, as, c, cd;
    void *ba, *bas;
    char bc[1024], b[1024];

    MPI_Win_allocate(1024,1,MPI_INFO_NULL,MPI_COMM_WORLD,&ba,&a);
    MPI_Win_fence(0,a);
    MPI_Win_free(&a);
    if (a != MPI_WIN_NULL) {
        printf("win null? %d\n",a==MPI_WIN_NULL);
        MPI_Abort(MPI_COMM_WORLD,1);
    }

    MPI_Win_allocate_shared(1024,1,MPI_INFO_NULL,MPI_COMM_WORLD,&bas,&as);
    MPI_Win_fence(0,as);
    MPI_Win_free(&as);
    if (as != MPI_WIN_NULL) {
        printf("win null? %d\n",as==MPI_WIN_NULL);
        MPI_Abort(MPI_COMM_WORLD,2);
    }

    // this is broken because OMPI sucks
    MPI_Win_create(&bc,1024,1,MPI_INFO_NULL,MPI_COMM_WORLD,&c);
    MPI_Win_fence(0,c);
    MPI_Win_free(&c);
    if (c != MPI_WIN_NULL) {
        printf("win null? %d\n",c==MPI_WIN_NULL);
        MPI_Abort(MPI_COMM_WORLD,3);
    }

    MPI_Win_create_dynamic(MPI_INFO_NULL,MPI_COMM_WORLD,&cd);
    MPI_Win_attach(cd,&b,1024);
    MPI_Win_fence(0,cd);
    MPI_Win_detach(cd,&b);
    MPI_Win_free(&cd);
    if (cd != MPI_WIN_NULL) {
        printf("win null? %d\n",cd==MPI_WIN_NULL);
        MPI_Abort(MPI_COMM_WORLD,4);
    }

    fflush(0);
    usleep(1);
    MPI_Barrier(MPI_COMM_WORLD);
    if (me==0) printf("all done\n");

    rc = MPI_Finalize();

    return rc;
}

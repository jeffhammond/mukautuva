#include <stdio.h>
#include <stdint.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int rc;
    rc = MPI_Init(&argc,&argv);

    printf("main: MPI_COMM_WORLD=%lx\n", (intptr_t)MPI_COMM_WORLD);

    int me, np;
    MPI_Comm_rank(MPI_COMM_WORLD,&me);
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    printf("i am %d of %d\n", me, np);

    if (np==3) MPI_Abort(MPI_COMM_SELF,np);

    MPI_Win a, as, c, cd;
    void *ba, *bas;

    MPI_Win_allocate(0,1,MPI_INFO_NULL,MPI_COMM_WORLD,&ba,&a);
    MPI_Win_fence(0,a);
    MPI_Win_free(&a);

    MPI_Win_allocate_shared(0,1,MPI_INFO_NULL,MPI_COMM_SELF,&bas,&as);
    MPI_Win_fence(0,as);
    MPI_Win_free(&as);

    MPI_Win_create(NULL,0,1,MPI_INFO_NULL,MPI_COMM_WORLD,&c);
    MPI_Win_fence(0,c);
    MPI_Win_free(&c);

    char b;
    MPI_Win_create_dynamic(MPI_INFO_NULL,MPI_COMM_WORLD,&cd);
    MPI_Win_attach(cd,&b,1);
    MPI_Win_fence(0,cd);
    MPI_Win_detach(cd,&b);
    MPI_Win_free(&cd);

    rc = MPI_Finalize();

    return rc;
}

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

    MPI_Comm dup;
    MPI_Comm_dup(MPI_COMM_WORLD,&dup);
    MPI_Barrier(dup);
    MPI_Comm_free(&dup);

    MPI_Comm split;
    MPI_Comm_split(MPI_COMM_WORLD,0,-me,&split);
    MPI_Barrier(split);
    MPI_Comm_free(&split);

#if 0
    MPI_Comm shared;
    MPI_Comm_split_type(MPI_COMM_WORLD,MPI_COMM_TYPE_SHARED,0,MPI_INFO_NULL,&shared);
    MPI_Barrier(shared);
    MPI_Comm_free(&shared);
#endif

    rc = MPI_Finalize();

    return rc;
}

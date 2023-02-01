#include <stdio.h>
#include <stdint.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int rc;
    rc = MPI_Init(&argc,&argv);

    printf("MPI_COMM_WORLD=%lx\n", (intptr_t)MPI_COMM_WORLD);

    int me, np;
    MPI_Comm_rank(MPI_COMM_WORLD,&me);
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    printf("i am %d of %d\n", me, np);

    if (np==3) MPI_Abort(MPI_COMM_SELF,np);

    rc = MPI_Finalize();

    return rc;
}

#include <stdio.h>
#include "mpi.h"

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

    printf("wtime = %f wtick = %f\n", MPI_Wtime(), MPI_Wtick());

#if 0
    int me, np;
    MPI_Comm_rank(MPI_COMM_WORLD,&me);
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    printf("i am %d of %d\n", me, np);

    //if (np==3) MPI_Abort(MPI_COMM_SELF,np);
#endif

    rc = MPI_Finalize();

    return rc;
}

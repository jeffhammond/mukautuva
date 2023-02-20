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

    {
        MPI_Comm cart_world;
        int dims[1]     = { np };
        int periodic[1] = { 0 };
        int reorder     = 0;

        MPI_Cart_create(MPI_COMM_WORLD, 1, dims, periodic, reorder, &cart_world);

        int result;
        MPI_Comm_compare(MPI_COMM_WORLD,cart_world,&result);
        if (result != MPI_CONGRUENT) {
            printf("cartesian world is not congruent: %d\n", result);
            MPI_Abort(MPI_COMM_WORLD,result);
        }

        MPI_Comm_free(&cart_world);
        if (cart_world != MPI_COMM_NULL) {
            printf("freed window is not null\n");
            MPI_Abort(MPI_COMM_WORLD,1);
        }
    }

    fflush(0);
    usleep(1);
    MPI_Barrier(MPI_COMM_WORLD);
    if (me==0) printf("all done\n");

    rc = MPI_Finalize();

    return rc;
}

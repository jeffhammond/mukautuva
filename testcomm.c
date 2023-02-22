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

    printf("main: MPI_COMM_WORLD=%lx\n", (intptr_t)MPI_COMM_WORLD);

    int me, np;
    MPI_Comm_rank(MPI_COMM_WORLD,&me);
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    printf("I am %d of %d\n", me, np);

    {
        int result;
        MPI_Comm world = MPI_COMM_WORLD;
        MPI_Comm_compare(MPI_COMM_WORLD,world,&result);
        if (result != MPI_IDENT) MPI_Abort(MPI_COMM_WORLD,result);

        MPI_Comm dup;
        MPI_Comm_dup(MPI_COMM_WORLD,&dup);
        MPI_Barrier(dup);

        MPI_Comm_compare(MPI_COMM_WORLD,dup,&result);
        if (result != MPI_CONGRUENT) MPI_Abort(MPI_COMM_WORLD,result);

        MPI_Comm split;
        MPI_Comm_split(MPI_COMM_WORLD,0,-me,&split);
        MPI_Barrier(split);

        MPI_Comm_compare(MPI_COMM_WORLD,split,&result);
        if (np > 1 && result != MPI_SIMILAR) {
            printf("result=%d, MPI_CONGRUENT=%d MPI_SIMILAR=%d\n", result, MPI_CONGRUENT, MPI_SIMILAR);
            MPI_Abort(MPI_COMM_WORLD,result);
        }
        else if (np == 1 && result != MPI_CONGRUENT) {
            printf("result=%d, MPI_CONGRUENT=%d MPI_SIMILAR=%d\n", result, MPI_CONGRUENT, MPI_SIMILAR);
            MPI_Abort(MPI_COMM_WORLD,result);
        }

        MPI_Comm oddeven;
        MPI_Comm_split(MPI_COMM_WORLD,me%2,me,&oddeven);
        MPI_Barrier(oddeven);

        MPI_Comm_compare(MPI_COMM_WORLD,oddeven,&result);
        if ((np > 1) && (result != MPI_UNEQUAL)) MPI_Abort(MPI_COMM_WORLD,result);

        MPI_Comm shared;
        MPI_Comm_split_type(MPI_COMM_WORLD,MPI_COMM_TYPE_SHARED,0,MPI_INFO_NULL,&shared);
        MPI_Barrier(shared);

        MPI_Comm_free(&split);
        MPI_Comm_free(&oddeven);

        MPI_Comm_free(&shared);
        if (shared != MPI_COMM_NULL) {
            printf("freed window is not null\n");
            MPI_Abort(MPI_COMM_WORLD,1);
        }

        // disconnect is the same as free except it synchronizes
        MPI_Comm_disconnect(&dup);
        if (dup != MPI_COMM_NULL) {
            printf("freed window is not null\n");
            MPI_Abort(MPI_COMM_WORLD,1);
        }
    }

    {
        MPI_Comm split;
        MPI_Comm_split(MPI_COMM_WORLD,MPI_UNDEFINED,0,&split);
        if (split != MPI_COMM_NULL) {
            printf("color=MPI_UNDEFINED but split=%p != MPI_COMM_NULL=%p\n", split, MPI_COMM_NULL);
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

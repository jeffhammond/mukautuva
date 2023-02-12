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

static MPI_Op ops[] = { MPI_MIN, MPI_MAX, MPI_SUM,
                        MPI_BAND, MPI_BOR, MPI_BXOR };

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

    for (int o=0; o<(int)(sizeof(ops)/sizeof(ops[0])); o++)
    {
        MPI_Op op = ops[o];

        int in, out = -1;

        if (op == MPI_MIN || op == MPI_MAX || op == MPI_SUM) {
            in = 100 + me;
        }
        else if (op == MPI_BAND || op == MPI_BOR || op == MPI_BXOR) {
            in = 1;
        }

        rc = MPI_Allreduce(&in, &out, 1, MPI_INT, op, MPI_COMM_WORLD);

        int ref = 0;
        if (op == MPI_MIN) {
            ref = 100;
        }
        else if (op == MPI_MAX) {
            ref = 100 + (np-1);
        }
        else if (op == MPI_SUM) {
            ref = 100 * np + (np-1) * np / 2;
        }
        else if (op == MPI_BAND) {
            ref = 1;
            for (int i=0; i<np; i++) ref &= 1;
        }
        else if (op == MPI_BOR) {
            for (int i=0; i<np; i++) ref |= 1;
        }
        else if (op == MPI_BXOR) {
            for (int i=0; i<np; i++) ref ^= 1;
        }

        if (out != ref) {
            printf("%d: o=%d in=%d out=%d ref=%d\n", me, o, in, out, ref);
            MPI_Abort(MPI_COMM_WORLD,1);
        }

        fflush(0);
        usleep(1);
        MPI_Barrier(MPI_COMM_WORLD);
    }

#if 0
    {
        MPI_Op custom = MPI_OP_NULL;
        MPI_Op_free(&custom);
        if (custom != MPI_OP_NULL) {
            printf("freed handle is not null\n");
            MPI_Abort(MPI_COMM_WORLD,1);
        }
    }
#endif

    fflush(0);
    usleep(1);
    MPI_Barrier(MPI_COMM_WORLD);
    if (me==0) printf("all done\n");

    rc = MPI_Finalize();

    return rc;
}

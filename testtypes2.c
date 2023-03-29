// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#ifdef NOWRAP
    #include <mpi.h>
    #ifdef MPICH
        #define TYPE_FORMAT "%x"
        #define PRINT_REAL_HANDLE(h) printf("real handle=%x\n",h)
    #else
        #define TYPE_FORMAT "%p"
        #define PRINT_REAL_HANDLE(h) printf("real handle=%p\n",h)
    #endif
#else
    #include "mpi.h"
    #define TYPE_FORMAT "%p"
    #define PRINT_REAL_HANDLE(h) printf("real handle=%x=%p\n",*(int*)h,*(void**)h)
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

    {
        MPI_Datatype c1 = MPI_DATATYPE_NULL;
        MPI_Type_contiguous(100, MPI_BYTE, &c1);
        if (c1 == MPI_DATATYPE_NULL) {
            printf("fail 1\n");
            MPI_Abort(MPI_COMM_WORLD,1);
        }

        MPI_Datatype c2 = MPI_DATATYPE_NULL;
        MPI_Type_contiguous(100, c1, &c2);
        if (c2 == MPI_DATATYPE_NULL) {
            printf("fail 2\n");
            MPI_Abort(MPI_COMM_WORLD,2);
        }

        int ni, na, nd, combiner;
        MPI_Type_get_envelope(c1, &ni, &na, &nd, &combiner);
        if (ni != 1 || na != 0 || nd != 1 || combiner != MPI_COMBINER_CONTIGUOUS) {
            printf("c1 get_envelope: ni=%d na=%d nd=%d combiner=%d\n", ni, na, nd, combiner);
            printf("MPI_COMBINER_CONTIGUOUS = %d\n", MPI_COMBINER_CONTIGUOUS);
            MPI_Abort(MPI_COMM_WORLD,3);
        }

        int          * ai = malloc(sizeof(int));
        MPI_Datatype * ad = malloc(sizeof(MPI_Datatype));
        MPI_Type_get_contents(c1, 1, 0, 1, ai, NULL, ad);
        if (ai[0] != 100 || ad[0] != MPI_BYTE) {
            printf("c1 get_contents: ai[]=%d ad[]=" TYPE_FORMAT "\n", ai[0], ad[0]);
            MPI_Abort(MPI_COMM_WORLD,101);
        }

        MPI_Type_get_envelope(c2, &ni, &na, &nd, &combiner);
        if (ni != 1 || na != 0 || nd != 1 || combiner != MPI_COMBINER_CONTIGUOUS) {
            printf("c2 get_envelope: ni=%d na=%d nd=%d combiner=%d\n", ni, na, nd, combiner);
            printf("MPI_COMBINER_CONTIGUOUS = %d\n", MPI_COMBINER_CONTIGUOUS);
            MPI_Abort(MPI_COMM_WORLD,4);
        }

        MPI_Datatype c3;
        MPI_Type_get_contents(c2, 1, 0, 1, ai, NULL, &c3);
        if (ai[0] != 100) {
            printf("c2 get_contents: ai[]=%d ad[]=" TYPE_FORMAT "\n", ai[0], c3);
            MPI_Abort(MPI_COMM_WORLD,101);
        }

        // now see if c3=ad[0] is the same as c1...
        MPI_Type_get_envelope(c3, &ni, &na, &nd, &combiner);
        if (ni != 1 || na != 0 || nd != 1 || combiner != MPI_COMBINER_CONTIGUOUS) {
            printf("ad[0] get_envelope: ni=%d na=%d nd=%d combiner=%d\n", ni, na, nd, combiner);
            printf("MPI_COMBINER_CONTIGUOUS = %d\n", MPI_COMBINER_CONTIGUOUS);
            MPI_Abort(MPI_COMM_WORLD,5);
        }

        MPI_Type_get_contents(c3, 1, 0, 1, ai, NULL, ad);
        if (ai[0] != 100 || ad[0] != MPI_BYTE) {
            printf("ad[0] get_contents: ai[]=%d ad[]=" TYPE_FORMAT "\n", ai[0], ad[0]);
            MPI_Abort(MPI_COMM_WORLD,101);
        }

        free(ai);
        free(ad);

        MPI_Type_free(&c3);
        if (c3 != MPI_DATATYPE_NULL) {
            printf("c3 freed handle is not null\n");
            MPI_Abort(MPI_COMM_WORLD,13);
        }

        MPI_Type_free(&c2);
        if (c2 != MPI_DATATYPE_NULL) {
            printf("c2 freed handle is not null\n");
            MPI_Abort(MPI_COMM_WORLD,12);
        }

        MPI_Type_free(&c1);
        if (c1 != MPI_DATATYPE_NULL) {
            printf("c1 freed handle is not null\n");
            MPI_Abort(MPI_COMM_WORLD,11);
        }
    }

    fflush(0);
    usleep(1);
    MPI_Barrier(MPI_COMM_WORLD);
    if (me==0) printf("all done\n");

    rc = MPI_Finalize();

    return rc;
}

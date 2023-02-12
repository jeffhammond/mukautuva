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

// these are not constants (yet)
static MPI_Datatype types[] = { MPI_CHAR, MPI_SHORT, MPI_INT, MPI_LONG, MPI_LONG_LONG, MPI_FLOAT, MPI_DOUBLE };

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

    for (int t=0; t<(int)(sizeof(types)/sizeof(types[0])); t++)
    {
        MPI_Datatype type = types[t];

        int size;
        MPI_Type_size(type, &size);

        if (me == 0) {
            printf("t=%d type=%p\n", t, type);

            int len;
            char name[MPI_MAX_OBJECT_NAME] = {0};
            MPI_Type_get_name(type, name, &len);
            printf("name=%s\n", name);

            printf("size=%d\n", size);
        }
        fflush(0);
        usleep(1);
        MPI_Barrier(MPI_COMM_WORLD);

        void * buffer = malloc(2*size);
        memset(buffer,0xF,2*size);
        MPI_Request r[2];
        MPI_Isend(buffer,      1, type, me, t, MPI_COMM_WORLD, &r[0]);
        MPI_Irecv(buffer+size, 1, type, me, t, MPI_COMM_WORLD, &r[1]);
        MPI_Waitall(2,r,MPI_STATUSES_IGNORE);
    }

    {
        MPI_Datatype contig = MPI_DATATYPE_NULL;
        MPI_Type_contiguous(100, MPI_BYTE, &contig);

        int size;
        MPI_Type_size(contig, &size);
        if (size != 100) {
            printf("wrong: size=%d\n", size);
            MPI_Abort(MPI_COMM_WORLD,size);
        }

        MPI_Aint lb, extent;
        MPI_Type_get_extent(contig, &lb, &extent);
        if (lb !=0 || extent != 100) {
            printf("\n");
            printf("wrong: lb=%zu extent=%ld\n", lb, extent);
            MPI_Abort(MPI_COMM_WORLD,extent);
        }

        int ni, na, nd, combiner;
        MPI_Type_get_envelope(contig, &ni, &na, &nd, &combiner);
        if (ni != 1 || na != 0 || nd != 1 || combiner != MPI_COMBINER_CONTIGUOUS) {
            printf("get_envelope: ni=%d na=%d nd=%d combiner=%d\n", ni, na, nd, combiner);
            printf("MPI_COMBINER_CONTIGUOUS = %d\n", MPI_COMBINER_CONTIGUOUS);
            MPI_Abort(MPI_COMM_WORLD,extent);
        }

        MPI_Type_free(&contig);
        if (contig != MPI_DATATYPE_NULL) {
            printf("freed handle is not null\n");
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

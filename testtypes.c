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

static MPI_Datatype types[] = { MPI_CHAR, MPI_SHORT, MPI_INT, MPI_LONG, MPI_LONG_LONG, MPI_FLOAT, MPI_DOUBLE };
static size_t type_sizes[] = { sizeof(char), sizeof(short), sizeof(int), sizeof(long),
                               sizeof(long long), sizeof(float), sizeof(double) };
static char type_names[][20] = { "MPI_CHAR", "MPI_SHORT", "MPI_INT", "MPI_LONG",
                                 "MPI_LONG_LONG_INT", "MPI_FLOAT", "MPI_DOUBLE" };

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
        if ((size_t)size != type_sizes[t]) {
            printf("t=%d type=%p\n", t, type);
            MPI_Abort(MPI_COMM_WORLD,size);
        }

        int len;
        char name[MPI_MAX_OBJECT_NAME] = {0};
        MPI_Type_get_name(type, name, &len);
        int cmp = strcmp(name, type_names[t]);
        if (cmp != 0) {
            printf("name=%s\n", name);
            MPI_Abort(MPI_COMM_WORLD,cmp);
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
        MPI_Type_commit(&contig);

        int size;
        MPI_Type_size(contig, &size);
        if (size != 100) {
            printf("wrong: size=%d\n", size);
            MPI_Abort(MPI_COMM_WORLD,size);
        }

        int psize;
        MPI_Pack_size(1, contig, MPI_COMM_SELF, &psize);
        if (psize != 100) {
            printf("wrong: pack size=%d\n", psize);
            MPI_Abort(MPI_COMM_WORLD,psize);
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
            MPI_Abort(MPI_COMM_WORLD,combiner);
        }

        MPI_Type_free(&contig);
        if (contig != MPI_DATATYPE_NULL) {
            printf("freed handle is not null\n");
            MPI_Abort(MPI_COMM_WORLD,1);
        }
    }

    {
        MPI_Datatype vector = MPI_DATATYPE_NULL;
        MPI_Type_vector(10, 10, 20, MPI_BYTE, &vector);
        MPI_Type_commit(&vector);

        MPI_Type_set_name(vector,"vector: 10, 10, 20, MPI_BYTE");
        int len;
        char name[MPI_MAX_OBJECT_NAME] = {0};
        MPI_Type_get_name(vector, name, &len);
        int cmp = strcmp(name, "vector: 10, 10, 20, MPI_BYTE");
        if (cmp != 0) {
            printf("name=%s\n", name);
            MPI_Abort(MPI_COMM_WORLD,cmp);
        }

        int size;
        MPI_Type_size(vector, &size);
        if (size != 100) {
            printf("wrong: size=%d\n", size);
            MPI_Abort(MPI_COMM_WORLD,size);
        }

        int psize;
        MPI_Pack_size(1, vector, MPI_COMM_SELF, &psize);
        if (psize != 100) {
            printf("wrong: pack size=%d\n", psize);
            MPI_Abort(MPI_COMM_WORLD,psize);
        }

        MPI_Aint lb, extent;
        MPI_Type_get_extent(vector, &lb, &extent);
        if (lb !=0 || extent != 190) {
            printf("\n");
            printf("wrong: lb=%zu extent=%ld\n", lb, extent);
            MPI_Abort(MPI_COMM_WORLD,extent);
        }

        int ni, na, nd, combiner;
        MPI_Type_get_envelope(vector, &ni, &na, &nd, &combiner);
        if (ni != 3 || na != 0 || nd != 1 || combiner != MPI_COMBINER_VECTOR) {
            printf("get_envelope: ni=%d na=%d nd=%d combiner=%d\n", ni, na, nd, combiner);
            printf("MPI_COMBINER_VECTOR = %d\n", MPI_COMBINER_VECTOR);
            MPI_Abort(MPI_COMM_WORLD,combiner);
        }

        MPI_Type_free(&vector);
        if (vector != MPI_DATATYPE_NULL) {
            printf("freed handle is not null\n");
            MPI_Abort(MPI_COMM_WORLD,1);
        }
    }

    {
        MPI_Datatype subarray = MPI_DATATYPE_NULL;
        int sizes[2]    = {20,20};
        int subsizes[2] = {10,10};
        int starts[2]   = {0,0};
        MPI_Type_create_subarray(2, sizes, subsizes, starts, MPI_ORDER_FORTRAN, MPI_BYTE, &subarray);
        MPI_Type_commit(&subarray);

        int size;
        MPI_Type_size(subarray, &size);
        if (size != 100) {
            printf("wrong: size=%d\n", size);
            MPI_Abort(MPI_COMM_WORLD,size);
        }

        int psize;
        MPI_Pack_size(1, subarray, MPI_COMM_SELF, &psize);
        if (psize != 100) {
            printf("wrong: pack size=%d\n", psize);
            MPI_Abort(MPI_COMM_WORLD,psize);
        }

        MPI_Aint lb, extent;
        MPI_Type_get_extent(subarray, &lb, &extent);
        if (lb !=0 || extent != 400) {
            printf("\n");
            printf("wrong: lb=%zu extent=%ld\n", lb, extent);
            MPI_Abort(MPI_COMM_WORLD,extent);
        }

        int ni, na, nd, combiner;
        MPI_Type_get_envelope(subarray, &ni, &na, &nd, &combiner);
        if (ni != 8 || na != 0 || nd != 1 || combiner != MPI_COMBINER_SUBARRAY) {
            printf("get_envelope: ni=%d na=%d nd=%d combiner=%d\n", ni, na, nd, combiner);
            printf("MPI_COMBINER_SUBARRAY = %d\n", MPI_COMBINER_SUBARRAY);
            MPI_Abort(MPI_COMM_WORLD,combiner);
        }

        MPI_Type_free(&subarray);
        if (subarray != MPI_DATATYPE_NULL) {
            printf("freed handle is not null\n");
            MPI_Abort(MPI_COMM_WORLD,1);
        }
    }

    {
        MPI_Datatype subarray = MPI_DATATYPE_NULL;
        int sizes[2]    = {20,20};
        int subsizes[2] = {10,10};
        int starts[2]   = {0,0};
        MPI_Type_create_subarray(2, sizes, subsizes, starts, MPI_ORDER_C, MPI_BYTE, &subarray);
        MPI_Type_commit(&subarray);

        int size;
        MPI_Type_size(subarray, &size);
        if (size != 100) {
            printf("wrong: size=%d\n", size);
            MPI_Abort(MPI_COMM_WORLD,size);
        }

        int psize;
        MPI_Pack_size(1, subarray, MPI_COMM_SELF, &psize);
        if (psize != 100) {
            printf("wrong: pack size=%d\n", psize);
            MPI_Abort(MPI_COMM_WORLD,psize);
        }

        MPI_Aint lb, extent;
        MPI_Type_get_extent(subarray, &lb, &extent);
        if (lb !=0 || extent != 400) {
            printf("\n");
            printf("wrong: lb=%zu extent=%ld\n", lb, extent);
            MPI_Abort(MPI_COMM_WORLD,extent);
        }

        int ni, na, nd, combiner;
        MPI_Type_get_envelope(subarray, &ni, &na, &nd, &combiner);
        if (ni != 8 || na != 0 || nd != 1 || combiner != MPI_COMBINER_SUBARRAY) {
            printf("get_envelope: ni=%d na=%d nd=%d combiner=%d\n", ni, na, nd, combiner);
            printf("MPI_COMBINER_SUBARRAY = %d\n", MPI_COMBINER_SUBARRAY);
            MPI_Abort(MPI_COMM_WORLD,combiner);
        }

        MPI_Type_free(&subarray);
        if (subarray != MPI_DATATYPE_NULL) {
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

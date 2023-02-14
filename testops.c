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

void my_reduce_op_1(void *invec, void *inoutvec, int *len, MPI_Datatype * datatype)
{
    printf("my_reduce_op_1\n");
    for (int i=0; i<*len; i++) {
        if (*datatype == MPI_INT) {
            ((int*)inoutvec)[i]    += ((int*)invec)[i];
        }
        else {
            printf("my_reduce_op_1: unsupported datatype\n");
        }
    }
    fflush(0);
}

void my_reduce_op_2(void *invec, void *inoutvec, int *len, MPI_Datatype * datatype)
{
    printf("my_reduce_op_2\n");
    for (int i=0; i<*len; i++) {
        if (*datatype == MPI_INT) {
            ((int*)inoutvec)[i]    += ((int*)invec)[i];
        }
        else {
            printf("my_reduce_op_2: unsupported datatype\n");
        }
    }
    fflush(0);
}
void my_reduce_op_3(void *invec, void *inoutvec, int *len, MPI_Datatype * datatype)
{
    printf("my_reduce_op_3\n");
    for (int i=0; i<*len; i++) {
        if (*datatype == MPI_INT) {
            ((int*)inoutvec)[i]    += ((int*)invec)[i];
        }
        else {
            printf("my_reduce_op_3: unsupported datatype\n");
        }
    }
    fflush(0);
}

void my_reduce_op(void *invec, void *inoutvec, int *len, MPI_Datatype * datatype)
{
    //printf("my_reduce_op: in=%p inout=%p *len=%d *datatype=%p\n", invec, inoutvec, *len, *datatype);
    //printf("my_reduce_op: MPI_INT=%p MPI_DOUBLE=%p\n", MPI_INT, MPI_DOUBLE);
    //printf("my_reduce_op: *MPI_INT=%p *MPI_DOUBLE=%p\n", *(void**)MPI_INT, *(void**)MPI_DOUBLE);

    for (int i=0; i<*len; i++) {
        if (*datatype == MPI_INT) {
            //printf("my_reduce_op: MPI_INT detected\n");
            ((int*)inoutvec)[i]    += ((int*)invec)[i];
        }
        else if (*datatype == MPI_DOUBLE) {
            //printf("my_reduce_op: MPI_DOUBLE detected\n");
            ((double*)inoutvec)[i] += ((double*)invec)[i];
        }
        else {
            printf("my_reduce_op: unsupported datatype\n");
        }
    }

    fflush(0);
}

#if 0
void wrap_reduce_op(void *invec, void *inoutvec, int *len, MPI_Datatype * datatype)
{
    printf("wrap: in=%p inout=%p *len=%d *datatype=%p\n", invec, inoutvec, *len, *datatype);
    printf("wrap: MPI_INT=%p MPI_DOUBLE=%p\n", MPI_INT, MPI_DOUBLE);
    printf("wrap: *MPI_INT=%p *MPI_DOUBLE=%p\n", *(void**)MPI_INT, *(void**)MPI_DOUBLE);
    my_reduce_op(invec, inoutvec, len, (MPI_Datatype*)&datatype);
}
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

#if 1
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
#else
    (void)ops;
#endif

    {
        printf("my_reduce_op=%p\n", my_reduce_op);

        MPI_Op custom = MPI_OP_NULL;
        //rc = MPI_Op_create(&wrap_reduce_op, 0, &custom);
        rc = MPI_Op_create(&my_reduce_op, 0, &custom);
        if (rc != MPI_SUCCESS || custom == MPI_OP_NULL) {
            printf("MPI_Op_create failed\n");
            MPI_Abort(MPI_COMM_WORLD,rc);
        }

        int in = 10, out = -9999;
        printf("&in=%p &out=%p\n", &in, &out);
        rc = MPI_Allreduce(&in, &out, 1, MPI_INT, custom, MPI_COMM_WORLD);
        if (rc != MPI_SUCCESS) {
            printf("MPI_Allreduce failed\n");
            MPI_Abort(MPI_COMM_WORLD,rc);
        }
        printf("in = %d out = %d ref = %d \n", in, out, in * np);

        MPI_Op_free(&custom);
        if (custom != MPI_OP_NULL) {
            printf("freed handle is not null\n");
            MPI_Abort(MPI_COMM_WORLD,1);
        }
    }

    {
        printf("my_reduce_op_1=%p\n", my_reduce_op_1);
        printf("my_reduce_op_2=%p\n", my_reduce_op_2);
        printf("my_reduce_op_3=%p\n", my_reduce_op_3);

        MPI_Op f1 = MPI_OP_NULL;
        MPI_Op f2 = MPI_OP_NULL;
        MPI_Op f3 = MPI_OP_NULL;

        rc = MPI_Op_create(&my_reduce_op_1, 0, &f1);
        if (rc != MPI_SUCCESS || f1 == MPI_OP_NULL) {
            printf("MPI_Op_create failed\n");
            MPI_Abort(MPI_COMM_WORLD,rc);
        }

        rc = MPI_Op_create(&my_reduce_op_2, 0, &f2);
        if (rc != MPI_SUCCESS || f2 == MPI_OP_NULL) {
            printf("MPI_Op_create failed\n");
            MPI_Abort(MPI_COMM_WORLD,rc);
        }

        rc = MPI_Op_create(&my_reduce_op_3, 0, &f3);
        if (rc != MPI_SUCCESS || f3 == MPI_OP_NULL) {
            printf("MPI_Op_create failed\n");
            MPI_Abort(MPI_COMM_WORLD,rc);
        }

        int in = 10, out = -9999;
        rc = MPI_Allreduce(&in, &out, 1, MPI_INT, f1, MPI_COMM_WORLD);
        if (rc != MPI_SUCCESS) {
            printf("MPI_Allreduce 1 failed\n");
            MPI_Abort(MPI_COMM_WORLD,rc);
        }
        printf("f1: in = %d out = %d ref = %d \n", in, out, in * np);

        out = -1;
        rc = MPI_Allreduce(&in, &out, 1, MPI_INT, f2, MPI_COMM_WORLD);
        if (rc != MPI_SUCCESS) {
            printf("MPI_Allreduce 2 failed\n");
            MPI_Abort(MPI_COMM_WORLD,rc);
        }
        printf("f2: in = %d out = %d ref = %d \n", in, out, in * np);

        out = -10;
        rc = MPI_Allreduce(&in, &out, 1, MPI_INT, f3, MPI_COMM_WORLD);
        if (rc != MPI_SUCCESS) {
            printf("MPI_Allreduce 3 failed\n");
            MPI_Abort(MPI_COMM_WORLD,rc);
        }
        printf("f3: in = %d out = %d ref = %d \n", in, out, in * np);

        MPI_Op_free(&f1);
        if (f1 != MPI_OP_NULL) {
            printf("freed handle is not null\n");
            MPI_Abort(MPI_COMM_WORLD,1);
        }

        MPI_Op_free(&f2);
        if (f2 != MPI_OP_NULL) {
            printf("freed handle is not null\n");
            MPI_Abort(MPI_COMM_WORLD,2);
        }

        MPI_Op_free(&f3);
        if (f3 != MPI_OP_NULL) {
            printf("freed handle is not null\n");
            MPI_Abort(MPI_COMM_WORLD,3);
        }
    }


    fflush(0);
    usleep(1);
    MPI_Barrier(MPI_COMM_WORLD);
    if (me==0) printf("all done\n");

    rc = MPI_Finalize();

    return rc;
}

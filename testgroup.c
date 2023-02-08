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
    fflush(0);
    usleep(1);
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Group group_world, gwdup;
    MPI_Comm_group(MPI_COMM_WORLD, &group_world);
    MPI_Comm_group(MPI_COMM_WORLD, &gwdup);

    int result;
    MPI_Group_compare(group_world,gwdup,&result);
    if (result != MPI_IDENT) {
        printf("%d: result = %d MPI_IDENT = %d MPI_SIMILAR = %d MPI_UNEQUAL = %d\n",
                me, result, MPI_IDENT, MPI_SIMILAR, MPI_UNEQUAL);
        fflush(0);
        usleep(1);
        MPI_Abort(MPI_COMM_WORLD,1);
    }

    int gme, gnp;
    MPI_Group_rank(group_world,&gme);
    MPI_Group_size(group_world,&gnp);

    if (me != gme || np != gnp) {
        printf("%d : %d :: %d : %d\n", me, gme, np, gnp);
        MPI_Abort(MPI_COMM_WORLD,1);
    }

    MPI_Group group1;
    int excluded[1] = { 0 };
    MPI_Group_excl(group_world,1,excluded,&group1);
    MPI_Group_size(group1,&gnp);
    if (gnp != (np-1)) {
        printf("%d: excl size = %d\n", me, gnp);
        fflush(0);
        usleep(1);
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Group group2;
    int * included = malloc((np-1)*sizeof(int));
    for (int i=1; i<np; i++) {
        included[i-1] = i;
    }
    MPI_Group_incl(group_world,np-1,included,&group2);
    free(included);
    MPI_Group_size(group2,&gnp);
    if (gnp != (np-1)) {
        printf("%d: incl size = %d\n", me, gnp);
        fflush(0);
        usleep(1);
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Group diff;
    MPI_Group_difference(group1,group2,&diff);
    MPI_Group_size(diff,&gnp);
    if (gnp != 0) {
        printf("%d: diff size = %d\n", me, gnp);
        fflush(0);
        usleep(1);
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Group union1;
    MPI_Group_union(group1,group2,&union1);
    MPI_Group_size(union1,&gnp);
    if (gnp != (np-1)) {
        printf("%d: union size = %d\n", me, gnp);
        fflush(0);
        usleep(1);
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Group_compare(group_world,group1,&result);
    if (result != MPI_UNEQUAL) {
        printf("%d: result = %d MPI_IDENT = %d MPI_SIMILAR = %d MPI_UNEQUAL = %d\n",
                me, result, MPI_IDENT, MPI_SIMILAR, MPI_UNEQUAL);
        fflush(0);
        usleep(1);
        MPI_Abort(MPI_COMM_WORLD,1);
    }

    int * ranks1 = malloc(np * sizeof(int));
    for (int i=0; i<np; i++) ranks1[i] = i;
    int * ranks2 = malloc(np * sizeof(int));
    MPI_Group_translate_ranks(group_world,np,ranks1,group2,ranks2);

    int errors = 0;
    errors += (ranks2[0] != MPI_UNDEFINED);
    for (int i=1; i<np; i++) {
        errors += (ranks2[i] != (i-1));
    }
    if (errors > 0) {
        printf("%d: errors = %d ranks2 = ", me, errors);
        for (int i=0; i<np; i++) printf("%d,",ranks2[i]);
        printf("\n");
        if (me==0) printf("MPI_UNDEFINED = %d\n", MPI_UNDEFINED);
        fflush(0);
        usleep(1);
    }
    free(ranks2);
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Group_free(&union1);
    MPI_Group_free(&diff);
    MPI_Group_free(&group2);
    MPI_Group_free(&group1);
    MPI_Group_free(&group_world);

    fflush(0);
    usleep(1);
    MPI_Barrier(MPI_COMM_WORLD);
    if (me==0) printf("all done\n");

    rc = MPI_Finalize();

    return rc;
}

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

    // create the world group
    MPI_Group group_world = MPI_GROUP_NULL;
    MPI_Comm_group(MPI_COMM_WORLD, &group_world);

    // query the world group
    int gme, gnp;
    MPI_Group_rank(group_world,&gme);
    MPI_Group_size(group_world,&gnp);
    if (me != gme || np != gnp) {
        printf("%d : %d :: %d : %d\n", me, gme, np, gnp);
        MPI_Abort(MPI_COMM_WORLD,1);
    }

    // query the empty group
    MPI_Group_rank(MPI_GROUP_EMPTY,&gme);
    MPI_Group_size(MPI_GROUP_EMPTY,&gnp);
    if (MPI_UNDEFINED != gme || 0 != gnp) {
        printf("%d : %d :: %d : %d\n", MPI_UNDEFINED, gme, 0, gnp);
        MPI_Abort(MPI_COMM_WORLD,1);
    }

    // create a new world group
    MPI_Group dup1;
    MPI_Comm_group(MPI_COMM_WORLD, &dup1);

    // compare two world groups
    int result;
    MPI_Group_compare(group_world,dup1,&result);
    if (result != MPI_IDENT) {
        printf("%d: result = %d MPI_IDENT = %d MPI_SIMILAR = %d MPI_UNEQUAL = %d\n",
                me, result, MPI_IDENT, MPI_SIMILAR, MPI_UNEQUAL);
        fflush(0);
        usleep(1);
        MPI_Abort(MPI_COMM_WORLD,1);
    }

    // test excl using all but rank 0
    MPI_Group excl1;
    int excluded[1] = { 0 };
    MPI_Group_excl(group_world,1,excluded,&excl1);
    MPI_Group_size(excl1,&gnp);
    if (gnp != (np-1)) {
        printf("%d: excl size = %d\n", me, gnp);
        fflush(0);
        usleep(1);
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    // test incl using all but rank 0
    MPI_Group incl1;
    int * included = malloc((np-1)*sizeof(int));
    for (int i=1; i<np; i++) {
        included[i-1] = i;
    }
    MPI_Group_incl(group_world,np-1,included,&incl1);
    free(included);
    MPI_Group_size(incl1,&gnp);
    if (gnp != (np-1)) {
        printf("%d: incl size = %d\n", me, gnp);
        fflush(0);
        usleep(1);
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    // test diff using equivalent groups, so diff is empty
    MPI_Group diff1;
    MPI_Group_difference(excl1,incl1,&diff1);
    MPI_Group_size(diff1,&gnp);
    MPI_Group_compare(diff1, MPI_GROUP_EMPTY ,&result);
    if (gnp != 0 || result != MPI_IDENT) {
        printf("%d: diff1 size = %d\n", me, gnp);
        printf("result = %d diff1 = %p\n MPI_GROUP_EMPTY = %p\n", result, diff1, MPI_GROUP_EMPTY);
        fflush(0);
        usleep(1);
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    // test union with equivalent groups, so union is the same
    MPI_Group union1;
    MPI_Group_union(excl1,incl1,&union1);
    MPI_Group_size(union1,&gnp);
    if (gnp != (np-1)) {
        printf("%d: union1 size = %d\n", me, gnp);
        fflush(0);
        usleep(1);
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    // test compare with unequal groups
    MPI_Group_compare(group_world,excl1,&result);
    if (result != MPI_UNEQUAL) {
        printf("%d: result = %d MPI_IDENT = %d MPI_SIMILAR = %d MPI_UNEQUAL = %d\n",
                me, result, MPI_IDENT, MPI_SIMILAR, MPI_UNEQUAL);
        fflush(0);
        usleep(1);
        MPI_Abort(MPI_COMM_WORLD,1);
    }

    // test rank translation
    int * ranks1 = malloc(np * sizeof(int));
    for (int i=0; i<np; i++) ranks1[i] = i;
    int * ranks2 = malloc(np * sizeof(int));
    MPI_Group_translate_ranks(group_world,np,ranks1,incl1,ranks2);
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
    MPI_Group_free(&diff1);
    MPI_Group_free(&incl1);
    MPI_Group_free(&excl1);
    MPI_Group_free(&dup1);
    MPI_Group_free(&group_world);

    if (group_world != MPI_GROUP_NULL) {
        printf("freed group is not null\n");
    }

    fflush(0);
    usleep(1);
    MPI_Barrier(MPI_COMM_WORLD);
    if (me==0) printf("all done\n");

    rc = MPI_Finalize();

    return rc;
}

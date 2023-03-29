// SPDX-License-Identifier: MIT

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
    MPI_Barrier(MPI_COMM_WORLD);
    usleep(1);

    if (np < 2) {
        printf("this test requires np > 1\n");
        MPI_Abort(MPI_COMM_WORLD,np);
    }

    // Example 5.22 An elaborate example.
    {
        int   position, i = 200;
        float a[200];
        char  buff[1000]; /* larger than or equal to the size returned from MPI_PACK_SIZE for 1,newtype */
        if (me == 0)
        {
            /* SENDER CODE */
            int len[2];
            MPI_Aint disp[2];
            MPI_Datatype type[2], newtype;

            /* build datatype for i followed by a[0]...a[i-1] */
            len[0] = 1;
            len[1] = i;
            MPI_Get_address(&i, disp);
            MPI_Get_address(a, disp+1);

            type[0] = MPI_INT;
            type[1] = MPI_FLOAT;
            MPI_Type_create_struct(2, len, disp, type, &newtype);
            MPI_Type_commit(&newtype);

            /* Pack i followed by a[0]...a[i-1]*/
            position = 0;
            MPI_Pack(MPI_BOTTOM, 1, newtype, buff, 1000, &position, MPI_COMM_WORLD);

            /* Send */
            MPI_Send(buff, position, MPI_PACKED, 1, 0, MPI_COMM_WORLD);
            // One can replace the last three lines with
            // MPI_Send(MPI_BOTTOM, 1, newtype, 1, 0, MPI_COMM_WORLD);

            MPI_Type_free(&newtype);
        }
        else if (me == 1)
        {
            /* RECEIVER CODE */
            MPI_Status status;
            /* Receive */
            MPI_Recv(buff, 1000, MPI_PACKED, 0, 0, MPI_COMM_WORLD, &status);
            /* Unpack i */
            position = 0;
            MPI_Unpack(buff, 1000, &position, &i, 1, MPI_INT, MPI_COMM_WORLD);
            /* Unpack a[0]...a[i-1] */
            MPI_Unpack(buff, 1000, &position, a, i, MPI_FLOAT, MPI_COMM_WORLD);
        }
    }

    fflush(0);
    usleep(1);
    MPI_Barrier(MPI_COMM_WORLD);
    if (me==0) printf("all done\n");

    rc = MPI_Finalize();

    return rc;
}
